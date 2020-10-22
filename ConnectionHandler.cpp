#include "ConnectionHandler.hpp"

ConnectionHandler::ConnectionHandler(StreamSocket& socket,
                                     SocketReactor& reactor)
    : _socket(socket), _reactor(reactor) {
  i = 0;
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
  // delete[] _pBuffer;
}

void ConnectionHandler::onReadable(const AutoPtr<ReadableNotification>& pNf) {
  // char data[131073] = {0};
  // if (_socket.receiveBytes(data, 1024) > 0) {
  // std::cout << data << std::endl;
  // }
  // i++;
  char* pBuffer = {0};

  std::cout << "her???" << std::endl;

  int n = _socket.receiveBytes(_pBuffer, 131072);

  if (n > 0) {
    std::cout << "Read " << n << " bytes " << std::endl;
    this->onReadable(pNf);
  } else {
    delete this;
  }
}

void ConnectionHandler::onShutdown(const AutoPtr<ShutdownNotification>& pNf) {
  std::cout << "Shutdown???" << std::endl;
  delete this;
}
