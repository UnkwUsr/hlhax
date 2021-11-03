# HlHaxLib
HlHaxLib is a linux hack for games based on goldsource engine so this can work
for many games aka half-life 1, counter-strike 1.6, etc. For features list check
[src/funcs](src/funcs).

## Startup
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

## Goals (aka sweet dreams)
Autostrafe functions. That's all. Really, I very love cs 1.6 kz hacks like Tkz
or 101xD. They literally allow you to gain such speed that the player begins to
fly up on uneven surfaces.

Firstly I want to see it in half-life, and then make it *cross-mod*, to work in cs 1.6.

## Credits
Many thanks to all games hacking community, this is a really big scene. Mostly
it's a site [www.unknowncheats.me](https://www.unknowncheats.me), but also I've seen some archived
forum pages of [www.gamedeception.net](https://www.gamedeception.net).

Also thanks to russian forum [pvpru.com](https://pvpru.com). A long time ago there was many good persons who
write stuff and share code/instructions about counter-strike 1.6 .

Special thanks to `shelru` for his method of injecting library into process
using debugger (I found this method from his released extramirror version for
linux, but after he deleted all stuff related to linux version, so I can't even
see on it anymore, lol).

And, somewhere in the code I also inserted urls to original sources, but I'm
sure that's not all.
