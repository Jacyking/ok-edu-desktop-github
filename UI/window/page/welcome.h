//
// Created by workg on 7/27/2018.
//

#pragma once

#include <QWidget>

#include "UI/window/page/Page.h"
#include "UI/window/page/welcome.h"

namespace UI {
namespace page {
class Welcome : public Page {
  Q_OBJECT
public:
  Welcome(QWidget *parent = nullptr);
  ~Welcome();
};

} // namespace page
} // namespace UI
