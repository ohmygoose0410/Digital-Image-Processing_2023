#include "define.h"

void HSL::fromRGB (const Pixel<int> & pixel) {
	float r = (float)pixel.c1 / 255;
	float g = (float)pixel.c2 / 255;
	float b = (float)pixel.c3 / 255;
	
	float max = MAX(MAX(r, g), b);
	float min = MIN(MIN(r, g), b);

	hue = saturation = lightness = (max + min) / 2;

	if (max == min) {
		hue = saturation = 0;
	}
	else {
		float delta = max - min;
		saturation = lightness > 0.5 ? delta / (2 - max - min) : delta / (max + min);
		if (max == r) {
			hue = (g - b) / delta + (g < b ? 6 : 0);
		}
		else if (max == g) {
			hue = (b - r) / delta + 2;
		}
		else  {
			hue = (r - g) / delta + 4;
		}
		hue /= 6;
	}
}

Pixel<int> HSL::toRGB() {
	Pixel<int> pixel;

	if (saturation == 0) {
		pixel.c1 = pixel.c2 = pixel.c3 = lightness * 255;		
	}
	else {
		float q = lightness < 0.5 ? lightness * (1 + saturation) : lightness + saturation - lightness * saturation;
		float p = 2 * lightness - q;

		pixel.c1 	= hue2rgb(p, q, hue + 1./3) * 255;
		pixel.c2 = hue2rgb(p, q, hue) * 255;
		pixel.c3 	= hue2rgb(p, q, hue - 1./3) * 255;
	}

	return pixel;
}

float HSL::hue2rgb(float p, float q, float t) {
	if (t < 0) t += 1;
	if (t > 1) t -= 1;
	if (t < 1./6) return p + (q - p) * 6 * t;
	if (t < 1./2) return q;
	if (t < 2./3) return p + (q - p) * (2./3 - t) * 6;
	return p;
}