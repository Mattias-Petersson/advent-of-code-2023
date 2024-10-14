#include <regex>
#include "../utils/readFile.cpp"
#include <sstream>
#include <map>
#include <numeric>
#include <chrono>

int getIdx(const std::string &sessionString)
{
    std::regex findIdxFilter("Game (\\d+)");
    std::smatch sm;
    std::regex_search(sessionString, sm, findIdxFilter);
    return std::stoi(sm[1]);
}

struct Game
{
    int redCubes{};
    int greenCubes{};
    int blueCubes{};
    Game(int red, int green, int blue) : redCubes{red}, greenCubes{green}, blueCubes{blue}
    {
    }
    bool canBePlayed(const Game &otherGame) const
    {
        return otherGame.redCubes >= redCubes && otherGame.greenCubes >= greenCubes && otherGame.blueCubes >= blueCubes;
    }
};

Game makeGame(std::string &gameString)
{
    std::unordered_map<std::string, int> m;
    std::istringstream stream(gameString);
    std::string color;
    int num;
    while (stream >> num >> color)
    {
        m[color] = num;
    }
    return Game(m["red"], m["green"], m["blue"]);
}

std::vector<Game> getGames(const std::string &sessionString)
{
    std::vector<Game> games{};
    size_t delimiter{sessionString.find(":")};
    std::string modifiedString = std::regex_replace(sessionString, std::regex(","), ""); // Remove commas to make a clean map entry.
    int skip = 2;                                                                        // "Remove the symbol and the space after it, i.e. "; ".
    while (delimiter != std::string::npos)
    {
        delimiter += skip;
        size_t oldIndex{delimiter};
        delimiter = modifiedString.find(";", delimiter);
        std::string partGame{modifiedString.substr(oldIndex, delimiter - oldIndex)};
        games.push_back(makeGame(partGame));
    }
    return games;
}

int idxIfPossible(const std::string &sessionString, const Game &compareGame)
{
    std::vector<Game> games = getGames(sessionString);
    if (std::all_of(games.begin(), games.end(), [&](const Game &g)
                    { return g.canBePlayed(compareGame); }))
    {
        return getIdx(sessionString);
    }
    return 0; // We do not need the index if all games are not possible, return 0.
}

int prodOfLeast(const std::string &sessionString)
{
    std::vector<Game> games = getGames(sessionString);
    std::unordered_map<std::string, int> largest{
        {"red", 0}, {"green", 0}, {"blue", 0}};
    for (const auto &game : games)
    {
        largest["red"] = std::max(largest["red"], game.redCubes);
        largest["green"] = std::max(largest["green"], game.greenCubes);
        largest["blue"] = std::max(largest["blue"], game.blueCubes);
    }
    return largest["red"] * largest["green"] * largest["blue"];
}

void partOne(const std::vector<std::string> &rows)
{
    Game gameToCompare(12, 13, 14);
    int sum = std::accumulate(rows.begin(), rows.end(), 0, [&](int old, const std::string &row)
                              { return old + idxIfPossible(row, gameToCompare); });

    std::cout << "The sum of the index of all possible games is " << sum << "\n";
}

void partTwo(const std::vector<std::string> &rows)
{
    int sum = std::accumulate(rows.begin(), rows.end(), 0, [](int old, const std::string &row)
                              { return old + prodOfLeast(row); });

    std::cout << "The sum of the power of all sets is " << sum << "\n";
}

int main()
{
    std::vector<std::string> rows{readFile({"games.txt"})};
    partOne(rows);
    partTwo(rows);
    return 0;
}
