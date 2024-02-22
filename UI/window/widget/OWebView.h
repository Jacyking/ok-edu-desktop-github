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
#pragma once
#include <memory>
#include <QWidget>
#include <QShowEvent>
#include <QResizeEvent>
#include <QObject>


namespace UI {
	namespace widget {
		class JsContext : public QObject {
			Q_OBJECT
		public:
			explicit JsContext(QObject *parent = nullptr);
			~JsContext();

			void sendMsg(void* page, const QString& msg);

		signals:
			void recvdMsg(const QString&, const QString &);

		public slots:
			void onMsg(const QString&, const QString &);
		};

		class OWebView : public QWidget
		{
			Q_OBJECT

		public:
			OWebView(QWidget *parent = nullptr);
			~OWebView();

			void openWeb(QUrl& url);

		protected:

#ifdef Q_WEBENGINE
			std::unique_ptr<QWebEngineView> _webEngineView;
			std::unique_ptr<QWebChannel> m_webChannel;
#endif
			std::unique_ptr<JsContext> m_jsContext;

			virtual void showEvent(QShowEvent *event);
			virtual void resizeEvent(QResizeEvent *event);

		private :

			void initWebEngineView();

		};
	}
}