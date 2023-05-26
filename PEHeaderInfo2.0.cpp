#include "includes.h"

int main()
{
    std::string FileLocation;
    std::cout << "Enter PE File Location: \n";
    std::cin >> FileLocation;

    FILE* PpeFile;
    fopen_s(&PpeFile, FileLocation.c_str(), "r");

    PE64 test = PE64(PpeFile, "PE_FILE");
    test.PrintInfo();

    fclose(PpeFile);

}