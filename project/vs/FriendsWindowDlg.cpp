// FriendsWindowDlg.cpp: 实现文件
//

#include "pch.h"
#include "ChatRoomClient.h"
#include "FriendsWindowDlg.h"
#include "afxdialogex.h"


// CFriendsWindowDlg 对话框

IMPLEMENT_DYNAMIC(CFriendsWindowDlg, CDialog)

CFriendsWindowDlg::CFriendsWindowDlg(CWnd * pParent /*=nullptr*/)
    : CDialog(IDD_DLG_FRIENDS, pParent)
{

}

CFriendsWindowDlg::~CFriendsWindowDlg()
{
}

void CFriendsWindowDlg::DoDataExchange(CDataExchange * pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LST_FRIENDS, m_lstFriends);
}


BEGIN_MESSAGE_MAP(CFriendsWindowDlg, CDialog)
END_MESSAGE_MAP()


// CFriendsWindowDlg 消息处理程序


BOOL CFriendsWindowDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    CRect rect;
    m_lstFriends.GetClientRect(&rect);
    m_lstFriends.SetExtendedStyle(LVS_EX_TRACKSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_lstFriends.SetBkColor(RGB(135, 206, 235));
    m_lstFriends.SetTextBkColor(RGB(135, 206, 235));
    m_lstFriends.InsertColumn(0, _T("昵称"), LVCFMT_CENTER, rect.Width());
    m_lstFriends.InsertItem(0, _T("雄霸天下"));
    m_lstFriends.InsertItem(1, _T("小熊"));

    return TRUE;
}
