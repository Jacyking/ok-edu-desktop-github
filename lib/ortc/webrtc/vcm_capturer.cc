/*
 *  Copyright (c) 2013 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "vcm_capturer.h"

#include <iostream>
#include <stdint.h>
#include <memory>

#include "modules/video_capture/video_capture_factory.h"

namespace lib {
namespace ortc {

VcmCapturer::VcmCapturer(VideoCaptureModule::DeviceInfo* deviceInfo) :
    deviceInfo_(deviceInfo),
    vcm_(nullptr) {

}

bool VcmCapturer::Init(size_t width,
                       size_t height,
                       size_t target_fps,
                       size_t capture_device_index) {

  char device_name[256];
  char unique_name[256];
  int32_t r = deviceInfo_->GetDeviceName(static_cast<uint32_t>(capture_device_index),
                                 device_name,
                                 sizeof(device_name),
                                 unique_name,
                                 sizeof(unique_name));
  if(r){
//    qDebug() <<"Failed to GetDeviceName, result=>" << r;
    return false ;
  }
//  qDebug() << "Device device name is:"<< device_name << "unique name is:" << unique_name;
  vcm_ = webrtc::VideoCaptureFactory::Create(unique_name);
  if (!vcm_) {
//    qWarning() <<"Cannot create capturer for device:" << unique_name;
    return false;
  }

  vcm_->RegisterCaptureDataCallback(this);

  deviceInfo_->GetCapability(vcm_->CurrentDeviceName(), 0, capability_);

//  capability_.width = static_cast<int32_t>(width);
//  capability_.height = static_cast<int32_t>(height);
  capability_.maxFPS = static_cast<int32_t>(target_fps);
  capability_.videoType = VideoType::kI420;

  int sc = vcm_->StartCapture(capability_);
  if (sc != 0) {
    std::cerr << "Cannot start capture.";
    Destroy();
    return false;
  }

  if (vcm_->CaptureStarted()) {
    std::cerr << "Capture is not be started.";
    return false;
  }

  return true;
}

bool VcmCapturer::Create(size_t width,
                                 size_t height,
                                 size_t target_fps,
                                 size_t capture_device_index) {

    bool yes = Init(width, height, target_fps, capture_device_index);
    if(!yes)
      std::cerr << "Failed to create VcmCapturer(w = " << width
                        << ", h = " << height << ", fps = " << target_fps
                        << ")";
    return yes;
}

void VcmCapturer::Destroy() {
  if (!vcm_.get())
    return;

  vcm_->StopCapture();
  vcm_->DeRegisterCaptureDataCallback();
  // Release reference to VCM.
  vcm_ = nullptr;
}

VcmCapturer::~VcmCapturer() { Destroy(); }

void VcmCapturer::OnFrame(const VideoFrame &frame) {
  TestVideoCapturer::OnFrame(frame);
}

} // namespace ortc
} // namespace lib
