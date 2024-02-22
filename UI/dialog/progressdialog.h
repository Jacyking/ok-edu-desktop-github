//#ifndef PROGRESSDIALOG_H
//#define PROGRESSDIALOG_H
//
//#include <QDialog>
//#include <QObject>
//#include <QVBoxLayout>
//
//namespace UI {
//namespace dialog {
//
//class ProgressHandler {
//
//public:
//  ProgressHandler(QWidget *dialog) : dialog_(dialog) {}
//
//protected:
//  // TaskManagerHandler
//  virtual void onTaskAdded(task::Task *task) override;
//
//  virtual void onTaskProcessing(task::Task *task, int processed,
//                                int total) override;
//
//  virtual void onTaskCompleted(task::Task *task) override;
//
//private:
//  QWidget *dialog_;
//};
//
//class ProgressDialog : public QWidget {
//  Q_OBJECT
//public:
//  explicit ProgressDialog(QWidget *parent = nullptr);
//
//private:
//  std::unique_ptr<QVBoxLayout> _vLayout;
//
//  task::TaskManager *taskManager_;
//
//  std::unique_ptr<ProgressHandler> progressHandler_;
//
//signals:
//
//public slots:
//};
//
//} // namespace dialog
//} // namespace UI
//
//#endif // PROGRESSDIALOG_H
