# ncui_demo
Demo for the NerveCentre UI framework [jaddison06/nervecentre](https://github.com/jaddison06/nervecentre)

## Building
Only ever built this on Linux, should be portable so uhhhh good luck

- Python, Make, GCC required (use Cgywin on windows for latter two)
- SDL2-dev and SDL2-ttf-dev must be installed
- GCC & python executables must be correct in `build/generate_makefile.py` lines 9-10
- System names for SDL libraries must also be entered in `LIBS` (line 11, darwin=macos), already done for linux but not sure about other OS's, will probably (?) be the same
- Once set up, run the Python script from root dir, then `make run`