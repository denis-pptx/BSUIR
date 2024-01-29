#include <fstream>
#include <sstream>
#include <iostream>
#include <experimental/filesystem> // compilers that support the TS
// #include <filesystem> // C++17 compilers

// for readability
namespace fs = std::experimental::filesystem;

int main(int, char* [])
{
    fs::path filename = "test.txt";

    std::fstream file(filename);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << '\n';
        return EXIT_FAILURE;
    }

    // display current contents
    std::stringstream ss;
    ss << file.rdbuf();
    std::cout << ss.str() << '\n';

    // truncate file
    fs::resize_file(filename, 0);
    file.seekp(0);

    // write new stuff
    file << "new data";
}