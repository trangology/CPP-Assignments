#pragma once

#include "interface.h"

class computer_interface_t : public strategy_interface_t {
public:
  computer_interface_t();
  virtual move_list_t apply_strategy(board_t& board, const jumps_list_t & moves) = 0;

  void on_win() override;
  void on_lose() override;
  void on_draw() override;

  virtual void print_stat() const;

private:
  size_t win_counter;
  size_t lose_counter;
  size_t draw_counter;
};
