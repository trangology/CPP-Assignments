#include "board.h"


board_t::board_t()
{
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++)
        {
            if (row < 3 && (row + col) % 2)
            {
                piece_t piece('B', 'M', {row, col});
                board[row][col] = piece;
            }
            else if (row > 4 && (row + col) % 2)
            {
                piece_t piece('W', 'M', {row, col});
                board[row][col] = piece;
            } else
            {
                piece_t piece('*', 'E', {row, col});
                board[row][col] = piece;
            }
        }
    }
}


void board_t::display_board()
{
    for (auto & row : board) {
        for (auto & piece : row) {
            std::cout << piece.side;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void board_t::show_all_kings()
{
    std::vector<location_t> kings_loc = {};

    for (auto & row : board) {
        for (auto & piece : row)
        {
            if (is_king(piece.location)) {
                kings_loc.push_back(piece.location);
            }
        }
    }

    if (!kings_loc.empty())
    {
        std::cout << "You currently have " << kings_loc.size() << " king/kings. Here is the list of them: ";
        for (auto loc : kings_loc) {
            std::cout << "(" << loc.x << " " << loc.y << ") ";
        }
        std::cout << std::endl;
    }
}


bool board_t::is_king(const location_t location) {
    return board[location.x][location.y].kind == 'K';
}


bool board_t::is_man(const location_t location) {
    return board[location.x][location.y].kind == 'M';
}


bool board_t::is_empty(const location_t location) {
    return board[location.x][location.y].kind == 'E';
}


bool board_t::is_become_king(const location_t location, const char side) {
    return side == 'W' && location.x == 0 || side == 'B' && location.x == 7;
}


bool board_t::is_out_of_board(const location_t location) {
    return location.x < 0 || location.x > 7 || location.y < 0 || location.y > 7;
}


bool board_t::is_possible_to_jump(const location_t location) {
    return (is_empty(location) && !is_out_of_board(location));
}


bool board_t::is_opponent(const location_t location, location_t tmp)
{
    if (is_empty(tmp)) {
        return false;
    }

    return board[location.x][location.y].side != board[tmp.x][tmp.y].side;
}


bool board_t::is_legal_location(const location_t location)
{
    if (is_empty(location)) {
        std::cout << "Please choose another piece which corresponds to your side!" << std::endl;
    }

    if (is_out_of_board(location)) {
        std::cout << "This location is out of board!"<< std::endl;
    };

    // TODO: return false if location is not associated with side of player

    return true;
}


// checks if jump is already existed in jumps
bool is_existed(move_list_t& jump, move_list_t& jumps)
{
    for (auto j : jump) {
        for (auto _j : jumps) {
            if (j.x == _j.x && j.y == _j.y) {
                return true;
            }
        }
    }

    return false;
}


char board_t::get_side(const location_t location)
{
    return board[location.x][location.y].side;
}


char board_t::get_opponent_side(const location_t location)
{
    if (is_empty(location)) {
        std::cout << "This location is empty!" << std::endl;
    }

    auto cur_side = board[location.x][location.y].side;
    if (cur_side == 'W') {
        return 'B';
    }

    return 'W';
}


move_list_t board_t::get_slide(const location_t location, const location_t tmp)
{
    move_list_t slide = { location };
    auto new_location = location_t(location.x + tmp.x, location.y + tmp.y);

    while (!is_out_of_board(new_location))
    {
        if (get_side(location) == get_side(new_location)) {
            break;
        }
        slide.push_back(new_location);
        new_location = location_t(new_location.x + tmp.x, new_location.y + tmp.y);
    }

    return slide;
}


move_list_t board_t::check_king_jump(const move_list_t& jumps, const int index)
{
    auto dir = location_t{ DIRECTIONS[index][0], DIRECTIONS[index][1] };
    auto slide = get_slide(jumps.back(), dir);

    for (int i = 0; i < slide.size() - 1; i++) {
        if (is_opponent(jumps.front(), slide[i]) && is_empty(slide[i+1])) {
            return { slide[i], slide[i+1] };
        }
    }

    return {};
}


jumps_list_t board_t::get_king_jumps(move_list_t& jumps, jumps_list_t& jumps_list)
{
    if (jumps.empty()) {
        return jumps_list;
    }

    for (int i = 0; i < 4; i++)
    {
        auto jump = check_king_jump(jumps, i);
        if (i == 3 && jump.empty())
        {
            if (jumps.size() == 1) {
                jumps.pop_back();
            } else
            {
                jumps_list.push_back(jumps);
                jumps.pop_back();
                jumps.pop_back();
            }
        }
        else if (!jump.empty() && !is_existed(jump, jumps))
        {
            jumps.push_back(jump[0]);
            jumps.push_back(jump[1]);

            return get_king_jumps(jumps, jumps_list);
        }
    }

    return jumps_list;
}


move_list_t board_t::check_man_jump(const move_list_t& jumps, const int index)
{
    auto new_location = jumps.back();
    auto adjacent_loc = location_t(new_location.x + DIRECTIONS[index][0], new_location.y + DIRECTIONS[index][1]);
    auto jump = location_t(adjacent_loc.x + DIRECTIONS[index][0], adjacent_loc.y + DIRECTIONS[index][1]);

    if (is_opponent(jumps.front(), adjacent_loc) && !is_out_of_board(adjacent_loc) && is_possible_to_jump(jump)) {
        return {adjacent_loc, jump};
    }

    return {};
}


jumps_list_t board_t::get_man_jumps(move_list_t& jumps, jumps_list_t& jumps_list)
{
    if (jumps.empty()) {
        return jumps_list;
    }

    for (int i = 0; i < 4; i++)
    {
        auto jump = check_man_jump(jumps, i);
        if (i == 3 && jump.empty())
        {
            if (jumps.size() == 1) {
                jumps.pop_back();
            } else
            {
                jumps_list.push_back(jumps);
                jumps.pop_back();
                jumps.pop_back();
            }
        }
        else if (!jump.empty() && !is_existed(jump, jumps))
        {
            jumps.push_back(jump[0]);
            jumps.push_back(jump[1]);

            if (is_become_king(jump.back(), get_side(jumps.back()))) {
                return get_king_jumps(jump, jumps_list);
            }

            return get_man_jumps(jumps, jumps_list);
        }
    }

    return jumps_list;
}


jumps_list_t board_t::get_possible_jumps(const location_t location)
{
    jumps_list_t jumps_list = {};
    move_list_t jumps = { location };

    auto side = get_side(location);

    if (is_man(location)) {
        return get_man_jumps(jumps, jumps_list);
    }

    if (is_king(location)) {
        return get_king_jumps(jumps, jumps_list);
    }

    return {};
}


void board_t::make_empty(location_t location)
{
    board[location.x][location.y].side = '*';
    board[location.x][location.y].kind = 'E';
}


void board_t::update_piece(const location_t start_move, const location_t end_moves, char side)
{
    if (is_become_king(end_moves, side) || is_king(start_move))
    {
        board[end_moves.x][end_moves.y].kind = 'K';
        board[end_moves.x][end_moves.y].side = side;
    } else
    {
        board[end_moves.x][end_moves.y].kind = 'M';
        board[end_moves.x][end_moves.y].side = side;
    }
}


int board_t::apply_moves(const move_list_t& moves)
{
    auto start_moves = moves[0];
    auto end_moves = moves[moves.size() - 1];
    auto side = get_side(start_moves);
    auto n_captures = (moves.size() - 1) / 2;

    int i = 1;
    while (i < moves.size())
    {
        make_empty(moves[i]);
        i += 2;
    }
    update_piece(start_moves, end_moves, side);
    make_empty(moves[0]);
    display_board();

    return n_captures;
}


jumps_list_t board_t::get_man_moves(const location_t location)
{
    jumps_list_t moves = {};

    // by default, man_directions is direction of white man
    auto man_directions = {DIRECTIONS[0], DIRECTIONS[1]};

    if (get_side(location) == 'B') {
        man_directions = {DIRECTIONS[2], DIRECTIONS[3]};
    }

    for (auto dir : man_directions)
    {
        move_list_t move = {};
        auto tmp = location_t(location.x + dir[0], location.y + dir[1]);
        if (is_empty(tmp) && !is_out_of_board(tmp))
        {
            move.push_back(location);
            move.push_back(tmp);
            moves.push_back(move);
        }
    }

    return moves;
}


jumps_list_t board_t::get_king_moves(const location_t location)
{
    jumps_list_t slides = {};

    for (auto dir : DIRECTIONS)
    {
        auto tmp = location_t(dir[0],  dir[1]);
        auto slide = get_slide(location, tmp);

        if (!slide.empty()) {
            slides.push_back(slide);
        }
    }

    return slides;
}


jumps_list_t board_t::get_possible_moves(const location_t location)
{
    if (is_man(location)) {
        return get_man_moves(location);
    }

    return get_king_moves(location);
}


move_list_t board_t::get_possible_pieces(const int turn)
{
    enum turn_t {
        WHITE,
        BLACK,
    };

    move_list_t pos_pieces = {};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
        {
            auto loc = location_t{i, j};
            if ((turn == WHITE && get_side(loc) == 'W') || (turn == BLACK && get_side(loc) == 'B'))
            {
                auto jumps = get_possible_jumps(loc);
                auto moves = get_possible_moves(loc);
                if (!jumps.empty() || !moves.empty())
                {
                    pos_pieces.push_back(loc);
                }
            }
        }
    }

    return pos_pieces;
}