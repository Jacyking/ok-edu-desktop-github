#include "framewidget.h"
#include "frametitle.h"


#include <UI/widget/MoveableBar.h>
#include <UI/window/widgetfactory.h>
#include <base/logs.h>
#include <base/utils.h>


namespace office {

using namespace base;

FrameWidget::FrameWidget(QWidget *parent) : QFrame(parent), frameWidth_(10) {
  //    if(parent){
  //        setFixedSize(parent->size());
  //    }

  //自动析构
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  setAcceptDrops(false);

  setStyleSheet("frame{border:2px solid rgb(0,255,0)}");

  layout_v_ = new QVBoxLayout(this);
  layout_v_->setSpacing(0);
  layout_v_->setContentsMargins(QMargins(0, 0, 0, 0));

  //    bar_ = new UI::widget::MoveableBar(this);
  bar_ = UI::WidgetFactory::CreateWidget<FrameTitle>(this);

  layout_v_->addWidget(bar_);
  layout_v_->setAlignment(bar_, Qt::AlignTop);

  //    连接关闭事件

  //    connect(bar_, &FrameTitle::closeFrame, )

  //    QWidget *content = getContentWidget();
  //    layout_v_->addWidget(content);

  //    foo_ = new UI::widget::MoveableBar(this);
  //    foo_->setFixedHeight(20);
  //    layout_v_->addWidget(foo_);

  // setLayout(layout_v_);
}

FrameWidget::~FrameWidget() { DEBUG_LOG_S(L_INFO); }

void FrameWidget::setMoveableTarget(QWidget *target) {
  bar_->setTarget(target);
  if (foo_) {
    foo_->setTarget(target);
  }
}

void FrameWidget::setTitle(const QString &title) { bar_->setTitle(title); }

QRect FrameWidget::innerRect() {
  return QRect(frameWidth_, frameWidth_, this->width() - frameWidth_ * 2,
               this->height() - frameWidth_ * 2);
}

} // namespace office
