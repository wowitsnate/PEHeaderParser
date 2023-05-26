#pragma once

class ImageImportByName {
public:
    WORD    Hint;
    char   Name[100];
};

class ILTEntry64 {
public:
    union {
        DWORD ORDINAL : 16;
        DWORD HINT_NAME_TABE : 32;
    } FIELD_2;
    DWORD ORDINAL_NAME_FLAG : 1;
};

class ImageImportDescriptor {
public:
    union {
        DWORD   Characteristics;
        DWORD   OriginalFirstThunk;
    } DUMMYUNIONNAME;
    DWORD   TimeDateStamp;
    DWORD   ForwarderChain;
    DWORD   Name;
    DWORD   FirstThunk;
};

class ImportDirectory {
public:
	ImportDirectory(FILE* PEFile, NTHeaders* _NTHeaders, SectionHeaders* _SectionHeaders);
	void PrintImportDirectoryInfo(FILE* PEFile);
public:
    std::vector<ImageImportDescriptor> ImageImportDescriptorVec = {};
    std::vector<ImageSectionHeader>* SectionHeadersVec;
public:
    ImageSectionHeader locate(DWORD VA); //VirtualAddress
	DWORD resolve(DWORD VA, ImageSectionHeader Section); //VirtualAddress, Section
};