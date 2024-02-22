#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include "frametitle.h"

#include <QFile>
#include <QVBoxLayout>
#include <QWidget>

#include <UI/widget/MoveableBar.h>

namespace office {

class FrameWidget : public QFrame {
  //    Q_OBJECT
public:
  explicit FrameWidget(QWidget *parent = nullptr);
  virtual ~FrameWidget() override;

  virtual void play(const QFile &file) = 0;

  virtual void setMoveableTarget(QWidget *target);

  virtual void setTitle(const QString &title);

protected:
  //头部
  FrameTitle *bar_;

  //底部
  UI::widget::MoveableBar *foo_;

  //布局
  QVBoxLayout *layout_v_;

  QRect innerRect();

  //    QString filename_;

  int frameWidth_;

  // private:

  // signals:

  // public slots:
};

} // namespace office
#endif // FRAMEWIDGET_H
