#include "stdafx.h"
#include "IOThreads.h"

IOThreads::IOThreads(boost::asio::io_context& ioContext, unsigned threadCount)
	: _work(ioContext)
	, _threadCount(threadCount == 0 ? std::thread::hardware_concurrency() * 2 + 2 : threadCount)
{
}

IOThreads::~IOThreads()
{
}

void IOThreads::Run()
{
	if (_threads.size() > 0)
		throw std::exception("IOThreads is already running.");

	for (auto i = 0u; i < _threadCount; ++i)
	{
		auto thread = std::make_shared<std::thread>([&]() -> void
		{
			ThreadRoutine();
		});
		_threads.push_back(thread);
	}
}

void IOThreads::Stop()
{
	if (_threads.size() == 0)
		throw std::exception("IOThreads is already stopped.");

	auto& ioContext = _work.get_io_context();
	ioContext.stop();

	for (auto& thread : _threads)
	{
		thread->join();
	}

	_threads.clear();
}

void IOThreads::ThreadRoutine()
{
	auto& ioContext = _work.get_io_context();
	ioContext.run();
}