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
#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QFrame>
#include <QGridLayout>
#include <QObject>
#include <QWidget>

#include <UI/widget/MoveableBar.h>
#include <base/timer.h>

#include "lib/network/backend/User.h"
#include "modules/painter/WhiteboardController.h"

#include "UI/core/ui.h"
#include "UI/window/layout/FlowLayout.h"
#include "VideoWidget.h"
#include "lib/messenger/IMMessage.h"

namespace UI {

namespace page {
class Classing;
}

namespace widget {

class PlayerWidget;

class PlayerWidgetShadow : public QFrame {
  Q_OBJECT
public:
  PlayerWidgetShadow(QWidget *parent, PlayerWidget *player);

  virtual PlayerWidget *player() const { return _player; }

private:
  PlayerWidget *_player;
};

class PlayerWidget : public MoveableBar {
  Q_OBJECT
public:
  explicit PlayerWidget(QWidget *parent, QLayout *layout, QGridLayout *gLayout,
                        VideoWidgetConfig config, const lib::messenger::FriendId &id);

  virtual ~PlayerWidget() override;

  void setViewSize(VIDEO_SIZE size);

  void start();

  void stop();

  void setBorderRed();
  void setBorderBlue();

  void setChecked(bool checked);
  void setMute(bool checked);

  virtual const lib::messenger::FriendId &peerJID() { return _jid; }
  virtual void setPeerJID(const lib::messenger::FriendId &jid) { _jid = jid; }

  inline virtual const PlayerWidgetShadow *shadow() { return _shadow; }

  virtual void setPeerStatus(const ok::backend::PeerStatus &status);

  virtual void setPeerName(const QString &name);

  virtual void setDisabled();

  virtual bool left() { return _left; }

  virtual bool disabled() {
    return false; // return _videoWidget->disabled();
  }

  virtual bool isChecked() const { return _checked; }

protected:
  virtual void showEvent(QShowEvent *e) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
  virtual void resizeEvent(QResizeEvent *event) override;

private:
  VideoWidgetConfig _config;
  lib::messenger::FriendId _jid;

  bool _checked = false;

  bool _mute = false;

  bool _left = false;

  int _showTimes = 0;

  QWidget *_parent = nullptr;

  QLayout *_frame = nullptr;

  QGridLayout *_gLayout = nullptr;

  UI::WindowManager *_pageManager = nullptr;

  std::unique_ptr<VideoWidget> _videoWidget;

  std::unique_ptr<VideoOverlay> _overlay;

  PlayerWidgetShadow *_shadow;

signals:

public slots:

  void onCtrollerChecked(context::WB::WB_CTRL, bool);

  void goBack();

  void addSilverCoin(int coin);

  //    void onPeerStatus(PeerStatus status);
};

} // namespace widget
} // namespace UI
#endif // PLAYERWIDGET_H
