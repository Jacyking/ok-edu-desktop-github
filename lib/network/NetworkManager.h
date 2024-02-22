#pragma once

#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>
#include <QUrl>
#include <memory>

#include "lib/network/NetworkHttp.h"
#include "lib/network/network.h"

#include <base/basic_types.h>
#include <base/timer.h>

namespace network {

class NetworkManager : public QObject {
  Q_OBJECT
public:
  explicit NetworkManager(QObject* parent = nullptr);
  ~NetworkManager();
};

} // namespace network
