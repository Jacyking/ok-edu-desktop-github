﻿#pragma once

#include <QJsonDocument>
#include <QObject>
#include <QString>
#include <string>

#include "base/r.h"
#include "lib/network/NetworkHttp.h"
#include "lib/network/NetworkManager.h"
#include "lib/network/backend/BaseService.h"

#include <QJsonArray>
#include <QList>

namespace ok::backend {

template <typename T> //
class Res {
public:
  int code;
  QString msg;
  T *data;

  Res(const QJsonDocument &doc) : code{-1}, data{nullptr} {
    if (doc.isEmpty()) {
      code = -1;
      return;
    }

    auto obj = doc.object();
    code = obj.value(("code")).toInt();
    msg = obj.value("msg").toString();
    if (code == 0)
      data = new T(obj.value("data").toObject());
  }

  Res(const QString &err) {
    code = -1;
    msg = err;
  }

  ~Res() {
    if (code == 0)
      delete data;
  }

  bool success() const { return code == 0; }
};

template <typename T> //
class ResList {
public:
  int code;
  QString msg;
  QList<T*> data;

  ResList(const QJsonDocument &doc) : code{-1}  {
    if (doc.isEmpty()) {
      code = -1;
      return;
    }

    auto obj = doc.object();
    code = obj.value(("code")).toInt();
    msg = obj.value("msg").toString();
    if (code == 0){
      QJsonArray arr = obj.value("data").toArray();
      for(auto i : arr){
        data.append(new T(i.toObject()));
      }
    }
  }

  ResList(const QString &err) {
    code = -1;
    msg = err;
  }

  ~ResList() {
    if (code == 0){
//      qDeleteAll(data.begin(), data.end());
      data.clear();
    }
  }

  bool success() const { return code == 0; }
};

class BaseService : public QObject {
  Q_OBJECT
public:
  BaseService(QObject *parent = nullptr);
  ~BaseService();

  [[maybe_unused]] inline const QString &baseUrl() const { return _baseUrl; }

protected:
  std::unique_ptr<network::NetworkHttp> http;
  QString _baseUrl;
};

} // namespace ok::backend
