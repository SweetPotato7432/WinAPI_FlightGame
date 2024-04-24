#pragma once
#include "framework.h"
#include "WinAPIClass.h"

#define MAX_LOADSTRING 100

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

public : 
	Application();
	~Application() = default;

};

