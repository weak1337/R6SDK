#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <vector>


#include "mem.h"
#include "chat.h"
class R6 {
public:
	uintptr_t base;
	DWORD pid;
	Memory* mem;

	//Components
	ChatManager* Chat;

	R6();
};