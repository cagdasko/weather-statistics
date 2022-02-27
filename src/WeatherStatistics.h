/*
 * WeatherStatistics.h
 *
 *  Created on: Feb 27, 2022
 *      Author: cagdask
 */

#ifndef WEATHERSTATISTICS_H_
#define WEATHERSTATISTICS_H_

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

class WeatherStatistics {
public:
	WeatherStatistics();
	virtual ~WeatherStatistics();

	double computeCoeff(std::string startDate, std::string startTime, std::string endDate, std::string endTime);
	bool isValidDateTime(std::string date, std::string time);

private:
	const std::string RESOURCE_PATH { "../resources/" };

	std::map<time_t, double> timeToPressure_;

	void loadData();
	time_t getFirstDateTime();
	time_t getLastDateTime();
	time_t convertDateTime(std::string date, std::string time);
};

#endif /* WEATHERSTATISTICS_H_ */
