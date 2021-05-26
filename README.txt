1/OOP 2 ex. 4- PIPE:
//----------------------------------------------------------------------------
Creators:
a- Sharon Levi
b- Bar Ifrah
//----------------------------------------------------------------------------
General ideas and goals of the project:
This is a puzzle game. you get a 6*6 map of pipes, faucet and a sink.
map size is changeable in macros file.
this is an infinite game. Every time you fill up the sink with water,
you get a fresh, random level.
The goal is to fill the sink with water, with as less clicks as possible, and in the fastest time.
when a pipe is filled with water, it turns blue.
We kept the game similar to the original, by making clockwise rotation available only.
The game boars is random, but with a bfs manipulation every level is solvable.
water fills up with backtracking recursion.

//----------------------------------------------------------------------------
4. Files: General: CMakeLists.txt- cmake of the project.
Source files: -CMakeLists.txt - Cmake file to all src files.

main -Menu.cpp - class that redirects all commands.



Headers:
-CMakeLists.txt - To all headers
//----------------------------------------------------------------------------
5. Data structures :
Vectors - smart pointer vectors to hold objects in the game and the neighbours lists.
//----------------------------------------------------------------------------
6. Algorithms that are worth mentioning:
 backtracking, bfs like to fill water.

//----------------------------------------------------------------------------
7. Known bugs:
//----------------------------------------------------------------------------
8. Other notes: