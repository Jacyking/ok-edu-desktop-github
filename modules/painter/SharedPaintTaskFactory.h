
#pragma once

#include <cassert>
#include <memory>

#include "SharedPaintTask.h"



namespace painter {

    class CSharedPaintTaskFactory {
    public:
        static std::shared_ptr<CSharedPaintTask> createTask(TaskType type) {
            std::shared_ptr<CSharedPaintTask> task;
            switch (type) {
                case Task_AddItem:
                    task = std::make_shared<CAddItemTask>();
                    break;
                case Task_RemoveItem:
                    task = std::make_shared<CRemoveItemTask>();
                    break;
                case Task_MoveItem:
                    task = std::make_shared<CMoveItemTask>();
                    break;
                case Task_UpdateItem:
                    task = std::make_shared<CUpdateItemTask>();
                    break;
                default:
                    assert(false && "not supported task type");
            }
            return task;
        }
    };

}
