// WHU.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。


/*
#include <windows.h> //基于全局变量的多线程的多线程同步程序
#include <iostream>
using namespace std;
int globalvar = false; //同步全局变量
DWORD WINAPI ThreadFunc(LPVOID pParam)
{
	cout << "Wuhan\n" << endl;
	Sleep(200);
	globalvar = true;
	return 0;
}

DWORD WINAPI ThreadFunc2(LPVOID pParam)
{
	cout << "University" << endl;
	Sleep(1000);
	globalvar = true;
	return 0;
}
int main()
{
	HANDLE hthread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);//创建新线程
	HANDLE hthread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);//创建新线程
	if (!hthread)
	{
		cout << "Thread Create Error ! " << endl;
		CloseHandle(hthread);
	}
	
	while (!globalvar)
		Beep(1000,500); // 主线程运行,调用蜂鸣器
		cout << "the program is end." << endl;
	return 0;
}

*/


/*
//基于事件的多线程的多线程同步程序
#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;
HANDLE evBegin, evFinish;

void WuhanThread(void* param) {
	//等待事件evBegin
	WaitForSingleObject(evBegin, INFINITE);
	//写入Wuhan操作
	cout << "Wuhan" << endl;
	//激发事件evFinish
	SetEvent(evFinish);
}

void UniThread(void* param) {
	//写入University操作
	cout << "University" << endl;
	//唤醒事件evBegin
	SetEvent(evBegin);
}

int main()
{
	//创建两个事件，并初始化为未激发状态
	evBegin = CreateEvent(NULL, false, false, NULL);
	evFinish = CreateEvent(NULL, false, false, NULL);

	//创建Wuhan线程和Uni线程
	_beginthread(WuhanThread, 0, NULL);
	_beginthread(UniThread, 0, NULL);

	//等待事件evFinish
	WaitForSingleObject(evFinish, INFINITE);
	cout << "the program is end." << endl;

	return 0;
}
*/

//基于临界区的多线程的多线程同步程序
#include <windows.h>
#include <process.h>
#include <iostream>
#include <fstream>
using namespace std;
HANDLE evFin[2];
CRITICAL_SECTION cs;
void WithdrawThread1(LPVOID param)
{
	EnterCriticalSection(&cs);
	cout << "Wuhan\n" << endl;
	LeaveCriticalSection(&cs);
	SetEvent(evFin[0]);
	SetEvent(evFin[0]);	
}

void WithdrawThread2(LPVOID param)
{
	cout << "University" << endl;
	LeaveCriticalSection(&cs);
	SetEvent(evFin[1]);
	Sleep(1000);
}

int main(int argc, char* argv[])
{
	evFin[0] = CreateEvent(NULL,FALSE,FALSE,NULL);
	evFin[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&cs);
	_beginthread(WithdrawThread1, 0, NULL);
	_beginthread(WithdrawThread2, 0, NULL);
	WaitForMultipleObjects(2, evFin, TRUE, INFINITE);
	DeleteCriticalSection(&cs);
	Sleep(1000);
	cout << "the program is end." << endl;
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
