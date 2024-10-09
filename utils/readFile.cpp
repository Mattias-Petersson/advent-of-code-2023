#include <vector>
#include <fstream>
#include <iostream>

#ifndef READ_FILE
#define READ_FILE

/**
 * Read in from a file, delimiter as linebreak.
 */
std::vector<std::string> readFile(std::string_view fileName)
{
    std::vector<std::string> rows{};
    std::ifstream file(fileName.data());
    std::string line;
    while (std::getline(file, line))
    {
        rows.push_back(line);
    }
    return rows;
}
#endif
