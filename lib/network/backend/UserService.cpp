#include "UserService.h"

#include <QJsonObject>
#include <QUrl>

#include <base/basic_types.h>

#include <base/logs.h>

#include "lib/network/NetworkManager.h"

#include <lib/network/backend/BaseService.h>
#include <lib/network/backend/HttpService.h>

#include "base/r.h"
#include "qjsonarray.h"
#include "qjsonobject.h"

namespace ok::backend {

using namespace network;

UserService::UserService(QObject *parent) : BaseService(parent) {}

UserService::~UserService() {}

void UserService::search(const QString &query,
                         Fn<void(const QList<OrgStaff*> &)> fn) {

  QUrl url(QString(_baseUrl + "/staff/search?q=%1").arg(query));
  http->getJSON(
      QUrl(url),
      // success
      [=](QJsonDocument doc) {
        ResList<OrgStaff> res(doc);
        fn(res.data);
      },
      // error
      [=](QString err) {
        ResList<OrgStaff> res(err);
        fn(res.data);
      });
}

void UserService::setUserType(const QString &userType) {
  QUrl url(QString(_baseUrl + "/user/setUserType"));
  http->post(url, userType, [&](QByteArray res) {
    DEBUG_LOG_S(L_INFO) << "received:" << QString(res);
  });
}

} // namespace ok::backend
