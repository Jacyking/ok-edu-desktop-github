/** Copyright (c) 2022 船山信息 chuanshaninfo.com
OkEDU-Classroom is licensed under Mulan PubL v2.
You can use this software according to the terms and conditions of the Mulan
PubL v2. You may obtain a copy of Mulan PubL v2 at:
         http://license.coscl.org.cn/MulanPubL-2.0
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PubL v2 for more details.
*/
#include <QtWidgets>
#include <memory>

#include "RoomSelectDialog.h"
#include "base/logs.h"
#include "qbuttongroup.h"
#include "qdialog.h"
#include "qglobal.h"
#include "qobjectdefs.h"
#include "qpushbutton.h"
#include "qradiobutton.h"
#include "qsize.h"
#include "qwidget.h"

#include "lib/network/NetworkManager.h"
#include "lib/messenger/messenger.h"
#include "lib/network/backend/ChatService.h"
#include "lib/network/backend/UserService.h"

//! [0]
RoomSelectDialog::RoomSelectDialog(QWidget *parent) : QDialog(parent) {
  setFixedSize(QSize(420, 360));
  setAttribute(Qt::WA_DeleteOnClose, true);

  label_select_role = new QLabel(tr("请选择角色"));
  label_select_room = new QLabel(tr("请选择班级"));

  //! [1]
  findButton = new QPushButton(tr("确定"));
  findButton->setDefault(true);

  //! [1]

  //! [2]
  extension = new QWidget;

  //! [2]

  //! [3]

  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(label_select_role);

  //! [4]
  QHBoxLayout *roleLayout = new QHBoxLayout();
  _teacher = new QRadioButton(tr("教师"));
  _student = new QRadioButton(tr("学员"));
  _student->setChecked(true);
  roleGroup = new QButtonGroup(this);
  roleGroup->setExclusive(true);
  roleGroup->addButton(_teacher, 1);
  roleGroup->addButton(_student, 0);

  roleLayout->addWidget(_teacher);
  roleLayout->addWidget(_student);

  leftLayout->addLayout(roleLayout);
  leftLayout->addWidget(label_select_room);

  roomLayout = std::make_unique<QHBoxLayout>();
  leftLayout->addLayout(roomLayout.get());

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);
  mainLayout->addLayout(leftLayout, 0, 0);
  mainLayout->addWidget(extension, 1, 0, 1, 2);
  mainLayout->setRowStretch(2, 1);
  mainLayout->addWidget(findButton);

  setLayout(mainLayout);

  setWindowTitle(tr("请选择"));
  //! [4] //! [5]
  extension->hide();

  /**
   * @brief 连接信号
   *
   */
 
  connect(findButton, SIGNAL(clicked()), this, SLOT(onConfirm()));
}

RoomSelectDialog::~RoomSelectDialog() {
  disconnect(findButton, SIGNAL(clicked()), this, SLOT(onConfirm()));
}

void RoomSelectDialog::setRooms(const std::list<ok::backend::RoomInfo> &roomInfos) {

  roomGroup = new QButtonGroup(this);
  roomGroup->setExclusive(true);

  int i = 0;
  for (ok::backend::RoomInfo room : roomInfos) {
    auto btn = new QRadioButton((room.getName()));
    btn->setProperty("sn", room.getSn());
    roomLayout->addWidget(btn);
    roomGroup->addButton(btn);
    if (i++ == 0) {
      btn->setChecked(true);
    }
  }
}

void RoomSelectDialog::onConfirm() {
  DEBUG_LOG_S(L_INFO) << "yes";

  auto roleBtn = roleGroup->checkedButton();
  if (!roleBtn) {
    return;
  }

  auto roomBtn = roomGroup->checkedButton();
  if (!roomBtn) {
    return;
  }

  ok::backend::UserService userService(this);
  if (roleBtn->text().compare("教师")) {
    userService.setUserType("Teacher");
  } else if (roleBtn->text().compare("学员")) {
    userService.setUserType("Student");
  }

  ok::backend::ChatService chatService(this);
  chatService.saveSn(roomBtn->property("sn").toString(),
                     [this, &chatService](bool success) {
                       DEBUG_LOG_S(L_INFO) << "saveSn" << (success);
                       emit confirm();
                       done(QDialog::Accepted);
                     });
}
