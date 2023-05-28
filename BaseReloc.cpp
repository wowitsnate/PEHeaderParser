#include "includes.h"


ImageSectionHeader BaseReloc::locate(DWORD VA) {
	for (ImageSectionHeader CurSectionHeader : *SectionHeadersVec) {
		if (isInRangeExclusiveUpper(VA,
			CurSectionHeader.VirtualAddress,
			CurSectionHeader.VirtualAddress + CurSectionHeader.Misc.VirtualSize)) {
			return CurSectionHeader;
		}
	}
	return ImageSectionHeader();
}

DWORD BaseReloc::resolve(DWORD VA, ImageSectionHeader Section) {
	return ((VA - Section.VirtualAddress) + Section.PointerToRawData);
}


BaseReloc::BaseReloc(FILE* PEFile, NTHeaders64* _NTHeaders, SectionHeaders* _SectionHeaders) {
	SectionHeadersVec = &_SectionHeaders->SectionHeadersVec;

	ImageDataDirectory BaseRelocDirectoryFromNT = _NTHeaders->OptionalHeader.DataDirectory[___IMAGE_DIRECTORY_ENTRY_BASERELOC];
	BaseRelocDirectoryAddress = resolve(BaseRelocDirectoryFromNT.VirtualAddress, locate(BaseRelocDirectoryFromNT.VirtualAddress));
	int BaseRelocSizeCounter = 0;
	for (int BaseRelocDirectoryCount = 0; ; BaseRelocDirectoryCount++) {
		ImageBaseRelocation TmpImageBaseRelocation{ };

		int offset = (BaseRelocSizeCounter + BaseRelocDirectoryAddress);

		fseek(PEFile, offset, SEEK_SET);
		fread(&TmpImageBaseRelocation, sizeof(ImageBaseRelocation), 1, PEFile);

		if (TmpImageBaseRelocation.VirtualAddress == 0x00000000 &&
			TmpImageBaseRelocation.SizeOfBlock == 0x00000000) break;

		BaseRelocSizeCounter += TmpImageBaseRelocation.SizeOfBlock;
		ImageBaseRelocationVec.push_back(TmpImageBaseRelocation);
	}
}

BaseReloc::BaseReloc(FILE* PEFile, NTHeaders32* _NTHeaders, SectionHeaders* _SectionHeaders) {
	SectionHeadersVec = &_SectionHeaders->SectionHeadersVec;

	ImageDataDirectory BaseRelocDirectoryFromNT = _NTHeaders->OptionalHeader.DataDirectory[___IMAGE_DIRECTORY_ENTRY_BASERELOC];
	BaseRelocDirectoryAddress = resolve(BaseRelocDirectoryFromNT.VirtualAddress, locate(BaseRelocDirectoryFromNT.VirtualAddress));
	int BaseRelocSizeCounter = 0;
	for (int BaseRelocDirectoryCount = 0; ; BaseRelocDirectoryCount++) {
		ImageBaseRelocation TmpImageBaseRelocation{ };

		int offset = (BaseRelocSizeCounter + BaseRelocDirectoryAddress);

		fseek(PEFile, offset, SEEK_SET);
		fread(&TmpImageBaseRelocation, sizeof(ImageBaseRelocation), 1, PEFile);

		if (TmpImageBaseRelocation.VirtualAddress == 0x00000000 &&
			TmpImageBaseRelocation.SizeOfBlock == 0x00000000) break;

		BaseRelocSizeCounter += TmpImageBaseRelocation.SizeOfBlock;
		ImageBaseRelocationVec.push_back(TmpImageBaseRelocation);
	}
}

void BaseReloc::PrintBaseRelocInfo(FILE* PEFile) {
	printf(" BASE RELOCATIONS TABLE:\n");
	printf(" -----------------------\n");

	int szCounter = sizeof(ImageBaseRelocation);
	int BlockNumber = 0;
	for (const ImageBaseRelocation& CurImageBaseRelocation : ImageBaseRelocationVec) {
		DWORD PAGERVA = CurImageBaseRelocation.VirtualAddress;
		DWORD BLOCKSIZE = CurImageBaseRelocation.SizeOfBlock;
		int ENTRIES = (BLOCKSIZE - sizeof(ImageBaseRelocation)) / sizeof(WORD);

		printf("\n   Block 0x%X: \n", BlockNumber);
		printf("     Page RVA: 0x%X\n", PAGERVA);
		printf("     Block size: 0x%X\n", BLOCKSIZE);
		printf("     Number of entries: 0x%X\n", ENTRIES);
		printf("\n     Entries:\n");

		for (int i = 0; i < ENTRIES; i++) {

			BaseRelocEntry entry;

			int offset = (BaseRelocDirectoryAddress + szCounter + (i * sizeof(WORD)));

			fseek(PEFile, offset, SEEK_SET);
			fread(&entry, sizeof(WORD), 1, PEFile);

			printf("\n       * Value: 0x%X\n", entry);
			printf("         Relocation Type: 0x%X\n", entry.TYPE);
			printf("         Offset: 0x%X\n", entry.OFFSET);

		}
		printf("\n   ----------------------\n\n");
		szCounter += BLOCKSIZE;
		BlockNumber++;
	}
}
