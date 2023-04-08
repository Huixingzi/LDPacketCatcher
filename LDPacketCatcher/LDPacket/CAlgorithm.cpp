#include "pch.h"
#include "CAlgorithm.h"

/// <summary>
/// 使用zlib压缩
/// </summary>
/// <param name="pCsp"></param>
/// <param name="loc"></param>
/// <param name="len"></param>
INT CZlibAlgorithm::AGcompress(PCSOCKETPACKET pCsp, int loc, int len)
{
	if (!pCsp->pByte) return -1;
	DWORD cLen = compressBound(pCsp->len);	/* 压缩后的长度是不会超过blen的 */
	PBYTE pNewBuf = new BYTE[cLen];
	if (!pNewBuf) return -1;

	int iRet = compress((PBYTE)pNewBuf, &cLen, pCsp->pByte + loc, len);

	if (loc == 0) {
		delete[] pCsp->pByte;
		pCsp->pByte = pNewBuf;
		pCsp->len = cLen;
	}
	else
	{
		pCsp->len = loc + cLen;
		PBYTE tmp = new BYTE[pCsp->len];
		memcpy(tmp, pCsp->pByte, loc);
		memcpy(tmp + loc, pNewBuf, cLen);
		delete[] pCsp->pByte;
		delete[] pNewBuf;
		pCsp->pByte = tmp;
	}

	return iRet;
}

INT CZlibAlgorithm::AGuncompress(PCSOCKETPACKET pCsp, int loc, int len)
{
	DWORD dlen = 4096;
	PBYTE pNewBuf = new BYTE[dlen];
	memset(pNewBuf, 0, dlen);

	int iRet = uncompress(pNewBuf, &dlen, pCsp->pByte + loc, len);

	int Strlen = strlen((char *)pNewBuf);
	if (loc == 0) {
		delete[] pCsp->pByte;
		pCsp->pByte = pNewBuf;
		pCsp->len = Strlen;
	}
	else
	{
		pCsp->len = loc + Strlen;
		PBYTE tmp = new BYTE[pCsp->len];
		memcpy(tmp, pCsp->pByte, loc);
		memcpy(tmp + loc, pNewBuf, Strlen);
		delete[] pCsp->pByte;
		delete[] pNewBuf;
		pCsp->pByte = tmp;
	}

	return iRet;
}
