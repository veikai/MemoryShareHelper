#pragma once
#include <minwindef.h>
#include <string>
class NamedPipe
{
private:
	char msg_buffer[4096] = { 0 };
	DWORD read_length = 0;
	HANDLE hPipe = NULL;
public:
	int init(const wchar_t* pipe_path);
	char* read_pipe();
};

