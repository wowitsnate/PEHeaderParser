#pragma once

class BaseRelocEntry {
public:
	WORD OFFSET : 12;
	WORD TYPE : 4;
};

class ImageBaseRelocation {
public:
	DWORD   VirtualAddress;
	DWORD   SizeOfBlock;
};

class BaseReloc {
public:
	BaseReloc(FILE* PEFile, NTHeaders* _NTHeaders, SectionHeaders* _SectionHeaders);
	void PrintBaseRelocInfo(FILE* PEFile);
public:
	std::vector<ImageBaseRelocation> ImageBaseRelocationVec = {};
	std::vector<ImageSectionHeader>* SectionHeadersVec;
	DWORD BaseRelocDirectoryAddress;
public:
	ImageSectionHeader locate(DWORD VA);
	DWORD resolve(DWORD VA, ImageSectionHeader Section);
};