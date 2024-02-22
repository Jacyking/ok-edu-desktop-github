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
#ifndef WINDOW_VIDEO_PLAYER_H
#define WINDOW_VIDEO_PLAYER_H

#include <QLabel>
#include <QToolButton>
#include <QWidget>
#include <QMainWindow>

// #include <framelesswindow/framelesswindow.h>

#include "UI/component/OVideoPlayer.h"

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE

namespace Ui
{
    class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void setSource(const QUrl &url);
    void play();

protected slots:
    void on_btnMin_clicked();
    void on_btnMax_clicked();
    void on_btnClose_clicked();
    void on_bthFull_clicked();

private:
    Ui::VideoPlayer *ui;

    OVideoPlayer *videoPlayer_;
};

#endif
