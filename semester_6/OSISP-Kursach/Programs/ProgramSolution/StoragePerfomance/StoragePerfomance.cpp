#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")


int main() {
    HRESULT hres;

    // Инициализация COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM library. Error code: " << hres << std::endl;
        return 1;
    }

    // Инициализация WMI
    hres = CoInitializeSecurity(
        NULL,
        -1,                          // Разрешить WMI выполнение в локальной и удаленной среде.
        NULL,                        // Резервное хранилище для настроек
        NULL,                        // Использовать текущие учетные данные для установки защиты.
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Установить уровень аутентификации на уровень по умолчанию.
        RPC_C_IMP_LEVEL_IMPERSONATE, // Установить уровень имперсонации на уровень по умолчанию.
        NULL,                        // Использовать текущий принципал для аутентификации.
        EOAC_NONE,                   // Установить параметры безопасности на уровень по умолчанию.
        NULL                         // Зарезервировано.
    );
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize security. Error code: " << hres << std::endl;
        CoUninitialize();
        return 1;
    }

    // Получение указателя на объект управления WMI
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
        return 1;
    }

    // Получение указателя на сервис WMI
    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),  // Namespace
        NULL,                      // User name
        NULL,                      // Password
        0,                         // Locale
        NULL,                      // Security flags
        0,                         // Authority
        0,                         // Context object
        &pSvc                      // IWbemServices proxy
    );
    if (FAILED(hres)) {
        std::cerr << "Could not connect to WMI server. Error code: " << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Установка уровня аутентификации на использование учетных данных текущего пользователя
    hres = CoSetProxyBlanket(
        pSvc,                        // IWbemServices proxy
        RPC_C_AUTHN_WINNT,           // Аутентификация
        RPC_C_AUTHZ_NONE,            // Уровень авторизации
        NULL,                        // Server principal name
        RPC_C_AUTHN_LEVEL_CALL,      // Уровень аутентификации
        RPC_C_IMP_LEVEL_IMPERSONATE, // Уровень имперсонации
        NULL,                        // Учетные данные текущего пользователя
        EOAC_NONE                    // Установить параметры безопасности на уровень по умолчанию.
    );
    if (FAILED(hres)) {
        std::cerr << "Could not set proxy blanket. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Получение объектов Win32_LogicalDisk
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_LogicalDisk"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
    );
    if (FAILED(hres)) {
        std::cerr << "Query for disk drives failed. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Перечисление результатов запроса WMI
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    while (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (uReturn == 0)
            break;

        VARIANT vtProp;
        // Получение свойства "DeviceID" (буква диска)
        hres = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
        if (FAILED(hres)) {
            std::wcout << L"DeviceID: Unavailable" << std::endl;
            pclsObj->Release();
            continue;
        }
        std::wcout << L"DeviceID: " << vtProp.bstrVal << std::endl;
        VariantClear(&vtProp);

        // Получение свойства "Size" (размер диска)
        hres = pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
        if (FAILED(hres)) {
            std::wcout << L"Size: Unavailable" << std::endl;
        }
        else {

            ULONGLONG ulSize = 0;
            if (vtProp.vt == VT_BSTR) {
                ulSize = wcstoull(vtProp.bstrVal, nullptr, 10);
            }

            std::wcout << L"Size: " << ulSize / (1024 * 1024 * 1024.0) << L" GB" << std::endl;
            VariantClear(&vtProp);
        }

        // Получение свойства "FreeSpace" (свободное место на диске)
        hres = pclsObj->Get(L"FreeSpace", 0, &vtProp, 0, 0);
        if (FAILED(hres)) {
            std::wcout << L"FreeSpace: Unavailable" << std::endl;
        }
        else {

            ULONGLONG ulSpace = 0;
            if (vtProp.vt == VT_BSTR) {
                ulSpace = wcstoull(vtProp.bstrVal, nullptr, 10);
            }

            std::wcout << L"FreeSpace: " << ulSpace / (1024 * 1024 * 1024.0) << L" GB" << std::endl;
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }

    // Очистка
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return 0;
}
