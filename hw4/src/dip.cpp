#include <iostream>
#include <cmath>
#include "dip.h"
#include "freq_helper.hpp"

cv::Mat PM2CV(const PixelMatrix & orgPM) {
	const uint16_t height = orgPM.size();
  	const uint16_t width = orgPM[0].size();

	cv::Mat dstPM = cv::Mat::zeros(height, width, CV_8UC3);
	cv::Mat channels[3];
	
	for (uint16_t row = 0; row < height; row++) {
		for (uint16_t col = 0; col < width; col++) {
			cv::Vec3b & dsPpixel = dstPM.at<cv::Vec3b>(row, col);

			dsPpixel[0] = orgPM[row][col].c1;
			dsPpixel[1] = orgPM[row][col].c2;
			dsPpixel[2] = orgPM[row][col].c3;
		}
	}
	return dstPM;
}

PixelMatrix CV2PM(const cv::Mat & orgPM) {
	const uint16_t height = orgPM.rows;
  	const uint16_t width = orgPM.cols;

	PixelMatrix dstPM;
	
	for (uint16_t row = 0; row < height; row++) {
		PixelVector row_data;
		for (uint16_t col = 0; col < width; col++) {
			Pixel <int> pixel;

			pixel.c1 = (uint8_t)orgPM.at<cv::Vec3b>(row, col)[0];
			pixel.c2 = (uint8_t)orgPM.at<cv::Vec3b>(row, col)[1];
			pixel.c3 = (uint8_t)orgPM.at<cv::Vec3b>(row, col)[2];

			row_data.push_back(pixel);
		}
		dstPM.push_back(row_data);
	}

	return dstPM;
}

float dnorm(int pos, float sd, float mu = 0) {
  return 1 / (sqrt(2 * M_PI) * sd) * exp(-pow(((float)pos - mu) / sd, 2) / 2);
}

cv::Mat GaussianKernel(uint16_t kernelSize, float sd) {
	if (kernelSize % 2 == 0) {
		std::cerr << "[ERROR] Kernel size must be odd sized.\n";
		exit(1);
	}

	cv::Mat kernel1D = cv::Mat::zeros(kernelSize, 1, CV_32F);
	cv::Mat outerProduct;
	int offset = kernelSize / 2;

	float sum = 0;
	for (uint16_t i = 0; i < kernelSize; i++) {
		float & element = kernel1D.at<float>(i, 0);
		element = dnorm((int)(-offset+i), sd);
		sum += element;
	}
	for (uint16_t i = 0; i < kernel1D.rows; i++) {
		kernel1D.at<float>(i, 0) /= sum;
	}
	outerProduct = kernel1D * kernel1D.t();

  return outerProduct;
}

PixelMatrix GaussianDeblur(const PixelMatrix & orgPM, uint16_t kernelSize, float sigma, const float k) {
	const uint16_t height = orgPM.size();
  	const uint16_t width = orgPM[0].size();

	PixelMatrix dstPM;

	cv::Mat inputSD, imgOutput, in_channels[3], out_channels[3];
	inputSD = PM2CV(orgPM);
	cv::copyMakeBorder(inputSD, inputSD, kernelSize, kernelSize, kernelSize, kernelSize, cv::BORDER_REFLECT);
	cv::split(inputSD, in_channels);
	
	cv::Mat kernel = GaussianKernel(kernelSize, sigma);
	cv::copyMakeBorder(kernel, kernel, 0, height+kernelSize, 0, width+kernelSize, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	kernel = computeDFT(kernel);
	cv::Mat psf_dft_abs;
	magnitudeFFT(kernel, psf_dft_abs);
	cv::multiply(psf_dft_abs, psf_dft_abs, psf_dft_abs);
	cv::Mat temp1;
	cv::divide(psf_dft_abs, psf_dft_abs + k, temp1);

	for(uint16_t c = 0; c < 3; c++) {
		cv::Mat t_planes[2], temp2, inputFD;

		inputFD = computeDFT(in_channels[c]);
		temp2 = complexDiv(inputFD, kernel);
		cv::split(temp2, t_planes);
		cv::multiply(t_planes[0], temp1, t_planes[0]);
		cv::multiply(t_planes[1], temp1, t_planes[1]);
		cv::merge(t_planes, 2, inputFD);
		cv::idft(inputFD, inputFD, cv::DFT_REAL_OUTPUT + cv::DFT_SCALE);
		inputFD.convertTo(out_channels[c], CV_8U);
	}
	cv::merge(out_channels, 3, imgOutput);
	imgOutput = imgOutput(cv::Rect(kernelSize, kernelSize, width, height));
	dstPM = CV2PM(imgOutput);

	return dstPM;
}

PixelMatrix MotionDeblur(const PixelMatrix & orgPM, uint16_t kernelSize, int16_t angle,const float k) {
	const uint16_t height = orgPM.size();
  	const uint16_t width = orgPM[0].size();

	PixelMatrix dstPM;

	cv::Mat inputSD, imgOutput, in_channels[3], out_channels[3];
	inputSD = PM2CV(orgPM);
	cv::copyMakeBorder(inputSD, inputSD, kernelSize, kernelSize, kernelSize, kernelSize, cv::BORDER_REFLECT);
	cv::split(inputSD, in_channels);
	cv::Mat kernel = motionKernel(kernelSize, angle);
	cv::copyMakeBorder(kernel, kernel, 0, height+kernelSize, 0, width+kernelSize, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	kernel = computeDFT(kernel);
	cv::Mat psf_dft_abs;
	magnitudeFFT(kernel, psf_dft_abs);
	cv::multiply(psf_dft_abs, psf_dft_abs, psf_dft_abs);
	cv::Mat temp1;
	cv::divide(psf_dft_abs, psf_dft_abs + k, temp1);
	
	for(uint16_t c = 0; c < 3; c++) {
		cv::Mat t_planes[2], temp2, inputFD;

		inputFD = computeDFT(in_channels[c]);
		temp2 = complexDiv(inputFD, kernel);
		cv::split(temp2, t_planes);
		cv::multiply(t_planes[0], temp1, t_planes[0]);
		cv::multiply(t_planes[1], temp1, t_planes[1]);
		cv::merge(t_planes, 2, inputFD);
		cv::idft(inputFD, inputFD, cv::DFT_REAL_OUTPUT + cv::DFT_SCALE);
		inputFD.convertTo(out_channels[c], CV_8U);
	}
	cv::merge(out_channels, 3, imgOutput);
	imgOutput = imgOutput(cv::Rect(kernelSize, kernelSize, width, height));
	dstPM = CV2PM(imgOutput);

	return dstPM;
}

cv::Mat motionKernel(int kernelSize, float angle) {
    cv::Mat kernel = cv::Mat::zeros(kernelSize, kernelSize, CV_32F);

    float directionX = sin(angle * CV_PI / 180.0);
    float directionY = cos(angle * CV_PI / 180.0);

    if (directionX == 0 && directionY == 0) {
        kernel.at<float>(kernelSize / 2, kernelSize / 2) = 1.0;
    } else {
        for (int i = 0; i < kernelSize; ++i) {
            for (int j = 0; j < kernelSize; ++j) {
                float x = j - kernelSize / 2;
                float y = i - kernelSize / 2;
                if (std::abs(x * directionX - y * directionY) < 1.0) {
                    kernel.at<float>(i, j) = 1.0;
                }
            }
        }
    }

    kernel /= cv::sum(kernel)[0];

    return kernel;
}

double PSNR(const PixelMatrix & src1, const PixelMatrix & src2) {
	cv::Mat oriImage = PM2CV(src1);
	cv::Mat resImage = PM2CV(src2);

    cv::Mat diff;
    cv::absdiff(oriImage, resImage, diff);
    diff.convertTo(diff, CV_32F);

    diff = diff.mul(diff);

    cv::Scalar mse = cv::mean(diff);

    if (mse[0] <= 1e-10) {
        return 0.0;
    }

    double maxPixelValue = 255.0;
    double psnr = 10.0 * log10((maxPixelValue * maxPixelValue) / mse[0]); // 计算PSNR

	return psnr;
}