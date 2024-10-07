#include <vector>
#include <iostream>
#include <fstream>

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

int main()
{
    std::vector<std::string> rows{readFile({"calibrations.txt"})};
    for (std::string row : rows)
    {
        std::cout << row << "\n";
    }
}

int calibrate(std::vector<std::string> &vec)
{
    int sum{0};
    for (std::string row : vec)
    {
        std::cout << row << "\n";
    }
    return 0;
}
