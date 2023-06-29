# QtMines

The attempt of this project is to try to recreate a WindowsXP Minesweeper game in C++ Qt5.

![image](https://github.com/kubakubakuba/QtMines/assets/13603688/1b314aed-577c-4bc9-8d2b-003fae8d0211)

### Controls
- Left click to reveal the mine, right click to place or remove a flag. If all flags are placed on the correct mines, the whole board is revealed.
If a mine in revealed instead, the game is lost.
- The game can be restarted at any time by pressing the smiley face icon in the middle of the screen.
- The left 7-segment indicator shows, how much flags has the player left to place, the right one shows the time elapsed from the start of the last round.
- The difficulty can by changed by selecting the option in the top menu (player can also set their own difficulty).

## Online demo in WebAssembly

The project has been compiled into an WebAssembly, which is located [here](http://vps.swpelc.eu/ctu/minesweeper/).
- Note (1): the resizing does not work for some reason on the web, you may need to change the difficulty from hard to easy to fix it.
- Note (2): the custom difficulty currently does not work on the web (for some reason :/)

### Compiling
Compile in the usual way by running `qmake` and `make`.

## Sources
Assets were obtained from [here](https://github.com/ShizukuIchi/minesweeper/tree/master).

#### by Jakub Pelc for PPC semestral work
