#include <memory>

#include "game/game.h"
#include "strategies/human.h"
#include "strategies/computer_1.h"
#include "strategies/computer_2.h"


int main() {
    auto player1 = std::make_shared<first_computer_strategy_t>("First player");
    auto player2 = std::make_shared<second_computer_strategy_t>("Second player");

    for (int i = 1; i <= 3; ++i) {
        std::cout << "Game " << i << " is about to start: \n" << std::endl;
        game_t game(player1, player2);
        game.play();
    }

//    auto player1 = std::make_shared<first_computer_strategy_t>("First player");
//    auto player2 = std::make_shared<human_strategy_t>();

    game_t game(player1, player2);
    game.play();

    player1->print_stat();
    player2->print_stat();

  return 0;
}
