//
// TODO:
// - resource cleanup / print log when process cored
// - profiler
//
// http://www.sounds4email.com

#include "util/pch.h"

#include "snakeApp.h"

INITLOG("./snake.log");

int main() {
  START();


  auto pApp = make_shared<SnakeApp>();
  pApp->setup();
  pApp->sound("./sound/eat.wav");
  pApp->startThreads();

  //try {
  //} catch (...) {
  //  ERR << "main exception" << LEND;
  //}
  END("");

}

