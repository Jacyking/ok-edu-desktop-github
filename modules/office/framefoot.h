#ifndef FRAMEFOOT_H
#define FRAMEFOOT_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>


#include <UI/widget/MoveableBar.h>
#include <base/utils.h>


namespace office {

using namespace base;
using namespace UI::widget;

class FrameFoot : public MoveableBar {
  Q_OBJECT
public:
  explicit FrameFoot(QWidget *parent = nullptr);

protected:
  QHBoxLayout *layout_;

signals:

public slots:
};

} // namespace office
#endif // FRAMEFOOT_H
