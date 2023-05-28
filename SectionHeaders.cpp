#include "includes.h"

SectionHeaders::SectionHeaders(FILE* PEFile, DOSHeader* _DOSHeader, NTHeaders64* _NTHeaders) {
	for (int i = 0; i < _NTHeaders->FileHeader.NumberOfSections; i++) {
		int offset = (_DOSHeader->e_lfanew + sizeof(NTHeaders64)) + (i * ___IMAGE_SIZEOF_SECTION_HEADER);
		ImageSectionHeader CurSectionHeader = ImageSectionHeader();
		fseek(PEFile, offset, SEEK_SET);
		fread(&CurSectionHeader, ___IMAGE_SIZEOF_SECTION_HEADER, 1, PEFile);
		SectionHeadersVec.push_back(CurSectionHeader);
	}
}

SectionHeaders::SectionHeaders(FILE* PEFile, DOSHeader* _DOSHeader, NTHeaders32* _NTHeaders) {
	for (int i = 0; i < _NTHeaders->FileHeader.NumberOfSections; i++) {
		int offset = (_DOSHeader->e_lfanew + sizeof(NTHeaders32)) + (i * ___IMAGE_SIZEOF_SECTION_HEADER);
		ImageSectionHeader CurSectionHeader = ImageSectionHeader();
		fseek(PEFile, offset, SEEK_SET);
		fread(&CurSectionHeader, ___IMAGE_SIZEOF_SECTION_HEADER, 1, PEFile);
		SectionHeadersVec.push_back(CurSectionHeader);
	};
}

void SectionHeaders::PrintSectionHeadersInfo() {
	printf("\n SECTION HEADERS:\n");
	printf(" ----------------\n\n");

	for (ImageSectionHeader _ImageSectionHeader : SectionHeadersVec) {
		printf("   * %.8s:\n", _ImageSectionHeader.Name);
		printf("        VirtualAddress: 0x%X\n", _ImageSectionHeader.VirtualAddress);
		printf("        VirtualSize: 0x%X\n", _ImageSectionHeader.Misc.VirtualSize);
		printf("        PointerToRawData: 0x%X\n", _ImageSectionHeader.PointerToRawData);
		printf("        SizeOfRawData: 0x%X\n", _ImageSectionHeader.SizeOfRawData);
		printf("        Characteristics: 0x%X\n\n", _ImageSectionHeader.Characteristics);
	}
}
