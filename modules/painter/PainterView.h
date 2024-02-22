#pragma once

#include <QClipboard>
#include <QString>
#include <QWidget>
#include <memory>

#include "Base.h"
#include "PaintItem.h"
#include "PainterMdiArea.h"
#include "PainterView.h"
#include "SharedPaintManager.h"
#include "SharedPainterScene.h"
#include "painterdispatcher.h"
#include "painterevent.h"
#include "painterrenderer.h"

#include "lib/network/NetworkManager.h"
#include "lib/network/backend/HttpService.h"
#include <base/timer.h>

class OPainterToolBox;

namespace painter {

class WhiteboardController;

class PainterView : public QWidget {
public:
  PainterView(QWidget *parent = nullptr);
  virtual ~PainterView() override;

  static PainterView *Get(QWidget *parent = nullptr);

  virtual const CSharedPaintManager *manager() const {
    return painterManager_.get();
  }

  virtual const WhiteboardController *controller() const {
    return _oController.get();
  }

protected:
  void showEvent(QShowEvent *event) override;

  void resizeEvent(QResizeEvent *e) override;

private:
  network::NetworkManager *networkManager_;

  // 画板管理器
  std::unique_ptr<CSharedPaintManager> painterManager_;

  // 工具箱
  std::unique_ptr<OPainterToolBox> _oToolbox;

  // 控制面板
  std::unique_ptr<WhiteboardController> _oController;

  std::unique_ptr<base::DelayedCallTimer> _delayCaller;

  PainterMdiArea *mdiArea;

signals:

public slots:
  void onReceivedUrlInfo(ok::backend::FileResult);
  void onReceivedDraw(SmartBoard::SmartBoardDraw *);
  void onOpenFile(std::shared_ptr<CFileItem>);

  void onToolBoxChanged(ToolboxType toolboxType);

  void setTextColor(QColor clr);
  void setTextWeight(int weight);

  void setPenColor(QColor clr);
  void setPenWeight(int weight);

  void onCtrollerChecked(context::WB::WB_CTRL, bool);

  //  void onPubSubEvent(gloox::PubSub::ItemList &);
};

} // namespace painter
