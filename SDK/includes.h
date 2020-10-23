#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>


#include "mem.h"

class R6 {
public:
	uintptr_t base;
	DWORD pid;
	Memory* mem;
};