#pragma once

#include <string>

#include "computer_interface.h"

class first_computer_strategy_t : public computer_interface_t {
public:
    explicit first_computer_strategy_t(std::string name);

    move_list_t get_moves(board_t &board) override;
    move_list_t apply_strategy(board_t& board, const jumps_list_t & moves) override;

    void print_stat() const override;

private:
    std::string name;
};