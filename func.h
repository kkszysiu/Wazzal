// engine.h: interface for the engine class.
//
//////////////////////////////////////////////////////////////////////
/*
#if !defined(AFX_ENGINE_H__EB604380_F9F3_11D3_9282_A0A449C10801__INCLUDED_)
#define AFX_ENGINE_H__EB604380_F9F3_11D3_9282_A0A449C10801__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
*/
#define D3D_OVERLOADS
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <stdio.h>



#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput.lib")


//-----------------------------------------------------------------------------
// Name: struct D3DModeInfo
// Desc: Structure for holding information about a display mode
//-----------------------------------------------------------------------------
struct D3DModeInfo
{
    DWORD      Width;      // Screen width in this mode
    DWORD      Height;     // Screen height in this mode
    D3DFORMAT  Format;     // Pixel format in this mode
    DWORD      dwBehavior; // Hardware / Software / Mixed vertex processing
    D3DFORMAT  DepthStencilFormat; // Which depth/stencil format to use with this mode
};

//-----------------------------------------------------------------------------
// Name: struct D3DDeviceInfo
// Desc: Structure for holding information about a Direct3D device, including
//       a list of modes compatible with this device
//-----------------------------------------------------------------------------
struct D3DDeviceInfo
{
    // Device data
    D3DDEVTYPE   DeviceType;      // Reference, HAL, etc.
    D3DCAPS9     d3dCaps;         // Capabilities of this device
    const TCHAR* strDesc;         // Name of this device
    BOOL         bCanDoWindowed;  // Whether this device can work in windowed mode

    // Modes for this device
    DWORD        dwNumModes;
    D3DModeInfo  modes[150];

    // Current state
    DWORD        dwCurrentMode;
    BOOL         bWindowed;
    D3DMULTISAMPLE_TYPE MultiSampleType;
};


//-----------------------------------------------------------------------------
// Name: struct D3DAdapterInfo
// Desc: Structure for holding information about an adapter, including a list
//       of devices available on this adapter
//-----------------------------------------------------------------------------
struct D3DAdapterInfo
{
    // Adapter data
    D3DADAPTER_IDENTIFIER9 d3dAdapterIdentifier;
    D3DDISPLAYMODE d3ddmDesktop;      // Desktop display mode for this adapter

    // Devices for this adapter
    DWORD          dwNumDevices;
    D3DDeviceInfo  devices[5];

    // Current state
    DWORD          dwCurrentDevice;
	int number;//number of display adapter
};



	




	bool viivaviiva(bool suora2, bool *osuma,float *osumax,float *osumaz,float piste1x,float piste1z,float piste2x,float piste2z,float piste3x,float piste3z,float piste4x,float piste4z);//osuuko viiva viivaan
	//LPDIRECTDRAWSURFACE7 lataakuva(LPDIRECTDRAW7 m_pDD, char nimi[200], BOOL hardware);
	//LPDIRECTDRAWSURFACE7 lataatekstuuri(int screenmode,D3DDEVICEINFO info, LPDIRECT3DDEVICE7 *m_pDevice,LPDIRECTDRAW7 m_pDD,char nimi[200], BOOL hardware);
	int randInt( int low, int high );
	float randDouble( float low, float high );
	bool intersect(RECT eka,RECT toka);
	char *stripped_fgets(char *s, int n, FILE *f);	
	D3DMATRIX IdentityMatrix();
	D3DMATRIX ZeroMatrix(void);
	D3DMATRIX MatrixMult(const D3DMATRIX a, const D3DMATRIX b);
	D3DMATRIX ViewMatrix(const D3DVECTOR from,const D3DVECTOR at, const D3DVECTOR world_up, const float roll);	
	D3DMATRIX ProjectionMatrix(const float near_plane, const float far_plane, const float fov);
	bool strtobool(char *rivi);


	






//};

/*#endif // !defined(AFX_ENGINE_H__EB604380_F9F3_11D3_9282_A0A449C10801__INCLUDED_)
*/
