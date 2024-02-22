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
#include "WindowManager.h"

#include <memory>

#include <QApplication>
#include <QObject>
#include <QString>

#include "base/logs.h"
#include "modules/painter/PageClassing.h"
#include "UI/resources.h"
#include "UI/window/page/Page.h"
#include <window/window/MainWindow.h>

namespace UI {

using namespace page;

WindowManager::WindowManager(QObject *parent) : QObject(parent) {
  QString qss = utils::Resources::loadQss(utils::QSS::application);
  qApp->setStyleSheet(qss);
}

WindowManager::~WindowManager() {
}

WindowManager *WindowManager::Instance() {
  static WindowManager *instance = nullptr;
  if (!instance) {
    instance = new WindowManager;
  }
  return instance;
}

QFrame *WindowManager::getPage(PageMenu menu) {
  return m_mainWindow->getPage(menu);
}

#ifdef OK_MODULE_PAINTER
page::PageClassing *WindowManager::getPageClassing() {
  return static_cast<page::PageClassing *>(getPage(PageMenu::classing));
}
#endif

void WindowManager::startMainUI() {
  m_mainWindow = std::make_unique<UI::window::MainWindow>();

  /**
   * connect menu's button events.
   */
  connect(m_mainWindow.get(), &UI::window::MainWindow::toClose, //
          [&](){
            emit mainClose({
              m_mainWindow->saveGeometry()
            });
          } );


  connect(m_mainWindow->menu(), &OMainMenu::menuPushed,
          [&](PageMenu menu, bool checked) { emit menuPushed(menu, checked); });
  m_mainWindow->show();
}

void WindowManager::stopMainUI() {
  m_mainWindow->close();
  m_mainWindow.reset();
}

QWidget *WindowManager::getContainer(PageMenu menu) { //
  return m_mainWindow->getContainer(menu);
}

OMainMenu *WindowManager::getMainMenu() { //
  return m_mainWindow->menu();
}

} // namespace UI
