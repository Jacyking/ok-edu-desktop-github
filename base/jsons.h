#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

class Jsons {
public:
  inline static QString toString(const QJsonDocument &document) {
    return QString{document.toJson()};
  }

  inline static QJsonDocument toJSON(const QByteArray &buf) {
    return QJsonDocument::fromJson(buf);
  }
};