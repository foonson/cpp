#include "ieval.h"

IEval::IEval(SPLayer pLayer_, long interval_) : _pLayer(pLayer_), _tick(interval_)
{
}

bool IEval::needEvaluate() {
  if (_forceEval) {
    _forceEval = false;
    _tick.force();
    return true;
  }
  return _tick.pass();
}

bool IEval::needRender() {
  return _needRender;
}

void IEval::needRender(bool needRender_) {
  _needRender = needRender_;
}

void IEval::forceEvaluate(bool forceEval_) {
  _forceEval = forceEval_;
}

bool IEval::evaluate() {
  if (!needEvaluate()) return false;
  bool b = evaluateImpl();
  triggerDependEvals();
  return b;
}

void IEval::clearLayer() {
  _pLayer->clear();
}

bool IEval::completed() {
  return false;
}

bool IEval::onComplete() {
  return false;
}

void IEval::triggerDependEvals() {
  for(auto& pEval:_vpDependEvals) {
    pEval->forceEvaluate(true);
  }
}

