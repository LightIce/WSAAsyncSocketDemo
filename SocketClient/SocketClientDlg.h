
// SocketClientDlg.h : ͷ�ļ�
//

#pragma once


// CSocketClientDlg �Ի���
class CSocketClientDlg : public CDialogEx
{
// ����
public:
	CSocketClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKETCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	BOOL WinSockInit();

	SOCKET m_socket;
	BOOL Socket_select(SOCKET hSock, int nTimeOut = 100, BOOL bRead = TRUE);

	static UINT __cdecl ThreadProc(LPVOID pParam);
	afx_msg void OnBnClickedSend();
};
