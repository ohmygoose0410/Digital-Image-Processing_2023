#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <string>
#include "define.h"

class BMP {
  private:
    PixelMatrix pixels;
    
  public:
    bool existalpha;
    void Read(std::string);
    void Write(std::string, bool);
    bool ValidImage();
    PixelMatrix ToPixelMatrix();
    void FromPixelMatrix(const PixelMatrix &);
};
#endif