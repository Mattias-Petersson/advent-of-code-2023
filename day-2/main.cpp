#include <regex>
#include "../utils/readFile.cpp"
#include <sstream>
#include <map>

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
    std::map<std::string, int> m;
    gameString = std::regex_replace(gameString, std::regex(","), ""); // Remove commas to make a clean map entry.
    std::istringstream stream(gameString);
    std::string color;
    int num;
    while (stream >> num >> color)
    {
        m[color] = num;
    }
    return Game(m["red"], m["green"], m["blue"]);
}

int idxIfPossible(const std::string &sessionString, const Game &compareGame)
{
    auto delimiter{sessionString.find(":")};
    int skip = 2; // "Remove the symbol and the space after it, i.e. "; ".
    while (delimiter != std::string::npos)
    {
        delimiter += skip;
        auto oldIndex = delimiter;
        delimiter = sessionString.find(";", delimiter);
        std::string partGame = sessionString.substr(oldIndex, delimiter - oldIndex);
        Game game = makeGame(partGame);
        if (!game.canBePlayed(compareGame))
        {
            return 0;
        }
    }
    return getIdx(sessionString);
}

int main()
{
    std::vector<std::string> rows{readFile({"games.txt"})};
    Game gameToCompare(12, 13, 14);
    int sum{};
    for (auto &row : rows)
    {
        sum += idxIfPossible(row, gameToCompare);
    }
    std::cout << "The sum of the index of all possible games is " << sum << "\n";
    return 0;
}
