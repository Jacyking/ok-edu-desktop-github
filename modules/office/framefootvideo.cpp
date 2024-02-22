#include "framefootvideo.h"

#include <base/times.h>

namespace office
{

    FrameFootVideo::FrameFootVideo(QWidget *parent) : FrameFoot(parent)
    {

        play_btn_ = new QPushButton(this);
        play_btn_->setCheckable(true);
        layout_->addWidget(play_btn_);

        play_slider_ = new QSlider(Qt::Horizontal, this);
        play_slider_->setMinimum(0);
        //    play_slider_->setMaximum(100);
        layout_->addWidget(play_slider_);

        play_time_ = new QLabel(this);
        layout_->addWidget(play_time_);

        total_time_ = new QLabel(this);
        layout_->addWidget(total_time_);

        mute_btn_ = new QPushButton(this);
        mute_btn_->setCheckable(true);
        layout_->addWidget(mute_btn_);

        volume_slider_ = new QSlider(Qt::Horizontal, this);
        volume_slider_->setMinimum(0);
        volume_slider_->setMaximum(100);

        layout_->addWidget(volume_slider_);
    }

    void FrameFootVideo::setPlayTime(double time)
    {
        int ms = static_cast<int>(time) * 1000;
        play_time_->setText(QString::fromStdString(base::Times::formatTime(ms)));
        play_slider_->setValue(static_cast<int>(time));
    }

    void FrameFootVideo::setTotalTime(double time)
    {
        int ms = static_cast<int>(time) * 1000;
        total_time_->setText(QString::fromStdString(base::Times::formatTime(ms)));
        play_slider_->setMaximum(static_cast<int>(time));
    }

    void FrameFootVideo::setVolume(int64_t volume)
    {
        volume_slider_->setValue(volume);
    }

    void FrameFootVideo::setPlayPercent(int64_t percent)
    {
        play_slider_->setValue(percent);
    }

    void FrameFootVideo::setPauseResume(bool v)
    {
        play_btn_->setChecked(v);
    }

}
