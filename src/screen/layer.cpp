#include "layer.h"

Layer::Layer() {
  START("");
  _xOffset = 0;
  _yOffset = 0;
  _zOrder = 0;
  LOGFN << toString() << LEND;
  END("");
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
  START("");
  _xOffset = xOffset_;
  _yOffset = yOffset_;
  _zOrder = zOrder_;
  LOGFN << toString() << LEND;
  END("");
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

