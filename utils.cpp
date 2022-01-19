/*
 * John Carter
 * Created: 2022/01/19 13:03:12
 * Last modified: 2022/01/19 13:43:30
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

std::vector<std::string> split(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::string token;

    // Get rid of extra whitespace
    str = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
    std::istringstream ss(str);

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}