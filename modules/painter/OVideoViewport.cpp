﻿/** Copyright (c) 2022 船山信息 chuanshaninfo.com
OkEDU-Classroom is licensed under Mulan PubL v2.
You can use this software according to the terms and conditions of the Mulan
PubL v2. You may obtain a copy of Mulan PubL v2 at:
         http://license.coscl.org.cn/MulanPubL-2.0
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PubL v2 for more details.
*/
#include "OVideoViewport.h"
#include "ui_OVideoViewport.h"
#include "UI/window/widget/playerwidget.h"

#include "base/StringUtils.h"
#include "base/logs.h"

#include "lib/network/backend/UserService.h"
#include "lib/network/UserManager.h"

using namespace UI::widget;

OVideoViewport::OVideoViewport(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OVideoViewport),
      _gridLayout(Q_NULLPTR) {
  ui->setupUi(this);

//  auto userManager = networkManager_->userManager();

  // connect(userManager, &lib::IM::UserManager::left, this,
  //         &OVideoViewport::onLeft);

  // connect(userManager, &lib::IM::UserManager::statusEvent, this,
  //         &OVideoViewport::onPeerStatus);

  connect(this, &OVideoViewport::recvUserInfo, &OVideoViewport::onRecvUserInfo);

  _hLayout = static_cast<QHBoxLayout *>(ui->player_layout->layout());

  _gridLayout = static_cast<QGridLayout *>(ui->students_widget->layout());

  _delayCaller = new base::DelayedCallTimer();

  //一秒钟检查成员是否退出
  _timer = std::make_unique<QTimer>(this);
  _timer->start(500);
  connect(_timer.get(), SIGNAL(timeout()), this, SLOT(timerUp()));
}

OVideoViewport::~OVideoViewport() { delete ui; }

const std::list<PlayerWidget *> OVideoViewport::playerWidgets() const {
  std::list<PlayerWidget *> list;

  for (int i = 0; i < _hLayout->count(); i++) {
    QLayoutItem *it = _hLayout->itemAt(i);
    PlayerWidget *player = qobject_cast<PlayerWidget *>(it->widget());
    if (player) {
      list.push_back(player);
    }
  }

  for (int i = 0; i < _gridLayout->count(); i++) {
    QLayoutItem *it = _gridLayout->itemAt(i);
    PlayerWidget *player = qobject_cast<PlayerWidget *>(it->widget());
    if (player) {
      list.push_back(player);
    }

    PlayerWidgetShadow *shadow =
        qobject_cast<PlayerWidgetShadow *>(it->widget());
    if (shadow && shadow->player()) {
      list.push_back(shadow->player());
    }
  }

  return list;
}

UI::widget::PlayerWidget *
OVideoViewport::findByUserJID(const backend::UserJID &jid) {
  const std::list<PlayerWidget *> list = playerWidgets();
  for (PlayerWidget *player : list) {
    if (player && player->peerJID() == jid) {
      return player;
    }
  }

  return nullptr;
}

UI::widget::PlayerWidget *OVideoViewport::findMine() {

//  backend::UserInfo *myInfo = networkManager_->userManager()->myInfo();
//  if (myInfo) {
//    return findByUserJID(myInfo->getJID());
//  }

  return nullptr;
}

void OVideoViewport::showEvent(QShowEvent *e) {
  // TODO
  // Q_UNUSED(e);
  // _showTimes++;
  // if (_showTimes == 1) {

  //   _delayCaller->call(1200, [this]() {
  //     // SmartBoard
  //     auto smartBoard = networkManager_->GetIM()->getSmartBoard();
  //     connect(smartBoard, &network::smartboard::IMSmartBoard::ss,
  //             [this](const std::list<std::string> &users, bool mute) {
  //               const std::list<PlayerWidget *> pwList = playerWidgets();
  //               for (PlayerWidget *pw : pwList) {
  //                 for (auto u : users) {
  //                   if (pw->peerJID().id.username() == u) {

  //                     DEBUG_LOG_S(L_INFO) << ("doMute for:") << qstring(u);

  //                     pw->setMute(mute);

  //                     std::string me = networkManager_->userManager()
  //                                          ->myInfo()
  //                                          ->getUin()
  //                                          .toStdString();
  //                     if (base::str_equals(me, u, false)) {
  //                       //设置自己为静音/非静音
  //                       lib::IM::IMJingle *jingle =
  //                           networkManager_->GetIM()->jingle();
  //                       jingle->setMute(mute);
  //                     }

  //                     break;
  //                   }
  //                 }
  //               }
  //             });
  //   });
  // }
}

bool OVideoViewport::isExist(const backend::UserJID &jid) {
  return findByUserJID(jid) != nullptr;
}

const std::list<ok::backendUserJID> OVideoViewport::isCheckedUsers() const {
  std::list<ok::backendUserJID> list;
  const std::list<PlayerWidget *> players = playerWidgets();
  for (PlayerWidget *player : players) {
    if (player->isChecked()) {
      list.push_back(player->peerJID());
    }
  }
  return list;
}

void OVideoViewport::getRowColForStudent(int &ir, int &ic) {
  int columnCount = _gridLayout->columnCount();
  int rowCount = _gridLayout->rowCount();
  for (int r = 0; r < rowCount; r++) {
    for (int c = 0; c < columnCount; c++) {
      QLayoutItem *occupy = _gridLayout->itemAtPosition(r, c);
      if (occupy == nullptr) {
        ir = r;
        ic = c;
        return;
      }
    }
  }
  ir = -1;
  ic = -1;
}

void OVideoViewport::onRecvUserInfo(const backend::UserInfo &userInfo) {
  std::lock_guard<std::mutex> lock(_JoinLeftMutex);
  DEBUG_LOG(("begin"));
#if 0
  if (isExist(userInfo.getJID())) {
    DEBUG_LOG(("isExist:%1").arg(qstring(userInfo.getJID().id.full())));
    return;
  }

  bool is_my = networkManager_->userManager()->isMy(userInfo);
  bool is_teacher = networkManager_->userManager()->isTeacher(
      const_cast<ok::backendUserInfo &>(userInfo));
  DEBUG_LOG(("onJionedUser:%1 isTeacher:%2 userJid:{%3, %4}")
                .arg(userInfo.getUin())
                .arg(is_teacher)
                .arg(qstring(userInfo.getJID().id.full()))
                .arg(qstring(userInfo.getJID().from.full())));

  if (is_teacher) {
    //教师
    VideoWidgetConfig config = {is_my ? VIDEO_MODE::CAMERA : VIDEO_MODE::PLAYER,
                                VIDEO_SIZE::MIDDLE, VIDEO_FOR::TEACHER};

    UI::widget::PlayerWidget *_player_left =
        new UI::widget::PlayerWidget(this, nullptr, nullptr,

                                     config, userInfo.getJID());
    auto op = ui->player_left_widget;
    ui->player_layout->replaceWidget(ui->player_left_widget, _player_left);
    // XXX
    //  delete op;

    _player_left->start();
    _player_left->setPeerName(userInfo.getName());
  } else {
    // row column
    int r;
    int c;

    getRowColForStudent(r, c);

    if (r < 0) {
      DEBUG_LOG(("student grid layout is full!"));
      return;
    }

    //学员
    VideoWidgetConfig config = {is_my ? VIDEO_MODE::CAMERA
                                      : VIDEO_MODE::PLAYER, //
                                VIDEO_SIZE::SMALL,          //
                                VIDEO_FOR::STUDENT};        //

    auto _gridLayout =
        static_cast<QGridLayout *>(ui->students_widget->layout());

    widget::PlayerWidget *uw = new widget::PlayerWidget(this,        //
                                                        nullptr,     //
                                                        _gridLayout, //

                                                        config,             //
                                                        userInfo.getJID()); //
    _gridLayout->addWidget(uw, r, c);
    uw->setPeerName(userInfo.getName());
    uw->start();
  }
#endif
  DEBUG_LOG(("end"));
}

void OVideoViewport::onJoined(const backend::UserJID &jid) {
#if 0
  DEBUG_LOG(("UserJID:%1").arg(qstring(jid.id.full())));

  backend::UserService _userService;
  _userService.getByUin(
      qstring(jid.id.username()), [&, jid](const backend::UserInfo &info) {
        if (0 < info.getId()) {
          //            if(!_NetworkManager->userManager()->isTeacher(info)){
          _students.insert(
              std::pair<PeerUIN, backend::UserJID>(jid.id.username(), jid));
          //            }
          const_cast<ok::backendUserInfo &>(info).setJID(jid);
          emit recvUserInfo(info);
        }
      });
#endif
}

void OVideoViewport::onLeft(const backend::UserJID &jid) {
  std::lock_guard<std::mutex> lock(_JoinLeftMutex);

//  DEBUG_LOG(("UserJID:%1").arg(qstring(jid.id.full())));

  UI::widget::PlayerWidget *player = findByUserJID(jid);
  if (player) {
    player->setDisabled();
  }
}

void OVideoViewport::onPeerStatus(const backend::UserJID &jid,
                                  const backend::PeerStatus &status) {
  UI::widget::PlayerWidget *pw = findByUserJID(jid);
  if (pw) {
    pw->setPeerStatus(status);
  }
}

void OVideoViewport::timerUp() {
  std::lock_guard<std::mutex> lock(_JoinLeftMutex);

  auto it = _students.begin();
  for (; it != _students.end();) {
    const backend::UserJID j = it->second;
    UI::widget::PlayerWidget *player = this->findByUserJID(j);
    if (player == nullptr || player->disabled()) {
      DEBUG_LOG(("Remove JID:%1").arg( (j.id )));
      _students.erase(it++);
      if (player) {
        DEBUG_LOG_S(L_INFO) << ("Remove PlayerWidget:") << (player);
        delete player;
        player = nullptr;
      }
    } else {
      it++;
    }
  }
}
