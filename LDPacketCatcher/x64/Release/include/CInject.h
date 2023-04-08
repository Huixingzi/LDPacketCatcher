#pragma once

#ifndef _ATLSTR_H
#define _ATLSTR_H
#include "atlstr.h"
#endif // !_ATLSTR_H

/// <summary>
/// �ж�Exe�Ƿ����Dll
/// </summary>
/// <param name="dwPID">Exe��PID</param>
/// <param name="DllName">Dll��</param>
/// <returns></returns>
PBYTE isExistDll(DWORD dwPID, CString DllName);

/// <summary>
/// ע��DLL
/// </summary>
/// <param name="dwPID">����PIDֵ</param>
/// <param name="DllName">DLL��</param>
/// <returns></returns>
BOOL InjectDLL(DWORD dwPID, CString DllName);

/// <summary>
/// ����DLL
/// </summary>
/// <param name="dwPID">����PIDֵ</param>
/// <param name="DllName">DLL��</param>
/// <returns></returns>
BOOL EjectDll(DWORD dwPID, CString DllName);

/// <summary>
/// ���ݽ�������ȡPIDֵ
/// </summary>
/// <param name="ProcName"></param>
/// <returns>����PID</returns>
DWORD GetProcessPID(CString ProcName);


/// <summary>
/// ע��dll��ĳ����
/// </summary>
/// <param name="ProcName">������</param>
/// <param name="DllName">Dll��</param>
/// <returns></returns>
BOOL InjectProc(CString ProcName, CString DllName);