#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
  boost::asio::io_service ios;

  boost::asio::deadline_timer t(ios, boost::posix_time::seconds(1));
  t.wait();

  std::cout << "Hello, world!" << std::endl;

  return 0;
}