#pragma once


// CFriendsWindowDlg 对话框

class CFriendsWindowDlg : public CDialog
{
    DECLARE_DYNAMIC(CFriendsWindowDlg)

public:
    CFriendsWindowDlg(CWnd * pParent = nullptr);   // 标准构造函数
    virtual ~CFriendsWindowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DLG_FRIENDS };
#endif

protected:
    virtual void DoDataExchange(CDataExchange * pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
private:
    // 好友列表
    CListCtrl m_lstFriends;
};
