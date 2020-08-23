
#pragma once
#include <iostream>


#ifndef AMA_DATE_H
#define AMA_DATE_H

namespace ama
{
	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date
	{
		int year, month, day, statusValue;
		void status(int newStatus);
		int mdays(int year, int month) const;

	public:
		Date();
		Date(int year, int month, int day);
		int status() const;
		void clearError();
		bool isGood() const;
		Date& operator+=(int days);
		Date& operator++();
		Date operator++(int day);
		Date operator+(int days) const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		std::istream& read(std::istream& rs);
		std::ostream& write(std::ostream& os) const;

	};
	std::ostream& operator<<(std::ostream& rs, const Date& date);
	std::istream& operator>>(std::istream& rs, Date& date);
}

#endif
