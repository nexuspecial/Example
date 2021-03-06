// Coroutine2.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#include <iostream>

#include <boost/coroutine2/all.hpp>

int main()
{
#if 0

	std::cout << "Hello, World~!" << std::endl;

#else
	try
	{
		using namespace boost::coroutines2;

		coroutine<int>::pull_type numberGenerator(
			[&](coroutine<int>::push_type& sink) {

			int i = 0;
			while (true)
			{
				++i;
				sink(i);
			}

		});

		auto one = numberGenerator.get();
		numberGenerator();

		std::cout << "one: " << one << std::endl;

		auto two = numberGenerator.get();
		numberGenerator();

		std::cout << "two: " << two << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
#endif

    return 0;
}

