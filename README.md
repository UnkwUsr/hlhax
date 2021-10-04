# HlHaxLib
HlHaxLib is a linux hack for games based on goldsource engine so this can work for many games aka half-life 1, counter-strike 1.6, etc.

# How to startup
1. Clone this repo.
2. Download SDK:
```
mkdir sdk
git clone https://github.com/ValveSoftware/halflife.git sdk/halflife-master
```
3. Prepare build folder:
```
mkdir build
cd build
cmake ..
```
4. Start hl1 (preferably from terminal).
5. Inject hax (be sure you are in build folder):
```
./inject_tool.sh load
```
