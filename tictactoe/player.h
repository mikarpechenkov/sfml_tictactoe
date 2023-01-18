#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "iplayer.h"

/*Класс для сущности игрок*/
class Player :public IPlayer{
protected:
    sf::Sprite game_cells[9]; //Фигуры игрока, хранящие правильные позиции на поле
    bool cells_visibility[9]; //Видимость фигур в клетках
    int selected_figure = 0; //Поле, в котором мы храним выбранной пользователем фигуры (1 - крестик, 2 - нолик)

public:
    Player(const sf::Texture &element_texture);

    //Заполняет клетки нужными текстурами для пользователя
    void update();

    const sf::Sprite &get_game_cell(int i) const;

    const bool &get_visibility(int i) const;

    int get_selected_figure();

    void set_game_cell(int i, const sf::Sprite &game_cell);

    void set_visibility(int i, const bool &cell_visibility);

    void set_selected_figure(int selected_figure);
};

#endif // PLAYER_H
