#pragma once

#include "Stat.h"

#include <iostream>
#include <string>

#define MAX_STATS         100

class Day {
	private:
		std::string         _date;
		Stat*               _stats[MAX_STATS];
		int                 _statCount = 0;
		int                 _currentStat = -1;

	public:
		Day(std::string date);
		void addStat(Stat *stat);
		void resetStatIteration();
		Stat* getStatNext();
		std::string getDate();
};

