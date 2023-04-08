#pragma once

#ifndef _SOCKET_TYPE
#define _SOCKET_TYPE
enum class SocketType { Send, Recv, SendTo, RecvFrom };
#endif

class CSocketPacket
{
public:
	CSocketPacket();
	CSocketPacket(SOCKET _sock, CString fileName);
	CSocketPacket(SOCKET _sock, PBYTE _pByte, INT _len = 1, SocketType _type = SocketType::Send);
	CSocketPacket(CSocketPacket * pCsp);
	
	~CSocketPacket();

	SOCKET s;
	SocketType type;
	PBYTE pByte;
	INT len;

	CString LocAddr;
	CString PeerAddr;

	//显示 ========================
	static CString DisplaySocket(SOCKET s); //显示套接字
	static CString DisplayLen(INT len); //显示长度
	static CString DisplayType(SocketType type); //获得封包类型
	static CString DisplayBuf(PBYTE pByte, INT len, INT ShowBytes = 0); //显示封包内容
	static CString DisplayChar(PBYTE pByte, INT len, INT LineShowBytes = 16); //显示为字符

	static BOOL SetBuf(CSocketPacket* pCsp, CString Buf); //显示为字符

	static CString DisplayIP_local(SOCKET s); //获得本地ip
	static CString DisplayPort_local(SOCKET s); //获得本地端口
	static CString DisplayIP_peer(SOCKET s); //获得对方IP
	static CString DisplayPort_peer(SOCKET s); //获得对方端口

	//操作 =======================
	static INT Send(CSocketPacket * pCsp); //发送封包

	//方法 =====================
	static CString GetSaveDir();

	static VOID SavePacket(CSocketPacket* pCsp, CString fileName);
	static VOID ReadPacket(CSocketPacket* pCsp, CString fileName);
};

typedef CSocketPacket CSOCKETPACKET, * PCSOCKETPACKET;
