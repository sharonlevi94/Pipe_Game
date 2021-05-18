#pragma once
//general:
constexpr auto SQUARE_LEN = 128;
constexpr auto START_SIZE = 5;
constexpr auto HEIGHT = 900;
constexpr auto WIDTH = 1200;

//music:
constexpr auto MUSIC_VOLUME = 50;
constexpr auto MUSIC_PATH = "Music.ogg";

//paths:
constexpr auto BOARD_PATH = "Board.txt";
constexpr auto BACKGROUND_PATH = "Background.png";
constexpr auto LEVEL1_BACKGROUND_PATH = "level1.jpeg";
constexpr auto LEVEL2_BACKGROUND_PATH = "level2.png";
constexpr auto LEVEL3_BACKGROUND_PATH = "level3.jpeg";
constexpr auto GAME_LOGO_PATH = "Logo.png";

//textures:
constexpr auto BACKGROUND = 1;
constexpr auto LEVEL_BACKGROUND = 2;
constexpr auto GAME_LOGO = 3;
constexpr auto SQUARE = 4;

//objects:
constexpr auto STRAIGHT_PIPE = '-';
constexpr auto CORNER_PIPE = 'L';
constexpr auto PLUS_PIPE = '+';
constexpr auto T_PIPE = 'T';
constexpr auto SINK = 'S';
constexpr auto FAUCET = 'F';