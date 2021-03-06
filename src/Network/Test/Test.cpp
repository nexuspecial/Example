// Test.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#include "IOThreads.h"

int main()
{
	boost::asio::io_context io_context;
	IOThreads ioThreads(io_context);

	ioThreads.Run();

	ioThreads.Stop();

    return 0;
}

