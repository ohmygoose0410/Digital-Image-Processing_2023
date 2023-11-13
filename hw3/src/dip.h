#ifndef _DIP_H_
#define _DIP_H_

#include "define.h"

// RGB to YCbCr 係數 (float)
const float YCbCrYRF    = 0.299F;
const float YCbCrYGF    = 0.587F;
const float YCbCrYBF    = 0.114F;
const float YCbCrCbRF   = -0.168736F;
const float YCbCrCbGF   = -0.331264F;
const float YCbCrCbBF   = 0.500000F;
const float YCbCrCrRF   = 0.500000F;
const float YCbCrCrGF   = -0.418688F;
const float YCbCrCrBF   = -0.081312F;

// YCbCr to RGB 係數 (float)
const float RGBRYF  = 1.00000F;
const float RGBRCbF = 0.0000F;
const float RGBRCrF = 1.40200F;
const float RGBGYF  = 1.00000F;
const float RGBGCbF = -0.34414F;
const float RGBGCrF = -0.71414F;
const float RGBBYF  = 1.00000F;
const float RGBBCbF = 1.77200F;
const float RGBBCrF = 0.00000F;

const int Shift = 20;
const int HalfShiftValue = 1 << (Shift - 1);

// RGB to YCbCr 係數 (int)
const int YCbCrYRI  = (int)(YCbCrYRF * (1 << Shift) + 0.5);
const int YCbCrYGI  = (int)(YCbCrYGF * (1 << Shift) + 0.5);
const int YCbCrYBI  = (int)(YCbCrYBF * (1 << Shift) + 0.5);
const int YCbCrCbRI = (int)(YCbCrCbRF * (1 << Shift) + 0.5);
const int YCbCrCbGI = (int)(YCbCrCbGF * (1 << Shift) + 0.5);
const int YCbCrCbBI = (int)(YCbCrCbBF * (1 << Shift) + 0.5);
const int YCbCrCrRI = (int)(YCbCrCrRF * (1 << Shift) + 0.5);
const int YCbCrCrGI = (int)(YCbCrCrGF * (1 << Shift) + 0.5);
const int YCbCrCrBI = (int)(YCbCrCrBF * (1 << Shift) + 0.5);

// YCbCr to RGB 係數 (int)
const int RGBRYI    = (int)(RGBRYF * (1 << Shift) + 0.5);
const int RGBRCbI   = (int)(RGBRCbF * (1 << Shift) + 0.5);
const int RGBRCrI   = (int)(RGBRCrF * (1 << Shift) + 0.5);
const int RGBGYI    = (int)(RGBGYF * (1 << Shift) + 0.5);
const int RGBGCbI   = (int)(RGBGCbF * (1 << Shift) + 0.5);
const int RGBGCrI   = (int)(RGBGCrF * (1 << Shift) + 0.5);
const int RGBBYI    = (int)(RGBBYF * (1 << Shift) + 0.5);
const int RGBBCbI   = (int)(RGBBCbF * (1 << Shift) + 0.5);
const int RGBBCrI   = (int)(RGBBCrF * (1 << Shift) + 0.5);

void AddCol(PixelMatrix &, const PixelVector &, uint16_t);

void AddRow(PixelMatrix &, const PixelVector &, uint16_t);

// pad_type 預設為 'z'，zero padding
PixelMatrix Padding(const PixelMatrix &, const uint16_t, const char);

float dnorm(int, float, float);

PixelMatrix GaussianBlur(const PixelMatrix &, uint16_t, float);

PixelMatrix AdjustLightness(const PixelMatrix & orgPM, const float & value);

PixelMatrix HistEqual_HSL(const PixelMatrix &);

PixelMatrix UnsharpMask(const PixelMatrix &, const uint16_t);

PixelMatrix HistEqual_RGB(const PixelMatrix &);

PixelMatrix RGB2YCbCr(const PixelMatrix &);

PixelMatrix YCbCr2RGB(const PixelMatrix &);

PixelMatrix Rect(const PixelMatrix &, const uint16_t, const uint16_t, const uint16_t, const uint16_t);

std::vector <double> GlobalMean(const PixelMatrix &);

PixelMatrix AutomaticWhiteBalanceMethod(const PixelMatrix &);

void quickSort(std::vector <int> &, int, int);

std::vector <uint16_t> calculatePercentile(const PixelMatrix &, std::vector <uint16_t> &);

PixelMatrix RescaleIntensity(const PixelMatrix & srcPM, const uint16_t newMax, const uint16_t newMin);

PixelMatrix GrayWorldWB(const PixelMatrix & srcPM);
#endif