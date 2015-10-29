#include "screen.h"
#include <unistd.h>

Screen::Screen() {
  START("");
  setbuf(stdout, NULL);
  // hide cursor
  printf("\e[?25l");

  tcgetattr(STDIN_FILENO, &_term);
  termios term = _term;
  term.c_lflag &= ~ICANON;
  term.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  END("");
}

Screen::~Screen() {
  START("");
  colorDefault();
  // show cursor
  printf("\e[?25h");
  tcsetattr(STDIN_FILENO, TCSANOW, &_term);
  END("");
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

void Screen::text(int x_, int y_, const Pixel& pixel_) {
  xy(x_, y_).color(pixel_.fgColor).show(pixel_.ch);
}

SPLayer Screen::createLayer(int xOffset_, int yOffset_, int zOrder_) {
  START("");
  SPLayer pLayer = make_shared<Layer>(xOffset_, yOffset_, zOrder_);
  _vpLayers.push_back(pLayer);
  END("");
  return pLayer;
}

void Screen::render() {
  Layer target;
  for (auto & pLayer : _vpLayers) {
    for (int x=0;x<XMAX;x++) {
      for (int y=0;y<YMAX;y++) {
        Pixel& p = pLayer->pixel(x,y);
        Pixel& t = target.pixel(x,y);
        if (p.ch!=TRANSPARENT && p.ch!=BACKGROUND && p.ch!=t.ch) {
          target.text(x, y, p);
        }
      }
    }
  }
  
  for (int x=0;x<XMAX;x++) {
    for (int y=0;y<YMAX;y++) {
      Pixel& p = target.pixel(x,y);
      if (p.ch!=TRANSPARENT) {
        //LOG("") << "render screen:" << x << "," << y << " " << p.ch << LEND;
        text(x, y, p);
      } else {
        text(x, y, 0, 0, ' ');
      }
    }
  }
}
