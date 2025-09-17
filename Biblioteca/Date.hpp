#pragma once

#include <cstdint>
#include <string>

class Date
{
public:
    Date();
    Date(int8_t day, int8_t month, int year);

    static bool IsValid(int day, int month, int year);
    static bool IsYearLeap(int year);
    static Date Now();

    std::string ToString() const;

    bool operator>(const Date& other) const noexcept;
    bool operator>=(const Date& other) const noexcept;
    bool operator<(const Date& other) const noexcept;
    bool operator<=(const Date& other) const noexcept;
    bool operator==(const Date& other) const noexcept;
    bool operator!=(const Date& other) const noexcept;

    int Year() const noexcept { return m_Year; }
    int8_t Month() const noexcept { return m_Month; }
    int8_t Day() const noexcept { return m_Day; }

private:
    static constexpr int8_t DEFAULT_DAY = 1;
    static constexpr int8_t DEFAULT_MONTH = 1;
    static constexpr int DEFAULT_YEAR = 1900;

    int8_t m_Day;
    int8_t m_Month;
    int m_Year;
};
