#include "StdAfx.h"
#include "func.h"



/*
LPDIRECTDRAWSURFACE7 lataakuva(LPDIRECTDRAW7 m_pDD,char nimi[200], BOOL hardware)
{
	LPDIRECTDRAWSURFACE7 kuva = NULL;
	HBITMAP hbm = 0;
	BITMAP bminfo;
	DDSURFACEDESC2 ddsd;


	// Load the resource
	hbm = (HBITMAP)LoadImage(NULL, nimi, IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		

	// Find out how large this bitmap is
	//if 
		(!GetObject(hbm, sizeof(bminfo), &bminfo));
		//goto texture_error;

	// Create a surface for this bitmap
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.dwWidth = bminfo.bmWidth;
	ddsd.dwHeight = bminfo.bmHeight;
	//| DDSCAPS2_TEXTUREMANAGE
	//ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
	//ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	
	
	if (hardware)
		{
		ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;// | DDSCAPS_VIDEOMEMORY;
		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_D3DTEXTUREMANAGE;
		}
	else
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;

	
	//if 
		(m_pDD->CreateSurface(&ddsd, &kuva, NULL) != DD_OK);
		//goto texture_error;

	

    HDC hdcBitmap = CreateCompatibleDC( NULL );
    if( NULL == hdcBitmap )
    {
        kuva->Release();
        return NULL;
    }
    SelectObject( hdcBitmap, hbm );
    
	HDC hdcTexture;    
	if( SUCCEEDED( kuva->GetDC( &hdcTexture ) ) )    
	{


        BitBlt( hdcTexture, 0, 0, bminfo.bmWidth, bminfo.bmHeight, hdcBitmap,
                0, 0, SRCCOPY );
        kuva->ReleaseDC( hdcTexture );
    }
    DeleteDC( hdcBitmap );
	// Return the newly created texture
  


	return kuva;

//texture_error:
	//TRACE("Error creating texture\n");
	//RELEASE(kuva);
	//if (hbm)
	//	DeleteObject(hbm);
	//return NULL;
	//return kuva;
}


LPDIRECTDRAWSURFACE7 lataatekstuuri(int screenmode,D3DDEVICEINFO info, LPDIRECT3DDEVICE7 *m_pDevice,LPDIRECTDRAW7 m_pDD,char nimi[200], BOOL hardware)
{
	LPDIRECTDRAWSURFACE7 kuva = NULL;
	HBITMAP hbm = 0;
	BITMAP bminfo;
	DDSURFACEDESC2 ddsd;


	// Load the resource
	hbm = (HBITMAP)LoadImage(NULL, nimi, IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		

	// Find out how large this bitmap is
	//if 
		(!GetObject(hbm, sizeof(bminfo), &bminfo));
		//goto texture_error;

	// Create a surface for this bitmap
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);


	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT| DDSD_PIXELFORMAT;//  | DDSD_MIPMAPCOUNT;
	//ddsd.dwMipMapCount = 5; 
	ddsd.dwWidth = bminfo.bmWidth;
	ddsd.dwHeight = bminfo.bmHeight;
	
	
		ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;// | DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;// | DDSCAPS_VIDEOMEMORY;
		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_D3DTEXTUREMANAGE;
		
		ZeroMemory(&ddsd.ddpfPixelFormat, sizeof(DDPIXELFORMAT));
		ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT );
		memcpy(&ddsd.ddpfPixelFormat, &info.ddsdModes[screenmode].ddpfPixelFormat, sizeof(DDPIXELFORMAT));
	
		m_pDD->CreateSurface(&ddsd, &kuva, NULL);

		

    HDC hdcBitmap = CreateCompatibleDC( NULL );
    if( NULL == hdcBitmap )
    {
        kuva->Release();
        return NULL;
    }
    SelectObject( hdcBitmap, hbm );
    
	HDC hdcTexture;    
	if( SUCCEEDED( kuva->GetDC( &hdcTexture ) ) )    
	{


        BitBlt( hdcTexture, 0, 0, bminfo.bmWidth, bminfo.bmHeight, hdcBitmap,
                0, 0, SRCCOPY );
        kuva->ReleaseDC( hdcTexture );
    }
    DeleteDC( hdcBitmap );
	// Return the newly created texture
  


	return kuva;

//texture_error:
	//TRACE("Error creating texture\n");
	//RELEASE(kuva);
	//if (hbm)
	//	DeleteObject(hbm);
	//return NULL;
	//return kuva;
}
*/
/* 
 * randInt
 *
 * returns a random integer in the specified range
 */
int randInt( int low, int high )
{
    int range = high - low;
	if(range==0)return low;
    int num = rand() % range;
    return( num + low );
}

/*
 * randDouble
 *
 * returns a random double in the specified range
 */
float randDouble( float low, float high )
{
    float range = high - low;
	if(range==0)return low;
    float num = range * (float)rand()/(float)RAND_MAX;
    return( num + low );
}

bool intersect(RECT eka,RECT toka)
{
	int tempx1,tempx2,tempy1,tempy2;

	tempx1=eka.right-toka.left;
	tempx2=toka.right-eka.left;
	if (((tempx1>0)&&(tempx2>0)) ||
	((tempx1<0)&&(tempx2<0)) )
	
	{
	tempy1=eka.top-toka.bottom;
	tempy2=toka.top-eka.bottom;
	if (((tempy1>0)&&(tempy2>0)) ||
	((tempy1<0)&&(tempy2<0)))
	return true;
	}


	return false;

}
// Identical to fgets except the string is trucated at the first ';',
// carriage return or line feed.
char *stripped_fgets(char *s, int n, FILE *f)
{
   int i=0;

   if (fgets(s,n,f)==NULL)
      return(NULL);

   while (s[i]!=';' && s[i]!=13 && s[i]!=10 && s[i]!=0)
      i++;
   s[i]=0;

   return(s);
}




//////////////////////// MATRIX FUNCTIONS ///////////////////////////////////
/*
#define PI 3.141592653

D3DMATRIX IdentityMatrix()
{
	return D3DMATRIX(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
}

D3DMATRIX ZeroMatrix(void)  // initializes matrix to zero
{
	D3DMATRIX ret;
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			ret(i, j) = 0.0f;
	return ret;
} // end of ZeroMatrix()

// Multiplies two matrices.
D3DMATRIX MatrixMult(const D3DMATRIX a, const D3DMATRIX b)  
{
	D3DMATRIX ret = ZeroMatrix();
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			for (int k=0; k<4; k++)
				ret(i, j) += a(k, j) * b(i, k);
	return ret;
} // end of MatrixMult()

D3DMATRIX Translate(const float dx, const float dy, const float dz)
{
	D3DMATRIX ret = IdentityMatrix();
	ret(3, 0) = dx;
	ret(3, 1) = dy;
	ret(3, 2) = dz;
	return ret;
} // end of Translate()

D3DMATRIX RotateX(const float rads)
{
	float cosine = (float)cos(rads);
	float sine = (float)sin(rads);
	D3DMATRIX ret = IdentityMatrix();
	ret(1,1) = cosine;
	ret(2,2) = cosine;
	ret(1,2) = -sine;
	ret(2,1) = sine;
	return ret;
} // end of RotateX()

D3DMATRIX RotateY(const float rads)
{
	float cosine = (float)cos(rads);
	float sine = (float)sin(rads);
	D3DMATRIX ret = IdentityMatrix();
	ret(0,0) = cosine;
	ret(2,2) = cosine;
	ret(0,2) = sine;
	ret(2,0) = -sine;
	return ret;
} // end of RotateY()

D3DMATRIX RotateZ(const float rads)
{
	float cosine = (float)cos(rads);
	float sine = (float)sin(rads);
	D3DMATRIX ret = IdentityMatrix();
	ret(0,0) = cosine;
	ret(1,1) = cosine;
	ret(0,1) = -sine;
	ret(1,0) = sine;
	return ret;
}	// end of RotateZ()

D3DMATRIX Scale(const float size)
{
	D3DMATRIX ret = IdentityMatrix();
	ret(0, 0) = size;
	ret(1, 1) = size;
	ret(2, 2) = size;
	return ret;
}   // end of Scale()

D3DMATRIX ViewMatrix(const D3DVECTOR from,      // camera location
                            const D3DVECTOR at,        // camera look-at target
                            const D3DVECTOR world_up,  // world’s up, usually 0, 1, 0
                            const float roll)          // clockwise roll around
                                                       //    viewing direction, 
                                                       //    in radians
{
	D3DMATRIX  view = IdentityMatrix();
	D3DVECTOR  up, right, view_dir;

	view_dir = Normalize(at - from);
	right = CrossProduct(world_up, view_dir);
	up = CrossProduct(view_dir, right);
	right = Normalize(right);
	up = Normalize(up);
	view(0,0) = right.x;
	view(1,0) = right.y;
	view(2,0) = right.z;
	view(0,1) = up.x;
	view(1,1) = up.y;
	view(2,1) = up.z;
	view(0,2) = view_dir.x;
	view(1,2) = view_dir.y;
	view(2,2) = view_dir.z;
	view(3,0) = -DotProduct(right, from);
	view(3,1) = -DotProduct(up, from);
	view(3,2) = -DotProduct(view_dir, from);

	if (roll != 0.0f)
	{
		// MatrixMult function shown below
		view = MatrixMult(RotateZ(-roll), view); 
	}

	return view;
} // end of ViewMatrix()

D3DMATRIX ProjectionMatrix(const float near_plane,     // distance to near clipping plane
                                  const float far_plane,      // distance to far clipping plane
                                  const float fov)            // field of view angle, in radians
{
	float c = (float)cos(fov*0.5);
	float d = (float)(c*1.3333333);
	float s = (float)sin(fov*0.5);
	float Q = s/(1.0f - near_plane/far_plane);
	D3DMATRIX ret = ZeroMatrix();
	ret(0, 0) = c;
	ret(1, 1) = d;
	ret(2, 2) = Q;
	ret(3, 2) = -Q*near_plane;
	ret(2, 3) = s;
	return ret;
} // end of ProjectionMatrix()
*/
bool viivaviiva(bool suora2, bool *osuma,float *osumax,float *osumaz,float piste1x,float piste1z,float piste2x,float piste2z,float piste3x,float piste3z,float piste4x,float piste4z)//osuuko viiva viivaan
{
/*
	RECT r1,r2;
	r1.left=piste1x;
	r1.top=piste1z;
	r1.right=piste2x;
	r1.bottom=piste2z;
	r2.left=piste3x;
	r2.top=piste3z;
	r2.right=piste4x;
	r2.bottom=piste4z;

	if(!intersect(r1,r2))return false;
*/
	float kk1,kk2;
	float x1,x2,z1,z2;
	float virhetarkkuus=0.0f;
	//float temp=false;

	if((piste2x-piste1x==0)|(piste4x-piste3x==0))
	{	
		virhetarkkuus=0.01f;
		/*temp   =piste1x;
		piste1x=piste3x;
		piste3x=temp;
		temp   =piste2x;
		piste2x=piste4x;
		piste4x=temp;

		temp   =piste1z;
		piste1z=piste3z;
		piste3z=temp;
		temp   =piste2z;
		piste2z=piste4z;
		piste4z=temp;
		temp=true;*/
	}
		

	kk1=(float)(piste2z-piste1z)/(piste2x-piste1x+virhetarkkuus);//kulmakertoimet	
	kk2=(float)(piste4z-piste3z)/(piste4x-piste3x+virhetarkkuus);
	/*if(piste2x-piste1x==0)kk1=650000000;
	if(piste4x-piste3x==0)kk2=650000000;*/
	//if(kk1!=kk2)//jos eivät ole saman suuntaisia
	{

		
		/*x1=mopot[0].x1;
		y1=mopot[0].z1;
		x2=viivagroup[0].viivat[0].viiva[q].piste[a].x1;
		y2=viivagroup[0].viivat[0].viiva[q].piste[a].z1;*/

		*osumax=(kk1*piste1x-piste1z-kk2*piste3x+piste3z)/(kk1-kk2);
		*osumaz=kk1*(*osumax-piste1x)+piste1z;
virhetarkkuus=0.005f;
bool meneex,meneez;
		
		//onko piste viivalla 1
		if(piste1x<piste2x)
			{x2=piste2x; x1=piste1x;}
		if(piste1x>=piste2x)		
			{x2=piste1x; x1=piste2x;}		
		meneex=false;
		//if(x1!=x2){
		if (fabs(x2-x1)>virhetarkkuus){
			if(*osumax<x2)
			if(*osumax>x1)
			meneex=true;
		}
		else meneex=true;
		if(piste1z<piste2z)
			{z2=piste2z; z1=piste1z;}
		if(piste1z>=piste2z)		
			{z2=piste1z; z1=piste2z;}		
		meneez=false;
		//if(z1!=z2){
		if (fabs(z2-z1)>virhetarkkuus){
			if(*osumaz<z2)
			if(*osumaz>z1)
			meneez=true;
		}
		else meneez=true;

		//jos toista suoraa ei mitata
		if(!suora2)
		if(meneex&&meneez)
			{				
					*osuma=true;
					return true;
			}
		

		if(meneex&&meneez){		
		//onko piste viivalla 2
			if(piste3x<piste4x)
				{x2=piste4x; x1=piste3x;}
			if(piste3x>=piste4x)		
				{x2=piste3x; x1=piste4x;}		
			meneex=false;
			//if(x1!=x2){
			if (fabs(x2-x1)>virhetarkkuus){
				if(*osumax<x2)
				if(*osumax>x1)
				meneex=true;
			}
			else meneex=true;
			if(piste3z<piste4z)
				{z2=piste4z; z1=piste3z;}
			if(piste3z>=piste4z)		
				{z2=piste3z; z1=piste4z;}		
			meneez=false;
			//if(z1!=z2){
			if (fabs(z2-z1)>virhetarkkuus){
				if(*osumaz<z2)
				if(*osumaz>z1)
				meneez=true;		
			}
			else meneez=true;
			if(meneex&&meneez)
			{
					//if(temp==true) {temp=*osumax; *osumax=*osumaz; *osumaz=*osumax;}
					*osuma=true;
					return true;
			}
	
		}
	}
	*osuma=false;
	return false;
}

bool strtobool(char *rivi){
	int a=atoi(rivi);
	if (a==0)return false;
	else return true;
}







