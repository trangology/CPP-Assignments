project(game)

set(SOURCES
		game.cpp board.cpp)

set(HEADERS
		game.h board.h)

include_directories(../)

add_library(game ${SOURCES} ${HEADERS})