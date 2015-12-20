//
// TODO:
// - resource cleanup / print log when process cored
// - profiler
//

#include "util/pch.h"
#include "snakeApp.h"
#include "screen/evalGroup.h"

SnakeApp::SnakeApp() {

  _pegMain = make_shared<EvalGroup>();
  _pegMain->enabled(true);
  addEvalGroup(_pegMain);

}

