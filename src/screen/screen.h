#ifndef _SCREEN_SCREEN
#define _SCREEN_SCREEN

#include "util/pch.h"
#include "layer.h"

class Screen : public ILayer{
public:
  Screen();
  virtual ~Screen();
  virtual void dispose();
  void text(int x_, int y_, int fgc_, int bgc_, char ch_);
  void text(const Pixel& pixel_);
  SPLayer createLayer(int xOffset_, int yOffset_, int zOrder_);
  void render(); 
  Screen& xy(int x, int y);
  Screen& color(int clr);
  Screen& colorDefault();
  Screen& show(const string& s);
  Screen& show(char s);
  Screen& flush();

private:
  bool _disposed;
  Layer _current;
  Layer _target;
  vector<shared_ptr<Layer>> _vpLayers;
};

#endif
