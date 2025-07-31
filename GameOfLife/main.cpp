#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct CustomHashFunc;

using Coord = __int64;
using Cell = pair<Coord, Coord>;
using Collection = unordered_set<Cell, CustomHashFunc>;

// TODO: Read from input
constexpr int NIterations = 10;

struct CustomHashFunc {
    size_t operator()(const Cell& cell) const {
        return hash<Coord>{}(cell.first) ^ (hash<Coord>{}(cell.second) << 1);
    }
};

void PrintAllAliveCells(const Collection& aliveCells) {
    for (const auto& cell : aliveCells)
    {
        cout << "(" << cell.first <<  ", " << cell.second << ")" << endl;
    }
}

// Output current generation to Life 1.06 format
void WriteToFile(const Collection& aliveCells) {
    ofstream outputFile("out.txt");
    if (!outputFile.is_open())
        cerr << "Error: unable to open file." << endl;

    outputFile << "#Life 1.06" << endl;
    for (const auto& cell : aliveCells) {
        outputFile << cell.first << " " << cell.second << endl;
    }

    outputFile.close();
}

void Simulate(Collection& aliveCells) {
    Collection interestingCells;

    // First pass to gather all cells we care about
    for (const auto& cell : aliveCells) {
        for (Coord dx = -1; dx <= 1; ++dx) {
            for (Coord dy = -1; dy <= 1; ++dy) {
                interestingCells.emplace(cell.first + dx, cell.second + dy);
            }
        }
    }

    // Iterate next gen
    Collection nextGen;
    for (const auto& cell : interestingCells) {
        Coord x = cell.first;
        Coord y = cell.second;
        
        int aliveCount = 0;
        for (Coord dx = -1; dx <= 1; ++dx) {
            for (Coord dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;

                if (aliveCells.contains(Cell(x + dx, y + dy))) {
                    aliveCount++;
                }
            }
        }

        bool isAlive = aliveCells.contains(cell) > 0;
        if (isAlive && (aliveCount == 2 || aliveCount == 3)) {
            nextGen.insert(cell);
        }
        else if (!isAlive && aliveCount == 3) {
            nextGen.insert(cell);
        }
    }

    swap(aliveCells, nextGen);
}

int main() {
    string line;
    Collection liveCells;

    // Get first line to determine format
     getline(cin, line);
     if (line != "#Life 1.06") {
         cerr << "Error: Invalid format declaration" << endl;
         return 1;
     }

    while (getline(cin, line)) {
        if (line.empty())
            continue;

        // handle comments
        if (line.front() == '#')
            continue;
        
        stringstream ss(line);
        Coord x, y;
        if (ss >> x >> y) {
            auto ret = liveCells.emplace(x, y);
            auto newCell = ret.first;
        }
    }

    for (int i = 0; i < NIterations; ++i) {
        Simulate(liveCells);
    }
    
    PrintAllAliveCells(liveCells);
    WriteToFile(liveCells);
}
