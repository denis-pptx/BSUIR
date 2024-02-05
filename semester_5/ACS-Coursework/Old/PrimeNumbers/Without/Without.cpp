#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

vector<int> find_primes(int start, int end) {
    vector<int> primes;
    for (int i = start; i <= end; ++i) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main() {
    int start = 2;
    int end = 100000;

    auto start_time = chrono::high_resolution_clock::now();

    vector<int> primes = find_primes(start, end);

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);

    cout << "Number of primes between " << start << " and " << end << ": " << primes.size() << endl;
    /*cout << "Primes: ";
    for (int prime : primes) {
        cout << prime << " ";
    }*/
    cout << endl;
    cout << "Execution time: " << duration.count() << " nanoseconds" << endl;

    return 0;
}
