/*
 * Main.cpp
 *
 *  Created on: Feb 27, 2022
 *      Author: cagdask
 */

#include <utility>
#include "WeatherStatistics.h"

std::pair<std::string, std::string> getStartDateTime() {
	std::string date, startTime;
	std::cout << std::endl << "Enter START DATE as yyyy_mm_dd: ";
	std::cin >> date;
	std::cout << "Enter START TIME as hh:mm:ss (24-hour): ";
	std::cin >> startTime;

	return std::make_pair(date, startTime);
}

std::pair<std::string, std::string> getEndDateTime() {
	std::string date, time;
	std::cout << std::endl << "Enter END DATE as yyyy_mm_dd: ";
	std::cin >> date;
	std::cout << "Enter END TIME as hh:mm:ss (24-hour): ";
	std::cin >> time;

	return std::make_pair(date, time);
}

int main(int argc, char **argv) {
	WeatherStatistics stats;
	auto startDateTime = getStartDateTime();

	if (!stats.isValidDateTime(startDateTime.first, startDateTime.second))
		return 1;

	auto endDateTime = getEndDateTime();

	if (!stats.isValidDateTime(endDateTime.first, endDateTime.second))
		return 1;

	double coeff = stats.computeCoeff(startDateTime.first, startDateTime.second, endDateTime.first, endDateTime.second);

	std::cout << std::endl << "Coefficient: " << coeff * 24 * 60 * 60 << " inHg/day" << std::endl;

	if (coeff < 0)
		std::cout << "It will be stormy" << std::endl;
	else
		std::cout << "It will be sunny" << std::endl;

	return 0;
}
