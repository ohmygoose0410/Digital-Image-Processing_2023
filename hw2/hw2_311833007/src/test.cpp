#include <vector>
#include <iostream>
#include <cmath>
#include "bitmap.h"

using namespace std;

int main() {
    int32_t R = 125;
    int32_t G = 135;
    int32_t B = 145;
    int32_t A = 155;

    Pixel test_pixel(R, G, B, A);
    Pixel valid_pixel;
    HSL test_HSL;

    test_HSL.fromRGB(test_pixel);
    valid_pixel = test_HSL.toRGB();

    cout << "hue:" << test_HSL.hue << "\n";
    cout << "saturation:" << test_HSL.saturation << "\n";
    cout << "lightness:" << test_HSL.lightness << "\n";

    cout << "red:" << valid_pixel.red << "\n";
    cout << "green:" << valid_pixel.green << "\n";
    cout << "blue:" << valid_pixel.blue << "\n";
    return 0;
}