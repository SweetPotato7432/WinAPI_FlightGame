#pragma once
#include "framework.h"
#include "WinAPIClass.h"

#define MAX_LOADSTRING 100

// ����� ���� ����
//
// <���>
// - ��� 
//	�������� �̵�
//	���� �ݺ��ؼ� ���´�.
// 
// - �÷��̾� ��ü
//	����Ű�� �̵�
//	�����̽��ٷ� �Ѿ� �߻�
//	�ִϸ��̼�
//	�� ��ü�� �Ѿ˿� �ǰݽ� ���� ����
//  
// - �� ��ü
//  �÷��̾ ���� �̵�
//	�÷��̾ ���� �Ѿ��� �߻�
//	�ִϸ��̼�
//	�÷��̾� ��ü�� �Ѿ˿� ������ �ı��ȴ�.(�ı� �̹��� ���)
//	
// - �Ѿ� 
//	������ �������� �̵�
//	����⿡ ������ ����� �� �ڱ��ڽ� �ı�
//	�ִϸ��̼�(�Ѿ� ȸ��)

// ��ҵ��� GameObject Ŭ�������� �����Ѵ�.

class Application
{
private :
	static Application* instance;

private : 
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


private : 
	HINSTANCE hInst;                               
	HWND hWnd;
	TCHAR szTitle[MAX_LOADSTRING];                  
	TCHAR szWindowClass[MAX_LOADSTRING];    

private :
	GraphicManager graphic;

public : 
	ATOM RegisterWindow(HINSTANCE hInstance);
	BOOL Initiate(int nCmdShow);
	int MessageLoop();
	LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	static HINSTANCE GetInstanceHandle();

public : 
	Application();
	~Application() = default;

};

