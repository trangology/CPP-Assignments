project(strategies)
set(SOURCES
		human.cpp
		computer_1.cpp
		computer_2.cpp
		computer_interface.cpp)

set(HEADERS
		human.h
		computer_1.h
		computer_2.h
		interface.h
		computer_interface.h)

include_directories(../)

add_library(strategies ${SOURCES} ${HEADERS})
