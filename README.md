# Status

Fortunetly broken after Half-Life 25th anniversary update (because binaries do
not export dynamic symbols now). I'm not going to fix this because:

1. I hope hl1 will get some activity again, so I don't want to flood servers
   with cheaters.
2. I don't see much fun in dealing with byte patterns and offsets.

# HlHaxLib

HlHaxLib is a linux hack for games based on goldsource engine so this can work
for many games like half-life 1, counter-strike 1.6, etc. For features list see
[src/funcs](src/funcs).

## Demo

<details>
  <summary>Screenshot (click to expand)</summary>
  <img src="https://user-images.githubusercontent.com/49063932/159180098-ed79210e-4008-4c9e-9699-12cf9bebb7c0.png" alt="demo image"/>
</details>

<details>
  <summary>Video (click to expand)</summary>

  [![hlhax demo video](https://user-images.githubusercontent.com/49063932/235757516-9b58eb42-dcb2-4f70-bb89-4ad85235338b.png)](https://github.com/UnkwUsr/hlhax/assets/49063932/4cd6f581-e49d-4a38-bf3f-7b9da7700118)

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

    Check in-game console and find line "hlhax loaded". Also you can try to
    start typing `hx_`, `cv_` or `+hx_` and a completion list should appear.

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

Special thanks to `shelru` for method of injecting library into process using
debugger, which idea I took from extramirror version for linux.

Somewhere in the code I also inserted urls to original sources, but I'm sure
that's not all.
