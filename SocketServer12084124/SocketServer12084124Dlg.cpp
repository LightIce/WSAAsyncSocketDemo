
// SocketServer12084124Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SocketServer12084124.h"
#include "SocketServer12084124Dlg.h"
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
//	afx_msg LRESULT OnSocketMsg(WPARAM wParam, LPARAM lParam);
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


// CSocketServer12084124Dlg 对话框




CSocketServer12084124Dlg::CSocketServer12084124Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocketServer12084124Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketServer12084124Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSocketServer12084124Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTSERVICE, &CSocketServer12084124Dlg::OnBnClickedStartservice)
	ON_BN_CLICKED(IDC_STOPSERVICE, &CSocketServer12084124Dlg::OnBnClickedStopservice)
	ON_WM_CLOSE()
//	ON_MESSAGE(WM_SOCKET, &CSocketServer12084124Dlg::OnSocketMsg)
	ON_BN_CLICKED(IDC_SEND, &CSocketServer12084124Dlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CSocketServer12084124Dlg 消息处理程序

BOOL CSocketServer12084124Dlg::OnInitDialog()
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

	CEdit *editPort;
	editPort = (CEdit *)GetDlgItem(IDC_PORT);
	editPort->SetWindowText("10240");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSocketServer12084124Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocketServer12084124Dlg::OnPaint()
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
HCURSOR CSocketServer12084124Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketServer12084124Dlg::OnBnClickedStartservice()
{
	GetDlgItem(IDC_STOPSERVICE)->EnableWindow(TRUE);	//使停止服务按钮可用
	GetDlgItem(IDC_STARTSERVICE)->EnableWindow(FALSE);	//禁用开始服务按钮

	AfxBeginThread(ThreadProc, this);
}


void CSocketServer12084124Dlg::OnBnClickedStopservice()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//禁用停止服务按钮
	GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//启用启动服务按钮

	int index = 0;

	CEdit *editLog;
	editLog = (CEdit *)GetDlgItem(IDC_LOG);

	CString strLog;
	editLog->GetWindowText(strLog);

	strLog += "[System] Service stopping...\r\n";
	editLog->SetWindowText(strLog);

	index = editLog->GetLineCount();
	editLog->LineScroll(index, 0);

	closesocket(sockClient);
	closesocket(sock);

	WSACleanup();
	if (WSACleanup() == 0)
	{
		editLog->GetWindowText(strLog);
		strLog += "[Info] WSACleanup success.\r\n";
		editLog->SetWindowText(strLog);
		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
	}
}


// 重载关闭消息。
// 关闭时弹出确认框
void CSocketServer12084124Dlg::OnClose()
{
	if (IDYES == ::MessageBox(NULL, "真的要退出？","退出", MB_YESNO))
	{
		CDialogEx::OnClose();
	}
}


// 在oninitdlg中调用，用来初始化一些信息
BOOL CSocketServer12084124Dlg::WinSockInit(void)
{
	CEdit *editLog = (CEdit *)GetDlgItem(IDC_LOG);
	CString strLog;

	int index = 0;

	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2,2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		editLog->GetWindowText(strLog);
		strLog += "[Error] WSAStartup failed.\r\n";
		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);

		AfxMessageBox("[Error] WSAStartup failed.");
		return FALSE;
	}
	else
	{
		editLog->GetWindowText(strLog);
		strLog += "[Info] WSAStartup success.\r\n";
		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);

		return TRUE;
	}

}

LRESULT CSocketServer12084124Dlg::OnSocketMsg(WPARAM wParam, LPARAM lParam)
{
	SOCKET s = wParam;
	CString strLog;
	int index;
	//SOCKET sockClient;

	CEdit *editLog = (CEdit *)GetDlgItem(IDC_LOG);

	char szRecvBuffer[4096];
	ZeroMemory(szRecvBuffer, 4096);
	CString strBuffer;

	CEdit *editMsgLog = (CEdit *)GetDlgItem(IDC_MESSAGELOG);
	CString strMsgLog;


#ifdef _DEBUG
	editLog->GetWindowText(strLog);
	strLog += "[DEBUG] OnSocketMsg\r\n";
	editLog->SetWindowText(strLog);

	index = editLog->GetLineCount();
	editLog->LineScroll(index, 0);
#endif

	if (WSAGETSELECTERROR(lParam))
	{
		editLog->GetWindowText(strLog);
		strLog += "[Error] Get Select error!\r\n";
		editLog->SetWindowText(strLog);
		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);

		//AfxMessageBox("Get Select Error!");

		closesocket(s);

		GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//禁用停止服务按钮
		GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//启用启动服务按钮

		return false;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
		// 当有套接字连接上来时 
		sockClient = accept(wParam, NULL, NULL);
#ifdef _DEBUG
		editLog->GetWindowText(strLog);
		strLog += "[DEBUG] FD_ACCEPT\r\n";
		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
#endif
		if (sockClient == INVALID_SOCKET)
		{
			editLog->GetWindowText(strLog);
			strLog += "[Error] accept failed.\r\n";
			editLog->SetWindowText(strLog);

			index = editLog->GetLineCount();
			editLog->LineScroll(index, 0);

			GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//禁用停止服务按钮
			GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//启用启动服务按钮

			AfxMessageBox("Accept 失败！");

			return 0;
		}
		else
		{
			editLog->GetWindowText(strLog);
			strLog += "[Info] Accept success.\r\n";
			strLog += "[Info] A Remote host has connected.\r\n";

			index = editLog->GetLineCount();
			editLog->LineScroll(index, 0);
		}
		WSAAsyncSelect(sockClient, m_hWnd, WM_SOCKET, FD_CLOSE | FD_WRITE | FD_READ);
		break;
	case FD_WRITE:
		wParam = wParam;
		break;
	case FD_READ:

		recv(wParam, szRecvBuffer, 4096, 0);
		strBuffer.Format("%s", szRecvBuffer);
		editMsgLog->GetWindowText(strMsgLog);
		strMsgLog += "[Recv] ";
		strMsgLog += strBuffer;
		strMsgLog += "\r\n";

		index = editMsgLog->GetLineCount();
		editMsgLog->LineScroll(index, 0);	
		break;
	case FD_CLOSE:
		closesocket(wParam);
		editLog->GetWindowTextA(strLog);
		strLog += "[Info] A Remote host has disconnected.\r\n";
		editLog->SetWindowTextA(strLog);
		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
		break;
	default:
		break;
	}
	return 0;
}


void CSocketServer12084124Dlg::OnBnClickedSend()
{
	int index = 0;
	CString strLog;
	CString strMessage;
	CString strMsgLog;

	CEdit *editLog = (CEdit *)GetDlgItem(IDC_LOG);
	CEdit *editMsgLog = (CEdit *)GetDlgItem(IDC_MESSAGELOG);
	CEdit *editMessage = (CEdit *)GetDlgItem(IDC_MESSAGE);

	if (sockClient == INVALID_SOCKET)
	{
		AfxMessageBox("socket 无效!");
		editLog->GetWindowText(strLog);
		strLog += "[Error] member socket invalid.\r\n";
		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
		return;
	}
	else
	{
		editMsgLog->GetWindowText(strMsgLog);
		editMessage->GetWindowText(strMessage);

		if (editMessage->GetWindowTextLength() == 0)
		{
			AfxMessageBox("请输入发送内容!");
			return;
		}
		else
		{
			//AfxMessageBox(strMessage);
			send(sockClient, (char *)strMessage.GetBuffer(), strMessage.GetLength()*sizeof(char), 0);
			editMessage->SetWindowText("");
			editMsgLog->GetWindowText(strMsgLog);
			strMsgLog += "[Send] ";
			strMsgLog += strMessage;
			strMsgLog += "\r\n";
			editMsgLog->SetWindowText(strMsgLog);

			index = editMsgLog->GetLineCount();
			editMsgLog->LineScroll(index, 0);
		
		}

	}
}

LRESULT CSocketServer12084124Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	int index;
	CEdit *editLog = (CEdit *)GetDlgItem(IDC_LOG);
	CEdit *editMsgLog = (CEdit *)GetDlgItem(IDC_MESSAGELOG);
	CString strMsgLog;
	CString strTemp;
	CString strLog;
	CString strMessage;
	CEdit *editMessage = (CEdit *)GetDlgItem(IDC_MESSAGE);

	switch(message)
	{
	case WM_SYSCOMMAND:
		break;
	case WM_SOCKET:
		if (WSAGETSELECTERROR(lParam))
		{
			closesocket(wParam);
			editLog->GetWindowTextA(strLog);
			strLog += "[Info] A remote host has disconnected.\r\n";
			editLog->SetWindowTextA(strLog);

			index = editLog->GetLineCount();
			editLog->LineScroll(index, 0);
		}
		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_ACCEPT:
			sockClient = accept(wParam, NULL, NULL);
			if (sockClient == INVALID_SOCKET)
			{
				editLog->GetWindowTextA(strLog);
				strLog += "[Error] Accept failed.\r\n";
				editLog->SetWindowTextA(strLog);

				index = editLog->GetLineCount();
				editLog->LineScroll(index, 0);
			}
			else
			{
				editLog->GetWindowTextA(strLog);
				strLog += "[Info] A remote host has connected.\r\n";
				editLog->SetWindowTextA(strLog);

				index = editLog->GetLineCount();
				editLog->LineScroll(index, 0);
			}
			WSAAsyncSelect(sockClient, m_hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
			break;
		case FD_READ:
			char szBuffer[4096];
			ZeroMemory(szBuffer, 4096);
			recv(wParam, szBuffer, 4096, 0);

			strTemp.Format("%s", szBuffer);

			editMsgLog->GetWindowTextA(strMsgLog);
			strMsgLog += "[recv] ";
			strTemp.Format("%s", szBuffer);
			strMsgLog += strTemp;
			strMsgLog += "\r\n";
			editMsgLog->SetWindowTextA(strMsgLog);

			index = editMsgLog->GetLineCount();
			editMsgLog->LineScroll(index, 0);
			break;
		case FD_WRITE:
			//AfxMessageBox("FD_WRITE");
			wParam = wParam;
			break;
		}
		break;
	default:break;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}



UINT CSocketServer12084124Dlg::ThreadProc(LPVOID pParam)
{
	CSocketServer12084124Dlg *pThis = (CSocketServer12084124Dlg*)pParam;
	int index = 0;;

	CEdit *editLog;
	editLog = (CEdit *)pThis->GetDlgItem(IDC_LOG);
	CString strLog;

	editLog->GetWindowText(strLog);
	strLog += "[System] Service starting...\r\n";
	editLog->SetWindowText(strLog);

	index = editLog->GetLineCount();
	editLog->LineScroll(index, 0);

	pThis->WinSockInit();

	//检查PORT是否为空
	CEdit *editPort;
	editPort = (CEdit *)pThis->GetDlgItem(IDC_PORT);

	if ( (editPort->GetWindowTextLength()) == 0)
	{
		AfxMessageBox("请填写端口号");
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//禁用停止服务按钮
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//启用启动服务按钮
		return 0;
	}

	// 获取port
	CString strPort;
	editPort->GetWindowText(strPort);	//获取CString类型的端口号
	char *t = (LPSTR)(LPCTSTR)strPort;	//转换为char *类型

	char szPort[8];						//存放端口号
	ZeroMemory(szPort, 8);				//清零内存
	//复制内存
	memcpy(szPort, t, editPort->GetWindowTextLengthA());

	USHORT nPort = atoi(szPort);			//char转int

	//AF_INET:2 SOCK_STREAM:1
	pThis->sock = socket(2, 1, 0);
	if (pThis->sock == INVALID_SOCKET)
	{
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//禁用停止服务按钮
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//启用启动服务按钮

		int x = WSAGetLastError();
		editLog->GetWindowText(strLog);
		strLog += "[Error] socket failed.\r\n";
		strLog += "[Error] WSAGetLastError: ";

		char aa[12];
		ZeroMemory(aa, 12);
		sprintf(aa, "%d", x);
		CString errorNum;
		errorNum.Format("%s", aa);

		strLog += errorNum;
		strLog += "\r\n";

		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);

		AfxMessageBox("socket失败！");
		WSACleanup();
		return 0;
	}
	else
	{
		editLog->GetWindowText(strLog);
		strLog += "[Info] create socket success.\r\n";
		strLog += "[Info] Port: ";
		strLog += strPort;
		strLog += "\r\n";

		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = ntohs(nPort);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(pThis->sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//禁用停止服务按钮
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//启用启动服务按钮

		int x = WSAGetLastError();

		editLog->GetWindowText(strLog);
		strLog += "[Error] Bind failed.\r\n";
		strLog += "[Error] WSAGetLastError: ";

		char aa[12];
		ZeroMemory(aa, 12);
		sprintf(aa, "%d", x);
		CString errorNum;
		errorNum.Format("%s", aa);

		strLog += errorNum;
		strLog += "\r\n";

		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);

		AfxMessageBox("bind失败！");
		WSACleanup();
		return 0;
	}
	else
	{
		editLog->GetWindowText(strLog);
		strLog += "[Info] Bind success.\r\n";
		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
	}

	// 调用WSAAsyncSelect
	if (WSAAsyncSelect(pThis->sock, pThis->GetSafeHwnd(), WM_SOCKET, FD_ACCEPT | FD_CLOSE | FD_CONNECT) == 0)
	{
		// 调用成功
		editLog->GetWindowText(strLog);
		strLog += "[Info] WSAAsyncSelect success.\r\n";
		editLog->SetWindowTextA(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
	}
	else
	{
		// 调用失败
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//禁用停止服务按钮
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//启用启动服务按钮

		int x = WSAGetLastError();

		editLog->GetWindowText(strLog);
		strLog += "[Error] WSAAsyncSelect failed.\r\n";
		strLog += "[Error] WSAGetLastError: ";

		char aa[12];
		ZeroMemory(aa, 12);
		sprintf(aa, "%d", x);
		CString errorNum;
		errorNum.Format("%s", aa);

		strLog += errorNum;
		strLog += "\r\n";

		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);

		AfxMessageBox("WSAAsyncSelect失败！");
		WSACleanup();
		return 0;
	}

	if (listen(pThis->sock, 5) == 0)
	{
		//调用成功
		editLog->GetWindowText(strLog);
		strLog += "[Info] listen success.\r\n";
		editLog->SetWindowTextA(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
	}
	else
	{
		//调用失败
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//禁用停止服务按钮
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//启用启动服务按钮

		int x = WSAGetLastError();

		editLog->GetWindowText(strLog);
		strLog += "[Error] listen failed.\r\n";
		strLog += "[Error] WSAGetLastError: ";

		char aa[12];
		ZeroMemory(aa, 12);
		sprintf(aa, "%d", x);
		CString errorNum;
		errorNum.Format("%s", aa);

		strLog += errorNum;
		strLog += "\r\n";

		editLog->SetWindowText(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);

		AfxMessageBox("listen失败！");
		WSACleanup();
		return 0;
	}

	editLog->GetWindowText(strLog);
	strLog += "[Info] Waiting for connection...\r\n";
	editLog->SetWindowTextA(strLog);

	index = editLog->GetLineCount();
	editLog->LineScroll(index, 0);
	return 0 ;
}