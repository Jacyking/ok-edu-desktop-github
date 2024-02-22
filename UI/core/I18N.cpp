/*
 * Copyright (C) 2014 AnthonOS Open Source Community
 *               2014 - 2016 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 */
#include "I18N.h"

#include <QCoreApplication>
#include <QLibraryInfo>
#include <QTextCodec>
#include <QLocale>
#include <QDebug>

#include <base/logs.h>

namespace core
{

    const QString APPLICATION_ENCODING = "UTF-8";
    const QString TRANSLATIONS_PATH = "translations";

    I18N::I18N(const QString &path, const QString &encoding)
    {
        m_path = path;
        m_encoding = encoding;
    }

    void I18N::Init()
    {

        I18N *i18n = new I18N(TRANSLATIONS_PATH, APPLICATION_ENCODING);
        i18n->translate();

        self = i18n;
    }

    QString I18N::getEncoding() const { return m_encoding; }

    void I18N::setEncoding(const QString &encoding) { m_encoding = encoding; }

    QString I18N::getPath() const { return m_path; }

    void I18N::setPath(const QString &path) { m_path = path; }

    void I18N::translate()
    {
        QLocale::setDefault(QLocale::Chinese);

        QTranslator m_apTranslator, m_qtTranslator;
        m_qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        qApp->installTranslator(&m_qtTranslator);

        QString classroomQM(":/" + m_path + "/classroom_zh.qm");

        DEBUG_LOG(("load QM file:%1").arg(classroomQM));

        m_apTranslator.load(classroomQM);
        qApp->installTranslator(&m_apTranslator);
    }

}
