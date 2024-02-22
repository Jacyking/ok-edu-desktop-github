#pragma once

#include <QDateTime>
#include <QObject>
#include <QUuid>

#include "basic_types.h"

namespace base {

class Utils {
public:
  Utils();
  ~Utils();

  static QString GetUUID() {
    // 去除前后“{}”
    return QUuid::createUuid().toString().remove(0, 1).remove(36, 1);
  }

  static QString GetISOTime() {
    return QDateTime::currentDateTime().toString(Qt::DateFormat::ISODate);
  }

  static QString GetTimestamp() {
    QString ts =
        QString("%1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch());
    return ts;
  }
};
} // namespace base
