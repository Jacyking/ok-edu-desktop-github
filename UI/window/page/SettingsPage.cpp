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
#include "SettingsPage.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>
#include <memory>

#include <base/basic_types.h>
#include <base/widgets.h>

#include "base/r.h"
#include "UI/resources.h"

#include "UI/core/ui.h"
#include "UI/window/page/Page.h"

#include "lib/settings/translator.h"
#include "UI/window/widget/SettingItem.h"
#include "UI/window/widget/SettingView.h"
#if OK_PLUGIN
#include "widget/PluginManagerForm.h"
#endif
namespace UI {
namespace page {

using namespace widget;

SettingsPage::SettingsPage(QWidget *parent) : Page(parent) {
  menus = {
      {("setting_olc"), tr("setting_olc"), SettingViewMenu::OLC},             //
      {("setting_testing"), tr("setting_testing"), SettingViewMenu::TESTING}, //
      {("setting_voice"), tr("setting_voice"), SettingViewMenu::VOICE},       //
      {("setting_theme"), tr("setting_theme"), SettingViewMenu::THEME},       //
      {("setting_help"), tr("setting_help"), SettingViewMenu::HELP},          //
      {("setting_exit"), tr("setting_exit"), SettingViewMenu::EXIT},          //
  };

  if (parent) {
    setGeometry(parent->contentsRect());
  }

  setObjectName(qsl("Page:").arg(static_cast<int>(PageMenu::setting)));

  base::Widgets::SetPalette(this, QPalette::Background, QColor(DEFAULT_BG_COLOR));

  bodyLayout = std::make_unique<QVBoxLayout>(this);
  settingsWidgets = std::make_unique<QTabWidget>(this);
  settingsWidgets->setTabPosition(QTabWidget::North);

#if OK_PLUGIN
  settingsWidgets->addTab(new ok::plugin::PluginManagerForm(this), "PluginForm");
#endif

  bodyLayout->addWidget(settingsWidgets.get());
//  bodyLayout->addWidget(new PluginForm);
//  settingsWidgets->addTab(new PluginForm(this), "PluginForm2");

//  QLabel *header = new QLabel(this);
//  header->setFixedWidth(this->width());
//  header->setFixedHeight(PAGE_HEADER_HEIGHT);
//  header->setText(tr("Settings"));
//  header->setAlignment(Qt::AlignCenter);
//  header->setStyleSheet(
//      "background-color: #535353; color:white; font-weight: bold;");
//
//  bodyLayout->addWidget(header);
//
//  _hLayout = std::make_unique<QHBoxLayout>(this);
//  _hLayout->setDirection(QBoxLayout::LeftToRight);
//  _hLayout->setMargin(0);
//  _hLayout->setSpacing(0);
//
//  bodyLayout->addLayout(_hLayout.get());
//
//  _gLayout = new QGridLayout(this);
//  _gLayout->setMargin(0);
//  _gLayout->setSpacing(0);
//
//  QButtonGroup *buttonGroup = new QButtonGroup();
//  buttonGroup->setExclusive(true);
//
//  int count = menus.size();
//  for (int i = 0; i < count; i++) {
//
//    int r = i / 2 + 1;
//    int c = i % 2 + 1;
//
//    SettingItem *_settingBtn = new SettingItem(this);
//    _settingBtn->setObjectName(menus[i].name);
//    _settingBtn->setText(menus[i].text);
//
//    buttonGroup->addButton(_settingBtn, i);
//
//    _gLayout->addWidget(_settingBtn, r, c);
//  }
//
//  // 左侧网格
//  _hLayout->addLayout(_gLayout);
//
//  _hLayout->addSpacerItem(new QSpacerItem(10, 10));
//
//  // 右侧试图
//  _stack_view = std::make_unique<SettingView>(this);
//  _hLayout->addWidget(_stack_view.get(), Qt::AlignLeft);
//  _hLayout->addStretch();
//
//  bodyLayout->addStretch();
//
//  // 连接信号
//  connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onMenu(int)));
//  connect(this, SIGNAL(view(UI::widget::SettingViewMenu)), _stack_view.get(),
//          SLOT(onSwitchView(UI::widget::SettingViewMenu)));
//
//  // 设置样式
//  QString qss = utils::Resources::loadQss(utils::QSS::setting);
//  setStyleSheet(qss);
//
//  settings::Translator::registerHandler(std::bind(&Setting::retranslateUi, this), this);
//  retranslateUi();
}

SettingsPage::~SettingsPage() {}

void SettingsPage::showEvent(QShowEvent *) {
  if (inited)
    return;
}

//void Setting::onMenu(int id) { // 信号槽
//  SettingMenu menu = menus[id];
//  _stack_view->onSwitchView(menu.menu);
//}

void SettingsPage::retranslateUi() {

}

} // namespace page
} // namespace UI
