// RGBpixmap.cpp -读取BitMap文件
#include "RGBpixmap.h"

typedef unsigned short ushort;
typedef unsigned long ulong;
fstream inf; 

ushort getShort() 
{
		char ic;
		ushort ip;
		inf.get(ic); ip = ic;  
		inf.get(ic);  ip |= ((ushort)ic << 8); 
		return ip;
}

ulong getLong() 
{  
		ulong ip = 0;
		char ic = 0;
		unsigned char uc = ic;
		inf.get(ic); uc = ic; ip = uc;
		inf.get(ic); uc = ic; ip |=((ulong)uc << 8);
		inf.get(ic); uc = ic; ip |=((ulong)uc << 16);
		inf.get(ic); uc = ic; ip |=((ulong)uc << 24);
		return ip;
	}
int RGBpixmap:: readBMPFile(string fname, bool hasAlpha) 
{  
	// 读取BMP文件
	inf.open(fname.c_str(), ios::in|ios::binary); 
	if(!inf) { cout << " can't open file: " << fname << endl; return 0; }
	int k, row, col, numPadBytes, nBytesInRow;

	
	char ch1, ch2;
	inf.get(ch1);
	inf.get(ch2);						//类型: BM
	ulong fileSize      = getLong();
	ushort reserved1    = getShort();	
	ushort reserved2    = getShort();	
	ulong offBits       = getLong();	
	ulong headerSize    = getLong();	
	ulong numCols       = getLong();	// 图片的像素列
	ulong numRows       = getLong();	// 图片的像素行
	ushort planes       = getShort();	 
	ushort bitsPerPixel = getShort();	//位深
	ulong compression   = getLong();	
	ulong imageSize     = getLong();	// 图片像素数
	ulong xPels         = getLong();	
	ulong yPels         = getLong();	
	ulong numLUTentries = getLong();	
	ulong impColors     = getLong();	

	if(bitsPerPixel != 24) 
	{
		cout << "not a 24 bit/pixelimage, or is compressed!\n";
		inf.close();
		return 0;
	} 

	
	nBytesInRow = ((3 * numCols + 3)/4) * 4;
	numPadBytes = nBytesInRow - 3 * numCols; 
	nRows = numRows; 
	nCols = numCols;
	pixel = new mRGB[nRows * nCols];
	if (!pixel)
		return 0;

	long count = 0;
	char dum;
	for(row = 0; row < nRows; row++) // 读取像素值
	{
		for(col = 0; col < nCols; col++)
		{
			char r,g,b;
			inf.get(b);
			inf.get(g);
			inf.get(r); //读取字节
			pixel[count].r = r; 
			pixel[count].g = g;
			pixel[count].b = b;
			if ( (hasAlpha) && (r==-1) && (g==-1) && (b==-1) )
				pixel[count++].a = 0;
			else
				pixel[count++].a = 255;
		}
   		for(k = 0; k < numPadBytes ; k++) 
			inf >> dum;
	}
	inf.close();
	return 1; // 成功
}

void RGBpixmap :: setTexture(GLuint textureName)
{
	glBindTexture(GL_TEXTURE_2D,textureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nCols, nRows,0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
}

