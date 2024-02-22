#include "PushService.h"

#include "lib/network/NetworkManager.h"
#include <QObject>
#include <lib/network/backend/BaseService.h>
#include <lib/network/backend/HttpService.h>


namespace ok::backend {

PushService::PushService(QObject *parent) : BaseService(parent) {}

PushService::~PushService() {}

bool PushService::requestCount(Fn<void(PushInfo &)> callback) {
  // QUrl url(QString(_baseUrl + "/push/info.do"));

  // m_networkManager->getJSON(url, [&, callback](QJsonObject res)
  // 						  {
  // 							  if
  // (res.value(("success")).toBool())
  // 							  {
  // 								  QJsonObject jo =
  // res.value("data").toObject();

  // 								  PushInfo info;
  // 								  info.fromJSON(jo);

  // 								  callback(info);
  // 							  }
  // 						  });

  return true;
}
} // namespace ok::backend
