/*
 * Copyright (c) 2022 船山信息 chuanshaninfo.com
 * OkEDU is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PubL v2. You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */
#pragma once

#include "UI/window/widget/playerwidget.h"

#include <QWidget>
#include <mutex>

#include "lib/network/NetworkManager.h"
#include "lib/network/backend/domain/UserInfo.h"

namespace Ui {
class OVideoViewport;
}

class OVideoViewport : public QWidget {
  Q_OBJECT
public:
  explicit OVideoViewport(QWidget *parent = nullptr);
  virtual ~OVideoViewport() override;

  const std::list<UI::widget::PlayerWidget *> playerWidgets() const;

  UI::widget::PlayerWidget *findByUserJID(const backend::UserJID &jid);

  bool isExist(const backend::UserJID &jid);

  const std::list<ok::backendUserJID> isCheckedUsers() const;

  UI::widget::PlayerWidget *findMine();

protected:
  virtual void showEvent(QShowEvent *e) override;

private:
  Ui::OVideoViewport *ui;

  QHBoxLayout *_hLayout;
  QGridLayout *_gridLayout;

  backend::UserJIDMap _students;

  std::unique_ptr<QTimer> _timer;

  base::DelayedCallTimer *_delayCaller;

  std::mutex _JoinLeftMutex;

  int _showTimes = 0;

  void getRowColForStudent(int &ir, int &ic);

signals:
  void recvUserInfo(const backend::UserInfo &info);
  void voiceMute(bool mute);

public slots:
  void timerUp();
  void onJoined(const backend::UserJID &jid);
  void onLeft(const backend::UserJID &jid);

  void onPeerStatus(const backend::UserJID &jid,
                    const backend::PeerStatus &status);

  void onRecvUserInfo(const backend::UserInfo &userInfo);
};