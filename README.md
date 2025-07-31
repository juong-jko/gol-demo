# Conway's Game of Life

This project is a C++ implementation of Conway's Game of Life, a cellular automaton devised by the British mathematician John Horton Conway in 1970.

## Features

*   **Efficient Simulation:** Uses an `unordered_set` to store only live cells, making it highly efficient for sparse patterns on a virtually infinite grid.
*   **Life 1.06 Format:** Reads initial patterns from standard input using the common [Life 1.06 file format](https://www.conwaylife.com/wiki/Life_1.06).
*   **File Output:** Saves the final state of the simulation to a file (`out.txt`) in the same Life 1.06 format.
*   **Console Output:** Prints the coordinates of all live cells to the console after the simulation is complete.

## How to Build and Run

This is a standard C++ project. You can build it using any modern C++ compiler (like g++, Clang, or MSVC).

### Building with a Compiler (e.g., g++)

```bash
g++ -std=c++17 -o GameOfLife GameOfLife/main.cpp
```

### Running the Simulation

The program reads the initial state of the cells from standard input. You can pipe a file into it or paste the content directly.

**Example using a file:**

```bash
./GameOfLife < path/to/your/pattern.lif
```

**Example with manual input:**

1.  Run the executable: `./GameOfLife`
2.  Paste or type the pattern in the terminal, starting with `#Life 1.06`.
3.  Press `Ctrl+D` (on Linux/macOS) or `Ctrl+Z` then `Enter` (on Windows) to signal the end of input.

The simulation will run for a fixed number of iterations (currently hardcoded to 10) and then exit.

## Input Format

The program expects the input to follow the **Life 1.06** format.

*   The first line must be `#Life 1.06`.
*   Subsequent lines can be comments starting with `#`.
*   Each non-comment line should contain two space-separated integers representing the `x` and `y` coordinates of a live cell.

**Example Input (`glider.lif`):**

```
#Life 1.06
#N Glider
#O John Conway
#C A simple glider pattern.
1 0
2 1
0 2
1 2
2 2
```

## Output Format

### Console Output

After the simulation finishes, the coordinates of all live cells in the final generation will be printed to the standard output, one cell per line.

**Example Console Output:**

```
(11, 10)
(12, 11)
(10, 12)
(11, 12)
(12, 12)
```

### File Output

The final generation is also saved to `out.txt` in the Life 1.06 format, which can be used as input for future simulations.

**Example `out.txt`:**

```
#Life 1.06
11 10
12 11
10 12
11 12
12 12
```
