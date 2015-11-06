//
// TODO:
// - resource cleanup / print log when process cored
// - profiler
//

#include "util/pch.h"
#include "snakeGame.h"

INITLOG("./snake.log");

int main() {
  START();

  SnakeApp app;
  
  SnakeGame game(app);
  game.startThreads();

  try {
  } catch (...) {
    ERR << "main exception" << LEND;
  }
  END("");

}

