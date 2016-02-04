#ifndef _SCREEN_XY
#define _SCREEN_XY

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
    return (l_._x < r_._x);
  }

  bool operator==(const XY& other_) {
    if (_x!=other_._x) return false;
    return _y!=other_._y;
  }

  //XY& operator+=(const XY& xy_) {
  //  _x += xy_.x();
  //  _y += xy_.y();
  //  return *this;
  //}

  void x(int x_);
  void y(int y_);
  void xy(int x_, int y_);
  void xy(const XY& xy_);
  bool touching(const XY& xy_);
  bool touching(int x_, int y_);

  virtual string toString() const;
  int x() const;
  int y() const;

  static XY random(const XY& max);
  static XY random(const XY& min, const XY& max);

protected:
  int _x;
  int _y;

};

typedef vector<XY> XYs;
typedef set<XY> XYSet;

class XYZ {
public:
  XYZ(int x_, int y_, int z_);
  XYZ(const XYZ& xyz_);
  void xyz(int x_, int y_, int z_);
  bool touching(const XYZ& xyz_);
  bool touching(int x_, int y_, int z_);
  bool touchingXY(int x_, int y_);
  bool touchingXY(const XY& xy_);

protected:
  int _x;
  int _y;
  int _z;
};

#endif
