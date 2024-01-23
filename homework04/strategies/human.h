#pragma once

#include "interface.h"

class human_strategy_t : public strategy_interface_t {
public:
    human_strategy_t() = default;

    move_list_t get_moves(board_t &board) override;

    void on_win() override;
    void on_lose() override;
    void on_draw() override;
};