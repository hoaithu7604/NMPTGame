#pragma once
#define RGB_WHITE CARGB(255,255,255,255)
#define RGB_BLACK CARGB(255,0,0,0)
#define RGB_RED CARGB(255,255,0,0)
#define RGB_GREEN CARGB(255,0,255,0)
#define RGB_BLUE CARGB(255,0,0,255)

struct CARGB {
	CARGB() :red(255), green(255), blue(255), alpha(255) {}
	CARGB(int alpha,int red, int green, int blue) :
		red(red), green(green), blue(blue), alpha(alpha) {}
	int red;
	int green;
	int blue;
	int alpha;
	bool operator==(const CARGB& other) { //ignore alpha, may change later
		return this->red == other.red&&this->blue == other.blue&&this->green == other.blue;
	}
};

