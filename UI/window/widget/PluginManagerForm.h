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

#ifndef PLUGINFORM_H
#define PLUGINFORM_H

#include "base/timer.h"
#include "lib/plugin/PluginInfo.h"
#include <QMap>
#include <QWidget>

namespace Ui {
class PluginManagerForm;
class PluginInfoForm;
} // namespace Ui

class QListWidgetItem;

namespace ok {
namespace plugin {

class PluginInfoForm;

class PluginManagerForm : public QWidget {
  Q_OBJECT

public:
  explicit PluginManagerForm(QWidget *parent = nullptr);
  ~PluginManagerForm() override;

  void add(PluginInfo &info, int i);

private:
  Ui::PluginManagerForm *ui;
  QList<PluginInfo> mPluginInfos;
  std::unique_ptr<::base::DelayedCallTimer> delayCaller_;
  void createPlugin(PluginInfo &, int i);
  void setPluginInfo(PluginInfo &);

protected slots:
  void pluginClicked(QListWidgetItem *);
};
} // namespace plugin
} // namespace ok
#endif // PLUGINFORM_H
