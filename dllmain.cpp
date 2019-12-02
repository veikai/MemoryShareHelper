// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "namedpipe.h"

NamedPipe namedPipe;

std::wstring StringToWstring(std::string str) {
	std::wstring result;
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';
	result.append(buffer);
	delete[] buffer;
	return result;
}

extern "C" __declspec(dllexport) int init(char* pipe_path) {

	return namedPipe.init(StringToWstring(pipe_path).c_str());
}

extern "C" __declspec(dllexport) char* read() {
	return namedPipe.read_pipe();
}
