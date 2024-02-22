
#include "OCountDown.h"
#include "ui_OCountDown.h"

OCountDown::OCountDown(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OCountDown)
{
    ui->setupUi(this);
}

OCountDown::~OCountDown()
{
    delete ui;
}
