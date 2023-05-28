#include "includes.h"

ImageSectionHeader ImportDirectory64::locate(DWORD VA) {
	for (ImageSectionHeader CurSectionHeader : *SectionHeadersVec) {
		if (isInRangeExclusiveUpper(VA,
									CurSectionHeader.VirtualAddress,
									CurSectionHeader.VirtualAddress + CurSectionHeader.Misc.VirtualSize)) {
			return CurSectionHeader;
		}
	}
	return ImageSectionHeader();
}

DWORD ImportDirectory64::resolve(DWORD VA, ImageSectionHeader Section) {
	return ((VA - Section.VirtualAddress) + Section.PointerToRawData);
}

ImportDirectory64::ImportDirectory64(FILE* PEFile, NTHeaders64* _NTHeaders, SectionHeaders* _SectionHeaders) {
	SectionHeadersVec = &_SectionHeaders->SectionHeadersVec;

	ImageDataDirectory ImportDirectoryFromNT = _NTHeaders->OptionalHeader.DataDirectory[___IMAGE_DIRECTORY_ENTRY_IMPORT];
	DWORD ImportDirectoryAddress = resolve(ImportDirectoryFromNT.VirtualAddress, locate(ImportDirectoryFromNT.VirtualAddress));

	for (int ImportDirectoryCount = 0; ; ImportDirectoryCount++) {
		ImageImportDescriptor TmpImageImportDescriptor{ };

		int offset = (ImportDirectoryCount * sizeof(ImageImportDescriptor)) + ImportDirectoryAddress;
		fseek(PEFile, offset, SEEK_SET);

		fread(&TmpImageImportDescriptor, sizeof(ImageImportDescriptor), 1, PEFile);

		if (TmpImageImportDescriptor.Name == 0x00000000 && TmpImageImportDescriptor.FirstThunk == 0x00000000) {
			break;
		}
		else {
			ImageImportDescriptorVec.push_back(TmpImageImportDescriptor);
		}
	}
}

void ImportDirectory64::PrintImportDirectoryInfo(FILE* PEFile) {

	printf(" IMPORT TABLE:\n");
	printf(" ----------------\n\n");

	for (const ImageImportDescriptor &CurImportDescriptor : ImageImportDescriptorVec) {
		DWORD NameAddr = resolve(CurImportDescriptor.Name, locate(CurImportDescriptor.Name));
		int NameSize = 0;

		while (true) {
			char tmp;
			fseek(PEFile, (NameAddr + NameSize), SEEK_SET);
			fread(&tmp, sizeof(char), 1, PEFile);

			if (tmp == 0x00) {
				break;
			}

			NameSize++;
		}

		char* Name = new char[NameSize + 2];
		fseek(PEFile, NameAddr, SEEK_SET);
		fread(Name, (NameSize * sizeof(char)) + 1, 1, PEFile);
		printf("   * %s:\n", Name);
		

		printf("       ILT RVA: 0x%X\n", CurImportDescriptor.DUMMYUNIONNAME.OriginalFirstThunk);
		printf("       IAT RVA: 0x%X\n", CurImportDescriptor.FirstThunk);

		if (CurImportDescriptor.TimeDateStamp == 0) {
			printf("       Bound: FALSE\n");
		}
		else if (CurImportDescriptor.TimeDateStamp == -1) {
			printf("       Bound: TRUE\n");
		}

		printf("\n");

		DWORD ILTAddr = resolve(CurImportDescriptor.DUMMYUNIONNAME.OriginalFirstThunk, locate(CurImportDescriptor.DUMMYUNIONNAME.OriginalFirstThunk));
		int entrycounter = 0;

		while (true) {

			ILTEntry64 entry;

			fseek(PEFile, (ILTAddr + (entrycounter * sizeof(QWORD))), SEEK_SET);
			fread(&entry, sizeof(ILTEntry64), 1, PEFile);

			BYTE flag = entry.ORDINAL_NAME_FLAG;
			DWORD HintRVA = 0x0;
			WORD ordinal = 0x0;

			if (flag == 0x0) {
				HintRVA = entry.FIELD_2.HINT_NAME_TABE;
			}
			else if (flag == 0x01) {
				ordinal = entry.FIELD_2.ORDINAL;
			}

			if (flag == 0x0 && HintRVA == 0x0 && ordinal == 0x0) {
				break;
			}

			printf("\n       Entry:\n");

			if (flag == 0x0) {
				ImageImportByName hint;

				DWORD HintAddr = resolve(HintRVA, locate(HintRVA));
				fseek(PEFile, HintAddr, SEEK_SET);
				fread(&hint, sizeof(ImageImportByName), 1, PEFile);
				printf("         Name: %s\n", hint.Name);
				printf("         Hint RVA: 0x%X\n", HintRVA);
				printf("         Hint: 0x%X\n", hint.Hint);
			}
			else if (flag == 1) {
				printf("         Ordinal: 0x%X\n", ordinal);
			}

			entrycounter++;
		}
		printf("Total Number of Functions in %s: %i\n", Name, entrycounter);
		delete[] Name;
		printf("\n   ----------------------\n\n");
	}
}