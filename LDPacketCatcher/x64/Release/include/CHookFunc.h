#pragma once
#include <WinSock2.h>

#ifndef _SOCKET_TYPE
#define _SOCKET_TYPE
enum class SocketType { Send, Recv, SendTo, RecvFrom };
#endif

//初始话字节信息,使用前需要初始化
BOOL InitHook();

//恢复钩子,停止HOOK,即停止接受数据
bool StopHook();

//开始钩子，进行Hook,即开始接受数据
bool StartHook();

//储存封包, 需要实现，储存到容器中即可
bool SavePacket(SOCKET s, const char* pbuf, int len, SocketType type);

