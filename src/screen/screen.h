#ifndef _SCREEN_SCREEN
#define _SCREEN_SCREEN

#include "util/pch.h"
#include <termios.h>

#define ESC33 "\033["


enum {
  TRANSPARENT=0
};

enum COLOR {
  RED=31,
  GREEN=32,
};

enum KEY {
  KEY_NORMAL = 0,
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT
};

class Keyboard {
public:
  bool getKey(KEY& key_, char& ch_) {
    char ch=getchar();
    if (ch==27) {
      ch=getchar();
      if (ch==91) {
        ch=getchar();
        if (ch==65) {
          key_ = KEY_UP;
        } else if (ch==66) {
          key_ = KEY_DOWN;
        } else if (ch==68) {
          key_ = KEY_LEFT;
        } else if (ch==67) {
          key_ = KEY_RIGHT;
        }
      }
    } else {
      key_ = KEY_NORMAL;
      ch_ = ch;
    }
    return true;
  }
};

#define XMAX 80
#define YMAX 24


class Pixel {
public:
  Pixel() {
    fgColor = 0;
    bgColor = 0;
    ch = TRANSPARENT;
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
  Layer() {
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

  Layer(int xOffset_, int yOffset_, int zOrder_) {
    START("");
    _xOffset = xOffset_;
    _yOffset = yOffset_;
    _zOrder = zOrder_;
    LOGFN << toString() << LEND;
    END("");
  }

  virtual ~Layer() {
  }
  void text(int x_, int y_, int fgc_, int bgc_, char ch_) {
    LOGFN << toString() << " " << x_ << "," << y_ << " " << ch_ << LEND; 
    _pixels[x_][y_].ch = ch_;
  }
  void text(int x_, int y_, const Pixel& pixel_) {
    LOGFN << toString() << " " << x_ << "," << y_ << " " << pixel_.ch << LEND; 
    _pixels[x_][y_] = pixel_;
  }
  Pixel& pixel(int x_, int y_) {
    return _pixels[x_][y_];
  }
  string toString() const {
    string s;
    s = "zOrder=";
    s += UString::toString(_zOrder);
    s += " ";
    s += UString::toHexString((unsigned long long)(this));
    return s;
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

class Screen : public ILayer{
public:
  Screen();
  ~Screen();
  void text(int x_, int y_, int fgc_, int bgc_, char ch_) {
    xy(x_, y_).show(ch_);
  }

  void text(int x_, int y_, const Pixel& pixel_) {
    xy(x_, y_).show(pixel_.ch);
  }

  SPLayer createLayer(int xOffset_, int yOffset_, int zOrder_) {
    START("");
    SPLayer pLayer = make_shared<Layer>(xOffset_, yOffset_, zOrder_);
    _vpLayers.push_back(pLayer);
    //LOGFN << l1.toString() << LEND;
    //Layer& l=_vpLayers->back();
    //LOGFN << l.toString() << LEND;
    END("");
    return pLayer;
  }

  void render() {
    Layer target;
    for (auto & pLayer : _vpLayers) {
LOGFN  << pLayer->toString() << LEND; 
      for (int x=0;x<XMAX;x++) {
        for (int y=0;y<YMAX;y++) {
          Pixel& p = pLayer->pixel(x,y);
          Pixel& t = target.pixel(x,y);
LOGFN << pLayer->toString() << " " << x << "," << y << " " << p.ch << LEND;
          if (p.ch!=TRANSPARENT && p.ch!=t.ch) {
            LOG("") << x << "," << y << " " << p.ch << LEND;
            target.text(x, y, p);
          }   
        }
      }
    }
    
    for (int x=0;x<XMAX;x++) {
      for (int y=0;y<YMAX;y++) {
        Pixel& p = target.pixel(x,y);
        if (p.ch!=0) {
          LOG("") << "render screen:" << x << "," << y << " " << p.ch << LEND;
          text(x, y, p);
        }   
      }
    }

  }

  Screen& xy(int x, int y);
  Screen& color(int clr);
  Screen& colorDefault();
  Screen& show(const string& s);
  Screen& show(char s);
  Screen& flush();

private:
  termios _term; 
  vector<shared_ptr<Layer>> _vpLayers;
};

#endif
