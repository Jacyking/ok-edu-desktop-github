/** Copyright (c) 2022 船山信息 chuanshaninfo.com
OkEDU-Classroom is licensed under Mulan PubL v2.
You can use this software according to the terms and conditions of the Mulan
PubL v2. You may obtain a copy of Mulan PubL v2 at:
         http://license.coscl.org.cn/MulanPubL-2.0
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PubL v2 for more details.
*/
#include "whiteboard.h"

#include <QVariant>
#include <QDebug>

namespace UI {
    static QString WHITEBOARD_WEB_ENGINE = ( "whiteboard_webEngine");

    Whiteboard::Whiteboard(QObject *parent) : QObject(parent)
    {
        qDebug() << "Whiteboard... " << parent;

        this->parent = parent;
        this->init();
    }

    Whiteboard::~Whiteboard(){

    }

    void Whiteboard::init(){
        qDebug() << "Whiteboard init... " << parent;
        this->webEngine = this->parent->findChild<QObject*>(WHITEBOARD_WEB_ENGINE);
    }

    void Whiteboard::loadWeb(QString url){
        QObject* web = this->webEngine;

        qDebug() << "WebEngine:" << web;

        if(web) {
            qDebug() << "loadWeb:" << url;
            web->setProperty("url", QVariant(url));
        }

    }
}

