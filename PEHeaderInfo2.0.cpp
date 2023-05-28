#include "includes.h"

int main()
{
    std::string FileLocation = "C:\\Users\\nate\\Desktop\\Debug_Testing_Output\\ProjectUtilsTesting32bit.exe";
    //std::cout << "Enter PE File Location: \n";
    //std::cin >> FileLocation;

    FILE* PpeFile;
    fopen_s(&PpeFile, FileLocation.c_str(), "r");

    PE32 test = PE32(PpeFile, "PE_FILE");
    test.PrintInfo();

    if (PpeFile) {
       fclose(PpeFile);
    }
}