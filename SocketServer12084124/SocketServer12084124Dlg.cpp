
// SocketServer12084124Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocketServer12084124.h"
#include "SocketServer12084124Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSocketServer12084124Dlg �Ի���




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


// CSocketServer12084124Dlg ��Ϣ�������

BOOL CSocketServer12084124Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CEdit *editPort;
	editPort = (CEdit *)GetDlgItem(IDC_PORT);
	editPort->SetWindowText("10240");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSocketServer12084124Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSocketServer12084124Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketServer12084124Dlg::OnBnClickedStartservice()
{
	GetDlgItem(IDC_STOPSERVICE)->EnableWindow(TRUE);	//ʹֹͣ����ť����
	GetDlgItem(IDC_STARTSERVICE)->EnableWindow(FALSE);	//���ÿ�ʼ����ť

	AfxBeginThread(ThreadProc, this);
}


void CSocketServer12084124Dlg::OnBnClickedStopservice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//����ֹͣ����ť
	GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//������������ť

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


// ���عر���Ϣ��
// �ر�ʱ����ȷ�Ͽ�
void CSocketServer12084124Dlg::OnClose()
{
	if (IDYES == ::MessageBox(NULL, "���Ҫ�˳���","�˳�", MB_YESNO))
	{
		CDialogEx::OnClose();
	}
}


// ��oninitdlg�е��ã�������ʼ��һЩ��Ϣ
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

		GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//����ֹͣ����ť
		GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//������������ť

		return false;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
		// �����׽�����������ʱ 
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

			GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//����ֹͣ����ť
			GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//������������ť

			AfxMessageBox("Accept ʧ�ܣ�");

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
		AfxMessageBox("socket ��Ч!");
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
			AfxMessageBox("�����뷢������!");
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

	//���PORT�Ƿ�Ϊ��
	CEdit *editPort;
	editPort = (CEdit *)pThis->GetDlgItem(IDC_PORT);

	if ( (editPort->GetWindowTextLength()) == 0)
	{
		AfxMessageBox("����д�˿ں�");
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//����ֹͣ����ť
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//������������ť
		return 0;
	}

	// ��ȡport
	CString strPort;
	editPort->GetWindowText(strPort);	//��ȡCString���͵Ķ˿ں�
	char *t = (LPSTR)(LPCTSTR)strPort;	//ת��Ϊchar *����

	char szPort[8];						//��Ŷ˿ں�
	ZeroMemory(szPort, 8);				//�����ڴ�
	//�����ڴ�
	memcpy(szPort, t, editPort->GetWindowTextLengthA());

	USHORT nPort = atoi(szPort);			//charתint

	//AF_INET:2 SOCK_STREAM:1
	pThis->sock = socket(2, 1, 0);
	if (pThis->sock == INVALID_SOCKET)
	{
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//����ֹͣ����ť
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//������������ť

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

		AfxMessageBox("socketʧ�ܣ�");
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
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//����ֹͣ����ť
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//������������ť

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

		AfxMessageBox("bindʧ�ܣ�");
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

	// ����WSAAsyncSelect
	if (WSAAsyncSelect(pThis->sock, pThis->GetSafeHwnd(), WM_SOCKET, FD_ACCEPT | FD_CLOSE | FD_CONNECT) == 0)
	{
		// ���óɹ�
		editLog->GetWindowText(strLog);
		strLog += "[Info] WSAAsyncSelect success.\r\n";
		editLog->SetWindowTextA(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
	}
	else
	{
		// ����ʧ��
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//����ֹͣ����ť
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//������������ť

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

		AfxMessageBox("WSAAsyncSelectʧ�ܣ�");
		WSACleanup();
		return 0;
	}

	if (listen(pThis->sock, 5) == 0)
	{
		//���óɹ�
		editLog->GetWindowText(strLog);
		strLog += "[Info] listen success.\r\n";
		editLog->SetWindowTextA(strLog);

		index = editLog->GetLineCount();
		editLog->LineScroll(index, 0);
	}
	else
	{
		//����ʧ��
		pThis->GetDlgItem(IDC_STOPSERVICE)->EnableWindow(FALSE);	//����ֹͣ����ť
		pThis->GetDlgItem(IDC_STARTSERVICE)->EnableWindow(TRUE);	//������������ť

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

		AfxMessageBox("listenʧ�ܣ�");
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