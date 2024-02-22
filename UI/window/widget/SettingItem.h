#pragma once

#include <QFrame>
#include <QPushButton>

namespace UI {
	namespace widget {
		class SettingItem : public QPushButton
		{
			Q_OBJECT

		public:
			SettingItem(QWidget *parent);
			~SettingItem();

			virtual	void setText(const QString &);

		};
	}
}