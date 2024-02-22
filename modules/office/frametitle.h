#ifndef FRAMETITLE_H
#define FRAMETITLE_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>


#include <UI/widget/MoveableBar.h>
#include <base/utils.h>


namespace office {

using namespace UI::widget;
using namespace base;

class FrameTitle : public MoveableBar {
  Q_OBJECT
public:
  explicit FrameTitle(QWidget *parent = nullptr);
  virtual ~FrameTitle() override;

  virtual void setTitle(const QString &title);

private:
  QWidget *closeBox;

  QHBoxLayout *layout_;

  QLabel *title_;

signals:
  void closeFrame(bool);

public slots:
};

} // namespace office
#endif // FRAMETITLE_H
