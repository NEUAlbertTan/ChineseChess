cmake_minimum_required(VERSION 3.20)
project(ChineseChess)

set(CMAKE_CXX_STANDARD 11)

add_executable(ChineseChess main.cpp App.cpp App.h Player.cpp Player.h Game.cpp Game.h FileSys.cpp FileSys.h ChessBoard.cpp ChessBoard.h Chess.cpp Chess.h DrawerHelper.h MoveHelper.h MoveHelper.cpp SkillHelper.cpp SkillHelper.h)

set(CMAKE_EXE_LINKER_FLAGS -static)
