#pragma once

class ImageSectionHeader {
public:
    BYTE    Name[___IMAGE_SIZEOF_SHORT_NAME];
    union {
        DWORD   PhysicalAddress;
        DWORD   VirtualSize;
    } Misc;
    DWORD   VirtualAddress;
    DWORD   SizeOfRawData;
    DWORD   PointerToRawData;
    DWORD   PointerToRelocations;
    DWORD   PointerToLinenumbers;
    WORD    NumberOfRelocations;
    WORD    NumberOfLinenumbers;
    DWORD   Characteristics;
};

class SectionHeaders {
public:
    SectionHeaders(FILE* PEFile, DOSHeader* _DOSHeader, NTHeaders* _NTHeaders);
    void PrintSectionHeadersInfo();
public:
    std::vector<ImageSectionHeader> SectionHeadersVec = {};
};