#pragma once

#include "../game/board.h"

class strategy_interface_t {
public:
    virtual move_list_t get_moves(board_t& board) = 0;

    virtual void on_lose() = 0;
    virtual void on_win() = 0;
    virtual void on_draw() = 0;
};

