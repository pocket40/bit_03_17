//�߰� �� ��ȸ���� (�Ϻ� ����)
#include <Windows.h>
#include <commctrl.h>
#include "Member.h"
#include "resource.h"
#include <map>
map<wstring, Member*> mmap;
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
{
    DialogBox(hIns, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
    //MAKEINTRESOURCE
   // -���� ���� ���ҽ� ���� ��ɰ� ȣȯ�Ǵ� �������� ��ȯ
   // 
   // DialogBox
   // -��ȭ���� ���ø� ���ҽ����� ��� ��ȭ ���ڸ� ����ϴ�.
   // DialogBox�� ������ �ݹ� �Լ��� EndDialog �Լ��� ȣ���Ͽ� 
   // ��� ��ȭ���ڸ� ���� �� ������ ��Ʈ���� ��ȯ���� �ʽ��ϴ�.
   // 
   // ��Ʈ��
   //
    return 0;
}
void OnCancelProc(HWND hDlg)
{
    EndDialog(hDlg, IDCANCEL);
}
void InitControls(HWND hDlg)
{
    SetDlgItemText(hDlg, IDC_EDIT_ID, TEXT(""));
    SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""));
    //HWND sWnd = GetDlgItem(hDlg, IDC_SLIDER_AGE);
    //SetScrollPos(sWnd, SB_CTL, 0, TRUE); => ����~
    SetDlgItemText(hDlg, IDC_STATIC_AGE, TEXT("0"));
    SendDlgItemMessage(hDlg, IDC_RADIO_MALE, BM_SETCHECK, BST_CHECKED, 0);
    SendDlgItemMessage(hDlg, IDC_RADIO_FEMALE, BM_SETCHECK, BST_UNCHECKED, 0);
    SendDlgItemMessage(hDlg, IDC_CHECK_DRINK, BM_SETCHECK, BST_UNCHECKED, 0);
    SendDlgItemMessage(hDlg, IDC_CHECK_SMOKE, BM_SETCHECK, BST_UNCHECKED, 0);
}
void AddProc(HWND hDlg)
{
    WCHAR id[256];
    WCHAR name[256];
    int age;
    bool gender = false;
    bool is_smoker = false;
    bool is_drinker = false;
    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
    GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 256);
    age = GetDlgItemInt(hDlg, IDC_STATIC_AGE, 0, 0);
    if (SendDlgItemMessage(hDlg, IDC_RADIO_MALE, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        gender = true;
    }
    if (SendDlgItemMessage(hDlg, IDC_CHECK_DRINK, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        is_drinker = true;
    }
    if (SendDlgItemMessage(hDlg, IDC_CHECK_SMOKE, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        is_smoker = true;
    }
    if (mmap[id])
    {
        MessageBox(hDlg, TEXT("�̹� �����ϴ� ID�Դϴ�."), TEXT("�߰� ����!!!"), MB_OK);
    }
    else
    {
        Member* member = new Member(id, name, age, gender, is_smoker, is_drinker);
        mmap[id] = member;
        SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_ADDSTRING, 0, (LPARAM)id);
    }
    InitControls(hDlg);
}
void ModifyProc(HWND hDlg)
{

}
void FindProc(HWND hDlg)
{
    WCHAR id[256];
    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
    Member* member = mmap[id];
    if (member == 0)
    {
        MessageBox(hDlg, TEXT("�������� �ʽ��ϴ�."), TEXT("�˻� ����!!!"), MB_OK);
        return;
    }
    SetDlgItemText(hDlg, IDC_EDIT_NAME, member->GetName().c_str());
    SetDlgItemInt(hDlg, IDC_STATIC_AGE, member->GetAge(), TRUE);
    if (member->GetGender())
    {
        SendDlgItemMessage(hDlg, IDC_RADIO_MALE, BM_SETCHECK, BST_CHECKED, 0);
    }
    else
    {
        SendDlgItemMessage(hDlg, IDC_RADIO_FEMALE, BM_SETCHECK, BST_CHECKED, 0);
    }
    if (member->IsDrinker())
    {
        SendDlgItemMessage(hDlg, IDC_CHECK_DRINK, BM_SETCHECK, BST_CHECKED, 0);
    }
    else
    {
        SendDlgItemMessage(hDlg, IDC_CHECK_DRINK, BM_SETCHECK, BST_UNCHECKED, 0);
    }
    if (member->IsSmoker())
    {
        SendDlgItemMessage(hDlg, IDC_CHECK_SMOKE, BM_SETCHECK, BST_CHECKED, 0);
    }
    else
    {
        SendDlgItemMessage(hDlg, IDC_CHECK_SMOKE, BM_SETCHECK, BST_UNCHECKED, 0);
    }
    int index = SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_FINDSTRING, 0, (LPARAM)id);
    SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_SETCURSEL, index, 0);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_MODIFY), true);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_REMOVE), true);
}
void MemberListChangeProc(HWND hDlg)
{
    int index = SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_GETCURSEL, 0, 0);
    WCHAR id[256];
    SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_GETTEXT, index, (LPARAM)id);
    SetDlgItemText(hDlg, IDC_EDIT_ID, id);
    FindProc(hDlg);
}
void MemberListProc(HWND hDlg, WORD cmsg)
{
    switch (cmsg)
    {
    case LBN_SELCHANGE: MemberListChangeProc(hDlg); return;
    }
}
void OnCommand(HWND hDlg, WORD cid, WORD cmsg, HWND cWnd)
{
    switch (cid)
    {
    case IDC_LIST_MEMBER: MemberListProc(hDlg, cmsg); return;
    case IDC_BUTTON_FIND: FindProc(hDlg); return;
    case IDC_BUTTON_MODIFY: ModifyProc(hDlg); return;
    case IDC_BUTTON_ADD: AddProc(hDlg); return;
    case IDCANCEL: OnCancelProc(hDlg); return;
    }
}
void OnDestroy(HWND hDlg)
{
    PostQuitMessage(0);
}
void SetAge(HWND hDlg)
{
    //GetDlgItem
    //SendMessage
    int pos = SendDlgItemMessage(hDlg, IDC_SLIDER_AGE, TBM_GETPOS, 0, 0);
    SetDlgItemInt(hDlg, IDC_STATIC_AGE, pos, 0);
}
void OnInitDlg(HWND hDlg)
{
    SendDlgItemMessage(hDlg, IDC_SLIDER_AGE, TBM_SETRANGE, FALSE, MAKELPARAM(0, 200));
    SetAge(hDlg);
}
void OnHScroll(HWND hDlg)
{
    SetAge(hDlg);
}
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG: OnInitDlg(hDlg); return TRUE;
    case WM_HSCROLL: OnHScroll(hDlg); return TRUE;
    case WM_COMMAND: OnCommand(hDlg,
        LOWORD(wParam), HIWORD(wParam), (HWND)lParam); return TRUE;
    case WM_DESTROY: OnDestroy(hDlg); return TRUE;
    }
    return FALSE;
}