#ifndef SMARTBOARD_H
#define SMARTBOARD_H

#include <map>
#include <string>
#include <vector>

// #include <gloox/okplugin.h>
// #include <gloox/tag.h>

namespace SmartBoard {

enum DrawType { Line, Text, Move, File, Remove };
enum ControllerType {
  Select,
  Voice,
};

enum Action { Create, Update, ON, OFF };

struct Point {
  double x = 0;
  double y = 0;
};

struct Position {
  int x = 0;
  int y = 0;
  int z = 0;
};

using DrawId = std::string;
using PointList = std::vector<Point>;
using UserList = std::vector<std::string>;

class DrawItem {
protected:
  DrawType _type;
  DrawId _id;
  Action _action;

  std::vector<Point> _points;

public:
  DrawItem();
  ~DrawItem();

  const DrawId &id() const;

  Action action() const;
  void setAction(Action);

  // const std::map<std::string, std::string> &style() const;
  const std::vector<Point> &points() const;

  DrawType type();
};

class ControllerItem {
protected:
  ControllerType _type;
  DrawId _id;
  Action _action;

public:
  ControllerItem();
  ControllerItem(const DrawId &);
  ~ControllerItem();

  Action action() const;
  void setAction(Action);

  ControllerType type() const;
};

using ControllerMap = std::map<ControllerType, ControllerItem *>;
using DrawMap = std::map<DrawType, DrawItem *>;

class ITag {

protected:
//  gloox::Tag *_tag;

public:
//  gloox::Tag *tag() const { return _tag; }
};
} // namespace SmartBoard

#endif // SMARTBOARD_H
