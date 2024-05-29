#include <Windows.h>
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <vector>
#include <string>
#include <sstream>
#pragma comment(lib, "wbemuuid.lib")

// Get-WmiObject Win32_PnPEntity | Format-List *

class Win32_PnPEntity {
public:
    uint16_t Availability;
    std::wstring Caption;
    std::wstring ClassGuid;
    std::vector<std::wstring> CompatibleID;
    uint32_t ConfigManagerErrorCode;
    BOOL ConfigManagerUserConfig;
    std::wstring CreationClassName;
    std::wstring Description;
    std::wstring DeviceID;
    BOOL ErrorCleared;
    std::wstring ErrorDescription;
    std::vector<std::wstring> HardwareID;
    uint32_t LastErrorCode;
    std::wstring Manufacturer;
    std::wstring Name;
    std::wstring PNPClass;
    std::wstring PNPDeviceID;
    BOOL PowerManagementSupported;
    BOOL Present;
    std::wstring Service;
    std::wstring Status;
    uint16_t StatusInfo;
    std::wstring SystemCreationClassName;
    std::wstring SystemName;

    std::wstring to_string() const {
        std::wstringstream ss;
        ss << L"Availability: " << Availability << std::endl;
        ss << L"Caption: " << Caption << std::endl;
        ss << L"ClassGuid: " << ClassGuid << std::endl;

        ss << L"CompatibleID: { ";
        for (const auto& id : CompatibleID) {
            ss << id << L", ";
        }
        ss << L"}" << std::endl;

        ss << L"ConfigManagerErrorCode: " << ConfigManagerErrorCode << std::endl;
        ss << L"ConfigManagerUserConfig: " << ConfigManagerUserConfig << std::endl;
        ss << L"CreationClassName: " << CreationClassName << std::endl;
        ss << L"Description: " << Description << std::endl;
        ss << L"DeviceID: " << DeviceID << std::endl;
        ss << L"ErrorCleared: " << ErrorCleared << std::endl;
        ss << L"ErrorDescription: " << ErrorDescription << std::endl;

        ss << L"HardwareID: { ";
        for (const auto& id : HardwareID) {
            ss << id << L", ";
        }
        ss << L"}" << std::endl;

        ss << L"LastErrorCode: " << LastErrorCode << std::endl;
        ss << L"Manufacturer: " << Manufacturer << std::endl;
        ss << L"Name: " << Name << std::endl;
        ss << L"PNPClass: " << PNPClass << std::endl;
        ss << L"PNPDeviceID: " << PNPDeviceID << std::endl;
        ss << L"PowerManagementSupported: " << PowerManagementSupported << std::endl;
        ss << L"Present: " << Present << std::endl;
        ss << L"Service: " << Service << std::endl;
        ss << L"Status: " << Status << std::endl;
        ss << L"StatusInfo: " << StatusInfo << std::endl;
        ss << L"SystemCreationClassName: " << SystemCreationClassName << std::endl;
        ss << L"SystemName: " << SystemName << std::endl;

        return ss.str();
    }
};

std::wstring ConvertToWString(const VARIANT& vtProp) {
    if (vtProp.vt == VT_NULL || vtProp.vt == VT_EMPTY)
        return L"<null>";
    else
        return vtProp.bstrVal;
}

uint16_t ConvertToUInt16(const VARIANT& vtProp) {
    if (vtProp.vt == VT_NULL || vtProp.vt == VT_EMPTY)
        return -1;
    else
        return vtProp.uiVal;
}

uint16_t ConvertToUInt32(const VARIANT& vtProp) {
    if (vtProp.vt == VT_NULL || vtProp.vt == VT_EMPTY)
        return -1;
    else
        return vtProp.uintVal;
}

BOOL ConvertToBool(const VARIANT& vtProp) {
    if (vtProp.vt == VT_NULL || vtProp.vt == VT_EMPTY)
        return -1;
    else
        return vtProp.boolVal;
}



std::vector<std::wstring> ConvertToWStringVector(const VARIANT& vtProp) {
    std::vector<std::wstring> result;

    if (vtProp.vt == (VT_ARRAY | VT_BSTR)) {
        SAFEARRAY* psa = vtProp.parray;
        if (psa != nullptr && psa->cDims > 0) {
            LONG lBound, uBound;
            SafeArrayGetLBound(psa, 1, &lBound);
            SafeArrayGetUBound(psa, 1, &uBound);
            for (LONG i = lBound; i <= uBound; i++) {
                BSTR bstr;
                SafeArrayGetElement(psa, &i, &bstr);
                if (bstr != nullptr) {
                    result.push_back(std::wstring(bstr));
                    SysFreeString(bstr);
                }
            }
        }
    }

    return result;
}



std::vector<Win32_PnPEntity> GetPnPEntities() {
    std::vector<Win32_PnPEntity> devices;

    HRESULT hres;

    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM library. Error code: " << hres << std::endl;
        return devices;
    }

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
        std::cerr << "Failed to initialize security. Error code: " << hres << std::endl;
        CoUninitialize();
        return devices;
    }

    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc
    );
    if (FAILED(hres)) {
        std::cerr << "Failed to create IWbemLocator object. Error code: " << hres << std::endl;
        CoUninitialize();
        return devices;
    }

    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc
    );
    if (FAILED(hres)) {
        std::cerr << "Could not connect. Error code: " << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return devices;
    }

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
        std::cerr << "Could not set proxy blanket. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return devices;
    }

    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_PnPEntity"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
    );
    if (FAILED(hres)) {
        std::cerr << "Query failed. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return devices;
    }

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn) {
            break;
        }

        VARIANT vtProp;

        Win32_PnPEntity entity;

        hr = pclsObj->Get(L"Availability", 0, &vtProp, 0, 0);
        entity.Availability = ConvertToUInt16(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
        entity.Caption = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"ClassGuid", 0, &vtProp, 0, 0);
        entity.ClassGuid = ConvertToWString(vtProp);
        VariantClear(&vtProp);
       
        hr = pclsObj->Get(L"CompatibleID", 0, &vtProp, 0, 0);
        entity.CompatibleID = ConvertToWStringVector(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"ConfigManagerErrorCode", 0, &vtProp, 0, 0);
        entity.ConfigManagerErrorCode = ConvertToUInt32(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"ConfigManagerUserConfig", 0, &vtProp, 0, 0);
        entity.ConfigManagerUserConfig = ConvertToBool(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"CreationClassName", 0, &vtProp, 0, 0);
        entity.CreationClassName = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
        entity.Description = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
        entity.DeviceID = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"ErrorCleared", 0, &vtProp, 0, 0);
        entity.ErrorCleared = ConvertToBool(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"ErrorDescription", 0, &vtProp, 0, 0);
        entity.ErrorDescription = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"HardwareID", 0, &vtProp, 0, 0);
        entity.HardwareID = ConvertToWStringVector(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"LastErrorCode", 0, &vtProp, 0, 0);
        entity.LastErrorCode = ConvertToUInt32(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
        entity.Manufacturer = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        entity.Name = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"PNPClass", 0, &vtProp, 0, 0);
        entity.PNPClass = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"PNPDeviceID", 0, &vtProp, 0, 0);
        entity.PNPDeviceID = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"PowerManagementSupported", 0, &vtProp, 0, 0);
        entity.PowerManagementSupported = ConvertToBool(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"Present", 0, &vtProp, 0, 0);
        entity.Present = ConvertToBool(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"Service", 0, &vtProp, 0, 0);
        entity.Service = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);
        entity.Status = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"StatusInfo", 0, &vtProp, 0, 0);
        entity.StatusInfo = ConvertToUInt16(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"SystemCreationClassName", 0, &vtProp, 0, 0);
        entity.SystemCreationClassName = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"SystemName", 0, &vtProp, 0, 0);
        entity.SystemName = ConvertToWString(vtProp);
        VariantClear(&vtProp);

        devices.push_back(entity);

        pclsObj->Release();
    }

    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();

    CoUninitialize();

    return devices;
}

int main() {
    setlocale(LC_ALL, "Ru");

    std::vector<Win32_PnPEntity> devices = GetPnPEntities();

    for (const auto& device : devices) {
        std::wcout << device.to_string() << "\n\n";
    }

    return 0;
}
