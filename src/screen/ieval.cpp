#include "ieval.h"

IEval::IEval(SPLayer pLayer_, long interval_) : _pLayer(pLayer_), _tick(interval_)
{
}

bool IEval::needEvaluate() {
  return _tick.pass();
}

bool IEval::needRender() {
  return _needRender;
}

void IEval::needRender(bool needRender_) {
  _needRender = needRender_;
}

bool IEval::evaluate() {
  if (!needEvaluate()) return false;
  return evaluateImpl();
}
