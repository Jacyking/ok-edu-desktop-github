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
#include "SettingView.h"

#include <memory>
#include <QShowEvent>
#include <QWidget>
#include <QUrl>
#include <QPointF>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QApplication>

#include <base/widgets.h>
#include <base/basic_types.h>
#include <base/logs.h>

#include "base/r.h"

namespace UI
{
	namespace widget
	{

		SettingViewTesting::SettingViewTesting(QWidget *parent) : QWidget(parent)
		{
			if (parent)
			{
				setGeometry(parent->contentsRect());
			}
		}

		SettingViewTesting::~SettingViewTesting()
		{
		}

		struct Theme
		{
			QString color;
		} themes[] = {
			{"#535353"}, //
			{"#4274ff"}, //
			{"#9d0a16"}, //
			{"#307726"}, //
			{"#f6be4f"}, //
			{"#7519dd"}, //
			{"#307726"}, //
			{"#f6be4f"}, //
			{"#7519dd"}, //
		};

		SettingViewTheme::SettingViewTheme(QWidget *parent) : QWidget(parent)
		{
			if (parent)
			{
				setGeometry(parent->contentsRect());
			}

			base::Widgets::SetPalette(this, QPalette::Background, QColor("white"));

			_hLayout = std::make_unique<QGridLayout>(this);

			QSize blockSize(200, 140);

			QButtonGroup *buttonGroup = new QButtonGroup();
			buttonGroup->setExclusive(true);

			QString borderColor = "#ffd040";

			int count = ARRAY_LENGTH_OF(themes);
			for (int i = 0; i < count; i++)
			{

				QString color = themes[i].color;

				QPushButton *the = new QPushButton(this);
				the->setFixedSize(blockSize);
				the->setCheckable(true);
				the->setProperty("color", QVariant(color));
				the->setStyleSheet(qsl("background-color:%1").arg(color));

				base::Widgets::SetShadowEffect(the, QPointF(0, 0), Qt::gray, 20);

				buttonGroup->addButton(the, 2);

				int r = i / 3 + 1;
				int c = i % 3 + 1;

				_hLayout->addWidget(the, r, c);
			}

			connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonJudge(int)));

			setStyleSheet(qsl("QPushButton:checked {border: 2px solid %1; background: url(://resources/icon/setting_checked.png) no-repeat top right }").arg(borderColor));
		}

		SettingViewTheme::~SettingViewTheme()
		{
		}

		void SettingViewTheme::buttonJudge(int id)
		{
			qDebug() << "id===" << id;
		}

		SettingViewVoice::SettingViewVoice(QWidget *parent) : QWidget(parent)
		{
			if (parent)
			{
				setGeometry(parent->contentsRect());
			}
		}

		SettingViewVoice::~SettingViewVoice()
		{
		}

		SettingViewHelp::SettingViewHelp(QWidget *parent) : OWebView(parent)
		{
			if (parent)
			{
				setGeometry(parent->contentsRect());
			}
		}

		SettingViewHelp::~SettingViewHelp()
		{
		}

		void SettingViewHelp::showEvent(QShowEvent *e)
		{
			QUrl u("http://classroom.chuanshaninfo.com/classroom/v1/help.do");
			openWeb(u);
		}

		SettingViewAbout::SettingViewAbout(QWidget *parent) : OWebView(parent)
		{
			if (parent)
			{
				setGeometry(parent->contentsRect());
			}
		}

		SettingViewAbout::~SettingViewAbout()
		{
		}

		void SettingViewAbout::showEvent(QShowEvent *e)
		{
			QUrl u("http://classroom.chuanshaninfo.com/classroom/v1/about.do");
			openWeb(u);
		}

		SettingView::SettingView(QWidget *parent)
			: QWidget(parent)
		{
			if (parent)
			{
				setFixedHeight(parent->height() - PAGE_HEADER_HEIGHT);
			}

			setFixedWidth(SETTING_VIEW_WIDTH);

			_stackedLayout = std::make_unique<QStackedLayout>(this);
		}

		SettingView::~SettingView()
		{
		}

		QWidget *SettingView::getView(SettingViewMenu menu)
		{

			QWidget *page = nullptr;

			if (!_stackedLayout.get())
			{
				return page;
			}

			int idx = static_cast<int>(menu);
			DEBUG_LOG(qsl("switchPage: %1").arg(idx));

			QStackedLayout *stack = _stackedLayout.get();

			int sc = stack->count();
			for (int i = 0; i < sc; i++)
			{
				QWidget *p = stack->widget(i);

				if (QString::compare(p->objectName(), QString("View:%1").arg(idx)) == 0)
				{
					page = p;
					break;
				}
			}

			return page;
		}

		QWidget *SettingView::initView(SettingViewMenu menu)
		{

			QWidget *w = nullptr;
			switch (menu)
			{
			case UI::widget::SettingViewMenu::NONE:

				break;
			case UI::widget::SettingViewMenu::TESTING:
			{
				SettingViewTesting *p = new SettingViewTesting(this);
				w = qobject_cast<QWidget *>(p);
				break;
			}
			case UI::widget::SettingViewMenu::HELP:
			{
				SettingViewHelp *p = new SettingViewHelp(this);
				w = qobject_cast<QWidget *>(p);
				break;
			}
			case UI::widget::SettingViewMenu::OLC:
			{

				SettingViewAbout *p = new SettingViewAbout(this);
				w = qobject_cast<QWidget *>(p);

				break;
			}
			case UI::widget::SettingViewMenu::THEME:
			{

				SettingViewTheme *p = new SettingViewTheme(this);
				w = qobject_cast<QWidget *>(p);
				break;
			}
			case UI::widget::SettingViewMenu::VOICE:
			{

				SettingViewVoice *p = new SettingViewVoice(this);
				w = qobject_cast<QWidget *>(p);
				break;
			}
			case UI::widget::SettingViewMenu::EXIT:
				qApp->exit();
				break;
			default:
				break;
			}

			return w;
		}

		void SettingView::onSwitchView(UI::widget::SettingViewMenu menu)
		{
			QWidget *p = getView(menu);
			if (!p)
			{
				p = initView(menu);
				if (!p)
					return;

				_stackedLayout->addWidget(p);
			}
			_stackedLayout->setCurrentWidget(p);
		}
	}
}
