# ncui_demo
Demo for the NerveCentre UI framework

## Building
Only ever built this on Linux, should be portable so uhhhh good luck

- Python, Make, GCC required (use Cgywin on windows for latter two)
- SDL2-dev and SDL2-ttf-dev must be installed
- GCC & python executables must be correct in `build/generate_makefile.py`
- Paths to SDL libraries must also be entered in `LIBS` (darwin=macos), already done for linux but not sure about other OS's
- Once set up, run the Python script from root dir, then `make run`