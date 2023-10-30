#include <vector>
#include <iostream>
#include <cmath>
#include "bitmap.h"
#include <fstream>

// #define DEBUG

using namespace std;

PixelMatrix HistogramEqualization(const PixelMatrix & orgPixelMatrix) {
  PixelMatrix resPixelMatrix;
  HSLMatrix orgHSLMatrix;

  int histogram[256] = {0};
  int mappingFunction[256] = {0};

  const uint16_t height = orgPixelMatrix.size();
  const uint16_t width = orgPixelMatrix[0].size();
  const uint32_t totalPixel = orgPixelMatrix.size() * orgPixelMatrix[0].size();

  uint32_t cdf = 0;

  for (uint16_t row = 0; row < height; row++) {
    vector <HSL> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel.fromRGB(orgPixelMatrix[row][col]);
      
      row_data.push_back(pixel);
    }
    orgHSLMatrix.push_back(row_data);
  }

  // =================== write file ==================
  #ifdef DEBUG
  ofstream outdata;
  outdata.open("lightness.dat", ofstream::out | ofstream::trunc);
  if( !outdata ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
  #endif


  for (uint16_t row = 0; row < height; row++) {
    for (uint16_t col = 0; col < width; col++) {
      histogram[(int)(orgHSLMatrix[row][col].lightness * 255)]++;
      // #ifdef DEBUG
      // outdata << (int)(orgHSLMatrix[row][col].lightness * 255) << "\n";
      // #endif
    }
  }


  for (uint16_t i = 0; i < 256; i++) {
    cdf += histogram[i];
    mappingFunction[i] = round((float)cdf / totalPixel * 255);
    // if (mappingFunction[i] > 255) {
    //   cout << "idex " << i << " is greater than 255.\n";
    // }
  }

  for (uint16_t row = 0; row < height; row++) {
    vector <Pixel> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel.hue = orgHSLMatrix[row][col].hue;
      pixel.saturation = orgHSLMatrix[row][col].saturation;
      pixel.lightness = (float)mappingFunction[(int)(orgHSLMatrix[row][col].lightness * 255)] / 255;
      #ifdef DEBUG
      outdata << mappingFunction[(int)(orgHSLMatrix[row][col].lightness * 255)] << "\n";
      #endif

      row_data.push_back(pixel.toRGB());
    }
    resPixelMatrix.push_back(row_data);
  }

  #ifdef DEBUG
  outdata.close();
  #endif
  // =================== write file ==================
  return resPixelMatrix;
}

HSLMatrix RGB2HSL(const PixelMatrix & orgPixelMatrix) {
  PixelMatrix resPixelMatrix;
  HSLMatrix orgHSLMatrix;

  const uint16_t height = orgPixelMatrix.size();
  const uint16_t width = orgPixelMatrix[0].size();
  const uint32_t totalPixel = orgPixelMatrix.size() * orgPixelMatrix[0].size();

  for (uint16_t row = 0; row < height; row++) {
    vector <HSL> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;
      
      pixel.fromRGB(orgPixelMatrix[row][col]);

      row_data.push_back(pixel);
    }
    orgHSLMatrix.push_back(row_data);
  }

  return orgHSLMatrix;
}

PixelMatrix HSL2RGB(const HSLMatrix & orgHSLMatrix) {
  PixelMatrix orgPixelMatrix;

  const uint16_t height = orgHSLMatrix.size();
  const uint16_t width = orgHSLMatrix[0].size();
  const uint32_t totalPixel = orgHSLMatrix.size() * orgHSLMatrix[0].size();

  for (uint16_t row = 0; row < height; row++) {
    vector <Pixel> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel = orgHSLMatrix[row][col];
      row_data.push_back(pixel.toRGB());
    }
    orgPixelMatrix.push_back(row_data);
  }

  return orgPixelMatrix;
}

int main(const int argc, const char* argv[]) {
  BMP image, resultImage;
  PixelMatrix orgPixelMatrix;
  string filename;

  HSLMatrix hslMatrix;
  PixelMatrix rgbMatrix;

  for (int cnt = 1; cnt < argc; cnt++) {
    image.Read(argv[cnt]);

    bool validBmp = image.ValidImage();

    if(validBmp == true) {
      orgPixelMatrix = image.ToPixelMatrix();

      // hslMatrix = RGB2HSL(pixelMatrix);
      // rgbMatrix = HSL2RGB(hslMatrix);
      rgbMatrix = HistogramEqualization(orgPixelMatrix);

      resultImage.FromPixelMatrix(rgbMatrix);
      filename = "output" + to_string(cnt) + "_HistogramEqualization.bmp";
      resultImage.Write(filename, image.existalpha);
    }
  }
  return 0;
}