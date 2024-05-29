#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

int main() {
    setlocale(LC_ALL, "Ru");

    HRESULT hres;

    // Инициализация COM библиотеки
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Не удалось инициализировать COM библиотеку. Код ошибки: " << hres << std::endl;
        return 1;
    }

    // Получение указателя на интерфейс WMI
    IWbemLocator* pLoc = nullptr;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
        std::cerr << "Не удалось создать экземпляр IWbemLocator. Код ошибки: " << hres << std::endl;
        CoUninitialize();
        return 1;
    }

    // Получение указателя на сервис WMI
    IWbemServices* pSvc = nullptr;
    hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, 0, NULL, 0, 0, &pSvc);
    if (FAILED(hres)) {
        std::cerr << "Не удалось соединиться с сервисом WMI. Код ошибки: " << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Установка безопасности
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    if (FAILED(hres)) {
        std::cerr << "Не удалось установить безопасность для сервиса WMI. Код ошибки: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Выполнение запроса WMI
    IEnumWbemClassObject* pEnumerator = nullptr;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_PhysicalMemory"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr,
        &pEnumerator);
    if (FAILED(hres)) {
        std::cerr << "Не удалось выполнить запрос WMI. Код ошибки: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Обработка результатов запроса
    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;
    while (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (uReturn == 0)
            break;

        VARIANT vtProp;
        hres = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
        if (FAILED(hres)) {
            std::cerr << "Не удалось получить свойство Description. Код ошибки: " << hres << std::endl;
            pclsObj->Release();
            continue;
        }
        std::wcout << L"Описание: " << vtProp.bstrVal << std::endl;
        VariantClear(&vtProp);

        hres = pclsObj->Get(L"Capacity", 0, &vtProp, 0, 0);
        if (FAILED(hres)) {
            std::cerr << "Не удалось получить свойство Capacity. Код ошибки: " << hres << std::endl;
            pclsObj->Release();
            continue;
        }

        ULONGLONG ulCapacity = 0;
        if (vtProp.vt == VT_BSTR) {
            ulCapacity = wcstoull(vtProp.bstrVal, nullptr, 10);
        }

        // Вывод емкости в MB
        std::wcout << L"Емкость: " << ulCapacity / (1024 * 1024) << L" MB" << std::endl;

        VariantClear(&vtProp);

        hres = pclsObj->Get(L"Speed", 0, &vtProp, 0, 0);
        if (FAILED(hres)) {
            std::cerr << "Не удалось получить свойство Speed. Код ошибки: " << hres << std::endl;
            pclsObj->Release();
            continue;
        }
        std::wcout << L"Частота: " << vtProp.uintVal << L" MHz" << std::endl;
        VariantClear(&vtProp);

        // Другие свойства, которые могут быть полезными, могут быть получены аналогичным образом

        pclsObj->Release();
    }

    // Освобождение ресурсов
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();


    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    while (true) {
        GlobalMemoryStatusEx(&memoryStatus);

        std::cout << "Общее количество физической памяти: " << memoryStatus.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Количество доступной физической памяти: " << memoryStatus.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Общее количество виртуальной памяти: " << memoryStatus.ullTotalVirtual / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Количество доступной виртуальной памяти: " << memoryStatus.ullAvailVirtual / (1024 * 1024) << " MB" << std::endl;
        
        std::cout << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
   

    return 0;
}
