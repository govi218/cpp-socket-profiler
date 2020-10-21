#include <iostream>

#include "Poco/Exception.h"
#include "Poco/NObserver.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Thread.h"
#include "Poco/Util/ServerApplication.h"

using Poco::AutoPtr;
using Poco::NObserver;
using Poco::Thread;
using Poco::Net::ReadableNotification;
using Poco::Net::ShutdownNotification;
using Poco::Net::SocketReactor;
using Poco::Net::StreamSocket;
using Poco::Util::Application;

class ConnectionHandler {
 public:
  ConnectionHandler(StreamSocket& socket, SocketReactor& reactor);
  ~ConnectionHandler();
  void onReadable(const AutoPtr<ReadableNotification>& pNf);
  void onShutdown(const AutoPtr<ShutdownNotification>& pNf);

 private:
  enum { BUFFER_SIZE = 131072 };

  StreamSocket _socket;
  SocketReactor& _reactor;
  char* _pBuffer;
};
