#include "LoginTitleBar.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPushButton>


#include "base/r.h"
#include "UI/resources.h"
#include <UI/widget/MoveableBar.h>
#include <base/widgets.h>


namespace UI {

namespace widget {

using namespace UI::widget;

LoginTitleBar::LoginTitleBar(QWidget *parent)
    : MoveableBar(parent), minimizeBtn(nullptr), closeBtn(nullptr) {
  setFixedHeight(35);
  setFixedWidth(parent->width());

  base::Widgets::SetPalette(this, QPalette::Background,
                                 QColor(DEFAULT_BG_COLOR));

  auto w = this->width();

  // 关闭最小化按钮
  box = new QWidget(this);
  // box->setStyleSheet("QWidget{border: 1px solid #f00}");
  box->show();

  QHBoxLayout *_hLayout = new QHBoxLayout(box);
  _hLayout->setContentsMargins(QMargins(0, 0, 0, 0));
  _hLayout->setSpacing(0);
  _hLayout->addStretch();

  QPushButton *minimizeBtn = new QPushButton(box);
  minimizeBtn->setObjectName("title_btn_minimize");
  minimizeBtn->setProperty(QSS_CLASS, "title_btn_minimize");
  minimizeBtn->setCursor(QCursor(Qt::PointingHandCursor));
  _hLayout->addWidget(minimizeBtn);

  QPushButton *closeBtn = new QPushButton(box);
  closeBtn->setObjectName("title_btn_close");
  closeBtn->setProperty(QSS_CLASS, "title_btn_close");
  closeBtn->setCursor(QCursor(Qt::PointingHandCursor));
  _hLayout->addWidget(closeBtn);

  _hLayout->setAlignment(Qt::AlignRight);

  connect(minimizeBtn, SIGNAL(clicked()), this, SLOT(onButtoMinClicked()));
  connect(closeBtn, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));

  //设置样式
  QString qss = utils::Resources::loadQss(utils::QSS::titlebar);
  setStyleSheet(qss);
}

LoginTitleBar::~LoginTitleBar() {}

void LoginTitleBar::paintEvent(QPaintEvent *event) {}

void LoginTitleBar::showEvent(QShowEvent *event) {
  auto parent = qobject_cast<QWidget *>(this->parent());
  box->setFixedWidth(parent->width());
  // box->setFixedHeight(parent->height());
}
void LoginTitleBar::onButtoMinClicked() {
  QWidget *w = m_target;
  if (!w) {
    w = qobject_cast<QWidget *>(this->parent());
  }
  w->showMinimized();
}

void LoginTitleBar::onButtonCloseClicked() { qApp->exit(0); }

} // namespace widget
} // namespace UI
