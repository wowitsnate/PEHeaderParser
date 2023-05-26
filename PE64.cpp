#include "includes.h"

PE64::PE64(FILE* _PEFile, const char* _Name) {
	PEFile = _PEFile;
	Name = _Name;

	ParseFile();
}

void PE64::PrintInfo() {
	if (m_DOSHeader != nullptr) {
		m_DOSHeader->PrintDOSHeaderInfo();
	}
	if (m_RichHeader != nullptr) {
		m_RichHeader->PrintRichHeaderInfo();
	}
	if (m_NTHeaders != nullptr) {
		m_NTHeaders->PrintNTHeadersInfo();
	}
	if (m_SectionHeaders != nullptr) {
		m_SectionHeaders->PrintSectionHeadersInfo();
	}
	if (m_ImportDirectory != nullptr) {
		m_ImportDirectory->PrintImportDirectoryInfo(PEFile);
	}
	if (m_BaseReloc != nullptr) {
		m_BaseReloc->PrintBaseRelocInfo(PEFile);
	}
}

void PE64::ParseFile() {
	m_DOSHeader = new DOSHeader(PEFile);
	m_RichHeader = new RichHeader(PEFile, m_DOSHeader);
	m_NTHeaders = new NTHeaders(PEFile, m_DOSHeader);
	m_SectionHeaders = new SectionHeaders(PEFile, m_DOSHeader, m_NTHeaders);
	m_ImportDirectory = new ImportDirectory(PEFile, m_NTHeaders, m_SectionHeaders);
	m_BaseReloc = new BaseReloc(PEFile, m_NTHeaders, m_SectionHeaders);
}