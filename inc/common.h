#pragma once

#include <cstddef>
#include <iostream>

namespace Otus
{
    
struct Counters
{
	std::size_t lineCounter{0};
	std::size_t blockCounter{0};
	std::size_t commandCounter{0};

	friend std::ostream& operator<< (std::ostream& a_osOut, const Counters& a_counters)
	{
		if (a_counters.lineCounter > 0) {
			a_osOut << a_counters.lineCounter << " line(s), ";
		}
		a_osOut << a_counters.blockCounter << " block(s), " << a_counters.commandCounter << " command(s)";

		return a_osOut;
	}
};

} // Otus::
