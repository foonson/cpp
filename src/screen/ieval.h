#ifndef _SCREEN_IRENDER
#define _SCREEN_IRENDER

#include "Layer.h"
#include "util/tick.h"

class IEval {
public:
  IEval(SPLayer pLayer_, long interval_);
  virtual bool evaluateImpl() = 0;
  virtual void render() = 0;
  virtual string toString() = 0;

  virtual bool completed();
  virtual bool onComplete();
  virtual void clearLayer();
  virtual bool evaluate();
  virtual bool needEvaluate();
  virtual bool needRender();
  virtual void needRender(bool needRender_);

protected:
  SPLayer _pLayer;
  Tick _tick;
  bool _needRender;
  
};

typedef shared_ptr<IEval> SPEval;

#endif
