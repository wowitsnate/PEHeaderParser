#pragma once

class PE64 {
public:
	PE64(FILE* _PEFile, const char* _Name);
	void PrintInfo();
public:
	const char* Name;
	FILE*		PEFile;
public:
	DOSHeader*			m_DOSHeader =		nullptr;
	RichHeader*			m_RichHeader =		nullptr;
	NTHeaders64*			m_NTHeaders =		nullptr;
	SectionHeaders*		m_SectionHeaders =	nullptr;
	ImportDirectory64*	m_ImportDirectory = nullptr;
	BaseReloc*			m_BaseReloc =		nullptr;
public:
	void ParseFile();
};