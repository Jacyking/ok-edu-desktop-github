/*
 * Copyright (c) 2022 船山信息 chuanshaninfo.com
 * OkEDU is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PubL v2. You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

//
// Created by gaojie on 23-10-7.
//
#pragma once

#include "modules/module.h"

class Painter : public Module {
public:
  ~Painter();

  static QString Name();
  static Module *Create();

  void init(Profile *p) override;
  QString name() override;
  void start(ok::session::SignInInfo &signInInfo,
                     QWidget *parent = nullptr) override;
  [[nodiscard]] bool isStarted() override;
  void hide() override;
  
  void onSave(SavedInfo &) override;
  void cleanup() override;
private:
  Painter();
};
