
#pragma once

#include "Page.h"
#include <QWidget>

namespace UI {
namespace page {
class EMail : public Page {
  Q_OBJECT
public:
  EMail(QWidget *parent = nullptr);
  ~EMail();
};

} // namespace page
} // namespace UI
