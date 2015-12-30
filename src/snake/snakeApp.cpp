#include "util/pch.h"
#include "snakeApp.h"
#include "snakeAppEval.h"
#include "snakeGame.h"

SnakeApp::SnakeApp() {
}

void SnakeApp::setup() {
   
  auto pLayerPreGame = screen().createLayer(XY(0,0), 0);

  // App
  _pegApp = make_shared<EvalGroup>();
  addEvalGroup(_pegApp);
  _pegApp->enabled(true);
  auto pAppEval = make_shared<SnakeAppEval>(pLayerPreGame, 1000, shared_from_this());
  _pegApp->addEval(pAppEval);
  _pegApp->addKeyListener(pAppEval);  

  // Title
  auto pLayerTitle = screen().createLayer(XY(0,0), 0);
  _pegTitle = make_shared<EvalGroup>();
  addEvalGroup(_pegTitle);
  _pegTitle->enabled(true);
  auto pTitleEval = make_shared<SnakeTitleEval>(pLayerTitle, 1000, shared_from_this());
  _pegTitle->addEval(pTitleEval);

  // Main
  _pegMain = make_shared<EvalGroup>();
  addEvalGroup(_pegMain);
  _pegMain->enabled(false);
  _pGame = make_shared<SnakeGame>(shared_from_this());
  _pGame->setup();

}

void SnakeApp::keyListen(const Key& key_) {
  if (key_._ch=='X') {
    _exit = true;
  }
}
