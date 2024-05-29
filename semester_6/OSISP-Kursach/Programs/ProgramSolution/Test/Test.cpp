#include <Windows.h>
#include <iostream>

#include <pdh.h>
#pragma comment(lib, "pdh.lib")

int main() {
    // Open the performance counter for GPU usage
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    PDH_STATUS status;

    status = PdhOpenQuery(NULL, 0, &query);
    if (status != ERROR_SUCCESS) {
        std::cerr << "Failed to open query: " << status << std::endl;
        return 1;
    }

    status = PdhAddCounter(query, L"\\GPU Engine(_Total)\\Utilization Percentage", 0, &counter);
    if (status != ERROR_SUCCESS) {
        std::cerr << "Failed to add counter: " << status << std::endl;
        PdhCloseQuery(query);
        return 1;
    }

    // Collect and display GPU usage
    status = PdhCollectQueryData(query);
    if (status != ERROR_SUCCESS) {
        std::cerr << "Failed to collect query data: " << status << std::endl;
        PdhCloseQuery(query);
        return 1;
    }

    PDH_FMT_COUNTERVALUE value;
    status = PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &value);
    if (status != ERROR_SUCCESS) {
        std::cerr << "Failed to get counter value: " << status << std::endl;
        PdhCloseQuery(query);
        return 1;
    }

    std::cout << "GPU Usage: " << value.doubleValue << "%" << std::endl;

    // Close the query
    PdhCloseQuery(query);

    return 0;
}
