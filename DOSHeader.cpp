#include "includes.h"

DOSHeader::DOSHeader(FILE* PEFile) {
	//Update values in class
	fseek(PEFile, 0, SEEK_SET);
	fread(this, sizeof(DOSHeader), 1, PEFile);
}

void DOSHeader::PrintDOSHeaderInfo() {
	printf("\n DOS HEADER:\n");
	printf(" -----------\n\n");

	printf(" Magic: 0x%X\n", e_magic);
	printf(" File address of new exe header: 0x%X\n", e_lfanew);
}
