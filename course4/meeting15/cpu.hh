#pragma once

#include <stdexcept>

#include <sched.h>

void set_cpu(unsigned cpu)
{
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(cpu, &set);
	if (::sched_setaffinity(0, sizeof(set), &set))
	{
		throw std::runtime_error("Failed to set CPU mask");
	}
}

int get_cpu()
{
	return ::sched_getcpu();
}
