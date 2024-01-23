#include "human.h"

#include <iostream>

void human_strategy_t::on_win() {
    std::cout << "You win!" << std::endl;
}

void human_strategy_t::on_lose() {
    std::cout << "You lose!" << std::endl;
}

void human_strategy_t::on_draw() {
    std::cout << "Draw!" << std::endl;
}

move_list_t human_strategy_t::get_moves(board_t& board) {
    std::cout << "Computer has just moved with white side.\n" << std::endl;
    board.show_all_kings();

    move_list_t input = {};
    int n;
    int x, y;
    std::cout << "Enter number of locations of your move (or sequence of jumps):";
    std::cin >> n;

    std::cout << "\nNow, enter all locations started from your location of piece you want to move:" << std::endl;

    for (int i = 0; i < n; i++)
    {
        std::cin >> x >> y;
        auto location = location_t(x - 1 , y - 1);
        input.push_back(location);
    }

    return input;
}