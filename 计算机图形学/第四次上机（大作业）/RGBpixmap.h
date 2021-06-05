#ifndef _RGBPIXMAP
	#define _RGBPIXMAP
#if defined(_WIN32)
#include<GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

class IntPoint
{ 
public:
	int x,y;
	void set(int dx, int dy){x = dx; y = dy;}
	void set(IntPoint& p){ x = p.x; y = p.y;} 
	IntPoint(int xx, int yy){x = xx; y = yy;}
	IntPoint(){ x = y = 0;}
};

class Point2
{
public: 
	float x,y;
	void set(float dx, float dy){x = dx; y = dy;}
	void set(Point2& p){ x = p.x; y = p.y;} 
	Point2(float xx, float yy){x = xx; y = yy;}
	Point2(){x = y = 0;}
};

class PolyLine
{
	
public:
	int num;
	Point2 pt[80];
	PolyLine(){num = 0;}
};
class IntRect
{
public: 
  int left, top, right, bott;
  IntRect(){left = top = right = bott = 0;}
  IntRect(int l, int t, int r, int b)
  {left = l; top = t; right = r; bott = b;}
  void set(int l, int t, int r, int b)
  {left = l; top = t; right = r; bott = b;}
  void set(IntRect& r)
  {left = r.left; top = r.top; right = r.right; bott = r.bott;}
};

typedef unsigned char uchar;

class mRGB
{
public: uchar r,g,b,a;
		mRGB(){r = g = b = 0; a = 255;}
		mRGB(mRGB& p){r = p.r; g = p.g; b = p.b; a = p.a;}
		mRGB(uchar rr, uchar gg, uchar bb){r = rr; g = gg; b = bb; 
											if ( (r==255) && (g==255) && (b==255)) a = 0; else a = 255;}
		mRGB(uchar rr, uchar gg, uchar bb, uchar aa){r = rr; g = gg; b = bb; a = aa;}
		void set(uchar rr, uchar gg, uchar bb){r = rr; g = gg; b = bb; 
											if ( (r==255) && (g==255) && (b==255)) a = 0; else a = 255;}
		void set(uchar rr, uchar gg, uchar bb, uchar aa){r = rr; g = gg; b = bb; a = aa;}
};

class RGBpixmap
{
private: 
	mRGB* pixel; //像素队列

public:
	int nRows, nCols; // 像素图维度
	RGBpixmap() {nRows = nCols = 0; pixel = 0;}
	RGBpixmap(int rows, int cols) 
	{
		nRows = rows;
		nCols = cols;
		pixel = new mRGB[rows*cols]; 
	}

	int readBMPFile(string fname, bool hasAlpha); // 将BMP文件读到像素图
	void setTexture(GLuint textureName);

	void freeIt() 
	{
		delete []pixel; nRows = nCols = 0;
	}

	void copy(IntPoint from, IntPoint to, int x, int y, int width, int height)
	{
		if(nRows == 0 || nCols == 0) return;
		glCopyPixels(x, y, width, height,GL_COLOR);
	}

	void draw()
	{ 
		if(nRows == 0 || nCols == 0) return;

		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		glDrawPixels(nCols, nRows,GL_RGBA, GL_UNSIGNED_BYTE,pixel);
	}

	int read(int x, int y, int wid, int ht)
	{ 
		nRows = ht;
		nCols = wid;
		pixel = new mRGB[nRows *nCols];
		if(!pixel) return -1;

		glPixelStorei(GL_PACK_ALIGNMENT,1);
		glReadPixels(x, y, nCols, nRows, GL_RGBA,GL_UNSIGNED_BYTE,pixel);
		return 0;
	}

	int read(IntRect r)
	{
		nRows = r.top - r.bott;
		nCols = r.right - r.left;
		pixel = new mRGB[nRows *nCols]; 
		if(!pixel) return -1;
		glPixelStorei(GL_PACK_ALIGNMENT,1);
		glReadPixels(r.left,r.bott, nCols, nRows, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
		return 0;
	}

	void setPixel(int x, int y, mRGB color)
	{
		if(x>=0 && x <nCols && y >=0 && y < nRows)
			pixel[nCols * y + x] = color;
	}

	mRGB getPixel(int x, int y)
	{ 		
		mRGB bad(255,255,255);
		assert(x >= 0 && x < nCols);
		assert(y >= 0 && y < nRows);
		return pixel[nCols * y + x];
	}
}; 
#endif



