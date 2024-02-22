#ifndef PAINTERDISPATCHER_H
#define PAINTERDISPATCHER_H

#include "isharedpaintevent.h"

#include "lib/network/NetworkManager.h"
#include "lib/smartboard/smartboarddraw.h"

namespace painter {

using namespace network;

namespace lib{
namespace smartboard{
class IMSmartBoard;
}
}

class PainterDispatcher : public ISharedPaintEvent {
public:
  PainterDispatcher();
  virtual ~PainterDispatcher() {}

  //    virtual void setManager(CSharedPaintManager* manager){
  //        _manager = manager;
  //    }

  //    virtual void draw(SmartBoard::SmartBoardDraw *draw);

protected:
  // ISharedPaintEvent
  virtual void onISharedPaintEvent_AddTask(int totalTaskCount,
                                           bool playBackWorking) override;
  virtual void
  onISharedPaintEvent_AddPaintItem(std::shared_ptr<CPaintItem> item) override;
  virtual void onISharedPaintEvent_RemovePaintItem(
      std::shared_ptr<CPaintItem> item) override;
  virtual void
  onISharedPaintEvent_MovePaintItem(std::shared_ptr<CPaintItem> item, double x,
                                    double y) override;
  virtual void onISharedPaintEvent_UpdatePaintItem(
      std::shared_ptr<CPaintItem> item) override;

private:
  lib::smartboard::IMSmartBoard *_imSmartBoard;
  //    CSharedPaintManager* _manager;
};

} // namespace painter
#endif // PAINTERDISPATCHER_H
