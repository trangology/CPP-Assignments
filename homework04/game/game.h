#pragma once

#include <memory>
#include <vector>

#include "../strategies/interface.h"

class game_t {
public:
    using player_t = std::shared_ptr<strategy_interface_t>;
    game_t(const player_t &first, const player_t &second);

    void play();

private:
    enum game_result_t {
        LOSE,
        DRAW,
        IN_PROGRESS
    };

    std::map<char, int> captures;

    board_t board;

    game_result_t game_state(std::map<char, int>& captures, int turn);

    std::vector<player_t> players;
};