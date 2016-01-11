#ifndef _SCREEN_EVALGROUP
#define _SCREEN_EVALGROUP

#include "util/pch.h"
#include "ieval.h"
#include "ikeyListener.h"
#include "layer.h"

class EvalGroup {
public:
  bool enabled() { return _enabled;}
  void enabled(bool enabled_) { _enabled = enabled_; }

  vector<SPEval>& evaluations() { return _vpEvaluations; }
  vector<SPKeyListener>& keyListeners() { return _vpKeyListeners; }
  SPLayers& layers() { return _vpLayers; }
  void addEval(SPEval pEval_) {
    _vpEvaluations.push_back(pEval_);
  }
  void addKeyListener(SPKeyListener pListener_) {
    _vpKeyListeners.push_back(pListener_);
  }
  void addLayer(SPLayer pLayer_) {
    _vpLayers.push_back(pLayer_);
  }

private:
  bool _enabled;
  vector<SPEval> _vpEvaluations;
  vector<SPKeyListener> _vpKeyListeners;
  SPLayers _vpLayers;
};


typedef shared_ptr<EvalGroup> SPEvalGroup;

#endif
