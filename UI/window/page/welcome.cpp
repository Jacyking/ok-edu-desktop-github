
#include "welcome.h"

#include "UI/core/ui.h"
#include "UI/window/page/Page.h"

#include "base/r.h"

namespace UI {
namespace page {

Welcome::Welcome(QWidget *parent) : Page(parent) {

  setAutoFillBackground(true);
  QPalette palette(this->palette());
  palette.setColor(QPalette::Background, QColor(DEFAULT_BG_COLOR));
  setPalette(palette);
  setObjectName("Page:" + static_cast<int>(PageMenu::welcome));
}

Welcome::~Welcome() {}
} // namespace page

} // namespace UI
