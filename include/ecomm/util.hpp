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
        template <typename T>
        static bool expect_number_max_try(T &num_out, T min_val, T max_val, int max_try, std::string prompt = "")
        {
            int current_try = 0;
            while (!util::expect_number(num_out, min_val, max_val))
            {
                std::cout << "Retry. ";
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
    };

}