#ifndef _SCREEN_APPLICATION
#define _SCREEN_APPLICATION

#include "util/pch.h"

#include "screen.h"
#include "keyboard.h"

class Application {

public:

  Application();
  virtual ~Application();

  static void signalHandler(int signum);
  static Application* _pApp;

  void registerSignalHandler();
  virtual void dispose();

  Screen& screen() { return _screen; }
  Keyboard& keyboard() { return _keyboard; }
  bool _exit;

private:
  bool _disposed;
  Screen _screen;
  Keyboard _keyboard;
};

#endif
