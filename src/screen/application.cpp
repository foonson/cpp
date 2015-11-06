#include <csignal> //std:signal
#include <cstdlib> //std::exit

#include "Application.h"

Application* Application::_pApp = NULL;

Application::Application() {
  START("");
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

