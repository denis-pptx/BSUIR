#include <iostream>
#include <comdef.h>
#include <WbemIdl.h>
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <Powrprof.h>


#pragma comment(lib, "Powrprof.lib")

#pragma comment(lib, "wbemuuid.lib")

typedef struct _PROCESSOR_POWER_INFORMATION {
    ULONG  Number;
    ULONG  MaxMhz;
    ULONG  CurrentMhz;
    ULONG  MhzLimit;
    ULONG  MaxIdleState;
    ULONG  CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;

static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;


    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME& ft)
{
    return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.  Returns -1.0 on error.
float GetCPULoad()
{
    FILETIME idleTime, kernelTime, userTime;
    return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
}

int main() {
    setlocale(LC_ALL, "Russian");

    SYSTEM_INFO si = { 0 };
    GetSystemInfo(&si);

    std::vector<PROCESSOR_POWER_INFORMATION> a(si.dwNumberOfProcessors);
    DWORD dwSize = sizeof(PROCESSOR_POWER_INFORMATION) * si.dwNumberOfProcessors;

    if (CallNtPowerInformation(ProcessorInformation, NULL, 0, &a[0], dwSize) == ERROR_SUCCESS)
    {
        for (size_t i = 0; i < a.size(); ++i)
        {
            std::cout << "Processor " << i << " frequency: " << a[i].CurrentMhz << " MHz" << std::endl;
        }
    }
    else
    {
        std::cerr << "CallNtPowerInformation failed" << std::endl;
    }


    HRESULT hres;

    // Инициализация COM библиотеки
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Ошибка при инициализации COM библиотеки: " << std::hex << hres << std::endl;
        return 1;
    }

    // Инициализация WMI
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
        std::cerr << "Ошибка при инициализации безопасности: " << std::hex << hres << std::endl;
        CoUninitialize();
        return 1;
    }

    // Получение указателя на WMI сервис
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc
    );

    if (FAILED(hres)) {
        std::cerr << "Не удалось создать экземпляр IWbemLocator: " << std::hex << hres << std::endl;
        CoUninitialize();
        return 1;
    }

    // Подключение к WMI
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
        std::cerr << "Не удалось подключиться к WMI: " << std::hex << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Установка безопасности на WMI сервисе
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
        std::cerr << "Не удалось установить безопасность на WMI сервисе: " << std::hex << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Получение данных о загрузке процессора
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_Processor"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
    );

    if (FAILED(hres)) {
        std::cerr << "Ошибка при выполнении запроса WMI для процессора: " << std::hex << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Получение данных о системе (операционной системе)
    IEnumWbemClassObject* pOSEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_OperatingSystem"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pOSEnumerator
    );

    if (FAILED(hres)) {
        std::cerr << "Ошибка при выполнении запроса WMI для операционной системы: " << std::hex << hres << std::endl;
        pEnumerator->Release();
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Получение данных о процессоре
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (0 == uReturn) {
            break;
        }

        VARIANT vtProp;
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        std::wcout << L"Модель процессора: " << V_BSTR(&vtProp) << std::endl;
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
        std::wcout << L"Количество физических ядер: " << V_UINT(&vtProp) << std::endl;
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
        std::wcout << L"Количество логических процессоров: " << V_UINT(&vtProp) << std::endl;
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"L1CacheSize", 0, &vtProp, 0, 0);
        std::wcout << L"Размер кэша L1: " << V_UINT(&vtProp) << L" КБ" << std::endl;
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"L2CacheSize", 0, &vtProp, 0, 0);
        std::wcout << L"Размер кэша L2: " << V_UINT(&vtProp) << L" КБ" << std::endl;
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"L3CacheSize", 0, &vtProp, 0, 0);
        std::wcout << L"Размер кэша L3: " << V_UINT(&vtProp) << L" КБ" << std::endl;
        VariantClear(&vtProp);

        pclsObj->Release();
    }

    while (true) {
        // Получение данных о загрузке процессора
        IEnumWbemClassObject* pOSEnumerator = NULL;
        hres = pSvc->ExecQuery(
            bstr_t("WQL"),
            bstr_t("SELECT * FROM Win32_OperatingSystem"),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            &pOSEnumerator
        );

        if (FAILED(hres)) {
            std::cerr << "Ошибка при выполнении запроса WMI для операционной системы: " << std::hex << hres << std::endl;
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return 1;
        }

        IWbemClassObject* pclsObj = NULL;
        ULONG uReturn = 0;

        while (pOSEnumerator) {
            HRESULT hr = pOSEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

            if (0 == uReturn) {
                break;
            }

            VARIANT vtProp;
            hr = pclsObj->Get(L"NumberOfProcesses", 0, &vtProp, 0, 0);
            std::wcout << L"Количество процессов: " << V_UINT(&vtProp) << std::endl;
            VariantClear(&vtProp);

            hr = pclsObj->Get(L"LastBootUpTime", 0, &vtProp, 0, 0);
            _bstr_t bootTimeBstr(V_BSTR(&vtProp));
            VariantClear(&vtProp);

            // Преобразование времени загрузки в строку
            std::wstring bootTimeStr = static_cast<const wchar_t*>(bootTimeBstr);

            // Получение текущего времени
            auto currentTime = std::chrono::system_clock::now();
            // Преобразование времени запуска системы из строки во время
            struct tm bootTime = {};
            swscanf_s(bootTimeStr.c_str(), L"%4d%2d%2d%2d%2d%2d", &bootTime.tm_year, &bootTime.tm_mon, &bootTime.tm_mday, &bootTime.tm_hour, &bootTime.tm_min, &bootTime.tm_sec);
            bootTime.tm_year -= 1900; // tm_year начинается с 1900 года
            bootTime.tm_mon--; // tm_mon начинается с января (0)

            // Преобразование времени запуска системы во временную метку
            auto bootTimeTm = std::mktime(&bootTime);

            // Вычисление разницы между текущим временем и временем загрузки системы
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - std::chrono::system_clock::from_time_t(bootTimeTm));

            // Вычисление количества дней, часов, минут и секунд
            auto days = std::chrono::duration_cast<std::chrono::hours>(elapsedTime).count() / 24;
            auto hours = std::chrono::duration_cast<std::chrono::hours>(elapsedTime).count() % 24;
            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsedTime).count() % 60;
            auto seconds = elapsedTime.count() % 60;

            // Вывод времени работы системы
            std::wcout << L"Время работы системы: " << days << L" дней, " << hours << L" часов, " << minutes << L" минут, " << seconds << L" секунд" << std::endl;

            std::wcout << L"Загрузка процессора: " << GetCPULoad() * 100 << "%\n\n";

            pclsObj->Release();
        }

        // Освобождение ресурсов
        pOSEnumerator->Release();

        // Задержка выполнения перед новым запросом
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    return 0;
}
