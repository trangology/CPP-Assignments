#include "game.h"

game_t::game_t(const player_t &first, const player_t &second) : board()
{
  players.push_back(first);
  players.push_back(second);
}

game_t::game_result_t game_t::game_state(std::map<char, int>& captures, const int turn)
{
    if (captures['W'] == 12 || captures['B'] == 12)
        return LOSE;

    auto pieces = board.get_possible_pieces(turn);

    if (pieces.empty())
        return LOSE;

    // TODO: DRAW conditions
    // if (/* some conditions */) {
    // return DRAW;
    // }

    return IN_PROGRESS;
}


void game_t::play() {
    captures['W'] = 0;
    captures['B'] = 0;

    size_t turn = 0;
    while (game_state(captures, turn) == IN_PROGRESS)
    {
        auto moves = players[turn]->get_moves(board);
        auto opponent_side = board.get_opponent_side(moves[0]);
        auto counter = board.apply_moves(moves);

        captures[opponent_side] += counter;
        turn = (turn + 1) % 2;
    }

    if (game_state(captures, turn) == DRAW) {
        for (const auto &p : players) {
            p->on_draw();
        }
        return;
    }

    for (size_t i = 0; i < players.size(); ++i) {
        if (i == turn) {
            players[i]->on_lose();
        } else {
            players[i]->on_win();
        }
    }
}