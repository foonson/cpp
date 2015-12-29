#ifndef _SCREEN_EVALGROUP
#define _SCREEN_EVALGROUP

#include "util/pch.h"
#include "ieval.h"
#include "ikeyListener.h"

class EvalGroup {
public:
  bool enabled() { return _enabled;}
  void enabled(bool enabled_) { _enabled = enabled_; }

  vector<SPEval>& evaluations() { return _vpEvaluations; }
  vector<SPKeyListener>& keyListeners() { return _vpKeyListeners; }
  void addEval(SPEval pEval_) {
    _vpEvaluations.push_back(pEval_);
  }
  void addKeyListener(SPKeyListener pListener_) {
    _vpKeyListeners.push_back(pListener_);
  }

private:
  bool _enabled;
  vector<SPEval> _vpEvaluations;
  vector<SPKeyListener> _vpKeyListeners;
};

typedef shared_ptr<EvalGroup> SPEvalGroup;

#endif
