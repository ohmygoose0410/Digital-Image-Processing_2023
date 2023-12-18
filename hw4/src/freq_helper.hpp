#ifndef FREQ_HELPER_H
#define FREQ_HELPER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

cv::Mat computeDFT(cv::Mat);
void fftShift(cv::Mat);
void magnitudeFFT(const cv::Mat &, cv::Mat &);
void imshowFFTSpectrum(std::string, const cv::Mat &);
cv::Mat complexDiv(const cv::Mat &, const cv::Mat &);

#endif
