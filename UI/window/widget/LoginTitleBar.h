#ifndef LOGINTITLEBAR_H
#define LOGINTITLEBAR_H

#include <memory>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QHBoxLayout>
#include <QShowEvent>
#include <QPaintEvent>

#include "UI/widget/MoveableBar.h"

namespace UI
{

    namespace widget
    {

        using namespace UI::widget;

        class LoginTitleBar : public MoveableBar
        {
            Q_OBJECT

        public:
            LoginTitleBar(QWidget *parent = nullptr);
            ~LoginTitleBar();

        private:
            //    std::unique_ptr<QHBoxLayout> _hLayout;

            void paintEvent(QPaintEvent *event);
            void showEvent(QShowEvent *event);

        signals:

        private slots:

            void onButtoMinClicked();
            void onButtonCloseClicked();

        private:
            QPushButton *minimizeBtn;
            QPushButton *closeBtn;
            QWidget *box;
        };

    }
}

#endif // LOGINTITLEBAR_H
