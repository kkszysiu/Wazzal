// Stars.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "resource.h"
#include "Stars.h"

int numkuvia=6;
int number_of_samples=12;

const int objnum0=16; //obj1 
const int objnum1=27; //obj2 - asteroids
const int objnum2=15; //ships
float asteroid_radius=27;
float master_volume=0.85f;


#define MAX_LOADSTRING 100
#define RELEASE(x) {if (x) {(x)->Release(); (x)=NULL;}}
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define sqr(x)				((x)*(x))
static const float pi = 3.1415926535897932384626433832795f;
inline DWORD FtoDW( FLOAT f ) { return *((DWORD*)&f); }
#define SAFEDELETEARRAY(x) if (x) { delete[] x; x = NULL; x; }
#define WM_GRAPHNOTIFY  WM_APP + 1


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
HWND hWnd;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hInstNULL, LPSTR lpszCmdLine, int nCmdShow){	
	startApplication(hInstance);	
}

void startApplication(HINSTANCE hInstance){
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BIKEZ2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, 1)) 
	{
		return;
	}

	init();
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_BIKEZ2);
/*
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}*/

	
BOOL bGotMsg;    
//MSG  msg;
	m_LastTime = GetTickCount(); //alusta ajastin
	bool g_bReady=true;  
	bool g_bActive=true;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	while( WM_QUIT != msg.message  )    
	{
        // Use PeekMessage() if the app is active, so we can use idle time to
        // render the scene. Else, use GetMessage() to avoid eating CPU time.
        if( g_bActive )
            bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
        else
            bGotMsg = GetMessage( &msg, NULL, 0U, 0U );
		if( bGotMsg )
        {                
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }        
		else        
		{
            // Render a frame during idle time (no messages are waiting)
            if( g_bActive && g_bReady )
			{   


				luekeyb();				
				//exit game
				if(end_game)SendMessage( hWnd, WM_CLOSE, 0, 0 );
				if(!quittaos)
				{
					HRESULT hr;
					// Test the cooperative level to see if it's okay to render
					hr = m_pDevice->TestCooperativeLevel();
					if(hr==D3DERR_DEVICELOST){
						//shut down music
						if(music_initialized)g_pMediaControl->Stop();
					}
					if(hr==D3DERR_DEVICENOTRESET){
						clean_display();
						if(SUCCEEDED(m_pDevice->Reset(&m_d3dpp))){
							restore_display();
						}
						//start music
						if(music_initialized)g_pMediaControl->Run();
					}
					if(hr==D3D_OK){
						Render();
						m_pDevice->Present(NULL,NULL,NULL,NULL);
						//store mouse info for next frame						
						mouse_button_was_0=mouse_button_0;
						mouse_button_was_1=mouse_button_1;
					}
				}
			}
        }    
	}
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_ICON4);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= (LPCSTR)IDC_BIKEZ2;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON4);

	mouse_cursor=LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	//mouse_cursor=(HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   //HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
	RECT rDesktop;
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &rDesktop, NULL);
   hWnd = CreateWindow(szWindowClass, szTitle, WS_EX_TOPMOST,
      (rDesktop.left+rDesktop.right)/2-512, (rDesktop.top+rDesktop.bottom)/2-384, 1024, 768, NULL, NULL, hInstance, NULL);
		//(rDesktop.left+rDesktop.right)/2-50, (rDesktop.top+rDesktop.bottom)/2-50, (rDesktop.left+rDesktop.right)/2+50, (rDesktop.top+rDesktop.bottom)/2+50, NULL, NULL, hInstance, NULL);
   //CreateWindowEx(0, m_szAppName, m_szAppTitle, WS_OVERLAPPEDWINDOW, //& ~WS_THICKFRAME,
   //     160, rDesktop.bottom - 150, 300, 150, NULL, NULL, m_hInstance, NULL);
    /*hWnd = CreateWindow(szWindowClass, szTitle, WS_EX_TOPMOST,//WS_EX_TOPMOST WS_OVERLAPPEDWINDOW
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);*/

   if (!hWnd)
   {
      return FALSE;
   }

   

   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);



   PAINTSTRUCT ps;
    RECT rc;

    BeginPaint(hWnd, &ps);
    HDC hdc = GetDC(hWnd);
    GetWindowRect(hWnd, &rc);
    
    // Set the text color to bright green against black background
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkColor(hdc, RGB(255,255,255));

    // Decide where to place the text (centered in window)
    int X = (rc.right - rc.left) / 2;
    int Y = (rc.bottom - rc.top-45) / 2;
    SetTextAlign(hdc, TA_CENTER | VTA_CENTER);

	//ExtTextOut(hdc, 5, 1, ETO_OPAQUE, NULL, "Loading...", 10, NULL);
	ExtTextOut(hdc,
	       X, Y,
	       ETO_OPAQUE | ETO_CLIPPED,
	       NULL,
	       "Loading...",
	       10,
	       NULL);

    EndPaint(hWnd, &ps);


   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;
	//TCHAR szHello[MAX_LOADSTRING];
	//LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{	
		case WM_GRAPHNOTIFY:
			if(music_initialized)
            if(FAILED(HandleGraphEvent()))music_initialized=false;
            break;
		case WM_ACTIVATE:
			{
				if (g_pMouse)
					{
					g_pMouse->Acquire();
					}
				if (g_lpDIDevice)
					{
					g_lpDIDevice->Acquire();
					}
			}
			break;
		case WM_LBUTTONDOWN:
			{
				mouse_button_0=true;
			}
			break;
		case WM_LBUTTONUP:
			{
				mouse_button_0=false;
			}
			break;
		case WM_RBUTTONDOWN:
			{
				mouse_button_1=true;
			}
			break;
		case WM_RBUTTONUP:
			{
				mouse_button_1=false;
			}
			break;
		/*case WM_SETCURSOR:
            // Turn off Windows cursor in fullscreen mode
            {
                SetCursor( NULL );
                    m_pDevice->ShowCursor( FALSE );
                return TRUE; // prevent Windows from setting cursor to window class cursor
            }
            break;*/
		/*case WM_CHAR:	//näppäimistön luku nimen ottoa varten		
			{
				if(pelivaihe==7)
				if(pelivaihe2==0)
				if(keytimer<0){
					keytimer=25;

				switch (wParam) {                  
                case 0x0A:break;  // linefeed  
                case 0x1B:break;  // escape  
                case 0x09:break;  // tab  
                case 0x0D:break;  // carriage return 
                 
				case 0x08:  // backspace 				
					kirjaintanimessa=kirjaintanimessa-1;
					if(kirjaintanimessa<0)kirjaintanimessa=0;					
					savenimi[kirjaintanimessa]=NULL;
				break;
                default:
					char che=(char)wParam;
					savenimi[kirjaintanimessa]=che;					
					kirjaintanimessa=kirjaintanimessa+1;
					if(kirjaintanimessa>49)kirjaintanimessa=49;
				}
				}
			}
			break;*/
		case WM_DESTROY:
			CleanUp();
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

//ohjelman alustus
void init(void)
{
	end_game=false;
	help_screen=false;
	int q;
	
	start_timer=0;
	keytimer=0;
	suntimer=0;
	planet_visit_timer=0;
	warp_timer=0;
	game_started=false;	
	pelinopeus=1.0f;
	aspect=(4.0f/3.0f);

	//particles
	for (q=0; q<maximum_particles; q++){
		particle[q].dead=true;
	}

	
	//randomgeneraattori(en löytäny käskyä)	
	for (q=0; q<(int)GetTickCount()/100; q++){		
		rand();
	}

	

	menu_return_pelivaihe=-1;
	menu_return_pelivaihe2=-1;

	
	strcpy(options_text[0],"Nebula visible");
	strcpy(options_text[1],"Stars visible");
	strcpy(options_text[2],"High poly ships");
	strcpy(options_text[3],"Game start demo");
	strcpy(options_text[4],"Easy Mode");
	strcpy(options_text[5],"Sound");
	strcpy(options_text[6],"Music");
	strcpy(options_text[7],"Change keys");
	strcpy(options_text[8],"Particles visible");

	
	//alustaa 3d:n	
	ShowCursor(false);	
	SetCursor(NULL);
	LoadCursor(NULL, IDC_ARROW);
	initkeyb();
	createscreen();
	
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00FFFFFF, 0, 0 );
	m_pDevice->Present(NULL,NULL,NULL,NULL);
	
	m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);	
	m_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);//D3DCULL_CCW
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	//ensin linear filter
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFLINEAR)
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTEXF_LINEAR);	
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MINFLINEAR)
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTEXF_LINEAR);			
	//sitten anistropic filter
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFANISOTROPIC)		
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTEXF_ANISOTROPIC);	
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MINFANISOTROPIC)
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTEXF_ANISOTROPIC);		
	//point size
	point_size=1;
	if(deviceCaps.MaxPointSize>1)		
		point_size=4;
	

	m_pDevice->SetTextureStageState(0,D3DTSS_MAXANISOTROPY,2);
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSU,D3DTADDRESS_MIRROR ); 
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSV,D3DTADDRESS_MIRROR ); 
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSW,D3DTADDRESS_MIRROR );	
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	
	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, 
                                   D3DTTFF_COUNT2 //| D3DTTFF_PROJECTED 
								   );	
	m_pDevice->SetRenderState( D3DRS_LIGHTING,TRUE);	
	//ladataan tekstuurit
	lataatext();
	//alustetaan matriisi	
	ZeroMemory(&matriisi, sizeof(matriisi));
	D3DXCreateMatrixStack(  0, &matriisi);
	valota(0,0,0);
	//taustakuva
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00FFFFFF, 0, 0 );
	kirjota(1,-1,-1,-1,10,10,0,"Loading...");
	m_pDevice->Present(NULL,NULL,NULL,NULL);
	
	luekuvat();
	cfg_load();

	//music
	music_initialized=false;
	if(options[6])
	if(GraphInit()==S_OK)music_initialized=true;
	
	for (q=0; q<10; q++){option_rotate[q]=0;if(options[q])option_rotate[q]=pi;}
	for (q=0; q<10; q++)option_rotate_speed[q]=0;

	//sound
	g_pSoundManager = new CSoundManager();
	sound_init();
	


	
	//D3DXInitialize();

	
	//aspect=(float)((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT);
	plusmiinus=0;



	// Initialize and set the matrices
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
								  &D3DXVECTOR3( 0.0f, 0.0f, 1.0f ),
								  &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	D3DXMatrixPerspectiveFovLH( &matProj, pi/4, aspect, 1.0f, 100.0f );
	
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	m_pDevice->SetTransform( D3DTS_VIEW, &matView );

	// Set the render states
	//m_pDevice->SetRenderState(D3DRS_ANTIALIAS,D3DANTIALIAS_SORTDEPENDENT );//ota DDSCAPS2_HINTANTIALIASING pois jos poistat		
	
/*	//sumut
	if((desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGVERTEX)&&(!(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGRANGE)))
		SetupVertexFog(maxvisible-5000,maxvisible,0x004C4C4C, D3DFOG_LINEAR  , FALSE, 0);//sumu
	if((desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGVERTEX)&&(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGRANGE))
		SetupVertexFog(maxvisible-5000,maxvisible,0x004C4C4C, D3DFOG_LINEAR  , TRUE, 0);//sumu
*/
	/*if(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGTABLE)
		SetupPixelFog(0x004C4C4C, D3DFOG_LINEAR);*/

 /*
	m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);	
	m_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);//D3DCULL_CCW
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	//ensin linear filter
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFLINEAR)
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTEXF_LINEAR);	
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MINFLINEAR)
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTEXF_LINEAR);			
	//sitten anistropic filter
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFANISOTROPIC)		
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTEXF_ANISOTROPIC);	
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MINFANISOTROPIC)
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTEXF_ANISOTROPIC);		
	m_pDevice->SetTextureStageState(0,D3DTSS_MAXANISOTROPY,2);
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSU,D3DTADDRESS_MIRROR ); 
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSV,D3DTADDRESS_MIRROR ); 
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSW,D3DTADDRESS_MIRROR );	
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	
	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, 
                                   D3DTTFF_COUNT2 //| D3DTTFF_PROJECTED 
								   );*/
		

	//keskitä hiiri
	mousex=(float)(SCREEN_WIDTH/2);
	mousey=(float)(SCREEN_HEIGHT/2);
	
	DDCOLORKEY color;	
	color.dwColorSpaceHighValue=0x000000;//CLR_INVALID on ylänurkka
	color.dwColorSpaceLowValue=0x000000;

	//tausta[15]->SetColorKey(DDCKEY_SRCBLT,&color);

	//ladataan objektit //muista lisätä mallit[n]
	mallit[0].malli= new obj[objnum0];	
	mallit[1].malli= new obj[objnum1];
	mallit[2].malli= new obj[objnum2];/*
	mallit[3].malli= new obj[objnum3];
	mallit[4].malli= new obj[objnum4];
	mallit[5].malli= new obj[objnum5];
	mallit[6].malli= new obj[objnum6];
	mallit[7].malli= new obj[objnum7];
	mallit[8].malli= new obj[objnum8];
	mallit[9].malli= new obj[objnum9];
	mallit[10].malli= new obj[objnum10];*/
	lataa("models/obj1.3dw",	mallit[0].malli,	false,	false);
	lataa("models/obj2.3dw",	mallit[1].malli,	false,	false);
	lataa("models/ships.3dw",	mallit[2].malli,	false,	false);
	/*lataa("models/ukko0.3dw",	mallit[3].malli,	false,	false);
	lataa("models/ukko1.3dw",	mallit[4].malli,	false,	false);
	lataa("models/ukko2.3dw",	mallit[5].malli,	false,	false);
	lataa("models/obj3.3dw",	mallit[6].malli,	false,	false);
	lataa("models/ukko3.3dw",	mallit[7].malli,	false,	false);
	lataa("models/ukko4.3dw",	mallit[8].malli,	false,	false);
	lataa("models/obj4.3dw",	mallit[9].malli,	false,	false);
	lataa("models/ukko5.3dw",	mallit[10].malli,	false,	false);*/

/*
	moveparts(3);//siirtää ukko0 osat paikalleen
	moveparts(4);//siirtää ukko1 osat paikalleen
	moveparts(5);//siirtää ukko1 osat paikalleen
*/

	SetWindowLong( hWnd, GWL_STYLE, WS_MAXIMIZE|WS_VISIBLE|WS_POPUP );
	ShowCursor(false);	
	SetCursor(NULL);
	m_pDevice->ShowCursor(FALSE);
	cursor_shown=false;
	D3DUtil_SetDeviceCursor(m_pDevice,mouse_cursor);
	mouse_button_0=false;
	

	elapsed=15;
	for (q=0; q<100; q++){
		elapsed3[q]=15;
	}



	


	int d;

	d=0;
	strcpy(ship_base[d].classname,"unidentified flying object");
	ship_base[d].mass=3.0f*600000;
	ship_base[d].picture=0;
	ship_base[d].size=65;	
	ship_base[d].ship_type=0;
	ship_base[d].motordistance[0]=95;//front motor
	ship_base[d].motordistance[1]=96;//side motors
	ship_base[d].motorangle[1]=0.4f;//side motors
	ship_base[d].motorangle[2]=0.00f;//back motor0
	ship_base[d].motordistance[2]=-125;//back motor0
	ship_base[d].backmotors=1;
	ship_base[d].gun[0]=2;//phasor
	ship_base[d].number_of_guns[0]=1;
	ship_base[d].gunangle[0][0]=0;
	ship_base[d].gundistance[0][0]=00;
	ship_base[d].gun[1]=1;//bigger missile
	ship_base[d].number_of_guns[1]=2;
	ship_base[d].gunangle[1][0]=0.87f;
	ship_base[d].gundistance[1][0]=103;
	ship_base[d].gunangle[1][1]=-0.87f;
	ship_base[d].gundistance[1][1]=103;
	ship_base[d].motordownpower=4.0f;
	ship_base[d].motoruppower=5.7f;
	ship_base[d].motorleftpower=0.98f;
	ship_base[d].motorrightpower=0.98f;
	ship_base[d].threat=4;
	ship_base[d].base_energy=130;
	ship_base[d].base_heat=100;


	d=1;
	strcpy(ship_base[d].classname,"nebula");
	ship_base[d].mass=1.4f*600000;
	ship_base[d].picture=1;
	ship_base[d].size=40;	
	ship_base[d].ship_type=1;
	ship_base[d].motordistance[0]=145;//front motor
	ship_base[d].motordistance[1]=88;//side motors
	ship_base[d].motorangle[1]=0.27f;//side motors
	ship_base[d].motorangle[2]=0.0f;//back motor0
	ship_base[d].motordistance[2]=-60;//back motor0
	ship_base[d].backmotors=1;
	ship_base[d].gun[0]=4;//big gun
	ship_base[d].number_of_guns[0]=1;
	ship_base[d].gunangle[0][0]=0;
	ship_base[d].gundistance[0][0]=145;
	ship_base[d].gun[1]=6;//backward missiles
	ship_base[d].number_of_guns[1]=2;
	ship_base[d].gunangle[1][0]=1.75f;
	ship_base[d].gundistance[1][0]=54;
	ship_base[d].gunangle[1][0]=-1.75f;
	ship_base[d].gundistance[1][0]=54;
	ship_base[d].motordownpower=3.0f;
	ship_base[d].motoruppower=1.7f;
	ship_base[d].motorleftpower=0.77f;
	ship_base[d].motorrightpower=0.77f;
	ship_base[d].threat=3;
	ship_base[d].base_energy=50;
	ship_base[d].base_heat=100;

	d=2;
	strcpy(ship_base[d].classname,"star streak");
	ship_base[d].mass=1.6f*600000;
	ship_base[d].picture=2;
	ship_base[d].size=50;	
	ship_base[d].ship_type=2;
	ship_base[d].motordistance[0]=10;//front motor
	ship_base[d].motordistance[1]=88;//side motors
	ship_base[d].motorangle[1]=0.45f;//side motors
	ship_base[d].motorangle[2]=0.8f;//back motor0
	ship_base[d].motordistance[2]=-80;//back motor0
	ship_base[d].motorangle[3]=-0.8f;//back motor1
	ship_base[d].motordistance[3]=-80;//back motor1
	ship_base[d].backmotors=2;
	ship_base[d].gun[0]=0;//minigun
	ship_base[d].number_of_guns[0]=2;
	ship_base[d].gunangle[0][0]=0.37f;
	ship_base[d].gundistance[0][0]=115;
	ship_base[d].gunangle[0][1]=-0.37f;
	ship_base[d].gundistance[0][1]=115;
	ship_base[d].gun[1]=9;//smaller phasor
	ship_base[d].number_of_guns[1]=1;
	ship_base[d].gunangle[1][0]=0;
	ship_base[d].gundistance[1][0]=16;
	ship_base[d].motordownpower=3.0f;
	ship_base[d].motoruppower=1.7f;
	ship_base[d].motorleftpower=0.81f;
	ship_base[d].motorrightpower=0.81f;
	ship_base[d].threat=1.5f;
	ship_base[d].base_energy=90;
	ship_base[d].base_heat=60;

	d=3;
	strcpy(ship_base[d].classname,"blue tiger");
	ship_base[d].mass=1.6f*600000;
	ship_base[d].picture=3;
	ship_base[d].size=50;	
	ship_base[d].ship_type=3;
	ship_base[d].motordistance[0]=104;//front motor
	ship_base[d].motordistance[1]=65;//side motors
	ship_base[d].motorangle[1]=0.977f;//side motors
	ship_base[d].motorangle[2]=0.489f;//back motor0
	ship_base[d].motordistance[2]=-112;//back motor0
	ship_base[d].motorangle[3]=-0.489f;//back motor1
	ship_base[d].motordistance[3]=-112;//back motor1
	ship_base[d].motorangle[4]=0;//back motor2
	ship_base[d].motordistance[4]=-40;//back motor2
	ship_base[d].backmotors=3;
	ship_base[d].gun[0]=5;//asteroid gun
	ship_base[d].number_of_guns[0]=1;
	ship_base[d].gunangle[0][0]=0;
	ship_base[d].gundistance[0][0]=104;
	ship_base[d].gun[1]=3;//smaller missile
	ship_base[d].number_of_guns[1]=2;
	ship_base[d].gunangle[1][0]=0.977f;
	ship_base[d].gundistance[1][0]=65;
	ship_base[d].gunangle[1][1]=-0.977f;
	ship_base[d].gundistance[1][1]=65;
	ship_base[d].motordownpower=6.0f;
	ship_base[d].motoruppower=6.0f;
	ship_base[d].motorleftpower=0.9f;
	ship_base[d].motorrightpower=0.9f;
	ship_base[d].threat=3;
	ship_base[d].base_energy=110;
	ship_base[d].base_heat=100;

	d=4;
	strcpy(ship_base[d].classname,"terrible treble");
	ship_base[d].mass=2.6f*600000;
	ship_base[d].picture=4;
	ship_base[d].size=60;	
	ship_base[d].ship_type=4;
	ship_base[d].motordistance[0]=79;//front motor
	ship_base[d].motordistance[1]=157;//side motors
	ship_base[d].motorangle[1]=1.99f;//side motors
	ship_base[d].motorangle[2]=0;//back motor0
	ship_base[d].motordistance[2]=-79;//back motor0
	ship_base[d].backmotors=1;
	ship_base[d].gun[0]=8;//flamer
	ship_base[d].number_of_guns[0]=1;
	ship_base[d].gunangle[0][0]=0;
	ship_base[d].gundistance[0][0]=79;
	ship_base[d].gun[1]=7;//spike
	ship_base[d].number_of_guns[1]=2;
	ship_base[d].gunangle[1][0]=1.17f;
	ship_base[d].gundistance[1][0]=75;
	ship_base[d].gunangle[1][1]=-1.17f;
	ship_base[d].gundistance[1][1]=75;
	ship_base[d].motordownpower=50.0f;
	ship_base[d].motoruppower=50.0f;
	ship_base[d].motorleftpower=1.41f;
	ship_base[d].motorrightpower=1.41f;
	ship_base[d].threat=2;
	ship_base[d].base_energy=110;
	ship_base[d].base_heat=200;

	d=5;
	strcpy(ship_base[d].classname,"cargo vessel");
	ship_base[d].mass=3.6f*600000;
	ship_base[d].picture=13;
	ship_base[d].size=95;	
	ship_base[d].ship_type=5;
	ship_base[d].motordistance[0]=0;//front motor
	ship_base[d].motordistance[1]=90;//side motors
	ship_base[d].motorangle[1]=1.69f;//side motors
	ship_base[d].motorangle[2]=0.0f;//back motor0
	ship_base[d].motordistance[2]=-147;//back motor0
	ship_base[d].motorangle[3]=1.87f;//back motor1
	ship_base[d].motordistance[3]=79;//back motor1
	ship_base[d].motorangle[4]=-1.87f;//back motor2
	ship_base[d].motordistance[4]=79;//back motor2
	ship_base[d].backmotors=3;
	ship_base[d].gun[0]=7;//spike
	ship_base[d].number_of_guns[0]=1;
	ship_base[d].gunangle[0][0]=0;
	ship_base[d].gundistance[0][0]=0;
	ship_base[d].gun[1]=0;//minigun
	ship_base[d].number_of_guns[1]=2;
	ship_base[d].gunangle[1][0]=0.58f;
	ship_base[d].gundistance[1][0]=110;
	ship_base[d].gunangle[1][1]=-0.58f;
	ship_base[d].gundistance[1][1]=110;
	ship_base[d].motordownpower=3.0f;
	ship_base[d].motoruppower=1.7f;
	ship_base[d].motorleftpower=0.81f;
	ship_base[d].motorrightpower=0.81f;
	ship_base[d].threat=1;
	ship_base[d].base_energy=100;
	ship_base[d].base_heat=40;

	d=6;
	strcpy(ship_base[d].classname,"space station");
	ship_base[d].mass=30.6f*600000;
	ship_base[d].picture=12;
	ship_base[d].size=205;	
	ship_base[d].ship_type=6;
	ship_base[d].motordistance[0]=0;//front motor
	ship_base[d].motordistance[1]=90;//side motors
	ship_base[d].motorangle[1]=1.69f;//side motors
	ship_base[d].motorangle[2]=0.0f;//back motor0
	ship_base[d].motordistance[2]=147;//back motor0
	ship_base[d].motorangle[3]=2.094f;//back motor1
	ship_base[d].motordistance[3]=147;//back motor1
	ship_base[d].motorangle[4]=2*2.094f;//back motor2
	ship_base[d].motordistance[4]=147;//back motor2
	ship_base[d].backmotors=3;
	ship_base[d].gun[0]=1;//bigger missile
	ship_base[d].number_of_guns[0]=4;
	ship_base[d].gunangle[0][0]=0;
	ship_base[d].gundistance[0][0]=0;
	ship_base[d].gunangle[0][1]=0;
	ship_base[d].gundistance[0][1]=0;
	ship_base[d].gunangle[0][2]=0;
	ship_base[d].gundistance[0][2]=0;
	ship_base[d].gunangle[0][3]=0;
	ship_base[d].gundistance[0][3]=0;
	ship_base[d].gun[1]=2;//phasor
	ship_base[d].number_of_guns[1]=4;
	ship_base[d].gunangle[1][0]=0;
	ship_base[d].gundistance[1][0]=0;
	ship_base[d].gunangle[1][1]=0;
	ship_base[d].gundistance[1][1]=0;
	ship_base[d].gunangle[1][2]=0;
	ship_base[d].gundistance[1][2]=0;
	ship_base[d].gunangle[1][3]=0;
	ship_base[d].gundistance[1][3]=0;
	ship_base[d].motordownpower=0.001f;
	ship_base[d].motoruppower=0.001f;
	ship_base[d].motorleftpower=100.81f;
	ship_base[d].motorrightpower=100.81f;
	ship_base[d].threat=5;
	ship_base[d].base_energy=9000;
	ship_base[d].base_heat=1000;

	d=7;
	strcpy(ship_base[d].classname,"laser drill");
	ship_base[d].mass=4.0f*600000;
	ship_base[d].picture=5;
	ship_base[d].size=95;	
	ship_base[d].ship_type=7;
	ship_base[d].motordistance[0]=0;//front motor
	ship_base[d].motordistance[1]=90;//side motors
	ship_base[d].motorangle[1]=1.69f;//side motors
	ship_base[d].motorangle[2]=0.0f;//back motor0
	ship_base[d].motordistance[2]=-147;//back motor0
	ship_base[d].motorangle[3]=1.87f;//back motor1
	ship_base[d].motordistance[3]=79;//back motor1
	ship_base[d].motorangle[4]=-1.87f;//back motor2
	ship_base[d].motordistance[4]=79;//back motor2
	ship_base[d].backmotors=3;
	ship_base[d].gun[0]=10;//laser
	ship_base[d].number_of_guns[0]=1;
	ship_base[d].gunangle[0][0]=0;
	ship_base[d].gundistance[0][0]=82;
	ship_base[d].gun[1]=0;//minigun
	ship_base[d].number_of_guns[1]=2;
	ship_base[d].gunangle[1][0]=0.58f;
	ship_base[d].gundistance[1][0]=110;
	ship_base[d].gunangle[1][1]=-0.58f;
	ship_base[d].gundistance[1][1]=110;
	ship_base[d].motordownpower=3.0f;
	ship_base[d].motoruppower=1.7f;
	ship_base[d].motorleftpower=1.31f;
	ship_base[d].motorrightpower=1.31f;
	ship_base[d].threat=4;
	ship_base[d].base_energy=250;
	ship_base[d].base_heat=5000;

	
	

	//weapons
	q=0;//minigun
	weapon[q].bulletpicture=0;
	weapon[q].bulletspeed=3;
	weapon[q].bullettype=0;
	weapon[q].damage=1;
	weapon[q].firerate=70;
	weapon[q].collision_explosion=0;
	weapon[q].collision_smoke=0;
	weapon[q].movement_smoke=0;
	weapon[q].tracking=false;
	weapon[q].powerdownrate=0;
	weapon[q].sound_launch=3;
	weapon[q].sound_hit=8;
	weapon[q].heat=0.75f;

	q=1;//bigger missile
	weapon[q].bulletpicture=0;
	weapon[q].bulletspeed=2;
	weapon[q].bullettype=0;
	weapon[q].damage=5;
	weapon[q].firerate=500;
	weapon[q].collision_explosion=2;
	weapon[q].collision_smoke=2;
	weapon[q].movement_smoke=10;
	weapon[q].tracking=true;
	weapon[q].powerdownrate=0.0f;
	weapon[q].sound_launch=1;
	weapon[q].sound_hit=7;
	weapon[q].heat=5.0f;

	q=2;//phasor
	weapon[q].bulletpicture=1;
	weapon[q].bulletspeed=3;
	weapon[q].bullettype=0;
	weapon[q].damage=20;
	weapon[q].firerate=500;
	weapon[q].collision_explosion=2;
	weapon[q].collision_smoke=2;
	weapon[q].movement_smoke=0;
	weapon[q].tracking=false;
	weapon[q].powerdownrate=0.0003f;
	weapon[q].sound_launch=9;
	weapon[q].sound_hit=4;
	weapon[q].heat=10.0f;

	q=3;//smaller missile
	weapon[q].bulletpicture=4;
	weapon[q].bulletspeed=2;
	weapon[q].bullettype=0;
	weapon[q].damage=1;
	weapon[q].firerate=300;
	weapon[q].collision_explosion=1;
	weapon[q].collision_smoke=1;
	weapon[q].movement_smoke=10;
	weapon[q].tracking=true;
	weapon[q].powerdownrate=0.0f;
	weapon[q].sound_launch=1;
	weapon[q].sound_hit=10;
	weapon[q].heat=4.0f;

	q=4;//big gun
	weapon[q].bulletpicture=3;
	weapon[q].bulletspeed=5;
	weapon[q].bullettype=0;
	weapon[q].damage=25;
	weapon[q].firerate=400;
	weapon[q].collision_explosion=2;
	weapon[q].collision_smoke=2;
	weapon[q].movement_smoke=0;
	weapon[q].tracking=false;
	weapon[q].powerdownrate=0;
	weapon[q].sound_launch=2;
	weapon[q].sound_hit=10;
	weapon[q].heat=10.0f;

	q=5;//asteroid gun
	weapon[q].bulletpicture=2;
	weapon[q].bulletspeed=2;
	weapon[q].bullettype=0;
	weapon[q].damage=30;
	weapon[q].firerate=500;
	weapon[q].collision_explosion=2;
	weapon[q].collision_smoke=2;
	weapon[q].movement_smoke=0;
	weapon[q].tracking=false;
	weapon[q].powerdownrate=0;
	weapon[q].sound_launch=6;
	weapon[q].sound_hit=11;
	weapon[q].heat=10.0f;

	q=6;//backward missiles
	weapon[q].bulletpicture=0;
	weapon[q].bulletspeed=-2;
	weapon[q].bullettype=0;
	weapon[q].damage=10;
	weapon[q].firerate=300;
	weapon[q].collision_explosion=1;
	weapon[q].collision_smoke=1;
	weapon[q].movement_smoke=0;
	weapon[q].tracking=true;
	weapon[q].powerdownrate=0.0f;
	weapon[q].sound_launch=1;
	weapon[q].sound_hit=7;
	weapon[q].heat=3.0f;

	q=7;//spike
	weapon[q].bulletpicture=5;
	weapon[q].bulletspeed=5;
	weapon[q].bullettype=0;
	weapon[q].damage=10;
	weapon[q].firerate=600;
	weapon[q].collision_explosion=2;
	weapon[q].collision_smoke=2;
	weapon[q].movement_smoke=10;
	weapon[q].tracking=false;
	weapon[q].powerdownrate=0;
	weapon[q].sound_launch=1;
	weapon[q].sound_hit=11;
	weapon[q].heat=10.0f;

	q=8;//flamer
	weapon[q].bulletpicture=4;
	weapon[q].bulletspeed=3;
	weapon[q].bullettype=0;
	weapon[q].damage=6;
	weapon[q].firerate=30;
	weapon[q].collision_explosion=0;
	weapon[q].collision_smoke=0;
	weapon[q].movement_smoke=0;
	weapon[q].tracking=false;
	weapon[q].powerdownrate=0.006f;
	weapon[q].sound_launch=1;
	weapon[q].sound_hit=3;
	weapon[q].heat=0.75f;

	q=9;//smaller phasor
	weapon[q].bulletpicture=4;
	weapon[q].bulletspeed=2;
	weapon[q].bullettype=0;
	weapon[q].damage=2;
	weapon[q].firerate=300;
	weapon[q].collision_explosion=1;
	weapon[q].collision_smoke=1;
	weapon[q].movement_smoke=10;
	weapon[q].tracking=false;
	weapon[q].powerdownrate=0.0f;
	weapon[q].sound_launch=5;
	weapon[q].sound_hit=4;
	weapon[q].heat=2.0f;

	q=10;//laser
	weapon[q].bulletpicture=4;
	weapon[q].bulletspeed=5;
	weapon[q].bullettype=0;
	weapon[q].damage=5;
	weapon[q].firerate=20;
	weapon[q].collision_explosion=2;
	weapon[q].collision_smoke=2;
	weapon[q].movement_smoke=10;
	weapon[q].tracking=false;
	weapon[q].powerdownrate=0;
	weapon[q].sound_launch=5;
	weapon[q].sound_hit=3;
	weapon[q].heat=3.0f;


	



	//random names for ships
	strcpy(randomname[0],"Falcon");
	strcpy(randomname[1],"Black Baza");
	strcpy(randomname[2],"Honeyguide");
	strcpy(randomname[3],"Gesneria");
	strcpy(randomname[4],"Discrepancy");
	strcpy(randomname[5],"Hallowed");
	strcpy(randomname[6],"Skin Beetle");
	strcpy(randomname[7],"Hadada Ibis");
	strcpy(randomname[8],"Gean");
	strcpy(randomname[9],"Halitosis");
	strcpy(randomname[10],"Capped Heron");
	strcpy(randomname[11],"Carriage");
	strcpy(randomname[12],"Camel");
	strcpy(randomname[13],"Radix");
	strcpy(randomname[14],"Raider");
	strcpy(randomname[15],"Drongo");
	strcpy(randomname[16],"Tuatara");
	strcpy(randomname[17],"Spoonbill");
	strcpy(randomname[18],"Passerina Amoena");
	randomnames=19;

	//random names random missions
	strcpy(random_mission_name[0],"General Duende");
	strcpy(random_mission_name[1],"Jack the Wicked");
	strcpy(random_mission_name[2],"Mom");
	strcpy(random_mission_name[3],"Eric the Red");
	strcpy(random_mission_name[4],"Powerman");
	strcpy(random_mission_name[5],"Seth");
	strcpy(random_mission_name[6],"Big Tulath");
	strcpy(random_mission_name[7],"Nerda");
	strcpy(random_mission_name[8],"Galadriel");
	strcpy(random_mission_name[9],"Spadefoot");
	random_mission_names=10;

	if(options[3]){
		//demo
		pelivaihe=8;
		pelivaihe2=0;
	}
	else{
		//menu
		pelivaihe=7;
		pelivaihe2=5;
	}
	luesavet();
}

BOOL lataa(char nimi[200],obj *kohde,BOOL mirror,BOOL miekkakala)
{

	

	FILE *fil;
	//INT faces;
	INT kolme,kolmi;
	FLOAT x[2000];
	FLOAT y[2000];
	FLOAT z[2000];
	FLOAT x1[2000];
	FLOAT y1[2000];
	FLOAT z1[2000];
	FLOAT u[2000];
	FLOAT v[2000];
	FLOAT w[2000];

	vvertex vertex[2000];

	//INT peili;
	//if (mirror) peili=-1; else peili=1;

	FLOAT groupx,groupy,groupz;
	//float g[3];
	//CHAR kuvat[300];
	
	INT sivu0[2000];
	INT sivu1[2000];
	INT sivu2[2000];
	INT sivu20[2000];
	INT sivu21[2000];
	INT sivu22[2000];
	D3DVECTOR p1;
	D3DVECTOR vNormal;
	INT cur=0;
	INT cura=0;
	//int lootia;
	//INT kolmion;

	INT i,j,b,a,q,faces;
	fil = fopen(nimi,"rt");


	//kohde = new objekt[lootia];

	
	fgets(rivi,sizeof(rivi),fil); 	
	j=atoi(rivi);
	//lataaapu(j,&kohde);
	//*kohde	= new obj[j];
	

	for (b=0; b<j; b++)
	{
		fgets(rivi,sizeof(rivi),fil); 	
		a=atoi(rivi);

		fgets(rivi,sizeof(rivi),fil);
		groupx=(float)atof(rivi);
		fgets(rivi,sizeof(rivi),fil);
		groupy=(float)atof(rivi);
		fgets(rivi,sizeof(rivi),fil);
		groupz=(float)atof(rivi);
		
//tässä välissä lataillaan miekan kärki
/*
		if (miekkakala)
			{
			fgets(rivi,sizeof(rivi),fil);
			kohde[b].swordpointx=(float)atof(rivi)-groupx;
			fgets(rivi,sizeof(rivi),fil);
			kohde[b].swordpointy=(float)atof(rivi)-groupy;
			fgets(rivi,sizeof(rivi),fil);
			kohde[b].swordpointz=(float)atof(rivi)-groupz;
			}
*/
		kohde[b].mirror=mirror;
		kohde[b].sisus = new objekt[a];
		kohde[b].count = a;

		for (q=0; q<a; q++)
		{


		fgets(rivi,sizeof(rivi),fil);//666666
		fgets(rivi,sizeof(rivi),fil);//matskut
			kohde[b].sisus[q].matsku=atoi(rivi);
		fgets(rivi,sizeof(rivi),fil);//matskut toiseen kertaan

			{

				fgets(rivi,sizeof(rivi),fil);
				 //new(INT faces=atoi(rivi));
				kolme=atoi(rivi);
				fgets(rivi,sizeof(rivi),fil);	
				faces=atoi(rivi);
				//D3DVERTEX kolmijako[faces*3];
				//FLOAT new( x[kolme]);
				//x=new(FLOAT[kolme]);
				//kohde[b].sisus[q].loota.kolmijako = new LPDIRECT3DVERTEXBUFFER8[kohde[b].count];
				kohde[b].sisus[q].loota.vert = faces*3;

				kohde[b].upleft.x=NULL;
				kohde[b].upleft.y=NULL;
				kohde[b].upleft.z=NULL;
				
				kohde[b].downright.x=NULL;
				kohde[b].downright.y=NULL;
				kohde[b].downright.z=NULL;

				for (i=0; i<kolme; i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					x[i]=(((float)atof(rivi))-groupx);
					fgets(rivi,sizeof(rivi),fil);
					y[i]=(((float)atof(rivi))-groupy);
					fgets(rivi,sizeof(rivi),fil);
					z[i]=(((float)atof(rivi))-groupz);//*peili


					//dimensiot
					if(x[i]<kohde[b].upleft.x) kohde[b].upleft.x=x[i];
					if(y[i]<kohde[b].upleft.y) kohde[b].upleft.y=y[i];
					if(z[i]<kohde[b].upleft.z) kohde[b].upleft.z=z[i];
					if(x[i]>kohde[b].downright.x) kohde[b].downright.x=x[i];
					if(y[i]>kohde[b].downright.y) kohde[b].downright.y=y[i];
					if(z[i]>kohde[b].downright.z) kohde[b].downright.z=z[i];
				}
				
				for (i=0; i<faces; i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					sivu0[i]=atoi(rivi);
					fgets(rivi,sizeof(rivi),fil);
					sivu1[i]=atoi(rivi);
					fgets(rivi,sizeof(rivi),fil);
					sivu2[i]=atoi(rivi);
				
					
					
				}

				fgets(rivi,sizeof(rivi),fil);
				kolmi=atoi(rivi);
				
				for (i=0; i<kolmi; i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					u[i]=(float)atof(rivi);
					fgets(rivi,sizeof(rivi),fil);
					v[i]=1.0f-(float)atof(rivi);
					fgets(rivi,sizeof(rivi),fil);
					w[i]=(float)atof(rivi);
				}
				
				fgets(rivi,sizeof(rivi),fil);
				kolmi=atoi(rivi);
				for (i=0; i<kolmi; i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					sivu20[i]=atoi(rivi);
					fgets(rivi,sizeof(rivi),fil);
					sivu21[i]=atoi(rivi);
					fgets(rivi,sizeof(rivi),fil);
					sivu22[i]=atoi(rivi);	
				}
				for (i=0; i<(3*faces); i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					x1[i]=((float)atof(rivi));
					fgets(rivi,sizeof(rivi),fil);
					y1[i]=((float)atof(rivi));
					fgets(rivi,sizeof(rivi),fil);
					z1[i]=((float)atof(rivi));//*peili
					/*fgets(rivi,sizeof(rivi),fil);
					x1[i]=randDouble(-1,1);
					fgets(rivi,sizeof(rivi),fil);
					y1[i]=randDouble(-1,1);
					fgets(rivi,sizeof(rivi),fil);
					z1[i]=randDouble(-1,1);*/
				}
			
				for (i=0; i<faces; i++)
				{
					p1.x=x[sivu0[i]];     
					p1.y=y[sivu0[i]];     
					p1.z=z[sivu0[i]];
					vNormal.x=x1[sivu0[i]];
					vNormal.y=y1[sivu0[i]];
					vNormal.z=z1[sivu0[i]]; 
					vertex[i*3+0].position=		p1; 
					vertex[i*3+0].normal=		vNormal;
					vertex[i*3+0].u=			u[sivu20[i]];//w[sivu20[i]];
					vertex[i*3+0].v=			v[sivu20[i]];//w[sivu20[i]];
					
					
				
					p1.x=x[sivu1[i]];     
					p1.y=y[sivu1[i]];     
					p1.z=z[sivu1[i]];
					vNormal.x=x1[sivu1[i]];
					vNormal.y=y1[sivu1[i]];
					vNormal.z=z1[sivu1[i]];
					vertex[i*3+1].position=		p1; 
					vertex[i*3+1].normal=		vNormal;
					vertex[i*3+1].u=			u[sivu21[i]];//w[sivu21[i]];
					vertex[i*3+1].v=			v[sivu21[i]];//w[sivu21[i]];
					
					
				
					p1.x=x[sivu2[i]];     
					p1.y=y[sivu2[i]];     
					p1.z=z[sivu2[i]];
					vNormal.x=x1[sivu2[i]];
					vNormal.y=y1[sivu2[i]];
					vNormal.z=z1[sivu2[i]];
					vertex[i*3+2].position=		p1; 
					vertex[i*3+2].normal=		vNormal;
					vertex[i*3+2].u=			u[sivu22[i]];//w[sivu22[i]];
					vertex[i*3+2].v=			v[sivu22[i]];//w[sivu22[i]];
					
					
				}	
				

				fgets(rivi,sizeof(rivi),fil);
				kohde[b].sisus[q].textuuri=atoi(rivi);
				kohde[b].sisus[q].textuuri2=atoi(rivi);
				kohde[b].sisus[q].x=0.0f;
				kohde[b].sisus[q].y=0.0f;
				kohde[b].sisus[q].z=0.0f;
				kohde[b].x=0.0f;
				kohde[b].y=0.0f;
				kohde[b].z=0.0f;
				kohde[b].rx=0.0f;
				kohde[b].ry=0.0f;
				kohde[b].rz=0.0f;

				m_pDevice->CreateVertexBuffer( kohde[b].sisus[q].loota.vert*sizeof(vvertex),
                                                  D3DUSAGE_WRITEONLY  , D3DFVF_WVERTEX,
                                                  D3DPOOL_DEFAULT, &kohde[b].sisus[q].loota.kolmijako );
				VOID* pVertices;
				kohde[b].sisus[q].loota.kolmijako->Lock( 0, 0, (BYTE**)&pVertices, 0 );					
				memcpy( pVertices, vertex, kohde[b].sisus[q].loota.vert*sizeof(vvertex) );
				kohde[b].sisus[q].loota.kolmijako->Unlock();
			}
		}
	}


	fclose(fil);

	return true;

}



BOOL lataatext()
{

	FILE *fil;
	CHAR rivit[13];
	CHAR texturenimi[100];
	DWORD x=100;
	DWORD y=100;
	DWORD mipmaps=D3DX_DEFAULT;
	DWORD mipmapping=D3DX_DEFAULT;
	int q;
	fil = fopen("models/mat.3dw","rt");

	fgets(rivi,sizeof(rivi),fil);
	materiaa=atoi(rivi);	
	mat = new D3DMATERIAL8[materiaa];
	tausta = new LPDIRECT3DTEXTURE8[materiaa];
	bool filter[300];//josko suodatetaan vai ei

	for (q=0; q<materiaa; q++)
		filter[q]=false;
/*
	//yleisöä ei suodateta
	filter[49]=true;
	filter[50]=true;
*/

	/*for (q=materiaa; q<materiaa+40; q++)
	{
		
		D3DXCreateTexture(
		m_pDevice,
		NULL,
		&x,
		&y,
		NULL,
		NULL,
		&tausta[q],
		NULL
		);

	}*/

	for (q=0; q<materiaa; q++)
	{
		ZeroMemory( &tausta[q], sizeof(tausta[q]) );
		ZeroMemory( &mat[q], sizeof(mat[q]) );
		 
		// Set the RGBA for ambient reflection. 
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Ambient.r = (D3DVALUE)atof(rivi);     
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Ambient.g = (D3DVALUE)atof(rivi); 
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Ambient.b = (D3DVALUE)atof(rivi);     
		mat[q].Ambient.a = (D3DVALUE)1.0;  
		
		// Set the RGBA for diffuse reflection.
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Diffuse.r = (D3DVALUE)atof(rivi);
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Diffuse.g = (D3DVALUE)atof(rivi);     
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Diffuse.b = (D3DVALUE)atof(rivi); 
		mat[q].Diffuse.a = (D3DVALUE)1.0; 

		// Set the color and sharpness of specular highlights. 
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Specular.r = (D3DVALUE)atof(rivi);     
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Specular.g = (D3DVALUE)atof(rivi); 
		fgets(rivi,sizeof(rivi),fil);
		mat[q].Specular.b = (D3DVALUE)atof(rivi); 
		mat[q].Specular.a = (D3DVALUE)1.0; 
		
				
		// Set the RGBA for emissive color.
		mat[q].Emissive.r = 0.0f;
		mat[q].Emissive.g = 0.0f;
		mat[q].Emissive.b = 0.0f;
		mat[q].Emissive.a = 0.0f;
		mat[q].Power = 20;

		fgets(rivit,sizeof(rivit),fil);
		fgets(rivi,sizeof(rivi),fil);

		//itoa(tallennuspaikka,temprivi,10);
		strcpy(texturenimi,"textures/");
		strcat(texturenimi,rivit);

		//if(atoi(rivi)==155) 
 

		

		//if(atoi(rivi)==255)		

		//tausta[q]=lataakuva(m_pDD,rivit,true);

	D3DXCreateTextureFromFileExA(				
		  m_pDevice,
		  texturenimi,
		  0,
		  0,
		  D3DX_DEFAULT,
		  0,
		  format,
		  D3DPOOL_MANAGED,
		  D3DX_FILTER_LINEAR ,
		  D3DX_FILTER_LINEAR  ,
		  0,
		  NULL,
		  NULL,
		  &tausta[q]
		);
	
	}

	fclose(fil);


	return TRUE;
}

	
bool createscreen(void){
		
	m_pD3D = Direct3DCreate8( D3D_SDK_VERSION );

	m_bUseDepthBuffer   = TRUE;
    m_dwMinDepthBits    = 16;
    m_dwMinStencilBits  = 0;
	
		
    // Set up the presentation parameters	
	D3DDISPLAYMODE d3ddm;
	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	format=d3ddm.Format;

    ZeroMemory( &m_d3dpp, sizeof(m_d3dpp) );
    m_d3dpp.Windowed               = false;
	m_d3dpp.BackBufferCount        = 1;
    m_d3dpp.MultiSampleType        = D3DMULTISAMPLE_NONE;
    m_d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    m_d3dpp.hDeviceWindow          = hWnd;
    m_d3dpp.BackBufferWidth  = 1024;
    m_d3dpp.BackBufferHeight = 768;
    m_d3dpp.BackBufferFormat = format;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
                    D3DDEVTYPE_HAL,
                              hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp,
                               &m_pDevice );
	m_pDevice->GetDeviceCaps(&deviceCaps);

	SCREEN_WIDTH=1024;
	SCREEN_HEIGHT=768;
		

	return true;
}

void luekeyb(void)
{
	#define KEYDOWN(name,key) (name[key] & 0x80)  
	int q;
	
    HRESULT  hr; 

	D3DXVECTOR3 intersect; 
	//int kolmio;//,sisus,q;

	long thistime = GetTickCount();	
	elapsed2=0;
	elapsed3[30]=(float)(thistime - m_LastTime);
	for (q=0; q<30; q++){
		elapsed3[q]=elapsed3[q+1];
		elapsed2=elapsed2+elapsed3[q];
	}
	elapsed=elapsed2/30;
	m_LastTime = thistime;
/*
	elapsed2=elapsed;
	elapsed = (float)((thistime - m_LastTime)+elapsed+elapsed2)/3;
	m_LastTime = thistime;*/
/*
	mousestate2=mousestate;
	hr = g_pMouse->GetDeviceState(sizeof(mousestate),&mousestate);
	if FAILED(hr)     
	{                
		return;     
	}
	

	mousex2=mousex;
	mousey2=mousey;
	mousex= mousex + (mousestate.lX+mousestate2.lX)*SCREEN_WIDTH/1024;
	mousey= mousey + (mousestate.lY+mousestate2.lY)*SCREEN_HEIGHT/768;

	if(mousex2!=mousex)	mouse_active=true;
	if(mousey2!=mousey)	mouse_active=true;
	if(mouse_button_0)mouse_active=true;
	if(mousestate.rgbButtons[1])mouse_active=true;
	

	//mousex= mousex + mousestate.lX*2;
	//mousey= mousey + mousestate.lY*2;

	if (mousex<0) mousex=0;
	if (mousex>SCREEN_WIDTH) mousex=(float)SCREEN_WIDTH-1;
	if (mousey<0) mousey=0;
	if (mousey>SCREEN_HEIGHT) mousey=(float)SCREEN_HEIGHT-1;
*/
	
	pressed2=pressed;
	pressed=false;
	for (q=0; q<256; q++){buffer2[q]=buffer[q];}

    
	hr = g_lpDIDevice->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 
    if FAILED(hr)     
	{ 
         // If it failed, the device has probably been lost. 
         // We should check for (hr == DIERR_INPUTLOST) 
         // and attempt to reacquire it here.          
		return;     
	}
	down2=down;
	for (q=0; q<256; q++){if((buffer[q]& 0x80)!=0){pressed=true;down=q;}}
	if((mouse_button_0)||(mouse_button_1))pressed=true;


	//plusmiinus
	if (KEYDOWN(buffer, DIK_SUBTRACT))
		plusmiinus=plusmiinus-0.001f*elapsed*pelinopeus;
	if (KEYDOWN(buffer, DIK_ADD))
		plusmiinus=plusmiinus+0.001f*elapsed*pelinopeus;

	//help
	if (help_screen&&KEYDOWN(buffer,  DIK_ESCAPE )&&!KEYDOWN(buffer2,  DIK_ESCAPE)){
		help_screen=false;
		pelinopeus=1.0f;
	}
	if (KEYDOWN(buffer,  DIK_F1 )&&!KEYDOWN(buffer2,  DIK_F1)){
		if(!help_screen){
			help_screen=true;
			pelinopeus=0.00001f;
		}
		else{
			help_screen=false;
			pelinopeus=1.0f;
		}
	}
	
		

	if((!pressed&&!pressed2)&&(pelivaihe!=0))return;

	//if ((!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE))||(!KEYDOWN(buffer,  DIK_F9 )&&KEYDOWN(buffer2,  DIK_F9)))
	if (!KEYDOWN(buffer,  DIK_F9 )&&KEYDOWN(buffer2,  DIK_F9))
		{
			end_game=true;
			//SendMessage( hWnd, WM_CLOSE, 0, 0 );
		}
	 

	//print screen
	if (KEYDOWN(buffer,  DIK_SYSRQ )){
		Screenshot(m_pDevice,NULL,screenshot_name);
		screenshot_timer=5000;
	}
	

	if(help_screen)return;

	switch (pelivaihe) 
	{
	case 0:{//game
			//esc
			if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE)){
				menu_return_pelivaihe=pelivaihe;
				menu_return_pelivaihe2=pelivaihe2;
				pelivaihe=7;
				pelivaihe2=5;
				selected_left_menu=0;
				focus=0;
				//particles
				for (q=0; q<maximum_particles; q++){
					particle[q].dead=true;
				}
			}
			/*//f2 - save
			if (!KEYDOWN(buffer,  DIK_F2 )&&KEYDOWN(buffer2,  DIK_F2)){
				luesavet();
				pelivaihe=7;
				pelivaihe2=2;
				luesavet();
				mouse_active=false;
			}*/
			readkey_game();
			break;
		   }
	case 1:{//dialog
			//esc
			if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE)){
				menu_return_pelivaihe=pelivaihe;
				menu_return_pelivaihe2=pelivaihe2;
				pelivaihe=7;
				pelivaihe2=5;


				focus=0;
				selected_left_menu=0;
				//particles
				for (q=0; q<maximum_particles; q++){
					particle[q].dead=true;
				}
			}
			//alas
			if (!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN)){
				if(dialog.nodown){dialog.nodown=false;break;}
				dialog_choice=dialog_choice+1;
				if(dialog_choice>=dialog.options)dialog_choice=0;
				playsound(0,1,0,0,0,0);
			}
			//ylös
			if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){
				if(dialog.noup){dialog.noup=false;break;}
				dialog_choice=dialog_choice-1;
				if(dialog_choice<0)dialog_choice=dialog.options-1;
				playsound(0,1,0,0,0,0);
			}
			//enter
			if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){
				if(dialog.noreturn){dialog.noreturn=false;break;}
				playsound(0,1,0,0,0,0);
				switch (dialog.option[dialog_choice].general_effect){
					case 0:{//leave
						pelivaihe=0;
						pelivaihe2=0;
						break;
					}
					case 1:{//talk
						create_dialog(dialog.option[dialog_choice].effect_parameter,dialog.option[dialog_choice].effect_parameter2,dialog.option[dialog_choice].default_selection);
						break;
					}
					case 2:{//attack
						pelivaihe=0;
						pelivaihe2=1;
						create_battle(dialog.option[dialog_choice].effect_parameter,dialog.option[dialog_choice].effect_parameter2);
						break;
					}
					case 3:{//trade
						for(q=0;q<5;q++){
							shipslot[0].cargo[q]=shipslot[0].cargo[q]+dialog.option[dialog_choice].cargoplus[q];
							shipslot[0].cargo[q]=shipslot[0].cargo[q]-dialog.option[dialog_choice].cargominus[q];
							if(shipslot[0].cargo[q]<0)shipslot[0].cargo[q]=0;
						}

						pelivaihe=0;
						pelivaihe2=0;
						break;
					}
					case 4:{//trade ship
						for(q=0;q<5;q++){
							shipslot[0].cargo[q]=shipslot[0].cargo[q]+dialog.option[dialog_choice].cargoplus[q];
							shipslot[0].cargo[q]=shipslot[0].cargo[q]-dialog.option[dialog_choice].cargominus[q];
							if(shipslot[0].cargo[q]<0)shipslot[0].cargo[q]=0;
						}
						edit_shipslot(dialog.option[dialog_choice].effect_parameter);
						break;
					}
					case 5:{//set mission						
						mission[free_mission()]=dialog.option[dialog_choice].mission;
						pelivaihe=0;
						pelivaihe2=0;
						break;
					}
					case 6:{//attack and get plot						
						pelivaihe=0;
						pelivaihe2=1;
						create_battle(dialog.option[dialog_choice].effect_parameter,dialog.option[dialog_choice].effect_parameter2);
						battle.endplot=dialog.option[dialog_choice].mission.prize_plot;
						break;
					}
					case 7:{//do nothing
						break;
					}
					case 8:{//trade and continue talking
						for(q=0;q<5;q++){
							shipslot[0].cargo[q]=shipslot[0].cargo[q]+dialog.option[dialog_choice].cargoplus[q];
							shipslot[0].cargo[q]=shipslot[0].cargo[q]-dialog.option[dialog_choice].cargominus[q];
							if(shipslot[0].cargo[q]<0)shipslot[0].cargo[q]=0;
						}
						create_dialog(dialog.option[dialog_choice].effect_parameter,dialog.option[dialog_choice].effect_parameter2,dialog.option[dialog_choice].default_selection);
						break;
					}
					case 9:{//repair ships						
						edit_shipslot(dialog.option[dialog_choice].effect_parameter);
						break;
					}
					case 10:{//set mission and trade					
						mission[free_mission()]=dialog.option[dialog_choice].mission;
						for(q=0;q<5;q++){
							shipslot[0].cargo[q]=shipslot[0].cargo[q]+dialog.option[dialog_choice].cargoplus[q];
							shipslot[0].cargo[q]=shipslot[0].cargo[q]-dialog.option[dialog_choice].cargominus[q];
							if(shipslot[0].cargo[q]<0)shipslot[0].cargo[q]=0;
						}
						pelivaihe=0;
						pelivaihe2=0;
						break;					
					}
					case 11:{//game over
						dialog.noreturn=true;
						pelivaihe=4;
						pelivaihe2=4;
						break;							
					}
					case 12:{//trade ship and set mission
						edit_shipslot(dialog.option[dialog_choice].effect_parameter);
						mission[free_mission()]=dialog.option[dialog_choice].mission;
						break;													
					}
				}
			}
			break;
		   }
			
	case 2:{//shipdialog
			//esc
			if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE)){	
				playsound(0,1,0,0,0,0);
				if(pelivaihe2==0){
					pelivaihe=0;
					pelivaihe2=0;
				}
				if(pelivaihe2==1){
					pelivaihe=0;
					pelivaihe2=0;
				}

				//possible end plot
				if(battle.endplot!=-1)
				create_dialog(2,battle.endplot,0);//prize plot
				
				//back from ship repairing
				if(pelivaihe2==2){
					create_dialog(3,ship[0].onplanet,6);
				}

				
			}
			//right
			if (!KEYDOWN(buffer,  DIK_RIGHT )&&KEYDOWN(buffer2,  DIK_RIGHT)){			
				if(dialog.nodown){dialog.nodown=false;break;}
				playsound(0,1,0,0,0,0);
				dialog_choice=dialog_choice+1;
				a0:
				if(dialog_choice>=6)dialog_choice=0;

				if(pelivaihe2==1)if(shipslot_battle[dialog_choice].dead){dialog_choice=dialog_choice+1;goto a0;}
				if(pelivaihe2==2)if(shipslot[dialog_choice+1].dead){dialog_choice=dialog_choice+1;goto a0;}
			}
			//left
			if (!KEYDOWN(buffer,  DIK_LEFT )&&KEYDOWN(buffer2,  DIK_LEFT)){
				if(dialog.noup){dialog.noup=false;break;}
				playsound(0,1,0,0,0,0);
				dialog_choice=dialog_choice-1;
				a1:
				if(dialog_choice<0)dialog_choice=5;

				if(pelivaihe2==1)if(shipslot_battle[dialog_choice].dead){dialog_choice=dialog_choice-1;goto a1;}
				if(pelivaihe2==2)if(shipslot[dialog_choice+1].dead){dialog_choice=dialog_choice-1;goto a1;}
			}
			//s-key
			if (!KEYDOWN(buffer,  DIK_S )&&KEYDOWN(buffer2,  DIK_S)){
				playsound(0,1,0,0,0,0);
				int ships=0;
				for (q=1; q<maximum_shipslot; q++){
					if(shipslot[q].dead)continue;
					ships++;
				}
			
					//sell ship
					if((ships>1)&&(pelivaihe2==2)){					
						int sell_amount;
						sell_amount=int((shipslot[dialog_choice+1].energy+20)*shipslot[dialog_choice+1].ship_basea.threat);
						shipslot[dialog_choice+1].energy=0;
						shipslot[dialog_choice+1].dead=true;
						shipslot[0].cargo[3]=shipslot[0].cargo[3]+sell_amount;
						dialog_choice=dialog_choice-1;
						//same as pressing left key
						a2:
						if(dialog_choice<0)dialog_choice=5;						
						if(pelivaihe2==2)if(shipslot[dialog_choice+1].dead){dialog_choice=dialog_choice-1;goto a2;}
					}
			}

			//enter
			if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){
				if(dialog.noreturn){dialog.noreturn=false;break;}
				playsound(0,1,0,0,0,0);
					//give player ship
					if(pelivaihe2==0){
						pelivaihe=0;
						pelivaihe2=0;
						shipslot[dialog_choice+1]=dialog.randomship;
						
						//possible end plot
						if(battle.endplot!=-1)
						create_dialog(2,battle.endplot,0);//prize plot
					}
					//attempt to capture ship
					if(pelivaihe2==1){
						if(options[4]){//easy mode							
							shipslot_battle[0]=shipslot_battle[dialog_choice];
							dialog.randomship=shipslot_battle[dialog_choice];//for giving the ship after the battle
							dialog.randomship.energy=randDouble(20,30);//ship is damaged after capture
							edit_shipslot(2);
							break;
						}
						else{
							pelivaihe=3;
							pelivaihe2=0;
							shipslot_battle[0]=shipslot_battle[dialog_choice];
							dialog.randomship=shipslot_battle[dialog_choice];//for giving the ship after the battle
							dialog.randomship.energy=randDouble(20,30);//ship is damaged after capture						
							//bullets
							for (q=0; q<maximum_bullets; q++){
								bullet[q].dead=true;
							}
							//init ship capturing men
							for(q=0;q<100;q++){
								capture_man[q].dead=true;
							}
							for(q=0;q<3;q++){
								capture_man[q].dead=false;
								capture_man[q].energy=130;
								capture_man[q].guntime=0;
								capture_man[q].x=randInt(-300,300);
								capture_man[q].z=650;
								capture_man[q].side=0;
								capture_man[q].legtimer=randDouble(0,1);		
								capture_man[q].leg=randInt(0,2);
								capture_man[q].targettimer=0;
								capture_man[q].uptimer=0;
								capture_man[q].left_right_timer=0;
								capture_man[q].rotatex=pi/2;
							}
							for(q=5;q<11;q++){
								capture_man[q].dead=false;
								capture_man[q].energy=45;
								capture_man[q].guntime=0;
								capture_man[q].x=randInt(-300,300);
								capture_man[q].z=-650;
								capture_man[q].side=1;
								capture_man[q].legtimer=randDouble(0,1);
								capture_man[q].leg=randInt(0,2);
								capture_man[q].targettimer=0;
								capture_man[q].uptimer=0;
								capture_man[q].left_right_timer=0;		
								capture_man[q].rotatex=-pi/2;
							}
						}
					}
					//repair ship
					if((pelivaihe2==2)&&(shipslot[dialog_choice+1].energy<shipslot[dialog_choice+1].ship_basea.base_energy)){
					
						int repair_amount;
						repair_amount=int(shipslot[dialog_choice+1].ship_basea.base_energy-shipslot[dialog_choice+1].energy)*shipslot[dialog_choice+1].ship_basea.threat;
						if(repair_amount>shipslot[0].cargo[3])repair_amount=shipslot[0].cargo[3];
						shipslot[dialog_choice+1].energy=shipslot[dialog_choice+1].energy+repair_amount/shipslot[dialog_choice+1].ship_basea.threat;
						shipslot[0].cargo[3]=shipslot[0].cargo[3]-repair_amount;
						
						if(shipslot[dialog_choice+1].energy>shipslot[dialog_choice+1].ship_basea.base_energy-1)shipslot[dialog_choice+1].energy=shipslot[dialog_choice+1].ship_basea.base_energy;
						
					}

				}
			break;
		   }
	//ship capturing
	case 3:{
			//right
			if (KEYDOWN(buffer,  DIK_RIGHT )){
				capture_man[0].right=true;
			}
			//left
			if (KEYDOWN(buffer,  DIK_LEFT )){
				capture_man[0].left=true;
			}
			//up
			if (KEYDOWN(buffer,  DIK_UP )){
				capture_man[0].up=true;
			}
			//down
			if (KEYDOWN(buffer,  DIK_DOWN )){
				capture_man[0].down=true;
			}
			//space
			if (KEYDOWN(buffer,  DIK_SPACE )){
				capture_man[0].space=true;
			}
			//alt
			if(KEYDOWN(buffer,  DIK_LMENU)||KEYDOWN(buffer,  DIK_RMENU)){
				capture_man[0].alt=true;
			}
			break;
		   }
	//map
	case 5:{
			//space
			if (!KEYDOWN(buffer,  DIK_SPACE )&&KEYDOWN(buffer2,  DIK_SPACE)){				
				if(dialog.noreturn){dialog.noreturn=false;break;}
					//return to game mode
					if(pelivaihe2==0){
						playsound(0,1,0,0,0,0);
						pelivaihe=0;
						pelivaihe2=0;					
					}
			}
			//enter
			if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){				
				if(dialog.noreturn){dialog.noreturn=false;break;}
					//return to game mode
					if(pelivaihe2==0){
						playsound(0,1,0,0,0,0);
						pelivaihe=0;
						pelivaihe2=0;					
					}
			}
			//esc
			if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE)){
					//return to game mode
					if(pelivaihe2==0){
						playsound(0,1,0,0,0,0);
						pelivaihe=0;
						pelivaihe2=0;					
					}			
			}
			break;
		   }
	//missions
	case 6:{
			//space
			if (!KEYDOWN(buffer,  DIK_SPACE )&&KEYDOWN(buffer2,  DIK_SPACE)){				
				if(dialog.noreturn){dialog.noreturn=false;break;}
					//return to game mode
					if(pelivaihe2==0){
						playsound(0,1,0,0,0,0);
						pelivaihe=0;
						pelivaihe2=0;					
					}
			}
			//enter
			if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){				
				if(dialog.noreturn){dialog.noreturn=false;break;}
					//return to game mode
					if(pelivaihe2==0){
						playsound(0,1,0,0,0,0);
						pelivaihe=0;
						pelivaihe2=0;					
					}
			}
			//selecting missions
			if(missions>0){
				//alas
				if (!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN)){
					//if(dialog.nodown){dialog.nodown=false;break;}
					playsound(0,1,0,0,0,0);
					selected_mission=selected_mission+1;
					if(selected_mission>=missions)selected_mission=0;
				}
				//ylös
				if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){
					//if(dialog.noup){dialog.noup=false;break;}
					playsound(0,1,0,0,0,0);
					selected_mission=selected_mission-1;
					if(selected_mission<0)selected_mission=missions-1;
				}
			}
			//esc
			if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE)){
					//return to game mode
					if(pelivaihe2==0){
						playsound(0,1,0,0,0,0);
						pelivaihe=0;
						pelivaihe2=0;					
					}			
			}
			break;
		   }
	case 7:{
			
		//sound:click
		if(!pressed&&pressed2)playsound(0,1,0,0,0,0);
			/*//esc
			if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE)){
				pelivaihe=0;
				pelivaihe2=0;
			}*/
			break;
		   }
	case 8:{
		if(!pressed&&pressed2){
			if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN))dialog.noreturn=true;
			pelivaihe=7;
			pelivaihe2=5;	
			mouse_button_0=false;
			mouse_button_was_0=false;
		}
			break;
		   }
	}
}

void laskesavut(void)//laskee savut
{
	int a;
	float savunnopeus=0.1f;
	float rotatenopeus=0.001f;
	
	for (a=0; a<maksimisavuja; a++){
		if(savu[a].pois)continue;
		savu[a].aika=savu[a].aika-elapsed*pelinopeus;

		//jos savu on liian pieni, häviää se
		savu[a].koko=savu[a].koko+savu[a].suurenee*elapsed*pelinopeus;
		//savu ei saa olla liian iso
		if(savu[a].koko>20)savu[a].koko=20;
		if(savu[a].koko<=0) {savu[a].aika=-1;}

		savu[a].paikka.x=savu[a].paikka.x+savu[a].vx*elapsed*pelinopeus;
		savu[a].paikka.y=savu[a].paikka.y+savu[a].vy*elapsed*pelinopeus;
		savu[a].paikka.z=savu[a].paikka.z+savu[a].vz*elapsed*pelinopeus;

		if(savu[a].aika<150.0f){
			savu[a].transparency=savu[a].transparency-savu[a].transparency*0.01f*elapsed*pelinopeus;
		}
		if(savu[a].aika<0){
			savu[a].pois=true;
			continue;
		}
		if(savu[a].transparency<0){
			savu[a].pois=true;
			continue;
		}		
	}
}

void savusta(float transparency, float koko, float suurenee,bool rotate,float savukesto,float x,float y,float z,int tyyppi,float q,float w,float e,float vx,float vy,float vz)//tekee savun ja räjähykset
{
	int a,b;	
		//päätetään minkä luodin paikalle tulee uusi
			a=0;
			b=0;
					alku1:
					a=randInt(0,maksimisavuja);
					b=b+1;
					if(b>maksimisavuja)savu[a].pois=true;
					if(!savu[a].pois)goto alku1;

	savu[a].pois=false;
	savu[a].paikka.x=x;
	savu[a].paikka.y=y;
	savu[a].paikka.z=z;
	savu[a].tyyppi=tyyppi;
	savu[a].koko=koko+randDouble(-0.2f,0.2f);
	if(koko<0.1f)koko=0.1f;
	savu[a].transparency=transparency;
	savu[a].q=q;
	savu[a].w=w;
	savu[a].e=e;
	savu[a].suurenee=suurenee;
	savu[a].vx=vx;
	savu[a].vy=vy;
	savu[a].vz=vz;
			
	savu[a].aika=randDouble(0,savukesto);	
	//savu[a].cos=(float)cos(savu[a].q);
	//savu[a].sin=(float)sin(savu[a].q);
	//savu[a].up=0;
	if(rotate)
	{
		savu[a].rotate=randDouble(-pi,pi);
		//savu[a].up=(float)sin(savu[a].w);
	}
	else savu[a].rotate=0;

}

void valota(float x,float y,float z)
{

	int q;
	for (q=0; q<maksimivaloja; q++) if(lamppu[q].on==false) break;//etsitään vapaa lamppu
		if(q>=maksimivaloja)q=randInt(0,maksimivaloja);//jos vapaata ei löydy

		
	//if(valoja>=maksimivaloja)poistavalo(randInt(0,valoja),&valoja);

		ZeroMemory(&lamppu[q].valo, sizeof(D3DLIGHT8));
 
			lamppu[q].on=true;				
			lamppu[q].valo.Type = D3DLIGHT_POINT;	
			lamppu[q].valo.Diffuse.r = 1.0f;    
			lamppu[q].valo.Diffuse.g = 1.0f;
			lamppu[q].valo.Diffuse.b = 1.0f;    
			lamppu[q].valo.Ambient.r = 1.0f;
			lamppu[q].valo.Ambient.g = 1.0f;    
			lamppu[q].valo.Ambient.b = 1.0f;
			lamppu[q].valo.Specular.r = 1.0f;    
			lamppu[q].valo.Specular.g = 1.0f;
			lamppu[q].valo.Specular.b = 1.0f;
			//lamppu[q].valo.Direction = 1.0f; 
			lamppu[q].valo.Position.x = x;
			lamppu[q].valo.Position.y = y;  
			lamppu[q].valo.Position.z = z;
			lamppu[q].valo.Attenuation0 = 0.5f;
			lamppu[q].valo.Attenuation1=0.0f;	
			lamppu[q].valo.Attenuation2=0.0f;
			lamppu[q].valo.Range = 500;
			
			m_pDevice->SetLight(q, &lamppu[q].valo);
			m_pDevice->LightEnable(q, TRUE);
}

	
bool Render(void)
{
	m_pDevice->BeginScene();


	if((pelivaihe==7)&&(!cursor_shown)){
		m_pDevice->ShowCursor(TRUE);
		cursor_shown=true;
	}
	if((pelivaihe!=7)&&(cursor_shown)){
		m_pDevice->ShowCursor(FALSE);
		cursor_shown=false;
	}

	switch (pelivaihe) 
	{
	case 0:{		
		clearzbuffer();
		render_game();
		break;
		   }
	case 1:{		
		clearzbuffer();
		render_dialog();
		break;
		   }	
	case 2:{
		clearzbuffer();
		render_ships();
		break;
		   }
	case 3:{
		clearzbuffer();
		render_capture();
		break;
		   }
	case 4:{
		render_cutscene();
		break;			
			}
	case 5:{
		render_map();
		break;			
			}
	case 6:{
		render_missions();
		break;			
			}
	case 7:{
		clearzbuffer();
		if(keytimer>-10*elapsed)keytimer=keytimer-(int)elapsed;
		render_menu();
		break;			
			}
	case 8:{
		clearzbuffer();
		render_start_demo();
		break;
		   }
			/*
	case 3:
		break;
	case 4:{
		clearzbuffer();
		if(keytimer>-10*elapsed)keytimer=keytimer-(int)elapsed;
		render_menu();
		break;
		   }
	}*/
	}
/*
	if(options[1]&&SOUNDS_LOADED){
		int q;
		for (q=0; q<25; q++){
			soundtimer[q]=soundtimer[q]+elapsed*pelinopeus;
		}
	}*/




	//help
	if(help_screen){
		kamerax1=0;
		kameray1=4200;
		kameraz1=0;
		kamerax2=1;
		kameray2=0;
		kameraz2=0;		
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
		D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );
		m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

		mallit[1].malli[1].sisus[0].textuuri2=62;
		mallit[1].malli[1].sisus[0].textuuri=62;
		m_pDevice->LightEnable(0, FALSE);
		m_pDevice->LightEnable(1, FALSE);
		m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
		m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);	
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO    );
		m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_INVSRCCOLOR);

		matriisi->LoadIdentity();
		matriisi->TranslateLocal(0,0,0);			
		matriisi->RotateYawPitchRollLocal(pi/2,pi/2,0);
		matriisi->ScaleLocal(46,46,46);
		drawfast(&mallit[1].malli[1]);

		kirjota(1,-1,-1,-1,100,150,0,"Help:");
		kirjota(1,-1,-1,-1,100,700,0,"Press F1 to continue.");

		switch (pelivaihe) 
		{
			case 0:
				if(pelivaihe2==0){						
					kirjota(1,-1,-1,-1,120,190,50,"This is the solar system mode. You fly your spaceship from planet to planet while taking missions from the planets.");
					kirjota(1,-1,-1,-1,120,244,50,"Saving: While in Solar system mode, you may save your game by pressing escape and selecting save game in the menu.");
					kirjota(1,-1,-1,-1,120,298,50,"Controls: You may switch the controlled ship by pressing the switch ship key (default:3). You may see your logbook by pressing the mission log key (default:space). Your hi-tech map is available with the map key (default:enter).");
					kirjota(1,-1,-1,-1,120,374,50,"Fuel: The number in the bottom right corner represents your fuel amount. When you run out of fuel, you cannot steer your ship. You may buy more fuel from the planets. If you run out of fuel and money, you have to wait for a ship to come along, then capture or destroy it to get more fuel. Remember that fuel is only spent when you press the up or down keys, so try to minimize the usage of these keys to preserve fuel.");
				}
				if(pelivaihe2==1){						
					kirjota(1,-1,-1,-1,120,190,50,"This is the battle mode. Your fleet attempts to destroy the enemy ships before they destroy you. You control one of your ships while the computer controls the others. The number under each ship represents its health. If the ship´s health runs low enough, it has a chance of being disabled.");
					kirjota(1,-1,-1,-1,120,282,50,"The battle ends when one side´s ships have been either destroyed or disabled.");
					kirjota(1,-1,-1,-1,120,316,50,"Controls: Fire ships weapons (default:1, 2). You can change the ship you control (if you have more than one ship) by pressing the switch ship key (default:3).");
					kirjota(1,-1,-1,-1,120,388,50,"Radar: The lower right greenish square is your radar. Your ships are marked with a green arrow and the enemies are represented by red arrows.");
					kirjota(1,-1,-1,-1,120,442,50,"Heat: The number above your radar is your heat meter. It increases when you fire your weapons, and decreases over time. If the meter reaches 100, your ship overheats and you cannot fire until all the heat has dissipated.");
				}
				break;	
			case 1:
				kirjota(1,-1,-1,-1,120,190,50,"This is the dialog window. You can select your response with the up and down cursor keys. Say your line by pressing enter.");
				break;
			case 2:
				kirjota(1,-1,-1,-1,120,190,50,"There is no help for this screen. Refer to the help in the lower portion of the display.");
				break;
			case 3:
				kirjota(1,-1,-1,-1,120,190,50,"This is the ship capturing screen. You control one of the three squad members attempting to capture the enemy ship. The enemy troops are marked red, your troops are grey. The soldier you control has a green outline. If you manage to kill all enemy troops, you get the ship at your disposal.");
				kirjota(1,-1,-1,-1,120,278,50,"Controls: To fire your weapon, press space. You can move sidewards using the alt key. Note: These keys are not configurable.");
				break;
			case 4:
				kirjota(1,-1,-1,-1,120,190,50,"There is no help for this screen.");
				break;
			case 5:
				kirjota(1,-1,-1,-1,120,190,50,"This is the map mode. It shows the planets rotating around the sun. Your ship is also marked on the map. This information helps you navigate through the solar system (That´s what maps are for, right?).");
				break;
			case 6:
				kirjota(1,-1,-1,-1,120,190,50,"This is the mission log. To the left you can see your currently active missions. You can select one by pressing the up and down keys. On the right you can see detailed information about the selected mission. This is useful if you don´t know where to find the moon you are supposed to go to.");
				break;
			case 7:
				kirjota(1,-1,-1,-1,120,190,50,"This is the menu. If you haven´t already started a game, you can start a new game here. You can save your current game only if you come to the menu from the solar system mode by pressing escape.");
				if(pelivaihe2==3){//options
					kirjota(1,-1,-1,-1,120,264,50,"Options:");
					kirjota(1,-1,-1,-1,140,264+1*20,50,"Nebula visible: If the background nebula and galaxies are visible.");
					kirjota(1,-1,-1,-1,140,264+2*20,50,"Stars visible: If the background stars are visible.");
					kirjota(1,-1,-1,-1,140,264+3*20,50,"High poly ships: If the ships are displayed in high polygon count in battle.");
					kirjota(1,-1,-1,-1,140,264+4*20,50,"Game start demo: If the spinning sword is displayed on game start.");
					kirjota(1,-1,-1,-1,140,264+5*20,50,"Easy Mode: You can ease the game if you find it difficult.");
					kirjota(1,-1,-1,-1,140,264+6*20,50,"Sound: If the sound effects should be played or not.");
					kirjota(1,-1,-1,-1,140,264+7*20,50,"Music: If the soundtrack should be played or not.");
					kirjota(1,-1,-1,-1,140,264+8*20,50,"Change Keys: Change the ship´s controls.");
					kirjota(1,-1,-1,-1,140,264+9*20,50,"Particles visible: If the particles from explosions should be visible.");
					
				}
				break;
				   
		}

	}

	if(plusmiinus!=0)
	{
		CHAR t[100];
		kirjota(1,-1,-1,-1,10,10,0,"debug mode:");	

		ltoa(bug1,t,10);
		kirjota(1,-1,-1,-1,10,25,0,t);

		ltoa(bug2,t,10);
		kirjota(1,-1,-1,-1,10,40,0,t);
		
		ltoa(bug3,t,10);
		kirjota(1,-1,-1,-1,10,55,0,t);

		ltoa((long)(plusmiinus*1000),t,10);
		kirjota(1,-1,-1,-1,10,70,0,t);
			
		ltoa((long)(1000/elapsed),t,10);
		kirjota(1,-1,-1,-1,10,85,0,t);	
	}

	if(screenshot_timer>0){
		screenshot_timer=screenshot_timer-elapsed*pelinopeus;
		strcpy(temprivi,"Screenshot saved as ´");
		strcat(temprivi,screenshot_name);
		strcat(temprivi,"´");
		kirjota(1,0,screenshot_timer/5000,0,10,10,0,temprivi);
	}
	if(game_saved_timer>0){
		game_saved_timer=game_saved_timer-elapsed*pelinopeus;
		strcpy(temprivi,"Game saved");
		kirjota(1,0,game_saved_timer/5000,0,10,10,0,temprivi);
	}
	if(game_saved_timer<0){
		game_saved_timer=game_saved_timer+elapsed*pelinopeus;
		strcpy(temprivi,"Game loaded");
		kirjota(1,0,-game_saved_timer/5000,0,10,10,0,temprivi);
	}
	if(fabs(game_saved_timer)<100)game_saved_timer=0;

	
	
	m_pDevice->EndScene();


	return true;
}

bool luekuvat(void)
{
	int q;
	kuvia	=	new LPDIRECT3DSURFACE8[numkuvia];	
	//HBITMAP hbm = 0;
	//BITMAP bminfo;

	

	for (q=0; q<numkuvia; q++){
		
		strcpy(rivi,"textures/pic");
		itoa(q,temprivi,10);
		strcat(rivi,temprivi);
		strcat(rivi,".bmp");


		// Load the resource
		//hbm = (HBITMAP)LoadImage(NULL, rivi, IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		//GetObject(hbm, sizeof(bminfo), &bminfo);

		HRESULT res=m_pDevice->CreateImageSurface(
		  SCREEN_WIDTH,
		  SCREEN_HEIGHT,
		  format,
		  //D3DFMT_A8R8G8B8,
		  &kuvia[q]
		);

		//kuvia[q]=lataakuva(m_pDD, rivi,false);	
		 res= D3DXLoadSurfaceFromFileA(
		  kuvia[q],
		  NULL,
		  NULL,
		  rivi,
		  NULL,
		  D3DX_DEFAULT,
		  0,
		  NULL
		);

		/*color.dwColorSpaceHighValue=0x000000;
		color.dwColorSpaceLowValue=0x000000;
		kuvia[q]->SetColorKey(DDCKEY_SRCBLT,&color);*/
	}
	//DeleteObject(hbm);
	//DeleteObject(&bminfo);

	return true;

}

bool initkeyb(void)
{
	



	HRESULT hr;      
	// Create the DirectInput object. 
    hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, 
                           IID_IDirectInput8, (void**)&g_lpDI, NULL); 
    if FAILED(hr) return FALSE;
	
	//näpiskä
				// Retrieve a pointer to an IDirectInputDevice7 interface 
				hr = g_lpDI->CreateDevice(GUID_SysKeyboard, 
						&g_lpDIDevice, NULL); 
				if FAILED(hr)     
				{         
					deinitkeyb();         
					return FALSE;     
				}  
				// Now that you have an IDirectInputDevice7 interface, get 
				// it ready to use.  
				// Set the data format using the predefined keyboard data 
				// format provided by the DirectInput object for keyboards. 
				hr = g_lpDIDevice->SetDataFormat(&c_dfDIKeyboard);     
				if FAILED(hr)     
				{ 
					deinitkeyb();          
					return FALSE;     
				}  
				// Set the cooperative level 
				hr = g_lpDIDevice->SetCooperativeLevel(hWnd,
								DISCL_FOREGROUND | DISCL_EXCLUSIVE);
				if FAILED(hr)     
				{         
					deinitkeyb();         
					return FALSE;     
				}  
				// Get access to the input device.     
				hr = g_lpDIDevice->Acquire(); 
				if FAILED(hr)     
				{         
					deinitkeyb();         
					return FALSE;     
				}
				

/*
	//moussi
				hr = g_lpDI->CreateDevice(GUID_SysMouse,
					&g_pMouse, NULL); 
				if (FAILED(hr)) 
					{   
						deinitkeyb();
						return FALSE;
					}
				hr = g_pMouse->SetDataFormat(&c_dfDIMouse); 
				if (FAILED(hr)) 
					{   
						deinitkeyb();
						return FALSE;
					}
				hr = g_pMouse->SetCooperativeLevel(hWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND); 
				if (FAILED(hr)) 
					{
						deinitkeyb();
						return FALSE;
					}
								
				hr = g_pMouse->Acquire();
				if (FAILED(hr)) 
					{
						deinitkeyb();
						return FALSE;
					}*/

    return TRUE; 


}

bool deinitkeyb(void)
{

	if (g_lpDI)     
	{         
		if (g_lpDIDevice)         
		{             
		 
		//Always unacquire device before calling Release().             
			
				 g_lpDIDevice->Unacquire();
				 g_lpDIDevice->Release();
				 g_lpDIDevice = NULL;         
		}
		g_lpDI->Release();
		g_lpDI = NULL;
		
		/*if (g_pMouse)         
		{             
		 
		//Always unacquire device before calling Release().             
			
				 g_pMouse->Unacquire();
				 g_pMouse->Release();
				 g_pMouse = NULL;         
		}*/
	} 
	       
		  
	 
	return true;
}


void poistaobj(obj *kohde, int indeksi)
{
	for (int a=0; a<indeksi; a++)
	{
	for (int q=0; q<kohde[a].count; q++)
	kohde[a].sisus[q].loota.kolmijako->Release();
	//SAFE_DELETE(kohde[a].sisus[q].loota.kolmijako);
	SAFE_DELETE_ARRAY(kohde[a].sisus);
	}
	SAFE_DELETE_ARRAY(kohde);
	
}

void CleanUp(void)
{

	int q;

	quittaos=true;
	deinitkeyb();
	
	poistaobj(mallit[0].malli,	objnum0	);
	poistaobj(mallit[1].malli,	objnum1	);
	poistaobj(mallit[2].malli,	objnum2	);
	
	for (q=0; q<materiaa; q++)
		SAFE_RELEASE(tausta[q]);
	for (q=0; q<numkuvia; q++)
		SAFE_RELEASE(kuvia[q]);
	//for (q=0; q<materiaa; q++)
	//	SAFE_RELEASE(mat[q]);
	SAFE_DELETE_ARRAY(tausta);
	SAFE_DELETE_ARRAY(kuvia);
	SAFE_DELETE_ARRAY(mat);
	RELEASE(m_pDevice);
	RELEASE(m_pD3D);

	for (int c=0; c<number_of_samples; c++){
			//g_pSound[c]->Stop();
			SAFE_DELETE(g_pSound[c] );
	}
        SAFE_DELETE( g_pSoundManager );
	// Stop playback
	//if(music_initialized){
		if (g_pMediaControl)
			g_pMediaControl->Stop();

		// Release all remaining pointers
		RELEASE( g_pSourceNext);
		RELEASE( g_pSourceCurrent);
		RELEASE( g_pMediaSeeking);
		RELEASE( g_pMediaControl);
		RELEASE( g_pGraphBuilder);
		RELEASE( pEvent);

		// Clean up COM
		CoUninitialize();
	//}
}



BOOL draw(float r,float g,float b,obj *tavara)
{
		
/*
	matriisi->TranslateLocal(tavara->x,tavara->y,tavara->z);
	matriisi->RotateYawPitchRollLocal(tavara->rx,tavara->ry,tavara->rz);	
*/
	//matriisi->TranslateLocal(tavara->x,tavara->y,tavara->z);
	m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());
	tavara->sijainti=*matriisi->GetTop();	
	//if (tavara->mirror) m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	//else m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
/* 
m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
	// Set the source blend state.
m_pDevice->SetRenderState(D3DRS_SRCBLEND, 
                            D3DBLEND_ONE); 
// Set the destination blend state.
m_pDevice->SetRenderState(D3DRS_DESTBLEND, 
                            D3DBLEND_SRCCOLOR );
*/
	if((r!=-1)&&(g!=-1)&&(b!=-1))
	{
			D3DMATERIAL8 mate;
			ZeroMemory( &mate, sizeof(D3DMATERIAL8));
			// Set the RGBA for diffuse reflection. 
			mate.Diffuse.r =0; 
			mate.Diffuse.g =0; 
			mate.Diffuse.b =0; 
			mate.Diffuse.a =0; 
 
			// Set the RGBA for ambient reflection. 
			mate.Ambient.r =1; 
			mate.Ambient.g =1; 
			mate.Ambient.b =1; 
			mate.Ambient.a =1; 
 
			// Set the color and sharpness of specular highlights. 
			mate.Specular.r =0; 
			mate.Specular.g =0; 
			mate.Specular.b =0; 
			mate.Specular.a =0; 
			mate.Power = (float)50.0;
			
			if(r<0)r=0;	if(r>0.99999f)r=0.99999f;
			if(g<0)g=0;	if(g>0.99999f)g=0.99999f;
			if(b<0)b=0;	if(b>0.99999f)b=0.99999f;
			m_pDevice->SetMaterial(&mate);			
			//m_pDevice->SetRenderState( D3DRS_AMBIENT , D3DCOLOR_RGBA(ra, ga, ba, 255));
			m_pDevice->SetRenderState( D3DRS_AMBIENT ,D3DCOLOR_COLORVALUE(r,g,b,1));			
		}

	for (INT q=0; q<tavara->count; q++)
	{
		
		if((r==-1)&&(g==-1)&&(b==-1))m_pDevice->SetMaterial( &mat[tavara->sisus[q].textuuri] );
		m_pDevice->SetTexture( 0, tausta[tavara->sisus[q].textuuri2] );  	
		
		
		m_pDevice->SetStreamSource( 0, tavara->sisus[q].loota.kolmijako, sizeof(vvertex) );
		m_pDevice->SetVertexShader( D3DFVF_WVERTEX );
		m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, tavara->sisus[q].loota.vert/3 );

		//matriisi->Pop();
	}
	//m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);
	//m_pDevice->SetTexture( 0, NULL);//tarvitaanko tätä?
	return true;

}


BOOL drawfast(obj *tavara)
{
	

	m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());
	//tavara->sijainti=*matriisi->GetTop();	
	//if (tavara->mirror) m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	//else m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	for (INT q=0; q<tavara->count; q++)
	{
		

		m_pDevice->SetMaterial( &mat[tavara->sisus[q].textuuri] );
		m_pDevice->SetTexture( 0, tausta[tavara->sisus[q].textuuri2] );  	
		
		
		m_pDevice->SetStreamSource( 0, tavara->sisus[q].loota.kolmijako, sizeof(vvertex) );
		m_pDevice->SetVertexShader( D3DFVF_WVERTEX );
		m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, tavara->sisus[q].loota.vert/3 );
		
	}
	//m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);
	//m_pDevice->SetTexture( 0, NULL);//tarvitaanko tätä?
	return true;

}

//rivi tarkottaa rivitetäänkö teksti(monenko char:n päästä
//void kirjota(-1,-1,-1,INT x, INT y, INT rivi,CHAR teksti[100],LPDIRECTDRAWSURFACE7 pinta,LPDIRECTDRAWSURFACE7 font1)
void kirjota(float size,float r,float g, float b, float x, float y, INT rivi,CHAR teksti[1000])
{

	//RECT loota;
	INT nume;
	int xplus=0;
	int yplus=0;
	float korkeus,leveys;
	float u1,u2,v1,v2;
	int xk,yk;
	int iso=0;
	korkeus=70;
	leveys=60;
	float kirjainleveys=50;
	float kirjainkorkeus=60;
	float xcord=0;
	int kirjainta[2];
	int space;
	kirjainta[0]=0;
	kirjainta[1]=0;
	BOOL lightenabled[2];
	//for (int i=0; i<4; i++)
			m_pDevice->SetMaterial( &mat[10] );			
			matriisi->LoadIdentity();
			m_pDevice->GetLightEnable(0,  &lightenabled[0]); 
			m_pDevice->GetLightEnable(1,  &lightenabled[1]); 
			m_pDevice->LightEnable(0, FALSE);
			m_pDevice->LightEnable(1, FALSE);
			//m_pDevice->SetRenderState( D3DRS_AMBIENT, 0xFFFFFFFF);
			
			if(r==-1){
				int rgb;
				rgb=(int)(0.7f*255);
				m_pDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_RGBA(rgb, rgb, rgb, rgb));
			}
			else
			m_pDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_RGBA((int)(r*255), (int)(g*255), (int)(b*255),255));

			m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());		 
			m_pDevice->SetRenderState( D3DRS_ZBIAS, 0);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
			m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE); 		
			D3DXMatrixPerspectiveFovLH( &matProj,  (float)((80)*pi/180), aspect, 25.0f, maxvisible);		
			m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
			m_pDevice->SetVertexShader( D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) );


	for (int i=0; i<abs((int)strlen(teksti)); i++)
	//for (int i=0; i<4; i++)
	{


	nume=0;
//		teksti[i]=*CharLower(&teksti[i]);
        //kirj:=LowerCase(kirj);
        //if kirj= #32 then exit;
	iso=0;
		switch (teksti[i]) 
		{
			case ' ':{kirjainleveys=16;space=i;nume=-1;goto te;}
			case 'a':{kirjainleveys=16;nume=0;goto fa;}
			case 'b':{kirjainleveys=16;nume=1;goto fa;}
			case 'c':{kirjainleveys=16;nume=2;goto fa;}
			case 'd':{kirjainleveys=16;nume=3;goto fa;}
			case 'e':{kirjainleveys=16;nume=4;goto fa;}
			case 'f':{kirjainleveys=10;nume=5;goto fa;}
			case 'g':{kirjainleveys=16;nume=6;goto fa;}
			case 'h':{kirjainleveys=16;nume=7;goto fa;}
			case 'i':{kirjainleveys=10;nume=8;goto fa;}
			case 'j':{kirjainleveys=10;nume=9;goto fa;}
			case 'k':{kirjainleveys=16;nume=10;goto fa;}
			case 'l':{kirjainleveys=10;nume=11;goto fa;}
			case 'm':{kirjainleveys=25;nume=12;goto fa;}
			case 'n':{kirjainleveys=16;nume=13;goto fa;}
			case 'o':{kirjainleveys=16;nume=14;goto fa;}
			case 'p':{kirjainleveys=16;nume=15;goto fa;}
			case 'q':{kirjainleveys=16;nume=16;goto fa;}
			case 'r':{kirjainleveys=14;nume=17;goto fa;}
			case 's':{kirjainleveys=16;nume=18;goto fa;}
			case 't':{kirjainleveys=16;nume=19;goto fa;}
			case 'u':{kirjainleveys=16;nume=20;goto fa;}
			case 'v':{kirjainleveys=16;nume=21;goto fa;}
			case 'w':{kirjainleveys=24;nume=22;goto fa;}
			case 'x':{kirjainleveys=16;nume=23;goto fa;}
			case 'y':{kirjainleveys=16;nume=24;goto fa;}
			case 'z':{kirjainleveys=15;nume=25;goto fa;}
			case 'å':{kirjainleveys=16;nume=26;goto fa;}
			case 'ä':{kirjainleveys=16;nume=27;goto fa;}
			case 'ö':{kirjainleveys=16;nume=28;goto fa;}
			case '1':{kirjainleveys=12;nume=29;goto fa;}
			case '2':{kirjainleveys=19;nume=30;goto fa;}
			case '3':{kirjainleveys=19;nume=31;goto fa;}
			case '4':{kirjainleveys=20;nume=32;goto fa;}
			case '5':{kirjainleveys=19;nume=33;goto fa;}
			case '6':{kirjainleveys=19;nume=34;goto fa;}
			case '7':{kirjainleveys=19;nume=35;goto fa;}
			case '8':{kirjainleveys=19;nume=36;goto fa;}
			case '9':{kirjainleveys=19;nume=37;goto fa;}
			case '-':{kirjainleveys=10;nume=38;goto fa;}
			case '0':{kirjainleveys=19;nume=39;goto fa;}
			case '.':{kirjainleveys=5;nume=40;goto fa;}
			case '/':{kirjainleveys=12;nume=41;goto fa;}
			case ':':{kirjainleveys=8;nume=42;goto fa;}
			case '´':{kirjainleveys=5;nume=43;goto fa;}
			case '?':{kirjainleveys=16;nume=44;goto fa;}
			case ',':{kirjainleveys=5;nume=45;goto fa;}
			case '!':{kirjainleveys=5;nume=46;goto fa;}
			case '(':{kirjainleveys=12;nume=47;goto fa;}
			case ')':{kirjainleveys=12;nume=48;goto fa;}

			case 'A':{kirjainleveys=21;nume=0;goto fr;}
			case 'B':{kirjainleveys=20;nume=1;goto fr;}
			case 'C':{kirjainleveys=20;nume=2;goto fr;}
			case 'D':{kirjainleveys=20;nume=3;goto fr;}
			case 'E':{kirjainleveys=18;nume=4;goto fr;}
			case 'F':{kirjainleveys=17;nume=5;goto fr;}
			case 'G':{kirjainleveys=21;nume=6;goto fr;}
			case 'H':{kirjainleveys=21;nume=7;goto fr;}
			case 'I':{kirjainleveys=6;nume=8;goto fr;}
			case 'J':{kirjainleveys=17;nume=9;goto fr;}
			case 'K':{kirjainleveys=20;nume=10;goto fr;}
			case 'L':{kirjainleveys=17;nume=11;goto fr;}
			case 'M':{kirjainleveys=26;nume=12;goto fr;}
			case 'N':{kirjainleveys=21;nume=13;goto fr;}
			case 'O':{kirjainleveys=21;nume=14;goto fr;}
			case 'P':{kirjainleveys=20;nume=15;goto fr;}
			case 'Q':{kirjainleveys=21;nume=16;goto fr;}
			case 'R':{kirjainleveys=20;nume=17;goto fr;}
			case 'S':{kirjainleveys=20;nume=18;goto fr;}
			case 'T':{kirjainleveys=19;nume=19;goto fr;}
			case 'U':{kirjainleveys=21;nume=20;goto fr;}
			case 'V':{kirjainleveys=21;nume=21;goto fr;}
			case 'W':{kirjainleveys=30;nume=22;goto fr;}
			case 'X':{kirjainleveys=20;nume=23;goto fr;}
			case 'Y':{kirjainleveys=21;nume=24;goto fr;}
			case 'Z':{kirjainleveys=19;nume=25;goto fr;}
			case 'Å':{kirjainleveys=22;nume=26;goto fr;}
			case 'Ä':{kirjainleveys=22;nume=27;goto fr;}
			case 'Ö':{kirjainleveys=20;nume=28;goto fr;}
		}

fr:
		iso=1;
fa:

		//if(nume>-1){//jos ei ole väli
			
		
		yk=(int)(nume/8);
		xk=nume-yk*8;
		u1=(xk*16)/128.0f;
		u2=(xk*16+16)/128.0f;
		v1=(yk*18)/128.0f;
		v2=(yk*18+18)/128.0f;

			vertexletters[iso][kirjainta[iso]*6+0].position.x=xcord+0;
			vertexletters[iso][kirjainta[iso]*6+0].position.y=-yplus*kirjainkorkeus*size+0;
			vertexletters[iso][kirjainta[iso]*6+0].position.z=0;
			vertexletters[iso][kirjainta[iso]*6+0].u=u2;
			vertexletters[iso][kirjainta[iso]*6+0].v=v2;

			vertexletters[iso][kirjainta[iso]*6+1].position.x=xcord+leveys*size;
			vertexletters[iso][kirjainta[iso]*6+1].position.y=-yplus*kirjainkorkeus*size+korkeus*size;
			vertexletters[iso][kirjainta[iso]*6+1].position.z=0;
			vertexletters[iso][kirjainta[iso]*6+1].u=u1;
			vertexletters[iso][kirjainta[iso]*6+1].v=v1;

			vertexletters[iso][kirjainta[iso]*6+2].position.x=xcord+0;
			vertexletters[iso][kirjainta[iso]*6+2].position.y=-yplus*kirjainkorkeus*size+korkeus*size;
			vertexletters[iso][kirjainta[iso]*6+2].position.z=0;
			vertexletters[iso][kirjainta[iso]*6+2].u=u2;
			vertexletters[iso][kirjainta[iso]*6+2].v=v1;

			vertexletters[iso][kirjainta[iso]*6+3].position.x=xcord+0;
			vertexletters[iso][kirjainta[iso]*6+3].position.y=-yplus*kirjainkorkeus*size+0;
			vertexletters[iso][kirjainta[iso]*6+3].position.z=0;
			vertexletters[iso][kirjainta[iso]*6+3].u=u2;
			vertexletters[iso][kirjainta[iso]*6+3].v=v2;

			vertexletters[iso][kirjainta[iso]*6+4].position.x=xcord+leveys*size;
			vertexletters[iso][kirjainta[iso]*6+4].position.y=-yplus*kirjainkorkeus*size+0;
			vertexletters[iso][kirjainta[iso]*6+4].position.z=0;
			vertexletters[iso][kirjainta[iso]*6+4].u=u1;
			vertexletters[iso][kirjainta[iso]*6+4].v=v2;

			vertexletters[iso][kirjainta[iso]*6+5].position.x=xcord+leveys*size;
			vertexletters[iso][kirjainta[iso]*6+5].position.y=-yplus*kirjainkorkeus*size+korkeus*size;
			vertexletters[iso][kirjainta[iso]*6+5].position.z=0;
			vertexletters[iso][kirjainta[iso]*6+5].u=u1;
			vertexletters[iso][kirjainta[iso]*6+5].v=v1;
		
					
		kirjainta[iso]++;
te:
		xcord=xcord-kirjainleveys*1.85f*size;

		//rivitys
		if(rivi>0)
		if((xcord<-rivi*40)&&(nume==-1)){xcord=0;yplus=yplus+1;i=space;}	
	
}

	for (iso=0; iso<2; iso++){
			if(iso==1)m_pDevice->SetTexture( 0, tausta[10] );			
			else m_pDevice->SetTexture( 0, tausta[11] );
			
			//kamera kohdalleen
			//kamerax1=(x+xplus*(12.5f)-1024/2)*(3.28f)+42;
			//kameray1=(y+yplus*(15.17f)-768/2)*(3.28f)+46;
			kamerax1=(x-1024/2)*(3.28f)+42;
			kameray1=(y-768/2)*(3.28f)+46;
			kameraz1=1500;
			kamerax2=kamerax1+3.7f;
			kameray2=kameray1+3.7f;
			kameraz2=0;
			D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
			m_pDevice->SetTransform( D3DTS_VIEW, &matView );

			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO    );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_INVSRCCOLOR);	
			m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST  ,kirjainta[iso]*2,vertexletters[iso],
				sizeof(pvertex));

			//kamera kohdalleen			
			kamerax2=kamerax1;
			kameray2=kameray1;	
			D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));		
			m_pDevice->SetTransform( D3DTS_VIEW, &matView );
			
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE    );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE    );	
			m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,kirjainta[iso]*2,vertexletters[iso],sizeof(pvertex));

	}
			m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE); 
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
			m_pDevice->LightEnable(0, lightenabled[0]);
			m_pDevice->LightEnable(1, lightenabled[1]);

}





void cfg_save(void){
		FILE *fil;
		int q;
		
		fil = fopen("cfg.cfg","wt");
		for (q=0; q<10; q++){
			fprintf(fil, "%d\n", options[q]);
		}
		for (q=0; q<13; q++){
			fprintf(fil, "%d\n", key[q]);
		}

		
		fclose(fil);
}

void cfg_load(void){
		FILE *fil;
		int q,b;

		
		fil = fopen("cfg.cfg","rt");
		
		for (q=0; q<10; q++){
			fgets(temprivi,sizeof(temprivi),fil);b=atoi(temprivi);
			if(b==0)options[q]=false;
			else options[q]=true;
		}
		for (q=0; q<13; q++){
			fgets(temprivi,sizeof(temprivi),fil);key[q]=atoi(temprivi);			
		}

		fclose(fil);

		//SOUNDS_ON=options[1];
}

void clearzbuffer(void){
	//if(!options[3]){
		m_pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER , 0x00000000, 1, 0 );
	//}
	/*else{	
		DDBLTFX ddbltfx;	
		memset(&ddbltfx, 0, sizeof(ddbltfx));
		ddbltfx.dwSize = sizeof(DDBLTFX);
		ddbltfx.dwFillDepth=0x00FFFFFF;
		zpuskuri->Blt(NULL,NULL,NULL,DDBLT_DEPTHFILL,&ddbltfx);
	}*/
}

float fHatRandom(float fRange)

{

  static float fRandMax = 1.0f * RAND_MAX;



  static float fArea = 4*atanf(6.0f);



  float fP = fArea * (rand()/fRandMax);



  return tanf(fP/4)*fRange/6.0f;

}


void render_game(void){
	int d;
	int a,q;

	d=0;
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);
	//select ship for player control in combat
	if(pelivaihe2==1){
		//no ship controlled yet
		if(player_controlled_ship==-1)
		for (q=1; q<maximum_ships; q++){
			if(ship[q].dead)continue;
			if(ship[q].disabled)continue;
			if(ship[q].side!=0)continue;
			
			player_controlled_ship=q;
			break;
		}
		//player presses 3
		//for (q=1; q<maximum_ships; q++){
		if(((ship[player_controlled_ship].disabled)||(ship[player_controlled_ship].dead))||((!ship[player_controlled_ship].three)&&(ship[player_controlled_ship].three2))){
			q=player_controlled_ship;
			a=player_controlled_ship;
			d=0;
			player_controlled_ship=-1;
			while(player_controlled_ship==-1){
				d++;
				if(d>maximum_ships){player_controlled_ship=a;break;}
				q++;
				if(q>=maximum_ships)q=1;
				if(ship[q].dead)continue;
				if(ship[q].disabled)continue;
				if(ship[q].side!=0)continue;
				
				player_controlled_ship=q;
				break;			
			}		
		}
	}
	//select ship for player control in astronomy screen
	if(pelivaihe2==0){
		if(shipslot[player_controlled_ship_in_map].dead==true)player_controlled_ship_in_map=-1;
		//no ship controlled yet
		if(player_controlled_ship_in_map==-1)
		for (q=1; q<maximum_shipslot; q++){
			if(shipslot[q].dead)continue;
			
			player_controlled_ship_in_map=q;
			break;
		}
		//player presses 3
		//for (q=1; q<maximum_ships; q++){
		if((!ship[0].three)&&(ship[0].three2)){
			q=player_controlled_ship_in_map;
			a=player_controlled_ship_in_map;
			d=0;
			player_controlled_ship_in_map=-1;
			while(player_controlled_ship_in_map==-1){
				d++;
				if(d>maximum_shipslot){player_controlled_ship_in_map=a;break;}
				q++;
				if(q>=maximum_shipslot)q=1;
				if(shipslot[q].dead)continue;
				
				player_controlled_ship_in_map=q;
				break;			
			}		
		}
	}

	ship[0].encounter.ship_basea=shipslot[player_controlled_ship_in_map].ship_basea;

	if(pelivaihe2==0)player_controlled_ship=0;


	fly_particles();
	laskesavut();

	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0 );
	//m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x99999999, 0, 0 );
	
	if(pelivaihe2==0)cameraheight=4200;
	if(pelivaihe2==1){
		float distance=-1;
		for (q=1; q<maximum_ships; q++){
			if(ship[q].dead)continue;
			if(ship[q].disabled)continue;
			if(ship[q].side==0)continue;
			
			if(sqr(ship[q].x1-ship[player_controlled_ship].x1)+sqr(ship[q].z1-ship[player_controlled_ship].z1)>sqr(3000))continue;

			if(distance==-1)distance=sqrtf(sqr(ship[q].x1-ship[player_controlled_ship].x1)+sqr(ship[q].z1-ship[player_controlled_ship].z1));
			else distance=(distance+sqrtf((sqr(ship[q].x1-ship[player_controlled_ship].x1)+sqr(ship[q].z1-ship[player_controlled_ship].z1))))/2;
		}

		if(distance*5<cameraheight)
		cameraheight=cameraheight-elapsed*pelinopeus*0.25f;
		if(distance*5>cameraheight)
		cameraheight=cameraheight+elapsed*pelinopeus*0.25f*6;

		if(cameraheight>6000)cameraheight=6000;
		if(cameraheight<1500)cameraheight=1500;
	}

	//kamera taustan tähdille
	//float kerroin=0.45f;
	kamerax1=ship[0].x1/(200);
	kameray1=4200;
	kameraz1=ship[0].z1/(200);

	kamerax2=kamerax1-100;
	kameray2=0;
	kameraz2=kameraz1;
	

	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((60)*pi/180), aspect, 25.0f, maxvisible);		
	m_pDevice->SetTransform( D3DTS_VIEW, &matView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);

	
			//galaksi
			if(options[1]){
				m_pDevice->SetRenderState(D3DRS_ZENABLE,false);
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
				m_pDevice->SetRenderState( D3DRS_AMBIENT, 0xFFAAAAAA);
				matriisi->LoadIdentity();		
				matriisi->TranslateLocal(galaxy_x,0,galaxy_z);
				matriisi->RotateYawPitchRollLocal(galaxy_rx,galaxy_ry,galaxy_rz);
				matriisi->ScaleLocal(40,1,40);
				m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());			
				m_pDevice->SetMaterial( &mat[0] );
				m_pDevice->SetTexture( 0, tausta[0]);
				m_pDevice->SetVertexShader( D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) );
				
				m_pDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
				m_pDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );
				m_pDevice->SetRenderState( D3DRS_POINTSIZE,     FtoDW(1.0f) );
				m_pDevice->SetRenderState( D3DRS_POINTSIZE_MIN, FtoDW(1.00f) );
				m_pDevice->SetRenderState( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
				m_pDevice->SetRenderState( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
				m_pDevice->SetRenderState( D3DRS_POINTSCALE_C,  FtoDW(0.00f) );
			

				m_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST  ,2500,galaxy,
						sizeof(pvertex));
			}

	kamerax1=ship[0].x1/(30);
	kameray1=4200;
	kameraz1=ship[0].z1/(30);

	kamerax2=kamerax1-100;
	kameray2=0;
	kameraz2=kameraz1;
	

	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((60)*pi/180), aspect, 25.0f, maxvisible);		
	m_pDevice->SetTransform( D3DTS_VIEW, &matView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	
			//nebulat
			if(options[0]){
				m_pDevice->SetRenderState(D3DRS_ZENABLE,false);
				m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE );
				m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE );
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
				m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFAAAAAA);
				matriisi->LoadIdentity();
				//matriisi->TranslateLocal(-8000,0,-8000);
				matriisi->ScaleLocal(4,1,4);
				for (a=0; a<maximum_nebula; a++){
					//matriisi->Push();
					matriisi->LoadIdentity();
					matriisi->ScaleLocal(4,1,4);
					matriisi->TranslateLocal(nebula[a].x,nebula[a].y,nebula[a].z);			
					matriisi->RotateYawPitchRollLocal(nebula[a].rx,nebula[a].ry,nebula[a].rz);			
					matriisi->ScaleLocal(nebula[a].size,nebula[a].size,nebula[a].size);


					switch (nebula[a].picture) 
					{
						case 0:{
							mallit[1].malli[1].sisus[0].textuuri2=3;
							mallit[1].malli[1].sisus[0].textuuri=3;
							break;}
						case 1:{
							mallit[1].malli[1].sisus[0].textuuri2=4;
							mallit[1].malli[1].sisus[0].textuuri=4;
							break;}
						case 2:{
							mallit[1].malli[1].sisus[0].textuuri2=5;
							mallit[1].malli[1].sisus[0].textuuri=5;
							break;}				
						case 3:{
							mallit[1].malli[1].sisus[0].textuuri2=34;
							mallit[1].malli[1].sisus[0].textuuri=34;
							break;}
						case 4:{
							mallit[1].malli[1].sisus[0].textuuri2=35;
							mallit[1].malli[1].sisus[0].textuuri=35;
							break;}
						case 5:{
							mallit[1].malli[1].sisus[0].textuuri2=36;
							mallit[1].malli[1].sisus[0].textuuri=36;
							break;}
						case 6:{
							mallit[1].malli[1].sisus[0].textuuri2=37;
							mallit[1].malli[1].sisus[0].textuuri=37;
							break;}
						case 7:{
							mallit[1].malli[1].sisus[0].textuuri2=38;
							mallit[1].malli[1].sisus[0].textuuri=38;
							break;}
						case 8:{
							mallit[1].malli[1].sisus[0].textuuri2=39;
							mallit[1].malli[1].sisus[0].textuuri=39;
							break;}
						case 9:{
							mallit[1].malli[1].sisus[0].textuuri2=40;
							mallit[1].malli[1].sisus[0].textuuri=40;
							break;}
					}
					
					drawfast(&mallit[1].malli[1]);

				//matriisi->Pop();			
				}
			}

			
			m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
		



	

			
	if(pelivaihe2==0)rendersolarsystem();
	if(pelivaihe2==1)renderbattle();

	int tempcontrol;
	if(pelivaihe2==0){
		tempcontrol=player_controlled_ship;
		player_controlled_ship=0;
	}

	//kamera muille
	kamerax1=ship[player_controlled_ship].x1+100;
	kameray1=cameraheight;
	kameraz1=ship[player_controlled_ship].z1;

	kamerax2=ship[player_controlled_ship].x1;
	kameray2=0;
	kameraz2=ship[player_controlled_ship].z1;

	//kameran kulma
	float camq=-atan2f(-kamerax2+kamerax1,-kameraz2+kameraz1);			
	float camw=0;
	float came=-atan2f(-kameray2+kameray1,sqrtf((sqr(-kameraz2+kameraz1)+sqr(-kamerax2+kamerax1))));
	
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
	m_pDevice->SetTransform( D3DTS_VIEW, &matView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	
	//particle animation
	if(options[8]){
		int aa[4];
		aa[0]=0;aa[1]=0;aa[2]=0;aa[3]=0;
		for (q=0; q<maximum_particles; q++){
			if(particle[q].dead)continue;
			//if(particle[q].picture!=1)continue;
			if(sqr(particle[q].position.x-ship[player_controlled_ship].x1)+sqr(particle[q].position.z-ship[player_controlled_ship].z1)>sqr(2000*(cameraheight*0.00022f)))continue;		

			particle_animation[particle[q].picture][aa[particle[q].picture]].position=particle[q].position;
			
			aa[particle[q].picture]++;	
		}

		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
		m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
		m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE,  FALSE);
		m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);	
		m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
		m_pDevice->LightEnable(0, FALSE);
		m_pDevice->LightEnable(1, FALSE);
		m_pDevice->SetVertexShader( D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) );		
		m_pDevice->SetRenderState( D3DRS_POINTSIZE_MIN, FtoDW(point_size) );
		m_pDevice->SetRenderState( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
		m_pDevice->SetRenderState( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
		m_pDevice->SetRenderState( D3DRS_POINTSCALE_C,  FtoDW(1.00f) );	
		m_pDevice->SetRenderState( D3DRS_POINTSIZE,     FtoDW(point_size) );
		m_pDevice->SetMaterial( &mat[15] );
		m_pDevice->SetTexture( 0, tausta[15]);
		
		for (q=0; q<4; q++){
			if(aa[q]>0){
			
				
				matriisi->LoadIdentity();				
				m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());
				if(q==0){
					m_pDevice->SetMaterial( &mat[15] );
					m_pDevice->SetTexture( 0, tausta[15]);
				}
				if(q==1){
					m_pDevice->SetMaterial( &mat[13] );
					m_pDevice->SetTexture( 0, tausta[13]);
				}
				
				m_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST  ,aa[q],particle_animation[q],sizeof(pvertex));			
			

			}	
		}
		m_pDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
		m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	}


	
	//savujen piirto
	rendersmoke(camq,camw,came);			
			



	if(pelivaihe2==0){		
		player_controlled_ship=tempcontrol;
	}

}


void readkey_game(void){
	int temp;
	if(pelivaihe2==0){
		temp=player_controlled_ship;
		player_controlled_ship=0;
	}

	
	//ship controlling
	ship[player_controlled_ship].enter2=ship[player_controlled_ship].enter;
	ship[player_controlled_ship].esc2=ship[player_controlled_ship].esc;
	ship[player_controlled_ship].up2=ship[player_controlled_ship].up;
	ship[player_controlled_ship].down2=ship[player_controlled_ship].down;
	ship[player_controlled_ship].left2=ship[player_controlled_ship].left;
	ship[player_controlled_ship].right2=ship[player_controlled_ship].right;
	ship[player_controlled_ship].one2=ship[player_controlled_ship].one;
	ship[player_controlled_ship].two2=ship[player_controlled_ship].two;
	ship[player_controlled_ship].three2=ship[player_controlled_ship].three;
	ship[player_controlled_ship].four2=ship[player_controlled_ship].four;
	ship[player_controlled_ship].space2=ship[player_controlled_ship].space;

	ship[player_controlled_ship].enter=false;
	ship[player_controlled_ship].esc=false;
	ship[player_controlled_ship].up=false;
	ship[player_controlled_ship].down=false;
	ship[player_controlled_ship].left=false;
	ship[player_controlled_ship].right=false;
	ship[player_controlled_ship].one=false;
	ship[player_controlled_ship].two=false;
	ship[player_controlled_ship].three=false;
	ship[player_controlled_ship].four=false;
	ship[player_controlled_ship].space=false;


	
	if (KEYDOWN(buffer, DIK_ESCAPE))
		ship[player_controlled_ship].esc=true;
	if (buffer[key[1]]& 0x80)
		ship[player_controlled_ship].up=true;
	if (buffer[key[2]]& 0x80)
		ship[player_controlled_ship].down=true;
	if (buffer[key[3]]& 0x80)
		ship[player_controlled_ship].left=true;
	if (buffer[key[4]]& 0x80)
		ship[player_controlled_ship].right=true;
	if (buffer[key[5]]& 0x80)
		ship[player_controlled_ship].one=true;
	if (buffer[key[6]]& 0x80)
		ship[player_controlled_ship].two=true;
	if (buffer[key[7]]& 0x80)
		ship[player_controlled_ship].three=true;
	if (buffer[key[8]]& 0x80)
		ship[player_controlled_ship].four=true;
	if (buffer[key[9]]& 0x80)
		ship[player_controlled_ship].enter=true;
	if (buffer[key[11]]& 0x80)
		ship[player_controlled_ship].space=true;

			if(!help_screen){
				//pelin hidastus
				if (buffer[key[9]]& 0x80)
					{
					 if(pelinopeus>0.2f)
						 pelinopeus=pelinopeus-0.5f*0.01f*elapsed;
					}
				else
					if(pelinopeus<1)
						pelinopeus=pelinopeus+0.5f*0.01f*elapsed;

					if(pelinopeus>1)
						pelinopeus=1;						
					if(pelinopeus<0.2f)
						pelinopeus=0.2f;
			}
				/*
				//kameramoodin vaihto
				if (buffer[key[10]]& 0x80)
				if (!(buffer2[key[10]]& 0x80))
				{					
					if(!mapmode)mapmode=true;
					else mapmode=false;
				}
				
				//kameran ohjaus
				float MOTION_SPEED=0.1f;//kameran nopeus
				if (KEYDOWN(buffer,  DIK_END))
					{
						dy=dy-MOTION_SPEED*elapsed;
						if (dy<=-5) dy=-5;
					}
				if (KEYDOWN(buffer,  DIK_HOME))
					{
						dy=dy+MOTION_SPEED*elapsed;			
						if (dy>=43) dy=43;
					}
				if (KEYDOWN(buffer,  DIK_DELETE))
					{
						dx=dx-MOTION_SPEED*elapsed;
					}
				if (KEYDOWN(buffer,  DIK_NEXT))
					{
						dx=dx+MOTION_SPEED*elapsed;
					}*/
	if(pelivaihe2==0){

		//goto map mode
		if((!ship[player_controlled_ship].enter2)&&(ship[player_controlled_ship].enter)){
			pelivaihe=5;
			pelivaihe2=0;
			dialog.noreturn=true;
		}
		//goto missions mode
		if((!ship[player_controlled_ship].space2)&&(ship[player_controlled_ship].space)){
			pelivaihe=6;
			pelivaihe2=0;
			dialog.noreturn=true;
		}
	}	
	if(pelivaihe2==0)player_controlled_ship=temp;
}

void fly(shipbase *shipa){

	int q;

	
	
	float tuulenvastus=0.01f;
	float tuulenvastusrotate=0.1f;
	float powerdownrate=0.7f;
	float kerroin;

	//no fuel in map mode
	if((pelivaihe==0)&&(pelivaihe2==0)){
		if(shipa->number==0)
		if(shipslot[0].cargo[4]<=0){
			shipa->up=false;
			shipa->down=false;
		}
	}

	shipa->x2=shipa->x1;
	shipa->z2=shipa->z1;

	
	

	//transfer energy to shipslots
	if(shipa->side==0)shipslot[shipa->number].energy=shipa->energy;

	if(shipa->energy<=0){		
		shipa->dead=true;
		//destroy ship from list
		if(shipa->side==0)
			shipslot[shipa->number].dead=true;
	}

	//disabled
	if(shipa->disabled){
		shipa->enter=false;
		shipa->esc=false;
		shipa->up=false;
		shipa->down=false;
		shipa->left=false;
		shipa->right=false;
		shipa->one=false;
		shipa->two=false;
		shipa->three=false;
		shipa->four=false;
		shipa->space=false;
	}

	//for computer thinking
	if(shipa->shotlast_enemy>0){
		if(ship[shipa->shotlast_enemy].dead)shipa->shotlast_enemy=-1;
		if(ship[shipa->shotlast_enemy].disabled)shipa->shotlast_enemy=-1;
		if(ship[shipa->shotlast_enemy].side==shipa->side)shipa->shotlast_enemy=-1;
	}
	if(shipa->shotlast_me>0){
		if(ship[shipa->shotlast_me].dead)shipa->shotlast_me=-1;
		if(ship[shipa->shotlast_me].disabled)shipa->shotlast_me=-1;
		if(ship[shipa->shotlast_me].side==shipa->side)shipa->shotlast_me=-1;
	}

	/*
	//automaattiohjaus
	if(!shipa->left&&!shipa->right){
		if(shipa->vr<-0.02f/1000)shipa->right=true;
		if(shipa->vr>0.02f/1000)shipa->left=true;
	}*/

	//moottorien lieskat
	shipa->motor0time=shipa->motor0time+elapsed*pelinopeus;
	shipa->motor1time=shipa->motor1time+elapsed*pelinopeus;
	shipa->motor2time=shipa->motor2time+elapsed*pelinopeus;
	shipa->motor3time=shipa->motor3time+elapsed*pelinopeus;
	if(shipa->motor0time>10)shipa->motor0time=10;
	if(shipa->motor1time>10)shipa->motor1time=10;
	if(shipa->motor2time>10)shipa->motor2time=10;
	if(shipa->motor3time>10)shipa->motor3time=10;
	
	
	
	
		//shipa->mass=(6)*100000;
		if(shipa->up)shipa->motordown=shipa->motordown+(shipa->encounter.ship_basea.motordownpower-sqr(shipa->motordown)*tuulenvastus/1000)*elapsed*pelinopeus;	
		if(shipa->down)shipa->motorup=shipa->motorup+(shipa->encounter.ship_basea.motoruppower-sqr(shipa->motorup)*tuulenvastus/1000)*elapsed*pelinopeus;	
		if(shipa->left)shipa->motorleft=shipa->motorleft+(shipa->encounter.ship_basea.motorleftpower-sqr(shipa->motorleft)*tuulenvastusrotate/1000)*elapsed*pelinopeus;	
		if(shipa->right)shipa->motorright=shipa->motorright+(shipa->encounter.ship_basea.motorrightpower-sqr(shipa->motorright)*tuulenvastusrotate/1000)*elapsed*pelinopeus;	
	
		shipa->motorup=shipa->motorup-powerdownrate*elapsed*pelinopeus;
		shipa->motordown=shipa->motordown-powerdownrate*elapsed*pelinopeus;
		shipa->motorleft=shipa->motorleft-powerdownrate*elapsed*pelinopeus;
		shipa->motorright=shipa->motorright-powerdownrate*elapsed*pelinopeus;
		if(shipa->motorup<0)shipa->motorup=0;
		if(shipa->motordown<0)shipa->motordown=0;
		if(shipa->motorleft<0)shipa->motorleft=0;
		if(shipa->motorright<0)shipa->motorright=0;
		if(shipa->motorup>500)shipa->motorup=500;
		if(shipa->motordown>500)shipa->motordown=500;
		if(shipa->motorleft>500)shipa->motorleft=500;
		if(shipa->motorright>500)shipa->motorright=500;

	
	//spacestation
	if(shipa->encounter.ship_basea.ship_type==6){
		shipa->vx=shipa->vx+0.0002f*pelinopeus*elapsed;//angle to planet
		shipa->x1=sinf(shipa->vx)*2000*battle.planet.size;
		shipa->z1=cosf(shipa->vx)*2000*battle.planet.size;		
	}
	else{
		shipa->vx=shipa->vx+((sinf(shipa->rx+pi/2)*(-shipa->motorup+shipa->motordown))/shipa->encounter.ship_basea.mass)*elapsed*pelinopeus;
		shipa->vz=shipa->vz+((cosf(shipa->rx+pi/2)*(-shipa->motorup+shipa->motordown))/shipa->encounter.ship_basea.mass)*elapsed*pelinopeus;
		
		if((sqr(shipa->vx)+sqr(shipa->vz))>sqr(2.0f))
		{
			kerroin=sqrtf(sqr(2.0f)/(sqr(shipa->vx)+sqr(shipa->vz)));
			shipa->vx=(shipa->vx)*kerroin;
			shipa->vz=(shipa->vz)*kerroin;	
		}

		shipa->ry=-shipa->vr*0.5f*100;

		shipa->x1=shipa->x1+shipa->vx*elapsed*pelinopeus;
		shipa->z1=shipa->z1+shipa->vz*elapsed*pelinopeus;
	}
	shipa->vr=shipa->vr+((-shipa->motorleft+shipa->motorright)/shipa->encounter.ship_basea.mass-shipa->vr*0.01f)*elapsed*pelinopeus;
	shipa->rx=shipa->rx+shipa->vr*elapsed*pelinopeus;

	if(shipa->rx>pi)shipa->rx=shipa->rx-2*pi;
	if(shipa->rx<-pi)shipa->rx=shipa->rx+2*pi;

	shipa->x3=shipa->x1+(float)(sinf(shipa->rx+pi/2)*40);
	shipa->z3=shipa->z1+(float)(cosf(shipa->rx+pi/2)*40);

	shipa->vangle=atan2f(shipa->vx,shipa->vz);
	shipa->vpowersquare=sqr(shipa->vx)+sqr(shipa->vz);

		if(shipa->left) {		
			while(shipa->motor2time>=0){
				shipa->motor2time=shipa->motor2time-30.0f;		
				generate_particle(0,randDouble(100,300),shipa->x1+cosf(shipa->rx+shipa->encounter.ship_basea.motorangle[1])*shipa->encounter.ship_basea.motordistance[1],0,shipa->z1+sinf(-shipa->rx-shipa->encounter.ship_basea.motorangle[1])*shipa->encounter.ship_basea.motordistance[1],shipa->rx+pi/2+randDouble(-0.1f,0.1f),0,0,shipa->motorleft/(300),shipa->vx,0,shipa->vz);
			}
		}
		if(shipa->right) {		
			while(shipa->motor3time>=0){
				shipa->motor3time=shipa->motor3time-30.0f;		
				generate_particle(0,randDouble(100,300),shipa->x1+cosf(shipa->rx-shipa->encounter.ship_basea.motorangle[1])*shipa->encounter.ship_basea.motordistance[1],0,shipa->z1+sinf(-shipa->rx+shipa->encounter.ship_basea.motorangle[1])*shipa->encounter.ship_basea.motordistance[1],shipa->rx-pi/2+randDouble(-0.1f,0.1f),0,0,shipa->motorright/(300),shipa->vx,0,shipa->vz);
			}
		}

	//not a spacestation
	if(shipa->encounter.ship_basea.ship_type!=6){

		if(shipa->down) {		
			while(shipa->motor0time>=0){
				shipa->motor0time=shipa->motor0time-30.0f;		
				generate_particle(0,randDouble(100,300),shipa->x1+cosf(shipa->rx)*shipa->encounter.ship_basea.motordistance[0],0,shipa->z1+sinf(-shipa->rx)*shipa->encounter.ship_basea.motordistance[0],shipa->rx+randDouble(-0.1f,0.1f),0,0,shipa->motorup/(300),shipa->vx,0,shipa->vz);
			}
		}		
		if(shipa->up) {		
			while(shipa->motor1time>=0){				
				shipa->motor1time=shipa->motor1time-36.0f;		
				//generate_particle(0.0033f,0,randDouble(100,300),shipa->x1+cosf(shipa->rx+0.74f)*-65,0,shipa->z1+sinf(-shipa->rx-0.74f)*-65,shipa->rx+pi+randDouble(-0.1f,0.1f),0,0,shipa->motordown/(300),shipa->vx,0,shipa->vz);
				//generate_particle(0.0033f,0,randDouble(100,300),shipa->x1+cosf(shipa->rx-0.74f)*-65,0,shipa->z1+sinf(-shipa->rx+0.74f)*-65,shipa->rx+pi+randDouble(-0.1f,0.1f),0,0,shipa->motordown/(300),shipa->vx,0,shipa->vz);
			
				for (q=0; q<shipa->encounter.ship_basea.backmotors; q++){
					savusta(0.5f,randDouble(0.3f,0.5f),0.001f,true,randDouble(800,1200),shipa->x1+cosf(shipa->rx+shipa->encounter.ship_basea.motorangle[q+2])*shipa->encounter.ship_basea.motordistance[q+2],1,shipa->z1+sinf(-shipa->rx-shipa->encounter.ship_basea.motorangle[q+2])*shipa->encounter.ship_basea.motordistance[q+2],0,randDouble(-pi,pi),0,0,shipa->vx+cosf(shipa->rx+pi+randDouble(-0.1f,0.1f))*shipa->motordown/(2800),0,shipa->vz+sinf(-shipa->rx+pi+randDouble(-0.1f,0.1f))*shipa->motordown/(2800));			
				}
			}
		}
	}

	//map
	if((pelivaihe==0)&&(pelivaihe2==0)){
		/*//don't go off map
		if(sqrt(sqr(shipa->x1)+sqr(shipa->z1))>65000){
			//if((sqr(bulleta->movement.x)+sqr(bulleta->movement.z))>sqr(2))
			
				float kerroin=sqrtf(sqr(6500)/(sqr(shipa->x1/10)+sqr(shipa->z1/10)));
				shipa->x1=(shipa->x1)*kerroin;
				shipa->z1=(shipa->z1)*kerroin;
				shipa->vx=-shipa->vx;
				shipa->vz=-shipa->vz;
			

		}*/
		//reverse map
		if(shipa->x1<-51500){shipa->x1=51500;warp_timer=5000;}
		if(shipa->x1>51500){shipa->x1=-51500;warp_timer=5000;}
		if(shipa->z1<-66000){shipa->z1=66000;warp_timer=5000;}
		if(shipa->z1>66000){shipa->z1=-66000;warp_timer=5000;}
		//use fuel
		if(shipa->number==0)
		if((shipa->up)||(shipa->down)){
			fueltimer=fueltimer-elapsed*pelinopeus;
			if(fueltimer<0){
				fueltimer=1000;
				shipslot[0].cargo[4]=shipslot[0].cargo[4]-1;
				if(shipslot[0].cargo[4]<0)shipslot[0].cargo[4]=0;
			}
		}
		//not up or down
		/*if((!shipa->up)&&(!shipa->down)){
			if(sqr(shipa->vx)+(sqr(shipa->vz))>0.01f){
				shipa->vx=shipa->vx-shipa->vx*0.002f*elapsed*pelinopeus;
				shipa->vz=shipa->vz-shipa->vz*0.002f*elapsed*pelinopeus;
			}
		}*/
	}

	//battle
	if((pelivaihe==0)&&(pelivaihe2==1)){
		//borders
		if(shipa->x1<-battle.fieldsize){
			shipa->x1=-battle.fieldsize;
			shipa->vx=-shipa->vx*0.5f;
		}
		if(shipa->x1>battle.fieldsize){
			shipa->x1=battle.fieldsize;
			shipa->vx=-shipa->vx*0.5f;
		}
		if(shipa->z1<-battle.fieldsize){
			shipa->z1=-battle.fieldsize;
			shipa->vz=-shipa->vz*0.5f;
		}
		if(shipa->z1>battle.fieldsize){
			shipa->z1=battle.fieldsize;
			shipa->vz=-shipa->vz*0.5f;
		}

	
		//planet
		if(shipa->encounter.ship_basea.ship_type!=6)
		if(battle.type==0){	
			//gravity
			float gravity=11;
			float distancesquare=(sqr(battle.planet.x-shipa->x1)+sqr(battle.planet.z-shipa->z1));
			float angletoship=atan2f(shipa->x1-battle.planet.x,shipa->z1-battle.planet.z);	
			shipa->vx=shipa->vx-sinf(angletoship)*gravity*(100.0f*battle.planet.mass/distancesquare*pelinopeus*elapsed);
			shipa->vz=shipa->vz-cosf(angletoship)*gravity*(100.0f*battle.planet.mass/distancesquare*pelinopeus*elapsed);

			if(distancesquare<sqr((265*5)*battle.planet.size)){
				float temp=(angletoship-((shipa->vangle+pi)-angletoship));
				shipa->vx=sinf(temp)*sqrtf(shipa->vpowersquare);
				shipa->vz=cosf(temp)*sqrtf(shipa->vpowersquare);
				shipa->x1=shipa->x2;
				shipa->z1=shipa->z2;
				float kerroin=sqrtf(sqr((265*5)*battle.planet.size+shipa->encounter.ship_basea.size)/(sqr(shipa->x1)+sqr(shipa->z1)));
				shipa->z1=(shipa->z1)*kerroin;
				shipa->x1=(shipa->x1)*kerroin;
			}
		}

	
	int type;
	//ampuminen	
	if(shipa->one){
		type=0;
		while(shipa->guntime[type]>=0){
			shipa->guntime[type]=shipa->guntime[type]-weapon[shipa->encounter.ship_basea.gun[type]].firerate;
			for (q=0; q<shipa->encounter.ship_basea.number_of_guns[type]; q++)
			shoot(shipa,type,-1,shipa->x1+sinf(shipa->rx+shipa->encounter.ship_basea.gunangle[type][q]+pi/2)*shipa->encounter.ship_basea.gundistance[type][q],0,shipa->z1+cosf(shipa->rx+shipa->encounter.ship_basea.gunangle[type][q]+pi/2)*shipa->encounter.ship_basea.gundistance[type][q],shipa->rx,0,0,shipa->vx,0,shipa->vz);
		}
	}
	if(shipa->two){//shoot(shipa,1,-1,shipa->x1+sinf(shipa->rx+pi/2)*shipa->encounter.ship_basea.motordistance[0],0,shipa->z1+cosf(shipa->rx+pi/2)*shipa->encounter.ship_basea.motordistance[0],shipa->rx,0,0,shipa->vx,0,shipa->vz);
		type=1;
		while(shipa->guntime[type]>=0){
			shipa->guntime[type]=shipa->guntime[type]-weapon[shipa->encounter.ship_basea.gun[type]].firerate;
			for (q=0; q<shipa->encounter.ship_basea.number_of_guns[type]; q++)
			shoot(shipa,type,-1,shipa->x1+sinf(shipa->rx+shipa->encounter.ship_basea.gunangle[type][q]+pi/2)*shipa->encounter.ship_basea.gundistance[type][q],0,shipa->z1+cosf(shipa->rx+shipa->encounter.ship_basea.gunangle[type][q]+pi/2)*shipa->encounter.ship_basea.gundistance[type][q],shipa->rx,0,0,shipa->vx,0,shipa->vz);
		}
	}
	
	}

	//heat
	shipa->heat=shipa->heat-0.015f*elapsed*pelinopeus;
	if(shipa->heat>shipa->encounter.ship_basea.base_heat)shipa->overheat=true;
	if(shipa->overheat)if(shipa->heat<0)shipa->overheat=false;
	if(shipa->heat<0)shipa->heat=0;	

	if(!shipa->overheat){
		if(shipa->guntime[0]<0)shipa->guntime[0]=shipa->guntime[0]+elapsed*pelinopeus;
		if(shipa->guntime[1]<0)shipa->guntime[1]=shipa->guntime[1]+elapsed*pelinopeus;
		if(shipa->guntime[2]<0)shipa->guntime[2]=shipa->guntime[2]+elapsed*pelinopeus;
		if(shipa->guntime[3]<0)shipa->guntime[3]=shipa->guntime[3]+elapsed*pelinopeus;
	}

}

void fly_particles(void){
	if(!options[8])return;
	int q;
	for (q=0; q<maximum_particles; q++){
		if(particle[q].dead)continue;
		particle[q].time=particle[q].time-elapsed*pelinopeus;
		if(particle[q].time<0)particle[q].dead=true;
		
		particle[q].position.x=particle[q].position.x+particle[q].movement.x*elapsed*pelinopeus;
		particle[q].position.y=particle[q].position.y+particle[q].movement.y*elapsed*pelinopeus;
		particle[q].position.z=particle[q].position.z+particle[q].movement.z*elapsed*pelinopeus;

	}
}

void fly_asteroids(asteroidi *asteroidi){
	
	//float asteroid_speed=1.000f;
	float asteroid_rotate_speed=0.15f*0.001f;
	float kerroin;
	float asteroid_mass=100*asteroidi->size*asteroidi->size*asteroidi->size;
	float asteroid_mass2;
	float temp3,temp4;
	int q;
	float distance;
	float energy_transfer=1.0f;
	
	asteroidi->x=asteroidi->x+asteroidi->vx*elapsed*pelinopeus;
	asteroidi->y=asteroidi->y+asteroidi->vy*elapsed*pelinopeus;
	asteroidi->z=asteroidi->z+asteroidi->vz*elapsed*pelinopeus;

	
	asteroidi->sectorx=(int)asteroidi->x/300;
	asteroidi->sectorz=(int)asteroidi->z/300;
	

	asteroidi->distance=(sqr(asteroidi->x-ship[player_controlled_ship].x3)+sqr(asteroidi->z-ship[player_controlled_ship].z3));
		
	if(asteroidi->distance>sqr(500)){
		if(asteroidi->size<0.1f)if(randInt(0,100)==0)asteroidi->dead=true;}
	if(asteroidi->distance>sqr(3000)){
		if(asteroidi->size<0.3f)if(randInt(0,100)==0)asteroidi->dead=true;}

	//if outside of camera range don't calculate collisions
	if(asteroidi->distance>sqr(2100)){
		return;
	}

	
	asteroidi->rx=asteroidi->rx+asteroidi->vrx*elapsed*pelinopeus*asteroid_rotate_speed;
	asteroidi->ry=asteroidi->ry+asteroidi->vry*elapsed*pelinopeus*asteroid_rotate_speed;
	asteroidi->rz=asteroidi->rz+asteroidi->vrz*elapsed*pelinopeus*asteroid_rotate_speed;


	//collisions with the ships
	for (int b=1; b<maximum_ships; b++){
		if(ship[b].dead)continue;
		if(ship[b].disabled)continue;
		if(sqr(asteroidi->x-ship[b].x3)+sqr(asteroidi->z-ship[b].z3)<sqr(asteroid_radius*asteroidi->size+ship[b].encounter.ship_basea.size)){		
			kerroin=0.003f+sqrtf(sqr(asteroid_radius*asteroidi->size+ship[b].encounter.ship_basea.size)/(sqr(asteroidi->x-ship[b].x3)+sqr(asteroidi->z-ship[b].z3)));
			if(kerroin>1.01f)kerroin=1.01f;
			ship[b].z1=(ship[b].z1-asteroidi->z)*kerroin+asteroidi->z;
			ship[b].x1=(ship[b].x1-asteroidi->x)*kerroin+asteroidi->x;

			
			//energy of collision
			if(ship[b].vx<0)temp3=-0.5f*sqr(ship[b].vx)*ship[b].encounter.ship_basea.mass*0.0001f*3;
			else temp3=0.5f*sqr(ship[b].vx)*ship[b].encounter.ship_basea.mass*0.0001f*3;
			if(asteroidi->vx<0)temp3=temp3-0.5f*sqr(asteroidi->vx)*asteroid_mass;
			else temp3=temp3+0.5f*sqr(asteroidi->vx)*asteroid_mass;

			if(ship[b].vz<0)temp4=-0.5f*sqr(ship[b].vz)*ship[b].encounter.ship_basea.mass*0.0001f*3;
			else temp4=0.5f*sqr(ship[b].vz)*ship[b].encounter.ship_basea.mass*0.0001f*3;
			if(asteroidi->vz<0)temp4=temp4-0.5f*sqr(asteroidi->vz)*asteroid_mass;
			else temp4=temp4+0.5f*sqr(asteroidi->vz)*asteroid_mass;
			
			temp3=(float)fabs(temp3);
			temp4=(float)fabs(temp4);

			//bits fly
			for (q=0; q<(int)(sqrt(sqr(temp3)+sqr(temp4))*0.5f); q++){				
				generate_particle(1,randDouble(500,700),ship[b].x1,0,ship[b].z1,randDouble(-pi,pi),0,0,randDouble(0,0.4f),0,0,0);
			}
			float shipmass=(ship[b].encounter.ship_basea.mass*0.0001f*5);

			//movement changes
			kerroin=1;
			if(ship[b].vx>asteroidi->vx)kerroin=-1;		
			ship[b].vx=ship[b].vx+kerroin*sqrtf((2*(temp3/(1+shipmass/asteroid_mass)))/shipmass)*energy_transfer;
			asteroidi->vx=asteroidi->vx-kerroin*sqrtf((2*(temp3/(1+asteroid_mass/shipmass)))/(asteroid_mass))*energy_transfer;
			
			kerroin=1;
			if(ship[b].vz>asteroidi->vz)kerroin=-1;	
			ship[b].vz=ship[b].vz+kerroin*sqrtf((2*(temp4/(1+shipmass/asteroid_mass)))/shipmass)*energy_transfer;
			asteroidi->vz=asteroidi->vz-kerroin*sqrtf((2*(temp4/(1+asteroid_mass/shipmass)))/(asteroid_mass))*energy_transfer;
			
			asteroidi->vrx=asteroidi->vx*50;
			asteroidi->vry=asteroidi->vy*50;
			asteroidi->vrz=asteroidi->vz*50;

		}
	}


	//with asteroids
	for (q=0; q<maksimiasteroid; q++){
		if(asteroid[q].dead)continue;
		if(abs(asteroidi->sectorx-asteroid[q].sectorx)>2)continue;
		if(abs(asteroidi->sectorz-asteroid[q].sectorz)>2)continue;
		if(asteroidi->number==q)continue;
		distance=(sqr(asteroidi->x-asteroid[q].x)+sqr(asteroidi->z-asteroid[q].z));
		if(distance<sqr(asteroid_radius*asteroidi->size+asteroid_radius*asteroid[q].size)){	

			asteroid_mass2=100*asteroid[q].size*asteroid[q].size*asteroid[q].size;
			
			kerroin=0.004f+sqrtf(sqr(asteroid_radius*asteroidi->size+asteroid_radius*asteroid[q].size)/(sqr(asteroidi->x-asteroid[q].x)+sqr(asteroidi->z-asteroid[q].z)));		
			asteroid[q].z=(asteroid[q].z-asteroidi->z)*kerroin+asteroidi->z;
			asteroid[q].x=(asteroid[q].x-asteroidi->x)*kerroin+asteroidi->x;
						
			temp3=(0.5f*sqr(asteroid[q].vx)*asteroid_mass2+0.5f*sqr(asteroidi->vx)*asteroid_mass);
			temp4=(0.5f*sqr(asteroid[q].vz)*asteroid_mass2+0.5f*sqr(asteroidi->vz)*asteroid_mass);

			kerroin=1;
			if(asteroid[q].vx>asteroidi->vx)kerroin=-1;		
			asteroid[q].vx=asteroid[q].vx+kerroin*sqrtf((2*(temp3/(1+asteroid_mass2/asteroid_mass)))/asteroid_mass2)*energy_transfer;
			asteroidi->vx=asteroidi->vx-kerroin*sqrtf((2*(temp3/(1+asteroid_mass/asteroid_mass2)))/(asteroid_mass))*energy_transfer;
			
			kerroin=1;
			if(asteroid[q].vz>asteroidi->vz)kerroin=-1;	
			asteroid[q].vz=asteroid[q].vz+kerroin*sqrtf((2*(temp4/(1+asteroid_mass2/asteroid_mass)))/asteroid_mass2)*energy_transfer;
			asteroidi->vz=asteroidi->vz-kerroin*sqrtf((2*(temp4/(1+asteroid_mass/asteroid_mass2)))/(asteroid_mass))*energy_transfer;
			
			asteroidi->vrx=asteroidi->vx*50;
			asteroidi->vry=asteroidi->vy*50;
			asteroidi->vrz=asteroidi->vz*50;

			asteroid[q].vrx=asteroid[q].vx*50;
			asteroid[q].vry=asteroid[q].vy*50;
			asteroid[q].vrz=asteroid[q].vz*50;
		}
	}
}

void generate_particle(int picture, float aika, float paikkax,float paikkay,float paikkaz,float suuntax,float suuntay,float suuntaz,float speed,float vx,float vy,float vz)//particle animation starter
{	
	if(!options[8])return;
	int a,b,q;
	int d=-1;

	{
		for (q=0; q<1; q++){

			a=0;
			b=0;
					alku2:
					a=randInt(0,maximum_particles);
					b=b+1;
					if(b>maximum_particles)particle[a].dead=true;
					if(!particle[a].dead)goto alku2;
		d=a;
		
		ZeroMemory(&particle[a], sizeof(particles));
		particle[a].dead=false;
		particle[a].position.x=paikkax;
		particle[a].position.y=paikkay;
		particle[a].position.z=paikkaz;
		particle[a].movement.x=(float)cos(suuntax)*speed+vx;
		particle[a].movement.y=randDouble(-0.1f,0.1f);//(float)sin(suuntay)*speed+vy;
		particle[a].movement.z=(float)sin(-suuntax)*speed+vz;
		particle[a].time=aika;
		particle[a].picture=picture;
		
	
		}
	}	
}


void shoot(shipbase *shooter, int type, float time, float placex,float placey,float placez,float directionx,float directiony,float directionz,float vx,float vy,float vz)//fire a bullet
{	
	int a,b,q;
	int d=-1;	

	//while(shooter->guntime[type]>=0){
	{

		//determine target
		int temp1=-1;
		float shooterangle;
		shooterangle=shooter->rx;
		if(weapon[shooter->encounter.ship_basea.gun[type]].bulletspeed<0)shooterangle=shooterangle+pi;

		for (q=1; q<maximum_ships; q++){
			if(q==shooter->number)continue;
			if(ship[q].dead)continue;
			if(ship[q].disabled)continue;
			if(ship[q].side==shooter->side)continue;
			float angletoship=atan2f(shooter->x1-ship[q].x1,shooter->z1-ship[q].z1)+pi/2;
			if(fabs(fabs(angletoship)-fabs(shooterangle))<0.7f)//if angle is small enough
			{
				if(temp1==-1){temp1=q;continue;}
				if(fabs(fabs(angletoship)-fabs(shooterangle))<0.6f)//if new angle is small enough
				{
					if((sqr(ship[q].x1-shooter->x1)+sqr(ship[q].z1-shooter->z1))<(sqr(ship[temp1].x1-shooter->x1)+sqr(ship[temp1].z1-shooter->z1)))//if previous is farther
					temp1=q;
				}
				else temp1=q;
			}
		}
		


		//smoking barrels
		generate_particle(1,randDouble(100,300),placex,placey,placez,shooterangle,0,0,randDouble(0,0.2f),shooter->vx,0,shooter->vz);
		//shooter->guntime[type]=shooter->guntime[type]-weapon[shooter->encounter.ship_basea.gun[type]].firerate;
		

		for (q=0; q<1; q++){
			//päätetään minkä luodin paikalle tulee uusi

			a=0;
			b=0;
					alku2:
					a=randInt(0,maximum_bullets);
					b=b+1;
					if(b>maximum_bullets)bullet[a].dead=true;
					if(!bullet[a].dead)goto alku2;
		d=a;

		ZeroMemory(&bullet[a], sizeof(bulletbase));
		//mopot->asetime[aseena]=mopot->asetime[aseena]-ase[mopot->ase[aseena]].ampumanopeus;
		bullet[a].target=temp1;
		bullet[a].dead=false;
		bullet[a].position.x=placex;
		bullet[a].position.y=placey;
		bullet[a].position.z=placez;		
		bullet[a].movement.x=(float)cos(directionx)*weapon[shooter->encounter.ship_basea.gun[type]].bulletspeed+vx;
		bullet[a].movement.y=0;
		bullet[a].movement.z=(float)sin(-directionx)*weapon[shooter->encounter.ship_basea.gun[type]].bulletspeed+vz;
		//if bullet doesn't want to move, don't move it
		if(weapon[shooter->encounter.ship_basea.gun[type]].bulletspeed==0){
			bullet[a].movement.x=0;
			bullet[a].movement.y=0;
			bullet[a].movement.z=0;
		}
		bullet[a].rotate.x=shooterangle;
		bullet[a].rotate.y=shooter->ry;
		bullet[a].rotate.z=shooter->rz;
		bullet[a].time=time;
		bullet[a].fromweapon=shooter->encounter.ship_basea.gun[type];
		bullet[a].shooter=shooter->number;
		bullet[a].power=1;
		shooter->heat=shooter->heat+weapon[shooter->encounter.ship_basea.gun[type]].heat;

		playsound(weapon[shooter->encounter.ship_basea.gun[type]].sound_launch,1,placex,placez,ship[player_controlled_ship].x1,ship[player_controlled_ship].z1);
		
		

	
		}
	}	
}

void fly_bullet(bulletbase *bulleta)
{
	bulleta->power=bulleta->power-elapsed*pelinopeus*weapon[bulleta->fromweapon].powerdownrate;
	if(bulleta->power<=0){bulleta->dead=true;return;}
	bulleta->position2=bulleta->position;
	bulleta->position.x=bulleta->position.x+bulleta->movement.x*elapsed*pelinopeus;
	bulleta->position.y=bulleta->position.y+bulleta->movement.y*elapsed*pelinopeus;
	bulleta->position.z=bulleta->position.z+bulleta->movement.z*elapsed*pelinopeus;

	bulleta->sectorx=(int)bulleta->position.x/300;
	bulleta->sectorz=(int)bulleta->position.z/300;

	//rotate silly looking bullets
	switch (weapon[bulleta->fromweapon].bulletpicture)
		{
			//case 0:{draw(1,1,1,&mallit[0].malli[3]);break;}
			case 1:{
				bulleta->rotate.x=randDouble(-pi,pi);
				break;
				   }
			case 2:{
				bulleta->rotate.x=bulleta->rotate.x+0.04f*elapsed*pelinopeus;
				bulleta->rotate.y=bulleta->rotate.y+0.04f*elapsed*pelinopeus;
				bulleta->rotate.z=bulleta->rotate.z+0.04f*elapsed*pelinopeus;
				break;
				   }
			case 4:{
				bulleta->rotate.x=randDouble(-pi,pi);
				break;
				   }
			case 5:{
				bulleta->rotate.y=bulleta->rotate.y+0.05f*elapsed*pelinopeus;
				break;
				   }

		}


	//movement smoke
	if(weapon[bulleta->fromweapon].movement_smoke>0){
		if(randInt(0,1+(int)(weapon[bulleta->fromweapon].movement_smoke/(elapsed*pelinopeus)))==0){
			generate_particle(1,randDouble(100,300),bulleta->position.x,0,bulleta->position.z,bulleta->movement.x/2,0,bulleta->movement.z/2,0,0,0,0);
			//generate_particle(0,randDouble(100,300),bulleta->position.x,0,bulleta->position.z,bulleta->movement.x/2,0,bulleta->movement.z/2,0,0,0,0);
		}
	}

	//tracking
	if((bulleta->target!=-1)&&(weapon[bulleta->fromweapon].tracking)&&(!ship[bulleta->target].dead)){		
		if(bulleta->position.x<ship[bulleta->target].x1){
			bulleta->movement.x=bulleta->movement.x+elapsed*pelinopeus*5*0.001f;
		}
		else bulleta->movement.x=bulleta->movement.x-elapsed*pelinopeus*5*0.001f;
		if(bulleta->position.z<ship[bulleta->target].z1){
			bulleta->movement.z=bulleta->movement.z+elapsed*pelinopeus*5*0.001f;
		}
		else bulleta->movement.z=bulleta->movement.z-elapsed*pelinopeus*5*0.001f;

		//rotate bullet
		bulleta->rotate.x=atan2f(bulleta->movement.x,bulleta->movement.z)-pi/2;
	}

	//tracking bullets don't go too fast
	if(weapon[bulleta->fromweapon].tracking)
	if((sqr(bulleta->movement.x)+sqr(bulleta->movement.z))>sqr(2))
		{
			float kerroin=sqrtf(sqr(2)/(sqr(bulleta->movement.x)+sqr(bulleta->movement.z)));
			bulleta->movement.x=(bulleta->movement.x)*kerroin;
			bulleta->movement.z=(bulleta->movement.z)*kerroin;	
		}

	
	bulleta->distancesquare=sqr(bulleta->position.x-ship[player_controlled_ship].x3)+sqr(bulleta->position.z-ship[player_controlled_ship].z3);
	
	if(bulleta->distancesquare>sqr(15000)){bulleta->dead=true;return;}

	//float kk=-(bulleta->position2.x-bulleta->position.x)/(bulleta->position2.z-bulleta->position.z);
	
	int q,a;
	bool osuma;
	float osumax,osumaz;
	float asteroid_piece;

	float rad;
	if((bulleta->movement.x==0)&&(bulleta->movement.z==0))return;

	//hits ships
	for (q=1; q<maximum_ships; q++){
		if(ship[q].dead)continue;
		if((sqr(bulleta->position.x-ship[q].x3)+sqr(bulleta->position.z-ship[q].z3))>sqr(ship[q].encounter.ship_basea.size+fabs(weapon[bulleta->fromweapon].bulletspeed)*elapsed*pelinopeus))continue;
		if(ship[bulleta->shooter].side==ship[q].side)continue;
		//if(bulleta->shooter==q)continue;
		
		rad=ship[q].encounter.ship_basea.size;
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position2.x,bulleta->position2.z,bulleta->position.x,bulleta->position.z,ship[q].x3,ship[q].z3+rad,ship[q].x3-rad,ship[q].z3))goto osuma1;
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position2.x,bulleta->position2.z,bulleta->position.x,bulleta->position.z,ship[q].x3,ship[q].z3-rad,ship[q].x3+rad,ship[q].z3))goto osuma1;
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position.x,bulleta->position.z,bulleta->position2.x,bulleta->position2.z,ship[q].x3+rad,ship[q].z3,ship[q].x3,ship[q].z3+rad))goto osuma1;		
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position.x,bulleta->position.z,bulleta->position2.x,bulleta->position2.z,ship[q].x3-rad,ship[q].z3,ship[q].x3,ship[q].z3-rad))goto osuma1;
		
		continue;

		osuma1:
		ship[q].shotlast_me=bulleta->shooter;//who shot me last
		ship[bulleta->shooter].shotlast_enemy=q;//who I shot last

		//damage
		if(options[4]){//easy mode
			if(ship[q].side==0)ship[q].energy=ship[q].energy-weapon[bulleta->fromweapon].damage*bulleta->power*randDouble(0.5f,1.0f)*0.75f;
			else ship[q].energy=ship[q].energy-weapon[bulleta->fromweapon].damage*bulleta->power*randDouble(0.5f,1.0f)*1.15f;
		}
		else ship[q].energy=ship[q].energy-weapon[bulleta->fromweapon].damage*bulleta->power*randDouble(0.5f,1.0f);
		bulleta->dead=true;

		//sound
		playsound(weapon[bulleta->fromweapon].sound_hit,1,osumax,osumaz,ship[player_controlled_ship].x1,ship[player_controlled_ship].z1);

		//disable ship
		if((ship[q].energy>0)&&(ship[q].energy<10)){
			if(randInt(0,5)==0)
				ship[q].disabled=true;
		}

		//particles from ship
		for (a=0; a<15; a++){
			generate_particle(1,randDouble(1800,3500)*bulleta->power,osumax,0,osumaz,bulleta->rotate.x+randDouble(-0.2f,0.2f),0,0,randDouble(0.2f,0.8f),0,0,0);
		}
		//räjähdys
		for (a=0; a<weapon[bulleta->fromweapon].collision_explosion; a++){savusta(1.0f,randDouble(0.7f,1.8f)*bulleta->power, randDouble(0.015f,0.021f)*bulleta->power,true,randDouble(400,900),osumax+randDouble(-10,10),0,osumaz+randDouble(-10,10),0,randDouble(-pi,pi),0,0,0,0,0);}
		//savuaa
		for (a=0; a<weapon[bulleta->fromweapon].collision_smoke; a++){savusta(0.6f,randDouble(0.6f,1.8f)*bulleta->power, 0.012f*bulleta->power,true,randDouble(1500,2500),osumax,0,osumaz,2,randDouble(-pi,pi),0,0,randDouble(-0.05f,0.05f),0,randDouble(-0.05f,0.05f));}

		return;
	}
	
	if(bulleta->distancesquare>sqr(2000))return;

	if(battle.type==0){
	//hits planet
	rad=((265*5)*battle.planet.size);
	if((sqr(bulleta->position.x)+sqr(bulleta->position.z))>sqr(rad+fabs(weapon[bulleta->fromweapon].bulletspeed)*elapsed*pelinopeus))goto next;
	float xa[13];
	float za[13];
		xa[0]=1.0000f;	za[0]=0.0000f;	
		xa[1]=0.8634f;	za[1]=0.5045f;	
		xa[2]=0.5045f;	za[2]=0.8634f;	
		xa[3]=-0.0000f;	za[3]=1.0000f;
		xa[4]=-0.5045f;	za[4]=0.8634f;
		xa[5]=-0.8634f;	za[5]=0.5045f;
		xa[6]=-1.0000f;	za[6]=-0.0000f;	
		xa[7]=-0.8634f;	za[7]=-0.5045f;
		xa[8]=-0.5045f;	za[8]=-0.8634f;
		xa[9]=0.0000f;	za[9]=-1.0000f;	
		xa[10]=0.5045f;	za[10]=-0.8634f;
		xa[11]=0.8634f;	za[11]=-0.5045f;
		xa[12]=1.0000f;	za[12]=0.0000f;
	for (q=0; q<12; q++){
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position2.x,bulleta->position2.z,bulleta->position.x,bulleta->position.z,xa[q]*rad,za[q]*rad,xa[q+1]*rad,za[q+1]*rad))goto osuma2;
	}
	if((sqr(bulleta->position.x)+sqr(bulleta->position.z))<sqr(rad)){
		osumax=bulleta->position.x;
		osumaz=bulleta->position.z;
		goto osuma2;
	}

		goto next;
		osuma2:
		{

			//rotate bullet
			bulleta->rotate.x=atan2f(bulleta->movement.x,bulleta->movement.z)-pi/2;

			//particles from planet
			float temp1=atan2f(osumax-battle.planet.x,osumaz-battle.planet.z);
			float temp=(temp1-((bulleta->rotate.x)-temp1));
			for (a=0; a<weapon[bulleta->fromweapon].damage*bulleta->power*3; a++){
					generate_particle(1,randDouble(1800,3500)*bulleta->power,osumax,0,osumaz,temp+randDouble(-0.2f,0.2f),0,0,randDouble(0.2f,0.8f),0,0,0);
			}

			bulleta->dead=true;

			//sound
			playsound(weapon[bulleta->fromweapon].sound_hit,1,osumax,osumaz,ship[player_controlled_ship].x1,ship[player_controlled_ship].z1);

			//räjähdys
			for (a=0; a<weapon[bulleta->fromweapon].collision_explosion; a++){savusta(1.0f,randDouble(0.7f,1.8f)*bulleta->power, randDouble(0.015f,0.021f)*bulleta->power,true,randDouble(400,900),osumax+randDouble(-10,10),0,osumaz+randDouble(-10,10),0,randDouble(-pi,pi),0,0,0,0,0);}
			//savuaa
			for (a=0; a<weapon[bulleta->fromweapon].collision_smoke; a++){savusta(0.6f,randDouble(0.6f,1.8f)*bulleta->power, 0.012f*bulleta->power,true,randDouble(1500,2500),osumax,0,osumaz,2,randDouble(-pi,pi),0,0,randDouble(-0.05f,0.05f),0,randDouble(-0.05f,0.05f));}
		}
		next:;
	}
	//hits asteroids
	for (q=0; q<maksimiasteroid; q++){
		if(asteroid[q].dead)continue;
		if(abs(bulleta->sectorx-asteroid[q].sectorx)>2)continue;
		if(abs(bulleta->sectorz-asteroid[q].sectorz)>2)continue;	
		if((sqr(bulleta->position.x-asteroid[q].x)+sqr(bulleta->position.z-asteroid[q].z))>sqr(asteroid_radius*asteroid[q].size+fabs(weapon[bulleta->fromweapon].bulletspeed)*elapsed*pelinopeus))continue;

		rad=asteroid_radius*asteroid[q].size;
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position2.x,bulleta->position2.z,bulleta->position.x,bulleta->position.z,asteroid[q].x,asteroid[q].z+rad,asteroid[q].x-rad,asteroid[q].z))goto osuma;
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position2.x,bulleta->position2.z,bulleta->position.x,bulleta->position.z,asteroid[q].x,asteroid[q].z-rad,asteroid[q].x+rad,asteroid[q].z))goto osuma;
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position.x,bulleta->position.z,bulleta->position2.x,bulleta->position2.z,asteroid[q].x+rad,asteroid[q].z,asteroid[q].x,asteroid[q].z+rad))goto osuma;		
		if(viivaviiva(true,&osuma,&osumax,&osumaz,bulleta->position.x,bulleta->position.z,bulleta->position2.x,bulleta->position2.z,asteroid[q].x-rad,asteroid[q].z,asteroid[q].x,asteroid[q].z-rad))goto osuma;
		
		continue;

		osuma:
		{
			//räjähdys
			for (a=0; a<weapon[bulleta->fromweapon].collision_explosion; a++){savusta(1.0f,randDouble(0.7f,1.8f)*bulleta->power, randDouble(0.015f,0.021f)*bulleta->power,true,randDouble(400,900),osumax+randDouble(-10,10),0,osumaz+randDouble(-10,10),0,randDouble(-pi,pi),0,0,0,0,0);}
			//savuaa
			for (a=0; a<weapon[bulleta->fromweapon].collision_smoke; a++){savusta(0.6f,randDouble(0.6f,1.8f)*bulleta->power, 0.012f*bulleta->power,true,randDouble(1500,2500),osumax,0,osumaz,2,randDouble(-pi,pi),0,0,randDouble(-0.05f,0.05f),0,randDouble(-0.05f,0.05f));}

			//luoti häviää
			bulleta->dead=true;	
			
			//sound
			playsound(weapon[bulleta->fromweapon].sound_hit,1,osumax,osumaz,ship[player_controlled_ship].x1,ship[player_controlled_ship].z1);

			if(asteroid[q].size<0.7f){
				asteroid[q].dead=true;
				//palaset lentää
				for (a=0; a<35; a++){
					generate_particle(1,randDouble(800,1500)*bulleta->power,osumax,0,osumaz,randDouble(-pi,pi),0,0,randDouble(0,0.3f),0,0,0);
				}
			}
			else{
				//asteroidista palanen irti			
				asteroid_piece=randDouble(0.2f,0.5f)*(bulleta->power*weapon[bulleta->fromweapon].damage)/10;
				if(asteroid_piece<0.01f)return;
				if(asteroid_piece>0.5f)asteroid_piece=0.5f;
				

				for (a=0; a<(int)(1/asteroid_piece)+1; a++){
					if(asteroid[q].size*asteroid_piece>randDouble(0.15f,0.31f))
						shoot_asteroid(randInt(1,3), asteroid[q].size*asteroid_piece, asteroid[q].type, bulleta->position2.x, asteroid[q].y, bulleta->position2.z, randDouble(-pi,pi), randDouble(-pi,pi), randDouble(-pi,pi), asteroid[q].vx+randDouble(-0.1f,0.1f), asteroid[q].vy, asteroid[q].vz+randDouble(-0.1f,0.1f),randDouble(-0.1f,0.1f),randDouble(-0.1f,0.1f),randDouble(-0.1f,0.1f));			
					else{
						generate_particle(1,randDouble(300,700)*bulleta->power,osumax,0,osumaz,randDouble(-pi,pi),0,0,randDouble(0,0.5f),0,0,0);
						if(randInt(0,3)==0)generate_particle(0,randDouble(300,700)*bulleta->power,osumax,0,osumaz,randDouble(-pi,pi),0,0,randDouble(0,0.5f),0,0,0);
					}
				}
				
				asteroid[q].size=asteroid[q].size*(1-asteroid_piece);
				asteroid[q].vx=asteroid[q].vx+randDouble(-0.02f,0.02f);
				asteroid[q].vz=asteroid[q].vz+randDouble(-0.02f,0.02f);
			
			}
			return;
		}

	}


}

void shoot_asteroid(int picture, float size, int type, float x, float y, float z, float rx, float ry, float rz, float vx, float vy, float vz, float vrx, float vry, float vrz){

	int a,b;
	int d=-1;


			a=0;
			b=0;
					alku2:
					a=randInt(0,maksimiasteroid);
					b=b+1;					
					if(b>maksimiasteroid)asteroid[a].dead=true;
					if(!asteroid[a].dead)goto alku2;
			//d=a;

				ZeroMemory(&asteroid[a], sizeof(asteroidi));
				asteroid[a].number=a;
				asteroid[a].x=x;
				asteroid[a].y=y;
				asteroid[a].z=z;
				asteroid[a].rx=rx;
				asteroid[a].ry=ry;
				asteroid[a].rz=rz;
				asteroid[a].vx=vx;
				asteroid[a].vy=vy;
				asteroid[a].vz=vz;
				asteroid[a].vrx=vrx;
				asteroid[a].vry=vry;
				asteroid[a].vrz=vrz;
				asteroid[a].type=type;
				asteroid[a].picture=picture;
				asteroid[a].size=size;
				asteroid[a].dead=false;
			
}

void renderbattle(void){
	
	int q,a;
	battle.side[0]=0;
	battle.side[1]=0;
	for (q=1; q<maximum_ships; q++){
			if(ship[q].dead)continue;
			if(ship[q].disabled)continue;
			fly(&ship[q]);
			battle.side[ship[q].side]++;
	}

	//which side wins
	if(pelivaihe2==1){
		if(battle.side[0]==0)end_battle(1,battle.type);
		if(battle.side[1]==0)end_battle(0,battle.type);
	}

	for (q=0; q<maksimiasteroid; q++){
			if(asteroid[q].dead)continue;
				fly_asteroids(&asteroid[q]);
	}
	for (q=1; q<maximum_ships; q++){
			if(ship[q].dead)continue;
			if(q==player_controlled_ship)continue;
			computer_think(&ship[q]);
			//fly(&battle.ship[q]);
	}

	for (q=0; q<maximum_bullets; q++){
		if(bullet[q].dead)continue;
		fly_bullet(&bullet[q]);
	}

	/*//onko pelaaja alueen ulkopuolella
		if(ship[0].x1<-battle.fieldsize)end_battle(2,0);
		if(ship[0].x1>battle.fieldsize)end_battle(2,0);
		if(ship[0].z1<-battle.fieldsize)end_battle(2,0);
		if(ship[0].z1>battle.fieldsize)end_battle(2,0);
	*/

	//kamera
		kamerax1=ship[player_controlled_ship].x1+100;
		kameray1=cameraheight;
		kameraz1=ship[player_controlled_ship].z1;
		kamerax2=ship[player_controlled_ship].x1;
		kameray2=0;
		kameraz2=ship[player_controlled_ship].z1;


		
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
		D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );
		m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

		

	q=0;
	//maailman valo
	
	ZeroMemory(&lamppu[0].valo, sizeof(D3DLIGHT8));
	
	lamppu[0].valo.Position.y = 0;
	lamppu[0].valo.Position.x = ship[0].x1;
	lamppu[0].valo.Position.z = ship[0].z1;
	lamppu[0].valo.Range = 50000;
	lamppu[0].valo.Diffuse.r = 1;    
	lamppu[0].valo.Diffuse.g = 1;
	lamppu[0].valo.Diffuse.b = 1;    
	lamppu[0].valo.Ambient.r = 0.5f;
	lamppu[0].valo.Ambient.g = 0.5f;    
	lamppu[0].valo.Ambient.b = 0.5f;
	lamppu[0].valo.Specular.r = 1.0f;    
	lamppu[0].valo.Specular.g = 1.0f;
	lamppu[0].valo.Specular.b = 1.0f;
	lamppu[0].valo.Type=D3DLIGHT_POINT;
	lamppu[0].valo.Attenuation0=0;
	lamppu[0].valo.Attenuation1=0;
	lamppu[0].valo.Attenuation2=0.1f/10000;
	m_pDevice->SetLight(0, &lamppu[0].valo);
	m_pDevice->LightEnable(0, TRUE);

	//m_pDevice->SetRenderState( D3DRS_AMBIENT, 0xFFFFEEEE);
	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	//asteroidit aluksen tasolla
	//näkyykö?
	for (a=0; a<maksimiasteroid; a++){
			if(asteroid[a].dead)continue;
			if(asteroid[a].distance<sqr(2000*(cameraheight*0.00022f)))asteroid[a].visible=true;
			else asteroid[a].visible=false;
	}

	for (q=0; q<maksimiasteroid; q++){
		if(asteroid[q].dead)continue;
		if(!asteroid[q].visible){continue;}
		matriisi->LoadIdentity();
		matriisi->TranslateLocal(asteroid[q].x,asteroid[q].y,asteroid[q].z);			
		matriisi->RotateYawPitchRollLocal(asteroid[q].rx,asteroid[q].ry,asteroid[q].rz);			
		matriisi->ScaleLocal(asteroid[q].size,asteroid[q].size,asteroid[q].size);
		lamppu[0].valo.Position.x = asteroid[q].x+100*asteroid[q].size*battle.sunx;
		lamppu[0].valo.Position.z = asteroid[q].z-100*asteroid[q].size*battle.sunz;
		m_pDevice->SetLight(0, &lamppu[0].valo);
		
		switch (asteroid[q].picture) 
			{
			case 0:{drawfast(&mallit[1].malli[4]);break;}
			case 1:{drawfast(&mallit[1].malli[5]);break;}
			case 2:{drawfast(&mallit[1].malli[6]);break;}
			/*case 3:{drawfast(&mallit[1].malli[7]);break;}
			case 4:{drawfast(&mallit[1].malli[8]);break;}*/
		}
	}


	//playfield lines
	pvertex vert[8];
	vert[0].position.x=-battle.fieldsize;
	vert[0].position.z=-battle.fieldsize;
	vert[1].position.x=battle.fieldsize;
	vert[1].position.z=-battle.fieldsize;
	vert[2].position.x=battle.fieldsize;
	vert[2].position.z=-battle.fieldsize;
	vert[3].position.x=battle.fieldsize;
	vert[3].position.z=battle.fieldsize;
	vert[4].position.x=battle.fieldsize;
	vert[4].position.z=battle.fieldsize;
	vert[5].position.x=-battle.fieldsize;
	vert[5].position.z=battle.fieldsize;
	vert[6].position.x=-battle.fieldsize;
	vert[6].position.z=battle.fieldsize;
	vert[7].position.x=-battle.fieldsize;
	vert[7].position.z=-battle.fieldsize;

	for (q=0; q<8; q++){		
		vert[q].position.y=0;	
		vert[q].u=0.35f;
		vert[q].v=1;
	}

	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
	matriisi->LoadIdentity();
	m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());
	m_pDevice->SetMaterial( &mat[7] );
	m_pDevice->SetTexture( 0, tausta[7]);
	m_pDevice->SetRenderState(D3DRS_ZENABLE ,FALSE);
	m_pDevice->SetVertexShader( D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) );	
	m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST   ,4,vert,sizeof(pvertex));	



	
	//planeetta
	float planetsize=100;
	if(battle.type==0){
		m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
		//if(planet[q].distancesquare>(sqr(2400)+sqr(450*planet[q].size))){continue;}		
			
		//matriisi->LoadIdentity();
		D3DXMATRIX tempmatrix;
		D3DXPLANE plane;
		D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
		D3DXMatrixShadow(&tempmatrix,&D3DXVECTOR4(0,4200,0,0),&plane);
		matriisi->LoadMatrix(&tempmatrix);	
		//matriisi->RotateYawPitchRollLocal(-pi/2,0,0);
		//matriisi->TranslateLocal(battle.planet.x,battle.planet.y,battle.planet.z);	
		matriisi->RotateYawPitchRollLocal(battle.planet.rx,battle.planet.ry,battle.planet.rz);					
		matriisi->ScaleLocal(planetsize,planetsize,planetsize);	
		m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);		
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
		drawfast(&mallit[1].malli[battle.planet.picture]);

			
		//planeetan varjo
		if(battle.planet.shadow==0){
			m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,FALSE);		
			matriisi->LoadIdentity();			
			matriisi->RotateYawPitchRollLocal(battle.planet.angletosun,0,0);			
			matriisi->ScaleLocal(planetsize*battle.planet.size,1,planetsize*battle.planet.size);
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO    );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_SRCCOLOR);				
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);	
			matriisi->RotateYawPitchRollLocal(0,pi/2,0);
			draw(1.0f,1.0f,1.0f,&mallit[1].malli[24]);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
		}
		
		
		//ilmakehä / rengas
		if(battle.planet.atmosphere!=-1){
			m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
			matriisi->LoadIdentity();			
			matriisi->RotateYawPitchRollLocal(battle.planet.rx,battle.planet.ry,battle.planet.rz);			
			matriisi->ScaleLocal(planetsize,planetsize,planetsize);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);	
			matriisi->RotateYawPitchRollLocal(0,battle.planet.ry,0);
			draw(0.3f,0.3f,0.3f,&mallit[1].malli[battle.planet.atmosphere]);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
		}

		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
		m_pDevice->SetRenderState(D3DRS_ZENABLE ,FALSE);

		

	}

	
	
	
	//bullets
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );	
	m_pDevice->SetRenderState(D3DRS_AMBIENT, 0x00FFFFFF);
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);
	for (q=0; q<maximum_bullets; q++){
		if(bullet[q].dead)continue;	
		if(bullet[q].distancesquare>sqr(2000*(cameraheight*0.00022f)))continue;
		matriisi->LoadIdentity();	
		matriisi->TranslateLocal(bullet[q].position.x,0,bullet[q].position.z);	
		matriisi->RotateYawPitchRollLocal(bullet[q].rotate.x,bullet[q].rotate.y+pi/2,bullet[q].rotate.z);
		matriisi->ScaleLocal(bullet[q].power,bullet[q].power,bullet[q].power);
		switch (weapon[bullet[q].fromweapon].bulletpicture)
		{
			case 0:{
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
				draw(1,1,1,&mallit[0].malli[3]);break;}
			case 1:{
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
				matriisi->RotateYawPitchRollLocal(pi/2,0,0);
				matriisi->ScaleLocal(1,1,1);
				draw(1,1,1,&mallit[0].malli[12]);
				break;
				   }
			case 2:{
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
				drawfast(&mallit[1].malli[6]);
				break;}
			case 3:{
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
				matriisi->RotateYawPitchRollLocal(pi/2,0,0);
				drawfast(&mallit[0].malli[13]);break;}
			case 4:{
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
				matriisi->RotateYawPitchRollLocal(pi/2,0,0);
				matriisi->ScaleLocal(1,1,1);
				draw(1,1,1,&mallit[0].malli[14]);
				break;				
				   }
			case 5:{
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
				matriisi->RotateYawPitchRollLocal(pi/2,pi,pi);
				matriisi->ScaleLocal(3,3,3);
				drawfast(&mallit[0].malli[15]);break;}
		}
	}


	//ships 
	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);	
	m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pDevice->LightEnable(0, TRUE);
	m_pDevice->LightEnable(1, TRUE);
	//light
	ZeroMemory(&lamppu[0].valo, sizeof(D3DLIGHT8));	
	lamppu[0].valo.Range = 10000;
	lamppu[0].valo.Diffuse.r = 1;    
	lamppu[0].valo.Diffuse.g = 1;
	lamppu[0].valo.Diffuse.b = 1;    
	lamppu[0].valo.Ambient.r = 0.16f;
	lamppu[0].valo.Ambient.g = 0.16f;    
	lamppu[0].valo.Ambient.b = 0.16f;
	lamppu[0].valo.Specular.r = 1.0f;    
	lamppu[0].valo.Specular.g = 1.0f;
	lamppu[0].valo.Specular.b = 1.0f;
	lamppu[0].valo.Type=D3DLIGHT_POINT;
	lamppu[0].valo.Attenuation0=1;
	lamppu[0].valo.Attenuation1=0;
	lamppu[0].valo.Attenuation2=0;

	for (q=1; q<maximum_ships; q++){
		if(ship[q].dead)continue;
		if(sqr(ship[q].x1-ship[player_controlled_ship].x1)+sqr(ship[q].z1-ship[player_controlled_ship].z1)>sqr(2000*(cameraheight*0.00022f)))continue;
		
		//valo1
		lamppu[0].valo.Position.x = ship[q].x1-2000;
		lamppu[0].valo.Position.y = 2500;
		lamppu[0].valo.Position.z = ship[q].z1-2000;		
		m_pDevice->SetLight(0, &lamppu[0].valo);
		//valo2
		lamppu[0].valo.Position.x = ship[q].x1+1000;
		lamppu[0].valo.Position.y = 2000;
		lamppu[0].valo.Position.z = ship[q].z1+2500;
		m_pDevice->SetLight(1, &lamppu[0].valo);
		matriisi->LoadIdentity();
		matriisi->TranslateLocal(ship[q].x1,ship[q].y1,ship[q].z1);			
		matriisi->RotateYawPitchRollLocal(ship[q].rx,ship[q].ry,ship[q].rz);


		//low poly models
		int model=ship[q].encounter.ship_basea.picture;
		if(!options[2])
		switch (model)
		{
			case 0:model=6;break;
			case 1:model=7;break;
			case 2:model=8;break;
			case 3:model=9;break;
			case 4:model=10;break;
			case 13:model=11;break;
			case 12:model=12;break;
			case 5:model=14;break;
		}
		
		
		//disabled
		if((ship[q].disabled)){
			m_pDevice->LightEnable(0, FALSE);
			m_pDevice->LightEnable(1, FALSE);
			//m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
			//m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
			
			draw(randDouble(0.5f,1),randDouble(0.5f,1),randDouble(0.5f,1),&mallit[2].malli[model]);
			//m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
			//m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
			m_pDevice->LightEnable(0, TRUE);
			m_pDevice->LightEnable(1, TRUE);
			m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000);
		}
		//not disabled
		else{
			drawfast(&mallit[2].malli[model]);
		}

		
	}

	//radar
		D3DXMATRIX tempmatrix;
		D3DXPLANE plane;
		D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
		D3DXMatrixShadow(&tempmatrix,&D3DXVECTOR4(0,4200,0,0),&plane);
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
		m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);
		m_pDevice->LightEnable(0, FALSE);
		m_pDevice->LightEnable(1, FALSE);		
		m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x0000FF00);
		m_pDevice->SetRenderState(D3DRS_ZENABLE ,FALSE);
	//camera
		kamerax1=0;
		kameray1=4200;
		kameraz1=1;
		kamerax2=0;
		kameray2=0;
		kameraz2=0;		
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
		D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );
		m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	//grid	
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR );
		m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_INVDESTCOLOR);	
		matriisi->LoadIdentity();	
		matriisi->TranslateLocal(-1250,0,850);
		matriisi->RotateYawPitchRollLocal(0,0,pi/2);
		matriisi->ScaleLocal(8,8,8);
		draw(0.5f,0.5f,0.5f,&mallit[0].malli[4]);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
		m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );	
		matriisi->LoadIdentity();	
		matriisi->TranslateLocal(-1250,0,850);
		matriisi->RotateYawPitchRollLocal(0,0,pi/2);
		matriisi->ScaleLocal(8,8,8);
		draw(0.5f,0.5f,0.5f,&mallit[0].malli[4]);
	//planet
	if(battle.type==0){	
		matriisi->LoadMatrix(&tempmatrix);	
		matriisi->TranslateLocal(-1250,0,850);
		matriisi->RotateYawPitchRollLocal(-pi/2+battle.planet.rx,battle.planet.ry,battle.planet.rz);
		matriisi->ScaleLocal(3,3,3);	
		draw(0.0f,0.7f,0.0f,&mallit[1].malli[battle.planet.picture]);
	}		
	//ships	
	for (q=1; q<maximum_ships; q++){
		if(ship[q].dead)continue;
		matriisi->LoadIdentity();	
		matriisi->TranslateLocal(-1250,0,850);
		matriisi->TranslateLocal(-ship[q].z1*0.03f,0,ship[q].x1*0.03f);
		matriisi->RotateYawPitchRollLocal(ship[q].rx,0,pi/2);
		//enemy
		if(ship[q].side==1){
			matriisi->ScaleLocal(0.4f,0.4f,0.4f);
			draw(0.8f,0.0f,0.0f,&mallit[0].malli[5]);	
		}
		//self controlled own ship
		if((ship[q].side==0)&&(q==player_controlled_ship)){
			matriisi->ScaleLocal(0.6f,0.6f,0.6f);
			draw(0.0f,0.8f,0.0f,&mallit[0].malli[5]);	
		}
		//computer controlled own ship
		if((ship[q].side==0)&&(q!=player_controlled_ship)){
			matriisi->ScaleLocal(0.4f,0.4f,0.4f);
			draw(0.3f,0.8f,0.3f,&mallit[0].malli[5]);	
		}
	}
	//heat meter
		matriisi->LoadIdentity();	
		matriisi->TranslateLocal(-1250-114,0,850-232);
		matriisi->RotateYawPitchRollLocal(-pi/2,pi/2,0);
		matriisi->ScaleLocal(1.5f,1.5f,1.5f);
		mallit[1].malli[1].sisus[0].textuuri2=26;
		mallit[1].malli[1].sisus[0].textuuri=26;
		float heatmeter=ship[player_controlled_ship].heat/ship[player_controlled_ship].encounter.ship_basea.base_heat;
		if(heatmeter>1)heatmeter=1;
		draw(heatmeter,1-heatmeter,0,&mallit[1].malli[1]);
		itoa((int)(heatmeter*100),temprivi,10);
		if(heatmeter<0.1f)
		kirjota(1,heatmeter,1-heatmeter,0,977,592,0,temprivi);
		else
		kirjota(1,heatmeter,1-heatmeter,0,973,592,0,temprivi);
		if(ship[player_controlled_ship].overheat)
		kirjota(1,1,0,0,890,592,0,"Overheat");
	
	//disabled text
	for (q=1; q<maximum_ships; q++){
		if(ship[q].dead)continue;
		if(ship[q].disabled){
			float textx=(ship[q].x1-ship[player_controlled_ship].x1)*3.5f/(cameraheight*2.5f*0.001f)+384;
			float textz=(ship[q].z1-ship[player_controlled_ship].z1)*3.5f/(cameraheight*2.5f*0.001f)+512;
			if(ship[q].side==0)kirjota(1,0,1,0,textz,textx,0,"disabled");
			if(ship[q].side==1)kirjota(1,1,0,0,textz,textx,0,"disabled");
		}
		if(!ship[q].disabled){
			float textx=(ship[q].x1-ship[player_controlled_ship].x1)*3.5f/(cameraheight*2.5f*0.001f)+384+20;
			float textz=(ship[q].z1-ship[player_controlled_ship].z1)*3.5f/(cameraheight*2.5f*0.001f)+512+20;
			//energy
			
		//textx=(planet[q].x-ship[0].x1)*3.8f*0.1f+384;
		//textz=(planet[q].z-ship[0].z1)*3.8f*0.1f+512;
			bool osuma;
			float osumax,osumaz;

			if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,5,0,5,1024)){textx=osumax;textz=osumaz;}
			if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,750,0,750,1024)){textx=osumax;textz=osumaz;}
			if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,0,5,768,5)){textx=osumax;textz=osumaz;}
			if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,0,1000,768,1000)){textx=osumax;textz=osumaz;}
		
			itoa((int)ship[q].energy,temprivi,10);
			if(ship[q].side==0)kirjota(1,0,1,0,textz,textx,0,temprivi);
			if(ship[q].side==1)kirjota(1,1,0,0,textz,textx,0,temprivi);
		}
	}
	
	//battle ending text
	if(pelivaihe2==1){
		if((battle.side[0]==0)||(battle.side[1]==0))
		kirjota(1,-1,-1,-1,580,368,0,"Battle Ends...");
	}

}

void rendersolarsystem(void){//draws solar system

	int q;
	float rad;
	compute_missions();//calculates which missions are finished
	
	if(planet_visit_timer>0)planet_visit_timer=planet_visit_timer-elapsed*pelinopeus;
	//if ship is on a planet, go there
	if(ship[0].nearstar!=-1)
		if(ship[0].nearstar2==-1){
			if(planet_visit_timer<=0)
			if(planet[ship[0].nearstar].population>0){
				create_dialog(0,ship[0].nearstar,0);
				planet_visit_timer=1000;
			}
			//ship[0].vx=0;
			//ship[0].vz=0;
		}
	//fly
	fly(&ship[0]);
	if(!ship[1].dead)fly(&ship[1]);

	//sun's gravity
	float sun_size=3;
	float sun_mass=30;
	float distancesquare=(sqr(ship[0].x1)+sqr(ship[0].z1));
	//if(distancesquare<sqr((265*10)*sun_size)){
	{
		//gravity
			float angletoship=atan2f(ship[0].x1,ship[0].z1);
			float gravity=0.5f;
			//float distancesquare=(sqr(battle.planet.x-ship[0].x1)+sqr(planeta->z-ship[0].z1));
			//float angletoship=atan2f(ship[0].x1-planeta->x,ship[0].z1-planeta->z);	
			ship[0].vx=ship[0].vx-sinf(angletoship)*gravity*(100.0f*sun_mass/distancesquare*pelinopeus*elapsed);
			ship[0].vz=ship[0].vz-cosf(angletoship)*gravity*(100.0f*sun_mass/distancesquare*pelinopeus*elapsed);

			if(distancesquare<sqr((265)*sun_size)){
				float temp=(angletoship-((ship[0].vangle+pi)-angletoship));
				ship[0].vx=sinf(temp)*sqrtf(ship[0].vpowersquare)*1.05f;
				ship[0].vz=cosf(temp)*sqrtf(ship[0].vpowersquare)*1.05f;
				ship[0].x1=ship[0].x2;
				ship[0].z1=ship[0].z2;
				float kerroin=sqrtf(sqr((265)*sun_size)/(sqr(ship[0].x1)+sqr(ship[0].z1)));
				ship[0].z1=(ship[0].z1)*kerroin;
				ship[0].x1=(ship[0].x1)*kerroin;
			}
	}


	//planeetat lentää
	for (q=0; q<maximumplanets; q++){
			if(planet[q].dead)continue;				
			fly_planet(&planet[q]);
	}
	//avaruuskivet
	if((elapsed*pelinopeus*ship[0].vpowersquare*2!=0)&&(elapsed*pelinopeus*ship[0].vpowersquare*2<180)){
		if(randInt(0,200/(elapsed*pelinopeus*ship[0].vpowersquare*2))==0)
		for (q=0; q<maximumrocks; q++){
				if(rock[q].dead)continue;
					rock[q].distancesquare=(sqr(rock[q].x-ship[0].x1)+sqr(rock[q].z-ship[0].z1));				
		}
	}
	//kamera
		kamerax1=ship[0].x1+100;
		kameray1=4200;

		kameraz1=ship[0].z1;
		kamerax2=kamerax1-100;
		kameray2=0;
		kameraz2=kameraz1;		
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
		D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );
		m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);

	//spacedust
			m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
			m_pDevice->SetMaterial( &mat[0] );
			m_pDevice->SetTexture( 0, tausta[0]);
			m_pDevice->SetVertexShader( D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) );
			
			m_pDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
			m_pDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );
			m_pDevice->SetRenderState( D3DRS_POINTSIZE,     FtoDW(1.0f) );
			m_pDevice->SetRenderState( D3DRS_POINTSIZE_MIN, FtoDW(1.00f) );
			m_pDevice->SetRenderState( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
			m_pDevice->SetRenderState( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
			m_pDevice->SetRenderState( D3DRS_POINTSCALE_C,  FtoDW(0.00f) );
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
			m_pDevice->SetRenderState( D3DRS_AMBIENT, 0xFF777777);


			int k1=1;
			if(ship[0].x1<0)k1=-1;
			int k2=1;
			if(ship[0].z1<0)k2=-1;

			matriisi->LoadIdentity();		
			matriisi->TranslateLocal((float)((int)(ship[0].x1/4000)*4000),0,(float)((int)(ship[0].z1/4000)*4000));			
			matriisi->ScaleLocal(2,1,2);
			m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());			
			m_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST  ,1500,spacedust,
					sizeof(pvertex));

			matriisi->LoadIdentity();		
			matriisi->TranslateLocal((float)((int)(ship[0].x1/4000)*4000+4000*k1),0,(float)((int)(ship[0].z1/4000)*4000));			
			matriisi->ScaleLocal(2,1,2);
			m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());			
			m_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST  ,1500,spacedust,
					sizeof(pvertex));

			matriisi->LoadIdentity();		
			matriisi->TranslateLocal((float)((int)(ship[0].x1/4000)*4000),0,(float)((int)(ship[0].z1/4000)*4000+4000*k2));			
			matriisi->ScaleLocal(2,1,2);
			m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());			
			m_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST  ,1500,spacedust,
					sizeof(pvertex));

			matriisi->LoadIdentity();		
			matriisi->TranslateLocal((float)((int)(ship[0].x1/4000)*4000+4000*k1),0,(float)((int)(ship[0].z1/4000)*4000+4000*k2));			
			matriisi->ScaleLocal(2,1,2);
			m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());			
			m_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST  ,1500,spacedust,
					sizeof(pvertex));

			m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
			









	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
	//aurinko
	if(sqr(ship[0].x1)+sqr(ship[0].z1)<sqr(2700)){
		suntimer=suntimer+elapsed*pelinopeus;
		if(suntimer>40)suntimer=40;
		
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
		m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
		//draw the disk
		for (q=0; q<1; q++){
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(0,0,0);			
			matriisi->RotateYawPitchRollLocal(randDouble(-pi,pi),pi/2,0);			
			matriisi->ScaleLocal(13,13,13);		
			draw(1.0f,1.0f,1.0f,&mallit[1].malli[9]);
		}

		m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);

		while(suntimer>=0){
			suntimer=suntimer-9.0f;						
			rad=randDouble(-pi,pi);
			savusta(1,randDouble(1.3f,3.5f),0.001f,true,400,sinf(rad)*730,0,cosf(rad)*730,0,randDouble(-pi,pi),0,0,randDouble(-0.1f,0.1f),0,randDouble(-0.1f,0.1f));
			rad=randDouble(-pi,pi);
			savusta(1,randDouble(1.3f,3.5f),0.001f,true,400,sinf(rad)*730,0,cosf(rad)*730,0,randDouble(-pi,pi),0,0,randDouble(-0.1f,0.1f),0,randDouble(-0.1f,0.1f));
		}
	}
	
	
	//planets
	for (q=0; q<maximumplanets; q++){
		if(planet[q].dead)continue;
		m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
		if(planet[q].distancesquare>(sqr(2500)+sqr(460*planet[q].size))){continue;}		

		//matriisi->LoadIdentity();

		D3DXMATRIX tempmatrix;
		D3DXPLANE plane;
		D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
		D3DXMatrixShadow(&tempmatrix,&D3DXVECTOR4(0,4200,0,0),&plane);
		matriisi->LoadMatrix(&tempmatrix);

		matriisi->TranslateLocal(planet[q].x,planet[q].y,planet[q].z);	
		matriisi->RotateYawPitchRollLocal(planet[q].rx,planet[q].ry,planet[q].rz);			
		matriisi->ScaleLocal(20,20,20);	
		m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00CCCCCC);		
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
		drawfast(&mallit[1].malli[planet[q].picture]);

			
		//shadow
		if(planet[q].shadow==0){
			m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,FALSE);		
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(planet[q].x,planet[q].y,planet[q].z);
			matriisi->RotateYawPitchRollLocal(planet[q].angletosun,0,0);			
			matriisi->ScaleLocal(20*planet[q].size,1,20*planet[q].size);
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO    );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_SRCCOLOR);				
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);	
			matriisi->RotateYawPitchRollLocal(0,pi/2,0);
			draw(1.0f,1.0f,1.0f,&mallit[1].malli[24]);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
		}
		
		
		//atmosphere / ring
		if(planet[q].atmosphere!=-1){
			m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(planet[q].x,planet[q].y,planet[q].z);								
			matriisi->RotateYawPitchRollLocal(planet[q].rx,planet[q].ry,planet[q].rz);			
			matriisi->ScaleLocal(20,20,20);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);	
			matriisi->RotateYawPitchRollLocal(0,planet[q].ry,0);
			draw(0.3f,0.3f,0.3f,&mallit[1].malli[planet[q].atmosphere]);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
		}


	}

	
	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);		
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);

	//rocks
	for (q=0; q<maximumrocks; q++){
		if(rock[q].distancesquare>sqr(2000)){continue;}
		if(rock[q].dead)continue;		
		matriisi->LoadIdentity();
		matriisi->TranslateLocal(rock[q].x,rock[q].y,rock[q].z);	
		matriisi->RotateYawPitchRollLocal(rock[q].rx,rock[q].ry,rock[q].rz);			
		matriisi->ScaleLocal(rock[q].size,rock[q].size,rock[q].size);	
		drawfast(&mallit[1].malli[rock[q].picture]);

	}

	

	//ships 
	m_pDevice->SetRenderState(D3DRS_AMBIENT, 0x00000000);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);	
	m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pDevice->LightEnable(0, TRUE);
	m_pDevice->LightEnable(1, TRUE);
	//light
	ZeroMemory(&lamppu[0].valo, sizeof(D3DLIGHT8));	
	lamppu[0].valo.Range = 10000;
	lamppu[0].valo.Diffuse.r = 1;    
	lamppu[0].valo.Diffuse.g = 1;
	lamppu[0].valo.Diffuse.b = 1;
	lamppu[0].valo.Diffuse.a = 1.0f;    
	lamppu[0].valo.Ambient.r = 0.16f;
	lamppu[0].valo.Ambient.g = 0.16f;    
	lamppu[0].valo.Ambient.b = 0.16f;
	lamppu[0].valo.Ambient.a = 1.0f;
	lamppu[0].valo.Specular.r = 1.0f;    
	lamppu[0].valo.Specular.g = 1.0f;
	lamppu[0].valo.Specular.b = 1.0f;
	lamppu[0].valo.Specular.a = 1.0f;
	lamppu[0].valo.Type=D3DLIGHT_POINT;
	lamppu[0].valo.Attenuation0=1;
	lamppu[0].valo.Attenuation1=0;
	lamppu[0].valo.Attenuation2=0;	
		//valo1
		lamppu[0].valo.Position.x = ship[0].x1-2000;
		lamppu[0].valo.Position.y = 2500;
		lamppu[0].valo.Position.z = ship[0].z1-2000;		
		m_pDevice->SetLight(0, &lamppu[0].valo);
		//valo2
		lamppu[0].valo.Position.x = ship[0].x1+1000;
		lamppu[0].valo.Position.y = 2000;
		lamppu[0].valo.Position.z = ship[0].z1+2500;
		m_pDevice->SetLight(1, &lamppu[0].valo);

	clearzbuffer(); 
	
		
	for (q=0; q<2; q++){
		if(ship[q].dead)continue;
		if(sqr(ship[q].x1-ship[0].x1)+sqr(ship[q].z1-ship[0].z1)>sqr(2200*(cameraheight*0.00022f)))continue;
		matriisi->LoadIdentity();
		matriisi->TranslateLocal(ship[q].x1,ship[q].y1,ship[q].z1);			
		matriisi->RotateYawPitchRollLocal(ship[q].rx,ship[q].ry,ship[q].rz);
		drawfast(&mallit[2].malli[ship[q].encounter.ship_basea.picture]);	
	}

	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);

	//planet's names
	float textx,textz;
	bool osuma;
	float osumax,osumaz;
	for (q=0; q<maximumplanets; q++){
		if(planet[q].dead)continue;
		if(q==mission[missionlist[selected_mission]].planet){goto a;}
		if(planet[q].type==2)if(planet[q].distancesquare>sqr(13000))continue;
		if(planet[q].type==1)if(planet[q].distancesquare>sqr(13000))continue;
		if(planet[q].type==0)if(planet[q].distancesquare>sqr(30000))continue;
		a:
		textx=(planet[q].x-ship[0].x1)*3.8f*0.1f+384;
		textz=(planet[q].z-ship[0].z1)*3.8f*0.1f+512;

		if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,3,0,3,1024)){textx=osumax;textz=osumaz;}
		if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,750,0,750,1024)){textx=osumax;textz=osumaz;}
		if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,0,5,768,5)){textx=osumax;textz=osumaz;}
		if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,0,900,768,900)){textx=osumax;textz=osumaz;}
		
		kirjota(1,-1,-1,-1,textz,textx,0,planet[q].name);
		if(q==mission[missionlist[selected_mission]].planet)kirjota(1,1,0,0,textz,textx+0.5f,0,planet[q].name);
	}

	//onko lähellä planeettaa
	ship[0].nearstar2=ship[0].nearstar;
	ship[0].nearstar=-1;
	for (q=0; q<maximumplanets; q++){
		if(planet[q].dead)continue;
		if(planet[q].distancesquare<sqr((265)*planet[q].size)){
			ship[0].nearstar=q;
			break;
		}
	}	
	if(ship[0].nearstar!=-1)
		if(ship[0].nearstar2==-1){
			ship[0].onplanet=q;
		}

	//random encounters
	if(pelinopeus>0.7f){
		//if(randInt(0,100000/(elapsed*pelinopeus))==0){
		if((ship[1].dead)||(sqr(ship[0].x1-ship[1].x1)+sqr(ship[0].z1-ship[1].z1)>sqr(3000)))
		if(randInt(0,1000/(elapsed*pelinopeus))==0){
			ZeroMemory(&ship[1], sizeof(shipbase));
			create_random_ship(&ship[1].encounter,-1,0);
			float angle=randDouble(0,2*pi);
			ship[1].x1=ship[0].x1+2000*sinf(angle);
			ship[1].z1=ship[0].z1+2000*cosf(angle);
			ship[1].motordown=0;
			ship[1].motorleft=0;
			ship[1].motorright=0;
			ship[1].motorup=0;
			ship[1].rx=randDouble(0,pi);
			ship[1].ry=0;
			ship[1].rz=0;
			ship[1].y1=0;
			ship[1].x2=ship[1].x1;                                                                                     	
			ship[1].y2=0;
			ship[1].z2=ship[1].z1;	
			ship[1].vx=0;
			ship[1].vz=0;
			ship[1].guntime[0]=0;
			ship[1].guntime[1]=0;
			ship[1].guntime[2]=0;
			ship[1].guntime[3]=0;
			ship[1].dead=false;
			ship[1].number=1;
			ship[1].energy=100;
			ship[1].side=1;	
			ship[1].disabled=false;
			
		}		
	}	

	//if encountered ship is near
	if(!ship[1].dead)
	if(sqr(ship[0].x1-ship[1].x1)+sqr(ship[0].z1-ship[1].z1)<sqr(100)){		
		dialog.randomship=ship[1].encounter;
		create_dialog(1,0,0);
		//too little guel
		if(shipslot[0].cargo[4]==0)
		if(randInt(0,3)==0){
			create_dialog(2,51,0);//offer fuel
			dialog.randomship=ship[1].encounter;				
		}
		ship[1].dead=true;
	}
	//random encounter AI
	if(!ship[1].dead){
		if(ship[1].left)if(randInt(0,1000/(elapsed*pelinopeus))==0)
		ship[1].left=false;
		if(ship[1].right)if(randInt(0,1000/(elapsed*pelinopeus))==0)
		ship[1].right=false;
		ship[1].up=false;
		ship[1].down=false;
		ship[1].one=false;
		ship[1].two=false;
		if((ship[1].vpowersquare<0.7f)||(ship[1].left)||(ship[1].right))
			ship[1].up=true;
		if(randInt(0,10000/(elapsed*pelinopeus))==0)
			ship[1].left=true;
		if(randInt(0,10000/(elapsed*pelinopeus))==0)
			ship[1].right=true;
		

		//steer
		if(ship[1].encounter.chasing){
			ship[1].left=false;
			ship[1].right=false;
			ship[1].up=true;
			//target is to left or to right
			float dq=-atan2f(ship[1].z1-ship[0].z3,ship[1].x1-ship[0].x3);
			float temp1=ship[1].rx;
			if(ship[1].rx-dq>pi)temp1=temp1-pi*2;
			if(dq-ship[1].rx>pi)dq=dq-pi*2;
			
							int negaatio=1;
							if (dq<temp1)
								negaatio=-1;						
			
			if(fabs(fabs(dq-temp1)-pi)>0.01f){
				if(negaatio==1)
					ship[1].left=true;
				if(negaatio==-1)
					ship[1].right=true;		
			}
		}
	}



	//fuel meter
	strcpy(rivi,"Fuel: ");
	itoa(shipslot[0].cargo[4],temprivi,10);strcat(rivi,temprivi);
	kirjota(1,-1,-1,-1,815,730,0,rivi);
	//fuel low
	if((shipslot[0].cargo[4]<5)&&(shipslot[0].cargo[4]!=0)){
		fuellowtimer=fuellowtimer-elapsed*pelinopeus*3*0.001f*fuellowdirection;
		if(fuellowtimer<0){fuellowdirection=-1;fuellowtimer=0;}
		if(fuellowtimer>1){fuellowdirection=1;fuellowtimer=1;}		
		kirjota(1,fuellowtimer,0,0,815,749,0,"FUEL LOW");
	}
	//engines down
	if(shipslot[0].cargo[4]==0){
		fuellowtimer=fuellowtimer-elapsed*pelinopeus*3*0.001f*fuellowdirection;
		if(fuellowtimer<0){fuellowdirection=-1;fuellowtimer=0;}
		if(fuellowtimer>1){fuellowdirection=1;fuellowtimer=1;}		
		kirjota(1,fuellowtimer,0,0,815,749,0,"ENGINES DOWN");
	}
	//space warp timer
	if(warp_timer>0){
		warp_timer=warp_timer-elapsed*pelinopeus;
		strcpy(temprivi,"You have hit a space warp");
		kirjota(1,0,warp_timer/5000,0,10,10,0,temprivi);
	}

}

void fly_planet(planets *planeta){
	float general_speed=0.1f;
	float planetspeed=0.04f*general_speed;
	float rotatespeed=1.f/240.0f*general_speed;
	float radiusmultiplier=70;	
	//float gravity=0.7f;
	planeta->angletohost=planeta->angletohost-planeta->speed*planetspeed*pelinopeus*elapsed;	
	float hostx=0;
	float hostz=0;
	if(planeta->host!=-1){
		hostx=planet[planeta->host].x;
		hostz=planet[planeta->host].z;
	}
	planeta->x=hostx+sinf(planeta->angletohost)*radiusmultiplier*planeta->radiustohost/planeta->ellipce;
	planeta->z=hostz+cosf(planeta->angletohost)*radiusmultiplier*planeta->radiustohost;
	planeta->ry=planeta->ry+planeta->rotatespeed*rotatespeed*pelinopeus*elapsed;	
	planeta->distancesquare=(sqr(planeta->x-ship[0].x1)+sqr(planeta->z-ship[0].z1));
	if(planeta->shadow==0)planeta->angletosun=-atan2f(planeta->z,planeta->x)+pi;
			
	if(planeta->distancesquare<sqr((265*10)*planeta->size)){
		//gravity
			planeta->angletoship=atan2f(ship[0].x1-planeta->x,ship[0].z1-planeta->z);
			float gravity=0.4f;
			//float distancesquare=(sqr(battle.planet.x-ship[0].x1)+sqr(planeta->z-ship[0].z1));
			//float angletoship=atan2f(ship[0].x1-planeta->x,ship[0].z1-planeta->z);	
			ship[0].vx=ship[0].vx-sinf(planeta->angletoship)*gravity*(100.0f*planeta->mass/planeta->distancesquare*pelinopeus*elapsed);
			ship[0].vz=ship[0].vz-cosf(planeta->angletoship)*gravity*(100.0f*planeta->mass/planeta->distancesquare*pelinopeus*elapsed);

			if(planeta->distancesquare<sqr((265)*planeta->size)){
				if(ship[0].vpowersquare<0.1f)ship[0].vpowersquare=0.1f;
				if(ship[0].vpowersquare>0.5f)ship[0].vpowersquare=0.5f;
				float temp=(planeta->angletoship-((ship[0].vangle+pi)-planeta->angletoship));
				ship[0].vx=sinf(temp)*sqrtf(ship[0].vpowersquare)*1.05f;
				ship[0].vz=cosf(temp)*sqrtf(ship[0].vpowersquare)*1.05f;
				ship[0].x1=ship[0].x2;
				ship[0].z1=ship[0].z2;
				float kerroin=sqrtf(sqr((265)*planeta->size)/(sqr(ship[0].x1-planeta->x)+sqr(ship[0].z1-planeta->z)));						
				ship[0].z1=(ship[0].z1-planeta->z)*kerroin+planeta->z;
				ship[0].x1=(ship[0].x1-planeta->x)*kerroin+planeta->x;
			}
	}
}

void render_dialog(void){
	int q;

	dialog.rotate=dialog.rotate+0.0005f*elapsed*pelinopeus;
	//m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0 );
	m_pDevice->SetRenderState(D3DRS_ZENABLE ,FALSE);	
	pelinopeus=1;	
	//kamera dialogille
	kamerax1=0;
	kameray1=300;
	kameraz1=1;

	kamerax2=0;
	kameray2=0;
	kameraz2=0;

	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((60)*pi/180), aspect, 25.0f, maxvisible);		
	m_pDevice->SetTransform( D3DTS_VIEW, &matView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);

	//background
	LPDIRECT3DSURFACE8 pBackBuffer;
    m_pDevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
	RECT rcSource[] = {  0,  0,  SCREEN_WIDTH,  SCREEN_HEIGHT};
	POINT ptDest[]   = {  0,  0};
    m_pDevice->CopyRects(kuvia[0], rcSource, 1, pBackBuffer, ptDest);
    pBackBuffer->Release();

	//small picture of earth
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	matriisi->LoadIdentity();
	matriisi->TranslateLocal(46,0,(float)(-43+dialog_choice*10+dialog.dialog_options_place*0.43f));		
	matriisi->ScaleLocal(0.2f,0.2f,0.2f);	
	drawfast(&mallit[1].malli[7]);

	
	//draw the picture (left box)
	if(dialog.picture!=-1){
			m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(164,0,-44);
			matriisi->RotateYawPitchRollLocal(pi,pi/2,0);
			matriisi->ScaleLocal(1.15f,1.5f,1);

				
				switch(dialog.picture){				
						case 0:{
							mallit[1].malli[1].sisus[0].textuuri2=1;
							mallit[1].malli[1].sisus[0].textuuri=1;
							break;
							   }
						case 1:{
							mallit[1].malli[1].sisus[0].textuuri2=2;
							mallit[1].malli[1].sisus[0].textuuri=2;
							break;
							   }
						case 2:{
							mallit[1].malli[1].sisus[0].textuuri2=9;
							mallit[1].malli[1].sisus[0].textuuri=9;
							break;
							   }
						case 3:{
							mallit[1].malli[1].sisus[0].textuuri2=47;
							mallit[1].malli[1].sisus[0].textuuri=47;
							break;
							   }
						case 4:{
							mallit[1].malli[1].sisus[0].textuuri2=59;
							mallit[1].malli[1].sisus[0].textuuri=59;
							break;
							   }
						case 5:{
							mallit[1].malli[1].sisus[0].textuuri2=60;
							mallit[1].malli[1].sisus[0].textuuri=60;
							break;
							   }
						case 6:{
							mallit[1].malli[1].sisus[0].textuuri2=61;
							mallit[1].malli[1].sisus[0].textuuri=61;
							break;
							   }
						case 7:{
							mallit[1].malli[1].sisus[0].textuuri2=64;
							mallit[1].malli[1].sisus[0].textuuri=64;
							break;
							   }

				}
				drawfast(&mallit[1].malli[1]);				
	}

	//picture of planet or ship
	if(dialog.lowpictureclass!=-1){
		kamerax1=-157;
		kameray1=300;
		kameraz1=-77.4f;
		kamerax2=kamerax1;
		kameray2=0;
		kameraz2=kameraz1-1;
		float kerroin;
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );
		//planet
		if(dialog.lowpictureclass==1){
			m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xCCCCCCCC);
			D3DXMATRIX tempmatrix;
			D3DXPLANE plane;
			D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
			D3DXMatrixShadow(&tempmatrix,&D3DXVECTOR4(0,300,0,0),&plane);
			matriisi->LoadMatrix(&tempmatrix);			
			matriisi->RotateYawPitchRollLocal(-pi/2,dialog.rotate,0);
			float t0=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].downright.x;
			float t1=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].downright.y;
			float t2=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].downright.z;
			float t3=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].upleft.x;
			float t4=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].upleft.y;
			float t5=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].upleft.z;
			kerroin=(float)(85/sqrt(sqr(t0-t3)+sqr(t1-t4)+sqr(t2-t5)));
		}
		//ship
		if(dialog.lowpictureclass==2){
			m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
			matriisi->LoadIdentity();
			matriisi->RotateYawPitchRollLocal(dialog.rotate,0,0);
			float t0=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].downright.x;
			float t1=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].downright.y;
			float t2=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].downright.z;
			float t3=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].upleft.x;
			float t4=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].upleft.y;
			float t5=mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber].upleft.z;
			kerroin=(float)(30/sqrt(sqr(t0-t3)+sqr(t1-t4)+sqr(t2-t5)));
		}
		matriisi->ScaleLocal(kerroin,kerroin,kerroin);	
		m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
		drawfast(&mallit[dialog.lowpictureclass].malli[dialog.lowpicturenumber]);
	}

	//text
	kirjota(1,-1,-1,-1,390,110,30,dialog.text);	

	//dialog options
	for (q=0; q<dialog.options; q++){
		kirjota(1,-1,-1,-1,430,(float)(285+23*q+dialog.dialog_options_place),30,dialog.option[q].text);		
		//uudestaan jos on valittu
		if(q==dialog_choice)
			kirjota(1,-1,-1,-1,430,(float)(285+23*q+dialog.dialog_options_place),30,dialog.option[q].text);	
	}

	//cargo
	itoa(shipslot[0].cargo[3],temprivi,10);//funds
	kirjota(1,-1,-1,-1,940,603+0*23,30,temprivi);
	itoa(shipslot[0].cargo[4],temprivi,10);//fuel
	kirjota(1,-1,-1,-1,940,603+1*23,30,temprivi);
	itoa(shipslot[0].cargo[1],temprivi,10);//contraband goods
	kirjota(1,-1,-1,-1,940,603+2*23,30,temprivi);
	itoa(shipslot[0].cargo[0],temprivi,10);//slaves
	kirjota(1,-1,-1,-1,940,603+3*23,30,temprivi);
	itoa(shipslot[0].cargo[2],temprivi,10);//illegal weapons
	kirjota(1,-1,-1,-1,940,603+4*23,30,temprivi);
	
	//info
	if(dialog.infos>0)
	for (q=0; q<dialog.infos; q++){
		kirjota(1,-1,-1,-1,370,(float)(500+23*q),30,dialog.info[q]);	
	}
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);

}

void create_dialog(int dialogtype,int value0,int select_choise){
	int q,r,a,b;
	pelivaihe=1;
	dialog_choice=select_choise;
	battle.endplot=-1;
	dialog.ships=-1;

	ship[0].motordown=0;
	ship[0].motorup=0;
	ship[0].motorleft=0;
	ship[0].motorright=0;

	//show a cutscene
	if(value0<0){
		dialog.noreturn=false;
		pelivaihe=4;
		pelivaihe2=-value0;
		return;
	}

	//erase all smoke
	for (q=0; q<maksimisavuja; q++){
		savu[q].pois=true;
	}
	//particles
	for (q=0; q<maximum_particles; q++){
		ZeroMemory(&particle[q], sizeof(particles));
		particle[q].dead=true;
	}
	//bullets
	for (q=0; q<maximum_bullets; q++){
		bullet[q].dead=true;
	}

	//defaults
	//dialog.picture=-1;
	//dialog.infos=0;
	//dialog.lowpictureclass=-1;

	//next key ups won't take action
	dialog.noup=false;
	dialog.nodown=false;
	dialog.noreturn=false;
	if(buffer[DIK_UP]&0x80)dialog.noup=true;
	if(buffer[DIK_DOWN]&0x80)dialog.nodown=true;
	if(buffer[DIK_RETURN]&0x80)dialog.noreturn=true;

	for (q=0; q<10; q++){
		strcpy(dialog.option[q].text," ");
		dialog.option[q].default_selection=0;
		for (a=0; a<5; a++){
			dialog.option[q].cargoplus[a]=0;
			dialog.option[q].cargominus[a]=0;			
			dialog.option[q].mission.cargominus[a]=0;
			dialog.option[q].mission.cargoplus[a]=0;
			dialog.option[q].mission.end_flag=-1;
			dialog.option[q].mission.end_flag_do=-1;
			dialog.option[q].mission.planet=-1;
			dialog.option[q].mission.prize_plot=-1;
		}
	}
	dialog.dialog_options_place=0;

	//for (q=0; q<6; q++){
	//	strcpy(dialog.info[q]," ");	
	//}

	//approaching planet
	if(dialogtype==0){
		bool normal=true;
		//start plot on any planet
		if(plot_started==false){
			plot_started=true;
			normal=false;

			
			dan_planet=value0;//store dan's location for further use

			strcpy(dialog.text,"Captain, we have just arrived on ");		
			strcat(dialog.text,planet[value0].name);
			strcat(dialog.text,". We are being hailed by a local merchant.");

			strcpy(dialog.option[0].text,"Show me.");
			dialog.options=1;
			
			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=3;//start plot
				//dialog.option[0].effect_parameter2=20;//start plot

			strcpy(dialog.info[0],"      Name:");		
			strcpy(dialog.info[1],"     Class:");		
			strcpy(dialog.info[2],"Population:");
			strcpy(dialog.info[3],"  Military:");
			strcpy(dialog.info[4],"    Wealth:");
			
			strcat(dialog.info[0],planet[value0].name);	
			if(planet[value0].type==0)strcat(dialog.info[1],"planet");
			if(planet[value0].type==1)strcat(dialog.info[1],"moon");
			if(planet[value0].type==2)strcat(dialog.info[1],"asteroid base");
			itoa(planet[value0].population,temprivi,10);strcat(dialog.info[2],temprivi);
			itoa(planet[value0].military,temprivi,10);strcat(dialog.info[3],temprivi);
			itoa(planet[value0].wealth,temprivi,10);strcat(dialog.info[4],temprivi);
			
			dialog.infos=5;

			dialog.lowpictureclass=1;
			dialog.lowpicturenumber=planet[value0].picture;	
			dialog.picture=0;


		}

		//normal planet dialog
		if(normal){
			r=randInt(0,3);
			if(r==0)strcpy(dialog.text,"Grrr! We are approaching ");	
			if(r==1)strcpy(dialog.text,"Captain, we are getting close to ");	
			if(r==2)strcpy(dialog.text,"Oh Grand Sire, we are approaching ");	
			strcat(dialog.text,planet[value0].name);
			strcat(dialog.text,". Shall we...");

			strcpy(dialog.option[0].text,"Leave");
			strcpy(dialog.option[1].text,"Enter spaceport");
			strcpy(dialog.option[2].text,"Launch attack");
			dialog.options=3;
			
			dialog.option[0].general_effect=0;//leave			
			dialog.option[1].general_effect=1;//talk
				dialog.option[1].effect_parameter=3;//talk with a spaceport
				dialog.option[1].effect_parameter2=ship[0].onplanet;//
			dialog.option[2].general_effect=2;//attack
				if((planet[value0].type==0)||(planet[value0].type==1))
				dialog.option[2].effect_parameter=0;//attack planet
				if(planet[value0].type==2)
				dialog.option[2].effect_parameter=1;//attack asteroid
				dialog.option[2].effect_parameter2=value0;//which planet

			strcpy(dialog.info[0],"      Name:");		
			strcpy(dialog.info[1],"     Class:");		
			strcpy(dialog.info[2],"Population:");
			strcpy(dialog.info[3],"  Military:");
			strcpy(dialog.info[4],"    Wealth:");
			
			strcat(dialog.info[0],planet[value0].name);	
			if(planet[value0].type==0)strcat(dialog.info[1],"planet");
			if(planet[value0].type==1)strcat(dialog.info[1],"moon");
			if(planet[value0].type==2)strcat(dialog.info[1],"asteroid base");
			itoa(planet[value0].population,temprivi,10);strcat(dialog.info[2],temprivi);
			itoa(planet[value0].military,temprivi,10);strcat(dialog.info[3],temprivi);
			itoa(planet[value0].wealth,temprivi,10);strcat(dialog.info[4],temprivi);
			
			dialog.infos=5;

			dialog.lowpictureclass=1;
			dialog.lowpicturenumber=planet[value0].picture;	
			dialog.picture=0;

			//players threat
			threat=0;
			for (q=1; q<maximum_shipslot; q++){
				if(shipslot[q].dead)continue;
				threat=threat+shipslot[q].energy*shipslot[q].ship_basea.threat/100;
			}

			//random events on planet			
			if(randInt(0,70)==0){				
				dialog.option[0].cargoplus[3]=randInt(10,20);//give funds
				strcpy(dialog.text,"Good, Bad Sir, the citizens of ");
				strcat(dialog.text,planet[value0].name);
				strcat(dialog.text," have kindly given us ");
				itoa(dialog.option[0].cargoplus[3],temprivi,10);strcat(dialog.text,temprivi);
				strcat(dialog.text," pieces of gold. In return they ask that we don´t kill them.");

				strcpy(dialog.option[0].text,"Good.");
				dialog.option[0].general_effect=3;//trade
				dialog.options=1;
			}
			//if player is in bad shape, give ships in random
			if(threat<5)
			if(randInt(0,40)==0){				
				strcpy(dialog.text,"Great news sir! We have been contacted by an anonymous donor here on ");
				strcat(dialog.text,planet[value0].name);
				strcat(dialog.text,". He has given us a brand new ship!");

				strcpy(dialog.option[0].text,"Let´s see it!");
				create_random_ship(&dialog.randomship,2,0);
				dialog.option[0].general_effect=4;//give ship
					dialog.option[0].effect_parameter=0;//give ship
				dialog.options=1;
			}
			//normal random give
			if(randInt(0,100)==0){				
				strcpy(dialog.text,"Great news sir! We have been contacted by an anonymous donor here on ");
				strcat(dialog.text,planet[value0].name);
				strcat(dialog.text,". He has given us a brand new ship!");

				strcpy(dialog.option[0].text,"Let´s see it!");
				create_random_ship(&dialog.randomship,2,0);
				dialog.option[0].general_effect=4;//give ship
					dialog.option[0].effect_parameter=0;//give ship
				dialog.options=1;
			}
			if(randInt(0,80)==0){
				a=randomplanet(value0);
				strcpy(dialog.text,"Captain, we have hit some sort of a space anomaly here on ");
				strcat(dialog.text,planet[value0].name);
				strcat(dialog.text," and we have been mysteriously transported to ");
				strcat(dialog.text,planet[a].name);
				strcat(dialog.text,".");

				strcpy(dialog.option[0].text,"Oh, I don´t even want to know!");
				dialog.option[0].general_effect=0;//leave
				dialog.options=1;

				ship[0].x1=planet[a].x;	
				ship[0].z1=planet[a].z;
			}
		}
	}

	//random ship encounter
	if(dialogtype==1){
		//just met
		if(value0==0){
			//encounter randomship;
			//create_random_ship(&dialog.randomship,-1,0);
			//chasing us
			if(dialog.randomship.chasing){				
				r=randInt(0,3);
				if(r==0)strcpy(dialog.text,"Grrr! Scanners report that the ");	
				if(r==1)strcpy(dialog.text,"Captain, we are receiving an urgent message from the ");	
				if(r==2)strcpy(dialog.text,"Oh Grand Sire, we are being chased by the ");
				strcat(dialog.text,dialog.randomship.ship_basea.classname);
				strcat(dialog.text," ");
				strcat(dialog.text,dialog.randomship.name);
				if(r==0)strcat(dialog.text," is approaching us");
				strcat(dialog.text,". Shall we receive it?");

				strcpy(dialog.option[0].text,"On screen!");
				strcpy(dialog.option[1].text,"Ruthlessly attack!");
				dialog.options=2;
				
				dialog.option[0].general_effect=1;//talk				
					dialog.option[0].effect_parameter=1;//talk with a ship
					dialog.option[0].effect_parameter2=1;//talk about what the ship has to say
				dialog.option[1].general_effect=2;//attack
				dialog.option[1].effect_parameter=2;//attack ship
				dialog.picture=0;
			}
			else{//not chasing us
				r=randInt(0,3);
				if(r==0)strcpy(dialog.text,"Grrr! Scanners report the ");	
				if(r==1)strcpy(dialog.text,"Captain, we are receiving a signal from the ");	
				if(r==2)strcpy(dialog.text,"Oh Grand Sire, we are approaching the ");	
				strcat(dialog.text,dialog.randomship.ship_basea.classname);
				strcat(dialog.text," ");
				strcat(dialog.text,dialog.randomship.name);
				strcat(dialog.text,". Shall we...");

				strcpy(dialog.option[0].text,"Leave them be.");
				strcpy(dialog.option[1].text,"Hear their pleads.");
				strcpy(dialog.option[2].text,"Ruthlessly attack!");
				dialog.options=3;
				
				dialog.option[0].general_effect=0;//leave
				dialog.option[1].general_effect=1;//talk				
					dialog.option[1].effect_parameter=1;//talk with a ship
					dialog.option[1].effect_parameter2=1;//talk about what the ship has to say
				dialog.option[2].general_effect=2;//attack
				dialog.option[2].effect_parameter=2;//attack ship
				dialog.picture=0;
			}
			strcpy(dialog.info[0],"      Name:");		
			strcpy(dialog.info[1],"     Class:");			
			strcat(dialog.info[0],dialog.randomship.name);	
			strcat(dialog.info[1],dialog.randomship.ship_basea.classname);			
			dialog.infos=2;
			dialog.lowpictureclass=2;
			dialog.lowpicturenumber=dialog.randomship.ship_basea.picture;	
		}
		//ship has something to say
		if(value0==1){
			//take random ship from previous dialog
			//plead mercy
			if(dialog.randomship.strategy==0){
				if(dialog.randomship.type==0){//refugee
					strcpy(dialog.text,"We are simple refugees from ");
					strcat(dialog.text,planet[randomplanet(-1)].name);
					strcat(dialog.text," on our way to ");
					strcat(dialog.text,planet[randomplanet(-1)].name);
					strcat(dialog.text,". Please don´t hurt, kill or enslave us.");
					
					strcpy(dialog.option[0].text,"We´ll leave you for now.");
					strcpy(dialog.option[1].text,"Die you pathetic worms!");
					dialog.options=2;					
					dialog.option[0].general_effect=0;//leave
					dialog.option[1].general_effect=2;//attack
					dialog.option[1].effect_parameter=2;//attack ship
					dialog.picture=4;//refugee
				}
				if(dialog.randomship.type==2){//merchant
					strcpy(dialog.text,"Oh mighty pirates, we are but simple, and poor, very very poor, merchants from ");
					strcat(dialog.text,planet[randomplanet(-1)].name);
					strcat(dialog.text," en route to ");
					strcat(dialog.text,planet[randomplanet(-1)].name);
					strcat(dialog.text,". Please don´t hurt us, we just sold all our goods!");
					
					strcpy(dialog.option[0].text,"Then we won´t need to kill you.");
					strcpy(dialog.option[1].text,"Methinks thou art lying!");
					dialog.options=2;					
					dialog.option[0].general_effect=0;//leave
					dialog.option[1].general_effect=2;//attack
					dialog.option[1].effect_parameter=2;//attack ship
					dialog.picture=1;//merchant
				}
				if(dialog.randomship.type==5){//traveller
					strcpy(dialog.text,"Please, horrible terrible pirates, don´t take our money! We have children to feed!");
					if(randInt(0,2)==0)strcpy(dialog.text,"Oh shoot! Pirates, again! We just gave all our money to the last bunch of you guys. Just let us go, and we won´t take offence.");					
					
					strcpy(dialog.option[0].text,"You are free to go as you wish.");
					strcpy(dialog.option[1].text,"Quit your whining! You die now!");
					dialog.options=2;					
					dialog.option[0].general_effect=0;//leave
					dialog.option[1].general_effect=2;//attack
					dialog.option[1].effect_parameter=2;//attack ship
					dialog.picture=3;//explorer
				}
			}
			//ask a question strategy
			if(dialog.randomship.strategy==1){
				if(dialog.randomship.type==0){//refugee
					strcpy(dialog.text,"Mayday! This is ");
					strcat(dialog.text,dialog.randomship.ship_basea.classname);
					strcat(dialog.text," class refugee ship ");
					strcat(dialog.text,dialog.randomship.name);
					strcat(dialog.text,". Can anyone hear us? Our ship´s life support is failing, we are dying here! Please take us on board!");
					
					strcpy(dialog.option[0].text,"We won´t waste our time on you!");
					strcpy(dialog.option[1].text,"We´ll take you, but as slaves.");
					strcpy(dialog.option[2].text,"I might just prefer killing you!");
					dialog.options=3;
					dialog.option[0].general_effect=0;//leave
					dialog.option[1].general_effect=3;//trade
						dialog.option[1].cargoplus[0]=15;//give slaves
					dialog.option[2].general_effect=2;//attack
					dialog.option[2].effect_parameter=2;//attack ship
					dialog.picture=4;//refugee
				}
				if(dialog.randomship.type==1){//pirate
					strcpy(dialog.text,"You are nothing! You are worthless! But if you have money, I might just give command of my old trusty ");
					strcat(dialog.text,dialog.randomship.ship_basea.classname);
					strcat(dialog.text," class pirate ship ");
					strcat(dialog.text,dialog.randomship.name);
					strcat(dialog.text,". So, how about it? For 150 pieces my crew will be loyal to you.");
						
					strcpy(dialog.option[0].text,"Go away, we don´t need your kind!");					
					strcpy(dialog.option[2].text,"I cannot trust you on this. Die punk!");
					dialog.options=3;
					dialog.option[0].general_effect=0;//leave
					dialog.option[2].general_effect=2;//attack
					dialog.option[2].effect_parameter=2;//attack ship
					dialog.picture=2;//pirate

					//enough money
					if(shipslot[0].cargo[3]>=150){
						strcpy(dialog.option[1].text,"Let´s join forces!");
						dialog.option[1].general_effect=4;//give ship
						dialog.option[1].effect_parameter=0;//give ship
							dialog.option[1].cargominus[3]=150;//give money
					}
					//not enough money
					if(shipslot[0].cargo[3]<150){
						strcpy(dialog.option[1].text,"We don´t have the money.");
						dialog.option[1].general_effect=0;//leave
					}
					
				}
				if(dialog.randomship.type==2){//merchant
					strcpy(dialog.text,"I just came from ");
					strcat(dialog.text,planet[randomplanet(-1)].name);
					strcat(dialog.text," and some contraband goods fell in to my lap. Twenty tons of the finest synthetic drugs. I´ll let you have them for, say 50 pieces. Do we have a deal?");
						
					strcpy(dialog.option[0].text,"No, we´re not interested.");					
					strcpy(dialog.option[2].text,"We´ll just take them by force!");
					dialog.options=3;
					dialog.option[0].general_effect=0;//leave
					dialog.option[2].general_effect=2;//attack
					dialog.option[2].effect_parameter=2;//attack ship
					dialog.picture=1;//merchant

					//enough money
					if(shipslot[0].cargo[3]>=50){
						strcpy(dialog.option[1].text,"All right, let´s trade.");
						dialog.option[1].general_effect=3;//trade
							dialog.option[1].cargoplus[1]=20;//plus goods
							dialog.option[1].cargominus[3]=50;//minus money
					}
					//not enough money
					if(shipslot[0].cargo[3]<50){
						strcpy(dialog.option[1].text,"We don´t have the money.");
						dialog.option[1].general_effect=0;//leave
					}					
				}
				if(dialog.randomship.type==3){//colonial navy
					strcpy(dialog.text,"Well, well. What did we run into here? A pirate! A smelly, stupid, outlaw. Since I´m on a good mood, I promise I won´t blow you to bits if you have enough money. 100 pieces should do it.");
					
					strcpy(dialog.option[1].text,"You will have nothing but cold steel!");
					dialog.options=2;
					dialog.option[1].general_effect=2;//attack
					dialog.option[1].effect_parameter=2;//attack ship
					dialog.picture=5;//general

					//enough money
					if(shipslot[0].cargo[3]>=100){
						strcpy(dialog.option[0].text,"Here´s your stupid money! Now go away!");
						dialog.option[0].general_effect=3;//trade
							dialog.option[0].cargominus[3]=100;//minus money
					}
					//not enough money
					if(shipslot[0].cargo[3]<100){
						strcpy(dialog.option[0].text,"We don´t have enough money.");
						dialog.option[0].general_effect=2;//attack
						dialog.option[0].effect_parameter=2;//attack ship
					}					
				}
				if(dialog.randomship.type==4){//alien
					strcpy(dialog.text,"Kiinnostaako uhkapeli? Väliltä sata viiva miinus sata rahaa olisi luvassa.        --The translation computer cannot comprehend this proposal, but accepting to it might be somewhat of a gamble.--");

					strcpy(dialog.option[0].text,"Leave, we don´t understand you.");					
					strcpy(dialog.option[2].text,"Speak English or die alien bastard!");
					dialog.options=3;
					dialog.option[0].general_effect=0;//leave
					dialog.option[2].general_effect=2;//attack
					dialog.option[2].effect_parameter=2;//attack ship
					dialog.picture=6;//alien

					//gamble money
						strcpy(dialog.option[1].text,"All right, let´s gamble.");
						dialog.option[1].general_effect=3;//trade
							dialog.option[1].cargoplus[3]=randInt(0,100);//plus money
							dialog.option[1].cargominus[3]=randInt(0,100);//minus money
															
				}
				if(dialog.randomship.type==5){//traveller
					strcpy(dialog.text,"We were just visiting ");
					strcat(dialog.text,planet[randomplanet(-1)].name);
					strcat(dialog.text," and the fuel prices there are just extraordinary! So we didn´t buy any fuel there and we are soon running out of it. Would you be willing to sell some?");
						
					strcpy(dialog.option[0].text,"No, we´ll leave you here to rot.");					
					strcpy(dialog.option[1].text,"No, but your life might be worth taking!");					
					dialog.option[0].general_effect=0;//leave
					dialog.option[1].general_effect=2;//attack
					dialog.option[1].effect_parameter=2;//attack ship
					dialog.options=2;
					dialog.picture=3;//explorer

					//5 fuel
					if(shipslot[0].cargo[4]>5){
						strcpy(dialog.option[2].text,"We´ll trade 5 units of fuel for 30 pieces.");
						dialog.option[2].general_effect=3;//trade
							dialog.option[2].cargoplus[3]=30;//plus money
							dialog.option[2].cargominus[4]=5;//minus fuel
							dialog.options=3;
					}
					//10 fuel
					if(shipslot[0].cargo[4]>16){
						strcpy(dialog.option[3].text,"We´ll trade 15 units of fuel for 80 pieces.");
						dialog.option[3].general_effect=3;//trade
							dialog.option[3].cargoplus[3]=80;//plus money
							dialog.option[3].cargominus[4]=15;//minus fuel
							dialog.options=4;
					}					
				}
			}
			//offencive strategy
			if(dialog.randomship.strategy==2){
				if(dialog.randomship.type==0){//refugee
					strcpy(dialog.text,"The aliens just torched our homes on ");
					strcat(dialog.text,planet[randomplanet(-1)].name);
					strcat(dialog.text," and we are not going to take this abuse anymore! It´s time for you pirates to learn a lesson!");					
					
					strcpy(dialog.option[0].text,"You won´t stand a chance.");
					dialog.options=1;					
					dialog.option[0].general_effect=2;//attack
					dialog.option[0].effect_parameter=2;//attack ship
					dialog.picture=4;//refugee
				}
				if(dialog.randomship.type==1){//pirate
					strcpy(dialog.text,"I just heard from the colonial forces, that there is a price on your head. I think you are worth much more dead than alive!");
					
					strcpy(dialog.option[0].text,"Go ahead, take your best shot.");
					dialog.options=1;					
					dialog.option[0].general_effect=2;//attack
					dialog.option[0].effect_parameter=2;//attack ship
					dialog.picture=2;//pirate
				}
				if(dialog.randomship.type==2){//merchant
					strcpy(dialog.text,"So, thou palpable worm, thou hast lust for our capital! Thou wilt acquire nothing but death from us!");
					
					strcpy(dialog.option[0].text,"Sure you can try. Just go ahead!");
					dialog.options=1;					
					dialog.option[0].general_effect=2;//attack
					dialog.option[0].effect_parameter=2;//attack ship
					dialog.picture=1;//merchant
				}
				if(dialog.randomship.type==3){//colonial navy
					strcpy(dialog.text,"Your reign of terror has come to an end, the colonial navy is here to make sure of it.");
					if(randInt(0,2)==0)strcpy(dialog.text,"Capturing you will be my ticket for a promotion! Prepare to taste some colonial steel!");

					strcpy(dialog.option[0].text,"Let´s see if you can back your words!");
					dialog.options=1;					
					dialog.option[0].general_effect=2;//attack
					dialog.option[0].effect_parameter=2;//attack ship
					dialog.picture=5;//general
				}
				if(dialog.randomship.type==4){//alien
					strcpy(dialog.text,"Teidän surkeiden maan matojen aika on tullut, räjäytän teidät muussiksi!        --The translation computer cannot comprehend this message, but judging by the exclamation mark, it is most hostile.--");

					strcpy(dialog.option[0].text,"And the same to you alien swine!");
					dialog.options=1;					
					dialog.option[0].general_effect=2;//attack
					dialog.option[0].effect_parameter=2;//attack ship
					dialog.picture=6;//alien
				}
				if(dialog.randomship.type==5){//traveller
					strcpy(dialog.text,"No longer shall you prey on us innocent travellers. Surrender or face the consequences!");

					strcpy(dialog.option[0].text,"Consequences, schmonsequences!");
					dialog.options=1;					
					dialog.option[0].general_effect=2;//attack
					dialog.option[0].effect_parameter=2;//attack ship
					dialog.picture=3;//explorer
				}
			}

		}
	}
	//plot
	if(dialogtype==2){
		//on pluto
		if(value0==0){
			strcpy(dialog.text,"Haha! We captured the ship! The crew has elected you as their captain! I´m your first mate, the name´s Dusky Joe. Time to get into business. At the time we captured the ship we were orbiting Pluto, so I´d recommend visiting there first. The old captain and few high officers of this ship are at our cargo base as slaves. If you like, I could give you a few pointers on controlling the ship. So?");
			
			strcpy(dialog.option[0].text,"Alright, what do you suggest?");
			strcpy(dialog.option[1].text,"No no. I´ll figure it out myself!");
			dialog.options=2;
			
			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=1;//education
			dialog.option[1].general_effect=0;//leave
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;
		}
		//education
		if(value0==1){
			strcpy(dialog.text,"It is our mission as interplanetary pirates to kill, enslave and loot as much and as often as possible. In space we will find helpless ships to capture, and on planets we can get all sorts of malevolent missions. Other pirates may be after our loot. There may even be aliens! Remember our motto: GRR! Now a bit on the keyboard controls.");
			
			strcpy(dialog.option[0].text,"Go ahead.");
			strcpy(dialog.option[1].text,"I´ll figure them without you!");
			dialog.options=2;
			
			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=2;//education2
			dialog.option[1].general_effect=0;//leave
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;
		}
		//education2
		if(value0==2){
			strcpy(dialog.text,"Every time you don´t know what the keys are, you can find out the default keys by pressing F1. Most keys are fully configurable, but the factory defaults for flying in space are as follows: Up, down, left, right - move spacecraft. 1, 2 - shoot. 3 - switch ship. Enter - map. Space - mission log. Now would be a good time to visit Pluto. Go with my blessings!");
			
			strcpy(dialog.option[0].text,"I´m off.");
			dialog.options=1;
			
			dialog.option[0].general_effect=0;//leave
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;
		}
		//start plot
		if(value0==3){
			strcpy(dialog.text,"Great to meet you! I´m Diesel Dan, and I understand you are looking for a way to save your hide when the sun blows, no? I suppose everyone is, but for you, I have something special: I can get you in contact with the aliens. Just hear my offer, won´t you?");
			
			strcpy(dialog.option[0].text,"I´m listening.");
			dialog.options=1;
			
			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=4;//merchant has an offer
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=1;
		}
		//merchant has an offer
		if(value0==4){
			//take random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			dialog.option[0].mission.prize_plot=5;//meet contact on planet
			strcpy(dialog.option[0].mission.name,"Meet contact on ");//name mission
			strcat(dialog.option[0].mission.name,planet[dialog.option[0].mission.planet].name);
			strcpy(dialog.option[0].mission.text,"Diesel Dan asked you to meet his contact on ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,"). He might know the whereabouts of Dan´s brother, Petrol Pete.");//mission briefing

			strcpy(dialog.text,"I don´t know if you believe in prophecies, captain, but I have been told that I´m destined to die by the hand of my brother: Petrol Pete. I´d prefer him to die before me. However I cannot kill him myself, I don´t even know where he is! But there is someone on ");
			strcat(dialog.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.text," who does, and you must find him. Kill my brother, and I´ll tell you how to contact the aliens! Is it a deal?");
			
			strcpy(dialog.option[0].text,"Alright, I´ll look for him.");
			dialog.options=1;
			
			dialog.option[0].general_effect=5;//set mission
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=1;//merchant
		}
		//meet contact on planet
		if(value0==5){

			strcpy(dialog.text,"Captain, we have located Diesel Dan´s contact here on ");
			strcat(dialog.text,planet[ship[0].onplanet].name);
			strcat(dialog.text,". It seems there are two people here who can tell us where to find Dan´s brother. Both claim that if you meet one of them, you cannot meet the other. Would you like to meet the mangy pirate, or the deplorable explorer?");
			
			strcpy(dialog.option[0].text,"The pirate.");
			strcpy(dialog.option[1].text,"The explorer.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=6;//meet contact 1
			dialog.option[1].general_effect=1;//talk				
				dialog.option[1].effect_parameter=2;//talk plot
				dialog.option[1].effect_parameter2=7;//meet contact 2
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//meet contact 1 : pirate
		if(value0==6){
			
			create_random_ship(&dialog.randomship,1,0);//create ship for pirate

			//set mission
			dialog.option[0].mission.type=1;//items to planet	
			dialog.option[0].mission.planet=ship[0].onplanet;//this planet
			//for(q=0;q<5;q++)dialog.option[0].mission.cargominus[q]=0;//zero the cargo
			//for(q=0;q<5;q++)dialog.option[0].mission.cargoplus[q]=0;//zero the cargo
			dialog.option[0].mission.cargominus[3]=shipslot[0].cargo[3]+10;//take all players current money plus 10
			dialog.option[0].mission.prize_plot=8;//pirate tells of brother
			strcpy(dialog.option[0].mission.name,"Pay ");//name mission
			itoa(shipslot[0].cargo[3]+10,temprivi,10);
			strcat(dialog.option[0].mission.name,temprivi);
			strcat(dialog.option[0].mission.name," to pirate on ");
			strcat(dialog.option[0].mission.name,planet[ship[0].onplanet].name);
			strcpy(dialog.option[0].mission.text,"Diesel Dan´s contact was a pirate who asked ");//mission briefing
			itoa(shipslot[0].cargo[3]+10,temprivi,10);
			strcat(dialog.option[0].mission.text,temprivi);
			strcat(dialog.option[0].mission.text," gold pieces for the location of Dan´s brother. When you have enough money, return to ");
			strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].name);
			strcat(dialog.option[0].mission.text," (");
			strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].location);
			strcat(dialog.option[0].mission.text,").");


			strcpy(dialog.text,"You have come for Petrol Pete haven´t you? Fool! Why should I betray my old friend? Bah! For cash maybe? For ");
			itoa(shipslot[0].cargo[3]+10,temprivi,10);
			strcat(dialog.text,temprivi);
			strcat(dialog.text," gold pieces I just might do it. Get the money, then come back here.");
			
			
			strcpy(dialog.option[0].text,"I accept.");
			strcpy(dialog.option[1].text,"I´ll get the info from your dead body!");

			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=2;//attack ship
				dialog.option[1].mission.prize_plot=9;//pirate killed, find out about brother
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=2;//pirate
			ship[0].onplanet=-1;//take ship off planet
		}
		//meet contact 2 : explorer
		if(value0==7){
			create_random_ship(&dialog.randomship,1,0);//create ship for explorer/goon

			strcpy(dialog.text,"You are the rookie pirate, the hired gun. Yes, I know the one you seek, Petrol Pete. I´m his old enemy, rival you might say. Both in the game making business. Bloody war over a stupid space privateering game. He has sent a hitman after me as well, and I would very much like you to kill him. If you can kill the goon, I´m sure I could give you Pete´s location.");
						
			strcpy(dialog.option[0].text,"I´ll pulverize the goon then.");
			strcpy(dialog.option[1].text,"I´ll get the location from your dead body!");

			dialog.option[0].general_effect=6;//attack and get plot
				dialog.option[0].effect_parameter=2;//attack ship
				dialog.option[0].mission.prize_plot=11;//goon killed, find out about brother
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=2;//attack ship
				dialog.option[1].mission.prize_plot=10;//explorer killed, find out about brother
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=3;//explorer
		}
		//pirate tells of brother
		if(value0==8){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			dialog.option[0].mission.prize_plot=13;//meet Petrol Pete on planet
			strcpy(dialog.option[0].mission.name,"Meet Pete on ");//name mission
			strcat(dialog.option[0].mission.name,planet[dialog.option[0].mission.planet].name);
			strcpy(dialog.option[0].mission.text,"You were finally able to find out where the treacherous Petrol Pete resides. You are to go to ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,") and kick his ass.");//mission briefing


			strcpy(dialog.text,"Thank you for the money fellow pirate. Now: Petrol Pete has been lurking on ");
			strcat(dialog.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.text," for years. I don´t know what he does there, but I´m sure you can find in the local Space Bar.");
			
			
			strcpy(dialog.option[0].text,"Great! I´ll go get him.");

			dialog.option[0].general_effect=5;//set mission			
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=2;//pirate
		}
		//pirate killed, find out about brother
		if(value0==9){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			dialog.option[0].mission.prize_plot=13;//meet Petrol Pete on planet
			strcpy(dialog.option[0].mission.name,"Meet Pete on ");//name mission
			strcat(dialog.option[0].mission.name,planet[dialog.option[0].mission.planet].name);
			strcpy(dialog.option[0].mission.text,"You were finally able to find out where the dishonourable Petrol Pete resides. You are to go to ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,") and take care of him. Go already! This is just a logbook! You are wasting your time reading this! Press space to continue!");//mission briefing


			strcpy(dialog.text,"Oh mighty pirate lord, we have searched the wreckage of the pirate´s ship and found absolutely nothing of value. However we were able to find the location of Petrol Pete by looking up his name in the interplanetary phone book found in the wreck. I suggest confronting him next. Remember to check your logbook.");
			strcpy(dialog.option[0].text,"Set course.");
			strcpy(dialog.option[1].text,"Does it have my name also?");

			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=1;//talk				
				dialog.option[1].effect_parameter=2;//talk plot
				dialog.option[1].effect_parameter2=12;//phone book discussion
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//explorer killed, find out about brother
		if(value0==10){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			dialog.option[0].mission.prize_plot=13;//meet Petrol Pete on planet
			strcpy(dialog.option[0].mission.name,"Meet Pete on ");//name mission
			strcat(dialog.option[0].mission.name,planet[dialog.option[0].mission.planet].name);
			strcpy(dialog.option[0].mission.text,"You were finally able to find out where the disreputable Petrol Pete resides. You are to go to ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,") and split him.");//mission briefing


			strcpy(dialog.text,"The explorer´s computers indeed do contain the information we seek. Petrol Pete can be found at ");
			strcat(dialog.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.text,". And personally I want to congratulate you on that last shot you took at him. It was like no other shot before!");
			
			strcpy(dialog.option[0].text,"Set course.");

			dialog.option[0].general_effect=5;//set mission
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//goon killed, find out about brother
		if(value0==11){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			dialog.option[0].mission.prize_plot=13;//meet Petrol Pete on planet
			strcpy(dialog.option[0].mission.name,"Meet Pete on ");//name mission
			strcat(dialog.option[0].mission.name,planet[dialog.option[0].mission.planet].name);
			strcpy(dialog.option[0].mission.text,"The explorer told you where the ill-famed Petrol Pete resides. You are to go to ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,") and split him.");//mission briefing


			strcpy(dialog.text,"Thank you for killing that pesky goon! As for your reward: Petrol Pete can be found at ");
			strcat(dialog.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.text,". Go kill that slimy bastard. Oh, and give him my regards! May he rot where no man has ever decayed before!");
			
			strcpy(dialog.option[0].text,"Set course.");

			dialog.option[0].general_effect=5;//set mission
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=3;//explorer
		}
		//phone book discussion
		if(value0==12){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			dialog.option[0].mission.prize_plot=13;//meet Petrol Pete on planet
			strcpy(dialog.option[0].mission.name,"Meet Pete on ");//name mission
			strcat(dialog.option[0].mission.name,planet[dialog.option[0].mission.planet].name);
			strcpy(dialog.option[0].mission.text,"You were finally able to find out where the dishonourable Petrol Pete resides. You are to go to ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,") and take care of him. Go already! This is just a logbook! You are wasting your time reading this! Press space to continue!");//mission briefing


			strcpy(dialog.text,"No, there is no one listed under Player 1.");
			strcpy(dialog.option[0].text,"Such a shame. Well, let´s get going.");

			dialog.option[0].general_effect=5;//set mission
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//meet Petrol Pete on planet
		if(value0==13){

			//set mission: goto dan's planet
			dialog.option[1].mission.type=0;//goto planet
			dialog.option[1].mission.planet=dan_planet;//random planet
			dialog.option[1].mission.prize_plot=21;//diesel dan about to be killed
			strcpy(dialog.option[1].mission.name,"Go kill Dan on ");//name mission
			strcat(dialog.option[1].mission.name,planet[dialog.option[1].mission.planet].name);
			strcpy(dialog.option[1].mission.text,"Petrol Pete offered you 150 gold to betray Diesel Dan and kill him. You are to go to ");//mission briefing
			strcat(dialog.option[1].mission.text,planet[dialog.option[1].mission.planet].name);
			strcat(dialog.option[1].mission.text," (" );
			strcat(dialog.option[1].mission.text,planet[dialog.option[1].mission.planet].location);
			strcat(dialog.option[1].mission.text,") and kill him.");//mission briefing


			create_random_ship(&dialog.randomship,2,0);//create ship
			strcpy(dialog.text,"You have... found me. I know my brother has sent you after me. He and his stupid prophecies! Perhaps I should make those prophecies come true. Captain, I´ll make you a deal. I will give you 150 pieces if you go and kill Diesel Dan. Remember, you puny bastard, that I´m much harder to defeat than him!");
			strcpy(dialog.option[0].text,"I think I´ll still kill you!");
			strcpy(dialog.option[1].text,"Alright, I accept. Show me the money!");
			
			dialog.option[0].general_effect=6;//attack and get plot
				dialog.option[0].effect_parameter=2;//attack ship
				dialog.option[0].mission.prize_plot=17;//Petrol Pete killed
			dialog.option[1].general_effect=10;//set mission and trade
				dialog.option[1].cargoplus[3]=150;//give 150 gold
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=1;//merchant
		}
		//give random mission
		if(value0==14){
			a=randInt(0,2);	
			
				strcpy(dialog.text,"Mission giver: ");
				strcat(dialog.text,random_mission_name[randInt(0,random_mission_names)]);
				strcat(dialog.text,". Description: ");

			//goto random planet			
			if(a==0){
				dialog.option[0].mission.type=0;//goto planet
				dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
				dialog.option[0].mission.prize_plot=15;//random thank you
				dialog.option[0].mission.cargoplus[3]=randInt(40,160);
				
				strcpy(dialog.option[0].mission.name,"Go to ");//name mission
				strcat(dialog.option[0].mission.name,planet[dialog.option[0].mission.planet].name);
				strcpy(dialog.option[0].mission.text,"On ");//mission briefing
				strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].name);
				strcat(dialog.option[0].mission.text," you accepted a mission involving going to " );
				strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
				strcat(dialog.option[0].mission.text," (" );
				strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
				strcat(dialog.option[0].mission.text,").");//mission briefing
				if(dialog.option[0].mission.cargoplus[3]>0){
					strcat(dialog.option[0].mission.text," The pay is ");//mission briefing
					itoa(dialog.option[0].mission.cargoplus[3],temprivi,10);strcat(dialog.option[0].mission.text,temprivi);
					strcat(dialog.option[0].mission.text," gold coins.");//mission briefing
				}
				
				b=randInt(0,3);
				if(b==0){
					strcat(dialog.text,"Looking for a way to get to ");
					strcat(dialog.text,planet[dialog.option[0].mission.planet].name);
					strcat(dialog.text," to squash that dude. Willing to pay up to ");
					itoa(dialog.option[0].mission.cargoplus[3],temprivi,10);strcat(dialog.text,temprivi);
					strcat(dialog.text," in cash or Solar Energy stock.");
				}
				if(b==1){
					strcat(dialog.text,"Seeking for someone to take a package to ");
					strcat(dialog.text,planet[dialog.option[0].mission.planet].name);
					strcat(dialog.text,". No, there´s nothing in it. Absolutely nothing. Recommend keeping it in a cool place to avoid bad consequences. Paid ");
					itoa(dialog.option[0].mission.cargoplus[3],temprivi,10);strcat(dialog.text,temprivi);
					strcat(dialog.text," monetary thingys on completion.");
				}
				if(b==2){
					strcat(dialog.text,"Interested in a good pay for an easy job? Take me with you to ");
					strcat(dialog.text,planet[dialog.option[0].mission.planet].name);
					strcat(dialog.text," to meet with a contact. Paid ");
					itoa(dialog.option[0].mission.cargoplus[3],temprivi,10);strcat(dialog.text,temprivi);
					strcat(dialog.text," upon completion.");
				}
				
			dialog.option[0].general_effect=5;//set mission
			}
			//pick random fight			
			if(a==1){
				create_random_ship(&dialog.randomship,1,0);//create ship

				b=randInt(0,3);
				if(b==0){
					strcat(dialog.text,"Looking for someone to take care of a renegade ship on this planet. Good pay!");
				}
				if(b==1){
					strcat(dialog.text,"A good challenge for a tough pilot! We want to get rid of an enemy on this planet.");
				}
				if(b==2){
					strcat(dialog.text,"Get into show business! Take an arena fight to the death in front of an audience! Pay based on performance.");
				}
				
				dialog.option[0].general_effect=6;//attack and get plot
					dialog.option[0].effect_parameter=2;//attack ship
					dialog.option[0].mission.prize_plot=16;//random thank you with a good prize
			}


			strcpy(dialog.option[0].text,"Take the mission.");
			strcpy(dialog.option[1].text,"Decline.");
			dialog.option[1].general_effect=1;//talk
				dialog.option[1].effect_parameter=3;//talk with a spaceport
				dialog.option[1].effect_parameter2=ship[0].onplanet;//
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//random thank you
		if(value0==15){
			strcpy(dialog.text,"The mission was successful captain. We are resuming course.");
			strcpy(dialog.option[0].text,"Great!");
			if(randInt(0,3)==0)strcpy(dialog.option[0].text,"Carry on!");
			if(randInt(0,3)==0)strcpy(dialog.option[0].text,"Let´s go!");

			dialog.option[0].general_effect=0;//leave
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//random thank you with a good prize
		if(value0==16){
			
			//prize
			a=randInt(0,5);			
			switch(a){
			case 0:{dialog.option[0].cargoplus[a]=randInt(14,38);//plus slaves
				break;
				   }
			case 1:{dialog.option[0].cargoplus[a]=randInt(13,47);//plus contraband goods
				break;
				   }
			case 2:{dialog.option[0].cargoplus[a]=randInt(11,38);//plus illegal weapons
				break;
				   }
			case 3:{dialog.option[0].cargoplus[a]=randInt(20,150);//plus funds
				break;
				   }
			case 4:{dialog.option[0].cargoplus[a]=randInt(20,50);//plus fuel
				break;
				   }

			}

			strcpy(dialog.text,"The mission was successful captain. As a prize we have received ");

			switch(a){
			case 0:{
				itoa(dialog.option[0].cargoplus[a],temprivi,10);strcat(dialog.text,temprivi);				
				strcat(dialog.text," high quality slaves.");
				break;
				   }
			case 1:{
				itoa(dialog.option[0].cargoplus[a],temprivi,10);strcat(dialog.text,temprivi);				
				strcat(dialog.text," boxes of contraband goods.");
				break;
				   }
			case 2:{
				itoa(dialog.option[0].cargoplus[a],temprivi,10);strcat(dialog.text,temprivi);				
				strcat(dialog.text," crates of illegal weapons.");
				break;
				   }
			case 3:{
				itoa(dialog.option[0].cargoplus[a],temprivi,10);strcat(dialog.text,temprivi);				
				strcat(dialog.text," pieces of gold.");
				break;
				   }
			case 4:{
				itoa(dialog.option[0].cargoplus[a],temprivi,10);strcat(dialog.text,temprivi);
				strcat(dialog.text," units of fuel.");
				break;
				   }
			}
			
			strcpy(dialog.option[0].text,"Great!");
			if(randInt(0,3)==0)strcpy(dialog.option[0].text,"Carry on!");
			if(randInt(0,3)==0)strcpy(dialog.option[0].text,"Let´s go!");

			dialog.option[0].general_effect=3;//trade
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//Petrol Pete killed
		if(value0==17){

			//set mission: goto dan's planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=dan_planet;//dan's planet
			dialog.option[0].mission.prize_plot=19;//reward for killing petrol pete
			strcpy(dialog.option[0].mission.name,"Meet Dan for reward");//name mission
			strcpy(dialog.option[0].mission.text,"Petrol Pete has been killed and you are on your way to see his brother Dan for reward. Dan is on ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,").");//mission briefing
			
			strcpy(dialog.text,"Captain, now that Petrol Pete has been killed, we should go see Dan for the reward he promised.");
			strcpy(dialog.option[0].text,"Let´s see if he is true to his word.");
			
			dialog.option[0].general_effect=5;//set mission

			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//diesel dan killed
		if(value0==18){

			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			alien_planet=dialog.option[0].mission.planet;
			dialog.option[0].mission.prize_plot=20;//meet the aliens
			strcpy(dialog.option[0].mission.name,"Meet the aliens");//name mission
			strcpy(dialog.option[0].mission.text,"You found the location of the aliens from the charred remains of Diesel Dan. Meet the aliens on ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,").");//mission briefing
			dialog.option[1]=dialog.option[0];

			strcpy(dialog.text,"Master. Master. We have successfully dealt injustice to Diesel Dan. In addition we have deduced the location of the aliens from the transmission logs on Dan´s ship. It seems Dan had some dealings with the aliens. What exactly did he do with the aliens, remains a mystery. In any case we should be heading to ");
			strcat(dialog.text,planet[dialog.option[1].mission.planet].name);
			strcat(dialog.text," to discuss saving our lives.");

			strcpy(dialog.option[0].text,"I wonder what the aliens look like?");
			strcpy(dialog.option[1].text,"Yes, let´s go on.");
			
			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=5;//set mission
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//reward for killing petrol pete
		if(value0==19){

			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			alien_planet=dialog.option[0].mission.planet;
			dialog.option[0].mission.prize_plot=20;//meet the aliens
			strcpy(dialog.option[0].mission.name,"Meet the aliens");//name mission
			strcpy(dialog.option[0].mission.text,"Diesel Dan told you the location of the aliens. Meet the aliens on ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,").");//mission briefing
			dialog.option[1]=dialog.option[0];

			strcpy(dialog.text,"I see that you bring my brother´s head. This is good news! You were trustworthy after all. Now to your reward. Did I promise you the Moon? An extra pair of eyes? A good gaming experience? Ah, now I remember... You wanted to see the aliens! I´d recommend keeping clear of them and just waiting for the sun to blow, such horror is their visage! But I see you are determined. ");
			strcat(dialog.text,planet[dialog.option[1].mission.planet].name);
			strcat(dialog.text," is their base of operations. Now go.");

			dialog.dialog_options_place=30;
			strcpy(dialog.option[0].text,"Have fun with the head!");
			strcpy(dialog.option[1].text,"Farewell Dan!");
			
			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=5;//set mission
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=1;//merchant
		}
		//meet the aliens
		if(value0==20){
			dialog.ships=10;//amount of ships in battle
			create_random_ship(&dialog.randomship,4,0);//create ship (alien)

			strcpy(dialog.text,"It´s the famous pirate captain! Yes, you are here to be saved. Tsah tsah! Saa-aved from the menace! Do you want to fee-eel the beat? Dab dab! Hear the muusiic! Do you waant to be saa-aved?");
			strcpy(dialog.option[0].text,"Oh yes! Save me!");
			strcpy(dialog.option[1].text,"Die you alien salmon leech!");
			
			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=22;//alien conversation 0
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=2;//attack ship
				dialog.option[1].mission.prize_plot=23;//aliens killed

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=6;//alien
		}
		//Diesel Dan about to be killed
		if(value0==21){
			create_random_ship(&dialog.randomship,2,0);//create ship

			strcpy(dialog.text,"You are in league with that idiotic Petrol Pete? You have betrayed me! I will have my revenge! The prophecies will not come true!");
						
			strcpy(dialog.option[0].text,"Yup. You´re dead. Punk.");

			dialog.option[0].general_effect=6;//attack and get plot
				dialog.option[0].effect_parameter=2;//attack ship
				dialog.option[0].mission.prize_plot=18;//diesel dan killed
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=1;//merchant
		}
		//alien conversation 0
		if(value0==22){

			//set mission: end mission by flag
			dialog.option[0].mission.type=2;//end mission by flag
			dialog.option[0].mission.end_flag=0;//terminate by flag:alien money hunt mission
			dialog.option[0].mission.prize_plot=20;//!!! muista vaihtaa toinenkin
			strcpy(dialog.option[0].mission.name,"Pay the aliens");//name mission
			strcpy(dialog.option[0].mission.text,"The aliens offered you salvation in exchange for GAZILLION GOLD PIECES. Where are you going to get that sort of money?");


			strcpy(dialog.text,"And saved you shall be! Saved from the apocalypse! Saved from the supernova! But not without a price. A price so terrible, that the very floor shakes when I say what it is! You must pay us GAZILLION GOLD PIECES!");
			strcpy(dialog.option[0].text,"I´ll be back with the money!");
			strcpy(dialog.option[1].text,"Just what exactly do you do with all that gold?");
			
			dialog.option[0].general_effect=5;//set mission				
			dialog.option[1].general_effect=1;//talk				
				dialog.option[1].effect_parameter=2;//talk plot
				dialog.option[1].effect_parameter2=24;//alien conversation 1

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=6;//alien
			money_offer_timer=30000;//start money offer timer
		}
		//aliens killed
		if(value0==23){

			strcpy(dialog.text,"You have killed the aliens. Their technology is lost forever. Your crew starts a mutiny and elects Dusky Joe as their new captain. You are thrown into space to think about your hasty decisions.");
			strcpy(dialog.option[0].text,"Darn!");
			strcpy(dialog.option[1].text,"Hey this is unfair!");
			
			dialog.option[0].general_effect=11;//game over				
			dialog.option[1].general_effect=11;//game over

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=-1;//nothing
		}
		//alien conversation 1
		if(value0==24){			
			dialog.ships=10;//amount of ships in battle
			create_random_ship(&dialog.randomship,4,0);//create ship (alien)

			//set mission: end mission by flag
			dialog.option[0].mission.type=2;//end mission by flag
			dialog.option[0].mission.end_flag=0;//terminate by flag:alien money hunt mission
//!
			dialog.option[0].mission.prize_plot=20;//!!! muista vaihtaa toinenkin
			strcpy(dialog.option[0].mission.name,"Pay the aliens");//name mission
			strcpy(dialog.option[0].mission.text,"The aliens offered you salvation in exchange for GAZILLION GOLD PIECES. Where are you going to get that sort of money?");

			strcpy(dialog.text,"But that is a secret. A big secret! Where would the omnipotent aliens ever need gold? For fuel cells perhaps? What about time travelling? I assure that the real reason is none of these. Now go! And when you come back, be sure to have the money!");
			strcpy(dialog.option[0].text,"I´ll return with the money!");
			strcpy(dialog.option[1].text,"Die! I won´t accept such arrogance!");
			
			dialog.option[0].general_effect=5;//set mission				
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=2;//attack ship
				dialog.option[1].mission.prize_plot=23;//aliens killed

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=6;//alien

			money_offer_timer=30000;//start money offer timer
		}
		//money offer
		if(value0==25){
			dialog.ships=3;//amount of ships in battle
			create_random_ship(&dialog.randomship,2,0);//create ship

			strcpy(dialog.text,"Good day dear captain! I hear you are looking for a huge sum of money to pay the aliens, right? I might be of some assistance to you if you are willing to prove your good intend. I have selected a particularly nasty pirate ship for you to destroy. This pirate is so evil, that she even sells drugs and slaves! Kill the pirate, and I will help you get your money.");
			strcpy(dialog.option[0].text,"Alright, let me at ´em!");
			strcpy(dialog.option[1].text,"I prefer killing you!");
			
			dialog.option[0].general_effect=6;//attack and get plot
				dialog.option[0].effect_parameter=2;//attack ship
				dialog.option[0].mission.prize_plot=26;//pirate killed
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=2;//attack ship
				dialog.option[1].mission.prize_plot=27;//money offerer killed

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=4;//refugee
		}
		//pirate killed
		if(value0==26){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=27;//Atlas
			dialog.option[0].mission.prize_plot=28;//Meet Coalition
			strcpy(dialog.option[0].mission.name,"Meet Saturn Coalition");//name mission
			strcpy(dialog.option[0].mission.text,"A strange man told you that the Saturn Coalition is looking for skilled mercenaries. Their headquarters are on ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,").");//mission briefing
			dialog.option[1]=dialog.option[0];

			strcpy(dialog.text,"Now that you have proven you are on the side of good I will tell you my plan. The Saturn Coalition is looking for a way to escape the supernova, and they are looking for a skilled mercenary to run some errands. You can find their headquarters at Atlas.");
			strcpy(dialog.option[0].text,"Perhaps they have some money to steal.");
			strcpy(dialog.option[0].text,"Thanks you kind sir.");

			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=5;//set mission

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=4;//refugee
		}
		//money offerer killed
		if(value0==27){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=27;//Atlas
			dialog.option[0].mission.prize_plot=28;//Meet Coalition
			strcpy(dialog.option[0].mission.name,"Meet Saturn Coalition");//name mission
			strcpy(dialog.option[0].mission.text,"A pirate told you that the Saturn Coalition is looking for Skilled mercenaries. Their headquarters are on ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,").");//mission briefing
			dialog.option[1]=dialog.option[0];

			strcpy(dialog.text,"Thank you pirate brother, I´ve been hunting that idiot for years! Tell you what, I´ll reward your good deed. I was just on my way to Atlas to work for the Saturn Coalition. They are looking for a way to escape the supernova and they might have some work for you also. I hope they´ll save us!");
			strcpy(dialog.option[0].text,"I´ll look into it.");
			strcpy(dialog.option[1].text,"I´ll go there.");

			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=5;//set mission

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=2;//pirate
		}
		//Meet Coalition
		if(value0==28){

			strcpy(dialog.text,"Why have you come to the Saturn Coalition? Ah, yes! You are that promising new pirate I have been hearing so much about. Is it true that you single-handedly destroyed the whole Inca nation? In any case, we have a proposal for you. I know you are interested in getting a LOT of money, I think we can help you there.");
			
			strcpy(dialog.option[0].text,"Go on.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=29;//meet Coalition 2
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=7;//Coalition agent
		}
		//Meet Coalition 2
		if(value0==29){

			strcpy(dialog.text,"You see, the sun is going to blow up any time now, and we at the Saturn Coalition aren´t going to sit idly by while Earthlings plans to take their planet out of the solar system with a quasi-quintuplet-device. Here is where you come in: You must raid the whole planet! Get us the device, the rest is yours to keep.");
			
			strcpy(dialog.option[0].text,"I hear you.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=30;//meet Coalition 3
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=7;//Coalition agent
		}
		//Meet Coalition 3
		if(value0==30){

			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=randomplanet(ship[0].onplanet);//random planet
			dialog.option[0].mission.prize_plot=31;//meet the general
			strcpy(dialog.option[0].mission.name,"See the general");//name mission
			strcpy(dialog.option[0].mission.text,"You agreed to work for the Saturn Coalition. Your first assignment is to meet a general on ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,").");//mission briefing

			//set mission: goto random planet
			dialog.option[1].mission.type=0;//goto planet
			dialog.option[1].mission.planet=randomplanet(ship[0].onplanet);//random planet
			dialog.option[1].mission.prize_plot=32;//meet the refugee
			strcpy(dialog.option[1].mission.name,"See the refugee");//name mission
			strcpy(dialog.option[1].mission.text,"You agreed to work for the Saturn Coalition. Your first assignment is to meet a refugee on ");//mission briefing
			strcat(dialog.option[1].mission.text,planet[dialog.option[1].mission.planet].name);
			strcat(dialog.option[1].mission.text," (" );
			strcat(dialog.option[1].mission.text,planet[dialog.option[1].mission.planet].location);
			strcat(dialog.option[1].mission.text,").");//mission briefing

			strcpy(dialog.text,"It is not possible to launch a direct assault against earth. First we must find a weakness in Earth´s defences. I have two contacts: a corrupt Earth general who wishes to join us, and a refugee from Earth. He was a scientist with the quasi-quintuplet-device program until his supervisors found that he had been using the device to make popcorn.");

			strcpy(dialog.option[0].text,"I´ll speak with the general.");
			strcpy(dialog.option[1].text,"I´ll go see the refugee.");
			
			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=5;//set mission
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=7;//Coalition agent
		}
		//meet the general
		if(value0==31){
			dialog.ships=3;//amount of ships in battle
			create_random_ship(&dialog.randomship,3,0);//create ship
			
			//set mission
			dialog.option[0].mission.type=1;//items to planet	
			dialog.option[0].mission.planet=ship[0].onplanet;//this planet
			dialog.option[0].mission.cargominus[3]=shipslot[0].cargo[3]+200;//take all players current money plus 200
			dialog.option[0].mission.prize_plot=33;//paid general
			strcpy(dialog.option[0].mission.name,"Pay ");//name mission
			itoa(dialog.option[0].mission.cargominus[3],temprivi,10);
			strcat(dialog.option[0].mission.name,temprivi);
			strcat(dialog.option[0].mission.name," to general");
			strcpy(dialog.option[0].mission.text,"The general wanted you to pay him ");//mission briefing
			itoa(dialog.option[0].mission.cargominus[3],temprivi,10);
			strcat(dialog.option[0].mission.text,temprivi);
			strcat(dialog.option[0].mission.text," gold pieces for information on how to defeat Earth. Take the money to ");
			strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].name);
			strcat(dialog.option[0].mission.text," (");
			strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].location);
			strcat(dialog.option[0].mission.text,").");


			strcpy(dialog.text,"Who would have thought that our Federation would some day lie in ruins? Who would have thought that the once mighty Saturn Coalition would send a low life pirate to deal with me in hopes of saving their hides? I will betray Earth, but it would be grossly stupid to do it without a price! You will pay ");
			itoa(dialog.option[0].mission.cargominus[3],temprivi,10);strcat(dialog.text,temprivi);
			strcat(dialog.text," gold pieces!");

			strcpy(dialog.option[0].text,"I´ll get you the money, can I have a receipt?");
			strcpy(dialog.option[1].text,"Die you cowardly bastard!");
			
			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=2;//attack ship
				dialog.option[1].mission.prize_plot=34;//killed general

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=5;//general
		}
		//meet the refugee
		if(value0==32){			
			dialog.ships=3;//amount of ships in battle
			create_random_ship(&dialog.randomship,3,0);//create ship

			
			//set mission
			dialog.option[0].mission.type=1;//items to planet	
			dialog.option[0].mission.planet=ship[0].onplanet;//this planet
			dialog.option[0].mission.cargominus[3]=shipslot[0].cargo[3]+200;//take all players current money plus 200
			dialog.option[0].mission.prize_plot=35;//paid refugee
			strcpy(dialog.option[0].mission.name,"Pay ");//name mission
			itoa(dialog.option[0].mission.cargominus[3],temprivi,10);
			strcat(dialog.option[0].mission.name,temprivi);
			strcat(dialog.option[0].mission.name," to the refugee");
			strcpy(dialog.option[0].mission.text,"The refugee scientist wanted you to pay him ");//mission briefing
			itoa(dialog.option[0].mission.cargominus[3],temprivi,10);
			strcat(dialog.option[0].mission.text,temprivi);
			strcat(dialog.option[0].mission.text," gold pieces for information on how to defeat Earth. Take the money to ");
			strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].name);
			strcat(dialog.option[0].mission.text," (");
			strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].location);
			strcat(dialog.option[0].mission.text,").");


			strcpy(dialog.text,"That´s what you get for 20 years of faithful service! They dump you! Really, I had nothing to do with that darned popcorn! When you blast the whole Earth into dust, remember to tell them that I am to blame. And now, there is only one thing we have to take care of first: My price is ");
			itoa(dialog.option[0].mission.cargominus[3],temprivi,10);strcat(dialog.text,temprivi);
			strcat(dialog.text," gold!");
			strcpy(dialog.option[0].text,"I´ll get you the money.");
			strcpy(dialog.option[1].text,"I won´t pay. Decease you bastard!");
			
			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=2;//attack ship
				dialog.option[1].mission.prize_plot=36;//killed refugee

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=4;//refugee
		}
		//paid general
		if(value0==33){

			strcpy(dialog.text,"Thank you. Here´s what I know: Most of Earth´s forces are garrisoned in a space station orbiting Earth. If you manage to destroy the station, they have no hope against you! Actually they´ll still probably kick your butt, but you should at least have a chance.");
			
			strcpy(dialog.option[0].text,"Marvelous.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=37;//message received from coalition
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=5;//general
		}
		//killed general
		if(value0==34){

			strcpy(dialog.text,"Searching the remains of the general´s ship we have found important details of Earth´s defences. It seems that most of Earth´s forces are garrisoned in a space station orbiting Earth. If we manage to destroy the station, we should have a good chance of defeating Earth.");
			
			strcpy(dialog.option[0].text,"Excellent.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=37;//message received from coalition
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//paid refugee
		if(value0==35){

			strcpy(dialog.text,"You may have heard that it is impossible to defeat Earth´s vast forces. That´s total bogus, you can take out most of their forces by blowing up their space station. I´d recommend a terrorist strike or a suicide attack. Make them pay!");
			
			strcpy(dialog.option[0].text,"Fabulous.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=37;//message received from coalition
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=4;//refugee
		}
		//killed refugee
		if(value0==36){

			strcpy(dialog.text,"Captain, our squad with the tweezers has concluded their prolonged search of the ship wreckage. They found documents revealing that Earth´s forces are based in a single space station orbiting Earth. If we are able to destroy the station, we can easily topple Earth!");
			
			strcpy(dialog.option[0].text,"Fantastic.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=37;//message received from coalition
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//message received from coalition
		if(value0==37){

			strcpy(dialog.text,"We have just received a message from the Saturn Coalition. They have promised us military assistance in conquering Earth. They also said that it is up to us to blow the space station. We´ve come a long way captain. Now we are about to loot a whole planet!");
			
			strcpy(dialog.option[0].text,"I see.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=38;//message received from coalition 2
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//message received from coalition 2
		if(value0==38){

			strcpy(dialog.text,"It isn´t possible to blow up a space station with normal explosives. We have to find something bigger and faster. You know, I used to work as a miner at the asteroid belt. There was a huge asteroid mounted laser drill there, I think it is still operational even with these recent pirate uprisings. We could use it to blow up the station.");
			
			strcpy(dialog.option[0].text,"Go on.");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=39;//go to asteroid 2
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//go to asteroid 2
		if(value0==39){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=70;//asteroid 2
			dialog.option[0].mission.prize_plot=40;//at asteroid 2
			strcpy(dialog.option[0].mission.name,"Find the drill");//name mission
			strcpy(dialog.option[0].mission.text,"You are looking for a weapon big enough to blow up a spacestation. One such could be the laser drill located on ");//mission briefing
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,").");//mission briefing
			dialog.option[1]=dialog.option[0];

			strcpy(dialog.text,"If my information is correct, there should be one such laser drill on Asteroid 2. It is likely heavily guarded, because these are very expensive pieces of mining machinery. Once we steal it, we have to find a platform to mount it on since our ships don´t have enough power to properly operate it.");
			strcpy(dialog.option[0].text,"On my way.");
			strcpy(dialog.option[1].text,"Set course to Asteroid 2!");

			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=5;//set mission

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//at asteroid 2
		if(value0==40){

			strcpy(dialog.text,"Scarlet Corporation owns this mine and it´s equipment. If you do not have an appointment, we kindly ask you to leave. We do not buy anything, and we prefer not selling anything unless you are very wealthy. If you find yourselves here in malicious intends, remember that this mine is heavily guarded.");
			
			strcpy(dialog.option[0].text,"Give us the drill!");
			strcpy(dialog.option[1].text,"Would you sell your drill?");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=41;//at asteroid 2: talk 2
			dialog.option[1].general_effect=1;//talk				
				dialog.option[1].effect_parameter=2;//talk plot
				dialog.option[1].effect_parameter2=41;//at asteroid 2: talk 2
			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=3;//explorer
		}
		//at asteroid 2: talk 2
		if(value0==41){
			
			dialog.ships=4;//amount of ships in battle
			create_random_ship(&dialog.randomship,3,0);//create ship
			
			//set mission
			dialog.option[0].mission.type=1;//items to planet	
			dialog.option[0].mission.planet=ship[0].onplanet;//this planet
			dialog.option[0].mission.cargominus[0]=100;//take hundred slaves
			dialog.option[0].mission.prize_plot=42;//drill is ours
			strcpy(dialog.option[0].mission.name,"Pay ");//name mission
			itoa(dialog.option[0].mission.cargominus[0],temprivi,10);
			strcat(dialog.option[0].mission.name,temprivi);
			strcat(dialog.option[0].mission.name," to the miner");
			strcpy(dialog.option[0].mission.text,"The miner was willing to trade the drill for ");//mission briefing
			itoa(dialog.option[0].mission.cargominus[0],temprivi,10);
			strcat(dialog.option[0].mission.text,temprivi);
			strcat(dialog.option[0].mission.text," slaves. Take the slaves to ");
			strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].name);
			strcat(dialog.option[0].mission.text," (");
			strcat(dialog.option[0].mission.text,planet[ship[0].onplanet].location);
			strcat(dialog.option[0].mission.text,").");


			strcpy(dialog.text,"You want our laser drill? If we sell it to you, what will we mine this asteroid field with? Slaves, of course! Captain, for 100 slaves this laser drill is yours. Remember, that it is highly sought-after: I´ve actually heard that some pirates working for the Saturn Coalition might be looking for it. Do you accept this trade?");			
			strcpy(dialog.option[0].text,"I´ll get the you slaves. You evil slaver!");
			strcpy(dialog.option[1].text,"Over your dead bodies!");
			
			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=1;//attack asteroid
				dialog.option[1].mission.prize_plot=42;//drill is ours

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=3;//explorer
		}
		//drill is ours
		if(value0==42){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=9;//The Moon
			dialog.option[0].mission.prize_plot=43;//about to attack moon
			strcpy(dialog.option[0].mission.name,"Attack Moon");//name mission
			strcpy(dialog.option[0].mission.text,"Now that you have the laser drill, you are on your way to conquer Earth´s Moon to place the drill on.");//mission briefing			
			dialog.option[1]=dialog.option[0];

			strcpy(dialog.text,"The drill is ours! Gnnnng! It reminds me of my dentist. Now that we have a BIG gun, we should put it to use. The Saturn Coalition has suggested that we place it on Earth´s moon and shoot down the space station. Once the station is destroyed, the Coalition´s forces will lure the rest of Earth´s forces away from Earth allowing us to strike!");
			strcpy(dialog.option[0].text,"Let´s go see the Moon!");
			strcpy(dialog.option[1].text,"The Moon will soon be ours!");

			dialog.option[0].general_effect=5;//set mission
			dialog.option[1].general_effect=5;//set mission

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//about to attack moon
		if(value0==43){
			strcpy(dialog.text,"Your forces are in orbit above Moon. Now is the time to kick some lunar ass!");
			strcpy(dialog.option[0].text,"Attack!");

			dialog.option[0].general_effect=6;//attack and get plot
				dialog.option[0].effect_parameter=0;//attack planet
				dialog.option[0].effect_parameter2=9;//attack Moon
				dialog.option[0].mission.prize_plot=44;//earth attacks
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=-1;//nothing
		}
		//earth attacks
		if(value0==44){
			
			dialog.ships=3;//amount of ships in battle
			create_random_ship(&dialog.randomship,3,0);//create ship

			strcpy(dialog.text,"Sir! Quickly! Earth has sent a squadron after us! We have to protect the drill!");
			strcpy(dialog.option[0].text,"Defend!");

			dialog.option[0].general_effect=6;//attack and get plot
				dialog.option[0].effect_parameter=2;//attack ship
				dialog.option[0].mission.prize_plot=-5;//show cutscene:station blows
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//about to attack Earth
		if(value0==45){
			strcpy(dialog.text,"Below you is Earth. Your ticket to salvation. The last handful of ships approach you. Without hesitation you give the command:");
			strcpy(dialog.option[0].text,"Attack!");
			strcpy(dialog.option[1].text,"Charge!");
			strcpy(dialog.option[2].text,"Engage!");

			dialog.option[0].general_effect=6;//attack and get plot
				dialog.option[0].effect_parameter=0;//attack planet
				dialog.option[0].effect_parameter2=2;//attack Earth
				dialog.option[0].mission.prize_plot=46;//earth conquered
			dialog.option[1].general_effect=6;//attack and get plot
				dialog.option[1].effect_parameter=0;//attack planet
				dialog.option[1].effect_parameter2=2;//attack Earth
				dialog.option[1].mission.prize_plot=46;//earth conquered
			dialog.option[2].general_effect=6;//attack and get plot
				dialog.option[2].effect_parameter=0;//attack planet
				dialog.option[2].effect_parameter2=2;//attack Earth
				dialog.option[2].mission.prize_plot=46;//earth conquered

			dialog.options=3;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=-1;//nothing
		}
		//earth conquered
		if(value0==46){

			strcpy(dialog.text,"Earth lies in ruins. The whole planet is at your mercy. Your delegation lands to present your demands. Huge amounts of gold are transferred to your freighters. The quasi-quintuplet-device is given to the Coalition. This is the raid of the century! Suddenly, the gold vanishes from your cargo holds!");
			
			strcpy(dialog.option[0].text,"Press enter to continue.");			

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=47;//Coalition laughs			
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=-1;//nothing
		}
		//Coalition laughs
		if(value0==47){
			//take all player's gold
			shipslot[0].cargo[3]=0;

			strcpy(dialog.text,"Buahaha! Hahahaha! You should have seen your eyes when we used our new quasi-quintuplet-device to transfer the gold from under your noses! Now we shall go to the aliens and claim our redemption. You cannot stop us, we have too many ships on our side! End transmission. What? Isn´t it voice activated? I have to push this button? Click.");
			
			strcpy(dialog.option[0].text,"I´ll catch you!");			
			strcpy(dialog.option[1].text,"Just you wait!");

			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=48;//new drill		
			dialog.options=1;			

			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=7;//Coalition agent
		}
		//new drill
		if(value0==48){
			//set mission: goto random planet
			dialog.option[0].mission.type=0;//goto planet
			dialog.option[0].mission.planet=alien_planet;//The alien planet
			dialog.option[0].mission.prize_plot=49;//final talk with coalition
			strcpy(dialog.option[0].mission.name,"Crush the Coalition");//name mission
			strcpy(dialog.option[0].mission.text,"With your new mobile drill, you are on your way to crush the traitorous Saturn Coalition. They are likely at ");//mission briefing			
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].name);
			strcat(dialog.option[0].mission.text," (" );
			strcat(dialog.option[0].mission.text,planet[dialog.option[0].mission.planet].location);
			strcat(dialog.option[0].mission.text,").");//mission briefing
			dialog.option[1]=dialog.option[0];

			strcpy(dialog.text,"Good news captain! Our engineers have modified the laser drill and mounted it on a freighter craft. When we go after the Coalition, it will be a great advantage on our side. The Coalition is likely trying to make a deal with the aliens at the alien base, we should go there.");
			strcpy(dialog.option[0].text,"Let´s hunt them down!");
			strcpy(dialog.option[1].text,"Nobody steals our gold!");

			create_random_ship(&dialog.randomship,4,5);//the new drill
			dialog.randomship.energy=230;
			dialog.randomship.ship_basea=ship_base[7];


			dialog.option[0].general_effect=12;//give ship and set mission
				dialog.option[0].effect_parameter=0;//give ship
			dialog.option[1].general_effect=12;//give ship and set mission
				dialog.option[1].effect_parameter=0;//give ship

			dialog.options=2;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=0;//dusky joe
		}
		//final talk with coalition
		if(value0==49){

			strcpy(dialog.text,"Do not mess with us captain! We took your gold fair and square. The device we got from Earth apparently cannot take us out of this solar system, but with your gold, the aliens can! We have already agreed to a deal with the aliens, so if you take the gold, they will not be pleased. Now go away!");
			
			strcpy(dialog.option[0].text,"GIVE ME MY GOLD!");			
			strcpy(dialog.option[1].text,"Perhaps you understand my weapons better.");
			strcpy(dialog.option[2].text,"Dying time is here!");	
	
			dialog.option[0].general_effect=1;//talk				
				dialog.option[0].effect_parameter=2;//talk plot
				dialog.option[0].effect_parameter2=50;//about to attack coalition		
			dialog.option[1].general_effect=1;//talk				
				dialog.option[1].effect_parameter=2;//talk plot
				dialog.option[1].effect_parameter2=50;//about to attack coalition		
			dialog.option[2].general_effect=1;//talk				
				dialog.option[2].effect_parameter=2;//talk plot
				dialog.option[2].effect_parameter2=50;//about to attack coalition		
			dialog.options=3;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=7;//Coalition agent
		}
		//about to attack coalition
		if(value0==50){
			strcpy(dialog.text,"This is the final battle. Only the sizable Saturnian task force stands between you and the aliens. No one messes with space pirates!");
			strcpy(dialog.option[0].text,"Press enter to continue.");

			planet[alien_planet].military=3;
			dialog.option[0].general_effect=6;//attack and get plot
				dialog.option[0].effect_parameter=0;//attack planet
				dialog.option[0].effect_parameter2=alien_planet;//attack the alien planet
				dialog.option[0].mission.prize_plot=-6;//show cutscene:station blows
			dialog.options=1;
			
			dialog.infos=0;

			dialog.lowpictureclass=-1;
			dialog.lowpicturenumber=-1;	
			dialog.picture=-1;//nothing
		}
		//offer for fuel
		if(value0==51){//merchant
			
					dialog.ships=1;//amount of ships in battle
					create_random_ship(&dialog.randomship,1,0);//create ship

					strcpy(dialog.text,"I see you don´t currently have any fuel. I can offer you some:");
					strcat(dialog.text," Five liters for 30 gold.");
						
					strcpy(dialog.option[0].text,"No, we´re not interested.");					
					strcpy(dialog.option[2].text,"We´ll just take that fuel by force!");
					dialog.options=3;
					dialog.option[0].general_effect=0;//leave
					dialog.option[2].general_effect=2;//attack
					dialog.option[2].effect_parameter=2;//attack ship
					dialog.picture=1;//merchant

					//enough money
					if(shipslot[0].cargo[3]>=30){
						strcpy(dialog.option[1].text,"All right, let´s trade.");
						dialog.option[1].general_effect=3;//trade
							dialog.option[1].cargoplus[4]=5;//plus fuel
							dialog.option[1].cargominus[3]=30;//minus money
					}
					//not enough money
					if(shipslot[0].cargo[3]<30){
						strcpy(dialog.option[1].text,"We don´t have the money.");
						dialog.option[1].general_effect=0;//leave
					}	
					dialog.picture=1;//merchant
				}
	}
/*
Good day dear captain! I hear you are looking for a huge sum of money to pay the aliens, right? I might be of some assistance to you if you are willing to prove your good intend. I have selected a particularly nasty pirate ship for you to destroy. They even sell drugs and slaves! Kill the pirate, and I will help you get your money.
	Alright, let me at ´em!
		ukko:Now that you have proven you are on the side of good I will tell you my plan. The Saturn Coalition is looking for a way to escape the supernova, and they are looking for a skilled mercenary to run some errands. You can find their headquarters at Atlas.
	I prefer killing you!
		piraatti:Thank you pirate brother, I´ve been hunting that idiot for years! Tell you what, I´ll reward your good deed. I was just on my way to Atlas to work for the Saturn Coalition. They are looking for a way to escape the supernova and they might have some work for you also. I hope they´ll save us!
Why have you come to the Saturn Coalition? Ah, yes! You are that promising new pirate I have been hearing so much about. Is it true that you single-handedly destroyed the whole Inca nation? In any case, we have a proposal for you. I know you are interested in getting a LOT of money, I think we can help you there.
You see, the sun is going to blow up any time now, and we at the Saturn Coalition aren´t going to sit idly by while Earthlings plans to take their planet out of the solar system with a quasi-quintuplet-device. Here is where you come in: You must raid the whole planet! Get us the device, the rest is yours to keep.
It is not possible to launch a direct assault against earth. First we must find a weakness in Earth´s defences. I have two contacts: a corrupt Earth general who wishes to join us, and a refugee from Earth. He was a scientist with the quasi-quintuplet-device program until his supervisors found that he had been using the device to make popcorn.
	I´ll speak with the general.
		Who would have thought that our Federation would some day lie in ruins? Who would have thought that the once mighty Saturn Coalition would send a low life pirate to deal with me in hopes of saving their hides? I will betray Earth, but it would be grossly stupid to do it without a price! You will pay one thousand gold pieces!
			Here´s your money, can I have a receipt?
				Thank you. Here´s what I know: Most of Earth´s forces are garrisoned in a space station orbiting Earth. If you manage to destroy the station, they have no hope against you! Actually they´ll still probably kick your butt, but you should at least have a chance.
			Die you cowardly bastard!
				Searching the remains of the general´s ship we have found important details of Earth´s defences. It seems that most of Earth´s forces are garrisoned in a space station orbiting Earth. If we manage to destroy the station, we should have a good chance of defeating Earth.
	I´ll go see the refugee.
		That´s what you get for 20 years of faithful service! They dump you! Really, I had nothing to do with that darned popcorn! When you blast the whole Earth into dust, remember to tell them that I am to blame. And now, there is only one thing we have to take care of first: My price is 1000 gold.
			I´ll pay. Let´s hear it.
				You may have heard that it is impossible to defeat Earth´s vast forces. That´s total bogus, you can take out most of their forces by blowing up their space station. I´d recommend a terrorist strike or a suicide attack. Make them pay!
			I won´t pay. Decease you bastard!
				Captain, our squad with the tweezers has concluded their prolonged search of the ship wreckage. They found documents revealing that Earth´s forces are based in a single space station orbiting Earth. If we are able to destroy the station, we can easily topple Earth!
We have just received a message from the Saturn Coalition. They have promised us military assistance in conquering Earth. They also said that it is up to us to blow the space station. We´ve come a long way captain. Now we are about to loot a whole planet!
It isn´t possible to blow up a space station with normal explosives. We have to find something bigger and faster. You know, I used to work as a miner at the asteroid belt. There was a huge asteroid mounted laser drill there, I think it is still operational even with these recent pirate uprisings. We could use it to blow up the station.
If my information is correct, there should be one such laser drill on Asteroid 2. It is likely heavily guarded, because these are very expensive pieces of mining machinery. Once we steal it, we have to find a platform to mount it on since our ships don´t have enough power to properly operate it.
Scarlet Corporation owns this mine and it´s equipment. If you do not have an appointment, we kindly ask you to leave. We do not buy anything, and we prefer not selling anything unless you are very wealthy. If you find yourselves here in malicious intends, remember that this mine is heavily guarded.
	We need the drill.
You want our laser drill? If we sell it to you, what will we mine this asteroid field with? Slaves, of course! Captain, for 100 slaves this laser drill is yours. Remember, that it is highly sought-after: I´ve actually heard that some pirates working for the Saturn Coalition might be looking for it. Do you accept this trade?
	Here are your slaves. You may actually know some of them.
	Over your dead bodies!
The drill is ours! You know that drill reminds me of my dentist. Now that we have it, we should put it to use. The Saturn Coalition has suggested that we place it on Earth´s moon and shoot down the space station. Once the station is destroyed, the Coalition forces will lure the rest of Earth´s forces away from Earth allowing us to strike.
Your forces are in orbit above Moon. Now is the time to kick some lunar ass!
	Attack!
Sir! Quickly! Earth has sent a squadron after us! We have to protect the drill!
välianimaatio:The drill is carefully targeted and fired. Earth´s portentous space station is blown up within seconds. While Coalition´s forces engage what is left of Earth´s fleet, you prepare to attack.
Below you is Earth. Your ticket to salvation. The last handful of ships approach you. Without hesitation you give the command:
	Attack!
	Charge!
	Engage!
Earth lies in ruins. The whole planet is at your mercy. Your delegation lands to present your demands. Huge amounts of gold are transferred to your freighters. The quasi-quintuplet-device is given to the Coalition. This is the raid of the century! Suddenly, the gold vanishes from your cargo holds!
Buahaha! Hahahaha! You should have seen your eyes when we used our new quasi-quintuplet-device to transfer the gold from under your noses! Now we shall go to the aliens and claim our redemption. You cannot stop us, we have too many ships on our side! End transmission. What? Isn't it voice activated? I have to push this button? Click.
Good news captain! Our engineers have modified the laser drill and mounted it on a freighter craft. When we go after the Coalition, it will be a great advantage on our side.
Do not mess with us captain! We took your gold fair and square. The device we got from Earth apparently cannot take us out of this solar system, but with your gold, the aliens can! We have already agreed to a deal with the aliens, so if you take the gold, they will not be pleased. Now go away!
	GIVE ME MY GOLD!
	Perhaps you understand my weapons better.
	Dying time is here!
This is the final battle. Only the sizable Saturnian task force stands between you and the aliens. No one messes with space pirates!
You pay the aliens what they asked: one GAZILLION GOLD PIECES. You and your crew are taken aboard their mysterious ships and you are taken to a safe distance away from the sun. Then, with great anticipation, the aliens push a button that blows up the sun.
So, did you find your salvation from the menace that destroyed mankind. And having no further concern, you and your companions sought adventure in the alien worlds. Many wars and feuds did you fight. Honor and fear were heaped upon your name. In time, you became an emperor by your own hand.... But that is another story.

*/



















































	//spaceport
	if(dialogtype==3){
		//if(value0==0)
		{
			dialog.dialog_options_place=-55;
			strcpy(dialog.text,"Spaceport: ");
			strcat(dialog.text,planet[ship[0].onplanet].name);
			if(shipslot[0].cargo[3]<300)
			strcat(dialog.text,". The local merchants eye you suspiciously. ");
			else
			strcat(dialog.text,". The local merchants greet you warmly. ");

			if((planet[value0].prize[0]+planet[value0].prize[1]+planet[value0].prize[2])/3>=2.0f)
			strcat(dialog.text,"There seems to be a good demand for piratey goods here.");
			else
			strcat(dialog.text,"There seems to be little demand for piratey goods here.");
			
			strcpy(dialog.option[0].text,"Leave spaceport");
			strcpy(dialog.option[1].text,"Ask for a mission");			
			strcpy(dialog.option[6].text,"Repair/sell ships");	
			dialog.options=7;
			
			
			dialog.option[0].general_effect=0;//leave
			dialog.option[1].general_effect=1;//talk				
				dialog.option[1].effect_parameter=2;//talk plot
				dialog.option[1].effect_parameter2=14;//give random mission
			//fuel	
				dialog.option[2].default_selection=2;
				strcpy(dialog.option[2].text,"Buy 10 liters of fuel for ");
				itoa(planet[value0].prize[4],temprivi,10);strcat(dialog.option[2].text,temprivi);
				strcat(dialog.option[2].text,"/liter");
				dialog.option[2].general_effect=8;//trade and continue talking
					dialog.option[2].cargominus[3]=10*planet[value0].prize[4];//minus money
					dialog.option[2].cargoplus[4]=10;//plus fuel
				dialog.option[2].effect_parameter=3;//talk with a spaceport
				dialog.option[2].effect_parameter2=ship[0].onplanet;//			
			if(shipslot[0].cargo[3]<10*planet[value0].prize[4]){
				strcpy(dialog.option[2].text,"Not enough money to buy fuel");
				dialog.option[2].general_effect=7;//do nothing
			}
			if(shipslot[0].cargo[4]>=100){
				strcpy(dialog.option[2].text,"Fuel tanks full");
				dialog.option[2].general_effect=7;//do nothing
			}
			//contraband goods
				dialog.option[3].default_selection=3;
				strcpy(dialog.option[3].text,"Sell all contraband goods for ");
				itoa(planet[value0].prize[1],temprivi,10);strcat(dialog.option[3].text,temprivi);
				strcat(dialog.option[3].text,"/packet");
				dialog.option[3].general_effect=8;//trade and continue talking
					dialog.option[3].cargoplus[3]=shipslot[0].cargo[1]*planet[value0].prize[1];//plus money
					dialog.option[3].cargominus[1]=shipslot[0].cargo[1];//minus contraband goods
				dialog.option[3].effect_parameter=3;//talk with a spaceport
				dialog.option[3].effect_parameter2=ship[0].onplanet;//
			if(shipslot[0].cargo[1]<=0){
				strcpy(dialog.option[3].text,"No contraband goods in cargo hold");
				dialog.option[3].general_effect=7;//do nothing
			}
			//slaves
				dialog.option[4].default_selection=4;
				strcpy(dialog.option[4].text,"Sell all slaves for ");
				itoa(planet[value0].prize[0],temprivi,10);strcat(dialog.option[4].text,temprivi);
				strcat(dialog.option[4].text,"/slave");
				dialog.option[4].general_effect=8;//trade and continue talking
					dialog.option[4].cargoplus[3]=shipslot[0].cargo[0]*planet[value0].prize[0];//plus money
					dialog.option[4].cargominus[0]=shipslot[0].cargo[0];//minus slaves
				dialog.option[4].effect_parameter=3;//talk with a spaceport
				dialog.option[4].effect_parameter2=ship[0].onplanet;//
			if(shipslot[0].cargo[0]<=0){
				strcpy(dialog.option[4].text,"No slaves in slave pen");
				dialog.option[4].general_effect=7;//do nothing
			}
			//illegal weapons
				dialog.option[5].default_selection=5;
				strcpy(dialog.option[5].text,"Sell all illegal weapons for ");
				itoa(planet[value0].prize[2],temprivi,10);strcat(dialog.option[5].text,temprivi);
				strcat(dialog.option[5].text,"/piece");
				dialog.option[5].general_effect=8;//trade and continue talking
					dialog.option[5].cargoplus[3]=shipslot[0].cargo[2]*planet[value0].prize[2];//plus money
					dialog.option[5].cargominus[2]=shipslot[0].cargo[2];//minus illegal weapons
				dialog.option[5].effect_parameter=3;//talk with a spaceport
				dialog.option[5].effect_parameter2=ship[0].onplanet;//
			if(shipslot[0].cargo[2]<=0){
				strcpy(dialog.option[5].text,"No illegal weapons to sell");
				dialog.option[5].general_effect=7;//do nothing
			}
			//repair ships
			dialog.option[6].general_effect=9;//repair ships				
				dialog.option[6].effect_parameter=3;//repair ships

			strcpy(dialog.info[0],"      Name:");		
			strcpy(dialog.info[1],"     Class:");		
			strcpy(dialog.info[2],"Population:");
			strcpy(dialog.info[3],"  Military:");
			strcpy(dialog.info[4],"    Wealth:");
			
			strcat(dialog.info[0],planet[value0].name);	
			if(planet[value0].type==0)strcat(dialog.info[1],"planet");
			if(planet[value0].type==1)strcat(dialog.info[1],"moon");
			if(planet[value0].type==2)strcat(dialog.info[1],"asteroid base");
			itoa(planet[value0].population,temprivi,10);strcat(dialog.info[2],temprivi);
			itoa(planet[value0].military,temprivi,10);strcat(dialog.info[3],temprivi);
			itoa(planet[value0].wealth,temprivi,10);strcat(dialog.info[4],temprivi);
			
			dialog.infos=5;

			dialog.lowpictureclass=1;
			dialog.lowpicturenumber=planet[value0].picture;	
			dialog.picture=0;
		}
	}
}


























//-----------------------------------------------------------------------------
// Name: SortModesCallback()
// Desc: Callback function for sorting display modes (used by BuildDeviceList).
//-----------------------------------------------------------------------------
int SortModesCallback( const VOID* arg1, const VOID* arg2 )
{
    D3DDISPLAYMODE* p1 = (D3DDISPLAYMODE*)arg1;
    D3DDISPLAYMODE* p2 = (D3DDISPLAYMODE*)arg2;

    if( p1->Format > p2->Format )   return -1;
    if( p1->Format < p2->Format )   return +1;
    if( p1->Width  < p2->Width )    return -1;
    if( p1->Width  > p2->Width )    return +1;
    if( p1->Height < p2->Height )   return -1;
    if( p1->Height > p2->Height )   return +1;

    return 0;
}




//-----------------------------------------------------------------------------
// Name: BuildDeviceList()
// Desc:
//-----------------------------------------------------------------------------
HRESULT BuildDeviceList(void)
{
    return D3DAPPERR_NOWINDOWABLEDEVICES;
}




//-----------------------------------------------------------------------------
// Name: FindDepthStencilFormat()
// Desc: Finds a depth/stencil format for the given device that is compatible
//       with the render target format and meets the needs of the app.
//-----------------------------------------------------------------------------
BOOL FindDepthStencilFormat( UINT iAdapter, D3DDEVTYPE DeviceType,
    D3DFORMAT TargetFormat, D3DFORMAT* pDepthStencilFormat )
{
   

    return FALSE;
}
//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device intialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT ConfirmDevice( D3DCAPS8* pCaps, DWORD dwBehavior,
                                          D3DFORMAT Format )
{
    if( dwBehavior & D3DCREATE_PUREDEVICE )
        return E_FAIL; // GetTransform doesn't work on PUREDEVICE

    // This sample uses alpha textures and/or straight alpha. Make sure the
    // device supports them
    /*if( pCaps->TextureCaps & D3DPTEXTURECAPS_ALPHAPALETTE )
        return S_OK;
    if( pCaps->TextureCaps & D3DPTEXTURECAPS_ALPHA )
        return S_OK;*/
	return S_OK;
    return E_FAIL;
}

void create_battle(int type, int parameter){

	int q,b,a;

	//players threat
		threat=0;
		for (q=1; q<maximum_shipslot; q++){
			if(shipslot[q].dead)continue;
			threat=threat+shipslot[q].energy*shipslot[q].ship_basea.threat/100;
		}
	
	//reset player control
	player_controlled_ship=-1;

	for (q=1; q<maximum_ships; q++){
		ZeroMemory(&ship[q], sizeof(shipbase));	
		ship[q].dead=true;
		ship[q].one=false;
		ship[q].two=false;
		ship[q].up=false;
		ship[q].down=false;
		ship[q].left=false;
		ship[q].right=false;
		ship[q].enter=false;
		ship[q].esc=false;
		ship[q].three=false;
		ship[q].four=false;
		ship[q].space=false;
	}

	//clear bullets
	for (q=0; q<maximum_bullets; q++){
		ZeroMemory(&bullet[q], sizeof(bulletbase));
		bullet[q].dead=true;
	}

	//clear asteroids
	for (q=0; q<maksimiasteroid; q++){
		ZeroMemory(&asteroid[q], sizeof(asteroidi));
		asteroid[q].dead=true;
	}

	//clear smoke
	for (q=0; q<maksimisavuja; q++){
		ZeroMemory(&savu[q], sizeof(smoke));
		savu[q].pois=true;
	}
	//clear particles
	for (q=0; q<maximum_particles; q++){
		ZeroMemory(&particle[q], sizeof(particles));
		particle[q].dead=true;
	}

	//no end plot by default
	battle.endplot=-1;

	//endtimer
	battle.endtimer=7000;

	//store sun location
	battle.sunx=ship[0].x1/(float)(fabs(ship[0].x1)+fabs(ship[0].z1));
	battle.sunz=ship[0].z1/(float)(fabs(ship[0].x1)+fabs(ship[0].z1));
	
	//attacking a planet
	if(type==0){
		encounter randomship;
		//own ships
		for (q=1; q<maximum_shipslot; q++){
			if(shipslot[q].dead)continue;
			//free_ship(&b);
			b=q;
			ship[b].dead=false;
			ship[b].motordown=0;
			ship[b].motorleft=0;
			ship[b].motorright=0;
			ship[b].motorup=0;
			ship[b].rx=atan2f(ship[0].vx,ship[0].vz)-pi/2;
			ship[b].ry=0;
			ship[b].rz=0;
			ship[b].x1=-ship[0].vx/(float)(fabs(ship[0].vx)+fabs(ship[0].vz))*(4700+q*100);
			ship[b].y1=0;
			ship[b].z1=-ship[0].vz/(float)(fabs(ship[0].vx)+fabs(ship[0].vz))*(4700+q*100);	
			ship[b].x2=ship[b].x1;
			ship[b].y2=ship[b].y1;
			ship[b].z2=ship[b].z1;	
			ship[b].vx=0;
			ship[b].vz=0;
			ship[b].guntime[0]=0;
			ship[b].guntime[1]=0;
			ship[b].guntime[2]=0;
			ship[b].guntime[3]=0;
			ship[b].number=b;
			ship[b].energy=shipslot[q].energy;
			ship[b].side=0;
			ship[b].shotlast_enemy=-1;
			ship[b].shotlast_me=-1;
			ship[b].encounter=shipslot[q];
			ship[b].disabled=false;
			ship[b].heat=0;
			ship[b].overheat=false;
		}


		battle.fieldsize=5000;
		battle.type=0;
		battle.planet=planet[parameter];
		battle.planet.x=0;
		battle.planet.y=0;
		battle.planet.z=0;

		//disable asteroids
		for (q=0; q<maksimiasteroid; q++){
			asteroid[q].dead=true;
		}

		//space station
		if(battle.planet.military==3)
		{
			free_ship(&b);			
			create_random_ship(&randomship,4,5);
			randomship.ship_basea=ship_base[6];
			ship[b].dead=false;
			ship[b].motordown=0;
			ship[b].motorleft=0;
			ship[b].motorright=0;
			ship[b].motorup=0;
			ship[b].rx=randDouble(-pi,pi);
			ship[b].ry=0;
			ship[b].rz=0;
			ship[b].x1=randDouble(-1000,1000);
			ship[b].y1=0;
			ship[b].z1=randDouble(-1000,1000);	
			ship[b].x2=ship[b].x1;
			ship[b].y2=ship[b].y1;
			ship[b].z2=ship[b].z1;	
			ship[b].vx=randDouble(0,2*pi);//space station's angle
			ship[b].vz=0;
			ship[b].guntime[0]=0;
			ship[b].guntime[1]=0;
			ship[b].guntime[2]=0;
			ship[b].guntime[3]=0;
			ship[b].number=b;
			ship[b].energy=randDouble(2900,3100);
			ship[b].side=1;
			ship[b].shotlast_enemy=-1;
			ship[b].shotlast_me=-1;
			ship[b].disabled=false;
			ship[b].encounter=randomship;	
			ship[b].heat=0;
			ship[b].overheat=false;				
		}
		
		//enemy ships		
		for (q=0; q<3; q++){
			free_ship(&b);			
			create_random_ship(&randomship,battle.planet.military,0);
			ship[b].dead=false;
			ship[b].motordown=0;
			ship[b].motorleft=0;
			ship[b].motorright=0;
			ship[b].motorup=0;
			ship[b].rx=randDouble(-pi,pi);
			ship[b].ry=0;
			ship[b].rz=0;
			ship[b].x1=randDouble(-1000,1000);
			ship[b].y1=0;
			ship[b].z1=randDouble(-1000,1000);	
			ship[b].x2=ship[b].x1;
			ship[b].y2=ship[b].y1;
			ship[b].z2=ship[b].z1;	
			ship[b].vx=0;
			ship[b].vz=0;
			ship[b].guntime[0]=0;
			ship[b].guntime[1]=0;
			ship[b].guntime[2]=0;
			ship[b].guntime[3]=0;
			ship[b].number=b;
			ship[b].energy=randomship.energy;
			ship[b].side=1;
			ship[b].shotlast_enemy=-1;
			ship[b].shotlast_me=-1;
			ship[b].disabled=false;
			ship[b].encounter=randomship;	
			ship[b].heat=0;
			ship[b].overheat=false;		
		
			//not too close to the planet
			if(sqr(ship[b].x3)+sqr(ship[b].z3)<sqr((265*5)*battle.planet.size)){		
				float kerroin=sqrtf(sqr((265*5)*battle.planet.size+ship[b].encounter.ship_basea.size)/(sqr(ship[b].x3)+sqr(ship[b].z3)));						
				//ship[b].z1=(ship[b].z1)*kerroin;
				//ship[b].x1=(ship[b].x1)*kerroin;
			}
			
		}
	}

	//attacking an asteroid field
	if(type==1){
		
		battle.fieldsize=5000;
		battle.type=1;
		battle.planet=planet[parameter];

		
		//own ships
		for (q=1; q<maximum_shipslot; q++){
			if(shipslot[q].dead)continue;
			//free_ship(&b);
			b=q;
			ship[b].dead=false;
			ship[b].motordown=0;
			ship[b].motorleft=0;
			ship[b].motorright=0;
			ship[b].motorup=0;
			ship[b].rx=atan2f(ship[0].vx,ship[0].vz)-pi/2;
			ship[b].ry=0;
			ship[b].rz=0;
			ship[b].x1=-ship[0].vx/(float)(fabs(ship[0].vx)+fabs(ship[0].vz))*(4700+q*100)+randDouble(-200,200);
			ship[b].y1=0;
			ship[b].z1=-ship[0].vz/(float)(fabs(ship[0].vx)+fabs(ship[0].vz))*(4700+q*100)+randDouble(-200,200);	
			ship[b].x2=ship[b].x1;
			ship[b].y2=ship[b].y1;
			ship[b].z2=ship[b].z1;	
			ship[b].vx=0;
			ship[b].vz=0;
			ship[b].guntime[0]=0;
			ship[b].guntime[1]=0;
			ship[b].guntime[2]=0;
			ship[b].guntime[3]=0;
			ship[b].number=b;
			ship[b].energy=shipslot[q].energy;
			ship[b].side=0;
			ship[b].shotlast_enemy=-1;
			ship[b].shotlast_me=-1;
			ship[b].encounter=shipslot[q];
			ship[b].disabled=false;	
			ship[b].heat=0;
			ship[b].overheat=false;		
		}

		//enemy ships
		encounter randomship;
		for (q=0; q<(int)((threat)/(battle.planet.military+1))+1; q++){
			free_ship(&b);			
			create_random_ship(&randomship,battle.planet.military,0);
			ship[b].dead=false;
			ship[b].motordown=0;
			ship[b].motorleft=0;
			ship[b].motorright=0;
			ship[b].motorup=0;
			ship[b].rx=randDouble(-pi,pi);
			ship[b].ry=0;
			ship[b].rz=0;
			ship[b].x1=randDouble(-1000,1000);
			ship[b].y1=0;
			ship[b].z1=randDouble(-1000,1000);	
			ship[b].x2=ship[b].x1;
			ship[b].y2=ship[b].y1;
			ship[b].z2=ship[b].z1;	
			ship[b].vx=0;
			ship[b].vz=0;
			ship[b].guntime[0]=0;
			ship[b].guntime[1]=0;
			ship[b].guntime[2]=0;
			ship[b].guntime[3]=0;
			ship[b].number=b;
			ship[b].energy=randomship.energy;
			ship[b].side=1;
			ship[b].shotlast_enemy=-1;
			ship[b].shotlast_me=-1;
			ship[b].disabled=false;
			ship[b].encounter=randomship;	
			ship[b].heat=0;
			ship[b].overheat=false;		
		
		}

		//asteroids
		for (q=0; q<maksimiasteroid; q++){
				asteroid[q].number=q;
				asteroid[q].x=randDouble(-battle.fieldsize-1500,battle.fieldsize+1500);
				asteroid[q].y=randDouble(-100,100);
				asteroid[q].z=randDouble(-battle.fieldsize-1500,battle.fieldsize+1500);
				asteroid[q].rx=randDouble(-pi,pi);
				asteroid[q].ry=randDouble(-pi,pi);
				asteroid[q].rz=randDouble(-pi,pi);
				asteroid[q].vx=randDouble(-0.01f,0.01f);
				asteroid[q].vy=0;//randDouble(-1,1);
				asteroid[q].vz=randDouble(-0.01f,0.01f);
				asteroid[q].vrx=randDouble(-1,1);
				asteroid[q].vry=randDouble(-1,1);
				asteroid[q].vrz=randDouble(-1,1);
				asteroid[q].type=0;
				asteroid[q].picture=randInt(0,1);
				asteroid[q].size=randDouble(0.3f,5.0f);
				asteroid[q].dead=false;			
		}
		//one big asteroid
		q=0;
		asteroid[q].x=0;
		asteroid[q].y=0;
		asteroid[q].z=0;
		asteroid[q].vx=0;
		asteroid[q].vy=0;
		asteroid[q].vz=0;
		asteroid[q].size=15;
	}

	//attacking a ship
	if(type==2){
		//position the player

		battle.fieldsize=5000;
		battle.type=2;	
		int player_ships=0;

		//own ships
		for (q=1; q<maximum_shipslot; q++){
			if(shipslot[q].dead)continue;
			//free_ship(&b);
			b=q;
			ship[b].dead=false;
			ship[b].motordown=0;
			ship[b].motorleft=0;
			ship[b].motorright=0;
			ship[b].motorup=0;
			ship[b].rx=randDouble(0,pi);
			ship[b].ry=0;
			ship[b].rz=0;
			ship[b].x1=randDouble(-battle.fieldsize,battle.fieldsize);
			ship[b].y1=0;
			ship[b].z1=randDouble(-battle.fieldsize,battle.fieldsize);	
			ship[b].x2=ship[b].x1;
			ship[b].y2=ship[b].y1;
			ship[b].z2=ship[b].z1;	
			ship[b].vx=0;
			ship[b].vz=0;
			ship[b].guntime[0]=0;
			ship[b].guntime[1]=0;
			ship[b].guntime[2]=0;
			ship[b].guntime[3]=0;
			ship[b].number=b;
			ship[b].energy=shipslot[q].energy;
			ship[b].side=0;
			ship[b].shotlast_enemy=-1;
			ship[b].shotlast_me=-1;
			ship[b].encounter=shipslot[q];
			ship[b].disabled=false;	
			ship[b].heat=0;
			ship[b].overheat=false;		
			player_ships++;
		}


		//enemy ships
		int ships;
		if(dialog.ships>0)ships=dialog.ships;
		else ships=(int)((threat)/dialog.randomship.ship_basea.threat);
		if(ships<1)ships=1;
		if(ships>10)ships=10;
		for (q=0; q<ships; q++){
			free_ship(&b);
			ship[b].dead=false;
			ship[b].motordown=0;
			ship[b].motorleft=0;
			ship[b].motorright=0;
			ship[b].motorup=0;
			ship[b].rx=randDouble(0,pi);
			ship[b].ry=0;
			ship[b].rz=0;
			ship[b].x1=randDouble(-battle.fieldsize,battle.fieldsize);
			ship[b].y1=0;
			ship[b].z1=randDouble(-battle.fieldsize,battle.fieldsize);	
			ship[b].x2=ship[b].x1;
			ship[b].y2=ship[b].y1;
			ship[b].z2=ship[b].z1;	
			ship[b].vx=0;
			ship[b].vz=0;
			ship[b].guntime[0]=0;
			ship[b].guntime[1]=0;
			ship[b].guntime[2]=0;
			ship[b].guntime[3]=0;
			ship[b].number=b;
			ship[b].energy=dialog.randomship.energy;
			ship[b].side=1;
			ship[b].shotlast_enemy=-1;
			ship[b].shotlast_me=-1;	
			ship[b].disabled=false;
			ship[b].encounter=dialog.randomship;	
			ship[b].heat=0;
			ship[b].overheat=false;		
			//randomize names (again)
			strcpy(ship[b].encounter.name,randomname[randInt(0,randomnames)]);
			if(randInt(0,3)==0){
				a=randInt(0,5);
				if(a==0)strcat(ship[b].encounter.name," I");
				if(a==1)strcat(ship[b].encounter.name," II");
				if(a==2)strcat(ship[b].encounter.name," III");
				if(a==3)strcat(ship[b].encounter.name," IV");
				if(a==4)strcat(ship[b].encounter.name," V");
			}
		}
		

		//asteroids
		for (q=0; q<200; q++){
				asteroid[q].number=q;
				asteroid[q].x=randDouble(-battle.fieldsize-1500,battle.fieldsize+1500);
				asteroid[q].y=randDouble(-100,100);
				asteroid[q].z=randDouble(-battle.fieldsize-1500,battle.fieldsize+1500);
				asteroid[q].rx=randDouble(-pi,pi);
				asteroid[q].ry=randDouble(-pi,pi);
				asteroid[q].rz=randDouble(-pi,pi);
				asteroid[q].vx=randDouble(-0.01f,0.01f);
				asteroid[q].vy=0;//randDouble(-1,1);
				asteroid[q].vz=randDouble(-0.01f,0.01f);
				asteroid[q].vrx=randDouble(-1,1);
				asteroid[q].vry=randDouble(-1,1);
				asteroid[q].vrz=randDouble(-1,1);
				asteroid[q].type=0;
				asteroid[q].picture=randInt(0,1);
				asteroid[q].size=randDouble(0.3f,5.0f);
				asteroid[q].dead=false;			
		}
	}

}

void computer_think(shipbase *ship_c){

	
	float dq,temp1;
	int negaatio;
	int q;
	float distance[maximum_ships];
	int closest_target;
	int target;
	ship_c->left=false;
	ship_c->right=false;
	ship_c->up=false;
	ship_c->down=false;
	ship_c->one=false;
	ship_c->two=false;

	//1.find nearest enemy
	//2.find enemy that player is shooting
	//3.find enemy that is shooting me
	//4.find enemy that I shot last time
	//5.determine best target
	//6.turn to face him
	//7.if facing target, and the distance is short enough, shoot him



	//determine distances to enemies
	closest_target=-1;
	for (q=1; q<maximum_ships; q++){
		distance[q]=10000;
		if(ship[q].dead)continue;
		if(ship[q].disabled)continue;
		if(ship[q].side==ship_c->side)continue;
		distance[q]=sqr(ship[q].x1-ship_c->x1)+sqr(ship[q].z1-ship_c->z1);
		//find nearest enemy
		if(closest_target==-1)closest_target=q;
		if(distance[q]<distance[closest_target])closest_target=q;
	}
	if(closest_target==-1)return;
	//determine best target
	target=closest_target;
		//enemy that player is shooting
		if(ship_c->side==0)
			if(ship[player_controlled_ship].shotlast_enemy!=-1)			
			if(2*distance[target]>distance[ship[player_controlled_ship].shotlast_enemy])
				target=ship[player_controlled_ship].shotlast_enemy;
		//enemy that is shooting me
			if(ship_c->shotlast_me!=-1)
			if(distance[ship_c->shotlast_me]<distance[target])target=ship_c->shotlast_me;
		//enemy that I shot last time
			if(ship_c->shotlast_enemy!=-1)
			if(distance[ship_c->shotlast_enemy]<distance[target])target=ship_c->shotlast_enemy;


	//target is to left or to right
	dq=-atan2f(ship_c->z1-ship[target].z3,ship_c->x1-ship[target].x3);
	temp1=ship_c->rx;
	if(ship_c->rx-dq>pi)temp1=temp1-pi*2;
	if(dq-ship_c->rx>pi)dq=dq-pi*2;
			
				//if(mopot[d].up){
					negaatio=1;
					if (dq<temp1)
						negaatio=-1;
				/*}
				else{
					negaatio=-1;
					if (dq<temp1)
						negaatio=1;
				}*/
	
	if(fabs(fabs(dq-temp1)-pi)>0.01f){
		if(negaatio==1)
			ship_c->left=true;
		if(negaatio==-1)
			ship_c->right=true;		
	}

	if((fabs(fabs(dq-temp1)-pi)<0.04f)&&(distance[target]<sqr(2000))){
		if(randInt(0,7)==0)
			ship_c->one=true;
		if(randInt(0,7)==0)
			ship_c->two=true;
	}

	//full throttle
	ship_c->up=true;

	//if no target, don't do anything
	if(target==-1){
		ship_c->left=false;
		ship_c->right=false;
		ship_c->up=false;
		ship_c->down=false;
		ship_c->one=false;
		ship_c->two=false;
	}

}

void end_battle(int type, int parameter){

int q,a;

	if(battle.endtimer>0){
		battle.endtimer=battle.endtimer-elapsed*pelinopeus;
		return;
	}
	//pick disabled ships
	int disabled_ships=0;
	for (q=0; q<maximum_shipslot; q++){
		shipslot_battle[q].dead=true;
	}
	for (q=1; q<maximum_ships; q++){
		if(ship[q].dead)continue;		
		if(!ship[q].disabled)continue;
		if(ship[q].side==0)continue;
		
		if(disabled_ships>=maximum_shipslot)continue;
		
		shipslot_battle[disabled_ships]=ship[q].encounter;
		shipslot_battle[disabled_ships].dead=false;
		shipslot_battle[disabled_ships].cargo[0]=0;
		shipslot_battle[disabled_ships].cargo[1]=0;
		shipslot_battle[disabled_ships].cargo[2]=0;
		shipslot_battle[disabled_ships].cargo[3]=0;
		shipslot_battle[disabled_ships].cargo[4]=0;

		disabled_ships++;
	}


	//delete computers ships
	for (q=1; q<maximum_ships; q++){
		ship[q].dead=true;
	}
	//erase all smoke
	for (q=0; q<maksimisavuja; q++){
		ZeroMemory(&savu[q], sizeof(smoke));
		savu[q].pois=true;
	}
	//particles
	for (q=0; q<maximum_particles; q++){
		ZeroMemory(&particle[q], sizeof(particles));
		particle[q].dead=true;
	}

	
	pelivaihe=0;
	pelivaihe2=0;
	ship[0].vx=0;
	ship[0].vz=0;		

	//player wins
	if(type==0){
		//fight was against a planet
		if(parameter==0){			
			//give resources
			for (a=0; a<5; a++){
				shipslot[0].cargo[a]=shipslot[0].cargo[a]+battle.planet.wealth*randInt(0,12);
			}
		}
		//fight was against an asteroid
		if(parameter==1){			
			//give resources
			for (a=0; a<5; a++){
				shipslot[0].cargo[a]=shipslot[0].cargo[a]+battle.planet.wealth*randInt(0,7);
			}
		}
		//fight was against a ship
		if(parameter==2){			
			//give resources
			for (a=0; a<5; a++){
				shipslot[0].cargo[a]=shipslot[0].cargo[a]+dialog.randomship.cargo[a];
			}
		}

		//want to capture disabled ships?
		if(disabled_ships>0)
		edit_shipslot(1);

		//possible end plot
		if(disabled_ships<=0)
		if(battle.endplot!=-1)
		create_dialog(2,battle.endplot,0);//prize plot
	}
	//computer wins
	if(type==1){
		dialog.noreturn=false;
		pelivaihe=4;
		pelivaihe2=4;		
	}
	
}

void free_ship(int *number){
		int a,b;
		int d=-1;

						a=0;
			b=0;
					alku2:
					a=randInt(1,maximum_ships);
					b=b+1;					
					if(b>maximum_ships)ship[a].dead=true;
					if(!ship[a].dead)goto alku2;
			*number=a;
}

void edit_shipslot(int parameter){
	
	pelivaihe=2;
	//ship for trading
	if(parameter==0){pelivaihe2=0;
		shipslot_battle[0]=dialog.randomship;
	}
	//choose ship to capture
	if(parameter==1)pelivaihe2=1;
	//select slot for captured ship
	if(parameter==2){
		//shipslot_battle[0] was selected at the point of enter pressing in select ship to capture screen
		pelivaihe2=0;
	}
	//choose ship to repair
	if(parameter==3)pelivaihe2=2;

	
	//choose first ship
	dialog_choice=5;
		a0:
		if(dialog_choice>=6)dialog_choice=0;
		if(pelivaihe2==1)if(shipslot_battle[dialog_choice].dead){dialog_choice=dialog_choice+1;goto a0;}
		if(pelivaihe2==2)if(shipslot[dialog_choice+1].dead){dialog_choice=dialog_choice+1;goto a0;}

	if(pelivaihe2==0)dialog_choice=0;



	//next key ups won't take action
	dialog.noup=false;
	dialog.nodown=false;
	dialog.noreturn=false;
	if(buffer[DIK_UP]&0x80)dialog.noup=true;
	if(buffer[DIK_DOWN]&0x80)dialog.nodown=true;
	if(buffer[DIK_RETURN]&0x80)dialog.noreturn=true;
}

void create_random_ship(encounter *randomship,int difficulty,int ship){//creates a random ship
	
	int q;
	float t0;
	float t1;

	//random name
	strcpy(randomship->name,randomname[randInt(0,randomnames)]);
	if(randInt(0,3)==0){
		q=randInt(0,5);
		if(q==0)strcat(randomship->name," I");
		if(q==1)strcat(randomship->name," II");
		if(q==2)strcat(randomship->name," III");
		if(q==3)strcat(randomship->name," IV");
		if(q==4)strcat(randomship->name," V");
	}

	randomship->ship_basea=ship_base[1];
	randomship->dead=false;
		
	float t[10];
	float g[10];

	//randomize ship by difficulty type
	if(difficulty!=-1){
		randomship->type=0;//not needed if not encountered

		
		//fully random ships
		if(difficulty==0){
			//ship class
			g[0]=1;//unidentified flying object
			g[1]=1;//nebula		
			g[2]=1;//star streak
			g[3]=1;//blue tiger
			g[4]=1;//terrible treble
			g[5]=1;//cargo vessel
			//cargo
			randomship->cargo[0]=randInt(0,10);//slaves
			randomship->cargo[1]=randInt(0,10);//contraband goods
			randomship->cargo[2]=randInt(0,10);//illegal weapons
			randomship->cargo[3]=randInt(0,10);//funds
			randomship->cargo[4]=randInt(0,10);//fuel
		}

		//easy ships
		if(difficulty==1){
			//ship class
			g[0]=0;//unidentified flying object
			g[1]=3;//nebula		
			g[2]=40;//star streak
			g[3]=4;//blue tiger
			g[4]=3;//terrible treble
			g[5]=50;//cargo vessel
			//cargo
			randomship->cargo[0]=randInt(0,15);//slaves
			randomship->cargo[1]=randInt(0,15);//contraband goods
			randomship->cargo[2]=randInt(0,15);//illegal weapons
			randomship->cargo[3]=randInt(0,15);//funds
			randomship->cargo[4]=randInt(0,15);//fuel
		}
		//moderate ships
		if(difficulty==2){			
			//ship class
			g[0]=0;//unidentified flying object
			g[1]=20;//nebula		
			g[2]=5;//star streak
			g[3]=30;//blue tiger
			g[4]=30;//terrible treble
			g[5]=5;//cargo vessel
			//cargo
			randomship->cargo[0]=randInt(0,20);//slaves
			randomship->cargo[1]=randInt(0,20);//contraband goods
			randomship->cargo[2]=randInt(0,20);//illegal weapons
			randomship->cargo[3]=randInt(0,20);//funds
			randomship->cargo[4]=randInt(0,20);//fuel
		}
		//difficult ships
		if(difficulty==3){
			//ship class
			g[0]=2;//unidentified flying object
			g[1]=10;//nebula		
			g[2]=0;//star streak
			g[3]=10;//blue tiger
			g[4]=10;//terrible treble
			g[5]=0;//cargo vessel
			//cargo
			randomship->cargo[0]=randInt(0,40);//slaves
			randomship->cargo[1]=randInt(0,40);//contraband goods
			randomship->cargo[2]=randInt(0,40);//illegal weapons
			randomship->cargo[3]=randInt(0,40);//funds
			randomship->cargo[4]=randInt(0,40);//fuel
		}
		//selected ship
		if(difficulty==4){
			//ship class
			g[0]=0;//unidentified flying object
			g[1]=0;//nebula		
			g[2]=0;//star streak
			g[3]=0;//blue tiger
			g[4]=0;//terrible treble
			g[5]=0;//cargo vessel
			g[6]=0;//space station

			g[ship]=1;//selected ship
			//cargo
			randomship->cargo[0]=randInt(0,10);//slaves
			randomship->cargo[1]=randInt(0,10);//contraband goods
			randomship->cargo[2]=randInt(0,10);//illegal weapons
			randomship->cargo[3]=randInt(0,10);//funds
			randomship->cargo[4]=randInt(0,10);//fuel
		}
	}

	//randomize ship by encounter type
	if(difficulty==-1){
		//players threat
		threat=0;
		for (q=1; q<maximum_shipslot; q++){
			if(shipslot[q].dead)continue;
			threat=threat+shipslot[q].energy*shipslot[q].ship_basea.threat/100;
		}
		//hard random encounter
		{
			t[0]=1;		//0=refugee
			t[1]=5;		//1=pirate
			t[2]=1;		//2=merchant
			t[3]=10;	//3=colonial navy
			t[4]=10;	//4=alien
			t[5]=2;		//5=traveller
		}
		//moderate random encounter
		if(threat<6){
			t[0]=5;		//0=refugee
			t[1]=5;		//1=pirate
			t[2]=7;		//2=merchant
			t[3]=2;		//3=colonial navy
			t[4]=2;		//4=alien
			t[5]=7;		//5=traveller
		}
		//easy random encounter
		if(threat<2.5f){
			t[0]=10;	//0=refugee
			t[1]=1;		//1=pirate
			t[2]=10;	//2=merchant
			t[3]=1;		//3=colonial navy
			t[4]=0;		//4=alien
			t[5]=4;		//5=traveller
		}
		t0=0;
		t1=randDouble(0,t[0]+t[1]+t[2]+t[3]+t[4]+t[5]);
		for (q=0; q<6; q++){		
			if((t1>t0)&&(t1<(t0+t[q]))){randomship->type=q;break;}
			t0=t0+t[q];		
		}
		

		if(randomship->type==0){//refugee		  
			//likeliness of strategy
			t[0]=60;	//0=plead mercy
			t[1]=20;	//1=ask question
			t[2]=10;	//2=offensive
			//cargo
			randomship->cargo[0]=randInt(0,43);//slaves
			randomship->cargo[1]=randInt(0,1);//contraband goods
			randomship->cargo[2]=randInt(0,1);//illegal weapons
			randomship->cargo[3]=randInt(0,15);//funds
			randomship->cargo[4]=randInt(0,18);//fuel
			//do they chase us
			randomship->chasing=false;
			//ship class
			g[0]=0;//unidentified flying object
			g[1]=3;//nebula		
			g[2]=40;//star streak
			g[3]=4;//blue tiger
			g[4]=3;//terrible treble
			g[5]=50;//cargo vessel
		}
		if(randomship->type==1){//pirate		  
			//likeliness of strategy
			t[0]=0;	//0=plead mercy
			t[1]=10;	//1=ask question
			t[2]=50;	//2=offensive
			//cargo
			randomship->cargo[0]=randInt(0,33);//slaves
			randomship->cargo[1]=randInt(0,33);//contraband goods
			randomship->cargo[2]=randInt(0,33);//illegal weapons
			randomship->cargo[3]=randInt(0,33);//funds
			randomship->cargo[4]=randInt(0,33);//fuel
			//do they chase us
			randomship->chasing=true;
			//ship class
			g[0]=0;//unidentified flying object
			g[1]=12;//nebula		
			g[2]=30;//star streak
			g[3]=20;//blue tiger
			g[4]=10;//terrible treble
			g[5]=10;//cargo vessel
		}
		if(randomship->type==2){//merchant		  
			//likeliness of strategy
			t[0]=60;	//0=plead mercy
			t[1]=30;	//1=ask question
			t[2]=20;	//2=offensive
			//cargo
			randomship->cargo[0]=randInt(0,2);//slaves
			randomship->cargo[1]=randInt(0,28);//contraband goods
			randomship->cargo[2]=randInt(0,2);//illegal weapons
			randomship->cargo[3]=randInt(0,76);//funds
			randomship->cargo[4]=randInt(0,37);//fuel
			//do they chase us
			randomship->chasing=false;
			//ship class
			g[0]=0;//unidentified flying object
			g[1]=10;//nebula		
			g[2]=50;//star streak
			g[3]=10;//blue tiger
			g[4]=10;//terrible treble
			g[5]=50;//cargo vessel
		}
		if(randomship->type==3){//colonial navy		  
			//likeliness of strategy
			t[0]=0;	//0=plead mercy
			t[1]=30;	//1=ask question
			t[2]=70;	//2=offensive
			//cargo
			randomship->cargo[0]=randInt(0,3);//slaves
			randomship->cargo[1]=randInt(0,2);//contraband goods
			randomship->cargo[2]=randInt(0,120);//illegal weapons
			randomship->cargo[3]=randInt(0,60);//funds
			randomship->cargo[4]=randInt(0,20);//fuel
			//do they chase us
			randomship->chasing=true;
			//ship class
			g[0]=0;//unidentified flying object
			g[1]=10;//nebula		
			g[2]=5;//star streak
			g[3]=50;//blue tiger
			g[4]=10;//terrible treble
			g[5]=5;//cargo vessel
		}
		if(randomship->type==4){//alien		  
			//likeliness of strategy
			t[0]=0;	//0=plead mercy
			t[1]=40;	//1=ask question
			t[2]=70;	//2=offensive
			//cargo
			randomship->cargo[0]=randInt(0,2);//slaves
			randomship->cargo[1]=randInt(0,50);//contraband goods
			randomship->cargo[2]=randInt(0,50);//illegal weapons
			randomship->cargo[3]=randInt(0,50);//funds
			randomship->cargo[4]=randInt(0,50);//fuel
			//do they chase us
			randomship->chasing=true;
			//ship class
			g[0]=100;//unidentified flying object
			g[1]=0;//nebula		
			g[2]=0;//star streak
			g[3]=0;//blue tiger
			g[4]=0;//terrible treble
			g[5]=0;//cargo vessel
		}
		if(randomship->type==5){//traveller		  
			//likeliness of strategy
			t[0]=60;	//0=plead mercy
			t[1]=30;	//1=ask question
			t[2]=10;	//2=offensive
			//cargo
			randomship->cargo[0]=randInt(0,2);//slaves
			randomship->cargo[1]=randInt(0,11);//contraband goods
			randomship->cargo[2]=randInt(0,18);//illegal weapons
			randomship->cargo[3]=randInt(0,29);//funds
			randomship->cargo[4]=randInt(0,22);//fuel
			//do they chase us
			randomship->chasing=false;
			//ship class
			g[0]=0;//unidentified flying object
			g[1]=50;//nebula		
			g[2]=10;//star streak
			g[3]=10;//blue tiger
			g[4]=5;//terrible treble
			g[5]=5;//cargo vessel
		}

		//randomize strategy
		t0=0;
		t1=randDouble(0,t[0]+t[1]+t[2]);
		for (q=0; q<3; q++){		
			if((t1>t0)&&(t1<(t0+t[q]))){randomship->strategy=q;break;}
			t0=t0+t[q];
		}	

	}
	//randomize ship class
		t0=0;
		t1=randDouble(0,g[0]+g[1]+g[2]+g[3]+g[4]+g[5]);
		for (q=0; q<6; q++){		
			if((t1>t0)&&(t1<(t0+g[q]))){randomship->ship_basea=ship_base[q];break;}
			t0=t0+g[q];
		}
	
	//if player is short of fuel, generate some for him
	if(shipslot[0].cargo[4]<5)
		randomship->cargo[4]=randInt(10,25);//fuel

	randomship->energy=randInt(randomship->ship_basea.base_energy-20,randomship->ship_basea.base_energy);
	
	
}

void render_ships(void){
	int q;

	dialog.rotate=dialog.rotate+0.0003f*elapsed*pelinopeus;
	m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);	
	pelinopeus=1;	
	
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((60)*pi/180), aspect, 25.0f, maxvisible);			
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	//background
	LPDIRECT3DSURFACE8 pBackBuffer;
    m_pDevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
	RECT rcSource[] = {  0,  0,  SCREEN_WIDTH,  SCREEN_HEIGHT};
	POINT ptDest[]   = {  0,  0};
    m_pDevice->CopyRects(kuvia[1], rcSource, 1, pBackBuffer, ptDest);
    pBackBuffer->Release();

	//ships 
	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
	m_pDevice->LightEnable(0, TRUE);
	m_pDevice->LightEnable(1, TRUE);
	//light
	ZeroMemory(&lamppu[0].valo, sizeof(D3DLIGHT8));	
	lamppu[0].valo.Range = 10000;
	lamppu[0].valo.Diffuse.r = 1;
	lamppu[0].valo.Diffuse.g = 1;
	lamppu[0].valo.Diffuse.b = 1;
	lamppu[0].valo.Ambient.r = 0.16f;
	lamppu[0].valo.Ambient.g = 0.16f;
	lamppu[0].valo.Ambient.b = 0.16f;
	lamppu[0].valo.Specular.r = 1.0f;
	lamppu[0].valo.Specular.g = 1.0f;
	lamppu[0].valo.Specular.b = 1.0f;
	lamppu[0].valo.Type=D3DLIGHT_POINT;
	lamppu[0].valo.Attenuation0=1;
	lamppu[0].valo.Attenuation1=0;
	lamppu[0].valo.Attenuation2=0;
	
	for (q=1; q<7; q++){		
		//pick slot for ship
		if(pelivaihe2==0){
			if(shipslot[q].dead)continue;
			kamerax1=(float)(-130+(q-1)*55);
			kameray1=300;
			kameraz1=70;
			kamerax2=kamerax1;
			kameray2=0;
			kameraz2=kameraz1-1;
			float kerroin;
			D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
			m_pDevice->SetTransform( D3DTS_VIEW, &matView );	
			//ship
				matriisi->LoadIdentity();
				matriisi->RotateYawPitchRollLocal(dialog.rotate,0,0);
				float t0=mallit[2].malli[shipslot[q].ship_basea.picture].downright.x;
				float t1=mallit[2].malli[shipslot[q].ship_basea.picture].downright.y;
				float t2=mallit[2].malli[shipslot[q].ship_basea.picture].downright.z;
				float t3=mallit[2].malli[shipslot[q].ship_basea.picture].upleft.x;
				float t4=mallit[2].malli[shipslot[q].ship_basea.picture].upleft.y;
				float t5=mallit[2].malli[shipslot[q].ship_basea.picture].upleft.z;
				kerroin=(float)(38/sqrt(sqr(t0-t3)+sqr(t1-t4)+sqr(t2-t5)));
			
				//light1
				lamppu[0].valo.Position.x = -2000;
				lamppu[0].valo.Position.y = 2500;
				lamppu[0].valo.Position.z = -2000;		
				m_pDevice->SetLight(0, &lamppu[0].valo);
				//light2
				lamppu[0].valo.Position.x = +1000;
				lamppu[0].valo.Position.y = 2000;
				lamppu[0].valo.Position.z = +2500;
				m_pDevice->SetLight(1, &lamppu[0].valo);

			matriisi->ScaleLocal(kerroin,kerroin,kerroin);	
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
			drawfast(&mallit[2].malli[shipslot[q].ship_basea.picture]);
		}
		//choose ship to repair
		if(pelivaihe2==2){
			if(shipslot[q].dead)continue;
			kamerax1=(float)(-130+(q-1)*55);
			kameray1=300;
			kameraz1=70;
			kamerax2=kamerax1;
			kameray2=0;
			kameraz2=kameraz1-1;
			float kerroin;
			D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
			m_pDevice->SetTransform( D3DTS_VIEW, &matView );	
			//ship
				matriisi->LoadIdentity();
				matriisi->RotateYawPitchRollLocal(dialog.rotate,0,0);
				float t0=mallit[2].malli[shipslot[q].ship_basea.picture].downright.x;
				float t1=mallit[2].malli[shipslot[q].ship_basea.picture].downright.y;
				float t2=mallit[2].malli[shipslot[q].ship_basea.picture].downright.z;
				float t3=mallit[2].malli[shipslot[q].ship_basea.picture].upleft.x;
				float t4=mallit[2].malli[shipslot[q].ship_basea.picture].upleft.y;
				float t5=mallit[2].malli[shipslot[q].ship_basea.picture].upleft.z;
				kerroin=(float)(38/sqrt(sqr(t0-t3)+sqr(t1-t4)+sqr(t2-t5)));
			
				//light1
				lamppu[0].valo.Position.x = -2000;
				lamppu[0].valo.Position.y = 2500;
				lamppu[0].valo.Position.z = -2000;		
				m_pDevice->SetLight(0, &lamppu[0].valo);
				//light2
				lamppu[0].valo.Position.x = +1000;
				lamppu[0].valo.Position.y = 2000;
				lamppu[0].valo.Position.z = +2500;
				m_pDevice->SetLight(1, &lamppu[0].valo);

			matriisi->ScaleLocal(kerroin,kerroin,kerroin);	
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
			drawfast(&mallit[2].malli[shipslot[q].ship_basea.picture]);
		}
	}
	//choose ship to capture
	for (q=0; q<maximum_shipslot-1; q++){	
		if(pelivaihe2==1){
			if(shipslot_battle[q].dead)continue;
			kamerax1=(float)(-130+(q)*55);
			kameray1=300;
			kameraz1=70;
			kamerax2=kamerax1;
			kameray2=0;
			kameraz2=kameraz1-1;
			float kerroin;
			D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
			m_pDevice->SetTransform( D3DTS_VIEW, &matView );	
			//ship
				matriisi->LoadIdentity();
				matriisi->RotateYawPitchRollLocal(dialog.rotate,0,0);
				float t0=mallit[2].malli[shipslot_battle[q].ship_basea.picture].downright.x;
				float t1=mallit[2].malli[shipslot_battle[q].ship_basea.picture].downright.y;
				float t2=mallit[2].malli[shipslot_battle[q].ship_basea.picture].downright.z;
				float t3=mallit[2].malli[shipslot_battle[q].ship_basea.picture].upleft.x;
				float t4=mallit[2].malli[shipslot_battle[q].ship_basea.picture].upleft.y;
				float t5=mallit[2].malli[shipslot_battle[q].ship_basea.picture].upleft.z;
				kerroin=(float)(38/sqrt(sqr(t0-t3)+sqr(t1-t4)+sqr(t2-t5)));
			
				//light1
				lamppu[0].valo.Position.x = -2000;
				lamppu[0].valo.Position.y = 2500;
				lamppu[0].valo.Position.z = -2000;		
				m_pDevice->SetLight(0, &lamppu[0].valo);
				//light2
				lamppu[0].valo.Position.x = +1000;
				lamppu[0].valo.Position.y = 2000;
				lamppu[0].valo.Position.z = +2500;
				m_pDevice->SetLight(1, &lamppu[0].valo);

			matriisi->ScaleLocal(kerroin,kerroin,kerroin);	
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
			drawfast(&mallit[2].malli[shipslot_battle[q].ship_basea.picture]);
		}
	}

	//choise
		kamerax1=145;
		kameray1=300;
		kameraz1=70;
		kamerax2=kamerax1;
		kameray2=0;
		kameraz2=kameraz1-1;
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );	
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE ,FALSE);	
	matriisi->LoadIdentity();
	matriisi->TranslateLocal((float)(270-dialog_choice*55),0,-2);		
	matriisi->RotateYawPitchRollLocal(0,0,pi/2);
	matriisi->ScaleLocal(1,1,1);	
	draw(0.4f,0.4f,0.4f,&mallit[0].malli[4]);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);	


	//help screen ship
	if(pelivaihe2==0){//give player a ship
		m_pDevice->LightEnable(0, TRUE);
		m_pDevice->LightEnable(1, TRUE);
		kamerax1=-55;
		kameray1=300;
		kameraz1=-100;
		kamerax2=kamerax1;
		kameray2=0;
		kameraz2=kameraz1-1;
		float kerroin;
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );	
		//ship
			matriisi->LoadIdentity();
			matriisi->RotateYawPitchRollLocal(dialog.rotate,0,0);
			float t0=mallit[2].malli[shipslot_battle[0].ship_basea.picture].downright.x;
			float t1=mallit[2].malli[shipslot_battle[0].ship_basea.picture].downright.y;
			float t2=mallit[2].malli[shipslot_battle[0].ship_basea.picture].downright.z;
			float t3=mallit[2].malli[shipslot_battle[0].ship_basea.picture].upleft.x;
			float t4=mallit[2].malli[shipslot_battle[0].ship_basea.picture].upleft.y;
			float t5=mallit[2].malli[shipslot_battle[0].ship_basea.picture].upleft.z;
			kerroin=(float)(38/sqrt(sqr(t0-t3)+sqr(t1-t4)+sqr(t2-t5)));
		
			//light1
			lamppu[0].valo.Position.x = -2000;
			lamppu[0].valo.Position.y = 2500;
			lamppu[0].valo.Position.z = -2000;		
			m_pDevice->SetLight(0, &lamppu[0].valo);
			//light2
			lamppu[0].valo.Position.x = +1000;
			lamppu[0].valo.Position.y = 2000;
			lamppu[0].valo.Position.z = +2500;
			m_pDevice->SetLight(1, &lamppu[0].valo);

		matriisi->ScaleLocal(kerroin,kerroin,kerroin);	
		m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
		drawfast(&mallit[2].malli[shipslot_battle[0].ship_basea.picture]);		
		kirjota(1,-1,-1,-1,272,650,30,shipslot_battle[0].name);
	}
	//ship's names
	if(pelivaihe2==0)//give player a ship
	for (q=1; q<maximum_shipslot; q++){
		strcpy(rivi,"Slot ");
		itoa(q,temprivi,10);
		strcat(rivi,temprivi);
		kirjota(1,-1,-1,-1,195+(float)(q-1)*123,165,30,rivi);
		if(shipslot[q].dead)continue;		
		kirjota(0.7f,-1,-1,-1,195+(float)(q-1)*123,280,30,shipslot[q].name);
	}
	if(pelivaihe2==1)//choose ship to capture
	for (q=0; q<maximum_shipslot-1; q++){		
		if(shipslot_battle[q].dead)continue;		
		kirjota(0.7f,-1,-1,-1,195+(float)(q)*123,280,30,shipslot_battle[q].name);
	}
	if(pelivaihe2==2)//choose ship to repair
	for (q=1; q<maximum_shipslot; q++){
		if(shipslot[q].dead)continue;		
		strcpy(rivi,"");
		itoa((int)shipslot[q].energy,temprivi,10);
		strcat(rivi,temprivi);
		float color=shipslot[q].energy/shipslot[q].ship_basea.base_energy;
		if(color>1)color=1;
		kirjota(1,1-color,color,0,195+(float)(q-1)*123,165,30,rivi);
		kirjota(0.7f,-1,-1,-1,195+(float)(q-1)*123,280,30,shipslot[q].name);
	}

	//help
	if(pelivaihe2==0){//give player a ship
		kirjota(1,-1,-1,-1,272,418,17,"Select the ship slot to place the new ship in. If the slot already has a ship, it will be abandoned. Press esc to forfeit the new ship.");
	}
	if(pelivaihe2==1){//choose ship to capture
		if(options[4])//easy mode
			kirjota(1,-1,-1,-1,272,418,17,"Captain, you may now select one ship you wish to capture. Since you´ve set easy mode, you don´t need to fight for the ship - it´s captured automatically. Press esc to not capture a ship at all.");
		else
			kirjota(1,-1,-1,-1,272,418,17,"Captain, you may now select one ship you wish to attemp to capture. While capturing use space key to shoot, alt to strafe and arrow keys to navigate. Press esc to not capture a ship at all.");
	}
	if(pelivaihe2==2){//choose ship to repair
		strcpy(rivi,"Choose the ship to repair/sell. Press enter to repair, s to sell. Press esc to exit. Current cash: ");
		itoa(shipslot[0].cargo[3],temprivi,10);	strcat(rivi,temprivi);
		if(shipslot[dialog_choice+1].energy<shipslot[dialog_choice+1].ship_basea.base_energy){
			strcat(rivi," Repairing this ship would cost: ");
			itoa((shipslot[dialog_choice+1].ship_basea.base_energy-shipslot[dialog_choice+1].energy)*shipslot[dialog_choice+1].ship_basea.threat,temprivi,10);	strcat(rivi,temprivi);
		}
		{
			strcat(rivi," Selling this ship would give: ");
			itoa((int)((shipslot[dialog_choice+1].energy+20)*shipslot[dialog_choice+1].ship_basea.threat),temprivi,10);	strcat(rivi,temprivi);
		}
		kirjota(1,-1,-1,-1,272,418,15,rivi);

	}
}

void render_capture(void){//renders the capture scene
	
	int q,a,b,d;
	float man_size=0.5f;
	
	if(!help_screen)pelinopeus=0.6f;

	//background
	LPDIRECT3DSURFACE8 pBackBuffer;
    m_pDevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
	RECT rcSource[] = {  0,  0,  SCREEN_WIDTH,  SCREEN_HEIGHT};
	POINT ptDest[]   = {  0,  0};
    m_pDevice->CopyRects(kuvia[2], rcSource, 1, pBackBuffer, ptDest);
    pBackBuffer->Release();
		
	//light
	ZeroMemory(&lamppu[0].valo, sizeof(D3DLIGHT8));	
	lamppu[0].valo.Position.y = 0;
	lamppu[0].valo.Position.x = 0;
	lamppu[0].valo.Position.z = 0;
	lamppu[0].valo.Range = 50000;
	lamppu[0].valo.Diffuse.r = 1;    
	lamppu[0].valo.Diffuse.g = 1;
	lamppu[0].valo.Diffuse.b = 1;    
	lamppu[0].valo.Ambient.r = 2.0f;
	lamppu[0].valo.Ambient.g = 2.0f;    
	lamppu[0].valo.Ambient.b = 2.0f;
	lamppu[0].valo.Specular.r = 1.0f;    
	lamppu[0].valo.Specular.g = 1.0f;
	lamppu[0].valo.Specular.b = 1.0f;
	lamppu[0].valo.Type=D3DLIGHT_POINT;
	lamppu[0].valo.Attenuation0=1;
	lamppu[0].valo.Attenuation1=0;
	lamppu[0].valo.Attenuation2=0;
	m_pDevice->SetLight(0, &lamppu[0].valo);

	//kamera
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((60)*pi/180), aspect, 25.0f, maxvisible);			
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

		kamerax1=0;
		kameray1=1000;
		kameraz1=0;
		kamerax2=kamerax1-1;
		kameray2=0;
		kameraz2=kameraz1;
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );


	//guns
	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
	m_pDevice->LightEnable(0, TRUE);
	m_pDevice->LightEnable(1, FALSE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);


	//think
	for (q=1; q<100; q++){
		if(capture_man[q].dead)continue;
		capture_man[q].targettimer=capture_man[q].targettimer-elapsed*pelinopeus;
		capture_man[q].uptimer=capture_man[q].uptimer-elapsed*pelinopeus;
		capture_man[q].left_right_timer=capture_man[q].left_right_timer-elapsed*pelinopeus;

		//find new target
		if(capture_man[q].targettimer<0){
			capture_man[q].targettimer=5000;
			capture_man[q].target=-1;
			capture_man[q].targetfar=-1;
			capture_man[q].left=false;
			capture_man[q].right=false;
			capture_man[q].left_right_timer=-1;


			//random target
			capture_man[q].target=-1;
			d=0;
			while((capture_man[q].target==-1)&&(d<100)){
				a=randInt(0,100);
				
				d++;
				if(capture_man[a].dead)continue;
				if(capture_man[a].side==capture_man[q].side)continue;
				//if(a==q)continue;
				capture_man[q].target=a;
			}
			capture_man[q].targetfar=-1;
			d=0;
			while((capture_man[q].targetfar==-1)&&(d<100)){
				a=randInt(0,100);
				d++;
				if(capture_man[a].dead)continue;
				if(capture_man[a].side==capture_man[q].side)continue;
				if(a==q)continue;
				capture_man[q].targetfar=a;
			}
		}
		
		if(capture_man[q].target==-1){capture_man[q].targettimer=-1;continue;}

		//if target is dead
		if(capture_man[capture_man[q].target].dead)capture_man[q].targettimer=-1;

		//if target is too close
		if(sqr(capture_man[capture_man[q].target].x-capture_man[q].x)+sqr(capture_man[capture_man[q].target].z-capture_man[q].z)<1.5f*10000){
			capture_man[q].uptimer=randDouble(1000,2000);
			capture_man[q].up_or_down=-1;
		}
		//if target is too far
		if(sqr(capture_man[capture_man[q].target].x-capture_man[q].x)+sqr(capture_man[capture_man[q].target].z-capture_man[q].z)>15.0f*10000){
			capture_man[q].uptimer=randDouble(1000,2000);
			capture_man[q].up_or_down=1;
		}

		

		
			//target is to left or right
			float dq=-atan2f(capture_man[q].z-capture_man[capture_man[q].target].z,capture_man[q].x-capture_man[capture_man[q].target].x);
			float temp2=capture_man[q].rotatex;
			if(capture_man[q].rotatex-dq>pi)temp2=temp2-pi*2;
			if(dq-capture_man[q].rotatex>pi)dq=dq-pi*2;
					
						int negaatio=1;
						if (dq<temp2)
							negaatio=-1;

			//if target is straight ahead
			if(fabs(fabs(dq-temp2)-pi)<0.15f){
				capture_man[q].left=false;
				capture_man[q].right=false;
			}

			//left and right
			if(capture_man[q].left_right_timer<0){
				capture_man[q].left=false;
				capture_man[q].right=false;
				if(negaatio==1){
					capture_man[q].left=true;
					capture_man[q].left_right_timer=randDouble(300,700);
				}
				if(negaatio==-1){
					capture_man[q].right=true;
					capture_man[q].left_right_timer=randDouble(300,700);
				}
			
		}

		if(capture_man[q].uptimer<0){
			capture_man[q].uptimer=randDouble(1000,2000);
			capture_man[q].up_or_down=1;
			if(randInt(0,2)==0)
				capture_man[q].up_or_down=-1;
		}
		if(capture_man[q].up_or_down==1)
			capture_man[q].up=true;
		if(capture_man[q].up_or_down==-1)
			capture_man[q].down=true;

		capture_man[q].space=true;
	}

	//men
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);	

	int sides[2];//how many men each side has
	sides[0]=0;
	sides[1]=0;
	for (q=0; q<100; q++){
		if(capture_man[q].dead)continue;
		sides[capture_man[q].side]++;

		//move
		if(!capture_man[q].alt){
			if(capture_man[q].left)capture_man[q].rotatex=capture_man[q].rotatex-0.0027f*elapsed*pelinopeus;
			if(capture_man[q].right)capture_man[q].rotatex=capture_man[q].rotatex+0.0027f*elapsed*pelinopeus;
		}
		else{
			if(capture_man[q].left){
				capture_man[q].x=capture_man[q].x+sinf(capture_man[q].rotatex)*0.30f*elapsed*pelinopeus*man_size;
				capture_man[q].z=capture_man[q].z+cosf(capture_man[q].rotatex)*0.30f*elapsed*pelinopeus*man_size;
			}
			if(capture_man[q].right){
				capture_man[q].x=capture_man[q].x+sinf(capture_man[q].rotatex+pi)*0.30f*elapsed*pelinopeus*man_size;
				capture_man[q].z=capture_man[q].z+cosf(capture_man[q].rotatex+pi)*0.30f*elapsed*pelinopeus*man_size;
			}
		}
		if(capture_man[q].up){
			capture_man[q].x=capture_man[q].x+sinf(capture_man[q].rotatex+pi/2)*0.30f*elapsed*pelinopeus*man_size;
			capture_man[q].z=capture_man[q].z+cosf(capture_man[q].rotatex+pi/2)*0.30f*elapsed*pelinopeus*man_size;
		}
		if(capture_man[q].down){
			capture_man[q].x=capture_man[q].x+sinf(capture_man[q].rotatex+pi/2+pi)*0.30f*elapsed*pelinopeus*man_size;
			capture_man[q].z=capture_man[q].z+cosf(capture_man[q].rotatex+pi/2+pi)*0.30f*elapsed*pelinopeus*man_size;
		}
		if(capture_man[q].rotatex<0)capture_man[q].rotatex=capture_man[q].rotatex+2*pi;
		if(capture_man[q].rotatex>2*pi)capture_man[q].rotatex=capture_man[q].rotatex-2*pi;
		if(capture_man[q].x<-455){capture_man[q].x=-455;capture_man[q].targettimer=10000;capture_man[q].target=capture_man[q].targetfar;capture_man[q].uptimer=randDouble(1000,2000);capture_man[q].up_or_down=capture_man[q].up_or_down*-1;}
		if(capture_man[q].x>500){capture_man[q].x=500;capture_man[q].targettimer=10000;capture_man[q].target=capture_man[q].targetfar;capture_man[q].uptimer=randDouble(1000,2000);capture_man[q].up_or_down=capture_man[q].up_or_down*-1;}
		if(capture_man[q].z<-540){capture_man[q].z=-540;capture_man[q].targettimer=10000;capture_man[q].target=capture_man[q].targetfar;capture_man[q].uptimer=randDouble(1000,2000);capture_man[q].up_or_down=capture_man[q].up_or_down*-1;}
		if(capture_man[q].z>620){capture_man[q].z=620;capture_man[q].targettimer=10000;capture_man[q].target=capture_man[q].targetfar;capture_man[q].uptimer=randDouble(1000,2000);capture_man[q].up_or_down=capture_man[q].up_or_down*-1;}

		

		//legs
		if((capture_man[q].up)||(capture_man[q].down))
		if(capture_man[q].legtimer>0)capture_man[q].legtimer=capture_man[q].legtimer-0.01f*0.36f*elapsed*pelinopeus;
		if(capture_man[q].legtimer<0){
			if(capture_man[q].leg==0)
				capture_man[q].leg=1;
			else
				capture_man[q].leg=0;
			capture_man[q].legtimer=1;
		}

		if(capture_man[q].energy<=0)capture_man[q].dead=true;

		//shoot
		if(capture_man[q].space){
			while(capture_man[q].guntime>=0){
				playsound(4,1,0,0,0,0);
				capture_man[q].guntime=capture_man[q].guntime-randInt(500,700);

				a=0;
				b=0;
					alku2:
					a=randInt(0,maximum_bullets);
					b=b+1;
					if(b>maximum_bullets)bullet[a].dead=true;
					if(!bullet[a].dead)goto alku2;

				bullet[a].dead=false;
				bullet[a].position.x=capture_man[q].x+sinf(2.4f+capture_man[q].rotatex)*30*man_size;
				bullet[a].position.y=0;
				bullet[a].position.z=capture_man[q].z+cosf(2.4f+capture_man[q].rotatex)*30*man_size;						
				bullet[q].position2.x=bullet[q].position.x;
				bullet[q].position2.z=bullet[q].position.z;
				bullet[a].rotate.x=capture_man[q].rotatex;
				bullet[a].rotate.y=0;
				bullet[a].rotate.z=0;
				bullet[a].movement.x=sinf(bullet[a].rotate.x+pi/2)*1*randDouble(0.9f,1.1f);
				bullet[a].movement.y=0;
				bullet[a].movement.z=cosf(bullet[a].rotate.x+pi/2)*1*randDouble(0.9f,1.1f);
				bullet[a].target=capture_man[q].side;//target refers to shooters side here
			}
		}
		if(capture_man[q].guntime<0)capture_man[q].guntime=capture_man[q].guntime+elapsed*pelinopeus;

		//capture_man[q].left=false;
		//capture_man[q].right=false;
		capture_man[q].up=false;
		capture_man[q].down=false;
		capture_man[q].space=false;
		capture_man[q].alt=false;

		//draw
		/*matriisi->LoadIdentity();
		matriisi->TranslateLocal(capture_man[q].x,0,capture_man[q].z);		
		matriisi->RotateYawPitchRollLocal(capture_man[q].rotatex,0,0);
		matriisi->ScaleLocal(0.8f,0.8f,0.8f);
		drawfast(&mallit[0].malli[8]);*/

			//draw the picture
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(capture_man[q].x,0,capture_man[q].z);		
			matriisi->RotateYawPitchRollLocal(capture_man[q].rotatex,pi/2,0);			
			//matriisi->RotateYawPitchRollLocal(-pi/2,pi/2,0);			
			matriisi->ScaleLocal(2*man_size,2*man_size,2*man_size);

				
				if(q==0){
					matriisi->Push();							
					matriisi->ScaleLocal(1.1f,1.1f,1.1f);
					m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
					m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
					if(capture_man[q].leg==0){
						mallit[1].malli[1].sisus[0].textuuri2=52;
						mallit[1].malli[1].sisus[0].textuuri=52;
					}
					else{
						mallit[1].malli[1].sisus[0].textuuri2=54;
						mallit[1].malli[1].sisus[0].textuuri=54;
					}
					draw(0,1,0,&mallit[1].malli[1]);	
					matriisi->Pop();
				}
				
				m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO    );
				m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_INVSRCCOLOR);
				if(capture_man[q].leg==0){
					mallit[1].malli[1].sisus[0].textuuri2=52;
					mallit[1].malli[1].sisus[0].textuuri=52;
				}
				else{
					mallit[1].malli[1].sisus[0].textuuri2=54;
					mallit[1].malli[1].sisus[0].textuuri=54;
				}
				draw(1,1,1,&mallit[1].malli[1]);				
				
				m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
				m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
				if(capture_man[q].side==0){
					if(capture_man[q].leg==0){
						mallit[1].malli[1].sisus[0].textuuri2=51;
						mallit[1].malli[1].sisus[0].textuuri=51;
					}
					else{
						mallit[1].malli[1].sisus[0].textuuri2=53;
						mallit[1].malli[1].sisus[0].textuuri=53;
					}
				}
				else{
					if(capture_man[q].leg==0){
						mallit[1].malli[1].sisus[0].textuuri2=55;
						mallit[1].malli[1].sisus[0].textuuri=55;
					}
					else{
						mallit[1].malli[1].sisus[0].textuuri2=56;
						mallit[1].malli[1].sisus[0].textuuri=56;
					}
				}
				draw(1,1,1,&mallit[1].malli[1]);
					
	
	}

	
	capture_man[0].left=false;
	capture_man[0].right=false;
	
	//bullets
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );	
	m_pDevice->SetRenderState(D3DRS_AMBIENT, 0x00FFFFFF);
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);	
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
	mallit[1].malli[1].sisus[0].textuuri2=57;
	mallit[1].malli[1].sisus[0].textuuri=57;
		
	bool osuma;
	float osumax,osumaz,rad;
	for (q=0; q<maximum_bullets; q++){
		if(bullet[q].dead)continue;
		bullet[q].position2.x=bullet[q].position.x;
		bullet[q].position2.z=bullet[q].position.z;
		bullet[q].position.x=bullet[q].position.x+bullet[q].movement.x*elapsed*pelinopeus;		
		bullet[q].position.z=bullet[q].position.z+bullet[q].movement.z*elapsed*pelinopeus;	
		
		matriisi->LoadIdentity();	
		matriisi->TranslateLocal(bullet[q].position.x,0,bullet[q].position.z);	
		matriisi->RotateYawPitchRollLocal(bullet[q].rotate.x,bullet[q].rotate.y+pi/2,bullet[q].rotate.z+pi/2);
		matriisi->ScaleLocal(0.1f,2.5f,0.5f);
		
		draw(1,1,1,&mallit[1].malli[1]);

		//hits men
		for (a=0; a<100; a++){
			if(capture_man[a].dead)continue;
			if(capture_man[a].side==bullet[q].target)continue;
			rad=40*man_size;
			if(viivaviiva(true,&osuma,&osumax,&osumaz,bullet[q].position2.x,bullet[q].position2.z,bullet[q].position.x,bullet[q].position.z,capture_man[a].x,capture_man[a].z+rad,capture_man[a].x-rad,capture_man[a].z))goto osuma1;
			if(viivaviiva(true,&osuma,&osumax,&osumaz,bullet[q].position2.x,bullet[q].position2.z,bullet[q].position.x,bullet[q].position.z,capture_man[a].x,capture_man[a].z-rad,capture_man[a].x+rad,capture_man[a].z))goto osuma1;
			if(viivaviiva(true,&osuma,&osumax,&osumaz,bullet[q].position.x,bullet[q].position.z,bullet[q].position2.x,bullet[q].position2.z,capture_man[a].x+rad,capture_man[a].z,capture_man[a].x,capture_man[a].z+rad))goto osuma1;		
			if(viivaviiva(true,&osuma,&osumax,&osumaz,bullet[q].position.x,bullet[q].position.z,bullet[q].position2.x,bullet[q].position2.z,capture_man[a].x-rad,capture_man[a].z,capture_man[a].x,capture_man[a].z-rad))goto osuma1;
			
			continue;

			osuma1:
			playsound(10,0.8f,0,0,0,0);
			//räjähdys
			for (b=0; b<2; b++){savusta(1.0f,randDouble(0.2f,0.5f), randDouble(0.003f,0.009f),true,randDouble(400,900),osumax+randDouble(-10,10),0,osumaz+randDouble(-10,10),0,randDouble(-pi,pi),0,0,0,0,0);}
			//savuaa
			for (b=0; b<2; b++){savusta(0.6f,randDouble(0.1f,0.4f), 0.002f,true,randDouble(1500,2500),osumax,0,osumaz,2,randDouble(-pi,pi),0,0,randDouble(-0.05f,0.05f),0,randDouble(-0.05f,0.05f));}

			bullet[q].dead=true;
			capture_man[a].energy=capture_man[a].energy-10;

		}
	}

	//smoke
	laskesavut();
	//kameran kulma
	float camq=-atan2f(-kamerax2+kamerax1,-kameraz2+kameraz1);			
	float camw=0;
	float came=-atan2f(-kameray2+kameray1,sqrtf((sqr(-kameraz2+kameraz1)+sqr(-kamerax2+kamerax1))));	
	rendersmoke(camq,camw,came);

	//who wins
	if(pelivaihe2==0){
		//defender wins
		if((sides[0]<=0)&&(sides[1]>0)){
			pelivaihe2=2;
			capture_end_timer=4000;
		}
		//attacker wins
		if((sides[1]<=0)&&(sides[0]>0)){
			pelivaihe2=1;
			capture_end_timer=4000;
		}
	}
	//end capture
	if((pelivaihe2==1)||(pelivaihe2==2)){
		capture_end_timer=capture_end_timer-elapsed*pelinopeus;
		if(capture_end_timer<0){			
			//take ship
			if(pelivaihe2==1){				
				edit_shipslot(2);
			}
			//back to space
			if(pelivaihe2==2){
				pelivaihe=0;
				pelivaihe2=0;				
				//possible end plot
				if(battle.endplot!=-1)
				create_dialog(2,battle.endplot,0);//prize plot
			}
		}
	}
	if(pelivaihe2==2){
		kirjota(1,-1,-1,-1,335,368,30,"You have failed to capture the ship and your tactical skills are being questioned by some crewmen. You blow the ship from a distance, so that no one can have it...");
	}
	if(pelivaihe2==1){
		kirjota(1,-1,-1,-1,335,368,30,"The ship was successfully captured and your crew anxiously starts fitting it for service...");
	}

}

void rendersmoke(float camq,float camw,float came){
	int q;
	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000);
			m_pDevice->LightEnable(0, FALSE);
			m_pDevice->LightEnable(1, FALSE);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);//ei kirjota z-bufferiin, jotta savut olisi läpinäkyvät
			m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);

			m_pDevice->SetRenderState(D3DRS_SRCBLEND, 
												D3DBLEND_ONE );
					m_pDevice->SetRenderState(D3DRS_DESTBLEND, 
												D3DBLEND_ONE );
			for (q=0; q<maksimisavuja; q++){
				if(savu[q].pois)continue;
				if(pelivaihe!=3)if(sqr(savu[q].paikka.x-ship[player_controlled_ship].x1)+sqr(savu[q].paikka.z-ship[player_controlled_ship].z1)>sqr(2000*(cameraheight*0.00022f)))continue;
				
				switch(savu[q].tyyppi){
				
				case 0:{//liekki
					matriisi->LoadIdentity();
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(savu[q].q,savu[q].w,savu[q].e+pi/2);
					matriisi->ScaleLocal(savu[q].koko,savu[q].koko,savu[q].koko);					
					
					draw(savu[q].transparency,savu[q].transparency,savu[q].transparency,&mallit[0].malli[0]);
					break;					   
				}
				case 1:{//räjähdys
					matriisi->LoadIdentity();
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(camq,camw,came);
					matriisi->ScaleLocal(savu[q].koko,savu[q].koko,savu[q].koko);
							
					draw(savu[q].transparency,savu[q].transparency,savu[q].transparency,&mallit[0].malli[1]);
					break;
				}
				case 2:{//savu
					matriisi->LoadIdentity();
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(savu[q].q,savu[q].w,savu[q].e+pi/2);
					matriisi->ScaleLocal(savu[q].koko,savu[q].koko,savu[q].koko);
						
					draw(savu[q].transparency,savu[q].transparency,savu[q].transparency,&mallit[0].malli[2]);
					break;
				}
			
			}
			
			}
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
			m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);



}

void render_cutscene(void){//renders a cutscene
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	char teksti[1000];
	int q;
	switch(pelivaihe2){				
		case 0:{
					strcpy(teksti,"The year was 2314 and you had just been hired as a crewman of a small cargo vessel Wolf IV. Transporting goods between mankinds most remote colonies: Saturn´s moons, Pluto and such.");
						break;
			   }
		case 1:{
					strcpy(teksti,"Mankind had spread to pretty much everywhere in the solar system forming the Federation. Some even dreamed of going to other stars, but no one had such technology. It was a peaceful time, no wars, no killing. You could almost wonder why everyone had big armed starships, but that was the way it had to be. If you are a spacefaring race, every single one of your ships has to have a lot of guns aboard even though it´s peace.");
						break;
			   }
		case 2:{
					strcpy(teksti,"But then came the aliens. Not warlike at all, a very peaceful bunch. But the news they had was bad. They claimed that our sun would blow up in a great big supernova and that they were here to rescue all those who had enough money. Good business for the aliens you might say.");
						break;
			   }
		case 3:{
					strcpy(teksti,"The Federation collapses into wars and corruption. You too, decide to seize the opportunity to gather enough money to be saved. With your closest crewmates you capture the ship you are working on, Wolf IV, to become interplanetary pirates. There is no time to loose, you must gather enough loot to win your salvation. Unless, of course, you happen to die before that.");
						break;
			   }
		case 4:{
					strcpy(teksti,"You have died. Your pirating days are over. Your bits and pieces float aimlessly in the vacuum of space until the sun blows up. Now would be a good time to load your game.");
						break;
			   }
		case 5:{
					strcpy(teksti,"The drill is carefully targeted and fired. Earth´s portentous space station is blown up within seconds. While Coalition´s forces engage what is left of Earth´s fleet, you prepare to attack.");
						break;
			   }
		case 6:{
					strcpy(teksti,"You pay the aliens what they asked: one GAZILLION GOLD PIECES. You and your crew are taken aboard their mysterious ships and you are taken to a safe distance away from the sun. Then, with great anticipation, the aliens push a button that blows up the sun.");
						break;
			   }
		case 7:{
					strcpy(teksti,"So, did you find your salvation from the menace that destroyed mankind. And having no further concern, you and your companions sought adventure in the alien worlds. Many wars and feuds did you fight. Honor and fear were heaped upon your name. In time, you became an emperor by your own hand.... But that is another story.");
						break;
			   }
	}



	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0 );
	
	//light
	ZeroMemory(&lamppu[0].valo, sizeof(D3DLIGHT8));	
	lamppu[0].valo.Position.y = 0;
	lamppu[0].valo.Position.x = 0;
	lamppu[0].valo.Position.z = 0;
	lamppu[0].valo.Range = 50000;
	lamppu[0].valo.Diffuse.r = 1;    
	lamppu[0].valo.Diffuse.g = 1;
	lamppu[0].valo.Diffuse.b = 1;    
	lamppu[0].valo.Ambient.r = 2.0f;
	lamppu[0].valo.Ambient.g = 2.0f;    
	lamppu[0].valo.Ambient.b = 2.0f;
	lamppu[0].valo.Specular.r = 1.0f;    
	lamppu[0].valo.Specular.g = 1.0f;
	lamppu[0].valo.Specular.b = 1.0f;
	lamppu[0].valo.Type=D3DLIGHT_POINT;
	lamppu[0].valo.Attenuation0=1;
	lamppu[0].valo.Attenuation1=0;
	lamppu[0].valo.Attenuation2=0;
	m_pDevice->SetLight(0, &lamppu[0].valo);

	//camera
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((60)*pi/180), aspect, 25.0f, maxvisible);			
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

		kamerax1=0;
		kameray1=1000;
		kameraz1=0;
		kamerax2=kamerax1-1;
		kameray2=0;
		kameraz2=kameraz1;
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );


	//draw the picture
			m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(0,0,0);			
			matriisi->RotateYawPitchRollLocal(-pi/2,pi/2,0);			
			matriisi->ScaleLocal(7,7,7);

				switch(pelivaihe2){				
						case 0:{
							mallit[1].malli[1].sisus[0].textuuri2=43;
							mallit[1].malli[1].sisus[0].textuuri=43;
							break;
							   }
						case 1:{
							mallit[1].malli[1].sisus[0].textuuri2=46;
							mallit[1].malli[1].sisus[0].textuuri=46;
							break;
							   }
						case 2:{
							mallit[1].malli[1].sisus[0].textuuri2=44;
							mallit[1].malli[1].sisus[0].textuuri=44;
							break;
							   }
						case 3:{
							mallit[1].malli[1].sisus[0].textuuri2=45;
							mallit[1].malli[1].sisus[0].textuuri=45;
							break;
							   }
						case 4:{
							mallit[1].malli[1].sisus[0].textuuri2=58;
							mallit[1].malli[1].sisus[0].textuuri=58;
							break;
							   }
						case 5:{
							mallit[1].malli[1].sisus[0].textuuri2=66;
							mallit[1].malli[1].sisus[0].textuuri=66;
							break;
							   }
						case 6:{
							mallit[1].malli[1].sisus[0].textuuri2=69;
							mallit[1].malli[1].sisus[0].textuuri=69;
							break;
							   }
						case 7:{
							mallit[1].malli[1].sisus[0].textuuri2=68;
							mallit[1].malli[1].sisus[0].textuuri=68;
							break;
							   }
				}
				
				drawfast(&mallit[1].malli[1]);
					
			
			


	kirjota(1,-1,-1,-1,200,610,50,teksti);
	kirjota(1,-1,-1,-1,400,750,0,"Press Enter to continue");

	
	if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){		
		if(dialog.noreturn){dialog.noreturn=false;return;}
		playsound(0,1,0,0,0,0);
		switch(pelivaihe2){	
			case 0:{pelivaihe2=1;break;}
			case 1:{pelivaihe2=2;break;}
			case 2:{pelivaihe2=3;break;}
			case 3:{create_dialog(2,0,0);//start plot
				break;}
			case 4:{//go to menu
				menu_return_pelivaihe=-1;
				menu_return_pelivaihe2=-1;
				pelivaihe=7;

				pelivaihe2=5;
				focus=0;
				//particles
				for (q=0; q<maximum_particles; q++){
					particle[q].dead=true;
				}
				break;}
			case 5:{
				//set Earth's defence lower
				planet[2].military=2;
				//set mission:attack Earth
				dialog.option[0].mission.type=0;//goto planet
				dialog.option[0].mission.planet=2;//Earth
				dialog.option[0].mission.prize_plot=45;//about to attack Earth
				strcpy(dialog.option[0].mission.name,"Attack Earth");//name mission
				strcpy(dialog.option[0].mission.text,"The drill has been fired and you are on your way to attack Earth.");//mission briefing
				mission[free_mission()]=dialog.option[0].mission;
				pelivaihe=0;
				pelivaihe2=0;
				break;}
			case 6:{pelivaihe2=7;break;}
			case 7:{//go to menu
				menu_return_pelivaihe=-1;
				menu_return_pelivaihe2=-1;
				pelivaihe=7;
				pelivaihe2=5;
				focus=0;
				//particles
				for (q=0; q<maximum_particles; q++){
					particle[q].dead=true;
				}
				break;}
		}


		
	}

}



void render_map(void){//draws solar system map

	int d,q;
	
	//erase all smoke
	for (q=0; q<maksimisavuja; q++){
		savu[q].pois=true;
	}
	//erase all particles
	for (q=0; q<maximum_particles; q++){
		particle[q].dead=true;
	}

	//background
	LPDIRECT3DSURFACE8 pBackBuffer;
    m_pDevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
	RECT rcSource[] = {  0,  0,  SCREEN_WIDTH,  SCREEN_HEIGHT};
	POINT ptDest[]   = {  0,  0};
    m_pDevice->CopyRects(kuvia[3], rcSource, 1, pBackBuffer, ptDest);
    pBackBuffer->Release();


	//kamera
		kamerax1=0;
		kameray1=4200;

		kameraz1=0;
		kamerax2=1;
		kameray2=0;
		kameraz2=0;		
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
		D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );
		m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);


	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
		
	//planets	
	float tx,tz;
	for (q=0; q<9; q++){
		if(planet[q].dead)continue;		
		D3DXMATRIX tempmatrix;
		D3DXPLANE plane;
		D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
		D3DXMatrixShadow(&tempmatrix,&D3DXVECTOR4(0,4200,0,0),&plane);
		matriisi->LoadMatrix(&tempmatrix);
			
		tx=planet[q].x*-2.32f*0.01f;
		tz=planet[q].z*-2.32f*0.01f;

		matriisi->TranslateLocal(tx,0,tz);	
		matriisi->RotateYawPitchRollLocal(planet[q].rx,planet[q].ry,planet[q].rz);			
		
		float size;
		size=(1/planet[q].size)*2;
		matriisi->ScaleLocal(size,size,size);	
		m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);		
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
		drawfast(&mallit[1].malli[planet[q].picture]);

			
		//shadow
		if(planet[q].shadow==0){
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,FALSE);		
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(tx,0,tz);
			matriisi->RotateYawPitchRollLocal(planet[q].angletosun,0,0);			
			matriisi->ScaleLocal(-2,1,-2);
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO    );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_SRCCOLOR);				
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);	
			matriisi->RotateYawPitchRollLocal(0,pi/2,0);
			draw(1.0f,1.0f,1.0f,&mallit[1].malli[24]);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
		}
		
		
		//atmosphere / ring
		if(planet[q].atmosphere!=-1){
			m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(tx,0,tz);								
			matriisi->RotateYawPitchRollLocal(planet[q].rx,planet[q].ry,planet[q].rz);			
			matriisi->ScaleLocal(size*1.2f,size*1.2f,size*1.2f);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);	
			matriisi->RotateYawPitchRollLocal(0,planet[q].ry,0);
			draw(0.3f,0.3f,0.3f,&mallit[1].malli[planet[q].atmosphere]);
			m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
		}


	}

	
	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);		
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	//m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,TRUE);

	
	d=0;	
	tx=ship[d].x1*-2.32f*0.01f;
	tz=ship[d].z1*-2.32f*0.01f;		

	matriisi->LoadIdentity();
	
	matriisi->TranslateLocal(tx,0,tz);
	matriisi->RotateYawPitchRollLocal(ship[d].rx+pi,ship[d].ry,ship[d].rz);
	matriisi->ScaleLocal(0.3f,0.3f,0.3f);
	drawfast(&mallit[2].malli[ship[d].encounter.ship_basea.picture]);


	//m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);

	//planet's names
	float textx,textz;
	bool osuma;
	float osumax,osumaz;
	for (q=0; q<9; q++){
		if(planet[q].dead)continue;
		
		textx=planet[q].x*-2.32f*0.001f*-3.4f+384;
		textz=planet[q].z*-2.32f*0.001f*-3.4f+512+15;

		if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,3,0,3,1024)){textx=osumax;textz=osumaz;}
		if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,750,0,750,1024)){textx=osumax;textz=osumaz;}
		if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,0,5,768,5)){textx=osumax;textz=osumaz;}
		if(viivaviiva(true,&osuma,&osumax,&osumaz,384,512,textx,textz,0,900,768,900)){textx=osumax;textz=osumaz;}
		
		kirjota(1,-1,-1,-1,textz,textx,0,planet[q].name);	
	}
}

int free_mission(void){//finds a free mission
		
		int a,b;
		int d=-1;

						a=0;
			b=0;
					alku2:
					a=randInt(0,100);
					b=b+1;					
					if(b>100)mission[a].dead=true;
					if(!mission[a].dead)goto alku2;
			return a;
}

void compute_missions(void){//calculates which missions are finished
	int q,a,d;
	bool mission_complete;

	//mission:money offer timer
	if(money_offer_timer>0){
		money_offer_timer=money_offer_timer-elapsed*pelinopeus;
		if(money_offer_timer<1000){
			create_dialog(2,25,0);//money offer timer
			money_offer_timer=-1;
		}
	}

	//list missions
	for (q=0; q<100; q++)missionlist[q]=-1;
	d=0;
	for (q=0; q<100; q++){
		if(mission[q].dead)continue;
		missionlist[d]=q;
		d++;
	}

	//no mission selected while there are some available
	if((selected_mission==-1)&&(d>0))selected_mission=0;

	for (q=0; q<100; q++){
		if(mission[q].dead)continue;
		mission_complete=true;

		switch (mission[q].type)
			{
			case 0:{//goto planet
				if(ship[0].onplanet==mission[q].planet){
					mission[q].dead=true;
					mission[q].planet=-1;
					for(a=0;a<5;a++){shipslot[0].cargo[a]=shipslot[0].cargo[a]+mission[q].cargoplus[a];}//prize stuff
					create_dialog(2,mission[q].prize_plot,0);//prize plot
					ship[0].nearstar2=ship[0].nearstar;//take ship off planet
					if(mission[q].end_flag_do!=-1)end_mission[mission[q].end_flag_do]=true;//end some other mission
				}								
				break;				   
				   }
			case 1:{//items to planet
				if(ship[0].onplanet==mission[q].planet){
					for(a=0;a<5;a++)if(shipslot[0].cargo[a]<mission[q].cargominus[a])mission_complete=false;

					if(mission_complete){
						for(a=0;a<5;a++){shipslot[0].cargo[a]=shipslot[0].cargo[a]+mission[q].cargoplus[a];}//prize stuff
						for(a=0;a<5;a++){shipslot[0].cargo[a]=shipslot[0].cargo[a]-mission[q].cargominus[a];}//take stuff
						mission[q].dead=true;
						mission[q].planet=-1;
						create_dialog(2,mission[q].prize_plot,0);//prize plot
						ship[0].nearstar2=ship[0].nearstar;//take ship off planet
						if(mission[q].end_flag_do!=-1)end_mission[mission[q].end_flag_do]=true;//end some other mission
					}
				}			
				break;				   
				   }			
			case 2:{//terminate mission by flag
				if(end_mission[mission[q].end_flag]){
					if(mission_complete){						
						mission[q].dead=true;
						mission[q].planet=-1;
						create_dialog(2,mission[q].prize_plot,0);//prize plot
						ship[0].nearstar2=ship[0].nearstar;//take ship off planet
						if(mission[q].end_flag_do!=-1)end_mission[mission[q].end_flag_do]=true;//end some other mission
					}
				}
				break;
				   }
		}
	}
}


void render_missions(void){//draws diagram of missions

	int d,q;
	
	//erase all smoke
	for (q=0; q<maksimisavuja; q++){
		savu[q].pois=true;
	}
	//erase all particles
	for (q=0; q<maximum_particles; q++){
		particle[q].dead=true;
	}

	//background
	LPDIRECT3DSURFACE8 pBackBuffer;
    m_pDevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
	RECT rcSource[] = {  0,  0,  SCREEN_WIDTH,  SCREEN_HEIGHT};
	POINT ptDest[]   = {  0,  0};
    m_pDevice->CopyRects(kuvia[4], rcSource, 1, pBackBuffer, ptDest);
    pBackBuffer->Release();


	//kamera
		kamerax1=0;
		kameray1=4200;

		kameraz1=0;
		kamerax2=1;
		kameray2=0;
		kameraz2=0;		
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
		D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );
		m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->LightEnable(1, FALSE);


	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);

	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00FFFFFF);		
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	//list missions
	float textx,textz;
	for (q=0; q<100; q++)missionlist[q]=-1;
	textx=140;
	textz=80;
	d=0;
	for (q=0; q<100; q++){
		if(mission[q].dead)continue;
		kirjota(1,-1,-1,-1,textz,textx,0,mission[q].name);	
		if(selected_mission==d)kirjota(1,-1,-1,-1,textz,textx,0,mission[q].name);
		textx=textx+18;
		missionlist[d]=q;
		d++;
	}
	missions=d;

	//if no missions, unselect
	if(missions==0){
		selected_mission=-1;
		kirjota(1,-1,-1,-1,textz,textx,20,"There are no missions currently active.");
	}
	//if selected mission is done
	if(missionlist[selected_mission]==-1){
		selected_mission=-1;
	}

	//select mission 0 by default
	if((missions>0)&&(selected_mission==-1))
		selected_mission=0;

	//mission description
	if(selected_mission!=-1){
		kirjota(1,-1,-1,-1,590,170,23,mission[missionlist[selected_mission]].text);
	}
	
}

int randomplanet(int number){
	int planetn=randInt(0,89);
	if(number==-1){
		planetn=randInt(0,89);
	}
	else{
		a:
		while(planetn==number)planetn=randInt(0,89);
		if(planet[planetn].population==0){planetn=randInt(0,89);goto a;}
	}

	return planetn;
}

HRESULT Screenshot(LPDIRECT3DDEVICE8 lpDevice, const char* lpszFileName,char line[200]){

    LPDIRECT3DSURFACE8 lpSurface = NULL;    // copy of the front buffer
    LPDIRECT3D8 lpD3D = NULL;   // IDirect3D8 interface that created lpDevice
    LPBYTE Bits = NULL;         // bitmap bits of the DIB
    FILE* f = NULL;             // BMP file handle

#define BITMAP_FILE_SIGNATURE 'MB'

    // check whether parameters are valid
    if (!lpDevice)
    {
     //   throw invalid_argument("Function \"Screenshot\": "
     //       "LPDIRECT3DDEVICE8 lpDevice is NULL.");
    }

//try
{
    string FileName;            // name of the BMP file

    // if a filename is given, use it
    if (lpszFileName)
    {   FileName = lpszFileName; }
    // if no filename is given, have a filename generated
    else
    {   GetScreenshotFileName(FileName); }

    // We need to know for which adapter the Direct3D device was created,
    // so that we can query the right adapter's screen dimensions.
    // Therefore, query the device's creation parameters
    D3DDEVICE_CREATION_PARAMETERS dcp;
    dcp.AdapterOrdinal = D3DADAPTER_DEFAULT;
    lpDevice->GetCreationParameters(&dcp);

    D3DDISPLAYMODE dm;
    dm.Width = dm.Height = 0;

    // retrieve pointer to IDirect3D8 interface,
    // which provides the GetAdapterDisplayMode method
    lpDevice->GetDirect3D(&lpD3D);
    if (lpD3D)
    {
        // query the screen dimensions of the current adapter
        lpD3D->GetAdapterDisplayMode(dcp.AdapterOrdinal, &dm);
        RELEASE(lpD3D);
    }

    // create a 32-bit ARGB system-memory surface that is going to receive
    // a copy of the front buffer's contents
    if (FAILED(lpDevice->CreateImageSurface(
        dm.Width, dm.Height,
        D3DFMT_A8R8G8B8,
        &lpSurface
    )))
    {
       // throw runtime_error("Function \"Screenshot\": "
       //     "IDirect3DDevice8::CreateImageSurface failed.");
    }

    // have the GetFrontBuffer method copy the contents of the front
    // buffer to our system-memory surface
    if (FAILED(lpDevice->GetFrontBuffer(lpSurface)))
    {
       // throw runtime_error("Function \"Screenshot\": "
       //    "IDirect3DDevice8::GetFrontBuffer failed.");
    }

    // prepare the bitmap info header
    BITMAPINFOHEADER bmih;
    bmih.biSize = sizeof(bmih);
    bmih.biWidth = dm.Width;
    bmih.biHeight = dm.Height;
    bmih.biPlanes = 1;
    bmih.biBitCount = 24;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = dm.Width * dm.Height * 3;
    bmih.biXPelsPerMeter = 0;
    bmih.biYPelsPerMeter = 0;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;

    // reserve memory for the DIB's bitmap bits
    // (The extra byte is needed because the bitmap is 24-bit but we're
    // going to write 32 bits (a DWORD) at a time. When we write the
    // last pixel, we'll exceed the array's limit if we don't reserve an
    // extra byte.)
    Bits = new BYTE[bmih.biSizeImage + 1];
    if (!Bits)
    {
       // throw runtime_error("Function \"Screenshot\": "
        //    "Could not allocate memory for bitmap bits.");
    }

    // lock the surface for reading
    D3DLOCKED_RECT LockedRect;
    if (FAILED(lpSurface->LockRect(&LockedRect, NULL, D3DLOCK_READONLY)))
    {
       // throw runtime_error("Function \"Screenshot\": "
       //     "IDirect3DSurface8::LockRect failed.");
    }

    // flip the bitmap vertically (because that's how DIBs are stored)
    // and convert it from 32-bits to 24-bits (some bitmap viewers can't
    // handle 32-bit bitmaps, although it's a valid format)

    LPDWORD lpSrc;
    LPBYTE lpDest = Bits;

    // read pixels beginning with the bottom scan line
    for (int y = dm.Height - 1; y >= 0; y--)
    {
        // calculate address of the current source scan line
        lpSrc = reinterpret_cast<LPDWORD>(LockedRect.pBits) + y * dm.Width;
        for (int x = 0; x < dm.Width; x++)
        {
            // store the source pixel in the bitmap bits array
            *reinterpret_cast<LPDWORD>(lpDest) = *lpSrc;
            lpSrc++;        // increment source pointer by 1 DWORD
            lpDest += 3;    // increment destination pointer by 3 bytes
        }
    }

    // we can unlock and release the surface
    lpSurface->UnlockRect();
    RELEASE(lpSurface);

    // prepare the bitmap file header
    BITMAPFILEHEADER bmfh;
    bmfh.bfType = BITMAP_FILE_SIGNATURE;
    bmfh.bfSize = sizeof(bmfh) + sizeof(bmih) + bmih.biSizeImage;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    bmfh.bfOffBits = sizeof(bmfh) + sizeof(bmih);

    // create the BMP file
    f = fopen(FileName.c_str(), "wb");
    if (!f)
    {
        char Msg[MAX_PATH + 256];
        wsprintf(
            Msg,
            "Function \"Screenshot\": "
             "The file \"%s\" could not be created.",
            FileName.c_str()
        );
        //throw runtime_error(Msg);
    }

	strcpy(screenshot_name,FileName.c_str());

    // dump the file header
    if (!fwrite(reinterpret_cast<void*>(&bmfh), sizeof(bmfh), 1, f))
    {  // THROW_FWRITE_EXCEPTION(FileName.c_str()); 
	}
    // dump the info header
    if (!fwrite(reinterpret_cast<void*>(&bmih), sizeof(bmih), 1, f))
    { //  THROW_FWRITE_EXCEPTION(FileName.c_str()); 
	}
    // dump the bitmap bits
    if (fwrite(reinterpret_cast<void*>(Bits), sizeof(BYTE),
        bmih.biSizeImage, f) < bmih.biSizeImage)
    {  	//THROW_FWRITE_EXCEPTION(FileName.c_str());
	}

    // close the file
    fclose(f);

    // free the memory for the bitmap bits
    SAFEDELETEARRAY(Bits);

    return S_OK;
}

}
void GetScreenshotFileName(string& FileName)
{
    // retrieve the filename of the EXE file
    string ModuleFileName;
    ModuleFileName.reserve(MAX_PATH);
    GetModuleFileName(
        NULL, const_cast<char*>(ModuleFileName.data()), MAX_PATH);
    // extract the path info from the filename
    FileName = ModuleFileName.substr(0, ModuleFileName.find_last_of(":\\"));
    // append the sub-folder path
  //  FileName += SCREENSHOT_REL_PATH;

    // search for first unused filename
    char Buf[MAX_PATH];
    WIN32_FIND_DATA ffd;
    HANDLE h;
    for (int i = 0; i < 1000; i++)
    {
        // prepare search mask for FindFirstFile
        wsprintf(Buf, (FileName + "shot%03i.bmp").c_str(), i);
        // check whether this file already exists
        h = FindFirstFile(Buf, &ffd);
        // if the file exists, close the search handle and continue
        if (h != INVALID_HANDLE_VALUE)
        {   FindClose(h); }
        // if the file does not exist, exit from the loop
        else
        {   break; }
    }

    // set FileName to the first unused filename
    FileName = Buf;
}

void save_game(int slot){//saves game
	
	SYSTEMTIME current_time;
	GetLocalTime(&current_time);
	
		int q,a;
		FILE *fil;
		game_saved_timer=5000;
		char tallennusrivi[300];

		itoa(slot,temprivi,10);
		strcpy(tallennusrivi,"save/s");
		strcat(tallennusrivi,temprivi);
		strcat(tallennusrivi,".sav");
		
		fil = fopen(tallennusrivi,"wb");

		//name	
		itoa((int)(current_time.wMonth),rivi,10);//strcpy(rivi,temprivi);
		strcat(rivi,".");
		itoa((int)(current_time.wDay),temprivi,10);strcat(rivi,temprivi);
		strcat(rivi,".");
		itoa((int)(current_time.wYear),temprivi,10);strcat(rivi,temprivi);
		strcat(rivi," ");
		if(current_time.wHour<10)strcat(rivi,"0");
		itoa((int)(current_time.wHour),temprivi,10);strcat(rivi,temprivi);
		strcat(rivi,":");
		if(current_time.wMinute<10)strcat(rivi,"0");
		itoa((int)(current_time.wMinute),temprivi,10);strcat(rivi,temprivi);
		fprintf(fil, "%s\n",rivi);

		//shipslot
		for (q=0; q<maximum_shipslot; q++){			
			fprintf(fil, "%f\n", shipslot[q].energy);
			fprintf(fil, "%d\n", shipslot[q].dead);
			fprintf(fil, "%s\n", shipslot[q].name);
			fprintf(fil, "%d\n", shipslot[q].ship_basea.ship_type);
			for (a=0; a<5; a++){fprintf(fil, "%d\n", shipslot[q].cargo[a]);}
		}
		//ship 0
		fprintf(fil, "%f\n", ship[0].x1);
		fprintf(fil, "%f\n", ship[0].z1);
		fprintf(fil, "%f\n", ship[0].x2);
		fprintf(fil, "%f\n", ship[0].z2);
		fprintf(fil, "%f\n", ship[0].rx);
		fprintf(fil, "%f\n", ship[0].ry);
		fprintf(fil, "%f\n", ship[0].rz);
		fprintf(fil, "%f\n", ship[0].vx);
		fprintf(fil, "%f\n", ship[0].vz);
		fprintf(fil, "%f\n", ship[0].vr);
		fprintf(fil, "%d\n", ship[0].nearstar);
		fprintf(fil, "%d\n", ship[0].nearstar2);

		//missions
		for (q=0; q<100; q++){	
			fprintf(fil, "%d\n", mission[q].dead);
			fprintf(fil, "%d\n", mission[q].type);
			fprintf(fil, "%s\n", mission[q].name);
			fprintf(fil, "%s\n", mission[q].text);
			fprintf(fil, "%d\n", mission[q].planet);
			for (a=0; a<5; a++)fprintf(fil, "%d\n", mission[q].cargominus[a]);
			fprintf(fil, "%d\n", mission[q].end_flag);
			for (a=0; a<5; a++)fprintf(fil, "%d\n", mission[q].cargoplus[a]);
			fprintf(fil, "%d\n", mission[q].prize_plot);
			fprintf(fil, "%d\n", mission[q].end_flag_do);
		}
		//planets
		for (q=0; q<89; q++){
			fprintf(fil, "%f\n", planet[q].radiustohost);
			fprintf(fil, "%f\n", planet[q].angletohost);
			fprintf(fil, "%f\n", planet[q].rx);
			fprintf(fil, "%f\n", planet[q].ry);
			fprintf(fil, "%f\n", planet[q].rz);
			fprintf(fil, "%d\n", planet[q].picture);
			fprintf(fil, "%d\n", planet[q].population);
			fprintf(fil, "%d\n", planet[q].wealth);
			fprintf(fil, "%d\n", planet[q].military);
			for (a=0; a<5; a++)fprintf(fil, "%d\n", planet[q].prize[a]);
		}
		//miscellaneous
			fprintf(fil, "%d\n", player_controlled_ship_in_map);
		//plot
			fprintf(fil, "%d\n", plot_started);//if the plot has started
			fprintf(fil, "%d\n", dan_planet);//which planet diesel dan is on
			for (q=0; q<100; q++)fprintf(fil, "%d\n", end_mission[q]);//end mission
			fprintf(fil, "%d\n", money_offer_timer);//how long before money offer is made
			fprintf(fil, "%d\n", alien_planet);//which planet the aliens are on
			
		fclose(fil);

		luesavet();
}


void load_game(int slot){//load game
		

		new_game();

		int q,a;
		FILE *fil;
		game_saved_timer=-5000;
		char tallennusrivi[300];

		itoa(slot,temprivi,10);
		strcpy(tallennusrivi,"save/s");
		strcat(tallennusrivi,temprivi);
		strcat(tallennusrivi,".sav");
		
		fil = fopen(tallennusrivi,"rb");

		//fgets(temprivi,sizeof(temprivi),fil); vaikeustaso=atoi(temprivi);
		
		//name
		fgets(temprivi,sizeof(temprivi),fil);
		//shipslot
		for (q=0; q<maximum_shipslot; q++){	
			fgets(temprivi,sizeof(temprivi),fil); shipslot[q].energy=atof(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); shipslot[q].dead=strtobool(temprivi);
			stripped_fgets(temprivi,sizeof(temprivi),fil); strcpy(shipslot[q].name,temprivi);
			fgets(temprivi,sizeof(temprivi),fil); shipslot[q].ship_basea=ship_base[atoi(temprivi)];
			for (a=0; a<5; a++){fgets(temprivi,sizeof(temprivi),fil); shipslot[q].cargo[a]=atoi(temprivi);}			
		}
		//ship 0
		fgets(temprivi,sizeof(temprivi),fil); ship[0].x1=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].z1=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].x2=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].z2=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].rx=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].ry=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].rz=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].vx=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].vz=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].vr=atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].nearstar=atoi(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); ship[0].nearstar2=atoi(temprivi);

		//missions
		for (q=0; q<100; q++){
			fgets(temprivi,sizeof(temprivi),fil); mission[q].dead=strtobool(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); mission[q].type=atoi(temprivi);
			//fgets(temprivi,sizeof(temprivi),fil); strcpy(mission[q].name,temprivi);
			//fgets(temprivi,sizeof(temprivi),fil); strcpy(mission[q].text,temprivi);
			stripped_fgets(temprivi,sizeof(temprivi),fil); strcpy(mission[q].name,temprivi);
			stripped_fgets(temprivi,sizeof(temprivi),fil); strcpy(mission[q].text,temprivi);
			fgets(temprivi,sizeof(temprivi),fil); mission[q].planet=atoi(temprivi);
			for (a=0; a<5; a++){fgets(temprivi,sizeof(temprivi),fil); mission[q].cargominus[a]=atoi(temprivi);}
			fgets(temprivi,sizeof(temprivi),fil); mission[q].end_flag=atoi(temprivi);
			for (a=0; a<5; a++){fgets(temprivi,sizeof(temprivi),fil); mission[q].cargoplus[a]=atoi(temprivi);}
			fgets(temprivi,sizeof(temprivi),fil); mission[q].prize_plot=atoi(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); mission[q].end_flag_do=atoi(temprivi);
		}
		//planets
		for (q=0; q<89; q++){
			fgets(temprivi,sizeof(temprivi),fil); planet[q].radiustohost=atof(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); planet[q].angletohost=atof(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); planet[q].rx=atof(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); planet[q].ry=atof(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); planet[q].rz=atof(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); planet[q].picture=atoi(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); planet[q].population=atoi(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); planet[q].wealth=atoi(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); planet[q].military=atoi(temprivi);
			for (a=0; a<5; a++){fgets(temprivi,sizeof(temprivi),fil); planet[q].prize[a]=atoi(temprivi);}		
		}
		//miscellaneous
			fgets(temprivi,sizeof(temprivi),fil); player_controlled_ship_in_map=atoi(temprivi);
		//plot
			fgets(temprivi,sizeof(temprivi),fil); plot_started=strtobool(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); dan_planet=atoi(temprivi);
			for (q=0; q<100; q++){fgets(temprivi,sizeof(temprivi),fil); end_mission[q]=strtobool(temprivi);}
			fgets(temprivi,sizeof(temprivi),fil); money_offer_timer=atoi(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); alien_planet=atoi(temprivi);
			
			

		fclose(fil);

	//init space rocks
	for (q=0; q<maximumrocks; q++){
			if(rock[q].dead)continue;
				rock[q].distancesquare=(sqr(rock[q].x-ship[0].x1)+sqr(rock[q].z-ship[0].z1));				
	}
}


void render_menu(void){//renders game menus

	int q;
	RECT rcDest;
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);

	//set mouse position
	POINT ptCursor;
    GetCursorPos( &ptCursor );
    ScreenToClient( hWnd, &ptCursor );
	mousex=ptCursor.x;
	mousey=ptCursor.y;

	//m_pDevice->ShowCursor(TRUE);

	
	//m_pDevice->SetCursorPosition(mousex,mousey,D3DCURSOR_IMMEDIATE_UPDATE);
	//m_pDevice->SetCursorPosition(mousex,mousey,NULL);
	//m_pDevice->SetCursorPosition(500,500,NULL);


	//normalize mouse position
	mousex=mousex/(float)SCREEN_WIDTH*1024.0f;
	mousey=mousey/(float)SCREEN_HEIGHT*768.0f;


	if((int)mousex2!=(int)mousex)	mouse_active=true;
	if((int)mousey2!=(int)mousey)	mouse_active=true;
	if(mouse_button_0)mouse_active=true;
	if(mouse_button_1)mouse_active=true;

	
	mousex2=mousex;
	mousey2=mousey;


	//camera
	kamerax1=0+100;
	kameray1=4200;
	kameraz1=0;

	kamerax2=0;
	kameray2=0;
	kameraz2=0;
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
	m_pDevice->SetTransform( D3DTS_VIEW, &matView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	//m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0 );
	//background
	LPDIRECT3DSURFACE8 pBackBuffer;
    m_pDevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
	RECT rcSource[] = {  0,  0,  SCREEN_WIDTH,  SCREEN_HEIGHT};
	POINT ptDest[]   = {  0,  0};
    m_pDevice->CopyRects(kuvia[5], rcSource, 1, pBackBuffer, ptDest);
    pBackBuffer->Release();

	//kirjota(2,-1,-1,-1,88,124,50,"Stars");
	kirjota(0.9f,-1,-1,-1,168,119,50,"v1.2");

	if((selected_left_menu!=0)||(focus!=0)){
		if(menu_return_pelivaihe==-1)kirjota(1.5f,-1,-1,-1,66,212,50,"New Game");
		else kirjota(1.5f,-1,-1,-1,66,212,50,"Resume");}
	if((selected_left_menu!=1)||(focus!=0))kirjota(1.5f,-1,-1,-1,66,274,50,"Load Game");
	if((selected_left_menu!=2)||(focus!=0))if((menu_return_pelivaihe==0)&&(menu_return_pelivaihe2==0))kirjota(1.5f,-1,-1,-1,66,338,50,"Save Game");
	if((selected_left_menu!=3)||(focus!=0))kirjota(1.5f,-1,-1,-1,66,402,50,"Options");
	if((selected_left_menu!=4)||(focus!=0))kirjota(1.5f,-1,-1,-1,66,466,50,"Quit");

	bool not_enter=false;//for double enter
	bool mouse_on_left=false;
	if(mouse_active)
	for (q=0; q<5; q++){
		if((q==2)&&((menu_return_pelivaihe!=0)||(menu_return_pelivaihe2!=0)))continue;
		rcDest.left = (44)*SCREEN_WIDTH/1024;
		rcDest.bottom =(241+q*62)*SCREEN_HEIGHT/768; 
		rcDest.top = rcDest.bottom-62*SCREEN_HEIGHT/768;
		rcDest.right = rcDest.left+170*SCREEN_WIDTH/1024;	

		if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom)){
			selected_left_menu=q;
			focus=0;
			mouse_on_left=true;
		}
	}
	if(focus==0){
		switch(selected_left_menu){	
			case 0:{
				if(menu_return_pelivaihe==-1)kirjota(1.5f,1,0,0,66,212,50,"New Game");
				else kirjota(1.5f,1,0,0,66,212,50,"Resume");				
				break;}
			case 1:{kirjota(1.5f,1,0,0,66,274,50,"Load Game");break;}
			case 2:{if((menu_return_pelivaihe==0)&&(menu_return_pelivaihe2==0))kirjota(1.5f,1,0,0,66,338,50,"Save Game");break;}
			case 3:{kirjota(1.5f,1,0,0,66,402,50,"Options");break;}
			case 4:{kirjota(1.5f,1,0,0,66,466,50,"Quit");break;}				
		}
		//keyboard
		if ((!KEYDOWN(buffer,  DIK_RETURN ))&&(KEYDOWN(buffer2,  DIK_RETURN)))
		{
			if(dialog.noreturn){dialog.noreturn=false;}
			else{
				focus=1;
				pelivaihe2=selected_left_menu;
				not_enter=true;
				mouse_active=false;
			}
		}
		if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){	
			selected_left_menu=selected_left_menu-1;
			if(selected_left_menu==2)if((menu_return_pelivaihe!=0)||(menu_return_pelivaihe2!=0))selected_left_menu=selected_left_menu-1;
			if(selected_left_menu<0)selected_left_menu=4;
			mouse_active=false;
		}
		if (!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN)){	
			selected_left_menu=selected_left_menu+1;
			if(selected_left_menu==2)if((menu_return_pelivaihe!=0)||(menu_return_pelivaihe2!=0))selected_left_menu=selected_left_menu+1;
			if(selected_left_menu>4)selected_left_menu=0;
			mouse_active=false;
		}
		if (!KEYDOWN(buffer,  DIK_RIGHT )&&KEYDOWN(buffer2,  DIK_RIGHT)){	
			focus=1;
			pelivaihe2=selected_left_menu;
			//selected_left_menu=pelivaihe2;
			mouse_active=false;
		}
	}
	if((mouse_button_was_0)&&(!mouse_button_0)&&(mouse_on_left)){
		//focus=1;
		pelivaihe2=selected_left_menu;		
	}

	if(focus==1){
		if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE)){	
			focus=0;
			selected_left_menu=pelivaihe2;
			mouse_active=false;
		}
	}

	//camera
	kamerax1=0+100;
	kameray1=4200;
	kameraz1=0;

	kamerax2=0;
	kameray2=0;
	kameraz2=0;
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
	m_pDevice->SetTransform( D3DTS_VIEW, &matView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	
	switch(pelivaihe2){

		//new game
		case 0:{
			if(menu_return_pelivaihe==-1){
					kirjota(1.5f,0,0,1,66,212,50,"New Game");
					new_game();
					break;
			}
			else{	
					pelivaihe=menu_return_pelivaihe;
					pelivaihe2=menu_return_pelivaihe2;
					break;
			}
			   }
		//load
		case 1:{
					bool mouse_on_save=false;
					kirjota(1.5f,0,0,1,66,274,50,"Load Game");
					if(no_games_to_load){kirjota(1,-1,-1,-1,430,112,50,"No games to load");focus=0;break;}
					kirjota(1,-1,-1,-1,430,112,50,"Select game to load:");
					//names
					for (q=0; q<10; q++){
						kirjota(1,-1,-1,-1,430,162+q*25,50,m_filenames[q]);						
						if(mouse_active){
							rcDest.left = (430)*SCREEN_WIDTH/1024;
							rcDest.bottom =(172+q*25)*SCREEN_HEIGHT/768; 
							rcDest.top = rcDest.bottom-20*SCREEN_HEIGHT/768;
							rcDest.right = rcDest.left+150*SCREEN_WIDTH/1024;	

							if((loadable[q])&&(mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom)){
								tallennuspaikka=q;
								focus=1;
								mouse_on_save=true;
							}
						}
					}
					if(focus==1){
						//lit
						kirjota(1,-1,-1,-1,431,162+tallennuspaikka*25,50,m_filenames[tallennuspaikka]);
						//keyboard
						if ((loadable[tallennuspaikka])&&((!not_enter)&&(!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN))||((mouse_button_was_0)&&(!mouse_button_0)&&(mouse_on_save))))
						{
							load_game(tallennuspaikka);	
							pelivaihe=0;
							pelivaihe2=0;
							mouse_active=false;
						}
						if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){	
							tallennuspaikka=tallennuspaikka-1;
							if(tallennuspaikka<0)tallennuspaikka=9;
							while(!loadable[tallennuspaikka]){
								tallennuspaikka=tallennuspaikka-1;
								if(tallennuspaikka<0)tallennuspaikka=9;
							}
							mouse_active=false;
						}
						if ((!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN))||(!loadable[tallennuspaikka])){	
							tallennuspaikka=tallennuspaikka+1;
							if(tallennuspaikka>9)tallennuspaikka=0;
							while(!loadable[tallennuspaikka]){
								tallennuspaikka=tallennuspaikka+1;
								if(tallennuspaikka>9)tallennuspaikka=0;
							}
							mouse_active=false;
						}
						if (!KEYDOWN(buffer,  DIK_LEFT )&&KEYDOWN(buffer2,  DIK_LEFT)){	
							focus=0;
							selected_left_menu=pelivaihe2;
							mouse_active=false;
						}
					}
					
					break;
			   }
		//save
		case 2:{
					bool mouse_on_save=false;
					kirjota(1.5f,0,0,1,66,338,50,"Save Game");
					if(!game_started){kirjota(1,-1,-1,-1,430,112,22,"Start a new game by pressing the New Game button.");break;}					
					kirjota(1,-1,-1,-1,430,112,50,"Select save game slot:");
					//names
					for (q=0; q<10; q++){
						kirjota(1,-1,-1,-1,430,162+q*25,50,m_filenames[q]);						
						if(mouse_active){
							rcDest.left = (430)*SCREEN_WIDTH/1024;
							rcDest.bottom =(172+q*25)*SCREEN_HEIGHT/768; 
							rcDest.top = rcDest.bottom-20*SCREEN_HEIGHT/768;
							rcDest.right = rcDest.left+150*SCREEN_WIDTH/1024;	

							if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom)){
								tallennuspaikka=q;
								focus=1;
								mouse_on_save=true;
							}
						}
					}
					if(focus==1){
						//lit
						kirjota(1,-1,-1,-1,431,162+tallennuspaikka*25,50,m_filenames[tallennuspaikka]);
						//keyboard
						if ((!not_enter)&&(!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN))||((mouse_button_was_0)&&(!mouse_button_0)&&(mouse_on_save)))
						{
							save_game(tallennuspaikka);	
							pelivaihe=0;
							pelivaihe2=0;
							mouse_active=false;
						}
						if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){	
							tallennuspaikka=tallennuspaikka-1;
							if(tallennuspaikka<0)tallennuspaikka=9;
							mouse_active=false;
						}
						if (!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN)){	
							tallennuspaikka=tallennuspaikka+1;
							if(tallennuspaikka>9)tallennuspaikka=0;
							mouse_active=false;
						}
						if (!KEYDOWN(buffer,  DIK_LEFT )&&KEYDOWN(buffer2,  DIK_LEFT)){	
							focus=0;
							selected_left_menu=pelivaihe2;
							mouse_active=false;
						}
					}
					break;
			   }
		//options
		case 3:{

					kirjota(1.5f,0,0,1,66,402,50,"Options");
					kirjota(1,-1,-1,-1,430,112,50,"Options: press F1 for help");

						//camera
						kamerax1=0+100;
						kameray1=4200;
						kameraz1=0;

						kamerax2=0;
						kameray2=0;
						kameraz2=0;
						D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
						D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
						m_pDevice->SetTransform( D3DTS_VIEW, &matView );
						m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
						/*D3DXMATRIX tempmatrix;
						D3DXPLANE plane;
						D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
						D3DXMatrixShadow(&tempmatrix,&D3DXVECTOR4(100,4200,0,0),&plane);
						*/
						//light
						ZeroMemory(&lamppu[0].valo, sizeof(D3DLIGHT8));							
						lamppu[0].valo.Range = 50000;
						lamppu[0].valo.Diffuse.r = 1;    
						lamppu[0].valo.Diffuse.g = 1;
						lamppu[0].valo.Diffuse.b = 1;    
						lamppu[0].valo.Ambient.r = 2.0f;
						lamppu[0].valo.Ambient.g = 2.0f;    
						lamppu[0].valo.Ambient.b = 2.0f;
						lamppu[0].valo.Specular.r = 1.0f;    
						lamppu[0].valo.Specular.g = 1.0f;
						lamppu[0].valo.Specular.b = 1.0f;
						lamppu[0].valo.Type=D3DLIGHT_POINT;
						lamppu[0].valo.Attenuation0=0;
						lamppu[0].valo.Attenuation1=0;
						lamppu[0].valo.Attenuation2=0.1f/10000;
						m_pDevice->LightEnable(0, TRUE);
						m_pDevice->SetRenderState(D3DRS_AMBIENT, 0x00000000);
						for (q=0; q<9; q++){
							if(mouse_active){
								rcDest.left = (440)*SCREEN_WIDTH/1024;
								rcDest.bottom =(162+13+q*29)*SCREEN_HEIGHT/768; 
								rcDest.top = rcDest.bottom-29*SCREEN_HEIGHT/768;
								rcDest.right = rcDest.left+230*SCREEN_WIDTH/1024;	

								if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom)){
									selected_option=q;
									focus=1;
								}
							}
							if(option_rotate_speed[q]!=0)option_rotate[q]=option_rotate[q]+option_rotate_speed[q]*elapsed*pelinopeus;
							if(option_rotate[q]>pi){option_rotate_speed[q]=0;option_rotate[q]=pi;options[q]=true;cfg_save();}
							if(option_rotate[q]<0){option_rotate_speed[q]=0;option_rotate[q]=0;options[q]=false;cfg_save();}							
							//matriisi->LoadMatrix(&tempmatrix);
							matriisi->LoadIdentity();
							matriisi->TranslateLocal(-640+85*q,0,-150);
							matriisi->RotateYawPitchRollLocal(0,pi/2+option_rotate[q],pi/2);
							matriisi->ScaleLocal(2.5f,2.5f,2.5f);
							
							lamppu[0].valo.Position.y = 0;
							lamppu[0].valo.Position.x = -640+85*q-400;
							lamppu[0].valo.Position.z = -150-400;
							m_pDevice->SetLight(0, &lamppu[0].valo);
							drawfast(&mallit[0].malli[1]);
							
						}
						for (q=0; q<9; q++){
							kirjota(1,-1,-1,-1,490,162+q*29,50,options_text[q]);
							if((focus==1)&&(selected_option==q))kirjota(1,-1,-1,-1,491,162+q*29,50,options_text[q]);
						}
						if(focus==1){
							//keyboard
							if ((!not_enter)&&(!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN))||((mouse_button_was_0)&&(!mouse_button_0)))
							{
								if(options[selected_option]==false)option_rotate_speed[selected_option]=0.020f;
								else option_rotate_speed[selected_option]=-0.020f;
								
								mouse_active=false;
							}
							if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){	
								selected_option=selected_option-1;
								if(selected_option<0)selected_option=8;
								mouse_active=false;
							}
							if (!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN)){	
								selected_option=selected_option+1;
								if(selected_option>8)selected_option=0;
								mouse_active=false;
							}
							if (!KEYDOWN(buffer,  DIK_LEFT )&&KEYDOWN(buffer2,  DIK_LEFT)){	
								focus=0;
								selected_left_menu=pelivaihe2;
								mouse_active=false;
							}
						}
						//change keys
						if(options[7]){
							wait_for_key=-1;
							pelivaihe2=6;
							options[7]=false;
							option_rotate[7]=0;
							cfg_save();
						}
						//music
						if((!music_initialized)&&(options[6])){
							if(GraphInit()!=S_OK){options[6]=false;}
							else music_initialized=true;
						}
						if((music_initialized)&&(!options[6])){
							if (g_pMediaControl)
								g_pMediaControl->Stop();
						}
						if((music_initialized)&&(options[6])){
							if (g_pMediaControl){
							long State;
							long msTimeout=10;
							g_pMediaControl->GetState(msTimeout,&State);
							if(State==State_Stopped){
								LONGLONG pos=0;

								// Reset to first frame of movie
								g_pMediaSeeking->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
													   NULL, AM_SEEKING_NoPositioning);
								g_pMediaControl->Run();
							}
							}
						}
					break;
			   }
		//quit
		case 4:{
					end_game=true;
					break;
			   }
		//game just started
		case 5:{
					kirjota(1,-1,-1,-1,430,112,50,"Welcome to Wazzal!");
					kirjota(1,-1,-1,-1,430,162,21,"You may press F1 at any time to see the help screen.");
					break;
			   }
		//change keys
		case 6:{					

					kirjota(1,-1,-1,-1,430,112,50,"Change keys");
					kirjota(0.7f,-1,-1,-1,430,127,22,"Keys are represented by numeric values. Don´t be alarmed.");
					q=0;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Up");
					q=1;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Down");
					q=2;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Left");
					q=3;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Right");
					q=4;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Shoot 1");
					q=5;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Shoot 2");
					q=6;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Map");
					q=7;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Mission Log");
					q=8;kirjota(1,(1-sqrtf(fabs((float)selected_key-(float)q))*(1.0f/sqrtf(8))),0.2f,0.2f,430,162+q*18,21,"Switch Ship");


					q=0;if(wait_for_key!=q){itoa(key[1],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}
					q=1;if(wait_for_key!=q){itoa(key[2],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}
					q=2;if(wait_for_key!=q){itoa(key[3],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}
					q=3;if(wait_for_key!=q){itoa(key[4],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}
					q=4;if(wait_for_key!=q){itoa(key[5],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}
					q=5;if(wait_for_key!=q){itoa(key[6],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}
					q=6;if(wait_for_key!=q){itoa(key[9],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}
					q=7;if(wait_for_key!=q){itoa(key[11],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}
					q=8;if(wait_for_key!=q){itoa(key[7],temprivi,10);kirjota(1,-1,-1,-1,570,162+q*18,21,temprivi);}								
					


					if(wait_for_key==-1){
						for (q=0; q<9; q++){
							if(mouse_active){
								rcDest.left = (430)*SCREEN_WIDTH/1024;
								rcDest.bottom =(162+10+q*18)*SCREEN_HEIGHT/768; 
								rcDest.top = rcDest.bottom-18*SCREEN_HEIGHT/768;
								rcDest.right = rcDest.left+230*SCREEN_WIDTH/1024;	

								if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom)){
									selected_key=q;
									focus=1;
								}
							}
						}
						if(focus==1){
								//keyboard
								if ((!not_enter)&&(!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN))||((mouse_button_was_0)&&(!mouse_button_0)))
								{
									not_enter=true;
									wait_for_key=selected_key;
									mouse_active=false;
								}
								if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){	
									selected_key=selected_key-1;
									if(selected_key<0)selected_key=8;
									mouse_active=false;
								}
								if (!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN)){	
									selected_key=selected_key+1;
									if(selected_key>8)selected_key=0;
									mouse_active=false;
								}
								if (!KEYDOWN(buffer,  DIK_LEFT )&&KEYDOWN(buffer2,  DIK_LEFT)){	
									focus=0;
									selected_left_menu=3;
									mouse_active=false;
								}						
						}
					}
					
					//set new key
					if((!not_enter)&&(wait_for_key!=-1)&&(!pressed)&&(pressed2)){
						switch(wait_for_key){
							case 0:q=1;break;
							case 1:q=2;break;
							case 2:q=3;break;
							case 3:q=4;break;
							case 4:q=5;break;
							case 5:q=6;break;
							case 6:q=9;break;
							case 7:q=11;break;
							case 8:q=7;break;						
						}
						key[q]=down2;
						wait_for_key=-1;
						cfg_save();
					}
					break;
			   }
	}

	//camera
	kamerax1=0+100;
	kameray1=4200;
	kameraz1=0;
	kamerax2=0;
	kameray2=0;
	kameraz2=0;
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((30)*pi/180), aspect, 25.0f, maxvisible);		
	m_pDevice->SetTransform( D3DTS_VIEW, &matView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );


	/*fly_particles();
	suntimer=suntimer+elapsed*pelinopeus;
	while(suntimer>=0){
			suntimer=suntimer-9.0f;	

			

			if((mouse_button_0))
				generate_particle(1,randDouble(20,100),(mousey/SCREEN_HEIGHT*768-768/2)*2.9f,0,(mousex/SCREEN_WIDTH*1024-1024/2)*2.9f,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi),randDouble(0,1),0,0,0);
			else
				generate_particle(0,randDouble(20,100),(mousey/SCREEN_HEIGHT*768-768/2)*2.9f,0,(mousex/SCREEN_WIDTH*1024-1024/2)*2.9f,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi),randDouble(0,1),0,0,0);
	}*/

	if(pelivaihe2<5){
		//small picture of earth
		matriisi->LoadIdentity();		
		m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
		m_pDevice->LightEnable(0, FALSE);
		m_pDevice->LightEnable(1, FALSE);
		matriisi->TranslateLocal(-520+pelivaihe2*190,0,-760);
		matriisi->RotateYawPitchRollLocal(23.5f/180*pi,planet[2].ry,0);
		matriisi->ScaleLocal(5.0f,5.0f,5.0f);	
		drawfast(&mallit[1].malli[7]);
		planet[2].ry=planet[2].ry+elapsed*pelinopeus*0.0001f;

		//atmosphere / ring
			if(planet[2].atmosphere!=-1){
				m_pDevice->SetRenderState(D3DRS_ZENABLE ,TRUE);
				m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
				m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
				matriisi->ScaleLocal(0.9f,0.9f,0.9f);
				m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
				m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);	
				matriisi->RotateYawPitchRollLocal(0,planet[2].ry,0);
				draw(0.3f,0.3f,0.3f,&mallit[1].malli[8]);
				m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
			}
	}
	
		
	/*//menu dots
	for (q=0; q<50; q++){
		if(menu_dot[q].x<615)menu_dot[q].x=790;
		if(menu_dot[q].x>790)menu_dot[q].x=615;
		if(menu_dot[q].z<-1500)menu_dot[q].z=-1010;
		if(menu_dot[q].z>-1010)menu_dot[q].z=-1500;

		menu_dot[q].vx=(mousey-768/2)*plusmiinus*0.001f*cosf((mousey-768/2)*plusmiinus*0.1f)*menu_dot[q].vy;
		menu_dot[q].vz=(mousex-1024/2)*plusmiinus*0.001f*cosf((mousex-1024/2)*plusmiinus*0.1f)*menu_dot[q].vy;
		menu_dot[q].x=menu_dot[q].x+menu_dot[q].vx*elapsed*pelinopeus;
		menu_dot[q].z=menu_dot[q].z+menu_dot[q].vz*elapsed*pelinopeus;		
	}

	for (q=0; q<50; q++){
		particle[q].dead=false;
		particle[q].picture=1;
		particle[q].position.x=menu_dot[q].x;
		particle[q].position.y=0;
		particle[q].position.z=menu_dot[q].z;		
	}*/

	//particle animation
	/*if(options[8]){
		int aa[4];
		aa[0]=0;aa[1]=0;aa[2]=0;aa[3]=0;
		for (q=0; q<maximum_particles; q++){
			if(particle[q].dead)continue;
			//if(sqr(particle[q].position.x-ship[player_controlled_ship].x1)+sqr(particle[q].position.z-ship[player_controlled_ship].z1)>sqr(2000*(cameraheight*0.00022f)))continue;		
			particle_animation[particle[q].picture][aa[particle[q].picture]].position=particle[q].position;
			aa[particle[q].picture]++;		
		}

		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
		m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);
		m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE,  FALSE);
		m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);	
		m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
		m_pDevice->LightEnable(0, FALSE);
		m_pDevice->LightEnable(1, FALSE);
		m_pDevice->SetVertexShader( D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) );		
		m_pDevice->SetRenderState( D3DRS_POINTSIZE_MIN, FtoDW(point_size) );
		m_pDevice->SetRenderState( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
		m_pDevice->SetRenderState( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
		m_pDevice->SetRenderState( D3DRS_POINTSCALE_C,  FtoDW(1.00f) );	
		m_pDevice->SetRenderState( D3DRS_POINTSIZE,     FtoDW(point_size) );
		m_pDevice->SetMaterial( &mat[15] );
		m_pDevice->SetTexture( 0, tausta[15]);
		
		for (q=0; q<4; q++){
			if(aa[q]>0){		
				
				matriisi->LoadIdentity();				
				m_pDevice->SetTransform(D3DTS_WORLD, matriisi->GetTop());
				if(q==0){
					m_pDevice->SetMaterial( &mat[3] );
					m_pDevice->SetTexture( 0, tausta[3]);
				}
				if(q==1){
					m_pDevice->SetMaterial( &mat[40] );
					m_pDevice->SetTexture( 0, tausta[40]);
				}			
				m_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST  ,aa[q],particle_animation[q],sizeof(pvertex));
			}	
		}
		m_pDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,FALSE);
		m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
		
	}*/
	//return mouse position
	mousex=mousex*(float)SCREEN_WIDTH/1024.0f;
	mousey=mousey*(float)SCREEN_HEIGHT/768.0f;
	//m_pDevice->ShowCursor(FALSE);

}

void luesavet(void){
	int		i;
	char	name[256];
	FILE	*f;

	no_games_to_load=true;
	for (i=0 ; i<10 ; i++)
	{
		//strcpy (m_filenames[i], "--- Unused Slot ---");
		strcpy (m_filenames[i], " -Unused-");
		loadable[i] = false;
		sprintf (name, "save/s%i.sav", i);
		f = fopen (name, "r");
		if (!f)
			continue;
		stripped_fgets(name,sizeof(name),f);
		strcpy (m_filenames[i], name);
		loadable[i] = true;
		no_games_to_load=false;
		//stripped_fgets(name,sizeof(name),f);		
		//kirjaintan[i]=atoi(name);
		fclose (f);
	}
}

void new_game(void){//starts a new game

	int d,q;
	game_started=true;

	player_controlled_ship_in_map=-1;
	fuellowdirection=1;
	fuellowtimer=1;
	screenshot_timer=-1;
	dan_planet=8;
	money_offer_timer=-1;
	planet_visit_timer=0;
	//plot
	plot_started=false;
	selected_mission=-1;

	dialog.noreturn=false;
	pelivaihe=4;
	pelivaihe2=0;
	pelinopeus=1.0f;

	for(q=0;q<maximum_ships;q++){
		ZeroMemory(&ship[q],sizeof(shipbase));		
		ship[q].dead=true;		
		ship[q].onplanet=-1;
		ship[q].nearstar=-1;
		ship[q].nearstar2=-1;
	}
	for(q=0;q<100;q++){		
		ZeroMemory(&mission[q],sizeof(missions));		
		mission[q].dead=true;
		mission[q].planet=-1;
	}
	for(q=0;q<100;q++){
		end_mission[q]=false;
	}
	for(q=0;q<maximum_shipslot;q++){
		ZeroMemory(&shipslot[q],sizeof(encounter));
		shipslot[q].dead=true;			
		strcpy(shipslot[q].name,"No Name");
	}
	
	for (q=0; q<maximum_nebula; q++){
				nebula[q].x=randDouble(-2000,2000);
				nebula[q].y=randDouble(-20000,-5000);
				nebula[q].z=randDouble(-2000,2000);
				nebula[q].rx=randDouble(-pi,pi);
				nebula[q].ry=randDouble(-0.5f,0.5f)+pi/2;
				nebula[q].rz=randDouble(-pi,pi);
				nebula[q].vx=randDouble(-1,1);
				nebula[q].vy=randDouble(-1,1);
				nebula[q].vz=randDouble(-1,1);
				nebula[q].type=0;
				nebula[q].picture=randInt(0,10);
				nebula[q].size=randDouble(0.2f,3.0f);
				if(randInt(0,12)==0)nebula[q].size=randDouble(5.0f,10.0f);
				if(randInt(0,maximum_nebula)==0)nebula[q].size=randDouble(50.0f,100.0f);
				nebula[q].dead=false;
			}

	for (q=0; q<maksimiasteroid; q++){
		asteroid[q].dead=true;
	}
	for (q=0; q<maximumrocks; q++){
		rock[q].dead=true;
	}
	for (q=0; q<maksimisavuja; q++){
		savu[q].pois=true;
	}	
	
	//taustan galaksi
	galaxy_x=randDouble(-2000,2000);
	galaxy_z=randDouble(-2000,2000);
	galaxy_rx=randDouble(-0.5f,0.5f);
	galaxy_ry=randDouble(-0.5f,0.5f);
	galaxy_rz=randDouble(-0.5f,0.5f);
	int m_nArms=randInt(4,8);
	float fRadius=randDouble(150,300);
	float fArmAngle = (float)((360 / m_nArms)%360);
	float fAngularSpread = (float)(400/(m_nArms*2));
	for (q=0; q<2500; q++){
		//float fR = randDouble(0, fRadius);
		float fR = fHatRandom(fRadius);
		  //float fQ = randDouble(0, fAngularSpread ) * (rand()&1 ? 1 : -1);
		  float fQ = fHatRandom(fAngularSpread)* (rand()&1 ? 1 : -1);
		  float fK = 1;
		  float fA = (rand() % m_nArms) * fArmAngle;
		galaxy[q].position.x=(float)(fR * cos(( fA + fR * fK + fQ )/180*pi));
		galaxy[q].position.y=randDouble(-2000,0);
		galaxy[q].position.z=(float)(fR * sin(( fA + fR * fK + fQ )/180*pi));		
		//galaxy[q].u=stars[q].position.x/4000;
		//galaxy[q].v=stars[q].position.z/4000;
		galaxy[q].u=randDouble(0,1);
		galaxy[q].v=randDouble(0,1);
	}	

	//spacedust
	for (q=0; q<1500; q++){
		spacedust[q].position.x=randDouble(-1000,1000);
		spacedust[q].position.y=randDouble(-5000,1000);
		spacedust[q].position.z=randDouble(-1000,1000);
		spacedust[q].u=randDouble(0,1);
		spacedust[q].v=randDouble(0,1);
	}

	//particles
	for (q=0; q<maximum_particles; q++){
		particle[q].dead=true;
	}

	//bullets
	for (q=0; q<maximum_bullets; q++){
		bullet[q].dead=true;
	}

	for (q=0; q<maximumplanets; q++){
		planet[q].dead=true;		
		//prizes for goods
		planet[q].prize[0]=randInt(1,9);//0=slaves
		planet[q].prize[1]=randInt(1,7);//1=contraband goods
		planet[q].prize[2]=randInt(1,11);//2=illegal weapons
		planet[q].prize[4]=randInt(2,5);//4=fuel
	}

	d=0;
	shipslot[d].cargo[0]=4;
	shipslot[d].cargo[1]=4;
	shipslot[d].cargo[2]=4;
	shipslot[d].cargo[3]=100;
	shipslot[d].cargo[4]=50;	
	shipslot[d].dead=false;
	
	d=1;
	shipslot[d].ship_basea=ship_base[2];
	shipslot[d].cargo[0]=0;
	shipslot[d].cargo[1]=0;
	shipslot[d].cargo[2]=0;
	shipslot[d].cargo[3]=0;
	shipslot[d].cargo[4]=0;
	shipslot[d].energy=shipslot[d].ship_basea.base_energy;
	strcpy(shipslot[d].name,"Wolf IV");
	shipslot[d].dead=false;	

	ship[0].encounter.ship_basea=ship_base[2];

	

	
	//merkurius
		q=0;
		planet[q].radiustohost=58;
		planet[q].rx=0.1f/180*pi;
		planet[q].ellipce=1.205f;
		planet[q].speed=1/87.9f;
		planet[q].rotatespeed=1/58.7f;
		planet[q].mass=0.05f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=10;
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=4.80f/12.76f;
		planet[q].type=0;
		planet[q].population=1;
		planet[q].military=3;
		planet[q].wealth=8;
		strcpy(planet[q].name,"Mercury");
		strcpy(planet[q].location,"first planet");

	//venus
		q=1;		
		planet[q].radiustohost=108;
		planet[q].rx=177.4f/180*pi;
		planet[q].ellipce=1.006f;
		planet[q].speed=1/224.7f;
		planet[q].rotatespeed=1/243.0f;
		planet[q].mass=0.81f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=11;
		planet[q].shadow=0;
		planet[q].atmosphere=8;
		planet[q].size=11.25f/12.76f;
		planet[q].type=0;
		planet[q].population=12;
		planet[q].military=3;
		planet[q].wealth=5;
		strcpy(planet[q].name,"Venus");
		strcpy(planet[q].location,"second planet");

	//maa
		q=2;		
		planet[q].radiustohost=150;
		planet[q].rx=23.5f/180*pi;
		planet[q].ellipce=1.016f;
		planet[q].speed=1/365.2f;
		planet[q].rotatespeed=1/1;
		planet[q].mass=1.0f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=7;
		planet[q].shadow=0;
		planet[q].atmosphere=8;
		planet[q].size=12.76f/12.76f;
		planet[q].type=0;
		planet[q].population=20;
		planet[q].military=3;
		planet[q].wealth=10;
		strcpy(planet[q].name,"Earth");
		strcpy(planet[q].location,"third planet");

	//mars
		q=3;		
		planet[q].radiustohost=228;
		planet[q].rx=25.19f/180*pi;
		planet[q].ellipce=1.093f;
		planet[q].speed=1/686.9f;
		planet[q].rotatespeed=1/1.1f;
		planet[q].mass=0.10f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=12;
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=6.79f/12.76f;
		planet[q].type=0;		
		planet[q].population=6;
		planet[q].military=2;
		planet[q].wealth=6;
		strcpy(planet[q].name,"Mars");
		strcpy(planet[q].location,"fourth planet");

	//jupiter
		q=4;		
		planet[q].radiustohost=350;//778
		planet[q].rx=3.12f/180*pi;
		planet[q].ellipce=1.048f;
		planet[q].speed=1/4307.0f;
		planet[q].rotatespeed=1/0.48f;
		planet[q].mass=51.89f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=13;
		planet[q].shadow=0;
		planet[q].atmosphere=18;
		planet[q].size=142.8f/12.76f;
		planet[q].type=0;
		planet[q].population=0;
		planet[q].military=0;
		planet[q].wealth=0;
		strcpy(planet[q].name,"Jupiter");
		strcpy(planet[q].location,"fifth planet");

	//saturnus
		q=5;		
		planet[q].radiustohost=450;//1427
		planet[q].rx=26.73f/180*pi;
		planet[q].ellipce=1.055f;
		planet[q].speed=1/10731.0f;
		planet[q].rotatespeed=1/0.425f;
		planet[q].mass=35.14f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=14;
		planet[q].shadow=0;
		planet[q].atmosphere=19;
		planet[q].size=119.3f/12.76f;
		planet[q].type=0;
		planet[q].population=0;
		planet[q].military=0;
		planet[q].wealth=0;
		strcpy(planet[q].name,"Saturn");
		strcpy(planet[q].location,"sixth planet");

	//uranus
		q=6;		
		planet[q].radiustohost=550;//2869
		planet[q].rx=97.86f/180*pi;
		planet[q].ellipce=1.047f;
		planet[q].speed=1/30660.0f;
		planet[q].rotatespeed=1/0.455f;
		planet[q].mass=14.52f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=15;
		planet[q].shadow=0;
		planet[q].atmosphere=20;
		planet[q].size=47.0f/12.76f;
		planet[q].type=0;
		planet[q].population=0;
		planet[q].military=0;
		planet[q].wealth=0;
		strcpy(planet[q].name,"Uranus");
		strcpy(planet[q].location,"seventh planet");

	//neptunus
		q=7;		
		planet[q].radiustohost=650;//4497
		planet[q].rx=29.56f/180*pi;
		planet[q].ellipce=1.008f;
		planet[q].speed=1/60000.0f;
		planet[q].rotatespeed=1/0.66f;
		planet[q].mass=17.25f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=16;
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=48.2f/12.76f;
		planet[q].type=0;
		planet[q].population=0;
		planet[q].military=0;
		planet[q].wealth=0;
		strcpy(planet[q].name,"Neptune");
		strcpy(planet[q].location,"eighth planet");

	//pluto
		q=8;		
		planet[q].radiustohost=750;//5899
		planet[q].rx=119.6f/180*pi;
		planet[q].ellipce=1.250f;
		planet[q].speed=1/90000.0f;
		planet[q].rotatespeed=1/6.3f;
		planet[q].mass=0.1f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=17;
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=5.9f/12.76f;
		planet[q].type=0;		
		planet[q].population=2;
		planet[q].military=1;
		planet[q].wealth=8;
		strcpy(planet[q].name,"Pluto");
		strcpy(planet[q].location,"ninth planet");

	//maan kuu
	for (q=9; q<10; q++){
		planet[q].radiustohost=8;
		planet[q].rx=23.5f/180*pi;
		planet[q].ellipce=1.016f;
		planet[q].speed=1/31.0f;
		planet[q].rotatespeed=1/31;
		planet[q].mass=0.1f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=2;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=21;
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=4.064f/12.76f;
		planet[q].type=1;
		planet[q].population=randInt(3,7);
		planet[q].military=randInt(1,3);
		planet[q].wealth=randInt(3,4);
		strcpy(planet[q].name,"Moon");
		strcpy(planet[q].location,"Earth´s moon");
	}

	//marsin kuut
	for (q=10; q<12; q++){
		planet[q].radiustohost=8+(float)(q-10)*4;
		planet[q].rx=23.5f/180*pi;
		planet[q].ellipce=1.016f;
		planet[q].speed=1/randDouble(25,100);
		planet[q].rotatespeed=1/randDouble(10.8f,18);
		planet[q].mass=0.1f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=3;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=22;
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=4.064f/12.76f;
		planet[q].type=1;
		planet[q].population=randInt(2,6);
		planet[q].military=randInt(1,3);
		planet[q].wealth=randInt(2,7);
		strcpy(planet[q].location,"Mars´ moon");
	}
	q=10;strcpy(planet[q].name,"Phobos");
	q=11;strcpy(planet[q].name,"Deimos");

	//jupiterin kuut
	for (q=12; q<27; q++){
		planet[q].radiustohost=70+(float)(q-12)*3;
		planet[q].rx=23.5f/180*pi;
		planet[q].ellipce=1.016f;
		planet[q].speed=1/randDouble(100,250);
		planet[q].rotatespeed=1/randDouble(30.8f,88);
		planet[q].mass=0.1f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=4;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=randInt(21,24);
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=4.064f/12.76f;
		planet[q].type=1;
		planet[q].population=randInt(3,7);
		planet[q].military=randInt(1,3);
		planet[q].wealth=randInt(3,8);		
		strcpy(planet[q].location,"Jupiter´s moon");
	}
	q=12;strcpy(planet[q].name,"Metis");
	q=13;strcpy(planet[q].name,"Adrastea");
	q=14;strcpy(planet[q].name,"Amalthea");
	q=15;strcpy(planet[q].name,"Thebe");
	q=16;strcpy(planet[q].name,"Io");
	q=17;strcpy(planet[q].name,"Europa");
	q=18;strcpy(planet[q].name,"Ganymedes");
	q=19;strcpy(planet[q].name,"Kallisto");
	q=20;strcpy(planet[q].name,"Leda");
	q=21;strcpy(planet[q].name,"Himalia");
	q=22;strcpy(planet[q].name,"Lysithea");
	q=23;strcpy(planet[q].name,"Ananke");
	q=24;strcpy(planet[q].name,"Charme");
	q=25;strcpy(planet[q].name,"Pasiphae");
	q=26;strcpy(planet[q].name,"Sinope ");

	//saturnuksen kuut
	for (q=27; q<44; q++){
		planet[q].radiustohost=70+(float)(q-27)*3;
		planet[q].rx=23.5f/180*pi;
		planet[q].ellipce=1.016f;
		planet[q].speed=1/randDouble(100,200);
		planet[q].rotatespeed=1/randDouble(30.8f,98);
		planet[q].mass=0.1f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=5;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=randInt(21,24);
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=4.064f/12.76f;
		planet[q].type=1;
		planet[q].population=randInt(3,7);
		planet[q].military=randInt(1,3);
		planet[q].wealth=randInt(3,8);
		strcpy(planet[q].location,"Saturn´s moon");
	}
	q=27;strcpy(planet[q].name,"Atlas");
	q=28;strcpy(planet[q].name,"Prometheus");
	q=29;strcpy(planet[q].name,"Pandora");
	q=30;strcpy(planet[q].name,"Epimetheus");
	q=31;strcpy(planet[q].name,"Janus");
	q=32;strcpy(planet[q].name,"Mimas");
	q=33;strcpy(planet[q].name,"Enceladus");
	q=34;strcpy(planet[q].name,"Telesto");
	q=35;strcpy(planet[q].name,"Tethys");
	q=36;strcpy(planet[q].name,"Calypso");
	q=37;strcpy(planet[q].name,"Dione");
	q=38;strcpy(planet[q].name,"Helene");
	q=39;strcpy(planet[q].name,"Rhea");
	q=40;strcpy(planet[q].name,"Titan");
	q=41;strcpy(planet[q].name,"Hyperion");
	q=42;strcpy(planet[q].name,"Japetus");
	q=43;strcpy(planet[q].name,"Phoebe");

	//uranuksen kuut
	for (q=44; q<59; q++){
		planet[q].radiustohost=30+(float)(q-44)*3;
		planet[q].rx=23.5f/180*pi;
		planet[q].ellipce=1.016f;
		planet[q].speed=1/randDouble(80,160);
		planet[q].rotatespeed=1/randDouble(30.8f,98);
		planet[q].mass=0.1f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=6;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=randInt(21,24);
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=4.064f/12.76f;
		planet[q].type=1;
		planet[q].population=randInt(3,7);
		planet[q].military=randInt(1,3);
		planet[q].wealth=randInt(3,8);
		strcpy(planet[q].location,"Uranus´ moon");
	}
	q=44;strcpy(planet[q].name,"Cordelia");
	q=45;strcpy(planet[q].name,"Ophelia");
	q=46;strcpy(planet[q].name,"Bianca");
	q=47;strcpy(planet[q].name,"Cressida");
	q=48;strcpy(planet[q].name,"Desdemona");
	q=49;strcpy(planet[q].name,"Juliet");
	q=50;strcpy(planet[q].name,"Portia");
	q=51;strcpy(planet[q].name,"Rosalind");
	q=52;strcpy(planet[q].name,"Belinda");
	q=53;strcpy(planet[q].name,"Puck");
	q=54;strcpy(planet[q].name,"Miranda");
	q=55;strcpy(planet[q].name,"Ariel");
	q=56;strcpy(planet[q].name,"Umbriel");
	q=57;strcpy(planet[q].name,"Titania");
	q=58;strcpy(planet[q].name,"Oberon");

	//neptunuksen kuut
	for (q=59; q<67; q++){
		planet[q].radiustohost=30+(float)(q-59)*3;
		planet[q].rx=23.5f/180*pi;
		planet[q].ellipce=1.016f;
		planet[q].speed=1/randDouble(60,160);
		planet[q].rotatespeed=1/randDouble(30.8f,78);
		planet[q].mass=0.1f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=7;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=randInt(21,24);
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=4.064f/12.76f;
		planet[q].type=1;
		planet[q].population=randInt(3,7);
		planet[q].military=randInt(1,3);
		planet[q].wealth=randInt(3,8);
		strcpy(planet[q].location,"Neptune´s moon");
	}
	q=59;strcpy(planet[q].name,"Naiad");
	q=60;strcpy(planet[q].name,"Thalassa");
	q=61;strcpy(planet[q].name,"Despina");
	q=62;strcpy(planet[q].name,"Galatea");
	q=63;strcpy(planet[q].name,"Larissa");
	q=64;strcpy(planet[q].name,"Proteus");
	q=65;strcpy(planet[q].name,"Triton");
	q=66;strcpy(planet[q].name,"Nereid");

	//pluton kuut
	for (q=67; q<68; q++){
		planet[q].radiustohost=7.0f+(float)(q-67)*4;
		planet[q].rx=23.5f/180*pi;
		planet[q].ellipce=1.016f;
		planet[q].speed=1/randDouble(25,100);
		planet[q].rotatespeed=1/randDouble(10.8f,18);
		planet[q].mass=0.1f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=8;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=randInt(21,24);
		planet[q].shadow=0;
		planet[q].atmosphere=-1;
		planet[q].size=4.064f/12.76f;
		planet[q].type=1;
		planet[q].population=randInt(3,7);
		planet[q].military=randInt(1,3);
		planet[q].wealth=randInt(3,8);
		strcpy(planet[q].name,"Kharon");
		strcpy(planet[q].location,"Pluto´s moon");
	}

	//asteroidivyöhyke
	for (q=69; q<89; q++){
		planet[q].radiustohost=280+(float)(q-69)*2;
		planet[q].rx=randDouble(0,180)/180*pi;
		planet[q].ellipce=1.093f;
		planet[q].speed=1/randDouble(600,650);
		planet[q].rotatespeed=1/randDouble(1.8f,18);
		planet[q].mass=0.05f;
		planet[q].angletohost=randDouble(-pi,pi);
		planet[q].host=-1;
		planet[q].ry=randDouble(-pi,pi);
		planet[q].rz=0;
		planet[q].x=0;
		planet[q].y=0;
		planet[q].z=0;
		planet[q].dead=false;
		planet[q].picture=randInt(25,27);
		planet[q].shadow=-1;
		planet[q].atmosphere=-1;
		planet[q].size=4.064f/12.76f;
		planet[q].type=2;
		planet[q].population=randInt(1,2);
		planet[q].military=randInt(1,3);
		planet[q].wealth=randInt(5,10);
		strcpy(planet[q].name,"Asteroid ");
		itoa(q-69+1,temprivi,10);
		strcat(planet[q].name,temprivi);
		strcpy(planet[q].location,"in the asteroid field between Mars and Jupiter");
	}

	//asteroidivyöhykkeen murikat
	for (q=0; q<2000; q++){
		rock[q].radiustohost=280+randDouble(-10,50);
		rock[q].rx=randDouble(0,180)/180*pi;
		rock[q].ellipce=1.093f;
		rock[q].speed=1/randDouble(600,650);
		rock[q].rotatespeed=1/randDouble(1.8f,18);
		rock[q].mass=1000.0f;
		rock[q].angletohost=randDouble(-pi,pi);
		rock[q].host=-1;
		rock[q].ry=randDouble(-pi,pi);
		rock[q].rz=0;
		rock[q].y=0;
		rock[q].x=sinf(rock[q].angletohost)*70*rock[q].radiustohost/rock[q].ellipce;
		rock[q].z=cosf(rock[q].angletohost)*70*rock[q].radiustohost;				
		rock[q].dead=false;
		rock[q].picture=randInt(25,27);
		rock[q].shadow=-1;
		rock[q].atmosphere=-1;
		rock[q].size=randDouble(1,10);
		rock[q].type=2;
		rock[q].distancesquare=(sqr(rock[q].x-ship[0].x1)+sqr(rock[q].z-ship[0].z1));
		strcpy(rock[q].name,"Rock number ");
		itoa(q+1,temprivi,10);
		strcat(rock[q].name,temprivi);
	}

	//satunnaiset murikat auringon ympärillä
	for (q=2000; q<maximumrocks; q++){
		rock[q].rx=randDouble(0,180)/180*pi;
		rock[q].ellipce=randDouble(0.8f,1.2f);
		rock[q].speed=1/randDouble(100,1000);
		rock[q].rotatespeed=1/randDouble(0.01f,6);
		rock[q].mass=1.0f;
		rock[q].angletohost=randDouble(-pi,pi);
		rock[q].host=-1;		
		rock[q].radiustohost=randDouble(100,2000);
		rock[q].ry=randDouble(-pi,pi);
		rock[q].rz=0;
		rock[q].y=0;
		rock[q].x=sinf(rock[q].angletohost)*70*rock[q].radiustohost/rock[q].ellipce;
		rock[q].z=cosf(rock[q].angletohost)*70*rock[q].radiustohost;				
		rock[q].dead=false;
		rock[q].picture=randInt(25,27);
		rock[q].shadow=-1;
		rock[q].atmosphere=-1;
		rock[q].size=randDouble(1,10);
		rock[q].type=2;
		rock[q].distancesquare=(sqr(rock[q].x-ship[0].x1)+sqr(rock[q].z-ship[0].z1));
		strcpy(rock[q].name,"Rock number ");
		itoa(q+1-2000,temprivi,10);
		strcat(rock[q].name,temprivi);
	}

	//planets fly
	for (q=0; q<maximumplanets; q++){
			if(planet[q].dead)continue;				
			fly_planet(&planet[q]);
	}
	
	d=0;
	ship[d].motordown=0;
	ship[d].motorleft=0;
	ship[d].motorright=0;
	ship[d].motorup=0;
	ship[d].rx=pi*0.75f;
	ship[d].ry=0;
	ship[d].rz=0;
	ship[d].x1=planet[8].x+250;//pluto
	ship[d].y1=0;
	ship[d].z1=planet[8].z+250;	
	ship[d].x2=0;                                                                                     	
	ship[d].y2=0;
	ship[d].z2=0;	
	ship[d].vx=0;
	ship[d].vz=0;
	ship[d].guntime[0]=0;
	ship[d].guntime[1]=0;
	ship[d].guntime[2]=0;
	ship[d].guntime[3]=0;
	ship[d].dead=false;
	ship[d].number=d;
	ship[d].energy=100;
	ship[d].side=0;
	//ship[d].encounter.ship_basea=ship_base[3];
	ship[d].nearstar2=-1;
	ship[d].nearstar=-1;

	//init space rocks
	for (q=0; q<maximumrocks; q++){
			if(rock[q].dead)continue;
				rock[q].distancesquare=(sqr(rock[q].x-ship[0].x1)+sqr(rock[q].z-ship[0].z1));				
	}





}

HRESULT SwapSourceFilter(int song_number)
{
    HRESULT hr = S_OK;
    IPin *pPin = NULL;
    CHAR szFilename[MAX_PATH];	
    WCHAR wFileName[MAX_PATH];
	
	music_playing=song_number;

	strcpy(szFilename,"sound/music");
	itoa(song_number,temprivi,10);				
	strcat(szFilename,temprivi);
	strcat(szFilename,".mp3");
	//_tcscpy( szFilename,"sound/music0.mp3");

    // Make sure that this file exists
    DWORD dwAttr = GetFileAttributes(szFilename);
    if (dwAttr == (DWORD) -1)
        return ERROR_FILE_NOT_FOUND;

    #ifndef UNICODE
        MultiByteToWideChar(CP_ACP, 0, szFilename, -1, wFileName, MAX_PATH);
    #else
        lstrcpy(wFileName, szFilename);
    #endif

    // OPTIMIZATION OPPORTUNITY
	// This will open the file, which is expensive. To optimize, this
    // should be done earlier, ideally as soon as we knew this was the
    // next file to ensure that the file load doesn't add to the
    // filter swapping time & cause a hiccup.
    //
    // Add the new source filter to the graph. (Graph can still be running)
    hr = g_pGraphBuilder->AddSourceFilter(wFileName, wFileName, &g_pSourceNext);

    // Get the first output pin of the new source filter. Audio sources 
    // typically have only one output pin, so for most audio cases finding 
    // any output pin is sufficient.
    if (SUCCEEDED(hr)) {
        hr = g_pSourceNext->FindPin(L"Output", &pPin);  
    }

    // Stop the graph
    if (SUCCEEDED(hr)) {
        hr = g_pMediaControl->Stop();
    }

    // Break all connections on the filters. You can do this by adding 
    // and removing each filter in the graph
    if (SUCCEEDED(hr)) {
        IEnumFilters *pFilterEnum = NULL;
        IBaseFilter  *pFilterTemp = NULL;

        if (SUCCEEDED(hr = g_pGraphBuilder->EnumFilters(&pFilterEnum))) {
            int iFiltCount = 0;
            int iPos = 0;

            // Need to know how many filters. If we add/remove filters during the
            // enumeration we'll invalidate the enumerator
            while (S_OK == pFilterEnum->Skip(1)) {
                iFiltCount++;
            }

            // Allocate space, then pull out all of the 
            IBaseFilter **ppFilters = reinterpret_cast<IBaseFilter **>
                                      (_alloca(sizeof(IBaseFilter *) * iFiltCount));
            pFilterEnum->Reset();

            while (S_OK == pFilterEnum->Next(1, &(ppFilters[iPos++]), NULL));
            RELEASE(pFilterEnum);

            for (iPos = 0; iPos < iFiltCount; iPos++) {
                g_pGraphBuilder->RemoveFilter(ppFilters[iPos]);
				// Put the filter back, unless it is the old source
				if (ppFilters[iPos] != g_pSourceCurrent) {
					g_pGraphBuilder->AddFilter(ppFilters[iPos], NULL);
                }
				RELEASE(ppFilters[iPos]);
            }
        }
    }

    // We have the new ouput pin. Render it
    if (SUCCEEDED(hr)) {
        hr = g_pGraphBuilder->Render(pPin);
        g_pSourceCurrent = g_pSourceNext;
        g_pSourceNext = NULL;
    }

    RELEASE(pPin);
    RELEASE(g_pSourceNext); // In case of errors

    // Re-seek the graph to the beginning
    if (SUCCEEDED(hr)) {
        LONGLONG llPos = 0;
        hr = g_pMediaSeeking->SetPositions(&llPos, AM_SEEKING_AbsolutePositioning,
                                           &llPos, AM_SEEKING_NoPositioning);
    } 

    // Start the graph
    if (SUCCEEDED(hr)) {
        hr = g_pMediaControl->Run();
    }

    // Release the old source filter.
    RELEASE(g_pSourceCurrent);
    return S_OK;   
}

HRESULT GraphInit(void)
{
    HRESULT hr;
    // Initialize COM
    if (FAILED (hr = CoInitialize(NULL)) )
        return hr;

    // Create DirectShow Graph
    if (FAILED (hr = CoCreateInstance(CLSID_FilterGraph, NULL,
                                      CLSCTX_INPROC, IID_IGraphBuilder,
                                      reinterpret_cast<void **>(&g_pGraphBuilder))) )
        return hr;

    // Get the IMediaControl Interface
    if (FAILED (hr = g_pGraphBuilder->QueryInterface(IID_IMediaControl,
                                 reinterpret_cast<void **>(&g_pMediaControl))))
        return hr;

    // Get the IMediaControl Interface
    if (FAILED (hr = g_pGraphBuilder->QueryInterface(IID_IMediaSeeking,
                                 reinterpret_cast<void **>(&g_pMediaSeeking))))
        return hr;

    // Create the intial graph
    if (FAILED (hr = SwapSourceFilter(0)))
        return hr;

	// Set the owner window to receive event notices.
    if (FAILED (hr = g_pGraphBuilder->QueryInterface(IID_IMediaEventEx, reinterpret_cast<void **>(&pEvent))))
		return hr;
    if (FAILED (hr = pEvent->SetNotifyWindow(reinterpret_cast<OAHWND>(hWnd), WM_GRAPHNOTIFY, 0)))
		return hr;

		



    return S_OK;
}


HRESULT HandleGraphEvent(void)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

    while(SUCCEEDED(pEvent->GetEvent(&evCode, &evParam1, &evParam2, 0)))
    {
        // Spin through the events
        hr = pEvent->FreeEventParams(evCode, evParam1, evParam2);

        if(EC_COMPLETE == evCode)
        {     
			int music_number=randInt(0,2);
			while(music_number==music_playing)music_number=randInt(0,2);
			hr = SwapSourceFilter(music_number);
		
		/*   
                LONGLONG pos=0;

                // Reset to first frame of movie
                hr = g_pMediaSeeking->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                       NULL, AM_SEEKING_NoPositioning);
                if (FAILED(hr))
                {
                    // Some custom filters (like the Windows CE MIDI filter) 
                    // may not implement seeking interfaces (IMediaSeeking)
                    // to allow seeking to the start.  In that case, just stop 
                    // and restart for the same effect.  This should not be
                    // necessary in most cases.
                    g_pMediaControl->Stop();
                    g_pMediaControl->Run();
                }            
            */
        }
    }
    return hr;
}
void playsound(int number,float volume,float soundx,float soundz,float listenerx,float listenerz){//plays a sound
	if(!options[5])return;
	if(!sound_initialized)return;

	float distance=sqrtf(sqr(soundx-listenerx)+sqr(soundz-listenerz));
	volume=(10000-distance)/10000-(1-volume);
	if(volume<0)volume=0;
	if(volume>1)volume=1;

	g_pSound[number]->Play( 0, NULL,volume*master_volume);
}
void render_start_demo(void){


	//start_timer=mousex*10;
	float color;
	float xa;
	color=1;
	if(start_timer>=1000)
	color=1-(start_timer-1000)/3000;
	if(color<0)color=0;
	
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(color,color,color,1), 0, 0 );

	start_timer=start_timer+elapsed*pelinopeus*2.0f;
	//start_timer=plusmiinus*1000;
	
	//camera
	D3DXMatrixPerspectiveFovLH( &matProj,  (float)((60)*pi/180), aspect, 25.0f, maxvisible);			
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

		kamerax1=0;
		kameray1=1000;
		kameraz1=0;
		kamerax2=kamerax1-1;
		kameray2=0;
		kameraz2=kameraz1;
		D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(kamerax1,kameray1,kameraz1),	&D3DXVECTOR3(kamerax2,kameray2,kameraz2), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	
		m_pDevice->SetTransform( D3DTS_VIEW, &matView );

		m_pDevice->LightEnable(0, FALSE);
		m_pDevice->LightEnable(1, FALSE);

	//draw the picture
			m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
			m_pDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);

			m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE);

		//sword
		for (int q=0; q<9; q++){
			matriisi->LoadIdentity();
			if(start_timer<6000){
				xa=(start_timer-q*q*3)-1000;			
				if(xa>0)xa=0;
			}
			else xa=(sqr(start_timer-q*q*3-6000)*0.0008f);
			float za=(start_timer-q*q*3)-1000;
			float ra=(start_timer-q*q*3)*((2*pi)/1000);
			float transparency=1-sqrtf(q)/3;
			if(za>0)za=0;
			if(ra>2*pi)ra=2*pi;
			matriisi->TranslateLocal(za,0,xa);			
			matriisi->RotateYawPitchRollLocal(-pi/2+ra,pi/2,0);			
			matriisi->ScaleLocal(17,17.0f*(156.0f/900.0f),17);
	

			mallit[1].malli[1].sisus[0].textuuri2=71;
			mallit[1].malli[1].sisus[0].textuuri=71;
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO    );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_INVSRCCOLOR);			
			draw(transparency,transparency,transparency,&mallit[1].malli[1]);
			
			mallit[1].malli[1].sisus[0].textuuri2=70;
			mallit[1].malli[1].sisus[0].textuuri=70;
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );		
			draw(transparency,transparency,transparency,&mallit[1].malli[1]);
		}
		//Stars-logo
		if(start_timer>6000)
		for (int q=0; q<1; q++){
			matriisi->LoadIdentity();
			
			xa=(sqr(start_timer-6000)*0.0008f-1000);
			if(xa>0)xa=0;
			float transparency=1;
			if(start_timer>10000)transparency=1-(start_timer-10000)/2000;
			matriisi->TranslateLocal(0,0,xa);			
			matriisi->RotateYawPitchRollLocal(-pi/2,pi/2,0);			
			matriisi->ScaleLocal(3*4,3,3);	
			
			mallit[1].malli[1].sisus[0].textuuri2=72;
			mallit[1].malli[1].sisus[0].textuuri=72;
			m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE );
			m_pDevice->SetRenderState(D3DRS_DESTBLEND,	D3DBLEND_ONE );		
			draw(transparency,transparency,transparency,&mallit[1].malli[1]);
		}

		float trans=start_timer/2000;
		if(trans>1)trans=1;
		xa=0;
		if(start_timer>6000)xa=(sqr(start_timer-6000)*0.0008f);
		kirjota(1,trans,trans,trans,504+xa,358,0,"Ville Mönkkönen presents:");



		if(start_timer>12000){
			pelivaihe=7;
			pelivaihe2=5;
		}
}
void sound_init(void){
	int q;

		// Create a static IDirectSound in the CSound class. 
		HRESULT hr;
		sound_initialized=true;
		if( FAILED( hr = g_pSoundManager->Initialize( hWnd, DSSCL_PRIORITY, 2, 44100, 16 ) ) )
		{
			sound_initialized=false; 
		}


		//how many simultaneous samples
		int sound_numbers[20];
		for (q=0; q<number_of_samples; q++)sound_numbers[q]=2;
		sound_numbers[0]=1;
		sound_numbers[1]=8;
		sound_numbers[2]=4;
		sound_numbers[3]=10;
		sound_numbers[4]=4;
		sound_numbers[5]=4;
		sound_numbers[6]=4;
		sound_numbers[7]=4;
		sound_numbers[8]=4;
		sound_numbers[9]=4;
		sound_numbers[10]=4;
		sound_numbers[11]=4;

		//load
		if(sound_initialized){
			char filename[256];
			for (q=0; q<number_of_samples; q++){
				itoa(q,temprivi,10);
				strcpy(filename,"sound/sound");
				strcat(filename,temprivi);
				strcat(filename,".wav");			
				//ZeroMemory(&g_pSound[q], sizeof(CSound));
				if( FAILED( hr = g_pSoundManager->Create( &g_pSound[q], filename, DSBCAPS_CTRLVOLUME, GUID_NULL,sound_numbers[q] ) ) )sound_initialized=false; 	
			}
		}
}

void clean_display(void){
	poistaobj(mallit[0].malli,	objnum0	);
	poistaobj(mallit[1].malli,	objnum1	);
	poistaobj(mallit[2].malli,	objnum2	);
	
	//SAFE_DELETE_ARRAY(tausta);
	for (int q=0; q<materiaa; q++)
		SAFE_RELEASE(tausta[q]);
	SAFE_DELETE_ARRAY(kuvia);
	SAFE_DELETE_ARRAY(mat);
	//RELEASE(m_pDevice);
	//RELEASE(m_pD3D);
}

void restore_display(void){
	int q;
	m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);	
	m_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);//D3DCULL_CCW
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	//ensin linear filter
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFLINEAR)
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTEXF_LINEAR);	
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MINFLINEAR)
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTEXF_LINEAR);			
	//sitten anistropic filter
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFANISOTROPIC)		
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTEXF_ANISOTROPIC);	
	if(deviceCaps.TextureFilterCaps&D3DPTFILTERCAPS_MINFANISOTROPIC)
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTEXF_ANISOTROPIC);		
	//point size
	point_size=1;
	if(deviceCaps.MaxPointSize>1)		
		point_size=4;
	m_pDevice->SetTextureStageState(0,D3DTSS_MAXANISOTROPY,2);
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSU,D3DTADDRESS_MIRROR ); 
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSV,D3DTADDRESS_MIRROR ); 
	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESSW,D3DTADDRESS_MIRROR );	
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	
	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, 
                                   D3DTTFF_COUNT2 //| D3DTTFF_PROJECTED 
								   );	
	m_pDevice->SetRenderState( D3DRS_LIGHTING,TRUE);
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00FFFFFF, 0, 0 );		
	m_pDevice->Present(NULL,NULL,NULL,NULL);
	//ladataan tekstuurit
	lataatext();
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00FFFFFF, 0, 0 );	
	kirjota(1,-1,-1,-1,10,10,0,"Restoring Device...");
	m_pDevice->Present(NULL,NULL,NULL,NULL);
	/*//alustetaan matriisi	
	ZeroMemory(&matriisi, sizeof(matriisi));
	D3DXCreateMatrixStack(  0, &matriisi);
	valota(0,0,0);*/	
	luekuvat();

	// Initialize and set the matrices
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
								  &D3DXVECTOR3( 0.0f, 0.0f, 1.0f ),
								  &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	D3DXMatrixPerspectiveFovLH( &matProj, pi/4, aspect, 1.0f, 100.0f );
	
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	m_pDevice->SetTransform( D3DTS_VIEW, &matView );		
	
	mallit[0].malli= new obj[objnum0];	
	mallit[1].malli= new obj[objnum1];
	mallit[2].malli= new obj[objnum2];
	lataa("models/obj1.3dw",	mallit[0].malli,	false,	false);
	lataa("models/obj2.3dw",	mallit[1].malli,	false,	false);
	lataa("models/ships.3dw",	mallit[2].malli,	false,	false);	

	
	m_LastTime = GetTickCount()-5;
	elapsed=5;
	for (q=0; q<100; q++){
		elapsed3[q]=5;
	}

	SetWindowLong( hWnd, GWL_STYLE, WS_MAXIMIZE|WS_VISIBLE|WS_POPUP );
	ShowCursor(false);	
	SetCursor(NULL);
	m_pDevice->ShowCursor(FALSE);
	cursor_shown=false;
	D3DUtil_SetDeviceCursor(m_pDevice,mouse_cursor);
	mouse_button_0=false;
	


}

//-----------------------------------------------------------------------------
// Name: D3DUtil_SetDeviceCursor
// Desc: Gives the D3D device a cursor with image and hotspot from hCursor.
//-----------------------------------------------------------------------------
HRESULT D3DUtil_SetDeviceCursor( LPDIRECT3DDEVICE8 pd3dDevice, HCURSOR hCursor )
{
    HRESULT hr = E_FAIL;
    ICONINFO iconinfo;
    BOOL bBWCursor;
    LPDIRECT3DSURFACE8 pCursorBitmap = NULL;
    HDC hdcColor = NULL;
    HDC hdcMask = NULL;
    HDC hdcScreen = NULL;
    BITMAP bm;
    DWORD dwWidth;
    DWORD dwHeightSrc;
    DWORD dwHeightDest;
    COLORREF crColor;
    COLORREF crMask;
    UINT x;
    UINT y;
    BITMAPINFO bmi;
    COLORREF* pcrArrayColor = NULL;
    COLORREF* pcrArrayMask = NULL;
    DWORD* pBitmap;
    HGDIOBJ hgdiobjOld;

    ZeroMemory( &iconinfo, sizeof(iconinfo) );
    if( !GetIconInfo( hCursor, &iconinfo ) )
        goto End;

    if (0 == GetObject((HGDIOBJ)iconinfo.hbmMask, sizeof(BITMAP), (LPVOID)&bm))
        goto End;
    dwWidth = bm.bmWidth;
    dwHeightSrc = bm.bmHeight;

    if( iconinfo.hbmColor == NULL )
    {
        bBWCursor = TRUE;
        dwHeightDest = dwHeightSrc / 2;
    }
    else 
    {
        bBWCursor = FALSE;
        dwHeightDest = dwHeightSrc;
    }

    // Create a surface for the fullscreen cursor
    if( FAILED( hr = pd3dDevice->CreateImageSurface( dwWidth, dwHeightDest, 
        D3DFMT_A8R8G8B8, &pCursorBitmap ) ) )
    {
        goto End;
    }

    pcrArrayMask = new DWORD[dwWidth * dwHeightSrc];

    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = dwWidth;
    bmi.bmiHeader.biHeight = dwHeightSrc;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    hdcScreen = GetDC( NULL );
    hdcMask = CreateCompatibleDC( hdcScreen );
    if( hdcMask == NULL )
    {
        hr = E_FAIL;
        goto End;
    }
    hgdiobjOld = SelectObject(hdcMask, iconinfo.hbmMask);
    GetDIBits(hdcMask, iconinfo.hbmMask, 0, dwHeightSrc, 
        pcrArrayMask, &bmi, DIB_RGB_COLORS);
    SelectObject(hdcMask, hgdiobjOld);

    if (!bBWCursor)
    {
        pcrArrayColor = new DWORD[dwWidth * dwHeightDest];
        hdcColor = CreateCompatibleDC( GetDC( NULL ) );
        if( hdcColor == NULL )
        {
            hr = E_FAIL;
            goto End;
        }
        SelectObject(hdcColor, iconinfo.hbmColor);
        GetDIBits(hdcColor, iconinfo.hbmColor, 0, dwHeightDest, 
            pcrArrayColor, &bmi, DIB_RGB_COLORS);
    }

    // Transfer cursor image into the surface
    D3DLOCKED_RECT lr;
    pCursorBitmap->LockRect( &lr, NULL, 0 );
    pBitmap = (DWORD*)lr.pBits;
    for( y = 0; y < dwHeightDest; y++ )
    {
        for( x = 0; x < dwWidth; x++ )
        {
            if (bBWCursor)
            {
                crColor = pcrArrayMask[dwWidth*(dwHeightDest-1-y) + x];
                crMask = pcrArrayMask[dwWidth*(dwHeightSrc-1-y) + x];
            }
            else
            {
                crColor = pcrArrayColor[dwWidth*(dwHeightDest-1-y) + x];
                crMask = pcrArrayMask[dwWidth*(dwHeightDest-1-y) + x];
            }
            if (crMask == 0)
                pBitmap[dwWidth*y + x] = 0xff000000 | crColor;
            else
                pBitmap[dwWidth*y + x] = 0x00000000;
        }
    }
    pCursorBitmap->UnlockRect();

    // Set the device cursor
    if( FAILED( hr = pd3dDevice->SetCursorProperties( 0, 
        0, pCursorBitmap ) ) )
    {
        goto End;
    }

    hr = S_OK;

End:
    if( iconinfo.hbmMask != NULL )
        DeleteObject( iconinfo.hbmMask );
    if( iconinfo.hbmColor != NULL )
        DeleteObject( iconinfo.hbmColor );
    if( hdcScreen != NULL )
        ReleaseDC( NULL, hdcScreen );
    if( hdcColor != NULL )
        DeleteDC( hdcColor );
    if( hdcMask != NULL )
        DeleteDC( hdcMask );
    SAFE_DELETE_ARRAY( pcrArrayColor );
    SAFE_DELETE_ARRAY( pcrArrayMask );
    SAFE_RELEASE( pCursorBitmap );
    return hr;
}