
#pragma once

#include "UI/core/ui.h"
#include <QFrame>

namespace UI {

namespace page {

class Page : public QFrame {
  Q_OBJECT
public:
  Page(QWidget *parent = nullptr);
  ~Page();
};

} // namespace page
} // namespace UI
