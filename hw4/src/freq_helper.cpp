#include <iostream>
#include "freq_helper.hpp"

// Compute the Discrete fourier transform
cv::Mat computeDFT(cv::Mat image) {
    cv::Mat padded;                            //expand input image to optimal size
    int m = cv::getOptimalDFTSize( image.rows );
    int n = cv::getOptimalDFTSize( image.cols ); // on the border add zero values
    cv::copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::Mat planes[] = {cv::Mat_<float>(image), cv::Mat::zeros(image.size(), CV_32F)};
    cv::Mat complex;
    cv::merge(planes, 2, complex);         // Add to the expanded another plane with zeros
    cv::dft(complex, complex, cv::DFT_COMPLEX_OUTPUT);  // fourier transform
    return complex;
}

void fftShift(cv::Mat magI) {

    // crop if it has an odd number of rows or columns
    magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

    int cx = magI.cols/2;
    int cy = magI.rows/2;

    cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
    cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
    cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

    cv::Mat tmp;     // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);  // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

void magnitudeFFT(const cv::Mat& complex, cv::Mat& dest)
{
	std::vector<cv::Mat> planes;
	cv::split(complex, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))
	cv::magnitude(planes[0], planes[1], dest); // sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
}

void imshowFFTSpectrum(std::string wname, const cv::Mat & complex)
{
	cv::Mat magI;
	magnitudeFFT(complex, magI);// sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
	
	// switch to logarithmic scale: log(1 + magnitude)
	cv::log(magI+1.0, magI);

	fftShift(magI);
	cv::normalize(magI, magI, 1, 0, cv::NORM_INF); // Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).
	cv::imshow(wname, magI);
    cv::waitKey(0);
}

cv::Mat complexDiv(const cv::Mat & src1, const cv::Mat & src2) {
    const uint16_t height = src1.rows;
  	const uint16_t width = src1.cols;
    
    cv::Mat dstPM(height, width, CV_32FC2, cv::Scalar(0));

    for(uint16_t row=0; row<height; row++) {
        for(uint16_t col=0; col<width; col++) {
            const cv::Vec2f & s1P = src1.at<cv::Vec2f>(row, col);
            const cv::Vec2f & s2P = src2.at<cv::Vec2f>(row, col);
            const float saP = std::pow(s2P[0],2) + std::pow(s2P[1],2);
            cv::Vec2f & dP = dstPM.at<cv::Vec2f>(row, col);
            
            dP[0] = (s1P[0] * s2P[0] + s1P[1] * s2P[1]) / saP;
            dP[1] = (s1P[1] * s2P[0] - s1P[0] * s2P[1]) / saP;
        }
    }

    return dstPM;
}