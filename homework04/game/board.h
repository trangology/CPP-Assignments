#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>


struct location_t{
    int x, y;

    location_t() : x{0}, y{0} {};

    location_t(int x, int y) : x{x}, y{y} {};
};


const int DIRECTIONS[][4] {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};


typedef std::vector<location_t> move_list_t;
typedef std::vector<move_list_t> jumps_list_t ;


struct piece_t
{
    char side;          // W -> WHITE, B -> BLACK, * -> NULL
    char kind;          // M -> MAN, K -> KING, E -> EMPTY
    location_t location;

    piece_t() : side{ '*' }, kind{ 'E' }, location{ location_t() } {};

    piece_t(char side, char kind, location_t location) :
            side{ side }, kind{ kind }, location{ location } {};
};


class board_t
{
public:
    piece_t board[8][8];

    board_t();

    void display_board();

    void show_all_kings();

    void make_empty(location_t location);

    void update_piece(const location_t start_moves, const location_t end_moves, char side);

    bool is_king(const location_t location);

    bool is_legal_location(const location_t location);

    char get_side(const location_t location);

    char get_opponent_side(const location_t location);

    int apply_moves(const move_list_t& moves);

    jumps_list_t get_possible_moves(const location_t location);

    jumps_list_t get_possible_jumps(const location_t location);

    move_list_t get_possible_pieces(const int turn);

    move_list_t get_slide(const location_t location, const location_t tmp);

private:
    bool is_man(const location_t location);

    bool is_empty(const location_t location);

    bool is_become_king(const location_t location, char side);

    bool is_opponent(const location_t location, const location_t tmp);

    bool is_out_of_board(const location_t location);

    bool is_possible_to_jump(const location_t location);

    move_list_t check_man_jump(const move_list_t& jumps, const int index);

    move_list_t check_king_jump(const move_list_t& jumps, const int index);

    jumps_list_t get_man_jumps(move_list_t& jumps, jumps_list_t& jumps_list);

    jumps_list_t get_king_jumps(move_list_t& jumps, jumps_list_t& jumps_list);

    jumps_list_t get_king_moves(const location_t location);

    jumps_list_t get_man_moves(const location_t location);
};
