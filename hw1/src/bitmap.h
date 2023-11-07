#include <string>
#include <vector>

class Pixel {
public:
	int red, green, blue, alpha;

	Pixel() : red(0), green(0), blue(0), alpha(0) { }
	Pixel(int r, int g, int b, int a) : red(r), green(g), blue(b), alpha(a) { }
};

typedef std::vector < std::vector <Pixel> > PixelMatrix;

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