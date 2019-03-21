#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <stdlib.h>
#include <sstream>
#include "spdlog/spdlog.h"
int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cerr << "Number of philosophers argument required." << std::endl;
	}
	else
	{
		int philosopher_count = std::atoi(argv[1]);
		bool isRunning;
		std::vector<std::thread> threads;

		for (int i = 0; i < philosopher_count; ++i)
		{
			threads.push_back(std::thread([&]() {
				while (isRunning)
				{
					static thread_local std::random_device device;
					static thread_local std::uniform_int_distribution<> dist(500, 2000);
					static thread_local int id = i;

					std::ostringstream ss;
					ss << std::this_thread::get_id();

					spdlog::info("Philosopher #{} is eating. Thread_id: {}", id, ss.str());
					std::this_thread::sleep_for(std::chrono::milliseconds(dist(device)));
					spdlog::info("Philosopher #{} is thinking. Thread_id: {}", id, ss.str());
					std::this_thread::sleep_for(std::chrono::milliseconds(dist(device)));
				}
				}));
		}

		while (std::getchar() != 'q');
		isRunning = false;

		for (auto &t : threads)
		{
			t.join();
		}
	}
	return 0;

}
