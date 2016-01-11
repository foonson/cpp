#include "screen.h"
#include <unistd.h>

Screen::Screen() : _frame0(*this), _frame1(*this), _tick(10) {
  START("");
  _disposed = false;
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

void Screen::clear() {
  color(_body.fgColor, _body.bgColor);
  printf(ESC33"1;1H");
  printf(ESC33"2J");
  _frame0.clear();
  _frame1.clear();
}

XY Screen::maxXY() const {
  return XY(80,30);
}

Screen& Screen::xy(const XY& xy_) {
  return xy(xy_.x(), xy_.y());
}

Screen& Screen::xy(int x_, int y_) {
  printf(ESC33"%d;%dH", y_, x_);
  return *this;
}

Screen& Screen::color(int fgc_, int bgc_) {
  printf(ESC256"%dm", fgc_);
  printf(ESC256B"%dm", bgc_);
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
  xy(x_, y_).color(fgc_, bgc_).show(ch_);
}

void Screen::text(const Pixel& pixel_) {
  xy((XY)pixel_).color(pixel_.fgColor, pixel_.bgColor).show(pixel_.ch);
}

SPLayer Screen::createLayer(const XY& offset_, int zOrder_) {
  START("");
  SPLayer pLayer = make_shared<Layer>(*this, offset_, zOrder_);
  //_vpLayers.push_back(pLayer);
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

void Screen::render(SPLayers vpLayers_) {

  if (!_tick.pass()) return;

  Layer& cur = current();
  Layer& tar = target();
  switchFrame();

  tar.clear();
  for (auto & pLayer : vpLayers_) {
    for (auto & pp: *pLayer) {
      //const XY& xy = pp.first;
      Pixel p = pp.second;
      p.addxy(pLayer->offset());
      //if (p.ch!=TRANSPARENT && p.ch!=BACKGROUND && p.ch!=t.ch) {
      if (p.ch!=TRANSPARENT && p.ch!=BACKGROUND) {
        tar.text(p);
      }
    }
  }

  for (auto & pp: cur) {
    const XY& xy = pp.first;
    if (!tar.pixel(xy)) {
      Pixel p(xy, _body.fgColor, _body.bgColor, ' ');
      tar.text(p);
    }
  }
  
  for (auto & pp: tar) {
    const XY& xy = pp.first;
    const Pixel& p = pp.second;
    if (p.ch!=TRANSPARENT) {
      auto ocp = cur.pixel(xy);
      if (ocp) {
        if (!(*ocp==p)) {
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
