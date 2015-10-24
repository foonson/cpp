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
#include "util/syncQueue"
#include "util/UString"
#include "snakeCommand.h"


#include <functional> // std:function

//#include <sys/select.h>


INITLOG("./snake.log");
bool g_exit=false;


void signalHandler(int signum) {
  printf("signal %d\n", signum);
  if (signum==SIGINT) {
    printf("SIGINT\n");
    ERR("SIGINT") << LEND;
    //std::exit(-1);
    g_exit = true;
  }
  if (signum==SIGQUIT) {  // core
    printf("SIGQUIT\n");
    ERR("SIGQUIT") << LEND;
    g_exit = true;
  }
  if (signum==SIGSEGV) {  // segmentation
    printf("SIGSEGV\n");
    ERR("SIGSEGV") << LEND;
    //_log.flush();
    std::exit(-1);
    g_exit = true;
  }
}


SNAKEACTION commonKeyActionMap(KEY key_, char ch_) {
  if (ch_=='x') {
    return SNAKE_EXIT;
  }
  return SNAKE_NOTHING;
}

SNAKEACTION snake1KeyActionMap(KEY key_, char ch_) {
  if (key_==KEY_UP) {
    return SNAKE_UP;
  } else if (key_==KEY_DOWN) {
    return SNAKE_DOWN;
  } else if (key_==KEY_LEFT) {
    return SNAKE_LEFT;
  } else if (key_==KEY_RIGHT) {
    return SNAKE_RIGHT;
  }
  return commonKeyActionMap(key_, ch_);
}

SNAKEACTION snake2KeyActionMap(KEY key_, char ch_) {
  if (ch_=='w') {
    return SNAKE_UP;
  } else if (ch_=='z') {
    return SNAKE_DOWN;
  } else if (ch_=='a') {
    return SNAKE_LEFT;
  } else if (ch_=='s') {
    return SNAKE_RIGHT;
  }
  return commonKeyActionMap(key_, ch_);
}

void initialize() {
  std::signal(SIGINT, signalHandler);
  std::signal(SIGTERM, signalHandler);
  std::signal(SIGSEGV, signalHandler);
  std::signal(SIGILL, signalHandler);
  std::signal(SIGABRT, signalHandler);
  std::signal(SIGFPE, signalHandler);
}

class Snake {
public:

  Snake(Layer& layer_) : _layer(layer_) {
    _lastAction = SNAKE_NOTHING;
    _x = 10;
    _y = 10;
    _layer.text(_x,_y,0,0,'X');
  }

  bool listenCommand(KEY key_, char ch_) {
    SNAKEACTION action = _fnKeyActionMap(key_, ch_);
    if (action!=SNAKE_NOTHING) {
      _pcmdQueue->put(SnakeCommand(action));
    }
  }

  void evaluate() {

    int xLast = _x;
    int yLast = _y;

    SNAKEACTION action = SNAKE_NOTHING;
    bool moved = false;

    do {
      if (_pcmdQueue->empty()) {
        break;
      }
      SnakeCommand cmd = _pcmdQueue->get();
      action = cmd.action();
      if (action==SNAKE_NOTHING) {
        break;
      }
      //screen.xy(1,8).show(UString::toString(queue_.size()) + " ");
    } while(action==_lastAction);

    if (action==SNAKE_NOTHING) {
      action = _lastAction;
    }

    if (action==SNAKE_EXIT) {
      return;
    }
    if (action==SNAKE_UP) {
      moved = true;
      _y=_y-1;
    } else if (action==SNAKE_DOWN) {
      moved = true;
      _y=_y+1;
    } else if (action==SNAKE_LEFT) {
      moved = true;
      _x=_x-1;
    } else if (action==SNAKE_RIGHT) {
      moved = true;
      _x=_x+1;
    }
    
    if (_y<=0) {
      _y=YMAX-1;
    }
    if (_y>=YMAX) {
      _y=0;
    }
    if (_x<=0) {
      _x=XMAX-1;
    }
    if (_x>=XMAX) {
      _x=0;
    }

    if (moved) {
      _layer.text(_x, _y, 0, 0, 'X');
      _layer.text(xLast, yLast, 0, 0, ' ');
      _lastAction = action;
    }
    printf("%d,%d ", _x,_y);

  }

  function<SNAKEACTION(KEY, char)> _fnKeyActionMap;
  SyncQueue<SnakeCommand>* _pcmdQueue;
private:
  Layer& _layer;
  int _x;
  int _y;
  SNAKEACTION _lastAction;
};


class SnakeGame {
public:
  SnakeGame() {
    START();
    _exit = false;    

    Layer& layer0 = _screen.createLayer(0,0,0);
    layer0.text(1,1,0,0,'K');
    _screen.render();

    Layer& layer1 = _screen.createLayer(0, 0, 0);
    Snake& snake1 = createSnake(layer1);
    snake1._fnKeyActionMap = snake1KeyActionMap;
    snake1._pcmdQueue = new SyncQueue<SnakeCommand>;

    Layer& layer2 = _screen.createLayer(0, 0, 0);
    Snake& snake2 = createSnake(layer2);
    snake2._fnKeyActionMap = snake2KeyActionMap;
    snake2._pcmdQueue = new SyncQueue<SnakeCommand>;
    END("");
  }

  //Snake& createSnake(Layer& layer_, (SNAKEACTION)(KEY, char) fnKeyActionMap_) {
  Snake& createSnake(Layer& layer_) {
    _vSnakes.push_back(Snake(layer_));
    Snake& snake = _vSnakes.back();
    //snake.setLayer(layer_);
    //snake._fnKeyActionMap = fnKeyActionMap_;
    return snake;
  } 

  void evaluateLoop() {
    START("");
    do {
      //printf("evaluateLoop");

      if (_exit || g_exit) {
        break;
      }   
      for (auto& snake: _vSnakes) {
        snake.evaluate();
      } 
      this_thread::sleep_for(std::chrono::milliseconds(100));
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
      this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (true);
    END("");
  }
  

  void startThreads() {
    START("");
    thread t1(&SnakeGame::listenCommandLoop, this);
    thread t2(&SnakeGame::renderLoop, this);
    thread t3(&SnakeGame::evaluateLoop, this);

    t1.join();
    t2.join();
    t3.join();
    END("");
  }

  //Screen& screen() { return screen_; }

private:
  bool _exit;
  Screen _screen;
  Keyboard _keyboard;
  vector<Snake> _vSnakes;
};

int main() {
  START("start");
  initialize();
  
  SnakeGame game;
  game.startThreads();

  try {
  } catch (...) {
    ERR("main exception") << LEND;
  }
  END("");

}

