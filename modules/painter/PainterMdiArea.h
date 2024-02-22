#ifndef PAINTERMDIAREA_H
#define PAINTERMDIAREA_H

#include <QMdiArea>
#include <memory>

namespace painter {

class CSharedPainterScene;

class PainterMdiArea : public QMdiArea {
  Q_OBJECT

public:
  explicit PainterMdiArea(std::shared_ptr<CSharedPainterScene> scene,
                          QWidget *parent = Q_NULLPTR);

  virtual ~PainterMdiArea() override;

protected:
  virtual void mouseReleaseEvent(QMouseEvent *e) override;
  virtual void mouseMoveEvent(QMouseEvent *e) override;
  virtual void mousePressEvent(QMouseEvent *e) override;

  virtual void keyPressEvent(QKeyEvent *e) override;

  virtual void dragEnterEvent(QDragEnterEvent *e) override;
  virtual void dragLeaveEvent(QDragLeaveEvent *e) override;
  virtual void dragMoveEvent(QDragMoveEvent *e) override;
  virtual void dropEvent(QDropEvent *e) override;

  bool eventFilter(QObject *watcher, QEvent *event) override;

private:
  virtual void forwardEvent(QMouseEvent *e);
  virtual void forwardEvent(QKeyEvent *e);

  virtual void forwardEvent(QDragEnterEvent *e);
  virtual void forwardEvent(QDragLeaveEvent *e);
  virtual void forwardEvent(QDragMoveEvent *e);
  virtual void forwardEvent(QDropEvent *e);

  std::shared_ptr<CSharedPainterScene> scene_;

public slots:
  void onDragLeaveEvent();
  void onDropEvent();
};
} // namespace painter

#endif // PAINTERMDIAREA_H
