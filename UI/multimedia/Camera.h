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

#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QVideoWidget>
#include <memory>

namespace multimedia {

class Camera : public QVideoWidget {

public:
  explicit Camera(QVideoWidget *parent = nullptr);
  ~Camera();

  void init();

  void startCamera();
  void stopCamera();

  void stop();

private slots:

  void record();
  void pause();
  void setMuted(bool);

  void toggleLock();
  void takeImage();
  void displayCaptureError(int, QCameraImageCapture::Error,
                           const QString &errorString);

  void configureCaptureSettings();
  void configureVideoSettings();
  void configureImageSettings();

  void displayRecorderError();
  void displayCameraError();

  void updateCameraDevice(QAction *action);

  void updateCameraState(QCamera::State);
  void updateCaptureMode();
  void updateRecorderState(QMediaRecorder::State state);
  void setExposureCompensation(int index);

  void updateRecordTime();

  void processCapturedImage(int requestId, const QImage &img);
  void updateLockStatus(QCamera::LockStatus, QCamera::LockChangeReason);

  void displayViewfinder();
  void displayCapturedImage();

  void readyForCapture(bool ready);
  void imageSaved(int id, const QString &fileName);

protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void closeEvent(QCloseEvent *event) override;

private:
  std::unique_ptr<QCamera> camera;
  std::unique_ptr<QCameraImageCapture> imageCapture;
  std::unique_ptr<QMediaRecorder> mediaRecorder;

  /*	QImageEncoderSettings imageSettings;
          QAudioEncoderSettings audioSettings;
          QVideoEncoderSettings videoSettings;*/

  QString videoContainerFormat;
  bool isCapturingImage = false;
  bool applicationExiting = false;
};

} // namespace multimedia
