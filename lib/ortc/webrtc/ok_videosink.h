/*
* Copyright (c) 2022 船山信息 chuanshaninfo.com
* OkEDU-Classroom is licensed under Mulan PubL v2.
* You can use this software according to the terms and conditions of the Mulan
* PubL v2. You may obtain a copy of Mulan PubL v2 at:
*          http://license.coscl.org.cn/MulanPubL-2.0
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
* KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the
* Mulan PubL v2 for more details.
*/

#pragma once


#include "../ok_rtc_renderer.h"
#include <mutex>
#include <api/video/video_sink_interface.h>
#include <api/video/video_frame.h>

namespace lib {
namespace ortc {

class OVideoSink : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
public:
  OVideoSink(OkRTCRenderer *renderer, std::string peerId = "");

  virtual ~OVideoSink() override;

  // VideoSinkInterface
  virtual void OnFrame(const webrtc::VideoFrame &frame) override;

private:
  uint64_t _renderCount;
  OkRTCRenderer *_renderer;
  std::string _track_id;
  std::string _peer_id;
};

} // namespace ortc
} // namespace lib
