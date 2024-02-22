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
#include "UI/resources.h"

#include <QFile>
#include <QString>

#include <base/basic_types.h>
#include <base/logs.h>

namespace utils {

// qss文件（resources.h一致）
struct QSS_FILE {
  QString name;
} files[] = {
    {":/resources/style/qss/application.qss"},
    {":/resources/style/qss/login.qss"},
    {":/resources/style/qss/menu.qss"},
    {":/resources/style/qss/toolbox.qss"},
    {":/resources/style/qss/IM.qss"},
    {":/resources/style/qss/topbar.qss"},
    {":/resources/style/qss/titlebar.qss"},
    {":/resources/style/qss/setting.qss"},
};

Resources::Resources() {}

Resources::~Resources() {}

QString Resources::loadQss(QSS qss) {
  int idx = static_cast<int>(qss);
  QSS_FILE qssFile = files[idx];

  QFile file(qssFile.name);
  if (!file.open(QFile::ReadOnly)) {
    qWarning()<<("open error:")<<qssFile.name;
    return "";
  }

  QString styleSheet = file.readAll();
  file.close();
  return styleSheet;
}

} // namespace utils
