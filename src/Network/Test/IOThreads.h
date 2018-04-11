#pragma once

class IOThreads
{
public:
	IOThreads(boost::asio::io_context& ioContext, unsigned threadCount = 0);
	~IOThreads();

	void Run();
	void Stop();

private:
	void ThreadRoutine();

private:
	unsigned _threadCount;
	std::vector<std::shared_ptr<std::thread>> _threads;
	boost::asio::io_context::work _work;
};
