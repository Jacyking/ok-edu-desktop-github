#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    ui->PushButton->setText("确定登录");

}

LoginForm::~LoginForm()
{
    delete ui;
}
