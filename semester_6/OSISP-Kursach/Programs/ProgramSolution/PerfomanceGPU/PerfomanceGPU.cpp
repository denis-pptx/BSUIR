#include <iostream>
#include <comdef.h>
#include <WbemIdl.h>
#include <comutil.h>

#pragma comment(lib, "wbemuuid.lib")

using namespace std;

int main() {
    HRESULT hres;

    // Initialize COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        cout << "Failed to initialize COM library. Error code: " << hres << endl;
        return 1;
    }

    // Initialize COM security
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );
    if (FAILED(hres)) {
        cout << "Failed to initialize security. Error code: " << hres << endl;
        CoUninitialize();
        return 1;
    }

    // Obtain the initial locator to WMI
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc
    );
    if (FAILED(hres)) {
        cout << "Failed to create IWbemLocator object. Error code: " << hres << endl;
        CoUninitialize();
        return 1;
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method
    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // WMI namespace
        NULL, // User name
        NULL, // User password
        0, // Locale
        NULL, // Security flags
        0, // Authority
        0, // Context object
        &pSvc // IWbemServices proxy
    );
    if (FAILED(hres)) {
        cout << "Failed to connect to WMI namespace. Error code: " << hres << endl;
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Set security levels on the proxy
    hres = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
    );
    if (FAILED(hres)) {
        cout << "Failed to set proxy blanket. Error code: " << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Use the IWbemServices pointer to make requests of WMI
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_VideoController"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
    );
    if (FAILED(hres)) {
        cout << "Query for operating system name failed. Error code: " << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Get the data from the query in step 7
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (0 == uReturn) {
            break;
        }

        VARIANT vtProp;

        // Get the value of the Name property
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        wcout << "GPU Name: " << vtProp.bstrVal << endl;
        VariantClear(&vtProp);

        // Get the value of the AdapterRAM property
        hr = pclsObj->Get(L"AdapterRAM", 0, &vtProp, 0, 0);
        wcout << "GPU RAM: " << vtProp.ulVal / (1024 * 1024) << " MB" << endl;
        VariantClear(&vtProp);

        // Get the value of the AdapterCompatibility property
        hr = pclsObj->Get(L"AdapterCompatibility", 0, &vtProp, 0, 0);
        wcout << "GPU Compatibility: " << vtProp.bstrVal << endl;
        VariantClear(&vtProp);

        pclsObj->Release();
    }

    // Cleanup
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return 0;
}
