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
#ifndef OMAINMENU_H
#define OMAINMENU_H

#include <QFrame>
#include <memory>

#include "base/timer.h"
#include "UI/core/ui.h"

namespace Ui {
class OMainMenu;
}

using namespace UI;

class OMainMenu : public QFrame {
  Q_OBJECT

public:
  explicit OMainMenu(QWidget *parent = nullptr);
  ~OMainMenu() override;
  void setAvatar(const QPixmap &);

protected:
  virtual void showEvent(QShowEvent *e) override;

private:
  Ui::OMainMenu *ui;

  PageMenu _menu;
  void *_imView = nullptr;
  bool _imViewShow;
  int _showTimes;
  // delayCaller
  std::shared_ptr<base::DelayedCallTimer> delayCaller_;

  void updateUI();

signals:
  void onPage(PageMenu menu);

  void toggleChat(bool);
  void toggleBook(bool);

  void menuReleased(PageMenu menu, bool checked);
  void menuPushed(PageMenu menu, bool checked);

public slots:
#ifdef OK_MODULE_PAINTER
  void onClassing();
#endif

  //    void onChat();
  void onBook();
  void onRecord();
  void onCalendar();
  void onEmail();
  void onSetting();

private slots:
  void on_personalBtn_clicked(bool checked);
  void on_chatBtn_clicked(bool checked);
  void on_settingBtn_clicked(bool checked);

#ifdef OK_MODULE_PAINTER
  void on_classBtn_clicked(bool checked);
#endif
};

#endif // OMAINMENU_H
