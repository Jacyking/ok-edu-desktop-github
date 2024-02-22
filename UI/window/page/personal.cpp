
#include "personal.h"

#include <QWidget>
#include <base/basic_types.h>

#include "UI/core/ui.h"
#include "UI/window/page/Page.h"

#include "base/r.h"

namespace UI {
namespace page {

Personal::Personal(QWidget *parent) : Page(parent) {

  setAutoFillBackground(true);
  QPalette palette(this->palette());
  palette.setColor(QPalette::Background, QColor("#ffdd00"));
  setPalette(palette);

  setObjectName(qsl("Page:%1").arg(static_cast<int>(PageMenu::personal)));
}

Personal::~Personal() {}
} // namespace page

} // namespace UI
