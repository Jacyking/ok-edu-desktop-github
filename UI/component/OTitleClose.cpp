
#include "OTitleClose.h"
#include "ui_OTitleClose.h"

OTitleClose::OTitleClose(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OTitleClose)
{
    ui->setupUi(this);
}

OTitleClose::~OTitleClose()
{
    delete ui;
}
