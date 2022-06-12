# HlHaxLib

HlHaxLib is a linux hack for games based on goldsource engine so this can work
for many games aka half-life 1, counter-strike 1.6, etc. For features list
check [src/funcs](src/funcs).

## Demo

<details>
  <summary>Screenshot (click to expand)</summary>
  <img src="https://user-images.githubusercontent.com/49063932/159180098-ed79210e-4008-4c9e-9699-12cf9bebb7c0.png" alt="demo image"/>
</details>

<details>
  <summary>Video (click to expand)</summary>

  [![hlhax demo video](https://img.youtube.com/vi/Qv62MQEc2wM/0.jpg)](https://www.youtube.com/watch?v=Qv62MQEc2wM "hlhax aimbot demo")

</details>

## Startup

1. Clone this repo.
2. Download SDK:

    ```bash
     mkdir sdk
     git clone https://github.com/ValveSoftware/halflife.git sdk/halflife-master
    ```

3. Prepare build folder:

    ```bash
     mkdir build
     cd build
     cmake ..
    ```

4. Actually build:

    ```bash
     make
    ```

5. Start hl1 (preferably from terminal).
6. Inject hax (be sure you are in build folder):

    ```bash
     ./injector.sh load
    ```

    P.S. injector runs `make` every time, so don't worry about modifying
    sources.

7. Make sure hax loaded fine.

    Check in-game console and find line "Hack loaded FINE". Also you can try to
    start typing `hx_` or `cv_` and a completion list should appear.

## Goals (aka sweet dreams)

Autostrafe functions. Really, I very love cs 1.6 kz hacks like Tkz or 101xD.
They literally allow you to gain such speed that the player begins to fly up on
uneven surfaces.

Firstly I want to see it in half-life, and then make it *cross-mod*, to work in
cs 1.6.

## Credits

Many thanks to all game hacking communities, this is a really big scene. Mostly
it's a site [www.unknowncheats.me](https://www.unknowncheats.me), but also I've
seen some archived forum pages of
[www.gamedeception.net](https://www.gamedeception.net).

Also thanks to russian forum [pvpru.com](https://pvpru.com). A long time ago
there was many good persons who write stuff and share code/instructions about
counter-strike 1.6 .

Unknown Russian site with a lot of useful information about hacks in cs 1.6:
<http://troll-homepage.narod.ru/>

Special thanks to `shelru` for his method of injecting library into process
using debugger (I found this method from his released extramirror version for
linux, but then he deleted all stuff related to linux version, so I can't even
see on it anymore, lol).

And, somewhere in the code I also inserted urls to original sources, but I'm
sure that's not all.
