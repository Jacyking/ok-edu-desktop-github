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

#include "PluginManagerForm.h"

#include <QDebug>
#include <QListWidgetItem>

#include "PluginInfoForm.h"
#include "PluginItemForm.h"
#include "base/system/sys_info.h"
#include "lib/plugin/PluginInfo.h"
#include "ui_PluginManagerForm.h"

namespace ok {
namespace plugin {

PluginManagerForm::PluginManagerForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::PluginManagerForm) {
  ui->setupUi(this);

  connect(ui->listWidget, &QListWidget::itemClicked, this,
          &PluginManagerForm::pluginClicked, Qt::UniqueConnection);

  delayCaller_ = std::make_unique<::base::DelayedCallTimer>();

  auto osInfo = ::base::SystemInfo::instance()->osInfo();
  auto cpuInfo = ::base::SystemInfo::instance()->cpuInfo();
  auto platform = osInfo.kernelName == "winnt" ? "windows" : osInfo.kernelName;
  // TODO(gaojie): 暂时固定
  int i = 1;
  PluginInfo info1 = {
      QString("id_%1").arg(i),
      "hello",
      QString("插件-%1").arg(i),
      "libPluginHello.so",
      "插件描述",
      static_cast<quint32>(i),
      QString("1.%1").arg(i),
      "OkStar",
      "http://okstar.org",
      "https://www.chuanshaninfo.com/download/logo/OkStar/01.jpg",
      "https://chuanshaninfo.com/download/plugins/" + cpuInfo.arch + "/" +
          platform + "/libPluginHello.so",
  };
  add(info1, i);

  i = 2;
  PluginInfo info2 = {
      QString("id_%1").arg(i),
      "omemo",
      QString("插件-%1").arg(i),
      "libomemoplugin.so",
      "插件描述",
      static_cast<quint32>(i),
      QString("1.%1").arg(i),
      "OkStar",
      "http://okstar.org",
      "https://www.chuanshaninfo.com/download/logo/OkStar/01.png",
      "https://chuanshaninfo.com/download/plugins/" + cpuInfo.arch + "/" +
          platform + "/libomemoplugin.so",
  };
  add(info2, i);
}

PluginManagerForm::~PluginManagerForm() { delete ui; }

void PluginManagerForm::pluginClicked(QListWidgetItem *item) {
  Q_UNUSED(item);
  auto wdg = static_cast<QListWidget *>(sender());
  auto mCurrentRow = wdg->currentRow();
  auto info = mPluginInfos.at(mCurrentRow);
  setPluginInfo(info);
}

void PluginManagerForm::add(PluginInfo &info, int i) {
  mPluginInfos.append(info);
  createPlugin(info, i);
}

void PluginManagerForm::createPlugin(PluginInfo &info, int i) {
  auto pitem = new PluginItemForm(0, info, this);
  auto aitem = new QListWidgetItem(ui->listWidget);
  aitem->setSizeHint(QSize(ui->listWidget->width(), 70));

  ui->listWidget->addItem(aitem);
  ui->listWidget->setItemWidget(aitem, pitem);

  delayCaller_->call(i + 1 * 100, [=]() { emit pitem->loadLogo(); });
}

void PluginManagerForm::setPluginInfo(PluginInfo &info) {

  for (auto i = 0; i < ui->stackedWidget->count(); i++) {
    auto entry = static_cast<PluginInfoForm *>(ui->stackedWidget->widget(i));
    if (entry->pluginId() == info.id) {
      ui->stackedWidget->setCurrentWidget(entry);
      return;
    }
  }

  auto selectedInfoForm = new PluginInfoForm(info);
  ui->stackedWidget->addWidget(selectedInfoForm);
  ui->stackedWidget->setCurrentWidget(selectedInfoForm);
}

} // namespace plugin
} // namespace ok