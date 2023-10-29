#include <vector>
#include <iostream>
#include <cmath>
#include "bitmap.h"

using namespace std;
// bits輸入要降解析的目標bit值
PixMat quantization(const PixMat & org_img, const int bits) {
  PixMat quan_img = org_img;
  // 產生bitmaskt -> 2^8 - 2^(8 - bits)
  int bitmask = pow(2, 8) - pow(2, (8 - bits));

  for(int row = org_img.size() - 1; row >= 0; row--) {
    vector <Pix> & row_data = quan_img[row];

    for(int col = 0; col < row_data.size(); col++) {
      Pix & pix = row_data[col];
      // 將pixel value與bitmask做and operation
      pix.blue  = pix.blue & bitmask;
      pix.green = pix.green & bitmask;
      pix.red   = pix.red & bitmask;
    }
  }
  return quan_img;
}

int main(const int argc, const char* argv[]) {
  BMP image, quan_image;
  PixMat bmp, quan_bmp;
  int levels[3] = {6, 4, 2};
  string filename;

  for (int cnt = 1; cnt < argc; cnt++) {
    image.Read(argv[cnt]);

    bool validBmp = image.ValidImage();

    if(validBmp == true) {
      bmp = image.ToPixMat();
      for (int level = 0; level != (sizeof(levels)/sizeof(levels[0])); level++) {
        quan_bmp = quantization(bmp, levels[level]);

        quan_image.FromPixMat(quan_bmp);
        filename = "output" + to_string(cnt) + "_" + to_string(level + 1) + ".bmp";
        quan_image.Write(filename, image.existalpha);
      }
    }
  }
  return 0;
}