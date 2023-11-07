#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "bitmap.h"
#include "define.h"
#include "dip.h"

using namespace std;

int main(const int argc, const char* argv[]) {
  BMP orgImage, resImage;
  PixelMatrix orgPM, resPM;
  string filename;

  const uint16_t kernelSize[2] = {5, 9};

  for (uint16_t j = 1; j < argc; j++) {
    orgImage.Read(argv[j]);

    bool validBmp = orgImage.ValidImage();

    if(validBmp == true) {
      orgPM = orgImage.ToPixelMatrix();

      for (uint16_t i = 0; i < 2; i++) {
        resPM = Padding(orgPM, kernelSize[i] / 2, 'e');
        resPM = GaussianBlur(resPM, kernelSize[i], 10);

        resImage.FromPixelMatrix(resPM);
        filename = "output3_" + to_string(i + 1) + ".bmp";
        resImage.Write(filename, orgImage.existalpha);
      }
    }
  }
  return 0;
}