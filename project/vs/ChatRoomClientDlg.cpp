
// ChatRoomClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ChatRoomClient.h"
#include "ChatRoomClientDlg.h"
#include "FriendsWindowDlg.h"
#include "afxdialogex.h"
#include "libos.h"
#include <string.h>
#include <errno.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange * pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange * pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatRoomClientDlg 对话框



CChatRoomClientDlg::CChatRoomClientDlg(CWnd * pParent /*=nullptr*/)
    : CDialogEx(IDD_DLG_MAIN, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatRoomClientDlg::DoDataExchange(CDataExchange * pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_OPTION, m_tabOption);
    DDX_Control(pDX, IDC_EDT_RECORD, m_edtRecord);
    DDX_Control(pDX, IDC_EDT_MSG, m_edtMsg);
}

BEGIN_MESSAGE_MAP(CChatRoomClientDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CREATE()
    ON_COMMAND(IDC_BTN_FILE, &CChatRoomClientDlg::OnBnClickedBtnFile)
    ON_COMMAND(IDC_BTN_PICTURE, &CChatRoomClientDlg::OnBnClickedBtnPicture)
    ON_COMMAND(IDC_BTN_MORE, &CChatRoomClientDlg::OnBnClickedBtnMore)
    ON_BN_CLICKED(IDC_BTN_SEND, &CChatRoomClientDlg::OnBnClickedBtnSend)
    ON_BN_CLICKED(IDC_BTN_CLEAR, &CChatRoomClientDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CChatRoomClientDlg 消息处理程序

BOOL CChatRoomClientDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu * pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    // TODO: 在此添加额外的初始化代码
    m_tabOption.InsertItem(0, _T("好友"));
    m_tabOption.InsertItem(1, _T("群/组"));
    loadChatRoomWindows();

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatRoomClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatRoomClientDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatRoomClientDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


int CChatRoomClientDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialogEx::OnCreate(lpCreateStruct) == -1)
        return -1;

     //创建ToolBar工具条
    m_toolBar.Create(this);

    //创建位图  CImageList
    HICON hIcon = NULL;
    m_imgList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 0, 0);//加载图片大小，图片格式，图片数量

    m_imgList.SetBkColor(GetSysColor(COLOR_WINDOW));

    hIcon = (HICON) ::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICO_FILE), IMAGE_ICON, 32, 32, 0);//导入添加学生图片0
    m_imgList.Add(hIcon);

    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICO_PICTURE), IMAGE_ICON, 32, 32, 0);//导入删除学生图片1
    m_imgList.Add(hIcon);

    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICO_MORE), IMAGE_ICON, 32, 32, 0);//导入查询学生图片2
    m_imgList.Add(hIcon);

    //添加按钮信息
    m_toolBar.GetToolBarCtrl().SetImageList(&m_imgList);
    m_toolBar.SetButtons(NULL, 6);

    m_toolBar.SetButtonInfo(0, IDC_BTN_FILE, TBSTYLE_BUTTON, 0);
    m_toolBar.SetButtonText(0, _T(""));

    m_toolBar.SetButtonInfo(1, -1, TBSTYLE_SEP, -1);
    m_toolBar.SetButtonText(1, _T(""));

    m_toolBar.SetButtonInfo(2, IDC_BTN_PICTURE, TBSTYLE_BUTTON, 1);
    m_toolBar.SetButtonText(2, _T(""));

    m_toolBar.SetButtonInfo(3, -1, TBSTYLE_SEP, -1);
    m_toolBar.SetButtonText(3, _T(""));

    m_toolBar.SetButtonInfo(4, IDC_BTN_MORE, TBSTYLE_BUTTON, 2);
    m_toolBar.SetButtonText(4, _T(""));

    m_toolBar.SetButtonInfo(5, -1, TBSTYLE_SEP, -1);
    m_toolBar.SetButtonText(5, _T(""));

    //设置工具栏按钮大小
    m_toolBar.SetSizes(CSize(32, 32), CSize(24, 24));
    m_toolBar.EnableToolTips(TRUE);
    CRect rect;
    GetClientRect(rect);
    CRect rectBar(CPoint(0, static_cast<int>(0.8 * rect.Height()) - 3), CPoint(400, static_cast<int>(0.9 * rect.Height()) - 3));
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, 0, 0, &rectBar); //显示工具栏

    return 0;
}

void CChatRoomClientDlg::OnBnClickedBtnFile()
{
    MessageBox(_T("发送文件"));
}

void CChatRoomClientDlg::OnBnClickedBtnPicture()
{
    MessageBox(_T("发送图片"));
}

void CChatRoomClientDlg::OnBnClickedBtnMore()
{
    MessageBox(_T("更多"));
}

void CChatRoomClientDlg::OnBnClickedBtnSend()
{
    // TODO: 在此添加控件通知处理程序代码
}


void CChatRoomClientDlg::OnBnClickedBtnClear()
{
    m_edtMsg.SetWindowText(_T(""));
}

void CChatRoomClientDlg::loadChatRoomWindows()
{
    CRect rect;
    m_tabOption.GetWindowRect(&rect);

    m_dlgFriends = new CFriendsWindowDlg();
    if (nullptr == m_dlgFriends)
    {
        log_msg_error("new CFriendsWindowDlg failed, err:%s", strerror(errno));
        return;
    }
    m_dlgFriends->Create(IDD_DLG_FRIENDS, this);
    m_dlgFriends->MoveWindow(rect);
    rect.left -= 16;
    rect.right += 20;
    //rect.top -= 8;
    m_dlgFriends->ShowWindow(SW_SHOW);
}
