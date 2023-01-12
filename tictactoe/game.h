#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "bot.h"


class Game {
private:
    /*Массив, хранящий информацию о заполненности клеток поля
     * (указывает, еслть ли такм крестик или нолик)*/
    bool filled_cells[9] = {false};

    /*Число заполненных клеток поля*/
    int count_filled_cells = 0;
    bool win = false; //Переменная, указывающая выполнено ли условие победы
    bool next_players_turn = false; //Перменная, указывающая разешено ли боту делать ход
    bool winning_case[8][2]; //Массив, хранящий все выигрышные случаи

    //Экземпляры текстур
    sf::Texture tictactoe_texture;
    sf::Texture play_grid_texture;

    //Обертки для структур
    sf::Sprite choice[2];
    sf::Sprite play_grid;

    //Экземпляр шрифта
    sf::Font font;

    //Создаем label для отображения результатов игры
    sf::Text label;
    sf::Text restart_label;

    /*Создаем игроков через указатели,
     * так как они не имеют безаргументных конструкторов*/
    Player *player1 = nullptr;
    Bot *bot = nullptr;

    /*Функция запуска игры, она возвращает true, если пользователь хочет перезапустить игру,
     * и false, если игра должна быть завершена*/
    bool start_game();

    //Функция для проверки на выполнение условий победы
    void check_winning();

    //Функция инициализации информационных labels
    void init_labels(std::string result_info);

public:
    Game();

    ~Game(); //Деконструктор необходим, так как Player и Bot - указатели

    //Функция игрового процесса с
    static void game_running();
};

#endif // GAME_H
