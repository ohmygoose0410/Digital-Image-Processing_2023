#include <vector>
#include <iostream>
#include <cmath>
#include "bitmap.h"

using namespace std;

PixelMatrix flip(const PixelMatrix & org_img) {
  PixelMatrix flip_img;
  // 將影像每一列讀出來，並反向寫回去
  for(int row = 0; row < org_img.size(); row++) {
    vector <Pixel> row_data;

    for(int col = org_img[0].size() - 1; col >= 0; col--) {
      row_data.push_back(org_img[row][col]);
    }
    flip_img.push_back(row_data);
  }
  return flip_img;
}

int main(const int argc, const char* argv[]) {
  BMP image, flip_image;
  PixelMatrix bmp, flip_bmp;
  string filename;

  for (int cnt = 1; cnt < argc; cnt++) {
    cout << argv[cnt] << "\n";
    image.Read(argv[cnt]);

    bool validBmp = image.ValidImage();

    if(validBmp == true) {
      bmp = image.ToPixelMatrix();

      flip_bmp = flip(bmp);

      flip_image.FromPixelMatrix(flip_bmp);
      filename = "output" + to_string(cnt) + "_flip.bmp";
      flip_image.Write(filename, image.existalpha);
    }
  }
  return 0;
}