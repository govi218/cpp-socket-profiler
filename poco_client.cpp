#include <Poco/Net/StreamSocket.h>
#include <signal.h>

#include <chrono>
#include <iostream>
#include <system_error>
#include <thread>
#include <vector>

namespace {
bool keepGoing = true;
void shutdown(int) { keepGoing = false; }
}  // namespace

int main(int, char **) {
  signal(SIGINT, shutdown);

  double gbps = 0, total_gbps = 0, iters = 0;
  Poco::Net::StreamSocket ss;
  ss.connect(Poco::Net::SocketAddress("127.0.0.1", "1234"));

  std::vector<uint8_t> buffer(131072, 0);
  buffer.back() = 'e';

  std::chrono::time_point<std::chrono::system_clock> last =
      std::chrono::system_clock::now();

  std::chrono::duration<double> delta = std::chrono::seconds(0);

  std::size_t bytesSent = 0;

  while (keepGoing) {
    // blocks during send?
    ss.sendBytes(buffer.data(), buffer.size());

    // accumulate bytes sent
    bytesSent += buffer.size();

    // accumulate time spent sending
    delta += std::chrono::system_clock::now() - last;
    last = std::chrono::system_clock::now();

    // print information periodically
    if (delta.count() >= 1.0) {
      gbps = 8 * bytesSent / 1.0e9 / delta.count();
      std::printf(
          "Mbytes/sec: %f, Gbytes/sec: %f, Mbits/sec: %f, "
          "Gbits/sec: %f\n",
          bytesSent / 1.0e6 / delta.count(), bytesSent / 1.0e9 / delta.count(),
          8 * bytesSent / 1.0e6 / delta.count(), gbps);

      // reset accumulators
      total_gbps += gbps;
      iters++;
      bytesSent = 0;
      delta = std::chrono::seconds(0);
    }
  }

  std::printf("Average thru Gbps: %f\n", total_gbps / iters);
  std::printf("client: goodbyte\n");
}
