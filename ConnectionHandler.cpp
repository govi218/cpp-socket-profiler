#include "ConnectionHandler.hpp"

ConnectionHandler::ConnectionHandler(StreamSocket& socket,
                                     SocketReactor& reactor)
    : _socket(socket), _reactor(reactor), _pBuffer(new char[BUFFER_SIZE]) {
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
  int n = _socket.receiveBytes(&_pBuffer[0], BUFFER_SIZE);

  // keep reading
  if (n == 0) {
    delete this;
  }
}

void ConnectionHandler::onShutdown(const AutoPtr<ShutdownNotification>& pNf) {
  std::cout << "goodbye" << std::endl;
  delete this;
}
