#include "pch.h"
#include "namedpipe.h"

int NamedPipe::init(const wchar_t* pipe_path)
{
	hPipe = CreateNamedPipe(pipe_path,							            //管道名  
							PIPE_ACCESS_DUPLEX,										//管道类型，双向通信  
							PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,  //管道参数  
							PIPE_UNLIMITED_INSTANCES,								//管道能创建的最大实例数量  
							0,														//输出缓冲区长度 0表示默认  
							0,														//输入缓冲区长度 0表示默认  
							NMPWAIT_WAIT_FOREVER,									//超时时间,NMPWAIT_WAIT_FOREVER为不限时等待
							NULL);
	if (INVALID_HANDLE_VALUE == hPipe) {
		MessageBox(NULL, L"创建管道失败: ", NULL, 0);
		return -1;
	}
	if (!ConnectNamedPipe(hPipe, NULL))						//阻塞等待客户端连接。  
	{
		MessageBox(NULL, L"连接失败: ", NULL, 0);
		return -1;
	}
	while (hPipe) {
		Sleep(1);
	}
	return init(pipe_path);
}

char* NamedPipe::read_pipe()
{
	if (hPipe) {
		if (ReadFile(hPipe, msg_buffer, 4096, &read_length, NULL)) {
			return msg_buffer;
		}
		else {
			hPipe = NULL;
			return (char*)-1;
		}	
	}
	return NULL;
}
