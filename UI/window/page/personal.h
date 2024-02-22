#pragma once

#include "Page.h"
#include <QWidget>

namespace UI {
namespace page {
class Personal : public Page {
  Q_OBJECT
public:
  Personal(QWidget *parent = nullptr);
  ~Personal();
};

} // namespace page
} // namespace UI
