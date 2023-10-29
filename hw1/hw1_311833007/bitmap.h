#include <string>
#include <vector>

class Pix {
public:
	int red, green, blue, alpha;

	Pix() : red(0), green(0), blue(0), alpha(0) { }
	Pix(int r, int g, int b, int a) : red(r), green(g), blue(b), alpha(a) { }
};

typedef std::vector < std::vector <Pix> > PixMat;

class BMP {
  private:
    PixMat pixels;
    
  public:
    bool existalpha;
    void Read(std::string);
    void Write(std::string, bool);
    bool ValidImage();
    PixMat ToPixMat();
    void FromPixMat(const PixMat &);
};