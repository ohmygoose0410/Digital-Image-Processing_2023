#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <vector>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define CLAMP(src) ((src) > 255 ? 255 : ((src) < 0 ? 0 : src))

typedef unsigned char uchar_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;

template <class T> class Pixel {
public:
	T red, green, blue, alpha;

	Pixel() : red(0), green(0), blue(0), alpha(0) { }
	Pixel(T r, T g, T b, T a) : red(r), green(g), blue(b), alpha(a) { }
};

class HSL {
  private:
    float hue2rgb(float, float, float);

  public:
    float hue, saturation, lightness;

    HSL() : hue(0), saturation(0), lightness(0) { }
    HSL(float h, float s, float l) : hue(h), saturation(s), lightness(l) { }

    void fromRGB(const Pixel<int> &);
    Pixel<int> toRGB();
};

typedef std::vector <std::vector <Pixel<int>>> PixelMatrix;
typedef std::vector <Pixel<int>> PixelVector;
typedef std::vector <std::vector <HSL>> HSLMatrix;

#endif