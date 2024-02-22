#include "SharedPaintTask.h"

#include <base/logs.h>

#include "SharedPaintCommand.h"
#include "SharedPaintManager.h"
#include "TaskPacketBuilder.h"

//#define DEBUG_PRINT_TASK()    qDebug() << __FUNCTION__ << "history item cnt : " << cmdMngr_->historyItemCount();

namespace painter
{

    static CDefferedCaller gCaller;

    void CSharedPaintTask::sendPacket(void)
    {
        DEBUG_LOG(("begin history item's count:%1").arg(cmdMngr_->historyItemCount()));
        //       //查找数据
        //       std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        //       if(!item){
        //           DEBUG_LOG(("findItem:%1 is be null!").arg(data_.itemId));
        //           return false;
        //       }
    }

    bool CAddItemTask::execute(void)
    {
        DEBUG_LOG(("begin history item's count:%1").arg(cmdMngr_->historyItemCount()));

        //查找数据
        std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        if (!item)
        {
            DEBUG_LOG(("findItem:%1 is be null!").arg(qstring(data_.itemId)));
            return false;
        }
        //序列化数据
        //        item->posX();
        //        item->posY();

        //发送数据
        //        sendPacket();

        if (item)
        {
            gCaller.performMainThread(std::bind(&CSharedPaintManager::fireObserver_AddPaintItem, spMngr_, item));
        }

        return true;
    }

    void CAddItemTask::rollback(void)
    {
        DEBUG_LOG(("count:%1").arg(cmdMngr_->historyItemCount()));

        std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        if (item)
        {
            gCaller.performMainThread(std::bind(&CSharedPaintManager::fireObserver_RemovePaintItem, spMngr_, item));
        }
    }

    bool CRemoveItemTask::execute(void)
    {
        DEBUG_LOG(("count:%1").arg(cmdMngr_->historyItemCount()));

        sendPacket();

        std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        if (item)
        {
            gCaller.performMainThread(std::bind(&CSharedPaintManager::fireObserver_RemovePaintItem, spMngr_, item));
        }

        return true;
    }

    void CRemoveItemTask::rollback(void)
    {
        DEBUG_LOG(("count:%1").arg(cmdMngr_->historyItemCount()));

        std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        if (item)
        {
            gCaller.performMainThread(std::bind(&CSharedPaintManager::fireObserver_AddPaintItem, spMngr_, item));
        }
    }

    bool CUpdateItemTask::execute(void)
    {
        DEBUG_LOG(("count:%1").arg(cmdMngr_->historyItemCount()));

        sendPacket();

        std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        if (item)
        {
            item->setData(paintData_);
            gCaller.performMainThread(std::bind(&CSharedPaintManager::fireObserver_UpdatePaintItem, spMngr_, item));
        }
        return true;
    }

    void CUpdateItemTask::rollback(void)
    {
        DEBUG_LOG(("count:%1").arg(cmdMngr_->historyItemCount()));

        std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        if (item)
        {
            item->setData(prevPaintData_);
            gCaller.performMainThread(std::bind(&CSharedPaintManager::fireObserver_UpdatePaintItem, spMngr_, item));
        }
    }

    bool CMoveItemTask::execute(void)
    {
        DEBUG_LOG(("count:%1").arg(cmdMngr_->historyItemCount()));

        sendPacket();

        std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        if (item)
        {
            gCaller.performMainThread(
                std::bind(&CSharedPaintManager::fireObserver_MovePaintItem, spMngr_, item, posX_, posY_));
        }
        return true;
    }

    void CMoveItemTask::rollback(void)
    {
        DEBUG_LOG(("count:%1").arg(cmdMngr_->historyItemCount()));

        std::shared_ptr<CPaintItem> item = cmdMngr_->findItem(data_.owner, data_.itemId);
        if (item)
        {
            gCaller.performMainThread(
                std::bind(&CSharedPaintManager::fireObserver_MovePaintItem, spMngr_, item, prevPosX_, prevPosY_));
        }
    }

}
