
// SocketServer12084124Dlg.h : ͷ�ļ�
//

#pragma once
#define WM_SOCKET (WM_USER + 10)


// CSocketServer12084124Dlg �Ի���
class CSocketServer12084124Dlg : public CDialogEx
{
// ����
public:
	CSocketServer12084124Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKETSERVER12084124_DIALOG };

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
	afx_msg void OnBnClickedStartservice();
	afx_msg void OnBnClickedStopservice();
	afx_msg void OnClose();
	afx_msg void OnBnClickedSend();
	BOOL WinSockInit();
	// ���ڴ���socket��Ϣ
	afx_msg LRESULT OnSocketMsg(WPARAM wParam, LPARAM lParam);
	SOCKET sock;
	SOCKET sockClient;
	
	static UINT __cdecl ThreadProc(LPVOID pParam);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
