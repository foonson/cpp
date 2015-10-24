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

//#include <sys/select.h>


INITLOG("./snake.log");
bool g_exit=false;

class Snake {
};

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
    ERR("SIGQIUT") << LEND;
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

void threadListenCommand(Screen& screen_, SyncQueue<SnakeCommand>& queue_) {
  START("threadListenCommand");

  do {

    if (g_exit) {
      break;
    }    
    
    //FD_ZERO(&readfds);
    //FD_SET(STDIN_FILENO, &readfds);
    //int iResult = select(1, &readfds, NULL, NULL, NULL);
    //if (iResult==-1 && errno!=EINTR) {
    //} else {
    //  if (FD_ISSET(STDIN_FILENO, &readfds)) {
    //    printf("%d", iResult);
    //  }
    //}

    char ch=getchar();
    if (ch==27) {
      ch=getchar();
      if (ch==91) {
        ch=getchar();
        if (ch==65) {
          queue_.put(SnakeCommand(SNAKE_UP));
        } else if (ch==66) {
          queue_.put(SnakeCommand(SNAKE_DOWN));
        } else if (ch==68) {
          queue_.put(SnakeCommand(SNAKE_LEFT));
        } else if (ch==67) {
          queue_.put(SnakeCommand(SNAKE_RIGHT));
        }
      }
      
    } else if (ch=='i') {
     queue_.put(SnakeCommand(SNAKE_UP));
    } else if (ch=='x') {
     queue_.put(SnakeCommand(SNAKE_EXIT));
     break;
    }
    
    screen_.xy(1,8).show(UString::toString(queue_.size()));

  } while (true);
  END("");
}


void threadMove(Screen& screen_, SyncQueue<SnakeCommand>& queue_) {
  START("threadMove");

  try {

    int xLast=0;
    int yLast=0;  
    int x=10;
    int y=10;
    SNAKEACTION lastAction = SNAKE_NOTHING;
    do {

      if (g_exit) {
        return;
      }
      bool moved = false;
      SNAKEACTION action = SNAKE_NOTHING;

      do {
        if (queue_.empty()) {
          break;
        }
        SnakeCommand cmd = queue_.get();
        action = cmd.action();
        if (action==SNAKE_NOTHING) {
          break;
        }
        screen_.xy(1,8).show(UString::toString(queue_.size()) + " ");
      } while(action==lastAction);

      if (action==SNAKE_NOTHING) {
        action = lastAction;
      }
      if (action==SNAKE_EXIT) {
        return;
      }
      if (action==SNAKE_UP) {
        moved = true;
        y=y-1;
      } else if (action==SNAKE_DOWN) {
        moved = true;
        y=y+1;
      } else if (action==SNAKE_LEFT) {
        moved = true;
        x=x-1;
      } else if (action==SNAKE_RIGHT) {
        moved = true;
        x=x+1;
      }
      if (y<=0) {
        y=40;
      }
      if (y>40) {
        y=0;
      }
      if (x<=0) {
        x=80;
      }
      if (x>80) {
        x=0;
      }

      if (moved) {
        //using namespace std::literals;
        screen_.xy(x, y).color(GREEN).show("X");
        screen_.xy(xLast, yLast).colorDefault().show(" ");
        this_thread::sleep_for(std::chrono::milliseconds(500));
        xLast = x;
        yLast = y;
        lastAction = action;
      }

    } while (true);
  } catch (...) {
    ERR("threadMove exception") << LEND;
  }
  END("");
}

void initialize() {
  std::signal(SIGINT, signalHandler);
  std::signal(SIGTERM, signalHandler);
  std::signal(SIGSEGV, signalHandler);
  std::signal(SIGILL, signalHandler);
  std::signal(SIGABRT, signalHandler);
  std::signal(SIGFPE, signalHandler);
}

int main() {
  START("start");
  initialize();

  Screen screen;
  SyncQueue<SnakeCommand> queue1;

  try {
    thread t1(threadMove, std::ref(screen), std::ref(queue1));
    thread t2(threadListenCommand, std::ref(screen), std::ref(queue1));

    t1.join();
    t2.join();
  } catch (...) {
    ERR("main exception") << LEND;
  }
  END("");

}

