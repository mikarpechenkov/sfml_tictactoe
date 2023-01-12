#ifndef BOT_H
#define BOT_H

#include "player.h"

/*Дочерний класс для бота*/
class Bot : public Player {
private:
    //Метод для генерации рандомной ячейки
    int generate_random_bot_cell(const bool filled_cells[]);

public:
    Bot(const sf::Texture &element_texture) :
            Player(element_texture) {}

    //Метод для умной генерации ячейки
    int generate_bot_cell(Player &player, const bool filled_cells[]);
};

#endif // BOT_H
