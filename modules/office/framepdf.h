#ifndef FRAMEPDF_H
#define FRAMEPDF_H

#include "framewidget.h"

#include <QObject>
#include <QWidget>

#include <base/logs.h>

#include "pdf/PDFiumReader.h"
#include "pdf/PDFiumReaderMgr.h"

namespace office
{

    class FramePDF : public FrameWidget
    {
        Q_OBJECT
    public:
        explicit FramePDF(QWidget *parent = nullptr);
        virtual ~FramePDF() override;

        virtual void play(const QFile &file) override;

    private:
        pdf::PDFIumReaderMgr *pdfMgr_;
        pdf::PDFIumReader *reader_;

        std::unique_ptr<QLabel> renderer_;

    signals:

    public slots:
    };

}
#endif // FRAMEPDF_H
