#ifndef _SCREEN_EVALGROUP
#define _SCREEN_EVALGROUP

#include "util/pch.h"
#include "ieval.h"

class EvalGroup {
public:
  vector<SPEval>& evaluations() { return _vpEvaluations; }
  bool enabled() { return _enabled;}
  void enabled(bool enabled_) { _enabled = enabled_; }
  void addEval(SPEval pEval_) {
    _vpEvaluations.push_back(pEval_);
  }

private:
  bool _enabled;
  vector<SPEval> _vpEvaluations;
};

typedef shared_ptr<EvalGroup> SPEvalGroup;

#endif
