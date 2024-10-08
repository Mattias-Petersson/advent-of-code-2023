#include <vector>
#include <fstream>
#include <iostream>
#include <map>

std::vector<std::string> readFile(std::string_view fileName)
{
    std::vector<std::string> rows{};
    std::ifstream file(fileName.data());
    std::string element;
    while (file >> element)
    {
        rows.push_back(element);
    }
    return rows;
}

const std::map<std::string, int> numText{
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}};

/**
 * Concatenates the first and last integer values of a given string. If the
 * string contains no integer, return 0.
 */
int rowAddFirstLast(std::string &str)
{
    std::map<int, int> digits{};

    for (auto &textAndValue : numText)
    {
        int pos = str.find(textAndValue.first);
        while (pos != std::string::npos)
        {
            digits[pos] = textAndValue.second;
            pos = str.find(textAndValue.first, ++pos);
        }
    }
    for (int i = 0; i < str.length(); i++)
    {
        char &current = str.at(i);
        if (isdigit(current))
        {
            digits[i] = current - '0';
        }
    }
    for (auto &t : digits)
    {
        std::cout << "First: " << t.first << " Second: " << t.second << "\n";
    }
    return digits.size() != 0 ? digits.begin()->second * 10 + std::prev(digits.end())->second : 0;
}

int calibrate(std::vector<std::string> &vec)
{
    int sum{0};
    for (std::string &row : vec)
    {
        sum += rowAddFirstLast(row);
    }
    return sum;
}

int main()
{
    std::vector<std::string> rows{readFile({"calibrations.txt"})};
    int res{calibrate(rows)};
    std::cout << res;
}
