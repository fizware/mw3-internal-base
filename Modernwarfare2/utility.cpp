#include "utility.h"

void Log_(const char* fmt, ...) {
	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);
#if defined(_LOG) == 0
	std::ofstream logfile(XOR("C:\\UC\\Logs\\_uc.logs"), std::ios::app);
	if (logfile.is_open() && text)	logfile << text << std::endl;
	logfile.close();

#endif	
}

DWORD utility::GetProcId(const char* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_stricmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

HMODULE utility::GetModuleHandleSafe(const char* pszModuleName)
{

	HMODULE hmModuleHandle = NULL;

	do
	{
		hmModuleHandle = GetModuleHandle(pszModuleName);
		Sleep(1);
	} while (hmModuleHandle == NULL);

	return hmModuleHandle;
}


bool MemCompare(const char* bData, const char* bSig, const char* szMask) {
	for (; *szMask; ++szMask, ++bData, ++bSig) {
		if (*szMask == 'x' && *bData != *bSig) {
			return false;
		}
	}
	return (*szMask == NULL);
}
//FFF aka cobalt services
address_t utility::find_ida_sig(const char* mod, const char* sig)
{
	/// Credits: MarkHC, although slightly modified by me and also documented

	static auto pattern_to_byte = [](const char* pattern)
	{
		/// Prerequisites
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		/// Convert signature into corresponding bytes
		for (auto current = start; current < end; ++current)
		{
			/// Is current byte a wildcard? Simply ignore that that byte later
			if (*current == '?')
			{
				++current;

				/// Check if following byte is also a wildcard
				if (*current == '?')
					++current;

				/// Dummy byte
				bytes.push_back(-1);
			}
			else
			{
				/// Convert character to byte on hexadecimal base
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	const auto module_handle = GetModuleHandleA(mod);
	auto base_mode = (uintptr_t)(iat(GetModuleHandleA).get()("cod.exe"));
	if (!module_handle)
		return {};

	/// Get module information to search in the given module
	MODULEINFO module_info;
	GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_handle), &module_info, sizeof(MODULEINFO));

	/// The region where we will search for the byte sequence
	const auto image_size = module_info.SizeOfImage;

	/// Check if the image is faulty
	if (!image_size)
		return {};

	/// Convert IDA-Style signature to a byte sequence
	auto pattern_bytes = pattern_to_byte(sig);

	const auto image_bytes = reinterpret_cast<byte*>(module_handle);

	const auto signature_size = pattern_bytes.size();
	const auto signature_bytes = pattern_bytes.data();

	LOGS("Looking for signature %s", sig);

	/// Loop through all pages and check the accessable pages
	auto page_information = MEMORY_BASIC_INFORMATION{};
	for (auto current_page = reinterpret_cast<byte*>(module_handle); current_page < reinterpret_cast<byte*>(module_handle + image_size); current_page = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(page_information.BaseAddress) + page_information.RegionSize))
	{
		auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

		if (page_information.Protect != PAGE_EXECUTE_READWRITE)
			continue;

		/// Now loop through all bytes and check if the byte sequence matches
		for (auto i = reinterpret_cast<uintptr_t>(page_information.BaseAddress) - reinterpret_cast<uintptr_t>(module_handle); i < page_information.RegionSize; ++i)
		{
			auto byte_sequence_found = true;

			if (i + signature_size == page_information.RegionSize)
			{
				auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

				if (page_information.Protect != PAGE_EXECUTE_READ)
					break;
			}

			/// Go through all bytes from the signature and check if it matches
			for (auto j = 0ul; j < signature_size; ++j)
			{
				if (image_bytes[i + j] != signature_bytes[j] /// Bytes don't match
					&& signature_bytes[j] != -1) /// Byte isn't a wildcard either, WHAT THE HECK
				{
					byte_sequence_found = false;
					break;
				}
			}

			if (byte_sequence_found)
				LOGS("Found signature %s: 0x%llx", sig, uintptr_t(&image_bytes[i]));

			/// All good, now return the right address
			if (byte_sequence_found)
				return address_t(uintptr_t(&image_bytes[i]));
		}
	}

	LOGS("Failed to find signature %s", sig);

	/// Byte sequence wasn't found
	return {};
}

address_t utility::get_vfunc(address_t table, uint16_t index)
{
	return table.get<uintptr_t*>()[index];
}

uint32_t utility::get_vtable_length(address_t table)
{
	auto length = uint32_t{};

	/// Walk through every function until it is no longer valid
	for (length = 0; table.cast<uintptr_t*>()[length]; length++)
		if (IS_INTRESOURCE(table.cast<uintptr_t*>()[length]))
			break;

	return length;
}

uintptr_t utility::GetMethod(uintptr_t table, const char* funcName)
{

	uint64_t hash = 0x79D6530B0BB9B5D1;
	uint64_t prime = 0x10000000233;

	while (*funcName)
	{
		uint8_t byte = *funcName++;

		if (static_cast<uint8_t>(byte - 65) <= 25)
			byte += 32;

		hash = prime * ((uint64_t)byte ^ hash);
	}

	while (uint64_t gsc_hash = *reinterpret_cast<uintptr_t*>(table))
	{
		if (gsc_hash ^ hash)
		{
			table += 0x10;
			continue;
		}

		return *reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(table + 8) + 8);
	}

	return NULL;
}


uintptr_t utility::PatternScan(const char* sig, const char* mask, uintptr_t begin, unsigned int size)
{
	unsigned int patternLength = strlen(sig);

	for (unsigned int i = 0; i < size - patternLength; i++)
	{
		if (MemCompare((const char*)(begin + i), (const char*)sig, mask)) {
			return begin + i;
		}
	}
	return (uintptr_t)nullptr;

}

uintptr_t utility::PatternScanEx(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask)
{
	BYTE* data = new BYTE[size];
	SIZE_T bytesRead;

	ReadProcessMemory(hProcess, (LPVOID)start, data, size, &bytesRead);

	for (uintptr_t i = 0; i < size; i++)
	{
		if (MemCompare((const char*)(data + i), (const char*)sig, mask)) {
			return start + i;
		}
	}
	delete[] data;
	return NULL;
}

uintptr_t utility::FindOffset(const char* sig, const char* mask, uintptr_t begin, unsigned int size, uintptr_t base_offset, uintptr_t pre_base_offset, uintptr_t rindex, bool addRip)
{
	auto address = utility::PatternScan(sig, mask, begin, size) + rindex;
	if (!address)
		return 0;

	auto ret = pre_base_offset + (*reinterpret_cast<int32_t*>(static_cast<unsigned long long>(address) + base_offset));

	if (addRip)
	{
		ret = ret + address;
		if (ret)
			return (ret - g_vars->baseModule);
	}

	return ret;
}

BOOL CALLBACK process::EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);
	if (dwPid == lParam)
	{
		hwnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

HWND process::get_process_window()
{
	if (hwnd)
		return hwnd;

	EnumWindows(process::EnumWindowCallBack, GetCurrentProcessId());

	if (hwnd == NULL)
		Exit();

	return hwnd;
}

HWND process::get_process_window(DWORD procID)
{
	if (hwnd)
		return hwnd;

	EnumWindows(process::EnumWindowCallBack, procID);

	if (hwnd == NULL)
		Exit();

	return hwnd;
}