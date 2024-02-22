#ifndef IMJINGLEHANDLER_H
#define IMJINGLEHANDLER_H

namespace lib {
namespace messenger {

class IMJingleHandler {
public:
  virtual ~IMJingleHandler();

  virtual void jingleInitiate() = 0;
  virtual void jingleAccept() = 0;
  virtual void jingleTerminate() = 0;

protected:
};

} // namespace messenger
} // namespace network

#endif // IMJINGLEHANDLER_H
