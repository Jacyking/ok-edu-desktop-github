#include "OMainTitleBar.h"
#include "ui_OMainTitleBar.h"


OMainTitleBar::OMainTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OMainTitleBar)
{
    ui->setupUi(this);

    ui->title_content_widget->setAttribute(Qt::WA_TransparentForMouseEvents);
}

OMainTitleBar::~OMainTitleBar()
{
    delete ui;
}

