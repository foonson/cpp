#ifndef _SCREEN_SCREEN
#define _SCREEN_SCREEN

#include "util/pch.h"
#include "util/tick.h"
#include "layer.h"
#include "util/idispose.h"

class IScreen {
  virtual void render(SPLayers vpLayers_) = 0; 
};

class Screen : public IScreen, public ILayer, private IDispose {
public:
  Screen();
  virtual ~Screen();

  // IScreen
  virtual void render(SPLayers vpLayers_); 

  // IDispose
  virtual void dispose();

  XY maxXY() const;

  void clear();
  void text(int x_, int y_, int fgc_, int bgc_, char ch_);
  void text(const Pixel& pixel_);
  SPLayer createLayer(int xOffset_, int yOffset_, int zOrder_);
  SPLayer createLayer(const XY& offset_, int zOrder_);
  Screen& xy(int x_, int y_);
  Screen& xy(const XY& xy_);
  Screen& color(int fgc_, int bgc_);
  Screen& colorDefault();
  Screen& show(const string& s);
  Screen& show(char s);
  Screen& flush();

  Layer& current();
  Layer& target();
  void switchFrame();

  void body(const Pixel& body_) { _body = body_; }
  Pixel body() { return _body; }

private:
  int _currentFrame;
  Layer _frame0;
  Layer _frame1;
  //vector<shared_ptr<Layer>> _vpLayers;
  //Tick _tick;
  Pixel _body;
};

#endif
