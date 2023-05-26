#include "includes.h"

RichHeaderInfo::RichHeaderInfo(int _size, char* _BufferPtr, int _entries) {
	size = _size;
	BufferPtr = _BufferPtr;
	entries = _entries;
}
RichHeaderEntry::RichHeaderEntry(WORD _prodID, WORD _buildID, DWORD _useCount) {
	prodID = _prodID;
	buildID = _buildID;
	useCount = _useCount;
}


RichHeader::RichHeader(FILE* PEFile, DOSHeader* _DOSHeader) {
	char* Data = new char[_DOSHeader->e_lfanew];

	fseek(PEFile, 0, SEEK_SET);
	fread(Data, _DOSHeader->e_lfanew, 1, PEFile);

	// Find the end of the rich header by identifying the string 'Rich'
	int RichHeaderEndIndex = 0;

	for (int i = 0; i < _DOSHeader->e_lfanew - 1; i++) {
		if (Data[i] == 0x52/*R*/ && Data[i + 1] == 0x69/*i*/) { //Rich
			//'Rich' found
			RichHeaderEndIndex = i;
			break;
		}
	}
	if (RichHeaderEndIndex == 0) return; //Not Found

	// Now we need to find the size of the rich header. We will loop through from its end location until
	// We reach the 'DanS' Sequence Decyrpting on the way

	//Decryption key stored directly after the 'Rich' sequence
	char XorKey[4];
	memcpy(XorKey, Data + (RichHeaderEndIndex + 4), 4);

	int StartIndex = RichHeaderEndIndex - 4;
	int RichHeaderSize = 0;

	while (true) {
		char TmpDecrypted[4];
		memcpy(TmpDecrypted, Data + StartIndex, 4);

		for (int i = 0; i < 4; i++) {
			TmpDecrypted[i] = TmpDecrypted[i] ^ XorKey[i];
		}

		StartIndex -= 4;
		RichHeaderSize += 4;

		if (TmpDecrypted[1] == 0x61/*a*/ && TmpDecrypted[0] == 0x44/*D*/) break; //DanS
	}

	//Allocate a buffer to store the rich header and then decrypt it
	char* RichHeaderBuffer = new char[RichHeaderSize];
	memcpy(RichHeaderBuffer, Data + (RichHeaderEndIndex - RichHeaderSize), RichHeaderSize);

	for (int i = 0; i < RichHeaderSize; i+=4) {
		for (int x = 0; x < 4; x++) {
			RichHeaderBuffer[i + x] = RichHeaderBuffer[i + x] ^ XorKey[x]; //Xor Decryption
		}
	}

	m_RichHeaderInfo = new RichHeaderInfo(RichHeaderSize,
										  RichHeaderBuffer,
										  (RichHeaderSize - 16) / 8);

	delete[] Data;

	for (int i = 16; i < RichHeaderSize; i+=8) {
		WORD PRODID = (uint16_t)((unsigned char)RichHeaderBuffer[i + 3] << 8) | (unsigned char)RichHeaderBuffer[i + 2];
		WORD BUILDID = (uint16_t)((unsigned char)RichHeaderBuffer[i + 1] << 8) | (unsigned char)RichHeaderBuffer[i];
		DWORD USECOUNT = (uint32_t)((unsigned char)RichHeaderBuffer[i + 7] << 24) | (unsigned char)RichHeaderBuffer[i + 6] << 16 | (unsigned char)RichHeaderBuffer[i + 5] << 8 | (unsigned char)RichHeaderBuffer[i + 4];

		RichHeaderEntry CurEntry = { PRODID, BUILDID, USECOUNT };

		m_RichHeaderEntryVec.push_back(CurEntry);
	}

}

void RichHeader::PrintRichHeaderInfo() {
	if (m_RichHeaderInfo == nullptr || m_RichHeaderEntryVec.empty()) {
		printf("RichHeader Error: Could not be located\n");
	}
	else {
		for (RichHeaderEntry entry : m_RichHeaderEntryVec) {
			printf(" 0x%X 0x%X 0x%X: %d.%d.%d\n",
				entry.buildID,
				entry.prodID,
				entry.useCount,
				entry.buildID,
				entry.prodID,
				entry.useCount);
		}
	}
}


