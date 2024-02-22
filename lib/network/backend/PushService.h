#pragma once

#include <QObject>

#include "base/jsons.h"
#include <lib/network/backend/BaseService.h>
#include <lib/network/backend/HttpService.h>

namespace ok::backend {

class PushInfo  {
public:
  int getCount() const { return count; }

private:
  int count = 0;
};

class PushService : public BaseService {
  Q_OBJECT

public:
  PushService(QObject *parent = nullptr);
  ~PushService();

  bool requestCount(Fn<void(PushInfo &)> callback);
};
} // namespace ok::backend
