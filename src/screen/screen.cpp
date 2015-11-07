#include "screen.h"
#include <unistd.h>

Screen::Screen() : _frame0(*this), _frame1(*this) {
  START("");
  _disposed = false;
  _frameInterval = 50;
  END("");
}

Screen::~Screen() {
  START("");
  dispose();
  END("");
}

void Screen::dispose() {
  START("");
  if (!_disposed) {
    colorDefault();
    _disposed = true;
  }
  END("");
}

XY Screen::maxXY() const {
  return XY(80,30);
}

Screen& Screen::xy(int x, int y) {
  printf(ESC33"%d;%dH", y, x);
  return *this;
}

Screen& Screen::color(int clr) {
  int i=clr/100;
  int j=clr%100;
  printf(ESC33"0%d;%dm", i,j);
  return *this;
}

Screen& Screen::colorDefault() {
  printf(ESC33"0m");
  return *this;
}

Screen& Screen::show(const string& s_) {
  printf("%s", s_.c_str());
  return *this;
}

Screen& Screen::show(char ch_) {
  printf("%c", ch_);
  return *this;
}

Screen& Screen::flush() {
  fflush(stdout);
  return *this;
}

void Screen::text(int x_, int y_, int fgc_, int bgc_, char ch_) {
  xy(x_, y_).color(fgc_).show(ch_);
}

void Screen::text(const Pixel& pixel_) {
  xy(pixel_._x, pixel_._y).color(pixel_.fgColor).show(pixel_.ch);
}

SPLayer Screen::createLayer(int xOffset_, int yOffset_, int zOrder_) {
  START("");
  SPLayer pLayer = make_shared<Layer>(*this, xOffset_, yOffset_, zOrder_);
  _vpLayers.push_back(pLayer);
  END("");
  return pLayer;
}

Layer& Screen::current() {
  if (_currentFrame%2==0) {
    return _frame0;
  } else {
    return _frame1;
  } 
}

Layer& Screen::target() {
  if (_currentFrame%2==0) {
    return _frame1;
  } else {
    return _frame0;
  } 
}

void Screen::switchFrame() {
  _currentFrame = (_currentFrame+1)%2;
}

void Screen::render() {

  if (!UTime::pass(_lastRender, _frameInterval)) return;
  _lastRender = UTime::now(); 

  Layer& cur = current();
  Layer& tar = target();
  switchFrame();

  tar.clear();
  for (auto & pLayer : _vpLayers) {
    for (auto & pp: *pLayer) {
      //const XY& xy = pp.first;
      Pixel p = pp.second;
      p._x += pLayer->xOffset();
      p._y += pLayer->yOffset();
      //if (p.ch!=TRANSPARENT && p.ch!=BACKGROUND && p.ch!=t.ch) {
      if (p.ch!=TRANSPARENT && p.ch!=BACKGROUND) {
        tar.text(p);
      }
    }
  }

  for (auto & pp: cur) {
    const XY& xy = pp.first;
    if (!tar.pixel(xy)) {
      Pixel p(xy, BLACK, BLACK, ' ');
      tar.text(p);
    }
  }
  
  for (auto & pp: tar) {
    const XY& xy = pp.first;
    const Pixel& p = pp.second;
    if (p.ch!=TRANSPARENT) {
      auto cp = cur.pixel(xy);
      if (cp) {
        if (cp->ch!=p.ch) {
          text(p);
        }
      } else {
        text(p);
      }
    //} else {
      //text(xy._x, xy._y, 0, 0, ' ');
    }
  }
  
}
