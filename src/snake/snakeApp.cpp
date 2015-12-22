//
// TODO:
// - resource cleanup / print log when process cored
// - profiler
//

#include "util/pch.h"
#include "snakeApp.h"
#include "snakeAppEval.h"
#include "snakeGame.h"
#include "screen/evalGroup.h"

SnakeApp::SnakeApp() {
}

void SnakeApp::setup() {
   
  auto pLayerPreGame = screen().createLayer(XY(0,0), 0);

  _pegApp = make_shared<EvalGroup>();
  _pegApp->enabled(true);
  auto pSnakeAppEval = make_shared<SnakeAppEval>(pLayerPreGame, 1000, shared_from_this());
  _pegApp->addEval(make_shared<SnakeAppEval>(pLayerPreGame, 1000, shared_from_this()));
  addEvalGroup(_pegApp);
  addKeyListener(pSnakeAppEval);  

  _pegMain = make_shared<EvalGroup>();
  _pegMain->enabled(false);
  addEvalGroup(_pegMain);
  _pGame = make_shared<SnakeGame>(shared_from_this());
  _pGame->setup();

}

