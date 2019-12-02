#include "pch.h"
#include "namedpipe.h"

int NamedPipe::init(const wchar_t* pipe_path)
{
	hPipe = CreateNamedPipe(pipe_path,							            //�ܵ���  
							PIPE_ACCESS_DUPLEX,										//�ܵ����ͣ�˫��ͨ��  
							PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,  //�ܵ�����  
							PIPE_UNLIMITED_INSTANCES,								//�ܵ��ܴ��������ʵ������  
							0,														//������������� 0��ʾĬ��  
							0,														//���뻺�������� 0��ʾĬ��  
							NMPWAIT_WAIT_FOREVER,									//��ʱʱ��,NMPWAIT_WAIT_FOREVERΪ����ʱ�ȴ�
							NULL);
	if (INVALID_HANDLE_VALUE == hPipe) {
		MessageBox(NULL, L"�����ܵ�ʧ��: ", NULL, 0);
		return -1;
	}
	if (!ConnectNamedPipe(hPipe, NULL))						//�����ȴ��ͻ������ӡ�  
	{
		MessageBox(NULL, L"����ʧ��: ", NULL, 0);
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
