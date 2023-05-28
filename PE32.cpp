#include "includes.h"

PE32::PE32(FILE* _PEFile, const char* _Name) {
	PEFile = _PEFile;
	Name = _Name;

	ParseFile();
}

void PE32::ParseFile() {
	m_DOSHeader = new DOSHeader(PEFile);
	m_RichHeader = new RichHeader(PEFile, m_DOSHeader);
	m_NTHeaders = new NTHeaders32(PEFile, m_DOSHeader);
	m_SectionHeaders = new SectionHeaders(PEFile, m_DOSHeader, m_NTHeaders);
	m_ImportDirectory = new ImportDirectory32(PEFile, m_NTHeaders, m_SectionHeaders);
	m_BaseReloc = new BaseReloc(PEFile, m_NTHeaders, m_SectionHeaders);
}

void PE32::PrintInfo() {
	m_DOSHeader->PrintDOSHeaderInfo();
	m_RichHeader->PrintRichHeaderInfo();
	m_NTHeaders->PrintNTHeadersInfo();
	m_SectionHeaders->PrintSectionHeadersInfo();
	m_ImportDirectory->PrintImportDirectoryInfo(PEFile);
	m_BaseReloc->PrintBaseRelocInfo(PEFile);
}