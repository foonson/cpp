//
// TODO:
// - resource cleanup / print log when process cored
// - profiler
//

#include "util/pch.h"

#include <thread>
#include <chrono>
#include <csignal> //std:signal
#include <cstdlib> //std::exit
#include "screen/screen.h"
#include "screen/keyboard.h"
#include "util/syncQueue"
//#include "util/UString"
#include "snakeCommand.h"
#include "snake.h"

#include <functional> // std:function

//#include <sys/select.h>

INITLOG("./snake.log");
bool g_exit=false;

void signalHandler(int signum) {
  printf("signal %d\n", signum);
  if (signum==SIGINT) {
    printf("SIGINT\n");
    ERR << "SIGINT" << LEND;
    //std::exit(-1);
    g_exit = true;
  }
  if (signum==SIGQUIT) {  // core
    printf("SIGQUIT\n");
    ERR << "SIGQUIT" << LEND;
    g_exit = true;
  }
  if (signum==SIGSEGV) {  // segmentation
    printf("SIGSEGV\n");
    ERR << "SIGSEGV" << LEND;
    //_log.flush();
    std::exit(-1);
    g_exit = true;
  }
}

void initialize() {
  std::signal(SIGINT, signalHandler);
  std::signal(SIGTERM, signalHandler);
  std::signal(SIGSEGV, signalHandler);
  std::signal(SIGILL, signalHandler);
  std::signal(SIGABRT, signalHandler);
  std::signal(SIGFPE, signalHandler);
}

class SnakeGame {
public:
  SnakeGame() {
    START("");
    _exit = false;    

    _pLayer = _screen.createLayer(0,0,0);
    //pLayer0->text(1,1,0,0,'K');
    //_screen.render();

    shared_ptr<Layer> pLayer1 = _screen.createLayer(0, 0, 1);
    Snake& snake1 = createSnake(pLayer1);
    snake1._fnKeyActionMap = snake1KeyActionMap;
    snake1._pcmdQueue = new SyncQueue<SnakeCommand>;
    snake1._body = Pixel(0,0,YELLOW,BLACK,'X');
    snake1._length = 2;
    snake1._id = 1;
    snake1._head = SnakeNode(10,10);
    snake1.init();
    //printf("%s\n", pLayer1->toString().c_str());

    shared_ptr<Layer> pLayer2 = _screen.createLayer(0, 0, 2);
    Snake& snake2 = createSnake(pLayer2);
    snake2._fnKeyActionMap = snake2KeyActionMap;
    snake2._pcmdQueue = new SyncQueue<SnakeCommand>;
    snake2._body = Pixel(0,0,LBLUE,BLACK,'O');
    snake2._length = 2;
    snake2._id = 2;
    snake2._head = SnakeNode(20,20);
    snake2.init();
    //printf("%s\n", layer2.toString().c_str());
    END("");
  }

  //Snake& createSnake(Layer& layer_, (SNAKEACTION)(KEY, char) fnKeyActionMap_) {
  Snake& createSnake(SPLayer pLayer_) {
    _vSnakes.push_back(Snake(pLayer_));
    Snake& snake = _vSnakes.back();
    //snake.setLayer(layer_);
    //snake._fnKeyActionMap = fnKeyActionMap_;
    return snake;
  } 

  void evaluate(Snake& snake_) {
    if (_counter%100==0) {
      _pLayer->text(XMAX/2,YMAX/2,RED,BLACK,'*');
    }

    if (snake_._head.touching(XMAX/2, YMAX/2)) {
      snake_.increaseLength(2);
      _pLayer->clear();
    }

    for (auto& other: _vSnakes) {
      if (snake_._id==other._id) {
        continue;
      }
      if (other.touching(snake_._head)) {
        snake_.increaseLength(-2);
      }
 
    } 
  }

  void evaluateLoop() {
    START("");
    do {
      _counter++;

      if (_exit || g_exit) {
        break;
      }   
      for (auto& snake: _vSnakes) {
        snake.evaluate();
        evaluate(snake);
      } 
      _screen.render();
      //this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (true);
    END("");
  }

  void listenCommandLoop() {
    START("");
    do {
      //printf("listenCommandLoop");

      if (_exit || g_exit) {
        break;
      }   

      KEY key;
      char ch;      
      _keyboard.getKey(key, ch);
      LOG << ch << LEND;

      for (auto& snake: _vSnakes) {
        snake.listenCommand(key, ch);
      } 
      
      if (ch=='x') {
        _exit = true;
        break;
      }
    

    } while (true);
    END("");
  }

  void renderLoop() {

    START("");
    do {
      //printf("renderLoop");
      if (_exit || g_exit) {
        break;
      }   
      _screen.render();
      //this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (true);
    END("");
  }
  

  void startThreads() {
    START("");
    thread t1(&SnakeGame::listenCommandLoop, this);
    //thread t2(&SnakeGame::renderLoop, this);
    thread t3(&SnakeGame::evaluateLoop, this);

    t1.join();
    //t2.join();
    t3.join();
    END("");
  }

  //Screen& screen() { return screen_; }

private:
  bool _exit;
  Screen _screen;
  Keyboard _keyboard;
  vector<Snake> _vSnakes;
  SPLayer _pLayer;
  vector<SnakeNode> _fruits;
  long long _counter;
};

int main() {
  START("start");
  initialize();
  
  SnakeGame game;
  game.startThreads();

  try {
  } catch (...) {
    ERR << "main exception" << LEND;
  }
  END("");

}

