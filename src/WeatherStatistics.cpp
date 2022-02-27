//============================================================================
// Name        : WeatherStatistics.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "WeatherStatistics.h"

WeatherStatistics::WeatherStatistics() {
	loadData();
}

WeatherStatistics::~WeatherStatistics() {
	// TODO Auto-generated destructor stub
}

void WeatherStatistics::loadData() {
	for (int year = 2012; year <= 2015; year++) {
		std::ostringstream fileNameStream;
		fileNameStream << RESOURCE_PATH << "Environmental_Data_Deep_Moor_" << year << ".txt";
		std::string fileName = fileNameStream.str();
		std::cout << "Loading " << fileName << std::endl;

		std::fstream dataFileStream;
		dataFileStream.open(fileName);

		std::string line;
		getline(dataFileStream, line); // discard top line with headers
		while (getline(dataFileStream, line)) {
			std::string date, time;
			double Air_Temp, Barometric_Press, Dew_Point, Relative_Humidity, Wind_Dir, Wind_Gust, Wind_Speed;
			std::istringstream buffer(line);

			buffer >> date >> time >> Air_Temp >> Barometric_Press >> Dew_Point >> Relative_Humidity >> Wind_Dir >> Wind_Gust >> Wind_Speed;
			time_t dateTime = convertDateTime(date, time);
			timeToPressure_[dateTime] = Barometric_Press;
		}

		dataFileStream.close();
	}
}

time_t WeatherStatistics::getFirstDateTime() {
	return timeToPressure_.begin()->first;
}

time_t WeatherStatistics::getLastDateTime() {
	return timeToPressure_.rbegin()->first;
}

double WeatherStatistics::computeCoeff(std::string startDate, std::string startTime, std::string endDate, std::string endTime) {
	time_t startDateTime = convertDateTime(startDate, startTime);
	time_t endDateTime = convertDateTime(endDate, endTime);

	if (endDateTime < startDateTime) {
		std::cerr << "ERROR: The start date/time must occur before the end date/time" << std::endl;
		exit(1);
	}

	auto startTimePressure = timeToPressure_.lower_bound(startDateTime);
	auto endTimePressure = timeToPressure_.lower_bound(endDateTime);

	double timeDiff = endTimePressure->first - startTimePressure->first;
	double pressureDiff = endTimePressure->second - startTimePressure->second;

	return (pressureDiff / timeDiff);
}

bool WeatherStatistics::isValidDateTime(std::string date, std::string time) {
	auto dateTime = convertDateTime(date, time);

	if (dateTime < 0)
		return false;

	if ((dateTime < getFirstDateTime()) || (dateTime > getLastDateTime())) {
		std::cerr << "ERROR: " << date << " " << time << " is ut of available data range" << std::endl;
		return false;
	}

	return true;
}

time_t WeatherStatistics::convertDateTime(std::string date, std::string time) {

	// parse values from date string
	int yyyy, mon, dd = 0;

	if (sscanf(date.c_str(), "%d_%d_%d", &yyyy, &mon, &dd) != 3) {
		std::cerr << "ERROR: Failed to parse date string " << date << std::endl;
		return -1;
	}

	// parse values from time string
	int hh, mm, ss = 0;

	if (sscanf(time.c_str(), "%d:%d:%d", &hh, &mm, &ss) != 3) {
		std::cerr << "ERROR: Failed to parse time string " << date << std::endl;
		return -2;
	}

	struct tm dateTime = { };
	dateTime.tm_year = yyyy - 1900; // years since 1900
	dateTime.tm_mon = mon - 1;      // months since January
	dateTime.tm_mday = dd;          // day of the month
	dateTime.tm_hour = hh;          // hours since midnight
	dateTime.tm_min = mm;           // minutes after the hour
	dateTime.tm_sec = ss;           // seconds after the minute

	// return a time_t value representing seconds since 1970
	return mktime(&dateTime);
}
