#include <signal.h>

#include <boost/asio.hpp>
#include <chrono>
#include <system_error>
#include <thread>
#include <vector>

namespace {
bool keepGoing = true;
void shutdown(int) { keepGoing = false; }

std::size_t bytesAccum = 0;
void justReceive(std::error_code ec, std::size_t bytesReceived,
                 boost::asio::ip::tcp::socket &socket,
                 std::vector<unsigned char> &buffer) {
  bytesAccum += bytesReceived;

  socket.async_receive(
      boost::asio::buffer(buffer), 0,
      [&](auto ec, auto bytes) { justReceive(ec, bytes, socket, buffer); });
}
}  // namespace

int main(int, char **) {
  signal(SIGINT, shutdown);

  boost::asio::io_service io;
  boost::asio::io_service::work work(io);

  std::thread t1([&]() { io.run(); });
  std::thread t2([&]() { io.run(); });
  std::thread t3([&]() { io.run(); });
  std::thread t4([&]() { io.run(); });

  boost::asio::ip::tcp::acceptor acceptor(
      io, boost::asio::ip::tcp::endpoint(
              boost::asio::ip::address::from_string("127.0.0.1"), 1234));
  boost::asio::ip::tcp::socket socket(io);

  // accept 1 client
  std::vector<unsigned char> buffer(131072, 0);
  acceptor.async_accept(socket, [&socket, &buffer](std::error_code ec) {
    // options
    // socket.set_option(boost::asio::ip::tcp::no_delay(true));
    // socket.set_option(boost::asio::socket_base::receive_buffer_size(8192  *
    // 2)); socket.set_option(boost::asio::socket_base::send_buffer_size(8192));

    socket.async_receive(
        boost::asio::buffer(buffer), 0,
        [&](auto ec, auto bytes) { justReceive(ec, bytes, socket, buffer); });
  });

  while (keepGoing) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  io.stop();

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  std::printf("server: goodbye\n");
}
