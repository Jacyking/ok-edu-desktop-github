#ifndef WHITEBORAD_H
#define WHITEBORAD_H

#include <QObject>

namespace UI {

    class Whiteboard : public QObject
    {
        Q_OBJECT
    public:
        explicit Whiteboard(QObject *parent = nullptr);
        ~Whiteboard();

        void init();

        void loadWeb(QString url);

    private:

        QObject *parent;

        QObject *webEngine;


    signals:

    public slots:
    };

}

#endif // WHITEBORAD_H
