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
#pragma once

#include <memory>
#include "lib/network/NetworkManager.h"
#include "lib/network/backend/domain/RoomInfo.h"
#include "qobjectdefs.h"
#include "qradiobutton.h"
#include <QDialog>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class RoomSelectDialog : public QDialog {
  Q_OBJECT

public:
  RoomSelectDialog(QWidget *parent = 0);
  ~RoomSelectDialog();

  void setRooms(const std::list<ok::backend::RoomInfo> &roomInfos);
  // void paintEvent(QPaintEvent *e) override;

private:
  QLabel *label_select_role;
  QLabel *label_select_room;

  QRadioButton *_teacher;
  QRadioButton *_student;

  QPushButton *findButton;

  QWidget *extension;
  QButtonGroup *roleGroup;
  QButtonGroup *roomGroup;
  std::unique_ptr<QHBoxLayout> roomLayout;
  // std::list<ok::backendRoomInfo> roomInfos;
//  lib::IM::IM *_im;
  signals :
    void confirm();
  public slots:
    void onConfirm();

};
