#ifndef _SCREEN_SCREEN
#define _SCREEN_SCREEN

#include "util/pch.h"
#include "util/tick.h"
#include "layer.h"

class Screen : public ILayer{
public:
  Screen();
  virtual ~Screen();
  virtual void dispose();
  XY maxXY() const;

  void clear();
  void text(int x_, int y_, int fgc_, int bgc_, char ch_);
  void text(const Pixel& pixel_);
  SPLayer createLayer(int xOffset_, int yOffset_, int zOrder_);
  SPLayer createLayer(const XY& offset_, int zOrder_);
  void render(); 
  Screen& xy(int x, int y);
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
  bool _disposed;
  int _currentFrame;
  Layer _frame0;
  Layer _frame1;
  vector<shared_ptr<Layer>> _vpLayers;
  Tick _tick;
  Pixel _body;
};

#endif
