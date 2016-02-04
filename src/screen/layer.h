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


class Layer : public ILayer {
public:
  Layer(const Screen& screen_);
  Layer(const Screen& screen_, const XY& offset_, int zOrder_);
  virtual ~Layer();
  string toString() const;
  virtual void clear();
  virtual void clearDelta();
  //virtual void clearPixel(const Pixel& pixel_);

  XY maxXY() const;

  void renderDelta();
  void text(int x_, int y_, int fgc_, int bgc_, char ch_);
  void text(int x_, int y_, int fgc_, int bgc_, const string& s_);
  void text(int x_, int y_, const Pixel& pixel_);
  void text(const XY& xy_, int fgc_, int bgc_, char ch_);
  void text(const XY& xy_, const Pixel& pixel_);
  void text(const Pixel& pixel_);
  optional<Pixel> pixel(const XY& xy_); 

  PixelMap::iterator begin();  
  PixelMap::iterator end();  

  void deltaAdd(const Pixel& pixel_);
  void deltaRemove(const XY& xy_);

  const XY& offset() { return _offset; }
  int zOrder() { return _zOrder; }

private:
  const Screen& _screen;
  PixelMap _pixels;
  XY _offset;
  int _zOrder;

  PixelMap _deltaAdd;
  XYSet _deltaRemove;
  
};

typedef shared_ptr<Layer> SPLayer;
typedef vector<SPLayer> SPLayers;

#endif
