// 201321047_주수강_5.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "stdafx.h"
#include "201321047_주수강_5.h"
#include "egl\egl.h"
#include "vg\openvg.h"
#include "vgLoadImage.h"
#include "DXUTsound.h"

#define MAX_LOADSTRING 100
#define KEY_DOWN(code) (( GetAsyncKeyState(code)&0x80000)?1:0)
#define WIDTH 677
#define HEIGHT 10
// 변수강

HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

DWORD lastTime = GetTickCount();
EGLDisplay display;
EGLSurface surface;
EGLContext context;

char map[HEIGHT][WIDTH];

CSoundManager* sm = NULL;


CSound* Menutrack =NULL;
CSound* Practicetrack =NULL;
CSound* Boop =NULL;
CSound* Explosion =NULL;
CSound* Fireworks =NULL;
CSound* Medal =NULL;
CSound* Soundtrack =NULL;

float Theta=0;
int x=40;
int fx=0;
int Height=210;
//text에서 플레이어 좌표는 (5,1)이다
int JumpCount=0;
int MedalOn=false;
bool BreakLevel=false;
int AttemptCount=1;
int TotalAttempt=0;
int PracticeOn=0;
int PlayerW[2];
int GameCount=0;
int HowToPlayCount=0;
int MedalCount=0;
int Mousex=0,Mousey=0;
int LoadingCount=0;
int LoadingMenuCount=-1;
int LoadingMenuAnimation=0;
int LevelCount=-1;
int LevelAnimation=0;
int PauseCount=-1;
int PauseAnimation=0;
int GameStats=0;
int LevSelectpix;
int JumpAnimation=0;
int RightAnimation=0;
int LeftAnimation=0;
float Levelx=0;
int LevelNum=0;
int CameraX=0;
int CameraCount=true;
int i=0;
int Deadcount=0;
int DeadFlag=false;
int FallingFlag=false;
int PracticeFlag=0;
struct Saved{
	float Theta;
	int x;
	int fx;
	int Height;

	char map[HEIGHT][WIDTH];
	int PlayerW[2];
	int JumpAnimation;
	int CameraX;
	int i;
	int FallingFlag;
	int FlagX,FlagY;
}saved[100];
VGImage Default, BlackRect,MenuStartFade,MenuBackGround,MenuHowToPlayButton,
	MenuMedalsButton,MenuStartButton,MenuStatsButton,Copyrighted,
	MenuStartBuyButton,MenuStartLevel1Button,MenuStartXboxButton,MenuStartXboxLocked,Paused,UseYourKeyboard,
	HowToPlay0,HowToPlay1,HowToPlay2,HowToPlay3,HowToPlay4,HowToPlay5,HowToPlay6,
	Background,DeleteFlagButton,FlagButton,Floor,
	Player,MenuButton,Load1,Load2,Load3,Load4,Load5,Load6,Load7,Load8,Load9,Load10,
	Menu1,Menu2,Menu3,Menu4,Menu5,Menu6,Menu7,Menu8,Menu9,Menu10,
	Level1,Level2,Level3,Level4,Level5,Level6,Level7,Level8,Level9,Level10,
	Pause1,Pause2,Pause3,Pause4,Pause5,Pause6,Pause7,Pause8,Pause9,Pause10,
	Medal1,Medal2,Medal3,Medal4,Medal5,Medal6,
	Game1,Game2,Game3,Game4,Game5,Game6,Game7,Game8,Game9,Game10,
	Spike,Block,Pit,PitFirst,DeadImg,StopPractice, PracticeMode,Attempt,
	n[10],sn[10],Flag,VolumeState,Arrow,MedalUnlock;

void LoadingProc();
void MenuProc();
void LevelProc();
void PauseProc();
void HowToPlayProc();
void GamingProc();
void MedalProc();
void StatsProc();

void DrawLoading();
void DrawMenu();
void DrawLevel();
void DrawPause();
void DrawHowToPlay();
void DrawGaming();
void DrawMedal();
void DrawStats();

void Jump();
void Dead();
void Falling();



// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY201321047__5, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY201321047__5));

	// 기본 메시지 루프입니다.
	while (1)//메시지강
	{
		if( PeekMessage(&msg, NULL, 0, 0, 1) )
		{
			if(!TranslateAccelerator(msg.hwnd, NULL, &msg))
			{ TranslateMessage(&msg);
			DispatchMessage(&msg); }
			if( msg.message == WM_QUIT ) break;
		}
		DWORD curTime = GetTickCount();
		if( curTime-lastTime>32 ) // 30 frame per second!
		{
			lastTime = lastTime+33;
			//TimerProc();
			switch(GameStats){
			case 0: LoadingProc();break;
			case 1: MenuProc();break;
			case 2: LevelProc();break;
			case 3: PauseProc();break;
			case 4: HowToPlayProc();break;
			case 5: GamingProc();break;
			case 6: MedalProc();break;
			case 7: StatsProc();break;
			}
		}
	}

	return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY201321047__5));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY201321047__5);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	hWnd = CreateWindow(szWindowClass, szTitle,WS_POPUP,
		0, 10, 1136, 665, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		{
			display = eglGetDisplay( GetDC(hWnd));
			eglInitialize( display, NULL, NULL );
			eglBindAPI( EGL_OPENVG_API );
			EGLint conf_list[] = { EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_NONE };
			EGLConfig config;
			EGLint num_config;
			eglChooseConfig( display, conf_list, &config, 1, &num_config );
			surface = eglCreateWindowSurface( display, config, hWnd, NULL );
			context = eglCreateContext( display, 0, NULL, NULL );

			LoadingCount=0;
			GameStats=0;
			LevSelectpix=388;
			Default=vgLoadImage(TEXT("Images/Default-568h@2x.jpg"));
			BlackRect=vgLoadImage(TEXT("Images/blackrect-568h.jpg"));
			MenuStartFade=vgLoadImage(TEXT("Images/menustartfade-hd.png"));
			MenuBackGround=vgLoadImage(TEXT("Images/menubackground-hd.png"));
			MenuHowToPlayButton=vgLoadImage(TEXT("Images/menuhowtoplaybutton-hd.png"));
			MenuMedalsButton=vgLoadImage(TEXT("Images/menumedalsbutton-hd.png"));
			MenuStartButton=vgLoadImage(TEXT("Images/menustartbutton-hd.png"));
			MenuStatsButton=vgLoadImage(TEXT("Images/menustatsbutton-hd.jpg"));
			Copyrighted=vgLoadImage(TEXT("Images/copyrighted.png"));
			MenuStartBuyButton=vgLoadImage(TEXT("Images/menustartbuybutton-hd.jpg"));
			MenuStartLevel1Button=vgLoadImage(TEXT("Images/menustartlevel1button-hd.jpg"));
			MenuStartXboxButton=vgLoadImage(TEXT("Images/menustartxboxbutton-hd.jpg"));
			MenuStartXboxLocked=vgLoadImage(TEXT("Images/menustartxboxlocked-hd.png"));
			Paused=vgLoadImage(TEXT("Images/paused.jpg"));
			HowToPlay0=vgLoadImage(TEXT("Images/howtoplay0.jpg"));
			HowToPlay1=vgLoadImage(TEXT("Images/howtoplay1.jpg"));
			HowToPlay2=vgLoadImage(TEXT("Images/howtoplay2.jpg"));
			HowToPlay3=vgLoadImage(TEXT("Images/howtoplay3.jpg"));
			HowToPlay4=vgLoadImage(TEXT("Images/howtoplay4.jpg"));
			HowToPlay5=vgLoadImage(TEXT("Images/howtoplay5.jpg"));
			HowToPlay6=vgLoadImage(TEXT("Images/howtoplay6.jpg"));
			Background=vgLoadImage(TEXT("Images/background-568h.jpg"));
			DeleteFlagButton=vgLoadImage(TEXT("Images/deleteflagbutton-hd.png"));
			FlagButton=vgLoadImage(TEXT("Images/flagbutton-hd.png"));
			Floor=vgLoadImage(TEXT("Images/floor-hd.png"));
			Player=vgLoadImage(TEXT("Images/player-hd.png"));
			MenuButton=vgLoadImage(TEXT("Images/menubutton-hd.png"));
			UseYourKeyboard=vgLoadImage(TEXT("Images/useyourkeyboard.png"));
			Load1=vgLoadImage(TEXT("Images/Load1.jpg"));
			Load2=vgLoadImage(TEXT("Images/Load2.jpg"));
			Load3=vgLoadImage(TEXT("Images/Load3.jpg"));
			Load4=vgLoadImage(TEXT("Images/Load4.jpg"));
			Load5=vgLoadImage(TEXT("Images/Load5.jpg"));
			Load6=vgLoadImage(TEXT("Images/Load6.jpg"));
			Load7=vgLoadImage(TEXT("Images/Load7.jpg"));
			Load8=vgLoadImage(TEXT("Images/Load8.jpg"));
			Load9=vgLoadImage(TEXT("Images/Load9.jpg"));
			Load10=vgLoadImage(TEXT("Images/Load10.jpg"));
			Menu1=vgLoadImage(TEXT("Images/Menu1.jpg"));
			Menu2=vgLoadImage(TEXT("Images/Menu2.jpg"));
			Menu3=vgLoadImage(TEXT("Images/Menu3.jpg"));
			Menu4=vgLoadImage(TEXT("Images/Menu4.jpg"));
			Menu5=vgLoadImage(TEXT("Images/Menu5.jpg"));
			Menu6=vgLoadImage(TEXT("Images/Menu6.jpg"));
			Menu7=vgLoadImage(TEXT("Images/Menu7.jpg"));
			Menu8=vgLoadImage(TEXT("Images/Menu8.jpg"));
			Menu9=vgLoadImage(TEXT("Images/Menu9.jpg"));
			Menu10=vgLoadImage(TEXT("Images/Menu10.jpg"));
			Level1=vgLoadImage(TEXT("Images/Level1.jpg"));
			Level2=vgLoadImage(TEXT("Images/Level2.jpg"));
			Level3=vgLoadImage(TEXT("Images/Level3.jpg"));
			Level4=vgLoadImage(TEXT("Images/Level4.jpg"));
			Level5=vgLoadImage(TEXT("Images/Level5.jpg"));
			Level6=vgLoadImage(TEXT("Images/Level6.jpg"));
			Level7=vgLoadImage(TEXT("Images/Level7.jpg"));
			Level8=vgLoadImage(TEXT("Images/Level8.jpg"));
			Level9=vgLoadImage(TEXT("Images/Level9.jpg"));
			Level10=vgLoadImage(TEXT("Images/Level10.jpg"));
			Pause1=vgLoadImage(TEXT("Images/Pause1.jpg"));
			Pause2=vgLoadImage(TEXT("Images/Pause2.jpg"));
			Pause3=vgLoadImage(TEXT("Images/Pause3.jpg"));
			Pause4=vgLoadImage(TEXT("Images/Pause4.jpg"));
			Pause5=vgLoadImage(TEXT("Images/Pause5.jpg"));
			Pause6=vgLoadImage(TEXT("Images/Pause6.jpg"));
			Pause7=vgLoadImage(TEXT("Images/Pause7.jpg"));
			Pause8=vgLoadImage(TEXT("Images/Pause8.jpg"));
			Pause9=vgLoadImage(TEXT("Images/Pause9.jpg"));
			Pause10=vgLoadImage(TEXT("Images/Pause10.jpg"));
			Medal1=vgLoadImage(TEXT("Images/Medal1.jpg"));
			Medal2=vgLoadImage(TEXT("Images/Medal2.jpg"));
			Medal3=vgLoadImage(TEXT("Images/Medal3.jpg"));
			Medal4=vgLoadImage(TEXT("Images/Medal4.jpg"));
			Medal5=vgLoadImage(TEXT("Images/Medal5.jpg"));
			Medal6=vgLoadImage(TEXT("Images/Medal6.jpg"));
			Game1=vgLoadImage(TEXT("Images/Game1.jpg"));
			Game2=vgLoadImage(TEXT("Images/Game2.jpg"));
			Game3=vgLoadImage(TEXT("Images/Game3.jpg"));
			Game4=vgLoadImage(TEXT("Images/Game4.jpg"));
			Game5=vgLoadImage(TEXT("Images/Game5.jpg"));
			Game6=vgLoadImage(TEXT("Images/Game6.jpg"));
			Game7=vgLoadImage(TEXT("Images/Game7.jpg"));
			Game8=vgLoadImage(TEXT("Images/Game8.jpg"));
			Game9=vgLoadImage(TEXT("Images/Game9.jpg"));
			Game10=vgLoadImage(TEXT("Images/Game10.jpg"));
			Spike=vgLoadImage(TEXT("Images/spike-hd.png"));//초기화강
			Block=vgLoadImage(TEXT("Images/block-hd.png"));
			Pit=vgLoadImage(TEXT("Images/pit-hd.png"));
			PitFirst=vgLoadImage(TEXT("Images/pit-hd.png"));
			DeadImg=vgLoadImage(TEXT("Images/dead.PNG"));
			StopPractice=vgLoadImage(TEXT("Images/pausedexitpracticemodebutton-hd.png"));
			PracticeMode=vgLoadImage(TEXT("Images/practicemodeheader-hd.png"));
			Attempt=vgLoadImage(TEXT("Images/Attempt.PNG"));
			n[0]=vgLoadImage(TEXT("Images/0.png"));
			n[1]=vgLoadImage(TEXT("Images/1.png"));
			n[2]=vgLoadImage(TEXT("Images/2.png"));
			n[3]=vgLoadImage(TEXT("Images/3.png"));
			n[4]=vgLoadImage(TEXT("Images/4.png"));
			n[5]=vgLoadImage(TEXT("Images/5.png"));
			n[6]=vgLoadImage(TEXT("Images/6.png"));
			n[7]=vgLoadImage(TEXT("Images/7.png"));
			n[8]=vgLoadImage(TEXT("Images/8.png"));
			n[9]=vgLoadImage(TEXT("Images/9.png"));
			sn[0]=vgLoadImage(TEXT("Images/Small0.png"));
			sn[1]=vgLoadImage(TEXT("Images/Small1.png"));
			sn[2]=vgLoadImage(TEXT("Images/Small2.png"));
			sn[3]=vgLoadImage(TEXT("Images/Small3.png"));
			sn[4]=vgLoadImage(TEXT("Images/Small4.png"));
			sn[5]=vgLoadImage(TEXT("Images/Small5.png"));
			sn[6]=vgLoadImage(TEXT("Images/Small6.png"));
			sn[7]=vgLoadImage(TEXT("Images/Small7.png"));
			sn[8]=vgLoadImage(TEXT("Images/Small8.png"));
			sn[9]=vgLoadImage(TEXT("Images/Small9.png"));
			MedalUnlock=vgLoadImage(TEXT("Images/medalunlocked-hd.png.png"));
			
			Flag=vgLoadImage(TEXT("Images/flag-hd.png"));
			VolumeState=vgLoadImage(TEXT("Images/voiume.jpg"));
			Arrow=vgLoadImage(TEXT("Images/arrow.jpg"));

			/*for(int i=0; i<(HEIGHT/2);i++){					//WIDTH가 18일 때 17개 쓸 수 있음
			for(int j=0;j<WIDTH;j++){
			int temp=map[i][j];
			map[i][j]=map[(HEIGHT-i)][j];
			map[(HEIGHT-i-1)][j]=temp;
			}
			}*/
			sm = new CSoundManager();
			sm -> Initialize(hWnd,DSSCL_NORMAL);
			sm ->Create(&Boop,TEXT("Music/boop.wav"),0,GUID_NULL);
			sm ->Create(&Explosion,TEXT("Music/explosion.wav"),0,GUID_NULL);
			sm ->Create(&Fireworks,TEXT("Music/fireworks.wav"),0,GUID_NULL);
			sm ->Create(&Medal,TEXT("Music/medal.wav"),0,GUID_NULL);
			sm ->Create(&Menutrack,TEXT("Music/menutrack.wav"),0,GUID_NULL);
			sm ->Create(&Practicetrack,TEXT("Music/practicetrack.wav"),0,GUID_NULL);
			sm ->Create(&Soundtrack,TEXT("Music/soundtrack.wav"),0,GUID_NULL);
			
		}
		break;

	case WM_KEYDOWN://키다운강
		if(GameStats==2){
			if(RightAnimation==0&&LeftAnimation==0)
			{
				if( wParam==VK_RIGHT){
					if(LevSelectpix+Levelx>-432)RightAnimation=1;/*LevSelectpix-=410;*/
				}
				if( wParam==VK_LEFT){
					if(LevSelectpix+Levelx<388)LeftAnimation=1;/*LevSelectpix+=410;*/
				}
				if( wParam==VK_SPACE&&LevSelectpix+Levelx==388){

					LevelAnimation=1;
				}
			}
		}
		if( wParam==VK_ESCAPE){
			DestroyWindow(hWnd);
		}
		if( wParam==VK_RETURN){
			Explosion->Play(0);Dead();
		}
		break;
	case WM_LBUTTONDOWN:
		if(GameStats==0)break;
		Mousex=LOWORD(lParam);
		Mousey=HIWORD(lParam);
		Boop->Play(0);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void LoadingProc()//로딩프
{
	DrawLoading();
	LoadingCount+=1;

	if(LoadingCount>200){GameStats=1;LoadingMenuAnimation=1;LoadingCount=0;} 

}
void MenuProc()//메뉴프
{
	Menutrack->Play(0,1);
	if(Mousex>270&Mousex<685&Mousey>170&Mousey<375){

		GameStats=2;
		Mousex=0;
		Mousey=0;
	}
	if(Mousex>568&Mousex<859&Mousey>416&Mousey<530){

		GameStats=7;
		Mousex=0;
		Mousey=0;
	}
	if(Mousex>700&Mousex<858&Mousey>170&Mousey<375){

		GameStats=4;
		Mousex=0;
		Mousey=0;
	}
	if(Mousex>270&Mousex<556&Mousey>392&Mousey<505){

		GameStats=6;
		Mousex=0;
		Mousey=0;
	}
	if(LoadingMenuAnimation==1){LoadingMenuCount+=1;}
	if(LoadingMenuCount>19){LoadingMenuAnimation=0;LoadingMenuCount=-1;}
	DrawMenu();
}
void LevelProc()//레벨프
{
	DrawLevel();
	if(LevelAnimation==1){
		LevelCount+=1;
		if(LevelCount>19){GameStats=5;CameraX=0;LevelCount=-1;LevelAnimation=0;Soundtrack->Play(0);

		Menutrack->Stop();
		Menutrack->Reset();

		FILE *fp = fopen("map.txt","r");
		for(int i=0; i<HEIGHT;i++){
			for(int j=0; j<WIDTH; j++){
				fscanf(fp, "%c", &map[HEIGHT-i-1][j]);
				if(map[HEIGHT-i-1][j]=='P'){
					PlayerW[0]=HEIGHT-i-1;
					PlayerW[1]=j;
				}
			}
		}
		fclose(fp);
		}
	}
	if(RightAnimation==1){
		LevelNum++;
		Levelx-=410/10;
		if(LevelNum==10){RightAnimation=0;LevelNum=0;}

	}
	if(LeftAnimation==1){
		LevelNum++;
		Levelx+=410/10;
		if(LevelNum==10){LeftAnimation=0;LevelNum=0;}

	}
}
void PauseProc()//휴식프
{
	DrawPause();
	if(Mousex>200&Mousex<940&Mousey>172&Mousey<342){
		Soundtrack->Play(0);
		CameraCount=true;
		GameStats=5;
		Mousex=0;
		Mousey=0;
	}
	if(Mousex>580&Mousex<940&Mousey>358&Mousey<543){
		Soundtrack->Reset();
		Practicetrack->Reset();
		PracticeOn=0;
		PauseAnimation=1;
		if(PauseAnimation==1){
			PauseCount+=1;
			if(PauseCount>19){
				GameStats=1;
				Mousex=0;
				Mousey=0;
				PauseCount=-1;
				PauseAnimation=0;
			}
			LoadingMenuAnimation=1;
			GameCount=0;
			FILE *fp = fopen("map.txt","r");
			for(int i=0; i<HEIGHT;i++){
				for(int j=0; j<WIDTH; j++){
					fscanf(fp, "%c", &map[HEIGHT-i-1][j]);
					if(map[HEIGHT-i-1][j]=='P'){
						PlayerW[0]=HEIGHT-i-1;
						PlayerW[1]=j;
					}
				}
			}
			PracticeFlag=0;
			while(PracticeFlag>=100){
				PracticeFlag++;
				saved[(PracticeFlag-1)%100].Theta=0;
				saved[(PracticeFlag-1)%100].x=40;
				saved[(PracticeFlag-1)%100].fx=0;
				saved[(PracticeFlag-1)%100].Height=210;
				for(int i=0; i<HEIGHT;i++){
					for(int j=0; j<WIDTH;j++){
						saved[(PracticeFlag-1)%5].map[i][j]=map[i][j];
					}
				}
				saved[(PracticeFlag-1)%100].PlayerW[0]=PlayerW[0];
				saved[(PracticeFlag-1)%100].PlayerW[1]=PlayerW[1];
				saved[(PracticeFlag-1)%100].JumpAnimation=0;
				saved[(PracticeFlag-1)%100].CameraX=0;
				saved[(PracticeFlag-1)%100].i=0;
				saved[(PracticeFlag-1)%100].FallingFlag=0;
				saved[(PracticeFlag-1)%100].FlagX=300;
				saved[(PracticeFlag-1)%100].FlagY=210;
				Soundtrack->Stop();
				Mousex=0;
				Mousey=0;
				PracticeOn=1;

			}
			fclose(fp);
		}
	}
	if(PracticeOn==1){
		if(Mousex>198&Mousex<558&Mousey>358&Mousey<543){
			PracticeFlag=0;
			Soundtrack->Play(0);
			GameStats=5;
			Dead();
			Mousex=0;
			Mousey=0;
			PracticeOn=0;
		}
	}


}
void HowToPlayProc()//설명프
{
	DrawHowToPlay();
	if(Mousex>767&Mousex<898&Mousey>416&Mousey<486){
		HowToPlayCount+=1;
		Mousex=0;
		Mousey=0;
	}
	if(HowToPlayCount==7){
		HowToPlayCount=0;
		GameStats=1;
	}

}
void GamingProc()//게임프
{
	if(Deadcount==0){

		if(CameraCount==true)GameCount++;
		if(PracticeFlag==0)Soundtrack->Play(0);



		if(Mousex>371&Mousex<647&Mousey>484&Mousey<626){
			Practicetrack->Play(0,1);
			PracticeFlag++;
			saved[(PracticeFlag-1)%100].Theta=Theta;
			saved[(PracticeFlag-1)%100].x=x;
			saved[(PracticeFlag-1)%100].fx=fx;
			saved[(PracticeFlag-1)%100].Height=Height;
			for(int i=0; i<HEIGHT;i++){
				for(int j=0; j<WIDTH;j++){
					saved[(PracticeFlag-1)%5].map[i][j]=map[i][j];
				}
			}
			saved[(PracticeFlag-1)%100].PlayerW[0]=PlayerW[0];
			saved[(PracticeFlag-1)%100].PlayerW[1]=PlayerW[1];
			saved[(PracticeFlag-1)%100].JumpAnimation=JumpAnimation;
			saved[(PracticeFlag-1)%100].CameraX=CameraX;
			saved[(PracticeFlag-1)%100].i=i;
			saved[(PracticeFlag-1)%100].FallingFlag=FallingFlag;
			saved[(PracticeFlag-1)%100].FlagX=CameraX+300;
			saved[(PracticeFlag-1)%100].FlagY=Height;
			Soundtrack->Stop();
			Mousex=0;
			Mousey=0;
			PracticeOn=1;
		}
		if(PracticeFlag!=0){

			if(Mousex>647&Mousex<776&Mousey>484&Mousey<626){
				PracticeFlag--;
				Mousex=0;
				Mousey=0;
				if(PracticeFlag==0)PracticeFlag=1;
			}
		}




		if(Mousex>15&Mousex<137&Mousey>14&Mousey<87){
			GameStats=3;
			CameraCount=false;
			Soundtrack->Stop();
			Practicetrack->Stop();
			CameraX-=20;
			Mousex=0;
			Mousey=0;
		}
		CameraX+=20;
		if(CameraX%60==0){

			map[PlayerW[0]][PlayerW[1]++]=' ';
			if(map[PlayerW[0]][PlayerW[1]]=='A'){Explosion->Play(0);Dead();map[PlayerW[0]][--PlayerW[1]]='P';}
			else if(map[PlayerW[0]][PlayerW[1]]=='M'){Explosion->Play(0);Dead();map[PlayerW[0]][--PlayerW[1]]='P';}
			else if(map[PlayerW[0]][PlayerW[1]]=='X'){Explosion->Play(0);Dead();map[PlayerW[0]][--PlayerW[1]]='F';}
			else if(FallingFlag==false && JumpAnimation==0 && PlayerW[0]!=0 && map[PlayerW[0]-1][PlayerW[1]]==' '|| FallingFlag==false && JumpAnimation==0 &&map[PlayerW[0]-1][PlayerW[1]]=='F'){FallingFlag=true;}
			else{map[PlayerW[0]][PlayerW[1]]='P';}
		}
		if(FallingFlag==true)Falling();
		if(CameraX>WIDTH*60){
			CameraX=0;
		}
		int Temp=JumpAnimation;
		if(KEY_DOWN(VK_SPACE))	{if(FallingFlag==false)JumpAnimation=1;}
		if(JumpAnimation==1){ Jump();}

		if(Temp==0&&JumpAnimation==1)	JumpCount++;

		DrawGaming();
	}
	if(Deadcount!=0){
		Deadcount++;
		if(Deadcount==30){
			AttemptCount++;
			if(PracticeFlag==0){
				FallingFlag=false;
				Deadcount=0;
				JumpAnimation=0;		//애니메이션을 멈춘다.
				x=40;					//속도 초기값으로 바꾼다.
				Theta=0;	//각도 초기값
				Height=210;
				DeadFlag=false;
				CameraX=0;
				FILE *fp = fopen("map.txt","r");
				for(int i=0; i<HEIGHT;i++){
					for(int j=0; j<WIDTH; j++){
						fscanf(fp, "%c", &map[HEIGHT-i-1][j]);
						if(map[HEIGHT-i-1][j]=='P'){
							PlayerW[0]=HEIGHT-i-1;
							PlayerW[1]=j;
						}
					}
				}
				fclose(fp);
			}
			else
			{
				Theta=saved[(PracticeFlag-1)%100].Theta;
				x=saved[(PracticeFlag-1)%100].x;
				fx=saved[(PracticeFlag-1)%100].fx;
				Height=saved[(PracticeFlag-1)%100].Height;
				for(int i=0; i<HEIGHT;i++){
					for(int j=0; j<WIDTH;j++){
						map[i][j]=saved[(PracticeFlag-1)%5].map[i][j];
					}
				}
				PlayerW[0]=saved[(PracticeFlag-1)%100].PlayerW[0];
				PlayerW[1]=saved[(PracticeFlag-1)%100].PlayerW[1];
				JumpAnimation=saved[(PracticeFlag-1)%100].JumpAnimation;
				CameraX=saved[(PracticeFlag-1)%100].CameraX;
				i=saved[(PracticeFlag-1)%100].i;
				FallingFlag=saved[(PracticeFlag-1)%100].FallingFlag;
				DeadFlag=false;
				Deadcount=0;
			}
		}
	}
}
void MedalProc()//메달프
{

	DrawMedal();
	if(Mousex>660&Mousex<790&Mousey>473&Mousey<543){
		if(MedalCount<5) MedalCount+=1;//next 버튼
		Mousex=0;
		Mousey=0;
	}
	if(Mousex>503&Mousex<633&Mousey>473&Mousey<543){
		GameStats=1;
		MedalCount=0;
		Mousex=0;
		Mousey=0;
	}
	if(Mousex>348&Mousex<478&Mousey>473&Mousey<543){
		if(MedalCount>0) MedalCount-=1;
		Mousex=0;
		Mousey=0;
	}
	if(MedalCount==6){
		MedalCount=0;
		GameStats=1;
	}
}
void StatsProc()	//설정프
{
	if(Mousex>503&Mousex<633&Mousey>465&Mousey<555){
		GameStats=1;
		Mousex=0;
		Mousey=0;
	}
	DrawStats();
}


void DrawLoading()//로딩그
{
	eglMakeCurrent(display,surface,surface,context);
	float clearColor[4] = {0.5,0.4,0.4,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1300,1000);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);

	vgLoadIdentity(); 
	vgDrawImage( Default);
	switch(LoadingCount){
	case 200:	vgLoadIdentity(); vgDrawImage( Load1);break;
	case 199:	vgLoadIdentity(); vgDrawImage( Load1);break;
	case 198:	vgLoadIdentity(); vgDrawImage( Load2);break;
	case 197:	vgLoadIdentity(); vgDrawImage( Load2);break;
	case 196:	vgLoadIdentity(); vgDrawImage( Load3);break;
	case 195:	vgLoadIdentity(); vgDrawImage( Load3);break;
	case 194:	vgLoadIdentity(); vgDrawImage( Load4);break;
	case 193:	vgLoadIdentity(); vgDrawImage( Load4);break;
	case 192:	vgLoadIdentity(); vgDrawImage( Load5);break;
	case 191:	vgLoadIdentity(); vgDrawImage( Load5);break;
	case 190:	vgLoadIdentity(); vgDrawImage( Load6);break;
	case 189:	vgLoadIdentity(); vgDrawImage( Load6);break;
	case 188:	vgLoadIdentity(); vgDrawImage( Load7);break;
	case 187:	vgLoadIdentity(); vgDrawImage( Load7);break;
	case 186:	vgLoadIdentity(); vgDrawImage( Load8);break;
	case 185:	vgLoadIdentity(); vgDrawImage( Load8);break;
	case 184:	vgLoadIdentity(); vgDrawImage( Load9);break;
	case 183:	vgLoadIdentity(); vgDrawImage( Load9);break;
	case 182:	vgLoadIdentity(); vgDrawImage( Load10);break;
	case 181:	vgLoadIdentity(); vgDrawImage( Load10);break;

	}
	eglSwapBuffers(display,surface);
}
void DrawMenu()//메뉴그
{
	eglMakeCurrent(display,surface,surface,context);
	float clearColor[4] = {0.5,0.4,0.4,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1300,1000);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);
	vgLoadIdentity();
	vgDrawImage( BlackRect);

	vgLoadIdentity(); 
	vgTranslate(700,262);
	vgDrawImage( MenuHowToPlayButton);

	vgLoadIdentity(); 
	vgTranslate(568,135);
	vgDrawImage( MenuStatsButton);

	vgLoadIdentity(); 
	vgTranslate(270,262);
	vgDrawImage( MenuStartButton);

	vgLoadIdentity(); 
	vgTranslate(270,135);
	vgDrawImage( MenuMedalsButton);

	vgLoadIdentity(); 
	vgTranslate(-17,110);
	vgDrawImage( MenuStartFade);

	vgLoadIdentity(); 
	vgTranslate(234,10);
	vgDrawImage( Copyrighted);

	vgLoadIdentity();
	vgTranslate(160,110);
	vgDrawImage( MenuBackGround);

	switch(LoadingMenuCount){
	case 0:	vgLoadIdentity(); vgDrawImage( Menu1);break;
	case 1:	vgLoadIdentity(); vgDrawImage( Menu1);break;
	case 2:	vgLoadIdentity(); vgDrawImage( Menu2);break;
	case 3:	vgLoadIdentity(); vgDrawImage( Menu2);break;
	case 4:	vgLoadIdentity(); vgDrawImage( Menu3);break;
	case 5:	vgLoadIdentity(); vgDrawImage( Menu3);break;
	case 6:	vgLoadIdentity(); vgDrawImage( Menu4);break;
	case 7:	vgLoadIdentity(); vgDrawImage( Menu4);break;
	case 8:	vgLoadIdentity(); vgDrawImage( Menu5);break;
	case 9:	vgLoadIdentity(); vgDrawImage( Menu5);break;
	case 10:	vgLoadIdentity(); vgDrawImage( Menu6);break;
	case 11:	vgLoadIdentity(); vgDrawImage( Menu6);break;
	case 12:	vgLoadIdentity(); vgDrawImage( Menu7);break;
	case 13:	vgLoadIdentity(); vgDrawImage( Menu7);break;
	case 14:	vgLoadIdentity(); vgDrawImage( Menu8);break;
	case 15:	vgLoadIdentity(); vgDrawImage( Menu8);break;
	case 16:	vgLoadIdentity(); vgDrawImage( Menu9);break;
	case 17:	vgLoadIdentity(); vgDrawImage( Menu9);break;
	case 18:	vgLoadIdentity(); vgDrawImage( Menu10);break;
	case 19:	vgLoadIdentity(); vgDrawImage( Menu10);break;

	}
	eglSwapBuffers(display,surface);
}
void DrawLevel()//레벨그
{
	eglMakeCurrent(display,surface,surface,context);
	float clearColor[4] = {0.5,0.4,0.4,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1300,1000);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);

	vgLoadIdentity();
	vgDrawImage( BlackRect);


	vgLoadIdentity();
	vgTranslate(LevSelectpix+820+Levelx,130);
	vgDrawImage( MenuStartBuyButton);

	vgLoadIdentity();
	vgTranslate(LevSelectpix+410+Levelx,130);
	vgDrawImage( MenuStartXboxButton);

	if(BreakLevel==false){
		vgLoadIdentity();
		vgTranslate(LevSelectpix+410+Levelx,130);
		vgDrawImage( MenuStartXboxLocked);
	}

	vgLoadIdentity();
	vgTranslate(LevSelectpix+Levelx,130);
	vgDrawImage(MenuStartLevel1Button);

	vgLoadIdentity(); 
	vgTranslate(-17,110);
	vgDrawImage( MenuStartFade);

	vgLoadIdentity(); 
	vgTranslate(234,10);
	vgDrawImage( Copyrighted);

	vgLoadIdentity();
	vgTranslate(160,110);
	vgDrawImage( MenuBackGround);

	vgLoadIdentity();
	vgTranslate(428,490);
	vgDrawImage( UseYourKeyboard);


	switch(LevelCount){
	case 0:	vgLoadIdentity(); vgDrawImage( Level10);break;
	case 1:	vgLoadIdentity(); vgDrawImage( Level10);break;
	case 2:	vgLoadIdentity(); vgDrawImage( Level9);break;
	case 3:	vgLoadIdentity(); vgDrawImage( Level9);break;
	case 4:	vgLoadIdentity(); vgDrawImage( Level8);break;
	case 5:	vgLoadIdentity(); vgDrawImage( Level8);break;
	case 6:	vgLoadIdentity(); vgDrawImage( Level7);break;
	case 7:	vgLoadIdentity(); vgDrawImage( Level7);break;
	case 8:	vgLoadIdentity(); vgDrawImage( Level6);break;
	case 9:	vgLoadIdentity(); vgDrawImage( Level6);break;
	case 10:	vgLoadIdentity(); vgDrawImage( Level5);break;
	case 11:	vgLoadIdentity(); vgDrawImage( Level5);break;
	case 12:	vgLoadIdentity(); vgDrawImage( Level4);break;
	case 13:	vgLoadIdentity(); vgDrawImage( Level4);break;
	case 14:	vgLoadIdentity(); vgDrawImage( Level3);break;
	case 15:	vgLoadIdentity(); vgDrawImage( Level3);break;
	case 16:	vgLoadIdentity(); vgDrawImage( Level2);break;
	case 17:	vgLoadIdentity(); vgDrawImage( Level2);break;
	case 18:	vgLoadIdentity(); vgDrawImage( Level1);break;
	case 19:	vgLoadIdentity(); vgDrawImage( Level1);break;
	}
	eglSwapBuffers(display,surface);
}
void DrawPause()//휴식그
{
	eglMakeCurrent(display,surface,surface,context);
	float clearColor[4] = {0.5,0.4,0.4,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1300,1000);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);

	vgLoadIdentity();
	vgDrawImage( Paused);
	switch(PauseCount){
	case 0:	vgLoadIdentity(); vgDrawImage( Pause10);break;
	case 1:	vgLoadIdentity(); vgDrawImage( Pause10);break;
	case 2:	vgLoadIdentity(); vgDrawImage( Pause9);break;
	case 3:	vgLoadIdentity(); vgDrawImage( Pause9);break;
	case 4:	vgLoadIdentity(); vgDrawImage( Pause8);break;
	case 5:	vgLoadIdentity(); vgDrawImage( Pause8);break;
	case 6:	vgLoadIdentity(); vgDrawImage( Pause7);break;
	case 7:	vgLoadIdentity(); vgDrawImage( Pause7);break;
	case 8:	vgLoadIdentity(); vgDrawImage( Pause6);break;
	case 9:	vgLoadIdentity(); vgDrawImage( Pause6);break;
	case 10:	vgLoadIdentity(); vgDrawImage( Pause5);break;
	case 11:	vgLoadIdentity(); vgDrawImage( Pause5);break;
	case 12:	vgLoadIdentity(); vgDrawImage( Pause4);break;
	case 13:	vgLoadIdentity(); vgDrawImage( Pause4);break;
	case 14:	vgLoadIdentity(); vgDrawImage( Pause3);break;
	case 15:	vgLoadIdentity(); vgDrawImage( Pause3);break;
	case 16:	vgLoadIdentity(); vgDrawImage( Pause2);break;
	case 17:	vgLoadIdentity(); vgDrawImage( Pause2);break;
	case 18:	vgLoadIdentity(); vgDrawImage( Pause1);break;
	case 19:	vgLoadIdentity(); vgDrawImage( Pause1);break;

	}
	if(PracticeOn==1){
		vgLoadIdentity();	
		vgTranslate(198,97);
		vgDrawImage(StopPractice);
	}

	eglSwapBuffers(display,surface);
}
void DrawHowToPlay()//설명그
{
	eglMakeCurrent(display,surface,surface,context);
	float clearColor[4] = {0.5,0.4,0.4,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1300,1000);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);

	switch(HowToPlayCount){
	case 0:vgLoadIdentity(); vgDrawImage(HowToPlay0);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 1:vgLoadIdentity(); vgDrawImage(HowToPlay1);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 2:vgLoadIdentity(); vgDrawImage(HowToPlay2);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 3:vgLoadIdentity(); vgDrawImage(HowToPlay3);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 4:vgLoadIdentity(); vgDrawImage(HowToPlay4);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 5:vgLoadIdentity(); vgDrawImage(HowToPlay5);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 6:vgLoadIdentity(); vgDrawImage(HowToPlay6);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;

	}


	vgLoadIdentity(); 
	vgTranslate(234,10);
	vgDrawImage( Copyrighted);

	eglSwapBuffers(display,surface);
}
void DrawGaming()
{
	eglMakeCurrent(display,surface,surface,context);
	float clearColor[4] = {0.5,0.4,0.4,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1300,1000);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);

	int Hundred=AttemptCount/100;
	int Ten=AttemptCount%100/10;
	int	One=AttemptCount%10;

	vgLoadIdentity();
	vgDrawImage( Background);

	vgLoadIdentity();
	vgTranslate(185,210);
	vgDrawImage( Floor);

	vgLoadIdentity();
	vgTranslate(15,553);
	vgDrawImage(MenuButton);

	vgLoadIdentity();
	vgTranslate(644,15);
	vgDrawImage(DeleteFlagButton);

	vgLoadIdentity();
	vgTranslate(370,15);
	vgDrawImage(FlagButton);

	switch(GameCount){
	case 1:	vgLoadIdentity(); vgDrawImage( Game1);break;
	case 2:	vgLoadIdentity(); vgDrawImage( Game1);break;
	case 3:	vgLoadIdentity(); vgDrawImage( Game2);break;
	case 4:	vgLoadIdentity(); vgDrawImage( Game2);break;
	case 5:	vgLoadIdentity(); vgDrawImage( Game3);break;
	case 6:	vgLoadIdentity(); vgDrawImage( Game3);break;
	case 7:	vgLoadIdentity(); vgDrawImage( Game4);break;
	case 8:	vgLoadIdentity(); vgDrawImage( Game4);break;
	case 9:	vgLoadIdentity(); vgDrawImage( Game5);break;
	case 10:	vgLoadIdentity(); vgDrawImage( Game5);break;
	case 11:	vgLoadIdentity(); vgDrawImage( Game6);break;
	case 12:	vgLoadIdentity(); vgDrawImage( Game6);break;
	case 13:	vgLoadIdentity(); vgDrawImage( Game7);break;
	case 14:	vgLoadIdentity(); vgDrawImage( Game7);break;
	case 15:	vgLoadIdentity(); vgDrawImage( Game8);break;
	case 16:	vgLoadIdentity(); vgDrawImage( Game8);break;
	case 17:	vgLoadIdentity(); vgDrawImage( Game9);break;
	case 18:	vgLoadIdentity(); vgDrawImage( Game9);break;
	case 19:	vgLoadIdentity(); vgDrawImage( Game10);break;
	case 20:	vgLoadIdentity(); vgDrawImage( Game10);break;

	}//게임그
	for(int i=0;i<HEIGHT;i++){
		for(int j=CameraX/60;j<CameraX/60+20;j++){
			vgLoadIdentity();
			vgTranslate(j*60-CameraX,i*60+210);
			switch(map[i][j])
			{
			case 'M': vgDrawImage(Block);break;
			case 'A': vgDrawImage(Spike);break;
			case 'X': vgDrawImage(Pit);break;
			case 'F': vgDrawImage(PitFirst);break;
			case 'P': vgTranslate(CameraX%60,Height-i*60-210); 	
				vgTranslate(30,30);
				vgRotate(Theta);
				vgTranslate(-30,-30); 	
				if(DeadFlag==false) vgDrawImage(Player);
				if(DeadFlag==true)vgDrawImage(DeadImg);break;
			default :break;
			}
			if(CameraX==40000)MedalOn=true;
			if(CameraX>=39600){Fireworks->Play(0);}
			if(CameraX>=40260){ 
				GameStats=1; BreakLevel=true;
				Practicetrack->Stop();
				Practicetrack->Reset();
				Soundtrack->Stop();
				Soundtrack->Reset();
				FILE *fp = fopen("map.txt","r");
				for(int i=0; i<HEIGHT;i++){
					for(int j=0; j<WIDTH; j++){
						fscanf(fp, "%c", &map[HEIGHT-i-1][j]);
						if(map[HEIGHT-i-1][j]=='P'){
							PlayerW[0]=HEIGHT-i-1;
							PlayerW[1]=j;
						}
					}
				}
				PracticeFlag=0;
				while(PracticeFlag>=100){
					PracticeFlag++;
					saved[(PracticeFlag-1)%100].Theta=0;
					saved[(PracticeFlag-1)%100].x=40;
					saved[(PracticeFlag-1)%100].fx=0;
					saved[(PracticeFlag-1)%100].Height=210;
					for(int i=0; i<HEIGHT;i++){
						for(int j=0; j<WIDTH;j++){
							saved[(PracticeFlag-1)%5].map[i][j]=map[i][j];
						}
					}
					saved[(PracticeFlag-1)%100].PlayerW[0]=PlayerW[0];
					saved[(PracticeFlag-1)%100].PlayerW[1]=PlayerW[1];
					saved[(PracticeFlag-1)%100].JumpAnimation=0;
					saved[(PracticeFlag-1)%100].CameraX=0;
					saved[(PracticeFlag-1)%100].i=0;
					saved[(PracticeFlag-1)%100].FallingFlag=0;
					saved[(PracticeFlag-1)%100].FlagX=300;
					saved[(PracticeFlag-1)%100].FlagY=210;
					Soundtrack->Stop();
					Mousex=0;
					Mousey=0;
				}
				PracticeOn=0;
				MedalOn=0;
				fclose(fp);
			}
		}
	}

	if(PracticeOn==1){
		for(int i=0;i<PracticeFlag;++i){
			vgLoadIdentity();
			vgTranslate(saved[i].FlagX-CameraX,saved[i].FlagY);
			vgDrawImage(Flag);
		}
	}
	if(PracticeOn==1){
		vgLoadIdentity();
		vgTranslate(790,550);
		vgDrawImage(PracticeMode);
	}
	vgLoadIdentity();
	vgTranslate(409,565);
	vgDrawImage(Attempt);
	if(MedalOn==true){
		vgLoadIdentity();
		vgTranslate(370,300);
		vgDrawImage(MedalUnlock);
	}
	vgLoadIdentity();
	vgTranslate(627,575);
	vgDrawImage(n[Hundred]);
	vgLoadIdentity();
	vgTranslate(662,575);
	vgDrawImage(n[Ten]);
	vgLoadIdentity();
	vgTranslate(697,575);
	vgDrawImage(n[One]);
	eglSwapBuffers(display,surface);
}
void DrawMedal()//메달그
{
	eglMakeCurrent(display,surface,surface,context);
	float clearColor[4] = {0.5,0.4,0.4,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1300,1000);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);

	switch(MedalCount){
	case 0:vgLoadIdentity(); vgDrawImage(Medal1);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 1:vgLoadIdentity(); vgDrawImage(Medal2);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 2:vgLoadIdentity(); vgDrawImage(Medal3);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 3:vgLoadIdentity(); vgDrawImage(Medal4);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 4:vgLoadIdentity(); vgDrawImage(Medal5);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;
	case 5:vgLoadIdentity(); vgDrawImage(Medal6);vgLoadIdentity();vgTranslate(160,110);vgDrawImage( MenuBackGround);break;

	}


	vgLoadIdentity(); 
	vgTranslate(234,10);
	vgDrawImage( Copyrighted);
	eglSwapBuffers(display,surface);
}
void DrawStats()	//설정그
{
	eglMakeCurrent(display,surface,surface,context);
	float clearColor[4] = {0.5,0.4,0.4,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1300,1000);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);
	int Thousand=AttemptCount/1000;
	int Hundred=AttemptCount/100;
	int Ten=AttemptCount%100/10;
	int	One=AttemptCount%10;

	int Thousand2=JumpCount/1000;
	int Hundred2=JumpCount%1000/100;
	int Ten2=JumpCount%100/10;
	int	One2=JumpCount%10;

	vgLoadIdentity(); 
	vgDrawImage( VolumeState);

	vgLoadIdentity();
	vgTranslate(367+10,300);
	vgDrawImage(sn[Thousand2]);
	vgLoadIdentity();
	vgTranslate(379+10,300);
	vgDrawImage(sn[Hundred2]);
	vgLoadIdentity();
	vgTranslate(391+10,300);
	vgDrawImage(sn[Ten2]);
	vgLoadIdentity();
	vgTranslate(403+10,300);
	vgDrawImage(sn[One2]);

	vgLoadIdentity();
	vgTranslate(688+10,300);
	vgDrawImage(sn[Thousand]);
	vgLoadIdentity();
	vgTranslate(700+10,300);
	vgDrawImage(sn[Hundred]);
	vgLoadIdentity();
	vgTranslate(712+10,300);
	vgDrawImage(sn[Ten]);
	vgLoadIdentity();
	vgTranslate(724+10,300);
	vgDrawImage(sn[One]);

	eglSwapBuffers(display,surface);
}
void Jump()//점프
{

	Height+=x;
	x-=8;  
	Theta-=20;
	map[PlayerW[0]][PlayerW[1]]=' ';//그 전칸 지움
	PlayerW[0]=(Height-210)/60;		//뛴 곳에 따른 위치 배열값을 y좌표로 둠

	if(map[PlayerW[0]][PlayerW[1]]=='A'){Explosion->Play(0);map[PlayerW[0]+1][PlayerW[1]]='P';Dead();return;}
	if(map[PlayerW[0]][PlayerW[1]]=='X'){Explosion->Play(0);map[PlayerW[0]+1][PlayerW[1]]='P';Dead();return;}
	if(map[PlayerW[0]][PlayerW[1]]=='M' || (CameraX%60==40 && map[PlayerW[0]][PlayerW[1]+1]=='M')){ //
		if(x>0){Explosion->Play(0); Dead();}

		if(x<=0){			//내려가는 도중이면
			++PlayerW[0];		//Player의 높이좌표를 +1해준다.
			map[PlayerW[0]][PlayerW[1]]='P'; //그 높이에 그린다.
			JumpAnimation=0;		//애니메이션을 멈춘다.
			x=40;					//속도 초기값으로 바꾼다.
			Theta=0;			//각도 초기값
			Height=210+PlayerW[0]*60;	//움직이는 애
		}
		return;
	}



	if(PlayerW[0]>=0){
		map[PlayerW[0]][PlayerW[1]]='P';
	}
	if(Height<=210){
		Height=210;
		PlayerW[0]=(Height-210)/60;
		map[PlayerW[0]][PlayerW[1]]='P';
		JumpAnimation=0;
		x=40;
		Theta=0;
	}

}	
void Dead()
{
	DeadFlag=true;
	Deadcount++;
	Soundtrack->Stop();
	Soundtrack->Reset();

}
void Falling()
{
	Height-=fx;
	fx+=8;	
	Theta-=20;
	map[PlayerW[0]][PlayerW[1]]=' ';//그 전칸 지움
	PlayerW[0]=(Height-210)/60;		//뛴 곳에 따른 위치 배열값
	if(map[PlayerW[0]][PlayerW[1]]=='A'){Explosion->Play(0);map[PlayerW[0]+1][PlayerW[1]]='P';Dead();return;}
	if(map[PlayerW[0]][PlayerW[1]]=='X'){Explosion->Play(0);map[PlayerW[0]+1][PlayerW[1]]='P';Dead();return;}
	if(map[PlayerW[0]][PlayerW[1]]=='M' || (CameraX%60==40 && map[PlayerW[0]][PlayerW[1]+1]=='M')){ //`
		++PlayerW[0];		//Player의 높이좌표를 +1해준다.
		map[PlayerW[0]][PlayerW[1]]='P'; //그 높이에 그린다.
		FallingFlag=false;		//애니메이션을 멈춘다.
		fx=0;					//속도 초기값으로 바꾼다.
		Theta=0;			//각도 초기값
		Height=210+PlayerW[0]*60;	//움직이는 애
		return;
	}



	if(PlayerW[0]>=0){
		map[PlayerW[0]][PlayerW[1]]='P';
	}
	if(Height<=210){
		Height=210;
		PlayerW[0]=(Height-210)/60;
		map[PlayerW[0]][PlayerW[1]]='P';
		FallingFlag=false;
		fx=0;
		Theta=0;
	}
}
/*
Height+=x;
x-=8;  
Theta-=20;
if(Height<=210){
JumpAnimation=0;
x=40;
Theta=0;
}*/