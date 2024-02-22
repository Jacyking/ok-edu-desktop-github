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
#include "OMainMenu.h"

#include "ui_OMainMenu.h"

#include <memory>
#include <QUrl>
#include <QMessageBox>


#include "WindowManager.h"

#include "base/files.h"
#include "lib/network/ImageLoader.h"

#include "lib/network/backend/PushService.h"


OMainMenu::OMainMenu(QWidget *parent)
    : QFrame(parent), ui(new Ui::OMainMenu), _menu(PageMenu::welcome),
      _showTimes(0) {
  ui->setupUi(this);
  delayCaller_ = (std::make_unique<base::DelayedCallTimer>());

  // 设置样式
  QString qss = base::Files::readStringAll(":/resources/style/qss/menu.qss");
  setStyleSheet(qss);
}

OMainMenu::~OMainMenu() { delete ui; }

void OMainMenu::setAvatar(const QPixmap &pixmap) {
  ui->label_avatar->setPixmap(pixmap);
}

void OMainMenu::showEvent(QShowEvent *e) {
  Q_UNUSED(e);
  _showTimes++;
  if (_showTimes == 1) {
    updateUI();
  }
}

void OMainMenu::updateUI() {

  //  if (_menu == PageMenu::welcome) {
  //    onClassing();
  //  }

  on_chatBtn_clicked(true);
}

void OMainMenu::onBook() {}

#ifdef OK_MODULE_PAINTER
void OMainMenu::onClassing() {

  ui->classBtn->setChecked(true);
  ui->chatBtn->setChecked(false);
  ui->settingBtn->setChecked(false);

  _menu = PageMenu::classing;
  emit onPage(PageMenu::classing);
}
void OMainMenu::on_classBtn_clicked(bool checked) { onClassing(); }

#endif

void OMainMenu::onRecord() {

  ui->classBtn->setChecked(false);
  ui->settingBtn->setChecked(false);
  ui->chatBtn->setChecked(false);

  _menu = PageMenu::record;
  emit onPage(PageMenu::record);
}

void OMainMenu::onCalendar() {

  ui->classBtn->setChecked(false);
  ui->settingBtn->setChecked(false);

  _menu = PageMenu::calendar;
  emit onPage(PageMenu::calendar);
}

void OMainMenu::onEmail() {}

void OMainMenu::on_personalBtn_clicked(bool checked) {}

void OMainMenu::on_chatBtn_clicked(bool checked) {
  ui->chatBtn->setChecked(true);
  ui->classBtn->setChecked(false);
  ui->settingBtn->setChecked(false);
  emit menuPushed(UI::PageMenu::chat, ui->chatBtn->isChecked());
  emit onPage(UI::PageMenu::chat);
}

void OMainMenu::onSetting() {

  ui->classBtn->setChecked(false);
  ui->settingBtn->setChecked(true);

  _menu = PageMenu::setting;
  emit onPage(PageMenu::setting);
}

/**
 * 设置按钮
 * @param checked
 */
void OMainMenu::on_settingBtn_clicked(bool checked) {
  ui->classBtn->setChecked(false);
  ui->chatBtn->setChecked(false);

  emit menuPushed(UI::PageMenu::setting, ui->settingBtn->isChecked());
  emit onPage(UI::PageMenu::setting);
}
