#ifndef _SNAKE_SNAKENODE
#define _SNAKE_SNAKENODE

#include "util/pch.h"

#include "screen/xy.h"
#include "snakeCommand.h"

enum SnakeNodeType {
  SN_NOTHING = 0,
  SN_BODY = 1,
  SN_FRUIT,
  SN_FRUITBIG,
  SN_BLOCK,
};

class SnakeNode : public XY {
public:
  SnakeNode() : XY() {
    _type = SN_NOTHING;
  }
  SnakeNode(const SnakeNode& node_) : XY((XY)node_) {
    _type = node_._type;
  }
  SnakeNode(int x_, int y_, SnakeNodeType type_) : XY(x_, y_) {
    _type = type_;
  }
  SnakeNode(const XY& xy_, SnakeNodeType type_) : XY(xy_) {
    _type = type_;
  }

  SnakeNodeType type() const {
    return _type;
  }  

  void type(SnakeNodeType type_) {
    _type = type_;
  }  

private:
  SnakeNodeType _type;

};

typedef shared_ptr<SnakeNode> SPSnakeNode;
typedef vector<SPSnakeNode> SPSnakeNodes;

#endif
