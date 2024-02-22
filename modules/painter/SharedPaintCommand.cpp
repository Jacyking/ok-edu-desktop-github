
#include "SharedPaintCommand.h"

#include "PainterView.h"
#include "SharedPaintManager.h"

namespace painter {

bool CAddItemCommand::execute(void) {
  std::shared_ptr<CAddItemTask> task(
      new CAddItemTask(item_->owner(), item_->itemId()));
  return cmdMngr_->executeTask(task);
}

bool CAddItemCommand::undo(void) {
  std::shared_ptr<CRemoveItemTask> task(
      new CRemoveItemTask(item_->owner(), item_->itemId()));
  return cmdMngr_->executeTask(task);
}

bool CRemoveItemCommand::execute(void) {
  std::shared_ptr<CRemoveItemTask> task(
      new CRemoveItemTask(item_->owner(), item_->itemId()));
  return cmdMngr_->executeTask(task);
}

bool CRemoveItemCommand::undo(void) {
  std::shared_ptr<CAddItemTask> task(
      new CAddItemTask(item_->owner(), item_->itemId()));
  return cmdMngr_->executeTask(task);
}

bool CUpdateItemCommand::execute(void) {
  std::shared_ptr<CUpdateItemTask> task(
      new CUpdateItemTask(item_->owner(), item_->itemId(), prevData_, data_));
  return cmdMngr_->executeTask(task);
}

bool CUpdateItemCommand::undo(void) {
  std::shared_ptr<CUpdateItemTask> task(
      new CUpdateItemTask(item_->owner(), item_->itemId(), prevData_, data_));
  return cmdMngr_->executeTask(task);
}

bool CMoveItemCommand::execute(void) {
  std::shared_ptr<CMoveItemTask> task(new CMoveItemTask(
      item_->owner(), item_->itemId(), prevX_, prevY_, posX_, posY_));
  return cmdMngr_->executeTask(task);
}

bool CMoveItemCommand::undo(void) {
  std::shared_ptr<CMoveItemTask> task(new CMoveItemTask(
      item_->owner(), item_->itemId(), prevX_, prevY_, posX_, posY_));
  return cmdMngr_->executeTask(task);
}
} // namespace painter
