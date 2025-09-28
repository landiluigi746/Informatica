#pragma once

#include <string>

class Date
{
public:
    Date();
    Date(int day, int month, int year);

    static bool IsValid(int day, int month, int year);
    static bool IsYearLeap(int year);
    static Date CurrentDate();

    std::string ToString() const;

    bool operator>(const Date& other) const noexcept;
    bool operator>=(const Date& other) const noexcept;
    bool operator<(const Date& other) const noexcept;
    bool operator<=(const Date& other) const noexcept;
    bool operator==(const Date& other) const noexcept;
    bool operator!=(const Date& other) const noexcept;

    int Year() const noexcept { return m_Year; }
    int Month() const noexcept { return m_Month; }
    int Day() const noexcept { return m_Day; }

private:
    static constexpr int DEFAULT_DAY = 1;
    static constexpr int DEFAULT_MONTH = 1;
    static constexpr int DEFAULT_YEAR = 1900;

    int m_Day;
    int m_Month;
    int m_Year;
};
