
// SocketServer12084124Dlg.h : 头文件
//

#pragma once
#define WM_SOCKET (WM_USER + 10)


// CSocketServer12084124Dlg 对话框
class CSocketServer12084124Dlg : public CDialogEx
{
// 构造
public:
	CSocketServer12084124Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SOCKETSERVER12084124_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 用于处理socket消息
	afx_msg LRESULT OnSocketMsg(WPARAM wParam, LPARAM lParam);
	SOCKET sock;
	SOCKET sockClient;
	
	static UINT __cdecl ThreadProc(LPVOID pParam);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
