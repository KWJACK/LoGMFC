#pragma once
#include "myImage.h"
class LoG : public myImage
{
private:
	uch **temp;
	char **memSign;
public:
	LoG();
	~LoG();
	void deleteLoG();
	void exLog(int opt);
};

