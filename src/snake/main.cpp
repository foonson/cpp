//
// TODO:
// - resource cleanup / print log when process cored
// - profiler
//

#include "util/pch.h"
#include "snakeGame.h"
#include "snakeGameEval.h"

INITLOG("./snake.log");

int main() {
  START();

  SnakeApp app;
  
  //SnakeGame game(app);
  SPSnakeGame pGame = make_shared<SnakeGame>(app);

  // should move to SnakeApp
  pGame->evaluations().push_back(make_shared<SnakeGameEval>(pGame->screenLayer(), 50, pGame));
  
  pGame->startThreads();

  try {
  } catch (...) {
    ERR << "main exception" << LEND;
  }
  END("");

}

