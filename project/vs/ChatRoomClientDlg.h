﻿
// ChatRoomClientDlg.h: 头文件
//

#pragma once

class CFriendsWindowDlg;
class CGroupsWindowsDlg;

// CChatRoomClientDlg 对话框
class CChatRoomClientDlg : public CDialogEx
{
// 构造
public:
    CChatRoomClientDlg(CWnd * pParent = nullptr);    // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DLG_MAIN };
#endif

protected:
    virtual void DoDataExchange(CDataExchange * pDX);    // DDX/DDV 支持


// 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
private:
    CTabCtrl m_tabOption;
    CEdit m_edtRecord;
    CEdit m_edtMsg;
    CToolBar m_toolBar;
    CImageList m_imgList;
    CFriendsWindowDlg * m_dlgFriends = nullptr;
    CGroupsWindowsDlg * m_dlgGroups = nullptr;

protected:
    // 加载聊天室界面
    void loadChatRoomWindows();

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnBnClickedBtnFile();
    afx_msg void OnBnClickedBtnPicture();
    afx_msg void OnBnClickedBtnMore();
    afx_msg void OnBnClickedBtnSend();
    afx_msg void OnBnClickedBtnClear();
};
