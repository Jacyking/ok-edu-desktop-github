//#include "progressdialog.h"
//
//#include <QProgressBar>
//#include <base/logs.h>
//
//namespace UI {
//namespace dialog {
//
//ProgressDialog::ProgressDialog(QWidget *parent) : QWidget(parent) {
//  _vLayout = std::make_unique<QVBoxLayout>();
//  _vLayout->setSpacing(0);
//  _vLayout->setContentsMargins(QMargins(0, 0, 0, 0));
//  setLayout(_vLayout.get());
//
//  setMinimumWidth(200);
//  setMinimumHeight(60);
//
//  taskManager_ = task::TaskManager::Get();
//
//  progressHandler_ = std::make_unique<ProgressHandler>(this);
//
//  taskManager_->registerHandler(progressHandler_.get());
//}
//
//void ProgressHandler::onTaskAdded(task::Task *task) {
//  if (!task)
//    return;
//
//  DEBUG_LOG_S(L_INFO) << " task:" << task->name();
//  if (!dialog_)
//    return;
//
//  QProgressBar *pProgressBar = new QProgressBar(dialog_);
//  pProgressBar->setOrientation(Qt::Horizontal);
//  pProgressBar->setValue(0);
//  pProgressBar->setMinimum(0);
//  pProgressBar->setMaximum(0);
//  pProgressBar->setObjectName(task->name());
//
//  dialog_->layout()->addWidget(pProgressBar);
//}
//
//void ProgressHandler::onTaskProcessing(task::Task *task, int processed,
//                                       int total) {
//  if (!task)
//    return;
//
//  DEBUG_LOG_S(L_INFO) << " task:" << task->name() << " processed:" << processed
//                      << " total: " << total;
//
//  if (!dialog_)
//    return;
//
//  for (int cc = 0; cc < dialog_->layout()->count(); cc++) {
//    QLayoutItem *it = dialog_->layout()->itemAt(cc);
//    QProgressBar *bar = qobject_cast<QProgressBar *>(it->widget());
//    if (bar && bar->objectName().compare(task->name()) == 0) {
//      bar->setValue(processed);
//      bar->setMaximum(total);
//    }
//  }
//}
//
//void ProgressHandler::onTaskCompleted(task::Task *task) {
//  if (!task)
//    return;
//
//  DEBUG_LOG_S(L_INFO) << " task:" << task->name();
//  if (!dialog_)
//    return;
//
//  for (int cc = 0; cc < dialog_->layout()->count(); cc++) {
//    QLayoutItem *it = dialog_->layout()->itemAt(cc);
//    QProgressBar *bar = qobject_cast<QProgressBar *>(it->widget());
//    if (bar && bar->objectName().compare(task->name()) == 0) {
//      dialog_->layout()->removeItem(it);
//    }
//  }
//}
//
//} // namespace dialog
//} // namespace UI
