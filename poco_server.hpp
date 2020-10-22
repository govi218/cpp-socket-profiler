#include "ConnectionHandler.hpp"
#include "Poco/Net/ParallelSocketAcceptor.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/ServerApplication.h"

using Poco::Net::ParallelSocketAcceptor;
using Poco::Net::ServerSocket;
using Poco::Net::SocketAcceptor;
using Poco::Net::SocketReactor;
using Poco::Util::Application;
using Poco::Util::HelpFormatter;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

class Server : public Poco::Util::ServerApplication {
 public:
  Server();
  ~Server();

 protected:
  int main(const std::vector<std::string>& args);
};
