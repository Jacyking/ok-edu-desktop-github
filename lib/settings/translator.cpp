/*
    Copyright © 2014-2019 by The qTox Project Contributors

    This file is part of qTox, a Qt-based graphical interface for Tox.

    qTox is libre software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    qTox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with qTox.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "translator.h"
#include <QApplication>
#include <QDebug>
#include <QLibraryInfo>
#include <QLocale>
#include <QMutexLocker>
#include <QString>
#include <QTranslator>
#include <algorithm>

namespace settings {

// module, QTranslator
static QMap<QString, QTranslator *> m_translatorMap{};
static QVector<Callback> callbacks{};
//static QMutex Translator::lock;
static bool m_loadedQtTranslations{false};


/**
 * @brief Loads the translations according to the settings or locale.
 */
void Translator::translate(const QString &moduleName, const QString &localeName) {
  qDebug() << "translate module:" << moduleName << "locale:" << localeName;
//  QMutexLocker locker{&lock};

//  if (!translator)
//    translator = new QTranslator();

  qDebug() <<"m_translatorMap" << m_translatorMap.size();

  auto * translator = m_translatorMap.value(moduleName);
  if(translator){
      qDebug() << "remove translator:" << translator;
    QCoreApplication::removeTranslator(translator);
    m_translatorMap.remove(moduleName);
    delete translator;
  }

  qDebug() << "New translator=>" << moduleName;
  translator = new QTranslator();


  // Load translations
  QString locale = localeName.isEmpty()
                       ? QLocale::system().name().section('_', 0, 0)
                       : localeName;
  qDebug() << "Loaded  locale" << locale <<"=>" << moduleName ;
  if (locale != "en") {
    //增加 {translations}/{module}
    QString path = ":translations/"+moduleName;
    qDebug() << "Loading translation path" << path << "locale" << locale;
    if (translator->load(locale+".qm", path)) {
      qDebug() << "Loaded translation successful for locale" <<locale;

      if(!m_loadedQtTranslations){

        // system menu translation (Qt国际化配置)
        QTranslator *qtTranslator = new QTranslator();
        QString s_locale = "qt_" + locale;
        QString location = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
        if (qtTranslator->load(s_locale, location)) {
          QApplication::installTranslator(qtTranslator);
          qDebug() << "System translation loaded" << locale;
        } else {
          qDebug() << "System translation not loaded" << locale;
        }
        m_loadedQtTranslations = true;
      }

      m_translatorMap.insert(moduleName, translator);
      QCoreApplication::installTranslator(translator);

    } else {
      delete translator;
      qWarning() << "Error loading translation" << locale;
      return;
    }

  }

  // After the language is changed from RTL to LTR, the layout direction isn't
  // always restored
  const QString direction =
      QApplication::tr("LTR", "Translate this string to the string 'RTL' in"
                              " right-to-left languages (for example Hebrew and"
                              " Arabic) to get proper widget layout");

  QGuiApplication::setLayoutDirection(direction == "RTL" ? Qt::RightToLeft
                                                         : Qt::LeftToRight);

  for (auto &pair : callbacks){
      pair.second();
  }
}

/**
 * @brief Register a function to be called when the UI needs to be retranslated.
 * @param f Function, wich will called.
 * @param owner Widget to retanslate.
 */
void Translator::registerHandler(const std::function<void()> &f, void *owner) {
//  QMutexLocker locker{&lock};
  callbacks.push_back({owner, f});
}

/**
 * @brief Unregisters all handlers of an owner.
 * @param owner Owner to unregister.
 */
void Translator::unregister(void *owner) {
//  QMutexLocker locker{&lock};
  callbacks.erase(
      std::remove_if(begin(callbacks), end(callbacks),
                     [=](const Callback &c) { return c.first == owner; }),
      end(callbacks));
}
} // namespace main
