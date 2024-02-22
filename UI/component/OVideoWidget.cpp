#include "OVideoWidget.h"
#include "ui_OVideoWidget.h"

OVideoWidget::OVideoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OVideoWidget)
{
    ui->setupUi(this);
}

OVideoWidget::~OVideoWidget()
{
    delete ui;
}
