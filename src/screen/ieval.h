#ifndef _SCREEN_IRENDER
#define _SCREEN_IRENDER

#include "Layer.h"
#include "util/tick.h"

class IEval {
public:
  IEval(SPLayer pLayer_, long interval_);
  virtual string toString() = 0;

  // IEval
  virtual bool evaluateImpl() = 0;
  virtual bool evaluate();
  virtual bool needEvaluate();
  virtual void forceEvaluate(bool forceEval_);
  void triggerDependEvals();

  virtual bool completed();
  virtual bool onComplete();

  void addDependEval(shared_ptr<IEval> pEval_) {
    _vpDependEvals.push_back(pEval_);
  }


  // IRender
  virtual void render() = 0;
  virtual void clearLayer();
  virtual bool needRender();
  virtual void needRender(bool needRender_);

  void layer(SPLayer pLayer_) { _pLayer = pLayer_; }
  SPLayer layer() { return _pLayer; }

protected:
  SPLayer _pLayer;
  Tick _tick;
  bool _needRender;
  bool _forceEval;

  vector<shared_ptr<IEval>> _vpDependEvals;
  
};

typedef shared_ptr<IEval> SPEval;
typedef weak_ptr<IEval> WPEval;

#endif
