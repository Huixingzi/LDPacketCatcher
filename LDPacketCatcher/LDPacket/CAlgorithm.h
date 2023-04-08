#pragma once


class CAlgorithm
{
public:
	virtual INT AGcompress(PCSOCKETPACKET pCsp, int loc, int len) = 0;
	virtual INT AGuncompress(PCSOCKETPACKET pCsp, int loc, int len) = 0;
};


class CZlibAlgorithm : public CAlgorithm
{
public:
	CZlibAlgorithm(){};

	INT AGcompress(PCSOCKETPACKET pCsp, int loc, int len);
	INT AGuncompress(PCSOCKETPACKET pCsp, int loc, int len);
};
