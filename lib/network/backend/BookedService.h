#pragma once

#include <QDateTime>
#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QVariant>

#include <base/basic_types.h>
#include <base/jsons.h>
#include <lib/network/backend/BaseService.h>

namespace ok::backend {

class BookedInfo {
public:
  qint64 getId() { return id; }
  qint64 getLessonId() { return lessonId; }
  QString getLessonName() { return lessonName; }
  QDateTime getBeginTime() { return beginTime; }
  QDateTime getEndTime() { return endTime; }

  void fromJSON(const QJsonObject &data) {
    id = (data.value("id").toVariant().toLongLong());
    if (0 < id) {
      lessonId = data.value("lessonId").toVariant().toLongLong();
      lessonName = data.value("lessonName").toVariant().toString();
      beginTime = QDateTime::fromTime_t(
          data.value("beginTime").toVariant().toLongLong() / 1000);
      endTime = QDateTime::fromTime_t(
          data.value("endTime").toVariant().toLongLong() / 1000);
    }
  }

  QJsonObject toJSON() {
    QJsonObject qo;
    qo.insert("id", QJsonValue(id));
    qo.insert("lessonId", QJsonValue(lessonId));
    qo.insert("lessonName", lessonName);
    qo.insert("beginTime", QJsonValue((qint64)beginTime.toTime_t()));
    qo.insert("endTime", QJsonValue((qint64)endTime.toTime_t()));
    return qo;
  }

private:
  qint64 id = 0;

  qint64 lessonId = 0;
  QString lessonName = nullptr;

  QDateTime beginTime;
  QDateTime endTime;
};

class DowncountInfo   {
public:
  qint64 getSeconds() { return seconds; }

//  void fromJSON(const QJsonObject &data) {
//    seconds = data.value("seconds").toVariant().toLongLong();
//  }
//
//  QJsonObject toJSON() {
//    QJsonObject qo;
//    qo.insert("seconds", QJsonValue(seconds));
//    return qo;
//  }

private:
  qint64 seconds = 0;
};

class BookedService : public BaseService {
  Q_OBJECT
public:
  BookedService(QObject *parent);
  ~BookedService();

  bool requestCurrent(Fn<void(BookedInfo)> callback);

  bool requestNext(Fn<void(BookedInfo)> callback);

  bool requestDowncount(Fn<void(DowncountInfo)> callback);

  bool requestBooked(QString &url, Fn<void(BookedInfo)> callback);

  QString baseUrl();

private:
signals:
  void lessonChange(ok::backend::BookedInfo *);

public slots:
};

} // namespace ok::backend
