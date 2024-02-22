#include "painterdispatcher.h"

#include "PaintItem.h"

#include <QColor>
#include <QString>
#include <memory>

#include <base/colorhelper.h>
#include <base/logs.h>
#include "lib/smartboard/imsmartboard.h"

#include "lib/messenger/messenger.h"
#include "lib/smartboard/smartboarddraw.h"
#include "lib/smartboard/smartboarddrawline.h"
#include "lib/smartboard/smartboarddrawmove.h"
#include "lib/smartboard/smartboarddrawremove.h"
#include "lib/smartboard/smartboarddrawtext.h"

namespace painter {

#undef DrawText // XXX resolve conflict DrawText in WinUser.h

using ColorHelper = base::ColorHelper;

PainterDispatcher::PainterDispatcher() : _imSmartBoard(nullptr) {
//TODO
  //  auto im = lib::IM::Messenger::getInstance()->im();
//  _imSmartBoard = im->getSmartBoard();
}

void PainterDispatcher::onISharedPaintEvent_AddTask(int totalTaskCount,
                                                    bool playBackWorking) {}

void PainterDispatcher::onISharedPaintEvent_AddPaintItem(
    std::shared_ptr<CPaintItem> item) {
  DEBUG_LOG(("item type:%1 posX:%2 posY:%3")
                .arg(item->type())
                .arg(item->posX())
                .arg(item->posY()));

  if (!_imSmartBoard) {
    DEBUG_LOG_S(L_WARN) << "_imSmartBoard is nullptr!";
    return;
  }

  std::shared_ptr<SmartBoard::SmartBoardDraw> draw = item->serialize();

  DEBUG_LOG_S(L_INFO) << "draw:" << draw.get();
//TODO 发送画图
//  _imSmartBoard->sendDraw(draw);
}

void PainterDispatcher::onISharedPaintEvent_RemovePaintItem(
    std::shared_ptr<CPaintItem> item) {
  DEBUG_LOG(
      ("item type:%1 id:%2").arg(item->type()).arg(qstring(item->itemId())));

  if (!_imSmartBoard) {
    DEBUG_LOG_S(L_WARN) << "_imSmartBoard is nullptr!";
    return;
  }

  std::shared_ptr<SmartBoard::SmartBoardDraw> draw =
      std::make_shared<SmartBoard::SmartBoardDraw>();

  auto move = new SmartBoard::DrawRemove();
  move->setRemoveId(item->itemId());
  draw->addPlugin(move);

//  _imSmartBoard->sendDraw(draw);
}

void PainterDispatcher::onISharedPaintEvent_MovePaintItem(
    std::shared_ptr<CPaintItem> item, double x, double y) {
  DEBUG_LOG(("item type:%1 prevPos:{%2, %3} => pos:{%4, %5}")
                .arg(item->type())
                .arg(item->posX())
                .arg(item->posY())
                .arg(x)
                .arg(y));

  if (!_imSmartBoard) {
    DEBUG_LOG_S(L_WARN) << "_imSmartBoard is nullptr!";
    return;
  }

  std::shared_ptr<SmartBoard::SmartBoardDraw> draw =
      std::make_shared<SmartBoard::SmartBoardDraw>();

  auto move = new SmartBoard::DrawMove();
  move->setMoveId(item->itemId());
  move->setPosition({(int)x, (int)y, 0});
  draw->addPlugin(move);

//  _imSmartBoard->sendDraw(draw);
}

void PainterDispatcher::onISharedPaintEvent_UpdatePaintItem(
    std::shared_ptr<CPaintItem> item) {
  DEBUG_LOG(("item type:%1 posX:%2 posY:%3")
                .arg(item->type())
                .arg(item->posX())
                .arg(item->posY()));

  if (!_imSmartBoard) {
    DEBUG_LOG_S(L_WARN) << "_imSmartBoard is nullptr!";
    return;
  }

  item->setAction(CPaintItem::Action::Update);
  std::shared_ptr<SmartBoard::SmartBoardDraw> draw = item->serialize();
  if (!draw) {
    DEBUG_LOG_S(L_WARN) << "draw is nullptr!";
    return;
  }

//  _imSmartBoard->sendDraw(draw);
}

} // namespace painter
