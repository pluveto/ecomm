/**
 * @file utils.hpp
 * @author Pluveto (pluvet@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Pluveto (Zhang Zijing), Incolore Team. All Rights Reserved.
 * 
 */
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include <algorithm>
#include <cctype>
#include <locale>
#include <codecvt>
#include <regex>
#include <iomanip>

namespace ecomm
{

    class util
    {
    public:
        /**
         * @brief Split a std::string by delim
         * 
         * @param str 
         * @param delim 
         * @return std::vector<std::string> 
         */
        static std::vector<std::string> str_split(const std::string &str, const std::string &delim)
        {
            std::vector<std::string> tokens;
            size_t prev = 0, pos = 0;
            do
            {
                pos = str.find(delim, prev);
                if (pos == std::string::npos)
                    pos = str.length();
                std::string token = str.substr(prev, pos - prev);
                if (!token.empty())
                    tokens.push_back(token);
                prev = pos + delim.length();
            } while (pos < str.length() && prev < str.length());
            return tokens;
        }

        /**
 * @brief Join a array of something to a single std::string
 * 
 * @tparam InputIt 
 * @param begin 
 * @param end 
 * @param separator 
 * @param concluder 
 * @return std::string 
 */
        template <typename InputIt>
        static std::string join(InputIt begin,
                                InputIt end,
                                const std::string &separator = "\n",
                                const std::string &concluder = "")
        {
            std::stringstream ss;

            if (begin != end)
            {
                ss << *begin++; // see 3.
            }

            while (begin != end) // see 3.
            {
                ss << separator;
                ss << *begin++;
            }

            ss << concluder;
            return ss.str();
        }

        template <typename K, typename V>
        static void print_map_key(std::unordered_map<K, V> const &m)
        {
            for (auto const &pair : m)
            {
                std::cout << pair.first;
            }
            std::cout << std::endl;
        }

        // trim from start (in place)
        static inline void str_ltrim(std::string &s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                        return !std::isspace(ch);
                    }));
        }

        static bool in_array(std::string needle, std::vector<std::string> haystack)
        {
            for (auto s : haystack)
            {
                if (s == needle)
                {
                    return true;
                }
            }
            return false;
        }

        // trim from end (in place)
        static inline void str_rtrim(std::string &s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                        return !std::isspace(ch);
                    }).base(),
                    s.end());
        }

        // trim from both ends (in place)
        static inline void str_trim(std::string &s)
        {
            util::str_ltrim(s);
            util::str_rtrim(s);
        }

        // trim from start (copying)
        static inline std::string str_ltrim_copy(std::string s)
        {
            util::str_ltrim(s);
            return s;
        }

        // trim from end (copying)
        static inline std::string str_rtrim_copy(std::string s)
        {
            util::str_rtrim(s);
            return s;
        }

        // trim from both ends (copying)
        static inline std::string str_trim_copy(std::string s)
        {
            util::str_trim(s);
            return s;
        }
        template <typename T>
        static bool expect_number(T &num_out, T min_val, T max_val)
        {
            std::cin >> num_out;
            if (std::cin.fail())
            {
                printf("Invalid input, expecting number.\n");
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return false;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (num_out < min_val || num_out > max_val)
            {
                std::cout << "Invalid number input, not in range " << min_val << " <= x <= " << max_val << "." << std::endl;
                return false;
            }
            return true;
        }

        static bool expect_datetime_max_try(time_t &ts_out, time_t min_time, time_t max_time, int max_try = 3, std::string prompt = "", std::string retry_prompt = "Retry. ")
        {
            int current_try = 0;
            while (!util::expect_datetime(ts_out, min_time, max_time))
            {
                std::cout << retry_prompt;
                std::cout << prompt;
                current_try++;
                if (current_try == max_try)
                {
                    std::cout << "Exceding max try times.\n";
                    return false;
                }
            }
            return true;
        }
        static bool expect_datetime(time_t &ts_out, time_t min_time, time_t max_time)
        {
            // auto static datetime_pattern = std::regex("^(0[1-9]|1\\d|2[0-8]|29(?=-\\d\\d-(?!1[01345789]00|2[1235679]00)\\d\\d"
            //                                           "(?:[02468][048]|[13579][26]))|30(?!-02)|31(?=-0[13578]|-1[02]))-(0[1-9]"
            //                                           "|1[0-2])-([12]\\d{3}) ([01]\\d|2[0-3]):([0-5]\\d):([0-5]\\d)$");

            std::string s;
            if (!expect_string(s, 10, 19))
            {
                return false;
            }
            // std::smatch result;
            // if (std::regex_search(str, result, datetime_pattern))
            // {
            //     return true;
            // }
            std::tm t{};
            std::istringstream ss(s);

            ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
            if (ss.fail())
            {
                ss >> std::get_time(&t, "%Y-%m-%d");
                if (ss.fail())
                {
                    printf("Invalid datetime format. Example: 2020-12-31 00:16:59\n");
                    return false;
                }
            }

            ts_out = mktime(&t);
            if (!(min_time <= ts_out && ts_out <= max_time))
            {
                printf("Invalid datetime, exceding limitation.\n");
                return false;
            }
            return true;
        }
        static bool expect_string(std::string &string_out, int min_len = 0, int max_len = 1024 * 1024)
        {
            std::getline(std::cin, string_out);
            if (min_len == max_len && string_out.size() != min_len)
            {
                string_out.clear();
                printf("Invalid input, expected length = %d\n", min_len);
                return false;
            }
            if (string_out.empty() && string_out.size() < min_len)
            {
                string_out.clear();
                printf("Invalid input, expected length >= %d\n", min_len);
                return false;
            }
            if (string_out.size() > max_len)
            {
                string_out.clear();
                printf("Invalid input, expected length <= %d\n", max_len);
                return false;
            }
            return true;
        }
        static bool expect_string_max_try(std::string &string_out, int min_len = 0, int max_len = 1024 * 1024, int max_try = 3, std::string prompt = "", std::string retry_prompt = "Retry. ")
        {
            int current_try = 0;
            while (!util::expect_string(string_out, min_len, max_len))
            {
                std::cout << retry_prompt;
                std::cout << prompt;
                current_try++;
                if (current_try == max_try)
                {
                    std::cout << "Exceding max try times.\n";
                    return false;
                }
            }
            return true;
        }
        static std::u16string int_to_u16string(size_t const &i)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::little_endian>, char16_t> conv;
            return conv.from_bytes(std::to_string(i));
        }
        static std::u16string string_to_u16string(std::string const &i)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::little_endian>, char16_t> conv;
            return conv.from_bytes(i);
        }
        static bool is_integer(const std::string &s)
        {
            static std::regex integer("(\\+|-)?[[:digit:]]+");
            return regex_match(s, integer);
        }
        static bool is_decimal(const std::string &s)
        {
            static std::regex decimal("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$");
            return regex_match(s, decimal);
        }
        template <typename T>
        static bool expect_number_max_try(T &num_out, T min_val, T max_val, int max_try = 3, std::string prompt = "", std::string retry_prompt = "Retry. ")
        {
            int current_try = 0;
            while (!util::expect_number(num_out, min_val, max_val))
            {
                current_try++;
                if (current_try == max_try)
                {
                    std::cout << "Exceding max try times.\n";
                    return false;
                }
                else
                {
                    std::cout << retry_prompt;
                    std::cout << prompt;
                }
            }
            return true;
        }
    };

}