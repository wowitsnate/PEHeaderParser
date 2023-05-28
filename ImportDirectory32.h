#pragma once

class ILTEntry32 {
public:
	union {
		DWORD ORDINAL : 16;
		DWORD HINT_NAME_TABE : 32;
		DWORD ORDINAL_NAME_FLAG : 1;
	} FIELD_1;
};

class ImportDirectory32 {
public:
	ImportDirectory32(FILE* PEFile, NTHeaders32* _NTHeaders, SectionHeaders* _SectionHeaders);
	void PrintImportDirectoryInfo(FILE* PEFile);
public:
	std::vector<ImageImportDescriptor> ImageImportDescriptorVec = {};
	std::vector<ImageSectionHeader>* SectionHeadersVec;
public:
	ImageSectionHeader locate(DWORD VA); //VirtualAddress
	DWORD resolve(DWORD VA, ImageSectionHeader Section); //VirtualAddress, Section
};