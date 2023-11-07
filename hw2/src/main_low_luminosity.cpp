#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "bitmap.h"
#include "dip.h"
#include "define.h"

using namespace std;

int main(const int argc, const char* argv[]) {
  BMP image, resultImage;
  PixelMatrix orgPixelMatrix;
  string filename;

  HSLMatrix hslMatrix;
  PixelMatrix resPM;

  for (int cnt = 1; cnt < argc; cnt++) {
    image.Read(argv[cnt]);

    bool validBmp = image.ValidImage();

    if(validBmp == true) {
      orgPixelMatrix = image.ToPixelMatrix();

      for (uint16_t i = 0; i < 2; i++) {
        switch(i) {
          case 0:
            resPM = HistEqual_RGB(orgPixelMatrix);
            break;
          case 1:
            resPM = HistEqual_HSL(orgPixelMatrix);
            break;
        }

        resultImage.FromPixelMatrix(resPM);
        filename = "output1_" + to_string(i+1) + ".bmp";
        resultImage.Write(filename, image.existalpha);
      }
    }
  }
  return 0;
}