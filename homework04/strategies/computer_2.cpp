#include "computer_2.h"

#include <iostream>
#include <random>


second_computer_strategy_t::second_computer_strategy_t(std::string name) : name(std::move(name)) {}


move_list_t second_computer_strategy_t::get_moves(board_t& board) {
    // by the rule, if there are any jump (or sequence of jumps)
    // we need to find possible jumps before find a non-jumping move
    jumps_list_t jumps_list = {};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
        {
            auto loc = location_t{i, j};
            if (board.get_side(loc) == 'B')
            {
                auto jumps = board.get_possible_jumps(loc);
                if (!jumps.empty())
                {
                    for (const auto& jump : jumps) {
                        jumps_list.push_back(jump);
                    }
                    return apply_strategy(board, jumps_list);
                }
            }
        }
    }

    // if there are no jumps, we will find a non-jumping move
    jumps_list_t moves_list = {};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
        {
            auto loc = location_t{i, j};
            if (board.get_side(loc) == 'B')
            {
                auto moves = board.get_possible_moves(loc);
                if (!moves.empty())
                {
                    for (auto move : moves) {
                        moves_list.push_back(move);
                    }
                    return apply_strategy(board, moves_list);
                }
            }
        }
    }
}


move_list_t second_computer_strategy_t::apply_strategy(board_t& board, const jumps_list_t& jumps_list) {
    std::cout << "First computer has just moved with white side.\n" << std::endl;
    if (jumps_list.empty()) {
        return move_list_t( {} );
    }

    return jumps_list.back();
}


void second_computer_strategy_t::print_stat() const {
    std::cout << "Random model [" << name << "]: " << std::endl;
    computer_interface_t::print_stat();
}