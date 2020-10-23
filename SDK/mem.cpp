#include "includes.h"
extern R6* r6;
static  uint8_t shellcode[] = {
	0x4C, 0x8B, 0xD1,
	0xB8, 0x2D, 0x10, 0x00, 0x00,
	0x0F, 0x05,
	0xC3
};


void Memory::cread(uintptr_t at, void* buffer, size_t size) {
	NtReadVirtualMemory(GameHandle, (PVOID)at, (PVOID)buffer, size, 0);
}

void Memory::cwrite(uintptr_t at, void* buffer, size_t size) {
	NtWriteVirtualMemory(GameHandle, (PVOID)at, (PVOID)buffer, size, 0);
}

uintptr_t Memory::get_base(const char* modname, DWORD pid) {
	uintptr_t base_buffer = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
	if (hSnap == INVALID_HANDLE_VALUE) {
		printf("[-] Couldn't open Snapshot!\n");
		system("pause");
	}

	MODULEENTRY32 me32{ 0 };
	me32.dwSize = sizeof(me32);

	BOOL status = Module32First(hSnap, &me32);
	while (status) {
		if (!strcmp(me32.szModule, modname)) {
			base_buffer = (uintptr_t)me32.modBaseAddr;
		}
		status = Module32Next(hSnap, &me32);
	}
	CloseHandle(hSnap);
	return base_buffer;
}

void Memory::setup() {
	//Get Module Handle of ntdll.dll
	HMODULE ntdll = GetModuleHandleA("ntdll.dll");

	//Get address of NtWriteVirtualMemory allocate memory for our shellcode and fill it
	uintptr_t NtWriteAddy = (uintptr_t)GetProcAddress(ntdll, "NtWriteVirtualMemory");
	DWORD Writeoffset = *(DWORD*)(NtWriteAddy + 0x4);
	*(DWORD*)(&shellcode[4]) = Writeoffset;
	LPVOID NtWriteCave = VirtualAlloc(0, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(NtWriteCave, shellcode, sizeof(shellcode));
	NtWriteVirtualMemory = reinterpret_cast<decltype(NtWriteVirtualMemory)>(NtWriteCave);

	//Get address of NtReadVirtualMemory allocate memory for our shellcode and fill it
	uintptr_t NtReadAddy = (uintptr_t)GetProcAddress(ntdll, "NtReadVirtualMemory");
	DWORD Readoffset = *(DWORD*)(NtReadAddy + 0x4);
	*(DWORD*)(&shellcode[4]) = Readoffset;
	LPVOID NtReadCave = VirtualAlloc(0, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(NtReadCave, shellcode, sizeof(shellcode));
	NtReadVirtualMemory = reinterpret_cast<decltype(NtReadVirtualMemory)>(NtReadCave);

	//Find Game Window
	while (!this->GameHwnd) { this->GameHwnd = FindWindowA(NULL, "Rainbow Six"); Sleep(1000); };
	printf("[+] Found RainbowSix\n");
	GetWindowThreadProcessId(this->GameHwnd, &r6->pid);
	//Open Process
	this->GameHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, r6->pid);
	if (this->GameHandle == INVALID_HANDLE_VALUE) {
		printf("[-] Failed opening Handle to RainbowSix.exe! (Battleye off?)\n");
		system("pause");
	}
	r6->base = get_base("RainbowSix.exe", r6->pid);
	printf("[+] Base: %p\n", r6->base);
	printf("[+] PID: %x\n", r6->pid);
}