#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <argparse/argparse.hpp>
#include "define.h"
#include "dip.h"
#include "bitmap.h"
#include "argparse.h"

using namespace std;

int RandomNumber()
{
	return (rand() % 100);
}

int main(const int argc, const char** argv)
{
	BMP orgImage, resImage;
	PixelMatrix srcPM, motionDeblurPM, gaussianDeblurPM, goldenPM;

	string srcPath, goldPath;
	uint16_t mSize;
	int16_t mAngle;
	float mK;
	uint16_t gSize;
	float gSigma;
	float gK;

	// parse and save command line args
    int parse_result = parse_arguments(
        argc, argv,
		&goldPath,
		&srcPath,
        &mSize,
        &mAngle,
        &mK,
        &gSize,
        &gSigma,
        &gK
    );

	if (parse_result != 1) return parse_result;
	
	orgImage.Read(srcPath);

	bool validBmp = orgImage.ValidImage();

	if (validBmp == true)
	{
		srcPM = orgImage.ToPixelMatrix();

		motionDeblurPM = MotionDeblur(srcPM, mSize, mAngle, mK);
		gaussianDeblurPM = GaussianDeblur(motionDeblurPM, gSize, gSigma, gK);

		if(!goldPath.empty()) 
		{
			orgImage.Read(goldPath);
			validBmp = orgImage.ValidImage();
			if (validBmp == true)
			{
				goldenPM = orgImage.ToPixelMatrix();
				printf("PSNR: %f\n", PSNR(goldenPM, gaussianDeblurPM));
			}
		}

		resImage.FromPixelMatrix(gaussianDeblurPM);
		string imageIndex{srcPath[srcPath.find(".bmp")-1]};
		string tarPath = "output" + imageIndex + ".bmp";
		resImage.Write(tarPath, orgImage.existalpha);
	}

	return 0;
}