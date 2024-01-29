
#include <iostream>
#include <Windows.h>

// http://rsdn.org/article/baseserv/dlluse.xml

class __declspec(dllimport) String
{
private:
    char* str_;
    size_t size_;
    size_t capacity_;
public:
    String();
    ~String();

    

};

int main()
{
 
    HINSTANCE hLib;
    hLib = LoadLibrary(L"StringDLL.dll");


    if (hLib)
        std::cout << "LOADED" << "\n";

    // Указатель на конструктор
    void (String:: * pConstructor)();
    (FARPROC&)pConstructor = GetProcAddress(hLib, "??0String@@QAE@XZ");

    // Получаем указатель на деструктор
    void (String:: * pDestructor)();
    (FARPROC&)pDestructor = GetProcAddress(hLib, "??1String@@QAE@XZ");

    // Указатель на функцию "size"
    size_t (String:: * pSize)();
    (FARPROC&)pSize = GetProcAddress(hLib, "?size@@YAXHH@Z");

   
    // Создаём объект в куче
    char* _pc = new char[sizeof(String)];
    String* pc = (String*)_pc;

    (pc->*pConstructor)();
    

    std::cout << (pc->*pSize)();
 
    // Уничтожаем объект, созданный в куче
    (pc->*pDestructor)();

    

    FreeLibrary(hLib);

    return 0;

}
