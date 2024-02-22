#include "BaseService.h"

#include <QObject>
#include <QString>

#include "base/r.h"
#include "lib/network/NetworkHttp.h"

#include <algorithm>
#include <base/singleton.h>
#include <lib/session/AuthSession.h>

namespace ok::backend {

BaseService::BaseService(QObject *parent)                   //
    : QObject(parent),                                      //
      http(std::make_unique<network::NetworkHttp>(this)), //
      _baseUrl(BACKEND_BASE_URL) {}

BaseService::~BaseService() {}

} // namespace ok::backend
