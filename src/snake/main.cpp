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
  // should move to SnakeApp

  SPSnakeGame pGame = make_shared<SnakeGame>(app);
  app.pegMain()->evaluations().push_back(make_shared<SnakeGameEval>(pGame->screenLayer(), 50, pGame));
  app.pegMain()->evaluations().push_back(make_shared<FruitEval>(pGame->boardLayer(), 3000, pGame));

  app.startThreads();

  //try {
  //} catch (...) {
  //  ERR << "main exception" << LEND;
  //}
  END("");

}

