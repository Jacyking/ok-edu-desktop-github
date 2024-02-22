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

#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>
#include <vector>

#include "UI/window/page/Page.h"
#include "UI/window/widget/SettingView.h"

namespace UI {
namespace page {

using namespace widget;

struct SettingMenu {
  QString name;
  QString text;
  SettingViewMenu menu;
};

class SettingsPage : public Page {
  Q_OBJECT
public:
  SettingsPage(QWidget *parent = nullptr);
  ~SettingsPage();

  virtual void showEvent(QShowEvent *);

protected:
  void retranslateUi();

private:
  std::vector<SettingMenu> menus;

  bool inited = false;

  std::unique_ptr<QVBoxLayout> bodyLayout;
  std::unique_ptr<QTabWidget> settingsWidgets;

  //  std::unique_ptr<QHBoxLayout> _hLayout;
  //  QGridLayout *_gLayout;
  //  std::unique_ptr<SettingView> _stack_view;

signals:
  //  void view(widget::SettingViewMenu menu);

public slots:
  //  void onMenu(int id);
};

} // namespace page
} // namespace UI
