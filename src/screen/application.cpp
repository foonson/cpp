#include <csignal> //std:signal
#include <cstdlib> //std::exit
#include <time.h>

#include "Application.h"

Application* Application::_pApp = NULL;

Application::Application() {
  START("");
  srand(time(NULL));
  _pApp = this;
  _disposed = false;
  _exit = false;
  registerSignalHandler();
  END("");
}

Application::~Application() {
  START("");
  dispose();
  END("");
}

void Application::dispose() {
  START("");
  if (!_disposed) {
    _screen.dispose();
    _keyboard.dispose();
    _disposed = true;
  }
  END("");
}

void Application::signalHandler(int signum) {
  printf("signal %d\n", signum);
  if (signum==SIGINT) {
    ERR << "SIGINT" << LEND;
    Application::_pApp->_exit = true;
  }
  if (signum==SIGQUIT) {  // core
    ERR << "SIGQUIT" << LEND;
    Application::_pApp->_exit = true;
  }
  if (signum==SIGSEGV) {  // segmentation
    printf("SIGSEGV\n");
    ERR << "SIGSEGV" << LEND;
    Application::_pApp->_exit = true;
    Application::_pApp->dispose();
    g_log.dispose();
    std::exit(-1);
  }
}

void Application::registerSignalHandler() {
  std::signal(SIGINT, signalHandler);
  std::signal(SIGTERM, signalHandler);
  std::signal(SIGSEGV, signalHandler);
  std::signal(SIGILL, signalHandler);
  std::signal(SIGABRT, signalHandler);
  std::signal(SIGFPE, signalHandler);
}


void Application::listenCommandLoop() {
  START("");
  do {

    if (_exit) {
      break;
    }   

    KEY key;
    char ch;
    _keyboard.getKey(key, ch);
    //LOG << ch << LEND;

    //for (auto& pSnake: _vpSnakes) {
    //  pSnake->listenCommand(key, ch);
    //}
    for (auto& pListener: _vpKeyListeners) {
      pListener->keyListen(key, ch);
    }
    
    if (ch=='X') {
      _exit = true;
      break;
    }

  } while (true);
  END("");
}


void Application::evaluateLoop() {
  START("");
  do {
    
    if (_exit) {
      break;
    }   

    for (auto& pEvalGroup: _vpEvalGroups) {
      if (!pEvalGroup->enabled()) {
        continue;
      }
      auto& vpEvals = pEvalGroup->evaluations();

      size_t i = 0;
      while (i<vpEvals.size()) {
        auto& pEval = vpEvals[i];
        //LOG << pEval->toString() << LEND;
        pEval->evaluate();
        i++;
      }

      for (auto& pEval: vpEvals) {
        if (pEval->needRender()) {
          pEval->clearLayer();
        }
      }

      for (auto& pEval: vpEvals) {
        if (pEval->needRender()) {
          pEval->render();
        }
      }

      auto it = vpEvals.begin();
      while(it!=vpEvals.end()) {
        auto& n = *it;
        if (n->completed()) {
          n->onComplete();
          it = vpEvals.erase(it);
          LOG << "vpEvals.erase" << LEND;
          //break;
        } else {
          it++;
        }
      }

      screen().render();
    //this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  } while (true);
  END("");
}


/*
void Application::renderLoop() {

  START("");
  do {
    if (_app._exit) {
      break;
    }   
    _app.screen().render();
    //this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (true);
  END("");
}
*/

void Application::startThreads() {
  START("");
  thread t1(&Application::listenCommandLoop, this);
  //thread t2(&SnakeGame::renderLoop, this);
  thread t3(&Application::evaluateLoop, this);

  t1.join();
  //t2.join();
  t3.join();
  END("");
}

