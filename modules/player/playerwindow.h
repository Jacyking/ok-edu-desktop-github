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

#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <AudioOutput.h>
#include <QLabel>
#include <QToolButton>
#include <QWidget>

#ifdef QtAV
#include <QtAV>
#endif

#include <UI/window/widget/OResizeWidget.h>
#include <framelesswindow/framelesswindow.h>

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE

namespace player {

using namespace UI::widget;

class PlayerWindow : public CFramelessWindow
{
    Q_OBJECT
public:
    explicit PlayerWindow(QWidget *parent = nullptr);

    const QUrl& source() const{
        return m_source;
    }


    void setSource(const QUrl& url);
    void player();


public slots:

    void setIODevice(QIODevice *qIODevice);
    void seekBySlider(int value);
    void seekBySlider();
    void playPause();


private slots:
    void setVolume();
    void onPositionChange(qint64 value);
    void onStartPlay();
    void onStopPlay();
    void updateSliderUnit();

    void muteVolume();

    void syncVolumeUi(qreal value);
    void onPaused();
private:

    AudioOutput* audioOutput(){
        return m_player ? m_player->audio() : nullptr;
    }


    QUrl m_source;
#ifdef QtAV
    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *m_player;
#endif

    QSlider *m_slider;
    QToolButton *m_playBtn;
    QPushButton *m_stopBtn;

    QLabel* mpCurrent;
    QLabel* mpEnd;

    QPushButton *m_muteBtn; //静音
    QSlider *m_volumeSlider;


    int m_unit;
};


}


#endif // PLAYERWINDOW_H
