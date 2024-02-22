#include "PassportService.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <memory>
#include <string>

#include "base/r.h"
#include <lib/session/AuthSession.h>

#include <base/basic_types.h>
#include <base/logs.h>

#include <lib/network/backend/BaseService.h>
#include <lib/network/backend/HttpService.h>

namespace ok::backend {

using namespace session;

PassportService::PassportService(QObject *parent) : BaseService(parent) {}

PassportService::~PassportService() {}

bool PassportService::getAccount(const QString &account,
                                 Fn<void(Res<SysAccount> &)> fn) {
  QString url = _baseUrl + "/passport/account/" + account;
  http->getJSON(
      QUrl(url),
      //success
      [=](QJsonDocument doc) {
        Res<SysAccount> res(doc);
        fn(res);
      },
      //error
      [=](QString err) {
        Res<SysAccount> res(err);
        fn(res);
      });
  return true;
}

} // namespace ok::backend
