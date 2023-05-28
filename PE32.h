#pragma once

class PE32 {
public:
	PE32(FILE* _PEFile, const char* _Name);
	void PrintInfo();
public:
	FILE* PEFile;
	const char* Name;
public:
	DOSHeader* m_DOSHeader = nullptr;
	RichHeader* m_RichHeader = nullptr;
	NTHeaders32* m_NTHeaders = nullptr;
	SectionHeaders* m_SectionHeaders = nullptr;
	ImportDirectory32* m_ImportDirectory = nullptr;
	BaseReloc* m_BaseReloc = nullptr;
public:
	void ParseFile();
};