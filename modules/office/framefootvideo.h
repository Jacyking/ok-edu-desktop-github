#ifndef FRAMEFOOTVIDEO_H
#define FRAMEFOOTVIDEO_H

#include "framefoot.h"

#include <QLabel>
#include <QMainWindow>
#include <QSlider>
#include <QWidget>

namespace office {


class FrameFootVideo : public FrameFoot
{
    Q_OBJECT
public:
    explicit FrameFootVideo(QWidget *parent = nullptr);

    void setPlayTime(double time);

    void setTotalTime(double time);

    void setVolume(int64_t volume);

    void setPlayPercent(int64_t percent);

    void setPauseResume(bool v);

    virtual const QSlider* volumeSlider() const {
        return volume_slider_;
    }

    virtual const QSlider* playSlider() const {
        return play_slider_;
    }

    virtual const QPushButton* muteButton() const {
        return mute_btn_;
    }

    virtual const QPushButton* playButton() const {
        return play_btn_;
    }

private:

    QPushButton* play_btn_;
    QPushButton* mute_btn_;
    QSlider* play_slider_;
    QSlider* volume_slider_;
    QLabel* play_time_;
    QLabel* total_time_;

signals:

public slots:

};

}
#endif // FRAMEFOOTVIDEO_H
