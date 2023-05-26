#include "includes.h"

NTHeaders::NTHeaders(FILE* PEFile, DOSHeader* _DOSHeader) {
	fseek(PEFile, _DOSHeader->e_lfanew, SEEK_SET);
	fread(this, sizeof(NTHeaders), 1, PEFile);
}

void NTHeaders::PrintNTHeadersInfo() {
	printf("\n NT HEADERS:\n");
	printf(" -----------\n\n");

	printf(" PE Signature: 0x%X\n", Signature);

	printf("\n File Header:\n\n");
	printf("   Machine: 0x%X\n", FileHeader.Machine);
	printf("   Number of sections: 0x%X\n", FileHeader.NumberOfSections);
	printf("   Size of optional header: 0x%X\n", FileHeader.SizeOfOptionalHeader);

	printf("\n Optional Header:\n\n");
	printf("   Magic: 0x%X\n", OptionalHeader.Magic);
	printf("   Size of code section: 0x%X\n", OptionalHeader.SizeOfCode);
	printf("   Size of initialized data: 0x%X\n", OptionalHeader.SizeOfInitializedData);
	printf("   Size of uninitialized data: 0x%X\n", OptionalHeader.SizeOfUninitializedData);
	printf("   Address of entry point: 0x%X\n", OptionalHeader.AddressOfEntryPoint);
	printf("   RVA of start of code section: 0x%X\n", OptionalHeader.BaseOfCode);
	printf("   Desired image base: 0x%X\n", OptionalHeader.ImageBase);
	printf("   Section alignment: 0x%X\n", OptionalHeader.SectionAlignment);
	printf("   File alignment: 0x%X\n", OptionalHeader.FileAlignment);
	printf("   Size of image: 0x%X\n", OptionalHeader.SizeOfImage);
	printf("   Size of headers: 0x%X\n", OptionalHeader.SizeOfHeaders);

	printf("\n Data Directories:\n");
	printf("\n   * Export Directory:\n");
	printf("       RVA: 0x%X\n", OptionalHeader.DataDirectory[___IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	printf("       Size: 0x%X\n", OptionalHeader.DataDirectory[___IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
	printf("\n   * COM Runtime Descriptor:\n");
	printf("       RVA: 0x%X\n", OptionalHeader.DataDirectory[___IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress);
	printf("       Size: 0x%X\n", OptionalHeader.DataDirectory[___IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size);
}
