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
#include "Camera.h"
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QKeyEvent>
#include <QMediaMetaData>
#include <QMediaRecorder>
#include <QMediaService>
#include <QMessageBox>
#include <QPalette>
#include <memory>

#include <QVideoWidget>
#include <base/logs.h>

namespace multimedia {

//    Q_DECLARE_METATYPE(QCameraInfo)

Camera::Camera(QVideoWidget *parent) : QVideoWidget(parent) {
  if (parent) {
    setFixedSize(parent->size());
  }

  //		const QList<QCameraInfo> availableCameras =
  //QCameraInfo::availableCameras(); 		for (const QCameraInfo &cameraInfo :
  //availableCameras) {
  //			DEBUG_LOG(("cameraInfo:%1").arg(cameraInfo.description()));
  //		}

  /*	QActionGroup *videoDevicesGroup = new QActionGroup(this);
          videoDevicesGroup->setExclusive(true);
          for (const QCameraInfo &cameraInfo : availableCameras) {
                  QAction *videoDeviceAction = new
     QAction(cameraInfo.description(), videoDevicesGroup);
                  videoDeviceAction->setCheckable(true);
                  videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
                  if (cameraInfo == QCameraInfo::defaultCamera())
                          videoDeviceAction->setChecked(true);
          }

          connect(videoDevicesGroup, &QActionGroup::triggered, this,
     &Camera::updateCameraDevice);*/
  // connect(ui->captureWidget, &QTabWidget::currentChanged, this,
  // &Camera::updateCaptureMode);
}

void Camera::init() {

  QCameraInfo cameraInfo = QCameraInfo::defaultCamera();

  // delete imageCapture;
  // delete mediaRecorder;
  // delete camera;

  camera = std::make_unique<QCamera>(cameraInfo);
  mediaRecorder = std::make_unique<QMediaRecorder>(camera.get());
  imageCapture = std::make_unique<QCameraImageCapture>(camera.get());
  mediaRecorder->setMetaData(QMediaMetaData::Title,
                             QVariant(QLatin1String("Test Title")));

  connect(camera.get(), &QCamera::stateChanged, this,
          &Camera::updateCameraState);
  connect(camera.get(), QOverload<QCamera::Error>::of(&QCamera::error), this,
          &Camera::displayCameraError);
  connect(camera.get(),
          QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(
              &QCamera::lockStatusChanged),
          this, &Camera::updateLockStatus);

  connect(mediaRecorder.get(), &QMediaRecorder::stateChanged, this,
          &Camera::updateRecorderState);
  connect(mediaRecorder.get(), &QMediaRecorder::durationChanged, this,
          &Camera::updateRecordTime);
  connect(mediaRecorder.get(),
          QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error), this,
          &Camera::displayRecorderError);

  // connect(ui->exposureCompensation, &QAbstractSlider::valueChanged, this,
  // &Camera::setExposureCompensation);

  updateCameraState(camera->state());
  updateLockStatus(camera->lockStatus(), QCamera::UserRequest);
  updateRecorderState(mediaRecorder->state());

  connect(imageCapture.get(), &QCameraImageCapture::readyForCaptureChanged,
          this, &Camera::readyForCapture);
  connect(imageCapture.get(), &QCameraImageCapture::imageCaptured, this,
          &Camera::processCapturedImage);
  connect(imageCapture.get(), &QCameraImageCapture::imageSaved, this,
          &Camera::imageSaved);
  connect(imageCapture.get(),
          QOverload<int, QCameraImageCapture::Error, const QString &>::of(
              &QCameraImageCapture::error),
          this, &Camera::displayCaptureError);

  camera->setViewfinder(this);

  camera->isCaptureModeSupported(QCamera::CaptureStillImage);
  camera->isCaptureModeSupported(QCamera::CaptureVideo);

  updateCaptureMode();
}

void Camera::keyPressEvent(QKeyEvent *event) {
  if (event->isAutoRepeat())
    return;

  switch (event->key()) {
  case Qt::Key_CameraFocus:
    displayViewfinder();
    camera->searchAndLock();
    event->accept();
    break;
  case Qt::Key_Camera:
    if (camera->captureMode() == QCamera::CaptureStillImage) {
      takeImage();
    } else {
      if (mediaRecorder->state() == QMediaRecorder::RecordingState)
        stop();
      else
        record();
    }
    event->accept();
    break;
  default:
    QVideoWidget::keyPressEvent(event);
  }
}

void Camera::keyReleaseEvent(QKeyEvent *event) {
  if (event->isAutoRepeat())
    return;

  switch (event->key()) {
  case Qt::Key_CameraFocus:
    camera->unlock();
    break;
  default:
    QVideoWidget::keyReleaseEvent(event);
  }
}

void Camera::updateRecordTime() {
  QString str =
      QString("Recorded %1 sec").arg(mediaRecorder->duration() / 1000);
  DEBUG_LOG((str));
}

void Camera::processCapturedImage(int requestId, const QImage &img) {
  // Q_UNUSED(requestId);
  // QImage scaledImage = img.scaled(ui->viewfinder->size(),
  // Qt::KeepAspectRatio, Qt::SmoothTransformation);

  // ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

  //// Display captured image for 4 seconds.
  // displayCapturedImage();
  // QTimer::singleShot(4000, this, &Camera::displayViewfinder);
}

void Camera::configureCaptureSettings() {
  switch (camera->captureMode()) {
  case QCamera::CaptureStillImage:
    configureImageSettings();
    break;
  case QCamera::CaptureVideo:
    configureVideoSettings();
    break;
  default:
    break;
  }
}

void Camera::configureVideoSettings() {
  /*VideoSettings settingsDialog(mediaRecorder);
  settingsDialog.setWindowFlags(settingsDialog.windowFlags() &
  ~Qt::WindowContextHelpButtonHint);

  settingsDialog.setAudioSettings(audioSettings);
  settingsDialog.setVideoSettings(videoSettings);
  settingsDialog.setFormat(videoContainerFormat);

  if (settingsDialog.exec()) {
          audioSettings = settingsDialog.audioSettings();
          videoSettings = settingsDialog.videoSettings();
          videoContainerFormat = settingsDialog.format();

          mediaRecorder->setEncodingSettings(
                  audioSettings,
                  videoSettings,
                  videoContainerFormat);
  }*/
}

void Camera::configureImageSettings() {
  /*ImageSettings settingsDialog(imageCapture);
  settingsDialog.setWindowFlags(settingsDialog.windowFlags() &
  ~Qt::WindowContextHelpButtonHint);

  settingsDialog.setImageSettings(imageSettings);

  if (settingsDialog.exec()) {
          imageSettings = settingsDialog.imageSettings();
          imageCapture->setEncodingSettings(imageSettings);
  }*/
}

void Camera::record() {
  mediaRecorder->record();
  updateRecordTime();
}

void Camera::pause() { mediaRecorder->pause(); }

void Camera::stop() { mediaRecorder->stop(); }

void Camera::setMuted(bool muted) { mediaRecorder->setMuted(muted); }

void Camera::toggleLock() {
  switch (camera->lockStatus()) {
  case QCamera::Searching:
  case QCamera::Locked:
    camera->unlock();
    break;
  case QCamera::Unlocked:
    camera->searchAndLock();
  }
}

void Camera::updateLockStatus(QCamera::LockStatus status,
                              QCamera::LockChangeReason reason) {
  /*QColor indicationColor = Qt::black;

  switch (status) {
  case QCamera::Searching:
          indicationColor = Qt::yellow;
          ui->statusbar->showMessage(tr("Focusing..."));
          ui->lockButton->setText(tr("Focusing..."));
          break;
  case QCamera::Locked:
          indicationColor = Qt::darkGreen;
          ui->lockButton->setText(tr("Unlock"));
          ui->statusbar->showMessage(tr("Focused"), 2000);
          break;
  case QCamera::Unlocked:
          indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
          ui->lockButton->setText(tr("Focus"));
          if (reason == QCamera::LockFailed)
                  ui->statusbar->showMessage(tr("Focus Failed"), 2000);
  }
*/
  /*QPalette palette = ui->lockButton->palette();
  palette.setColor(QPalette::ButtonText, indicationColor);
  ui->lockButton->setPalette(palette);*/
}

void Camera::takeImage() {
  isCapturingImage = true;
  imageCapture->capture();
}

void Camera::displayCaptureError(int id, const QCameraImageCapture::Error error,
                                 const QString &errorString) {
  Q_UNUSED(id);
  Q_UNUSED(error);
  QMessageBox::warning(this, tr("Image Capture Error"), errorString);
  isCapturingImage = false;
}

void Camera::startCamera() { camera->start(); }

void Camera::stopCamera() { camera->stop(); }

void Camera::updateCaptureMode() {
  /*int tabIndex = ui->captureWidget->currentIndex();
  QCamera::CaptureModes captureMode = tabIndex == 0 ? QCamera::CaptureStillImage
  : QCamera::CaptureVideo;

  if (camera->isCaptureModeSupported(captureMode))
          camera->setCaptureMode(captureMode);*/
}

void Camera::updateCameraState(QCamera::State state) {
  /*	switch (state) {
          case QCamera::ActiveState:
                  ui->actionStartCamera->setEnabled(false);
                  ui->actionStopCamera->setEnabled(true);
                  ui->captureWidget->setEnabled(true);
                  ui->actionSettings->setEnabled(true);
                  break;
          case QCamera::UnloadedState:
          case QCamera::LoadedState:
                  ui->actionStartCamera->setEnabled(true);
                  ui->actionStopCamera->setEnabled(false);
                  ui->captureWidget->setEnabled(false);
                  ui->actionSettings->setEnabled(false);
          }*/
}

void Camera::updateRecorderState(QMediaRecorder::State state) {
  /*	switch (state) {
          case QMediaRecorder::StoppedState:
                  ui->recordButton->setEnabled(true);
                  ui->pauseButton->setEnabled(true);
                  ui->stopButton->setEnabled(false);
                  break;
          case QMediaRecorder::PausedState:
                  ui->recordButton->setEnabled(true);
                  ui->pauseButton->setEnabled(false);
                  ui->stopButton->setEnabled(true);
                  break;
          case QMediaRecorder::RecordingState:
                  ui->recordButton->setEnabled(false);
                  ui->pauseButton->setEnabled(true);
                  ui->stopButton->setEnabled(true);
                  break;
          }*/
}

void Camera::setExposureCompensation(int index) {
  camera->exposure()->setExposureCompensation(index * 0.5);
}

void Camera::displayRecorderError() {
  QMessageBox::warning(this, tr("Capture Error"), mediaRecorder->errorString());
}

void Camera::displayCameraError() {
  QMessageBox::warning(this, tr("Camera Error"), camera->errorString());
}

void Camera::updateCameraDevice(QAction *action) {
  // setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void Camera::displayViewfinder() {
  // ui->stackedWidget->setCurrentIndex(0);
}

void Camera::displayCapturedImage() {
  // ui->stackedWidget->setCurrentIndex(1);
}

void Camera::readyForCapture(bool ready) {
  // ui->takeImageButton->setEnabled(ready);
}

void Camera::imageSaved(int id, const QString &fileName) {
  // Q_UNUSED(id);
  // ui->statusbar->showMessage(tr("Captured
  // \"%1\"").arg(QDir::toNativeSeparators(fileName)));

  // isCapturingImage = false;
  // if (applicationExiting)
  //	close();
}

void Camera::closeEvent(QCloseEvent *event) {
  if (isCapturingImage) {
    setEnabled(false);
    applicationExiting = true;
    event->ignore();
  } else {
    event->accept();
  }
}

Camera::~Camera() {}

} // namespace multimedia
