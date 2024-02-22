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
#include "VideoPlayer.h"
#include "UI/component/OTitleBar.h"
#include "ui_VideoPlayer.h"
#include <QMessageBox>
#include <QRect>

#include <base/logs.h>

VideoPlayer::VideoPlayer(QWidget *parent) : QMainWindow(parent),
                                            ui(new Ui::VideoPlayer)
{
    DEBUG_LOG_S(L_INFO) << "...";

    ui->setupUi(this);

    // setResizeableAreaWidth(8);

    // OTitleBar *bar = ui->title_bar;
    // setTitleBar(bar);
    // addIgnoreWidget(bar->getTitle());

    //初始化播放器
    videoPlayer_ = ui->videoPlayer;
    videoPlayer_->start();
}

VideoPlayer::~VideoPlayer()
{
    DEBUG_LOG_S(L_INFO) << "...";
    videoPlayer_->stop();
    delete ui;
}

void VideoPlayer::setSource(const QUrl &url)
{
    videoPlayer_->setSource(url);
}

void VideoPlayer::play()
{
    videoPlayer_->play();
}

void VideoPlayer::on_btnMin_clicked()
{
    showMinimized();
}
void VideoPlayer::on_btnMax_clicked()
{
    if (isMaximized())
        showNormal();
    else
        showMaximized();
}
void VideoPlayer::on_btnClose_clicked()
{
    close();
}

void VideoPlayer::on_bthFull_clicked()
{
    if (isFullScreen())
        showNormal();
    else
        showFullScreen();
}
