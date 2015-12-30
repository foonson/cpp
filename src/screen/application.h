#ifndef _SCREEN_APPLICATION
#define _SCREEN_APPLICATION

#include "util/pch.h"

#include <thread>
#include "screen.h"
#include "keyboard.h"
#include "key.h"
#include "ikeyListener.h"
#include "util/idispose.h"
#include "evalGroup.h"
#include "util/syncQueue"

class Application : private IKeyListener, private IDispose {

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

  void addEvalGroup(SPEvalGroup pEvalGroup_) {
    _vpEvalGroups.push_back(pEvalGroup_);
  }

  void sound(const string& pathName_);

protected:
  bool _exit;

private:
  //bool _disposed;
  Screen _screen;
  Keyboard _keyboard;

  vector<SPEvalGroup> _vpEvalGroups;
  SyncQueue<Key> _queueKey;
};

#endif
