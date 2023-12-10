# Advent of Code Solutions

Welcome to my Advent of Code repository! Here, you'll find my solutions to the Advent of Code challenges, written in C++ (I just recently started using C++20 features) and JavaScript/TypeScript.

## Disclaimer

Please note that the code in this repository might not be the epitome of cleanliness and perfection. It wasn't in the past and probably won't be in the future, but from time to time I'll try to update my structure.

## Advent of Code

[Advent of Code](https://adventofcode.com/) is an annual coding event that features a series of daily programming challenges throughout December. It's a great opportunity to improve your coding skills and have some fun along the way.

## Repository Structure (latest one, some years aren't converted yet)

- `year/`: Contains folders for each year.
  - `day/`: Holds folders for each day's challenge.
    - `solution.cpp`: C++ solution file.
    - `input.txt`: Input file for the challenge.
    - `test1.txt`, `test2.txt`: Test input files from task description.

## Initialization Script

To quickly set up a new day's folder, you can use the initialization script. Run the following command:

`./init [year] [day]`
- year needs to be between 2015 and current year
- day needs to be be between 1 and 25
- there's also special animation for day 25
- the script will automatically download input and insert it to `input.txt`
  - in order for download to work, you need to get your AOC cookie value from the browser and add `export AOC_COOKIE=[cookie from the browser]` to the shell you are using eg. `.bashrc`, `.zshrc`, etc.

Feel free to explore the solutions, learn from them, or offer suggestions for improvement. Remember, the goal here is not just to solve the challenges but to learn and grow as a programmer.

Happy coding!
