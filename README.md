# HlHaxLib
HlHaxLib is a hack for games based on goldsource engine so this can work for many games aka half-life 1, counter-strke 1.6, etc.

# How to startup
1. Clone this repo.
2. Download sdk:  
`mkdir sdk`  
`cd sdk`  
`git clone https://github.com/ValveSoftware/halflife.git halflife-master`  
`cd ..`  
3. Build project:  
`mkdir build`  
`cp inject_tool.sh build`  
`cd build`  
`cmake ..`  
`make`  
4. Start hl1 (preferably from terminal).
5. Inject hax:  
`./inject_tool.sh load`  
