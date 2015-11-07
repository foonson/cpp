#include "pixel.h"
#include <stdlib.h>

XY::XY(int x_, int y_) {
  //LOG << x_ << "," << y_ << LEND;
  _x = x_;
  _y = y_;
}

XY::XY(const XY& xy_) {
  //LOG << xy_.toString() << LEND;
  _x = xy_._x;
  _y = xy_._y;
}

void XY::xy(int x_, int y_) {
  _x = x_;
  _y = y_;
}

void XY::xy(const XY& xy_) {
  xy( xy_.x(), xy_.y() );
}

int XY::x() const {
  return _x;
}

int XY::y() const {
  return _y;
}

bool XY::touching(const XY& xy_) {
  return touching(xy_.x(), xy_.y()) ;
}

bool XY::touching(int x_, int y_) {
  return (_x==x_) && (_y==y_);
}

string XY::toString() const {
  string s = UString::toString(_x);
  s += ",";
  s += UString::toString(_y);
  return s;
}


XY XY::random(const XY& max_) {
  int x = rand()%max_.x();
  int y = rand()%max_.y();
  return XY(x,y);
}

XY XY::random(const XY& min_, const XY& max_) {
  int x = rand()%(max_.x()-min_.x()) + min_.x();
  int y = rand()%(max_.y()-min_.y()) + min_.y();
  return XY(x,y);
}

XYZ::XYZ(int x_, int y_, int z_) {
  _x = x_;
  _y = y_;
  _z = z_;
}

XYZ::XYZ(const XYZ& xyz_) {
  _x = xyz_._x;
  _y = xyz_._y;
  _z = xyz_._z;
}

void XYZ::xyz(int x_, int y_, int z_) {
  _x = x_;
  _y = y_;
  _z = z_;
}

bool XYZ::touching(const XYZ& xyz_) {
  return (xyz_._x==_x) && (xyz_._y==_y) && (xyz_._z==_z);
}

bool XYZ::touching(int x_, int y_, int z_) {
  return (x_==_x) && (y_==_y) && (z_==_z);
}

bool XYZ::touchingXY(int x_, int y_) {
  return (x_==_x) && (y_==_y);
}

bool XYZ::touchingXY(const XY& xy_) {
  return (xy_._x==_x) && (xy_._y==_y);
}

