#pragma once
typedef unsigned char uch;
typedef unsigned short ush;

class myImage
{
protected:
	uch **inBuf = nullptr;
	ush m_Width = 0;//VS2015 support this expression	
	uch m_Scale = 0;
	uch **outBuf = nullptr;

	void allocation2D();	
	void readFile(char *fileName);//copy to inBuf
public:
	myImage();
	~myImage();
	void deleteInOut2D();
	uch ** getInBuf() { return inBuf; }
	uch ** getOutBuf() { return outBuf; }
	void writeFile(char * fileName);//write using outBuf
	void makeImage(ush width, char * fileName);
};
