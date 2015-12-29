#ifndef _SCREEN_APPLICATION
#define _SCREEN_APPLICATION

#include "util/pch.h"

#include <thread>
#include "screen.h"
#include "keyboard.h"
#include "key.h"
#include "evalGroup.h"
#include "util/syncQueue"

class Application {

public:

  Application();
  virtual ~Application();

  static void signalHandler(int signum);
  static Application* _pApp;

  void registerSignalHandler();
  virtual void dispose();

  void evaluateLoop();
  void listenCommandLoop();
  //void renderLoop();
  void startThreads();

  vector<SPEvalGroup>& evalGroups() { return _vpEvalGroups; }
  Screen& screen() { return _screen; }
  Keyboard& keyboard() { return _keyboard; }
  bool _exit;

  //void addKeyListener(SPKeyListener listener_) {
  //  _vpKeyListeners.push_back(listener_);
  //}
  void addEvalGroup(SPEvalGroup pEvalGroup_) {
    _vpEvalGroups.push_back(pEvalGroup_);
  }

private:
  bool _disposed;
  Screen _screen;
  Keyboard _keyboard;

  //vector<SPKeyListener> _vpKeyListeners;
  vector<SPEvalGroup> _vpEvalGroups;
  SyncQueue<Key> _queueKey;
};

#endif
