#pragma once
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long QWORD;
typedef unsigned long LONG;
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#define ___IMAGE_NT_OPTIONAL_HDR32_MAGIC       0x10b
#define ___IMAGE_NT_OPTIONAL_HDR64_MAGIC       0x20b
#define ___IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16
#define ___IMAGE_DOS_SIGNATURE                 0x5A4D

#define ___IMAGE_DIRECTORY_ENTRY_EXPORT          0
#define ___IMAGE_DIRECTORY_ENTRY_IMPORT          1
#define ___IMAGE_DIRECTORY_ENTRY_RESOURCE        2
#define ___IMAGE_DIRECTORY_ENTRY_EXCEPTION       3
#define ___IMAGE_DIRECTORY_ENTRY_SECURITY        4
#define ___IMAGE_DIRECTORY_ENTRY_BASERELOC       5
#define ___IMAGE_DIRECTORY_ENTRY_DEBUG           6
#define ___IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7
#define ___IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8
#define ___IMAGE_DIRECTORY_ENTRY_TLS             9
#define ___IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10
#define ___IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11
#define ___IMAGE_DIRECTORY_ENTRY_IAT            12
#define ___IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13
#define ___IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14

#define ___IMAGE_SIZEOF_SHORT_NAME              8
#define ___IMAGE_SIZEOF_SECTION_HEADER          40

class ImageFileHeader {
public:
    WORD    Machine;
    WORD    NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    WORD    SizeOfOptionalHeader;
    WORD    Characteristics;
};

class ImageDataDirectory {
public:
    DWORD   VirtualAddress;
    DWORD   Size;
};

class ImageImportByName {
public:
    WORD    Hint;
    char   Name[100];
};

class ImageImportDescriptor {
public:
    union {
        DWORD   Characteristics;
        DWORD   OriginalFirstThunk;
    } DUMMYUNIONNAME;
    DWORD   TimeDateStamp;
    DWORD   ForwarderChain;
    DWORD   Name;
    DWORD   FirstThunk;
};