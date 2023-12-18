#ifndef _DIP_H_
#define _DIP_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "define.h"

cv::Mat PM2CV(const PixelMatrix &);

PixelMatrix CV2PM(const cv::Mat &);

PixelMatrix MotionDeblur(const PixelMatrix &, uint16_t, int16_t, float);

cv::Mat motionKernel(int, float);

float dnorm(int, float, float);

cv::Mat GaussianKernel(uint16_t, float);

PixelMatrix GaussianDeblur(const PixelMatrix &, uint16_t, float, const float);

double PSNR(const PixelMatrix &, const PixelMatrix &);
#endif