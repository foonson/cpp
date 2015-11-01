#include "layer.h"

XY::XY(int x_, int y_) {
  LOGFN << x_ << "," << y_ << LEND;
  _x = x_;
  _y = y_;
}

XY::XY(const XY& xy_) {
  LOGFN << xy_.toString() << LEND;
  _x = xy_._x;
  _y = xy_._y;
}

void XY::xy(int x_, int y_) {
  _x = x_;
  _y = y_;
}

bool XY::touching(const XY& xy_) {
  return (xy_._x==_x) && (xy_._y==_y);
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


Layer::Layer() {
  //START("");
  _xOffset = 0;
  _yOffset = 0;
  _zOrder = 0;
  //LOGFN << toString() << LEND;
  //END("");
}

  /*
  Layer(const Layer& layer_) {
    START("");
    LOGFN << layer_.toString() << LEND;
    LOGFN << toString() << LEND;
    END("");
  }
  Layer(const Layer&& layer_) {
    START("");
    LOGFN << layer_.toString() << LEND;
    LOGFN << toString() << LEND;
    END("");
  }
  */

Layer::Layer(int xOffset_, int yOffset_, int zOrder_) {
  //START("");
  _xOffset = xOffset_;
  _yOffset = yOffset_;
  _zOrder = zOrder_;
  //LOGFN << toString() << LEND;
  //END("");
}

Layer::~Layer() {
}

void Layer::text(int x_, int y_, int fgc_, int bgc_, char ch_) {
  //LOGFN << toString() << " " << x_ << "," << y_ << " " << ch_ << LEND; 
  _pixels[x_][y_].ch = ch_;
  _pixels[x_][y_].fgColor = fgc_;
  _pixels[x_][y_].bgColor = bgc_;
}

void Layer::text(int x_, int y_, const Pixel& pixel_) {
  //LOGFN << toString() << " " << x_ << "," << y_ << " " << pixel_.ch << LEND; 
  _pixels[x_][y_] = pixel_;
}

Pixel& Layer::pixel(int x_, int y_) {
  return _pixels[x_][y_];
}

string Layer::toString() const {
  string s;
  s = "zOrder=";
  s += UString::toString(_zOrder);
  s += " ";
  s += UString::toHexString((unsigned long long)(this));
  return s;
}

/*
int Layer::zOrder() { return _zOrder; }
int Layer::xOffset() { return _xOffset; }
int Layer::yOffset() { return _yOffset; }
*/

