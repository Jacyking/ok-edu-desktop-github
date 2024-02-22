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
#include <QStackedLayout>
#include <QShowEvent>
#include <QHBoxLayout>
#include <QGridLayout>

#include "UI/window/widget/OWebView.h"

namespace UI
{
	namespace widget
	{

		enum class SettingViewMenu
		{
			NONE = 0,
			TESTING,
			HELP,
			OLC,
			THEME,
			VOICE,
			EXIT,
		};

		// setting
		class SettingViewTesting : public QWidget
		{
			Q_OBJECT
		public:
			SettingViewTesting(QWidget *parent = nullptr);
			~SettingViewTesting();

		private:
		};

		// theme
		class SettingViewTheme : public QWidget
		{
			Q_OBJECT
		public:
			SettingViewTheme(QWidget *parent = nullptr);
			~SettingViewTheme();

		private:
			std::unique_ptr<QGridLayout> _hLayout;

		public slots:
			void buttonJudge(int id);
		};

		// voice
		class SettingViewVoice : public QWidget
		{
			Q_OBJECT
		public:
			SettingViewVoice(QWidget *parent = nullptr);
			~SettingViewVoice();

		private:
		};

		// help
		class SettingViewHelp : public OWebView
		{
			Q_OBJECT
		public:
			SettingViewHelp(QWidget *parent = nullptr);
			~SettingViewHelp();

		private:
			virtual void showEvent(QShowEvent *e);
		};

		// about
		class SettingViewAbout : public OWebView
		{
			Q_OBJECT
		public:
			SettingViewAbout(QWidget *parent = nullptr);
			~SettingViewAbout();

		private:
			virtual void showEvent(QShowEvent *e);
		};

		class SettingView : public QWidget
		{
			Q_OBJECT

		public:
			SettingView(QWidget *parent = nullptr);
			~SettingView();

			QWidget *initView(SettingViewMenu menu);
			QWidget *getView(SettingViewMenu menu);

		private:
			std::unique_ptr<QStackedLayout> _stackedLayout;

		public slots:
			void onSwitchView(widget::SettingViewMenu);
		};
	}
}
