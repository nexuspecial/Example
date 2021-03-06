// Ntp.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#include <iostream>

#include <boost/asio.hpp>
#include <boost/array.hpp>

int main()
{
	using namespace boost::asio;

	io_context io_context;

	ip::udp::resolver resolver(io_context);
	ip::udp::resolver::query query(ip::udp::v4(), "time.bora.net", "123");
	auto receiver_endpoint = *resolver.resolve(query);

	ip::udp::socket socket(io_context);
	socket.open(ip::udp::v4());

	boost::array<char, 48> send_buf = { 0 };
	send_buf[0] = (char)0b11100011;
	send_buf[1] = 0;
	send_buf[2] = 6;
	send_buf[3] = (char)0xEC;

	socket.send_to(buffer(send_buf), receiver_endpoint);

	boost::array<char, 48> recv_buf = { 0 };
	ip::udp::endpoint sender_endpoint;
	auto len = socket.receive_from(buffer(recv_buf), sender_endpoint);
	if (len == 48)
	{
		auto int_part = (long)recv_buf[40] << 24 | (long)recv_buf[41] << 16 | (long)recv_buf[42] << 8 | recv_buf[43];
		auto fract_part = (long)recv_buf[44] << 24 | (long)recv_buf[45] << 16 | (long)recv_buf[46] << 8 | recv_buf[47];
		auto milliseconds = 
	}
	else
	{
		std::cout << "error: size[" << len << "]"<< std::endl;
	}

    return 0;
}

