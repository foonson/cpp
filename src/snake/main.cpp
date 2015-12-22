//
// TODO:
// - resource cleanup / print log when process cored
// - profiler
//

#include "util/pch.h"

#include "snakeApp.h"

INITLOG("./snake.log");

int main() {
  START();

  auto pApp = make_shared<SnakeApp>();
  pApp->setup();
  pApp->startThreads();

  //try {
  //} catch (...) {
  //  ERR << "main exception" << LEND;
  //}
  END("");

}

