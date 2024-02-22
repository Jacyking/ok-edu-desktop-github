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
// Created by gaojie on 23-8-27.
//

#pragma once

#include <QObject>

namespace ok {
namespace plugin {

typedef struct  {
  QString id;       //插件id
  QString shortName;//标识符
  QString name;     //版本名称
  QString fileName; //文件名称
  QString content;  //版本说明
  quint32 ver;    //数字版本
  QString version; //可读版本
  QString author; //
    QString homeUrl; //主页地址
    QString logoUrl;  //logo
    QString downUrl; //下载地址
} PluginInfo;

} // namespace plugin
} // namespace ok
