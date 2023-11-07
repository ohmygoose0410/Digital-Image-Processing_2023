#include <vector>
#include <iostream>
#include <cmath>
#include "bitmap.h"

using namespace std;
// ratio填入放大或縮小倍數；若up_down為True，表示放大，False則為縮小
PixelMatrix scaling(const PixelMatrix & org_img, const bool up_down, const float ratio) {
  PixelMatrix scaling_img;
  unsigned int output_width, output_height;
  unsigned int x_l, y_l, x_h, y_h;
  float x_weight, y_weight;
  
  // 若放大就乘上ratio，若縮小則除以ratio
  if (up_down) {
    output_width = (float)org_img[0].size() * ratio;
    output_height = (float)org_img.size() * ratio;
  }
  else {
    output_width = (float)org_img[0].size() / ratio;
    output_height = (float)org_img.size() / ratio;
  }
  // 作業規定寬度要為4的倍數，因此做裁切
  output_width -= output_width % 4;

  for (unsigned int row = 0; row < output_height; row++) {
    vector <Pixel> row_data;

    for (unsigned int col = 0; col < output_width; col++) {
      // 計算mapping回來的pixel位置之周圍4個像素
      if (up_down) {
        x_l = floor((float)col / ratio);
        y_l = floor((float)row / ratio);
        x_h = ceil((float)col / ratio);
        x_h = x_h >= org_img[0].size() ? org_img[0].size() - 1 : x_h;
        y_h = ceil((float)row / ratio);
        y_h = y_h >= org_img.size() ? org_img.size() - 1 : y_h;

        x_weight = ((float)col / ratio) - x_l;
        y_weight = ((float)row / ratio) - y_l;
      }
      else {
        x_l = floor((float)col * ratio);
        y_l = floor((float)row * ratio);
        x_h = ceil((float)col * ratio);
        x_h = x_h >= org_img[0].size() ? org_img[0].size() - 1 : x_h;
        y_h = ceil((float)row * ratio);
        y_h = y_h >= org_img.size() ? org_img.size() - 1 : y_h;
        y_h = ceil((float)row * ratio);

        x_weight = ((float)col * ratio) - x_l;
        y_weight = ((float)row * ratio) - y_l;
      }

      // 下面計算在report中，有給出詳細的圖解，以及公式
      float t_l_area = x_weight * y_weight;
      float t_r_area = (1 - x_weight) * y_weight;
      float b_l_area = x_weight * (1 - y_weight);
      float b_r_area = (1 - x_weight) * (1 - y_weight);

      int red = org_img[y_l][x_l].red * b_r_area +
                org_img[y_l][x_h].red * t_r_area +
                org_img[y_h][x_l].red * b_l_area +
                org_img[y_h][x_h].red * t_l_area;
      int green = org_img[y_l][x_l].green * b_r_area +
                  org_img[y_l][x_h].green * t_r_area +
                  org_img[y_h][x_l].green * b_l_area +
                  org_img[y_h][x_h].green * t_l_area;
      int blue =  org_img[y_l][x_l].blue * b_r_area +
                  org_img[y_l][x_h].blue * t_r_area +
                  org_img[y_h][x_l].blue * b_l_area +
                  org_img[y_h][x_h].blue * t_l_area;
      int alpha = org_img[y_l][x_l].alpha * b_r_area +
                  org_img[y_l][x_h].alpha * t_r_area +
                  org_img[y_h][x_l].alpha * b_l_area +
                  org_img[y_h][x_h].alpha * t_l_area;

      row_data.push_back(Pixel(red, green, blue, alpha));
    }
    scaling_img.push_back(row_data);
  }
  return scaling_img;
}

int main(const int argc, const char* argv[]) {
  BMP image, scaling_image;
  PixelMatrix bmp, scaling_bmp;
  bool up_down[2] = {true, false};
  string filename;

  for (int cnt_1 = 1; cnt_1 < argc; cnt_1++) {
    image.Read(argv[cnt_1]);

    bool validBmp = image.ValidImage();

    if(validBmp == true) {
      bmp = image.ToPixelMatrix();
      for (int cnt_2 = 0; cnt_2 != (sizeof(up_down)/sizeof(up_down[0])); cnt_2++) {
        scaling_bmp = scaling(bmp, up_down[cnt_2], 1.5);
        scaling_image.FromPixelMatrix(scaling_bmp);

        if (up_down[cnt_2]) filename = "output" + to_string(cnt_1) + "_up.bmp";
        else filename = "output" + to_string(cnt_1) + "_down.bmp";
        scaling_image.Write(filename, image.existalpha);
      }
    }
  }
  return 0;
}