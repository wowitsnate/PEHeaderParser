#pragma once

class ILTEntry64 {
public:
    union {
        DWORD ORDINAL : 16;
        DWORD HINT_NAME_TABE : 32;
    } FIELD_2;
    DWORD ORDINAL_NAME_FLAG : 1;
};


class ImportDirectory64 {
public:
	ImportDirectory64(FILE* PEFile, NTHeaders64* _NTHeaders, SectionHeaders* _SectionHeaders);
	void PrintImportDirectoryInfo(FILE* PEFile);
public:
    std::vector<ImageImportDescriptor> ImageImportDescriptorVec = {};
    std::vector<ImageSectionHeader>* SectionHeadersVec;
public:
    ImageSectionHeader locate(DWORD VA); //VirtualAddress
	DWORD resolve(DWORD VA, ImageSectionHeader Section); //VirtualAddress, Section
};