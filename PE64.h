#pragma once

class PE64 {
	friend DOSHeader;
	friend RichHeader;
public:
	PE64(FILE* _PEFile, const char* _Name);
	void PrintInfo();
public:
	const char* Name;
	FILE*		PEFile;
public:
	DOSHeader*			m_DOSHeader =		nullptr;
	RichHeader*			m_RichHeader =		nullptr;
	NTHeaders*			m_NTHeaders =		nullptr;
	SectionHeaders*		m_SectionHeaders =	nullptr;
	ImportDirectory*	m_ImportDirectory = nullptr;
	BaseReloc*			m_BaseReloc =		nullptr;
public:
	void ParseFile();

};