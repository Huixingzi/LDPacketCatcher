#include "pch.h"
#include "CSocketPacket.h"


CSocketPacket::CSocketPacket()
{
	s = 0;
	type = SocketType::Send;
	pByte = NULL;
	len = 0;

	LocAddr = L"空";
	PeerAddr = L"空";
}

CSocketPacket::CSocketPacket(SOCKET _sock, CString fileName)
{
	s = _sock;
	ReadPacket(this, fileName);
	type = SocketType::Send;

	LocAddr = L"空";
	PeerAddr = L"空";
}

CSocketPacket::CSocketPacket(SOCKET _sock, PBYTE _pByte, INT _len, SocketType _type)
{
	s = _sock;
	len = _len;
	pByte = new BYTE[len];
	memcpy(pByte, _pByte, len);
	type = _type;

	LocAddr = DisplayIP_local(s) + ':' + DisplayPort_local(s);
	PeerAddr = DisplayIP_peer(s) + ':' + DisplayPort_peer(s);
}

CSocketPacket::CSocketPacket(CSocketPacket* pCsp)
{
	s = pCsp->s;
	len = pCsp->len;
	type = pCsp->type;
	pByte = new BYTE[len];
	memcpy(pByte, pCsp->pByte, len);

	LocAddr = pCsp->LocAddr;
	PeerAddr = pCsp->PeerAddr;
}


CSocketPacket::~CSocketPacket()
{
	delete[] pByte;
}

CString CSocketPacket::DisplaySocket(SOCKET s)
{
	CString Ret;
	Ret.Format(_T("%d"), (INT)s);

	return Ret;
}

CString CSocketPacket::DisplayLen(INT len)
{
	CString Ret;
	Ret.Format(_T("%d"), len);
	
	return Ret;
}

CString CSocketPacket::GetSaveDir()
{
	CString filePath;

	TCHAR szDmtPath[MAX_PATH] = { 0 };

	if (FAILED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, szDmtPath)))
	{
		MessageBox(NULL, _T("获取文档路径出错"), L"温馨提示", 0);
		return filePath;
	}

	//获得路径
	filePath.Format(_T("%s"), szDmtPath);
	filePath = filePath + _T("\\Assist\\Packet\\");
	if (!PathIsDirectory(filePath))
	{
		CreateDirectory(filePath, NULL);
	}

	return filePath;
}

//显示
CString CSocketPacket::DisplayType(SocketType type)
{
	CString Ret;

	switch (type)
	{
	case SocketType::Send:
		Ret = _T("Send");
		break;
	case SocketType::Recv:
		Ret = _T("Recv");
		break;
	case SocketType::SendTo:
		Ret = _T("SendTo");
		break;
	case SocketType::RecvFrom:
		Ret = _T("RecvFrom");
		break;
	default:
		break;
	}

	return Ret;
}

CString CSocketPacket::DisplayIP_local(SOCKET s)
{
	CHAR cip[32] = { 0 };
	CString ip_local;

	struct sockaddr_in addr = { 0 };
	int len = sizeof(sockaddr_in);
	if (!getsockname(s, (struct sockaddr*)&addr, &len)) {
		inet_ntop(AF_INET, &addr.sin_addr, cip, sizeof(cip));

		USES_CONVERSION;
		ip_local = A2CT(cip);
	}
	else {
		ip_local = _T("获取本地ip失败");
	}
	return ip_local;
}

CString CSocketPacket::DisplayPort_local(SOCKET s)
{
	CString port_local;

	struct sockaddr_in addr = { 0 };
	int len = sizeof(sockaddr_in);
	if (!getsockname(s, (struct sockaddr*)&addr, &len)) {
		port_local.Format(_T("%d"), ntohs(addr.sin_port));
	}
	else {
		port_local = _T("获取本地端口失败");
	}

	return port_local;
}

CString CSocketPacket::DisplayIP_peer(SOCKET s)
{
	CHAR cip[20] = { 0 };
	CString ip_peer;

	struct sockaddr_in addr = { 0 };
	int len = sizeof(sockaddr_in);
	if (!getpeername(s, (struct sockaddr*)&addr, &len)) {
		inet_ntop(AF_INET, &addr.sin_addr, cip, sizeof(cip));

		USES_CONVERSION;
		ip_peer = A2CT(cip);
	}
	else {
		ip_peer = _T("获取对方IP失败");
	}
	return ip_peer;
}

CString CSocketPacket::DisplayPort_peer(SOCKET s)
{
	CString port_peer;

	struct sockaddr_in addr = { 0 };
	int len = sizeof(sockaddr_in);
	if (!getpeername(s, (struct sockaddr*)&addr, &len)) {
		port_peer.Format(_T("%d"), ntohs(addr.sin_port));
	}
	else
	{
		port_peer = _T("获取对方端口失败");
	}

	return port_peer;
}


/// <summary>
/// 以cstring方式显示byte数组，
/// </summary>
/// <param name="pByte"></param>
/// <param name="len"></param>
/// <param name="LineShowBytes">每行显示的字符数</param>
/// <returns></returns>
CString CSocketPacket::DisplayChar(PBYTE pByte, INT len, INT LineShowBytes)
{
	CString Ret, str;  

	for (INT i = 0; i < len; ++i)
	{
		str.Format(L"%c", pByte[i] < 0x20 ? '.' : pByte[i]);
		Ret += str;
		if ((i + 1) % LineShowBytes == 0) Ret += L"\r\n";
	}

	return Ret;
}

BOOL CSocketPacket::SetBuf(CSocketPacket* pCsp, CString Buf)
{
	INT strLen = Buf.GetLength();
	PCHAR pText = new CHAR[strLen];

	USES_CONVERSION;
	memcpy(pText, T2A(Buf), strLen);

	for (INT i = 2; i < strLen; i += 3)
	{
		if (pText[i] != 0x20) {
			delete[] pText;
			return FALSE;
		}
	}

	if (pCsp && pCsp->pByte) delete[] pCsp->pByte;

	pCsp->len = (strLen % 3 == 0) ? strLen /3 : strLen / 3 + 1;
	pCsp->pByte = new BYTE[pCsp->len];

	for (INT i = 0, j = 0; i < strLen; i += 3, ++j)
	{
		pCsp->pByte[j] = (pText[i] & 0x40 ? (pText[i] << 4) + 0x90 : pText[i] << 4) | (pText[i + 1] & 0x40 ? (pText[i + 1] & 0x0f) + 0x09 : pText[i + 1] & 0x0f);
	}

	delete[] pText;
	return TRUE;
}


CString CSocketPacket::DisplayBuf(PBYTE pByte, INT len, INT ShowBytes)
{
	CString Ret, str;

	ShowBytes = ((ShowBytes == 0) | (ShowBytes > len)) ? len : ShowBytes;

	for (int i = 0; i < ShowBytes; ++i)
	{
		str.Format(L"%02x ", pByte[i]);
		Ret += str;
	}

	return Ret;
}

//操作
INT CSocketPacket::Send(CSocketPacket* pCsp)
{
	INT iRet = send(pCsp->s, (CONST CHAR*)pCsp->pByte, pCsp->len, 0);

	if (iRet == SOCKET_ERROR)return 0;
	if (iRet == pCsp->len) return 1;
	return -1;
}

VOID CSocketPacket::SavePacket(CSocketPacket* pCsp, CString fileName)
{
	CString filePath;

	switch (pCsp->type)
	{
	case SocketType::Send:
		filePath = GetSaveDir() + L"s_" + fileName + L".packet";
		break;
	case SocketType::SendTo:
		filePath = GetSaveDir() + L"st_" + fileName + L".packet";
		break;
	case SocketType::Recv:
		filePath = GetSaveDir() + L"r_" + fileName + L".packet";
		break;
	case SocketType::RecvFrom:
		filePath = GetSaveDir() + L"rf_" + fileName + L".packet";
		break;
	default:
		filePath = GetSaveDir() + L"zz_" + fileName + L".packet";
		break;
	}

	std::ofstream ofs;
	ofs.open(filePath, std::ios::out | std::ios::trunc);
	ofs.write((CHAR *)pCsp->pByte, pCsp->len);
	ofs.close();

}

VOID CSocketPacket::ReadPacket(CSocketPacket* pCsp, CString fileName)
{
	CString filePath;
	filePath = GetSaveDir() + fileName + L".packet";

	std::ifstream ifs;
	ifs.open(filePath, std::ios::in | std::ios::binary);
	ifs.seekg(0, std::ios::end);

	pCsp->len = (INT)ifs.tellg();

	pCsp->pByte = new BYTE[pCsp->len];
	ifs.seekg(0, std::ios::beg);
	ifs.read((CHAR *)pCsp->pByte, pCsp->len);
	ifs.close();
}