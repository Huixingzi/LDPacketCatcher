#include "pch.h"
#include "CBufEdit.h"
BEGIN_MESSAGE_MAP(CBufEdit, CEdit)

	ON_CONTROL_REFLECT(EN_UPDATE, &CBufEdit::OnEnUpdate)
END_MESSAGE_MAP()


/// <summary>
/// �����༭������
/// </summary>
/// <param name="pMsg"></param>
/// <returns></returns>
BOOL CBufEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message) {
		CString str;
		int startloc, endloc;
		GetSel(startloc, endloc);

		if (pMsg->wParam == VK_BACK)
		{
			if (startloc % 3 != 0) {
				GetWindowText(str);
				str.Delete(startloc / 3 * 3, 3);
				SetWindowText(str);
				SetSel(startloc / 3 * 3, startloc / 3 * 3, FALSE);
			}
			else {
				GetWindowText(str);
				str.Delete(startloc - 3, 3);
				SetWindowText(str);
				SetSel(startloc - 3, startloc - 3, FALSE);
			}
			
			return true;
		}

		if (pMsg->wParam == VK_TAB) {
			SetSel(startloc / 3 * 3 + 5, startloc / 3 * 3 + 5, FALSE);
			return true;
		}

		if (pMsg->wParam == VK_LEFT) {
			SetSel(startloc - 3, startloc - 3, FALSE);
			return true;
		}

		if (pMsg->wParam == VK_RIGHT) {
			SetSel(startloc + 3, startloc + 3, FALSE);
			return true;
		}

		if (pMsg->wParam == VK_SPACE) {
			SetSel(startloc / 3 * 3 + 5, startloc / 3 * 3 + 5, FALSE);
			return true;
		}

		if ((pMsg->wParam >= 0x30 && pMsg->wParam <= 0x39) | (pMsg->wParam >= 0x40 && pMsg->wParam <= 0x46))
		{
			return CEdit::PreTranslateMessage(pMsg);//���˷Ƿ��ַ�
		}

		return true;
	}

	return CEdit::PreTranslateMessage(pMsg);
}


void CBufEdit::OnEnUpdate()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CEdit::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int startLoc, endLoc;
	GetSel(startLoc, endLoc);

	CString str;
	GetWindowText(str);

	if ((startLoc - 1) % 3 == 0) {
		str.Delete(startLoc + 1, 1);
		SetWindowText(str);
		SetSel(startLoc, startLoc, false);
	}
	else if ((startLoc - 1) % 3 == 1)
	{
		str.Delete(startLoc, 1);
		SetWindowText(str);
		SetSel(startLoc, startLoc, false);
	}
	else if ((startLoc - 1) % 3 == 2)
	{
		str.Insert(startLoc, L"0");
		str.Insert(startLoc - 1, L" ");
		SetWindowText(str);
		SetSel(startLoc + 1, startLoc + 1, false);
	}

	if (pCsp) CSOCKETPACKET::SetBuf(pCsp, str); //����ǰ������buf

	return;
}
