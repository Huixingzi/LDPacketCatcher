#pragma once
#include <WinSock2.h>

#ifndef _SOCKET_TYPE
#define _SOCKET_TYPE
enum class SocketType { Send, Recv, SendTo, RecvFrom };
#endif

//��ʼ���ֽ���Ϣ,ʹ��ǰ��Ҫ��ʼ��
BOOL InitHook();

//�ָ�����,ֹͣHOOK,��ֹͣ��������
bool StopHook();

//��ʼ���ӣ�����Hook,����ʼ��������
bool StartHook();

//������, ��Ҫʵ�֣����浽�����м���
bool SavePacket(SOCKET s, const char* pbuf, int len, SocketType type);

