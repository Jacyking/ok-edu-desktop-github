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
#include "OWebView.h"
#include <memory>
#include <QUrlQuery>
#include <QDesktopServices>

#include <base/logs.h>
#include <lib/session/AuthSession.h>

#ifdef Q_WEBENGINE
#include <QWebChannel>
#include <QWebEngineView>
#include <QWebEngineSettings>
#endif

namespace UI
{
    namespace widget
    {

        JsContext::JsContext(QObject *parent) : QObject(parent)
        {
        }

        JsContext::~JsContext()
        {
        }

        void JsContext::onMsg(const QString &cmd, const QString &data)
        {
            emit recvdMsg(cmd, data);
        }

        void JsContext::sendMsg(void *page, const QString &msg)
        {
        }

        OWebView::OWebView(QWidget *parent) : QWidget(parent)
        {
            if (parent)
            {
                setGeometry(parent->contentsRect());
            }
        }

        OWebView::~OWebView()
        {
            // qDebug() << "OWebView::~OWebView=>" << this;
        }

        void OWebView::showEvent(QShowEvent *event)
        {
            Q_UNUSED(event);
#ifdef Q_WEBENGINE
            if (!_webEngineView)
            {
                initWebEngineView();
            }
#endif
        }

        void OWebView::resizeEvent(QResizeEvent *event)
        {
            Q_UNUSED(event);
#ifdef Q_WEBENGINE
            if (_webEngineView)
                _webEngineView->setGeometry(this->contentsRect());
#endif
        }

        void OWebView::initWebEngineView()
        {
            DEBUG_LOG_S(L_INFO) << "begin";

#ifdef Q_WEBENGINE
            QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

            m_jsContext = std::make_unique<JsContext>(this);

            m_webChannel = std::make_unique<QWebChannel>(this);
            m_webChannel->registerObject("context", m_jsContext.get());

            _webEngineView = std::make_unique<QWebEngineView>(this);
            _webEngineView->setContentsMargins(QMargins(0, 0, 0, 0));

            _webEngineView->page()->setWebChannel(m_webChannel.get());

            _webEngineView->show();

            QObject::connect(m_jsContext.get(), &JsContext::recvdMsg,
                             this, [](const QString &msg, const QString &data)
                             {
        if (msg.compare("openUrl") == 0) {
            QDesktopServices::openUrl(QUrl(data));
        } });

#endif
            DEBUG_LOG_S(L_INFO) << "end";
        }

        void OWebView::openWeb(QUrl &url)
        {
#ifdef Q_WEBENGINE
            if (url.isEmpty() || !url.isValid())
            {
                return;
            }

            if (!_webEngineView.get())
            {
                DEBUG_LOG_S(L_ERROR) << "_webEngineView is nullptr";
                return;
            }

            QUrlQuery uQuery(url.query());
            if (!uQuery.hasQueryItem("uin"))
                uQuery.addQueryItem("uin", session::AuthSession::Instance()->uin());

            url.setQuery(uQuery);

            _webEngineView->load(url);
#endif
        }

    }
}
