#ifndef _SCREEN_LAYER
#define _SCREEN_LAYER

#include "util/pch.h"
#include "sconstant.h"

class Pixel {
public:
  Pixel() {
    fgColor = RED;
    bgColor = BLACK;
    ch = TRANSPARENT;
  }
  Pixel(int x_, int y_, int fgc_, int bgc_, char ch_) {
    fgColor = fgc_;
    bgColor = bgc_;
    ch = ch_;
  }
  int fgColor;
  int bgColor;
  char ch;
};

class ILayer {
public:
  virtual void text(int x_, int y_, int fgc_, int bgc_, char ch_) =0;
  //virtual ILayer& color(int clr) =0;
  //virtual ILayer& colorDefault() =0;
  //virtual ILayer& show(const string& s) =0;
  //virtaul ILayer& flush() =0;
};

class Layer : public ILayer {
public:
  Layer();
  Layer(int xOffset_, int yOffset_, int zOrder_);
  virtual ~Layer();
  void text(int x_, int y_, int fgc_, int bgc_, char ch_);
  void text(int x_, int y_, const Pixel& pixel_);
  Pixel& pixel(int x_, int y_); 
  string toString() const;
  virtual void clear() {
    for (int x=0;x<XMAX;x++) {
      for (int y=0;y<YMAX;y++) {
        _pixels[x][y].ch = TRANSPARENT;
      }
    }
  }
  int zOrder() { return _zOrder; }
  int xOffset() { return _xOffset; }
  int yOffset() { return _yOffset; }

private:
  Pixel _pixels[XMAX][YMAX];
  int _xOffset;
  int _yOffset;
  int _zOrder;
  
};

typedef shared_ptr<Layer> SPLayer;

#endif
