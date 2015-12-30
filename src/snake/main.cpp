//
// TODO:
// - resource cleanup / print log when process cored
// - profiler
//

#include "util/pch.h"

#include "snakeApp.h"
#include "auplay/AudioPlayer.h"

INITLOG("./snake.log");

int main() {
  START();

  //unique_ptr<AudioPlayer> ap(AudioPlayer::file("./sound/pacman.wav"));
  unique_ptr<AudioPlayer> ap(AudioPlayer::file("./sound/eat.wav"));
  if(ap) {
    ap->play();
  }

  auto pApp = make_shared<SnakeApp>();
  pApp->setup();
  pApp->startThreads();

  

  //try {
  //} catch (...) {
  //  ERR << "main exception" << LEND;
  //}
  END("");

}

