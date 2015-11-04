#ifndef _SCREEN_PIXEL
#define _SCREEN_PIXEL

#include "util/pch.h"
#include "sconstant.h"

class XY {
public:
  XY() {};
  XY(int x_, int y_);
  XY(const XY& xy_);
  friend bool operator<(const XY& l_, const XY& r_) {
    if (l_._y < r_._y) return true;
    if (l_._y > r_._y) return false;
    if (l_._y == r_._y) return (l_._x < r_._x);
    
  }
  void xy(int x_, int y_);
  bool touching(const XY& xy_);
  bool touching(int x_, int y_);

  string toString() const;

  int _x;
  int _y;
};



class XYZ {
public:
  XYZ(int x_, int y_, int z_);
  XYZ(const XYZ& xyz_);
  void xyz(int x_, int y_, int z_);
  bool touching(const XYZ& xyz_);
  bool touching(int x_, int y_, int z_);
  bool touchingXY(int x_, int y_);
  bool touchingXY(const XY& xy_);

  int _x;
  int _y;
  int _z;
};

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

  int fgColor;
  int bgColor;
  char ch;
};

#endif
