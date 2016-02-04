#include "layer.h"
#include "screen.h"

Layer::Layer(const Screen& screen_) : _screen(screen_) {
  //START("");
  _offset = XY(0,0);
  _zOrder = 0;
  //END("");
}
  /*
  Layer(const Layer& layer_) {
    START("");
    LOG << layer_.toString() << LEND;
    LOG << toString() << LEND;
    END("");
  }
  Layer(const Layer&& layer_) {
    START("");
    LOG << layer_.toString() << LEND;
    LOG << toString() << LEND;
    END("");
  }
  */

Layer::Layer(const Screen& screen_, const XY& offset_, int zOrder_) :
  _screen(screen_),
  _offset(offset_)
{
  //START("");
  _zOrder = zOrder_;
  //END("");
}

XY Layer::maxXY() const {
  return _screen.maxXY();
}

Layer::~Layer() {
}

void Layer::clear() {
  _pixels.clear();
}

void Layer::clearDelta() {
  _deltaAdd.clear();
  _deltaRemove.clear();
}

void Layer::renderDelta() {
  for(auto const& xy: _deltaRemove) {
    auto it = _pixels.find(xy);
    if (it!=_pixels.end()) {
      _pixels.erase(it);
    }
  }
  for(auto const& itPixel: _deltaAdd) {
    text(itPixel.second);
  }
  
}

void Layer::text(int x_, int y_, int fgc_, int bgc_, char ch_) {
  Pixel p;
  p.xy(x_, y_);
  p.ch = ch_;
  p.fgColor = fgc_;
  p.bgColor = bgc_;
  text(p);
}

void Layer::text(const XY& xy_, int fgc_, int bgc_, char ch_) {
  Pixel p;
  p.xy(xy_);
  p.ch = ch_;
  p.fgColor = fgc_;
  p.bgColor = bgc_;
  text(p);
}

void Layer::text(int x_, int y_, int fgc_, int bgc_, const string& s_) {
  int x = x_;
  for (auto& ch:s_) {
    text(x, y_, fgc_, bgc_, ch);
    x++;
  }
}

void Layer::text(int x_, int y_, const Pixel& pixel_) {
  return text(XY(x_,y_), pixel_);
}

void Layer::text(const XY& xy_, const Pixel& pixel_) {
  Pixel p(pixel_);
  p.xy(xy_);
  return text(p);
}

void Layer::text(const Pixel& pixel_) {
  //LOG << toString() << " " << x_ << "," << y_ << " " << pixel_.ch << LEND; 
  //if (_pixels.find(xy_)!=_pixels.end()) {
    _pixels[(XY)pixel_] = pixel_;
  //} else {
  //}
}

void Layer::deltaAdd(const Pixel& pixel_) {
  //_deltaAdd.push_back(pixel_);
  _deltaAdd[(XY)pixel_] = pixel_;
}

void Layer::deltaRemove(const XY& xy_) {
  //_deltaRemove.push_back(xy_);
  _deltaRemove.insert(xy_);
}

optional<Pixel> Layer::pixel(const XY& xy_) {
  if (_pixels.find(xy_)==_pixels.end()) {
    return std::experimental::nullopt;
  }
  return optional<Pixel>(_pixels[xy_]);
}

string Layer::toString() const {
  string s;
  s = "zOrder=" + UString::toString(_zOrder) 
      + " " + UString::toHexString((unsigned long long)(this))
      + " len=" + UString::toString(_pixels.size())
  ;
  return s;
}

PixelMap::iterator Layer::begin() {
  return _pixels.begin();
} 

PixelMap::iterator Layer::end() {
  return _pixels.end();
} 

