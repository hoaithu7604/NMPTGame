#pragma once
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

#pragma once
#include <string>
#include <vector>
#include <windows.h>

class Utility {
public:
	static string wchar_t2string(const wchar_t *wchar);
	static wchar_t *string2wchar_t(const string &str);
	static vector<string> listFilesInDirectory(string directoryName);
};

