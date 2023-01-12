#include "player.h"

Player::Player(const sf::Texture &element_texture) {
    for (int i = 0; i != 9; i++) {
        game_cells[i].setTexture(element_texture);
        cells_visibility[i] = false;
    }
    //Устанавливаем позицию для клеток
    for (int i = 0; i != 3; i++)
        for (int j = 0; j != 3; j++)
            game_cells[i * 3 + j].setPosition(200 * j, 200 * i);
}

void Player::update() {
    for (int i = 0; i != 9; i++)
        game_cells[i].setTextureRect(sf::IntRect(200 * (selected_figure - 1), 0, 200, 200));
}

const sf::Sprite &Player::get_game_cell(int i) const {
    return game_cells[i];
}

const bool &Player::get_visibility(int i) const {
    return cells_visibility[i];
}

void Player::set_game_cell(int i, const sf::Sprite &game_cell) {
    game_cells[i] = game_cell;
}

void Player::set_visibility(int i, const bool &cell_visibility) {
    cells_visibility[i] = cell_visibility;
}

void Player::set_selected_figure(int selected_figure) {
    this->selected_figure = selected_figure;
}

int Player::get_selected_figure() {
    return selected_figure;
}
