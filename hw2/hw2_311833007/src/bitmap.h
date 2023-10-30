#include <string>
#include <vector>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef unsigned char uchar_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;

class Pixel {
public:
	int red, green, blue, alpha;

	Pixel() : red(0), green(0), blue(0), alpha(0) { }
	Pixel(int r, int g, int b, int a) : red(r), green(g), blue(b), alpha(a) { }
};

class HSL {
  private:
    float hue2rgb(float, float, float);

  public:
    float hue, saturation, lightness;

    HSL() : hue(0), saturation(0), lightness(0) { }
    HSL(float h, float s, float l) : hue(h), saturation(s), lightness(l) { }

    void fromRGB(const Pixel &);
    Pixel toRGB();
};

typedef std::vector < std::vector <Pixel> > PixelMatrix;
typedef std::vector < std::vector <HSL> > HSLMatrix;

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

bool comp(int, int);