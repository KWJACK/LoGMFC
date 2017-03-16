#include "stdafx.h"
#include "LoG.h"
#include <algorithm>
//https://docs.gimp.org/ko/plug-in-convmatrix.html
#define PSIZE 516 //padding size
LoG::LoG()
{
	temp = new uch*[PSIZE];
	memSign = new char*[PSIZE];
	for (ush i = 0; i < PSIZE; i++) {
		*(temp + i) = new uch[PSIZE]{ 0 };
		*(memSign + i) = new char[PSIZE];//default 1 ->positive
		std::fill_n(*(memSign + i), PSIZE, 1);
	}
}

LoG::~LoG()
{}
void LoG::deleteLoG() {
	if (temp != nullptr && memSign != nullptr) {
		for (ush i = 0; i < PSIZE; i++) {
			delete[] * (temp + i);
			delete[] * (memSign + i);
		}
		delete temp;
		delete memSign;
	}
}

void LoG::exLog(int opt)
{
	//copy original
	for (ush h = 2; h < PSIZE - 2; h++) {
		for (ush w = 2; w < PSIZE - 2; w++) {
			temp[h][w] = inBuf[h - 2][w - 2];
		}
	}
	//padding
	for (ush h = 0; h < 2; h++) {
		for (ush w = 2; w < PSIZE - 2; w++) {
			temp[h][w] = temp[2][w];//up
			temp[w][h] = temp[w][2];//left
			temp[PSIZE - 2 + h][w] = temp[PSIZE - 3][w];//bottom			
			temp[w][PSIZE - 2 + h] = temp[w][PSIZE - 3];//right
		}
	}
	//edge padding
	temp[1][1] = inBuf[0][0];
	temp[1][PSIZE - 2] = inBuf[0][m_Width - 1];
	temp[PSIZE - 2][1] = inBuf[m_Width - 1][0];
	temp[PSIZE - 2][PSIZE - 2] = inBuf[m_Width - 1][m_Width - 1];
	//LoG filter http://fourier.eng.hmc.edu/e161/lectures/gradient/node8.html
	for (ush h = 2; h<PSIZE - 2; h++) {
		for (ush w = 2; w<PSIZE - 2; w++) {
			int val =
				(int)(temp[h - 2][w]
					+ temp[h - 1][w - 1]
					+ 2*temp[h - 1][w]
					+ temp[h - 1][w + 1]

					+ temp[h][w - 2]
					+ 2 *temp[h][w - 1]
					- 16 * temp[h][w]
					+ 2 * temp[h][w + 1]
					+ temp[h][w + 2]

					+ temp[h + 1][w - 1]
					+ 2 * temp[h + 1][w]
					+ temp[h + 1][w + 1]
					+ temp[h + 2][w]);			
			if (val < 0) {//in case of not dominant [h][w]
				val = 0;//
				memSign[h-2][w-2] = -1;
			}
			else if (val > 255) {//in case of val<0,means dominant->edge
				val = 255;
			}
			outBuf[h - 2][w - 2] = (uch)val;//converted value			
		}
	}
	if (opt) {//opt 1 means zero crossing
		for (ush h = 2; h < m_Width-2; h+=2) {//except boundary
			for (ush w = 2; w < m_Width-2; w+=2) {//RGB black -> 0, RGB white -> 255
				if (outBuf[h][w]>0 ) {//zero crossing
					if ((memSign[h+2][w + 2 + 1] * memSign[h + 2][w + 2 - 1] < 0) ||
						(memSign[h + 2 + 1][w + 2] * memSign[h + 2 - 1][w + 2] < 0) ||
						(memSign[h + 2 + 1][w + 2 +1] * memSign[h + 2 - 1][w + 2 -1] < 0) ||
						(memSign[h + 2 + 1][w + 2 -1] * memSign[h + 2 - 1][w + 2 +1] < 0)) {
						outBuf[h-1][w-1] = 0 ;
					}
					//noise elimanate
					if (!(outBuf[h + 1][w]) && !(outBuf[h][w - 1]) && !(outBuf[h][w + 1]) && !(outBuf[h - 1][w])) {//sign check
						outBuf[h][w] = 0;//turn on black						
					}
					if (!(outBuf[h + 1][w + 1]) && !(outBuf[h - 1][w - 1]) && !(outBuf[h - 1][w + 1]) && !(outBuf[h + 1][w - 1]))
					{
						outBuf[h][w] = 0;//turn on black
					}
					
				}

			}
		}
	}//opt
}
