#pragma once

#ifndef _ATLSTR_H
#define _ATLSTR_H
#include "atlstr.h"
#endif // !_ATLSTR_H

/// <summary>
/// 判断Exe是否存在Dll
/// </summary>
/// <param name="dwPID">Exe的PID</param>
/// <param name="DllName">Dll名</param>
/// <returns></returns>
PBYTE isExistDll(DWORD dwPID, CString DllName);

/// <summary>
/// 注入DLL
/// </summary>
/// <param name="dwPID">进程PID值</param>
/// <param name="DllName">DLL名</param>
/// <returns></returns>
BOOL InjectDLL(DWORD dwPID, CString DllName);

/// <summary>
/// 弹出DLL
/// </summary>
/// <param name="dwPID">进程PID值</param>
/// <param name="DllName">DLL名</param>
/// <returns></returns>
BOOL EjectDll(DWORD dwPID, CString DllName);

/// <summary>
/// 根据进程名获取PID值
/// </summary>
/// <param name="ProcName"></param>
/// <returns>返回PID</returns>
DWORD GetProcessPID(CString ProcName);


/// <summary>
/// 注入dll到某进程
/// </summary>
/// <param name="ProcName">进程名</param>
/// <param name="DllName">Dll名</param>
/// <returns></returns>
BOOL InjectProc(CString ProcName, CString DllName);