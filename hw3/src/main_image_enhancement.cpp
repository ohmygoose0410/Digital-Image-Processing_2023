#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "define.h"
#include "dip.h"
#include "bitmap.h"

using namespace std;

int RandomNumber() {
  return (rand() % 100);
}

int main(const int argc, const char* argv[]) {
  BMP orgImage, resImage;
  PixelMatrix srcPM, dstPM, ycrcbPM;
  string filename;

  for (uint16_t j = 1; j < argc; j++) {
    orgImage.Read(argv[j]);

    bool validBmp = orgImage.ValidImage();

    if(validBmp == true) {
      srcPM = orgImage.ToPixelMatrix();

      dstPM = RescaleIntensity(srcPM, 255, 25);

      resImage.FromPixelMatrix(dstPM);
      filename = "output" + to_string(j) + "_2" + ".bmp";
      resImage.Write(filename, orgImage.existalpha);
    }
  }
  return 0;
}