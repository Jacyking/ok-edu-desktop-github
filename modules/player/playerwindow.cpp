/******************************************************************************
    Simple Player:  this file is part of QtAV examples
    Copyright (C) 2012-2016 Wang Bin <wbsecg1@gmail.com>

*   This file is part of QtAV

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "playerwindow.h"
#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QMessageBox>
#include <MediaIO.h>
#include <QToolButton>

namespace player{

const qreal kVolumeInterval = 0.1;

PlayerWindow::PlayerWindow(QWidget *parent) : CFramelessWindow(parent)
{

    setResizeableAreaWidth(8);

//    CFramelessTitlebar* titlebar = new  CFramelessTitlebar(this) ;
//    setTitleBar(titlebar);


//    setWindowTitle(QString::fromLatin1("QtAV simple player example"));


    m_unit = 1000;
    m_player = new AVPlayer(this);

//    QFrame* frame = new QFrame(frame());

//    frame->move(20, 20);


    QVBoxLayout *vl = new QVBoxLayout(this);
    m_vo = new VideoOutput(this);
    if (!m_vo->widget()) {
        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    m_player->setRenderer(m_vo);
    vl->addWidget(m_vo->widget());

    QHBoxLayout *hb = new QHBoxLayout();
    vl->addLayout(hb);

    //播放按钮
    m_playBtn = new QToolButton(this);
    m_playBtn->setIcon(QIcon(QString::fromLatin1(":/resources/icon/player_play.png")));
    m_playBtn->setCheckable(true);
    hb->addWidget(m_playBtn);

    //进度条
    m_slider = new QSlider();
    m_slider->setOrientation(Qt::Horizontal);
    connect(m_slider, SIGNAL(sliderMoved(int)), SLOT(seekBySlider(int)));
    connect(m_slider, SIGNAL(sliderPressed()), SLOT(seekBySlider()));
//    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider(qint64)));
//    connect(m_player, SIGNAL(started()), SLOT(updateSlider()));
//    connect(m_player, SIGNAL(notifyIntervalChanged()), SLOT(updateSliderUnit()));

    connect(m_player, SIGNAL(error(QtAV::AVError)), this, SLOT(handleError(QtAV::AVError)));
    connect(m_player, SIGNAL(started()), this, SLOT(onStartPlay()));
    connect(m_player, SIGNAL(stopped()), this, SLOT(onStopPlay()));
    connect(m_player, SIGNAL(paused(bool)), this, SLOT(onPaused(bool)));
//    connect(m_player, SIGNAL(speedChanged(qreal)), this, SLOT(onSpeedChange(qreal)));
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChange(qint64)));

//    connect(m_player, SIGNAL(volumeChanged(qreal)), SLOT(syncVolumeUi(qreal)));

    hb->addWidget(m_slider);

    //停止按钮
    m_stopBtn = new QPushButton(tr("Stop"));
    hb->addWidget(m_stopBtn);

    //时间
    mpCurrent = new QLabel(this);
    mpCurrent->setToolTip(tr("Current time"));
    mpCurrent->setContentsMargins(QMargins(2, 2, 2, 2));
    mpCurrent->setText(QString::fromLatin1("00:00:00"));
    hb->addWidget(mpCurrent);

    hb->addWidget(new QLabel("/"));

    mpEnd = new QLabel(this);
        mpEnd->setToolTip(tr("Duration"));
        mpEnd->setContentsMargins(QMargins(2, 2, 2, 2));
        mpEnd->setText(QString::fromLatin1("00:00:00"));
    hb->addWidget(mpEnd);

    //静音按钮

    m_muteBtn = new QPushButton(tr("Mute"));
    m_muteBtn->setCheckable(true);
    hb->addWidget(m_muteBtn);

    //音量进度
    m_volumeSlider = new QSlider();
    m_volumeSlider->setOrientation(Qt::Horizontal);
    hb->addWidget(m_volumeSlider);


    connect(m_volumeSlider, SIGNAL(sliderPressed()), SLOT(setVolume()));
    connect(m_volumeSlider, SIGNAL(valueChanged(int)), SLOT(setVolume()));
    connect(m_playBtn, SIGNAL(clicked()), SLOT(playPause()));
    connect(m_stopBtn, SIGNAL(clicked()), m_player, SLOT(stop()));
    connect(m_muteBtn, SIGNAL(clicked()), SLOT(muteVolume()));
}

void PlayerWindow::setSource(const QUrl &url)
{
    if (m_source == url)
        return;

    m_source = url;
    if (url.isLocalFile() || url.scheme().isEmpty()
            || url.scheme().startsWith("qrc")
            || url.scheme().startsWith("avdevice")
            // TODO: what about custom io?
            )
        m_player->setFile(QUrl::fromPercentEncoding(url.toEncoded()));
    else
        m_player->setFile(url.toEncoded());
}

void PlayerWindow::player()
{
    m_player->play();
}

void PlayerWindow::setIODevice(QIODevice* qIODevice)
{
    m_player->setIODevice(qIODevice);
}

void PlayerWindow::setVolume()
{
    AudioOutput *ao = audioOutput();
    qreal v = qreal(m_volumeSlider->value())*kVolumeInterval;
    if (ao) {
        if (qAbs(int(ao->volume()/kVolumeInterval) - m_volumeSlider->value()) >= int(0.1/kVolumeInterval)) {
            ao->setVolume(v);
        }
    }
    m_volumeSlider->setToolTip(QString::number(v));
    m_muteBtn->setToolTip(QString::number(v));
    if(v <= 0){
        m_muteBtn->setChecked(true);
    }else
        m_muteBtn->setChecked(false);
}

void PlayerWindow::muteVolume()
{
    qreal v ;
    AudioOutput *ao = audioOutput();
    if(ao->volume() <= 0){
        v = qreal(40)*kVolumeInterval;
        m_volumeSlider->setValue(40);
    }else{
        v = 0;
        m_volumeSlider->setValue(0);
    }
    ao->setVolume(v);
}

void PlayerWindow::syncVolumeUi(qreal value)
{
    int v = 0;
    if( 0 < value){
        v = (value/kVolumeInterval);
    }
    m_volumeSlider->setValue(v);
}


void PlayerWindow::seekBySlider(int value)
{
    if (!m_player->isPlaying())
        return;
    m_player->seek(qint64(value*m_unit));
}

void PlayerWindow::seekBySlider()
{
    seekBySlider(m_slider->value());
}

void PlayerWindow::playPause()
{
    if (!m_player->isPlaying()) {
        m_player->play();
        return;
    }
    m_player->pause(!m_player->isPaused());
}

void PlayerWindow::onPositionChange(qint64 pos)
{
    m_slider->setRange(0, int(m_player->duration()/m_unit));
    m_slider->setValue(int(pos/m_unit));

    mpCurrent->setText(QTime(0, 0, 0).addMSecs(pos)
                       .toString(QString::fromLatin1("HH:mm:ss"))
                       );
}

void PlayerWindow::onStartPlay()
{
    mpEnd->setText(QTime(0, 0, 0)
                   .addMSecs(m_player->mediaStopPosition())
                   .toString(QString::fromLatin1("HH:mm:ss"))
                   );


    m_playBtn->setIcon(QIcon(QString::fromLatin1(":/resources/icon/player_pause.png")));

    m_slider->setValue(0);
    m_slider->setMinimum(m_player->mediaStartPosition());
    m_slider->setMaximum(m_player->mediaStopPosition());
    m_slider->setEnabled(m_player->isSeekable());

    AudioOutput *ao = audioOutput();
    if(ao){

        m_volumeSlider->setValue((ao->volume()/kVolumeInterval));
    }

    onPositionChange(m_player->position());
}

void PlayerWindow::onPaused(){

}

void PlayerWindow::onStopPlay()
{
//    onPositionChange(m_player->position());
    mpEnd->setText(QString::fromLatin1("00:00:00"));
    mpCurrent->setText(QString::fromLatin1("00:00:00"));

    m_slider->setValue(0);
    m_slider->setMinimum(0);
    m_slider->setMaximum(0);
    m_slider->setDisabled(true);


    m_playBtn->setIcon(QIcon(QString::fromLatin1(":/resources/icon/player_play.png")));

}



void PlayerWindow::updateSliderUnit()
{
//    m_unit = m_player->notifyInterval();
//    updateSlider();
}


}
