# QtMines

The attempt of this project is to try to recreate a WindowsXP Minesweeper game in C++ Qt5.

![image](https://github.com/kubakubakuba/QtMines/assets/13603688/c281cbd4-f161-4347-92fb-525f60a3c105)

### Controls
- Left click to reveal the mine, right click to place or remove a flag. If all flags are placed on the correct mines and all other places are revealed, the game is won.
If a mine in revealed instead, the game is lost.
- The game can be restarted at any time by pressing the smiley face icon in the middle of the screen.
- The left 7-segment indicator shows, how much flags has the player left to place, the right one shows the time elapsed from the start of the last round.
- The difficulty can by changed by selecting the option in the top menu (player can also set their own difficulty).

## Online demo in WebAssembly

The project has been compiled into an WebAssembly, which is located [here](http://vps.swpelc.eu/ctu/minesweeper/).
- Note (1): the resizing does not work for some reason on the web, you may need to change the difficulty to fix it.
- ~~Note (2): the custom difficulty currently does not work on the web (for some reason :/)~~ (fixed)

### User interface

![image](https://github.com/kubakubakuba/QtMines/assets/13603688/3c38b27e-fe7a-4c66-8767-35bd548c2a4c)
![image](https://github.com/kubakubakuba/QtMines/assets/13603688/4980d425-e451-4177-944f-26dab4f69dff)

### Compiling
Compile in the usual way by running `qmake` and `make`.
To compile into web assembly, emscripten (`em++` compiler) is needed, as well as the Qt5 Creator WebAssembly addon (quite tedious installation). The compiled WebAssembly version can be found in the [releases](https://github.com/kubakubakuba/QtMines/releases) tab.

## Sources
Assets were obtained from [here](https://github.com/ShizukuIchi/minesweeper/tree/master).

#### by Jakub Pelc for B2B99PPC semestral work
