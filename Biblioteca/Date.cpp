#include "Date.hpp"

#include <ctime>

Date::Date() : m_Day(Date::DEFAULT_DAY), m_Month(Date::DEFAULT_MONTH), m_Year(Date::DEFAULT_YEAR) {}

Date::Date(int day, int month, int year)
{
    if(Date::IsValid(day, month, year))
    {
        m_Day = day;
        m_Month = month;
        m_Year = year;
    }
    else
    {
        m_Day = Date::DEFAULT_DAY;
        m_Month = Date::DEFAULT_MONTH;
        m_Year = Date::DEFAULT_YEAR;
    }
}

bool Date::IsValid(int day, int month, int year)
{
    int daysNumber[] = { 31, (Date::IsYearLeap(year)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return !(
        (year < Date::DEFAULT_YEAR) ||
        (month <= 0 || month > 12) ||
		(day <= 0 || day > daysNumber[month - 1])
    );
}

bool Date::IsYearLeap(int year)
{
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

Date Date::CurrentDate()
{
    std::time_t seconds = std::time(nullptr);
    std::tm* calendarTime = std::localtime(&seconds);

    return Date{calendarTime->tm_mday, calendarTime->tm_mon + 1, calendarTime->tm_year + 1900};
}

std::string Date::ToString() const
{
    constexpr const char* monthNames[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    return std::to_string(m_Day) + " " + monthNames[m_Month - 1] + " " + std::to_string(m_Year);
}

bool Date::operator>(const Date& other) const noexcept
{
    return (
        (m_Year > other.m_Year) ||
        (m_Year == other.m_Year && m_Month > other.m_Month) ||
        (m_Year == other.m_Year && m_Month == other.m_Month && m_Day > other.m_Day)
    );
}

bool Date::operator>=(const Date& other) const noexcept
{
    return (*this > other || *this == other);
}

bool Date::operator<(const Date& other) const noexcept
{
    return !(*this >= other);
}

bool Date::operator<=(const Date& other) const noexcept
{
    return !(*this > other);
}

bool Date::operator==(const Date& other) const noexcept
{
    return (m_Day == other.m_Day && m_Month == other.m_Month && m_Year == other.m_Year);
}

bool Date::operator!=(const Date& other) const noexcept
{
    return !(*this == other);
}
