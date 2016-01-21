#ifndef _SCREEN_PIXEL
#define _SCREEN_PIXEL

#include "util/pch.h"
#include "sconstant.h"
#include "xy.h"

class Pixel : public XY {
public:
  Pixel() : XY() {
    fgColor = RED;
    bgColor = BLACK;
    ch = TRANSPARENT;
  }
  Pixel(int x_, int y_, int fgc_, int bgc_, char ch_) : XY(x_, y_) {
    fgColor = fgc_;
    bgColor = bgc_;
    ch = ch_;
  }
  Pixel(const XY xy_, int fgc_, int bgc_, char ch_) : XY(xy_) {
    fgColor = fgc_;
    bgColor = bgc_;
    ch = ch_;
  }
  Pixel(const Pixel& pixel_) : XY((XY)pixel_) {
    fgColor = pixel_.fgColor;
    bgColor = pixel_.bgColor;
    ch = pixel_.ch;
  }

  bool operator==(const Pixel& other_) {
    if (!XY::operator==(other_)) return false;
    if (fgColor!=other_.fgColor) return false;
    if (bgColor!=other_.bgColor) return false;
    if (ch!=other_.ch) return false;
    return true;
  }

  void addxy(const XY& xy_) {
    //((XY)*this)+=xy_;
    _x += xy_.x();
    _y += xy_.y();
  }

  int fgColor;
  int bgColor;
  char ch;
};

typedef vector<Pixel> Pixels;
typedef map<XY, Pixel> PixelMap;

#endif
