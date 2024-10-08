#include <vector>
#include <fstream>
#include <deque>
#include <iostream>

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

/**
 * Concatenates the first and last integer values of a given string. If the
 * string contains no integer, return 0.
 */
int rowAddFirstLast(std::string &str)
{
    std::deque<int> digits{};
    for (int i = 0; i < str.length(); i++)
    {
        char current = str.at(i);
        if (isdigit(current))
        {
            digits.push_back(current - '0'); // Gets the integer value of the given digit.
        }
    }

    return digits.size() != 0 ? digits.front() * 10 + digits.back() : 0;
}

int calibrate(std::vector<std::string> &vec)
{
    int sum{0};
    for (std::string row : vec)
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
