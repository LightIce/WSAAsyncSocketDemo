
// SocketClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SocketClient.h"
#include "SocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSocketClientDlg 对话框




CSocketClientDlg::CSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocketClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSocketClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CSocketClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_SEND, &CSocketClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CSocketClientDlg 消息处理程序

BOOL CSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CEdit *editPort = (CEdit *)GetDlgItem(IDC_PORT);
	editPort->SetWindowText("10240");

	CEdit *editAddress = (CEdit *)GetDlgItem(IDC_SERVERIP);
	editAddress->SetWindowText("127.0.0.1");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSocketClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSocketClientDlg::OnPaint()
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
HCURSOR CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketClientDlg::OnBnClickedConnect()
{
	CEdit *editTemp = (CEdit *)GetDlgItem(IDC_PORT);
	if (editTemp->GetWindowTextLengthA() == 0)
	{
		AfxMessageBox("请填写端口号!");
		return;
	}
	editTemp = (CEdit *)GetDlgItem(IDC_SERVERIP);
	if (editTemp->GetWindowTextLengthA() == 0)
	{
		AfxMessageBox("请填写IP地址");
		return ;
	}


	AfxBeginThread(ThreadProc, this);

}


BOOL CSocketClientDlg::WinSockInit()
{
	WSADATA wsaDATA;
	if(WSAStartup(MAKEWORD(2, 2), &wsaDATA) == 0)
	{
		return TRUE;
	}
	else
	{
		WSACleanup();
		AfxMessageBox("SOCKET 初始化失败！");
		return FALSE;
	}
}


BOOL CSocketClientDlg::Socket_select(SOCKET hSock, int nTimeOut /* = 100 */, BOOL bRead /* = TRUE */)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSock, &fdset);
	nTimeOut = nTimeOut > 1000 ? 1000 : nTimeOut;
	tv.tv_sec  = 0;
	tv.tv_usec = nTimeOut;

	int iRet = 0;
	if ( bRead ) 
	{
		iRet = select(0, &fdset, NULL , NULL, &tv);
	}
	else
	{
		iRet = select(0, NULL , &fdset, NULL, &tv);
	}

	if(iRet <= 0) 
	{
		return FALSE;
	} 
	else if (FD_ISSET(hSock, &fdset))
	{
		return TRUE;
	}
	return FALSE;
}


UINT CSocketClientDlg::ThreadProc(LPVOID pParam)
{
	CSocketClientDlg *pThis = (CSocketClientDlg*)pParam;
	if (pThis->WinSockInit() == FALSE)
	{
		return 0;
	}
	pThis->m_socket = socket(2,1,0);
	if (pThis->m_socket == INVALID_SOCKET)
	{
		AfxMessageBox("新建socket失败！");
		return 0;
	}

	CString strPort;
	char szPort[8];
	ZeroMemory(szPort, 8);
	USHORT nPort = 0;;
	CEdit *editPort =(CEdit *)pThis->GetDlgItem(IDC_PORT);
	editPort->GetWindowText(strPort);
	char *t = (LPSTR)(LPCTSTR)strPort;

	memcpy(szPort, t, editPort->GetWindowTextLength());
	nPort = atoi(szPort);

	CString strAddress;
	char szAddress[16];
	ZeroMemory(szAddress, 16);

	CEdit *editAddress = (CEdit *)pThis->GetDlgItem(IDC_SERVERIP);
	editAddress->GetWindowText(strAddress);
	t = (LPSTR)(LPCTSTR)strAddress;

	memcpy(szAddress, t, editAddress->GetWindowTextLength());

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(nPort);
	addrServer.sin_addr.S_un.S_addr = inet_addr(szAddress);

	if ( connect(pThis->m_socket, (sockaddr *)&addrServer, sizeof(addrServer)) != 0)
	{
		AfxMessageBox("连接失败！");
		WSACleanup();
		return 0;
	}

	while (TRUE)
	{
		if (pThis->Socket_select(pThis->m_socket))
		{
			char szBuffer[4096];
			ZeroMemory(szBuffer, 4096);
			int iRet = recv(pThis->m_socket, szBuffer, 4096, 0);
#ifdef _DEBUG
			CString ss;
			CEdit *editMsgLog = (CEdit *)pThis->GetDlgItem(IDC_MESSAGELOG);
			editMsgLog->GetWindowText(ss);
			ss += "Recved.\r\n";
			CString tt;
			tt.Format("%s %d", szBuffer, iRet);
			ss += tt;
			editMsgLog->SetWindowTextA(ss);
#endif

			if (iRet > 0)
			{	
				CEdit *editMsgLog = (CEdit *)pThis->GetDlgItem(IDC_MESSAGELOG);
				CString strMsgLog;
				CString strTemp;
				strTemp.Format("%s", szBuffer);
				editMsgLog->GetWindowText(strMsgLog);
				strMsgLog += "[Recv] ";
				strMsgLog += strTemp;
				strMsgLog += "\r\n";
				editMsgLog->SetWindowTextA(strMsgLog);

				int index = editMsgLog->GetLineCount();
				editMsgLog->LineScroll(index, 0);

				ZeroMemory(szBuffer, 4096);
			}
			else
			{
				AfxMessageBox("服务器已跪，请重新连接!");
				WSACleanup();
				break;
			}
		}
	}
}

void CSocketClientDlg::OnBnClickedSend()
{
	CEdit *editSendMessage = (CEdit *)GetDlgItem(IDC_SENDMESSAGE);
	if (editSendMessage->GetWindowTextLengthA() == 0)
	{
		AfxMessageBox("请输入内容后再发送！");
		return ;
	}

	CString strSendMessage;
	editSendMessage->GetWindowTextA(strSendMessage);
// 	char szSendMessage[4096];
// 	char *t = (LPSTR)(LPCTSTR)strSendMessage;
// 	memcpy(szSendMessage, t, editSendMessage->GetWindowTextLengthA());

	if (m_socket == INVALID_SOCKET)
	{
		AfxMessageBox("socket错误！！");
		return ;
	}
	
	if (Socket_select(m_socket, 100 ,FALSE) )
	{
		send(m_socket, (char *)strSendMessage.GetBuffer(), strSendMessage.GetLength()*sizeof(char), 0);
		//
		CString strMsgLog;

		CEdit *editMsgLog = (CEdit*)GetDlgItem(IDC_MESSAGELOG);
		editMsgLog->GetWindowTextA(strMsgLog);
		strMsgLog += "[Send] ";
		strMsgLog += strSendMessage;
		strMsgLog += "\r\n";
	
		editMsgLog->SetWindowTextA(strMsgLog);
		int index = editMsgLog->GetLineCount();
		editMsgLog->LineScroll(index, 0);
	}



	return ;
}
