#include "stdafx.h"
#include "myImage.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

myImage::myImage() { }//not used

void myImage::makeImage(ush width, char * fileName)
{
	m_Width = width;
	allocation2D();//inbuf, outbuf create
	readFile(fileName);
}

myImage::~myImage()
{ }//not used

void myImage::allocation2D()
{

	inBuf = new uch*[m_Width];
	outBuf = new uch*[m_Width];

	for (ush i = 0; i < m_Width; i++) {
		*(inBuf + i) = new uch[m_Width]{ 0 };
		*(outBuf + i) = new uch[m_Width]{ 0 };
	}
}

void myImage::deleteInOut2D()
{//for destory message, using this func
	if (inBuf != nullptr) {
		for (ush i = 0; i < m_Width; i++) {
			delete[] * (inBuf + i);
			delete[] * (outBuf + i);
		}
	}
	delete outBuf;
	delete inBuf;
}

void myImage::readFile(char * fileName)
{
	FILE *fp;
	fopen_s(&fp, fileName, "rb");
	if (!fp)cout << "Can not open file " << endl;
	for (int i = 0; i < m_Width; i++)
		fread(*(inBuf + i), sizeof(uch), m_Width, fp);
	fclose(fp);
}
void myImage::writeFile(char *fileName)
{
	FILE *fp;
	fopen_s(&fp, fileName, "wb");
	if (!fp)cout << "Can not open file " << endl;
	for (int i = 0; i < m_Width; i++)
		fwrite(*(outBuf + i), sizeof(uch), m_Width, fp);
	fclose(fp);
}