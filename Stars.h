
#if !defined(AFX_BIKEZ2_H__59C06CDE_5406_43D9_992E_DA66D69E1E74__INCLUDED_)
#define AFX_BIKEZ2_H__59C06CDE_5406_43D9_992E_DA66D69E1E74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define DIRECTINPUT_VERSION 0x0900

#include "resource.h"
#define D3D_OVERLOADS
#include <windowsx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>
#include <stdio.h>
#include "func.h"
#include <tchar.h>
#include <string.h>
//#include <stdexcept.h>
#include <stdlib.h>
#include <dshow.h>
#include <malloc.h>
#include <mmreg.h>
#include "dsutil.h"
#include "dxutil.h"
using namespace std;


/*#include <windows.h>
#include <basetsd.h>
#include <commdlg.h>
#include <mmreg.h>
#include <dxerr8.h>
#include <dsound.h>
#include "resource.h"
#include "dsutil.h"
#include "dxutil.h"*/

#define D3DFVF_WVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL | D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0))


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput9.lib")
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "dsound.lib")


/*#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput.lib")
#pragma comment(lib, "dsound.lib")*/

	struct vvertex {
				D3DVECTOR position;
				D3DVECTOR normal;
				float     u, v;//, w;   
			};

	struct pvertex {
				D3DVECTOR position;
				float     u, v;   
			};

	struct esine
	{
		LPDIRECT3DVERTEXBUFFER9 kolmijako;
		INT vert;
	};


	struct objekt 
	{
		INT textuuri;//materiaali
		INT textuuri2;//tekstuurin numero
		INT matsku;//ihoa 0, ter‰st‰ 1, kangasta 2, miekka 3
		//D3DVECTOR upleft,downright;//koko
		esine loota;
		float x,y,z;
		float rx,ry,rz;

	};

	struct obj
	{
		BOOL mirror;
		INT count;
		objekt *sisus;
		float x,y,z;
		float rx,ry,rz;
		float swordpointx,swordpointy,swordpointz;
		D3DVECTOR upleft,downright;//koko
		D3DXMATRIX sijainti;
	};

	struct kuvat
	{
		obj *malli;
	};

	struct ship_type_base
	{
		float mass;//mass of ship
		int picture;//picture of ship
		float size;//size of ship
		char classname[300];//name of ship class
		int ship_type;//type of ship
		int gun[4];//guns
		int number_of_guns[4];//number of guns at a weapon set
		float gunangle[4][4],gundistance[4][4];//position of weapon set
		int backmotors;
		float motorangle[10];
		float motordistance[10];
		float motordownpower;
		float motoruppower;
		float motorleftpower;
		float motorrightpower;
		int threat;//the offensive capability of this ship
		float base_energy;//normal energy of ship
		float base_heat;//amount of heat ship can take
	};

	struct baseencounter
	{
		
		float energy;//for repairing ships
		bool chasing;
		bool dead;
		int strategy;//0=plead mercy 1=ask question 2=offensive
		char name[300];//name of ship
		ship_type_base ship_basea;//base of ship
		
			//0=refugee
			//1=pirate
			//2=merchant
			//3=colonial navy
			//4=alien
			//5=traveller
		int type;
		
			//0=slaves
			//1=contraband goods
			//2=illegal weapons
			//3=funds
			//4=fuel
		int cargo[5];
	};

	struct shipbase
	{
		bool enter,esc,up,down,left,right,one,two,three,four,space;//n‰pp‰imet
		bool enter2,esc2,up2,down2,left2,right2,one2,two2,three2,four2,space2;//n‰pp‰imet edellisell‰ framella
		float x1,y1,z1;//koordinaatit
		float x2,y2,z2;//koordinaatit oli
		float x3,y3,z3;//tˆrm‰yksen keskipisteen koordinaatit
		float rx,ry,rz;//kallistukset
		float vx,vz,vr;//nopeudet suuntiinsa ja kierien
		float motorright,motordown,motorleft,motorup;//oikea, ala, vasen ja ylˆs moottorit		
		float motor0time,motor1time,motor2time,motor3time;
		float guntime[4];//timing of weapons
		int nearstar,nearstar2;//is or was near a planet
		float vangle;//angle of movement
		float vpowersquare;//power of movement (square)
		bool dead;//dead or not
		int number;//index of this element
		float energy;//energy/health of ship
		int side;//0=player 1=enemy
		int shotlast_enemy,shotlast_me;//who I shot last and who shot me last
		bool disabled;//if the ship has been disabled
		baseencounter encounter;//store info for possible capture
		int onplanet;//which planet the ship is on (for missions)
		float heat;//amount of heat on ship
		bool overheat;//if the ship has overheated
	};


	struct dot
	{
		float x1,y1,z1;//alkupiste
		float x2,y2,z2;//loppupiste
	};

	struct linja
	{
		int linjaa;
		dot *piste;
	};
	
	struct linjat
	{
		int viivaa;
		linja *viiva;
	};

	struct linjagroup
	{
		int grouppia;
		linjat *viivat;
	};
	
	struct smoke
	{
		D3DXVECTOR3 paikka;
		float vx,vy,vz;//menossa
		int tyyppi;
		float q,w,e;//savun kulma
		//int kuva;//alakuva 0 tai 1
		float aika;//paljonko aikaa
		//float cos,sin,up;//kulmaa varten
		float rotate;
		float koko;//mink‰kokoinen savu on
		float suurenee;//paljonko suurenee
		float transparency;//0-1
		bool pois;
	};
	
	struct light
	{
		bool on;
		D3DLIGHT9 valo;	
		float aika;//paljonko aikaa t‰hteell‰
	};

	struct asteroidi
	{
		int sectorx,sectorz;//sektorit *100
		int number;//mik‰ indexi
		float x,y,z;//paikka
		float rx,ry,rz;//kulmat
		float vx,vy,vz;//menossa
		float vrx,vry,vrz;//rotatenopeudet
		int picture;//3d-malli
		int type;//0=tausta-asteroidi
		float size;//koko
		bool dead;//onko olemassa
		float distance;//et‰isyys pelaajasta
		bool visible;
	};	

	struct particles
	{
		D3DVECTOR position;
		D3DVECTOR movement;
		//float     u, v;
		bool dead;//onko ollenkaan olemassa
		int picture;//0=flame 1=smoke
		float time;
		//float uspeed;
	};

	struct bulletbase
	{
		D3DVECTOR position;
		D3DVECTOR position2;
		D3DVECTOR movement;		
		D3DVECTOR rotate;
		int sectorx,sectorz;
		bool dead;//onko ollenkaan olemassa
		int picture;
		float time;		
		int fromweapon;//mist‰ aseesta ammuttu
		float distancesquare;//square of distance to player
		int shooter;//who shot this bullet
		int target;//which ship it was shot at
		float power;//how much power it has left 1...0
	};

	struct weaponbase
	{
		float damage;
		int bulletpicture;
		int bullettype;
		float bulletspeed;
		float firerate;
		int collision_explosion;//explosion effects on collision 0=none
		int collision_smoke;//smoke effects on collision 0=none
		int movement_smoke;//smoke effects on movement 0=none
		bool tracking;//whether it tracks the ships or not
		float powerdownrate;//how fast the bullets power fades
		int sound_launch;//shooting sound effect
		int sound_hit;//hit sound effect3
		float heat;//amount of heat firing this weapon produces
	};

	struct planets
	{
		float x,y,z;
		float rx,ry,rz;
		float radiustohost;//radius to host
		float angletohost;//angle to host
		float angletosun;//angle to sun
		int host;//sun,planet
		float speed;
		float rotatespeed;
		float ellipce;
		bool dead;
		float distancesquare;//distance to player
		float mass;//planet mass
		int picture;
		int atmosphere;//picture number of atmosphere
		float size;//compared to earth
		char name[200];//name of planet
		int type;//0=planet 1=moon 2=asteroid
		int shadow;//-1=none 0=circular
		float angletoship;//angle to ship
		int population;//population of planet
		int wealth;//wealth of planet
		int military;//strength of military
		char location[200];//e.g. Jupiter's moon
		int prize[5];//prizes of fuel, slaves ,etc...
	};

	struct missions
	{
		bool dead;
		int type;//0=goto planet 1=items to planet		
		char name[100];//mission name
		char text[300];//short description

		//victory conditions		
		int planet;//which planet
		int cargominus[5];//take items
		int end_flag;//which end_mission flag terminates this mission

		//prize
		int cargoplus[5];//give items
		int prize_plot;//which plot to give as a prize
		int end_flag_do;//end some other mission
	};

	struct dialog_option
	{
		char text[300];
		int general_effect;
			//
		int effect_parameter;
		int effect_parameter2;

		int cargoplus[5];//give items to player
		int cargominus[5];//take items

		int default_selection;//select this item by default

		missions mission;//give player a mission
	};


	struct dialogs
	{
		
		baseencounter randomship;//possible random ship encountered
		char text[2000];
		int picture;
		int options;//number of possible dialogue options
		//char option[6][300];
		dialog_option option[10];//what the button does
		int lowpictureclass,lowpicturenumber;//the lower screen picture
		float rotate;
		char info[6][300];
		int infos;//number of infos
		bool noup,nodown,noreturn;//next keyboard up won't be taken notice of
		float dialog_options_place;//place of dialog options relative to normal
		int ships;//amount of ships in battle
	};

	struct battles
	{
		int type;//0=planet 1=asteroid field 2=ship
		planets planet;//info on planet
		float fieldsize;//size of battlefield
		float sunx,sunz;//direction of the sun
		int side[2];//number of ships on each side
		float endtimer;//timer for the battle ending
		int endplot;//when battle ends, initiate dialog
	};

	
	

	

	

	


BOOL lataa(char nimi[200],obj *kohde,BOOL mirror,BOOL miekkakala);
BOOL lataawall(char nimi[200],linjagroup *kohde,BOOL mirror);
BOOL lataatext();
void init(void);
bool createscreen(void);
bool Render(void);
bool luekuvat(void);
void CleanUp(void);//h‰vitt‰‰ kamat
BOOL draw(float r,float g,float b,obj *tavara);
void poistaobj(obj *kohde, int indeksi);
bool initkeyb(void);
bool deinitkeyb(void);
void luekeyb(void);
void savusta(float transparency, float koko, float suurenee,bool rotate,float savukesto,float x,float y,float z,int tyyppi,float q,float w,float e,float vx,float vy,float vz);//tekee savun
void laskesavut(void);//laskee savut
void SetupPixelFog(DWORD dwColor, DWORD dwMode);//sumu
void SetupVertexFog(float fStart, float fEnd,DWORD dwColor, DWORD dwMode, BOOL fUseRange, FLOAT fDensity);//sumu
void valota(float x,float y,float z);//tekee valon
void poistavalo(int a, int *b);//poistaa valon
BOOL drawfast(obj *tavara);//piirt‰‰ nopeammin
void kirjota(float size,float r,float g, float b,float x, float y, INT rivi,CHAR teksti[1000]);
void cfg_save(void);//tallentaa asetukset
void cfg_load(void);//lataa asetukset
void soita(int samplenumero,float volume,float paikkax,float paikkaz);//soittaa ‰‰nen
void clearzbuffer(void);

//pelin rutiinit
void render_game(void);//piirt‰‰ peli‰
void readkey_game(void);//lukee n‰pp‰imet
void fly(shipbase *ship);//alukset lent‰‰
void fly_asteroids(asteroidi *asteroid);//asteroidit lent‰‰
void generate_particle(int picture, float aika, float paikkax,float paikkay,float paikkaz,float suuntax,float suuntay,float suuntaz,float speed,float vx,float vy,float vz);//particle animation starter
void fly_particles(void);//pisteet lent‰‰
void shoot(shipbase *shooter, int type, float time, float placex,float placey,float placez,float directionx,float directiony,float directionz,float vx,float vy,float vz);//fire a bullet
void fly_bullet(bulletbase *bullet);//bullets fly
void shoot_asteroid(int picture, float size, int type, float x, float y, float z, float rx, float ry, float rz, float vx, float vy, float vz, float vrx, float vry, float vrz);//fires an asteroid
float fHatRandom(float fRange);
void renderbattle(void);//draws battle
void rendersolarsystem(void);//draws solar system
void fly_planet(planets *planeta);//flying planets
void render_dialog(void);//draws dialogs
void create_dialog(int dialogtype,int value0,int select_choise);//creates dialogs
void create_battle(int type, int parameter);//creates battles
void computer_think(shipbase *ship_c);//computer thinks
void end_battle(int type, int parameter);//battle ends
void free_ship(int *number);//finds a free ship
void create_random_ship(baseencounter *randomship,int difficulty,int ship);//creates a random ship
void edit_shipslot(int parameter);//asks a free slot for the player's new ship
void render_ships(void);//renders a dialog for player to choose ships
void render_capture(void);//renders the capture scene
void rendersmoke(float camq,float camw,float came);//renders smoke effects
void render_cutscene(void);//renders a cutscene
void render_map(void);//draws solar system map
int free_mission(void);//finds a free mission
void compute_missions(void);//calculates which missions are finished
void render_missions(void);//draws diagram of missions
int randomplanet(int number);
HRESULT Screenshot(LPDIRECT3DDEVICE9 lpDevice,const char* lpszFileName,char line[200]);
//void GetScreenshotFileName(string& FileName);
void save_game(int slot);//saves game
void render_menu(void);//renders game menus
void luesavet(void);
void load_game(int slot);//load game
void new_game(void);//starts a new game
HRESULT SwapSourceFilter(int song_number);
HRESULT GraphInit(void);
HRESULT HandleGraphEvent(void);
void playsound(int number,float volume,float soundx,float soundz,float listenerx,float listenerz);//plays a sound
void render_start_demo(void);
void sound_init(void);
void clean_display(void);
void restore_display(void);
HRESULT D3DUtil_SetDeviceCursor( LPDIRECT3DDEVICE9 pd3dDevice, HCURSOR hCursor );
void startApplication(HINSTANCE hInstance);



	//pelin sis‰llˆlliset objektit		
	
	const int maksimivaloja=10;	
	const int maksimisavuja=200;	
	const int maksimiasteroid=1000;
	const int maximum_particles=500;
	const int maximum_bullets=1000;
	const int maximumplanets=1000;
	const int maximumrocks=10000;	
	const int maximum_ships=100;
	const int maximum_shipslot=7;
	const int maximum_nebula=40;


	int pelivaihe,pelivaihe_oli;
	int pelivaihe2,pelivaihe2_oli;
	int keytimer;//n‰pp‰imistˆn ajastin	
	const float maxvisible =25000.0f;
	float pelinopeus;//pelin nopeus
	bool options[10];//asetukset
	smoke savu[maksimisavuja];//savut	
	light lamppu[maksimivaloja];
	int valoja;	
	float kamerax1,kameray1,kameraz1;//kamera from
	float kamerax2,kameray2,kameraz2;//kamera to
	float cameraheight;//height of the camera

	shipbase ship[maximum_ships];
	pvertex galaxy[2500];
	pvertex spacedust[1500];
	asteroidi nebula[maximum_nebula];//asteroidia taustalla
	asteroidi asteroid[maksimiasteroid];//asteroidit aluksen tasolla
	particles particle[maximum_particles];
	pvertex particle_animation[4][maximum_particles];
	bulletbase bullet[maximum_bullets];
	weaponbase weapon[20];
	float galaxy_x,galaxy_z;//taustan galaksi keskipiste
	float galaxy_rx,galaxy_ry,galaxy_rz;//taustan galaksi rotate	
	planets planet[maximumplanets];
	planets rock[maximumrocks];
	float suntimer;//sun's flame timer
	dialogs dialog;//dialog for events
	float aspect;//camera's aspect ratio
	int dialog_choice;//player's choise in dialog
	battles battle;//next battle
	baseencounter shipslot[maximum_shipslot];//player¥s ships
	baseencounter shipslot_battle[maximum_shipslot];//disabled ships
	pvertex vertexletters[2][6*1000];
	char temprivi[300],rivi[300];
	int player_controlled_ship;//what ship player controls
	ship_type_base ship_base[20];//different types of ships
	missions mission[100];//missions
	int missions;//how many missions there are currently active
	int missionlist[100];//which mission on the list is same in the table
	int selected_mission;
	int randomnames;//how many random ships names there are 
	char randomname[100][50];
	char screenshot_name[200];//stores name for screenshot
	float screenshot_timer;//timer for 'screenshot taken' text
	char random_mission_name[100][50];//random names for random missions
	int random_mission_names;
	bool end_game;//if the game is to exit in the next frame
	float fueltimer;//timer for fuel usage
	float fuellowtimer;
	int fuellowdirection;
	int player_controlled_ship_in_map;//the selected ship in map mode
	//int kirjaintanimessa;
	//char savenimi[256];//tallennuksen nimi
	float game_saved_timer;
	char m_filenames[10][256];//tallennustiedostojen nimet
	int kirjaintan[10];//montako kirjainta tallennusnimiss‰ on
	bool loadable[10];//voiko ladata tallennuksen
	int tallennuspaikka;//mik‰ tallennus on valittuna
	int selected_left_menu;//selected menu item
	int selected_option;//selected option in menu
	int focus;//which part of menu has focus
	bool mouse_active;//if mouse is active
	bool no_games_to_load;
	bool game_started;//if it is possible to save the game
	int menu_return_pelivaihe;//where to return from menu
	int menu_return_pelivaihe2;//where to return from menu
	char options_text[10][100];
	float option_rotate[10];//rotation of option buttons in menu
	float option_rotate_speed[10];
	int selected_key;//selected key in menu
	int wait_for_key;//wait for a key in change key dialog
	bool help_screen;//if the help screen is on
	bool music_initialized;//if music has been initialized
	float threat;//how terrible forces the player has
	float planet_visit_timer;//timer for visiting planets
	float start_timer;//timer for the game start
	float warp_timer;//timer for space warp text
	int music_playing;//which song is playing
	float point_size;//size of points
	HCURSOR mouse_cursor;
	bool mouse_button_0,mouse_button_was_0,mouse_button_1,mouse_button_was_1;
	bool cursor_shown;



	//plot
	bool plot_started;//if the plot has started
	int dan_planet;//which planet diesel dan is on
	int money_offer_timer;//a timer to start the money offer plot
	bool end_mission[100];//end mission
	int alien_planet;//which planet the aliens are on



	//capturing ships - bad code
	struct man
	{
		float x;
		float z;
		float energy;
		bool dead;
		float rotatex;
		bool left, right, up, down, space,alt;
		float left_right_timer;
		float guntime;
		int side;
		int target,targetfar;
		float targettimer;
		float uptimer;
		int up_or_down;
		float legtimer;
		int leg;
	};
	man capture_man[100];
	float capture_end_timer;




	//sound
	CSoundManager* g_pSoundManager = NULL;
	CSound*        g_pSound[15];
	bool sound_initialized;


	// DirectShow Graph, Filter & Pins used
	IGraphBuilder *g_pGraphBuilder = NULL;
	IMediaControl *g_pMediaControl = NULL;
	IMediaSeeking *g_pMediaSeeking = NULL;
	IBaseFilter   *g_pSourceCurrent = NULL;
	IBaseFilter   *g_pSourceNext = NULL;
	TCHAR          g_szCurrentFile[128];
	IMediaEventEx  *pEvent = NULL;



	//D3DAdapterInfo    m_Adapters[10];
	D3DCAPS9 deviceCaps;
	DWORD             m_dwNumAdapters;
	DWORD             m_dwAdapter;
	BOOL              m_bUseDepthBuffer;
	BOOL              m_bWindowed;
	DWORD             m_dwMinDepthBits;  
	DWORD             m_dwMinStencilBits;
	#define D3DAPPERR_NODIRECT3D          0x82000001
	#define D3DAPPERR_NOWINDOW            0x82000002
	#define D3DAPPERR_NOCOMPATIBLEDEVICES 0x82000003
	#define D3DAPPERR_NOWINDOWABLEDEVICES 0x82000004
	#define D3DAPPERR_NOHARDWAREDEVICE    0x82000005
	#define D3DAPPERR_HALNOTCOMPATIBLE    0x82000006
	#define D3DAPPERR_NOWINDOWEDHAL       0x82000007
	#define D3DAPPERR_NODESKTOPHAL        0x82000008
	#define D3DAPPERR_NOHALTHISMODE       0x82000009
	#define D3DAPPERR_NONZEROREFCOUNT     0x8200000a
	#define D3DAPPERR_MEDIANOTFOUND       0x8200000b
	#define D3DAPPERR_RESIZEFAILED        0x8200000c

	//int SortModesCallback( const VOID* arg1, const VOID* arg2 );
	HRESULT BuildDeviceList(void);
	BOOL FindDepthStencilFormat( UINT iAdapter, D3DDEVTYPE DeviceType,
	D3DFORMAT TargetFormat, D3DFORMAT* pDepthStencilFormat );
	HRESULT ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior, D3DFORMAT Format );



	//objektit
	kuvat mallit[3];
	
	//input
	LPDIRECTINPUT           g_lpDI;
	LPDIRECTINPUTDEVICE     g_lpDIDevice;
	LPDIRECTINPUTDEVICE     g_pMouse;
	//DIMOUSESTATE		  mousestate;
	//DIMOUSESTATE		  mousestate2;
	char  buffer[256], buffer2[256];
	float mousex, mousey, mousex2, mousey2;
	float plusmiinus;//n‰pisk‰ll‰ s‰‰dett‰v‰ tempfloat
	int key[20];//pelin n‰pp‰imet	
	bool pressed,pressed2;//onko yht‰‰n n‰pp‰int‰ painettu
	int down,down2;//mik‰ n‰pp‰in on pohjassa
	

	/*int ukkoja;//montako ukkoa kent‰ss‰
	int savuja;//montako savua kent‰ss‰
	int luoteja;//montako luotia kent‰ss‰ lent‰‰*/
	
	LPDIRECT3D9 m_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DPRESENT_PARAMETERS m_d3dpp; 
	//LPDIRECT3D8 m_pD3D;
	//LPDIRECTDRAWSURFACE8 taka;	
	//LPDIRECTDRAWSURFACE8 m_pPrimary;
	//LPDIRECTDRAW7 m_pDD;
	//LPDIRECTDRAWSURFACE7 zpuskuri;
	D3DMATRIX m_World, m_View, m_Projection;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	int enumerationint1,enumerationint2;//enumerointi intit
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int SCREEN_BITS;
	int driver,device,mode;//used 3d-device
	//D3DDEVICEINFO info;
	DWORD m_LastTime;
	bool quittaos;//ollaanko quittaamassa	
	int materiaa;//montako materiaalia
	D3DMATERIAL9 *mat;	
	ID3DXMatrixStack *matriisi;
	LONG bug1,bug2,bug3;
	float elapsed,elapsed2;
	float elapsed3[100];
	//D3DDEVICEDESC8 desc3d;
	float dx,dx2,dy,dz;//kameraa
	float camx,camy,camz;//kameraa
	LPDIRECT3DTEXTURE9
		*tausta;
	LPDIRECT3DSURFACE9
		*kuvia;

	D3DFORMAT format;

#endif // !defined(AFX_BIKEZ2_H__59C06CDE_5406_43D9_992E_DA66D69E1E74__INCLUDED_)
