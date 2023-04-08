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

	//��ʾ ========================
	static CString DisplaySocket(SOCKET s); //��ʾ�׽���
	static CString DisplayLen(INT len); //��ʾ����
	static CString DisplayType(SocketType type); //��÷������
	static CString DisplayBuf(PBYTE pByte, INT len, INT ShowBytes = 0); //��ʾ�������
	static CString DisplayChar(PBYTE pByte, INT len, INT LineShowBytes = 16); //��ʾΪ�ַ�

	static BOOL SetBuf(CSocketPacket* pCsp, CString Buf); //��ʾΪ�ַ�

	static CString DisplayIP_local(SOCKET s); //��ñ���ip
	static CString DisplayPort_local(SOCKET s); //��ñ��ض˿�
	static CString DisplayIP_peer(SOCKET s); //��öԷ�IP
	static CString DisplayPort_peer(SOCKET s); //��öԷ��˿�

	//���� =======================
	static INT Send(CSocketPacket * pCsp); //���ͷ��

	//���� =====================
	static CString GetSaveDir();

	static VOID SavePacket(CSocketPacket* pCsp, CString fileName);
	static VOID ReadPacket(CSocketPacket* pCsp, CString fileName);
};

typedef CSocketPacket CSOCKETPACKET, * PCSOCKETPACKET;
