#include "poco_server.hpp"

Server::Server() {}

Server::~Server() {}

int Server::main(const std::vector<std::string>& args) {
  unsigned short port = (unsigned short)1234;
  // set-up a server socket
  ServerSocket svs(port);
  // set-up a SocketReactor...
  SocketReactor reactor;
  // ... and a SocketAcceptor
  ParallelSocketAcceptor<ConnectionHandler, SocketReactor> acceptor(svs,
                                                                    reactor);
  // run the reactor in its own thread so that we can wait for
  // a termination request
  Thread thread;
  thread.start(reactor);
  // wait for CTRL-C or kill
  waitForTerminationRequest();
  // Stop the SocketReactor
  reactor.stop();
  thread.join();

  return Application::EXIT_OK;
}
