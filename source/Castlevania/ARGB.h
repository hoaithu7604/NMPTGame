#pragma once
#define RGB_WHITE CARGB(255,255,255,255)
#define RGB_BLACK CARGB(255,0,0,0)
#define RGB_RED CARGB(255,255,0,0)
#define RGB_GREEN CARGB(255,0,255,0)
#define RGB_BLUE CARGB(255,0,0,255)
#define RGB_YELLOW(alpha) CARGB(alpha,255,255,104)

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
	void fade() {
		int delta=51;
		if (red > 0 && blue == 0) {
			red-=delta;
			green += delta;
		}
		if (green> 0 && red == 0) {
			green-=delta;
			blue+=delta;
		}
		if (blue > 0 && green == 0) {
			red+=delta;
			blue-=delta;
		}
	}
	void reset()
	{
		if (red < 0) red = 0;
		if (red > 255) red = 255;
		if (blue < 0) blue = 0;
		if (blue > 255) blue = 255;
		if (green < 0) green = 0;
		if (green > 255) green = 255;
	}
	void loop()
	{
		if (red < 0) red = 255;
		if (red > 255) red = 0;
		if (blue < 0) blue = 255;
		if (blue > 255) blue = 0;
		if (green < 0) green = 255;
		if (green > 255) green = 0;
	}
	void fadetest()
	{
		int value = 15;
		red += value;
		green += value;
		blue += value;
		loop();
	}
};

