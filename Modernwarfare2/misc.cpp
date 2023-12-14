#include "misc.h"


namespace misc
{
	std::string to_utf8(std::wstring_view wstr)
	{
		if (wstr.empty())
			return std::string();

		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);

		std::string out(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), &out[0], size_needed, NULL, NULL);

		return out;
	}

	std::wstring to_unicode(std::string_view str)
	{
		if (str.empty())
			return std::wstring();

		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), NULL, 0);

		std::wstring out(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), &out[0], size_needed);

		return out;
	}

	std::string generate_random_string(const int len)
	{
		srand(static_cast<unsigned int>(__rdtsc()));

		std::string tmp_s;
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		tmp_s.reserve(len);

		for (int i = 0; i < len; ++i)
			tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


		return tmp_s;
	}

	std::string generate_unique_random_string(const int seed, const int len)
	{
		TCHAR  infoBuf[32767];
		DWORD  bufCharCount = 32767;

		GetComputerNameA(infoBuf, &bufCharCount);

		auto new_seed = HASH(infoBuf);

		srand(seed + new_seed);

		std::string tmp_s;
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		tmp_s.reserve(len);

		for (int i = 0; i < len; ++i)
			tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


		return tmp_s;
	}
}