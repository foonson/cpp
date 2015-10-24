#ifndef _SCREEN_SCREEN
#define _SCREEN_SCREEN

#include "util/pch.h"
#include <termios.h>

#define ESC33 "\033["

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
    ch = 0;
  }
  int fgColor;
  int bgColor;
  char ch;
};

class ILayer {
public:
  virtual bool text(int x_, int y_, int fgc_, int bgc_, char ch_) =0;
  //virtual ILayer& color(int clr) =0;
  //virtual ILayer& colorDefault() =0;
  //virtual ILayer& show(const string& s) =0;
  //virtaul ILayer& flush() =0;
};

class Layer : public ILayer {
public:
  Layer() {
    _xOffset = 0;
    _yOffset = 0;
    _zOrder = 0;
  }

  Layer(int xOffset_, int yOffset_, int zOrder_) {
    _xOffset = xOffset_;
    _yOffset = yOffset_;
    _zOrder = zOrder_;
  }

  virtual ~Layer() {
  }
  bool text(int x_, int y_, int fgc_, int bgc_, char ch_) {
    _pixels[x_][y_].ch = ch_;
    return true;
  }
  bool text(int x_, int y_, const Pixel& pixel_) {
    _pixels[x_][y_] = pixel_;
    return true;
  }
  Pixel& pixel(int x_, int y_) {
    return _pixels[x_][y_];
  }

private:
  Pixel _pixels[XMAX][YMAX];
  int _xOffset;
  int _yOffset;
  int _zOrder;
  
};

class Screen : public ILayer{
public:
  Screen();
  ~Screen();
  bool text(int x_, int y_, int fgc_, int bgc_, char ch_) {
    xy(x_, y_).show(ch_);
  }

  bool text(int x_, int y_, const Pixel& pixel_) {
    xy(x_, y_).show(pixel_.ch);
  }

  Layer& createLayer(int xOffset_, int yOffset_, int zOrder_) {
    _vLayers.push_back(Layer(xOffset_, yOffset_, zOrder_));
    return _vLayers.back();
  }

  bool render() {
    Layer target;
    for (Layer& layer : _vLayers) {
      for (int x=0;x<XMAX;x++) {
        for (int y=0;y<YMAX;y++) {
          Pixel& p = layer.pixel(x,y);
          Pixel& t = target.pixel(x,y);
          if (p.ch!=t.ch) {
            target.text(x, y, p);
          }   
        }
      }
    }
    
    for (int x=0;x<XMAX;x++) {
      for (int y=0;y<YMAX;y++) {
        Pixel& p = target.pixel(x,y);
        if (p.ch!=0) {
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
  vector<Layer> _vLayers;
};

#endif
