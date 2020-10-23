class Memory {
private:
	HANDLE GameHandle;
	HWND GameHwnd;


	void cwrite(uintptr_t at, void* buffer, size_t size);

	DWORD(*NtWriteVirtualMemory)(
		IN HANDLE               ProcessHandle,
		IN PVOID                BaseAddress,
		IN PVOID                Buffer,
		IN ULONG                NumberOfBytesToWrite,
		OUT PULONG              NumberOfBytesWritten OPTIONAL);

	DWORD(*NtReadVirtualMemory)(
		IN HANDLE               ProcessHandle,
		IN PVOID                BaseAddress,
		OUT PVOID               Buffer,
		IN ULONG                NumberOfBytesToRead,
		OUT PULONG              NumberOfBytesReaded OPTIONAL);

	uintptr_t get_base(const char* modname, DWORD pid);

public:

	void cread(uintptr_t at, void* buffer, size_t size);

	template <typename T>
	T read(uintptr_t at) {
		T buffer{};
		cread(at, &buffer, sizeof(T));
		return buffer;
	}

	template <typename T>
	void write(uintptr_t at, T value) {
		cwrite(at, &value, sizeof(T));
	}

	void setup();
};