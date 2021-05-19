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
constexpr auto GAME_LOGO_PATH = "Logo.png";
constexpr auto STRAIGHT_PIPE_PATH = "straight_pipe";
constexpr auto T_PIPE_PATH = "t_pipe";
constexpr auto CORNER_PIPE_PATH = "corner_pipe.png";
constexpr auto PLUS_PIPE_PATH = "plus_pipe";
constexpr auto SINK_PIPE_PATH = "";
constexpr auto FAUCET_PIPE_PATH = "";


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