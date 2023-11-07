#ifndef _DIP_H_
#define _DIP_H_

#include "define.h"

void AddCol(PixelMatrix &, const PixelVector &, uint16_t);

void AddRow(PixelMatrix &, const PixelVector &, uint16_t);

// pad_type 預設為 'z'，zero padding
PixelMatrix Padding(const PixelMatrix &, const uint16_t, const char);

float dnorm(int, float, float);

PixelMatrix GaussianBlur(const PixelMatrix &, uint16_t, float);

PixelMatrix UnsharpMask(const PixelMatrix &, const uint16_t);

PixelMatrix HistEqual_RGB(const PixelMatrix &);

PixelMatrix HistEqual_HSL(const PixelMatrix &);

PixelMatrix MinMaxStretching(const PixelMatrix & orgPM);

HSLMatrix RGB2HSL(const PixelMatrix &);

PixelMatrix HSL2RGB(const HSLMatrix &);

PixelMatrix MedianFilter(const PixelMatrix & orgPM, const uint16_t kernelSize);
#endif