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
//#include <sys/select.h>


INITLOG("./snake.log");
bool g_exit=false;

class Snake {
};

enum COMMAND {
  UP=1,
  DOWN,
  LEFT,
  RIGHT
};

class Command {
public:
  COMMAND _action;
};

template<typename T> {
class CommandQueue {

public:
  void put(const T& cmd_);
  T get();
private:
  vector<T> _queue;
};

void signalHandler(int signum) {
  printf("signal %d\n", signum);
  if (signum==SIGINT) {
    printf("SIGINT\n");
    ERR("SIGINT");
    //std::exit(-1);
    g_exit = true;
  }
  if (signum==SIGQUIT) {  // core
    printf("SIGQUIT\n");
    ERR("SIGQIUT");
    g_exit = true;
  }
  if (signum==SIGSEGV) {  // segmentation
    printf("SIGSEGV\n");
    ERR("SIGSEGV");
    //_log.flush();
    std::exit(-1);
    g_exit = true;
  }
}

void threadReadKey(Screeen& screen_, CommandQueue& cqueue_) {


}


void threadMove(Screen& screen_, CommandQueue& cqueue_) {

  try {

    int xLast=0;
    int yLast=0;  
    int x=10;
    int y=10;
    do {

      //if (x==15) {
      //  int* p = NULL;
      //  *p = 10;
      //}
      if (g_exit) {
        return;
      }
      if (cqueue_._ch=='x') {
        return;
      }
      if (cqueue_._ch=='i' || cqueue_._ch==0x4427D) {
        cqueue_._ch = ' ';
        xLast = x;
        yLast = y;
        y=y-1;
      }
      if (cqueue_._ch=='m') {
        cqueue_._ch = ' ';
        xLast = x;
        yLast = y;
        y=y+1;
      }
      if (y<=0) {
        y=1;
      }
      if (y>20) {
        y=0;
        x+=1;
      }

      if (y!=yLast) {
        //using namespace std::literals;
        screen_.xy(x, y).color(GREEN).show("X");
        screen_.xy(xLast, yLast).colorDefault().show(" ");
        this_thread::sleep_for(std::chrono::milliseconds(10));
      }

    } while (true);
  } catch (...) {
    printf("threadMove exception");
    ERR("threadMove exception")
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

int main() {
  LOG("start");
  initialize();

  Screen screen;
  CommandQueue cqueue;

  try {
    thread t1(threadMove, std::ref(screen), std::ref(cqueue));

    
    //fd_set readfds;
    //int sd;
    do {

      //char ch = getchar();
      //string s = "";
      //s[0] = ch;
      //screen.xy(1,20).show("i");
      //cqueue._ch = ch;
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
            cqueue._ch = 'i';
          } else if (ch==) {
          }
        }
        
      } else {
        cqueue._ch = ch;
      }

      printf("%ld",ch);
 
 
    } while (true);


    t1.join();
  } catch (...) {
    printf("main exception");
    ERR("main exception")
  }
}

