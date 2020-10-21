#include "ConnectionHandler.hpp"

ConnectionHandler::ConnectionHandler(StreamSocket& socket,
                                     SocketReactor& reactor)
    : _socket(socket), _reactor(reactor) {
  Application& app = Application::instance();
  app.logger().information("Connection from " +
                           socket.peerAddress().toString());

  _reactor.addEventHandler(_socket,
                           NObserver<ConnectionHandler, ReadableNotification>(
                               *this, &ConnectionHandler::onReadable));
  _reactor.addEventHandler(_socket,
                           NObserver<ConnectionHandler, ShutdownNotification>(
                               *this, &ConnectionHandler::onShutdown));
}

ConnectionHandler::~ConnectionHandler() {
  Application& app = Application::instance();
  try {
    app.logger().information("Disconnecting " +
                             _socket.peerAddress().toString());
  } catch (...) {
  }
  _reactor.removeEventHandler(
      _socket, NObserver<ConnectionHandler, ReadableNotification>(
                   *this, &ConnectionHandler::onReadable));
  _reactor.removeEventHandler(
      _socket, NObserver<ConnectionHandler, ShutdownNotification>(
                   *this, &ConnectionHandler::onShutdown));
  delete[] _pBuffer;
}

void ConnectionHandler::onReadable(const AutoPtr<ReadableNotification>& pNf) {
  int n = _socket.receiveBytes(_pBuffer, BUFFER_SIZE);
  char o[3];
  memset(o, 0x00, sizeof(o));

  // FIXME: modify to read
  if (n > 0) {
    for (int i = 0; i < 30; i++) {
      std::snprintf(o, 3, "%2d", i);
      _socket.sendBytes(&o, 3);
      sleep(1);
    }
  } else {
    delete this;
  }
}

void ConnectionHandler::onShutdown(const AutoPtr<ShutdownNotification>& pNf) {
  delete this;
}
