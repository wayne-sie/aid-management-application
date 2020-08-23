//Wayne Sie 139951180 BTP200SCC
#include <iostream>
#include <string>

#include "Date.h"

using namespace std;
using namespace ama;

namespace ama
{
	void Date::status(int newStatus)
	{
		this->statusValue = newStatus;
	}

	int Date::mdays(int year, int mon) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13; month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	Date::Date()
	{
		this->statusValue = no_error;
		this->month = 0;
		this->year = 0;
		this->day = 0;
	}

	Date::Date(int year, int month, int day)
	{
		bool correctYear = year >= min_year && year <= max_year;
		bool correctMonth = month >= 1 && month <= 12;
		bool correctDay = day>0 && day <= mdays(year, month);
		if (correctYear && correctMonth && correctDay)
		{
			statusValue = no_error;
			this->year = year;
			this->month = month;
			this->day = day;

		}
		else
		{
			if (correctYear != true)
			{
				*this = Date();
				this->statusValue = error_year;
			}
			else if (correctMonth != true)
			{
				*this = Date();
				this->statusValue = error_mon;
			}
			else if (correctDay != true)
			{
				*this = Date();
				this->statusValue = error_day;
			}
		}

	}

	int Date::status() const
	{
		return this->statusValue;
	}

	void Date::clearError()
	{
		this->statusValue = no_error;
	}

	bool Date::isGood() const
	{
		bool correctYear = year >= min_year && year <= max_year;
		bool correctMonth = month >= 1 && month <= 12;
		bool correctDay = day>0 && day <= mdays(year, month);
		bool correctStatus = statusValue == no_error;

		return (correctYear && correctMonth && correctDay && correctStatus);
	}

	Date& Date::operator+=(int days)
	{
		if (this->statusValue != no_error || (this->year == 0 && this->month == 0 && this->day == 0))
		{
			this->statusValue = error_invalid_operation;
		}
		else
		{
			int tempDay = this->day;
			tempDay += days;
			if (tempDay > mdays(this->year, this->month) || tempDay < 0)
			{
				this->statusValue = error_invalid_operation;
			}
			else
			{
				this->day = tempDay;
			}
		}
		//if(this->statusValue != no_error || )
		return *this;
	}

	Date& Date::operator++()
	{
		Date::operator+=(1);
		return *this;
	}

	Date Date::operator++(int)
	{
		Date temp = *this;
		*this += 1;
		return temp;
	}

	Date Date::operator+(int days) const
	{
		Date temp = *this;
		temp += (days);
		return temp;
	}

	bool Date::operator==(const Date& rhs) const
	{
		return this->year == rhs.year && this->month == rhs.month && this->day == rhs.day;
	}

	bool Date::operator!=(const Date& rhs) const
	{
		return !(*this == (rhs));
	}

	bool Date::operator<(const Date& rhs) const
	{
		int value1 = this->day + 31 * this->month + 372 * this->year;
		int value2 = rhs.day + 31 * rhs.month + 372 * rhs.year;
		return value1 < value2;

	}

	bool Date::operator>(const Date& rhs) const
	{

		int value1 = this->day + 31 * this->month + 372 * this->year;
		int value2 = rhs.day + 31 * rhs.month + 372 * rhs.year;
		return value1 > value2;
	}

	bool Date::operator<=(const Date& rhs) const
	{

		int value1 = this->day + 31 * this->month + 372 * this->year;
		int value2 = rhs.day + 31 * rhs.month + 372 * rhs.year;
		return value1 <= value2;
	}

	bool Date::operator>=(const Date& rhs) const
	{

		int value1 = this->day + 31 * this->month + 372 * this->year;
		int value2 = rhs.day + 31 * rhs.month + 372 * rhs.year;
		return value1 >= value2;
	}

	istream& Date::read(istream& is)
	{
		int yahr, monat, tag;
		is >> yahr;
		is.ignore();
		is >> monat;
		is.ignore();
		is >> tag;
		if (is.fail() == true)
		{
			*this = Date();
			statusValue = error_input;
		}
		else
		{
			*this = Date(yahr, monat, tag);
		}
		return is;
	}

	ostream& Date::write(ostream& os) const
	{
		Date temp = Date(this->year, this->month, this->day);

		char oldChar = os.fill('0');
		os.width(4);
		os << temp.year;
		os << "/";
		os.setf(ios::right);
		os.fill('0');
		os.width(2);
		os << temp.month;
		os << "/";
		os.fill('0');
		os.width(2);
		os << temp.day;
		os.fill(oldChar);
		os.unsetf(ios::right);

		return os;
	}

	std::ostream& operator<<(std::ostream & rs, const Date& date)
	{
		// TODO: insert return statement here
		date.write(rs);
		return rs;
	}
	std::istream& operator>>(std::istream & rs, Date& date)
	{
		// TODO: insert return statement here
		date.read(rs);
		return rs;
	}

}

