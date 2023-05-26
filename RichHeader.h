#pragma once

class RichHeaderEntry {
public:
    RichHeaderEntry(WORD _prodID, WORD _buildID, DWORD _useCount);
public:
    WORD prodID;
    WORD buildID;
    DWORD useCount;
};

class RichHeaderInfo {
public:
    RichHeaderInfo(int _size, char* _BufferPtr, int _entries);
public:
    int size;
    char* BufferPtr;
    int entries;
};

class RichHeader {
public:
    std::vector<RichHeaderEntry> m_RichHeaderEntryVec = {};
    RichHeaderInfo* m_RichHeaderInfo = nullptr;
public:
    RichHeader(FILE* PEFile, DOSHeader* _DOSHeader);
    void PrintRichHeaderInfo();
};