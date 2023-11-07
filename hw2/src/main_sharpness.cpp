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

#ifdef DEBUG
int main() {
  VECTOR2D orgPM {{ 1,  2,  3,  4,  5},
                  { 6,  7,  8,  9, 10},
                  {11, 12, 13, 14, 15},
                  {16, 17, 18, 19, 20},
                  {21, 22, 23, 24, 25}};

  VECTOR1D insertRow(5, 0);
  VECTOR1D insertCol(6, 0);
  VECTOR2D resPM;
  generate(insertRow.begin(), insertRow.end(), RandomNumber);
  generate(insertCol.begin(), insertCol.end(), RandomNumber);
  cout << "InsertRow:\n";
  for (int i = 0; i < insertRow.size(); i++) {
    cout << insertRow[i] << " ";
  }
  cout << "\n\n";
  cout << "InsertCol:\n";
  for (int i = 0; i < insertCol.size(); i++) {
    cout << insertCol[i] << " ";
  }
  cout << "\n\n";
  resPM = Padding(orgPM, 2);
  cout << "Result:\n";
  Display(resPM);
}
#else
int main(const int argc, const char* argv[]) {
  BMP orgImage, resImage;
  PixelMatrix orgPM, resPM;
  string filename;

  const uint16_t ratio[2] = {2, 10};
  // const uint16_t ratio[2] = {5, 9};

  for (uint16_t j = 1; j < argc; j++) {
    orgImage.Read(argv[j]);

    bool validBmp = orgImage.ValidImage();

    if(validBmp == true) {
      orgPM = orgImage.ToPixelMatrix();

      for (uint16_t i = 0; i < 2; i++) {
        resPM = UnsharpMask(orgPM, ratio[i]);

        resImage.FromPixelMatrix(resPM);
        filename = "output2_" + to_string(i + 1) + ".bmp";
        resImage.Write(filename, orgImage.existalpha);
      }
    }
  }
  return 0;
}
#endif