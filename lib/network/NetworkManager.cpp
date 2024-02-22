#include "NetworkManager.h"

#include <memory>

#include <base/files.h>
#include <base/logs.h>


namespace network {

static NetworkManager *self = nullptr;

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {}

NetworkManager::~NetworkManager() {}

} // namespace network
