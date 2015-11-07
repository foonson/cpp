#ifndef _SCREEN_LAYER
#define _SCREEN_LAYER

#include "util/pch.h"
#include "sconstant.h"
#include "pixel.h"
//#include "screen.h"

class Screen;

class ILayer {
public:
  virtual void text(int x_, int y_, int fgc_, int bgc_, char ch_) =0;
  virtual XY maxXY() const =0 ;
  //virtual ILayer& color(int clr) =0;
  //virtual ILayer& colorDefault() =0;
  //virtual ILayer& show(const string& s) =0;
  //virtaul ILayer& flush() =0;
};

typedef map<XY, Pixel> PixelMap;

class Layer : public ILayer {
public:
  Layer(const Screen& screen_);
  Layer(const Screen& screen_, int xOffset_, int yOffset_, int zOrder_);
  virtual ~Layer();
  string toString() const;
  virtual void clear();

  XY maxXY() const;

  void text(int x_, int y_, int fgc_, int bgc_, char ch_);
  void text(int x_, int y_, int fgc_, int bgc_, const string& s_);
  void text(int x_, int y_, const Pixel& pixel_);
  void text(const XY& xy_, const Pixel& pixel_);
  void text(const Pixel& pixel_);
  //const Pixel& pixel(int x_, int y_); 
  optional<Pixel> pixel(const XY& xy_); 

  PixelMap::iterator begin();  
  PixelMap::iterator end();  

  int zOrder() { return _zOrder; }
  int xOffset() { return _xOffset; }
  int yOffset() { return _yOffset; }

  const Screen& _screen;
private:
  PixelMap _pixels;
  //Pixel _pixels[XMAX][YMAX];
  int _xOffset;
  int _yOffset;
  int _zOrder;
  
};

typedef shared_ptr<Layer> SPLayer;

#endif
