#pragma once
#define DLL_API   __declspec(dllexport)
/*#include "stdafx.h"*/
#include <windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <commctrl.h>
#define GP 50                               //最大股票处理数

using namespace std;

typedef struct tagWNDINFO
{
	DWORD dwProcessId;
	HWND hWnd;
	char*    tag_title;
} WNDINFO, *LPWNDINFO;

struct   PositionItem
{
	char*  accountequity;                   //净值
	char*  accountfree;                     //可用资金
	char*  marketvalue;                     //市值
	char*  opsitionloss;                    //盈亏
	char*  opsitionrange;                //仓位
	char*  profitratio;                     //盈亏比例
};

class  DLL_API  Pystock
{
public:
	Pystock();
	~Pystock();
	//****接口函数/* 1.开启软件  2. 登录交易   3. 关闭软件*/
	int			OpenTrade(char *filename);
	HWND	GetWindowHd(DWORD  target, char* target_text);
	HWND	GetAdWindowHd(DWORD  target, char* target_text);
	int			LoginTrade(char *accName, char * secret, char * conSecret);
	int			CloseAdWindow();				//关闭广告窗口
	int			CloseTrade();
	int			HideTrade();							//软件隐藏函数
	int			LoginFailed();						//登录失败处理函数
	void		firsthidetrade();
	bool		IsVisble();								//返回窗口状态

	//****预处理函数
	int			PreHandle();							//窗口预处理函数
	//***********获取h_toolBar买入卖出持仓撤单成交刷新句柄
	void		getToolBar();							//获取toolbar的句柄
	void		getBtnBar();							//获取下单按钮的句柄
	void		getBuy();								//获取买入按钮的句柄
	void		getSell();								//获取卖出按钮的句柄
	void		getAbsort();							//获取撤单按钮的句柄
	void		getDeal();								//获取成交列表的句柄

	//****
	void		getPosition();						//获取持仓界面的句柄
	void		prePosition();
	//****获取持仓界面的实现函数
	void		getAccountTicket(int &rows, int &cols);
	bool		getAccoutHead();
	void		rangeAccount_Head();

	//****获取撤单界面的实现函数
	void		getAbsortTicket(int &rows, int &cols);
	bool		getAbsortHead();
	void		rangeAbsort_Head();

	//****获取成交界面的实现函数
	void		getDealTicket(int &rows, int &cols);
	bool		getDealHead();
	void		rangeDeal_Head();

	//****进程号
	DWORD		id_login;
	//****下单函数
	bool        iBuy(char* _stockcode,
		char* _orderprice,
		char* _orderlots);     //买入股票
	bool        iSell(char* _stockcode,
		char* _orderprice,
		char* _orderlots);     //卖出股票
	bool        iAbsort(char* _stockcode, bool AbsortAll);  //取消订单
	PositionItem		iPosition();
	bool		iTradeConfirm(int temp_icon);

private:                                    //----类成员函数
	//****软件开启、登录、验证


private:                                    //----类成员
	char* appName1 = "通达信网上交易V6.01";
	char* appName2 = "提示";
	char* appName3 = "通达信网上交易V6V5.78";
	char* appName4 = "买入交易确认";
	char* appName5 = "卖出交易确认";
	//****账户信息
	char*       accountName;                //账户名称
	char*       ibName;                     //券商名称
	char*       tradeSecret;                //交易密码
	char*       connetSecret;               //通讯密码
	//****句柄
	HWND        h_mainLogin;                //登录窗口
	HWND        h_mainTrade;                //交易窗口
	HWND		h_loginfailed;				//登录失败窗口
	HWND        h_adWindow;                //广告窗口
	HWND        h_tradeBar;                    //下单工具栏的句柄(买入|卖出|撤单|持仓)
	HWND        h_toolBar[8];                  //获取下单工具栏的上层句柄（h_toolBar的上层）
	HWND        h_buybtn[30];               //买入下单的句柄数组（买入，价格，数量，下单按钮）
	HWND        h_sellbtn[6];                  //卖出下单的句柄数组（卖出，价格，数量，下单按钮）
	HWND        h_Hposition[10];          //持仓状态下的句柄
	HWND        h_Absortticket[10];     //撤单状态的句柄
	HWND		h_Dealticket[10];			//成交列表的句柄
	HWND		h_tradeConfirm;			//成交确认
	//****类
	PositionItem item;

	//****交易软件属性
	bool		isopened = false;				//软件是否打开
	bool		islogined = false;				//软件是否登录

	char*      appFile;								 //软件所在目录
	char        loginTitle[50];					 //登录窗口名
	char        failTitle[50];						 //登录失败时，窗口名
	char        tradeTitle[50];					 //交易窗口名
	char        positionTitle[200];			 //账户简况

	char*      AccountTicket[GP][25];        //持仓列表
	char*      AccountHeader[25];             //持仓列表表头
	int           AccHeaderRange[25];         //表头顺序
	int           TicketNumber;						//持仓数量

	char*      AbsortTicket[GP][25];			//撤单列表
	char*		AbsortHeader[25];				//撤单列表表头
	int			AbsHeaderRange[25];		//表头顺序

	char*      DealTicket[GP][25];			//成交列表
	char*		DealHeader[25];
	int			DealHeaderRange[25];

	int			PosNum;						    //持仓信息个数
	char*		PosInfo[20];						//持仓详细信息
	//****交易参数
	const char* stockCode;                  //交易股票代码
	const char* orderPrice;                 //交易股票价格
	const char* orderLots;                  //交易股票数量
};
