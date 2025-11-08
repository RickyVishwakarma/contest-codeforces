# contest-codeforces

Collection of Codeforces problem solutions (mostly C++). Organized by rounds and individual problem files.

## Repository layout

- `gameOnarray.cpp`, `incermentalSubarray.cpp`, `primeGaming.cpp`, ... — standalone C++ solutions in the root.
- `educationalRound182/`, `pinelyRound/`, `Round1049/`, `round1052/`, ... — folders for round-specific solutions. Each folder contains individual problem source files (usually `.cpp`).

## How to compile and run (Windows PowerShell)

Most files are single-file C++ solutions (no external dependencies). Examples below assume you have a C++ compiler installed (g++ from MinGW/MSYS2, or Visual Studio `cl`).

Using g++ (MinGW / MSYS2 / WSL):

```powershell
# compile
g++ -std=c++17 -O2 -pipe path\to\solution.cpp -o solution.exe

# run with optional input redirection
.\solution.exe < input.txt
```

Using Microsoft Visual C++ (Developer Command Prompt / proper environment):

```powershell
# compile (from Developer Command Prompt where cl is available)
cl /std:c++17 /O2 path\to\solution.cpp /Fe:solution.exe

# run
.\solution.exe < input.txt
```

Notes:
- Replace `path\to\solution.cpp` with the actual file path (for example `round1056\sol3.cpp`).
- If you use WSL, build/run commands are the same as on Linux (use `g++` in WSL shell).

## Suggested workflow

1. Open the folder in VS Code.
2. Edit or choose a solution file (for example `round1056/sol3.cpp`).
3. Compile via the integrated terminal using the commands above.
4. Run with sample input using `.\solution.exe < sample_input.txt`.

## Contributing

- Add small, well-tested changes. Name new files clearly (e.g., `roundXXXX/solY.cpp`).
- Keep solutions focused and single-file where possible.

## Contact

If you want improvements or have questions, create an issue or contact the repository owner.
