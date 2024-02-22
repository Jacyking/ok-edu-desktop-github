/*
 * Copyright (c) 2022 船山信息 chuanshaninfo.com
 * OkEDU is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PubL v2. You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the
 * Mulan PubL v2 for more details.
 */

//
// Created by gaojie on 23-10-7.
//

#include "Painter.h"

Painter::Painter() {
  Q_INIT_RESOURCE(painter);
}
Painter::~Painter() {
    Q_CLEANUP_RESOURCE(painter);
}

QString Painter::Name() { return OK_Painter_MODULE; }

QString Painter::name() { return Name(); }

void Painter::init(Profile *p) {}

void Painter::start(ok::session::SignInInfo &signInInfo, QWidget *parent) {}

bool Painter::isStarted() { return true; }

void Painter::hide() {}

Module *Painter::Create() { return new Painter; }
void Painter::onSave(SavedInfo &) {}
void Painter::cleanup() {}
