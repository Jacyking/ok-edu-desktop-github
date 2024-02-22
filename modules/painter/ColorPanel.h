#pragma once

#include <memory>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#define TOOLBOX_PANEL_WIDTH 100
#define TOOLBOX_PANEL_HEIGHT 100

namespace painter
{
    class ToolboxPanelColor : public QWidget
    {
        private:
        public:
            ToolboxPanelColor(QWidget *parent);
    };

    class ToolboxPanelSize : public QLabel
    {
    private:
    public:
        ToolboxPanelSize(QWidget *parent);
       virtual void mousePressEvent(QMouseEvent *event);
    };

    class ToolboxPanelPoint : public QFrame
    {
    private:
    public:
        ToolboxPanelPoint(QWidget *parent);
        virtual void mousePressEvent(QMouseEvent *event);
    };

    class ColorPanel : public QFrame
    {
    private:
        std::make_shared<QHBoxLayout> _widthLayout;

    public:
        ColorPanel(QWidget *parent);
        ColorPanel(QWidget *parent, int defaultSize, QString defaultColor);
    
        virtual void checkColor(ToolboxPanelColor *color);

        virtual void hide(bool force);
        virtual bool eventFilter(QObject *target, QEvent *event);
    }
}