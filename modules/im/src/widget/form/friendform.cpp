#include "friendform.h"
#include "lib/network/backend/UserService.h"
#include "ui_friendform.h"

FriendForm::FriendForm(ok::backend::OrgStaff *staff_, QWidget *parent)
    : QFrame(parent), ui(new Ui::FriendForm), staff(staff_) {
  ui->setupUi(this);
  ui->no->setText(staff->no);
  ui->username->setText(staff->username);
  ui->name->setText(staff->name);
  ui->phone->setText(staff->phone);

  connect(ui->addFriend, &QPushButton::clicked,
          [&]() { emit onClicked(staff->username); });
}

FriendForm::~FriendForm() {
  delete staff;
  delete ui;
}
