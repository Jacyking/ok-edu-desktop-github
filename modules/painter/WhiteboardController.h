#pragma once

#include <vector>

#include <QEvent>
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>


#include <UI/widget/MoveableBar.h>

#include "Base.h"

namespace painter {

using namespace context::WB;

class WhiteboardControllerButton : public QLabel {
  Q_OBJECT
public:
  WhiteboardControllerButton(QWidget *parent = nullptr);
  ~WhiteboardControllerButton();

  void setType(WB_CTRL type);
  void setIcon(QString &icon);
  void setActiveIcon(QString &activeIcon);
  void setMoveable(bool moveable);

  void setTarget(QWidget *);

  void setChecked(bool);

  inline void setCheckable(bool checkable) { _checkable = checkable; }

  WB_CTRL type() { return _type; }

  bool isChecked() { return _isChecked; }

  QString icon() { return _icon; }

protected:
  virtual void showEvent(QShowEvent *event);

  virtual void mousePressEvent(QMouseEvent *event);

  virtual void mouseMoveEvent(QMouseEvent *event);

  virtual void mouseReleaseEvent(QMouseEvent *event);

  virtual void leaveEvent(QEvent *event);

  virtual void enterEvent(QEvent *event);

private:
  WB_CTRL _type;

  QString _icon;
  QString _activeIcon;

  bool _moveable = false;
  bool _checkable = false;

  //状态
  bool _isChecked = false;
  //移动
  bool m_isMoved = false;
  bool m_isPressed = false;

  QPoint m_startMovePos;
  QWidget *m_target = nullptr;

signals:
  void clicked();
};

class WhiteboardController : public QWidget {
  Q_OBJECT

public:
  WhiteboardController(QWidget *parent);
  ~WhiteboardController();

protected:
  virtual void ctrl(int i);

private:
  std::vector<WhiteboardControllerButton *> buttons;

signals:
  void checked(context::WB::WB_CTRL, bool);
};

} // namespace painter
