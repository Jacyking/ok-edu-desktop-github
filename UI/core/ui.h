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
#ifndef UI_H
#define UI_H

#include <string>

namespace UI
{

enum class PageMenu {
    welcome = 0,
#ifdef OK_MODULE_PAINTER
    classing,
#endif
    chat,
    record,
    calendar,
    email,
    personal,
    setting
};

enum class VIDEO_MODE {
    PLAYER,
    CAMERA
};

enum class VIDEO_SIZE {
    SMALL,
    MIDDLE,
    BIG,
};

enum class VIDEO_FOR {
    STUDENT,
    TEACHER,
};


typedef struct VideoWidgetConfT {
    VIDEO_MODE mode;
    VIDEO_SIZE size;
    VIDEO_FOR _for;

} VideoWidgetConfig;

}
#endif // UI_H
