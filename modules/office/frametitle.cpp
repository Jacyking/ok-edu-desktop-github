#include "frametitle.h"

#include <QLabel>
#include <QPushButton>



namespace office {


FrameTitle::FrameTitle(QWidget *parent) :
    MoveableBar(parent)
{
    setFixedHeight(50);

    layout_ = new QHBoxLayout(this);

    title_ = new QLabel(this);
    layout_->addWidget(title_);
    layout_->setAlignment(title_, Qt::AlignCenter);

    //关闭最小化盒子
    closeBox = new QWidget(this);

    QHBoxLayout* _hLayout = new QHBoxLayout(closeBox);

    _hLayout->setContentsMargins(QMargins(0, 0, 0, 0));
    _hLayout->setAlignment(Qt::AlignVCenter);
    _hLayout->addStretch();

    QPushButton* minimizeBtn = new QPushButton(closeBox);
    minimizeBtn->setObjectName("minimize");
    minimizeBtn->setCursor(QCursor(Qt::PointingHandCursor));
    _hLayout->addWidget(minimizeBtn);
    _hLayout->setAlignment(minimizeBtn, Qt::AlignVCenter);

    _hLayout->addSpacerItem(new QSpacerItem(20, 20));

    QPushButton* closeBtn = new QPushButton(closeBox);
    closeBtn->setObjectName("close");
    closeBtn->setCursor(QCursor(Qt::PointingHandCursor));
    _hLayout->addWidget(closeBtn);
    _hLayout->setAlignment(closeBtn, Qt::AlignVCenter);

    //发送关闭事件
    connect(closeBtn, &QPushButton::clicked,
            [this](bool v){
            emit closeFrame(v);
    });


    layout_->addWidget(closeBox);


    setLayout(layout_);

}

FrameTitle::~FrameTitle()
{

}

void FrameTitle::setTitle(const QString &title)
{
    title_->setText(title);
}




}
