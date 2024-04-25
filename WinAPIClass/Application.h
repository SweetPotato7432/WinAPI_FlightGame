#pragma once
#include "framework.h"
#include "WinAPIClass.h"

#define MAX_LOADSTRING 100

// 비행기 슈팅 게임
//
// <요소>
// - 배경 
//	좌측으로 이동
//	무한 반복해서 나온다.
// 
// - 플레이어 기체
//	방향키로 이동
//	스페이스바로 총알 발사
//	애니메이션
//	적 기체의 총알에 피격시 게임 오버
//  
// - 적 기체
//  플레이어를 향해 이동
//	플레이어를 향해 총알을 발사
//	애니메이션
//	플레이어 기체의 총알에 맞으면 파괴된다.(파괴 이미지 출력)
//	
// - 총알 
//	임의의 방향으로 이동
//	비행기에 맞으면 비행기 와 자기자신 파괴
//	애니메이션(총알 회전)

// 요소들은 GameObject 클래스에서 관리한다.

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

