#include <Windows.h>

int main()
{
	ShellExecute(NULL, L"open", L".\\BeInside_x64.exe", L"LdVBoxHeadless.exe LDPacket.dll", NULL, SW_SHOW);

	return 0;
}