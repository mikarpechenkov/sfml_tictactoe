#include "bot.h"

int Bot::generate_random_bot_cell(const bool filled_cells[]) {
    srand(time(0));//Для генерации случайного числа
    int result = 0;
    bool suitable = false;

    while (!suitable) {
        result = rand() % 9;
        suitable = !filled_cells[result];
    }

    return result;
}

/* Слишком часто получается ничья,
 * поэтому для увеличения шанса на победу несколько условий можно закомментить*/
int Bot::generate_bot_cell(Player &player, const bool filled_cells[]) {
    int result = 0;
    bool smart_choice = false;

    for (int i = 0; i < 3; i++) {
        //Если противник поставил фигуры по вертикали в первые две клетки
        if (player.get_visibility(i) && player.get_visibility(3 + i) && !filled_cells[6 + i]) {
            result = 6 + i;
            smart_choice = true;
        }

        //Если противник поставил фигуры по вертикали в последние две клетки
        if (player.get_visibility(6 + i) && player.get_visibility(3 + i) && !filled_cells[i]) {
            result = i;
            smart_choice = true;
        }

        //Если игрок поставил фигуры по вертикали в первую и последнюю клетки
        if (player.get_visibility(i) && player.get_visibility(6 + i) && !filled_cells[3 + i]) {
            result = 3 + i;
            smart_choice = true;
        }

        //Если противник поставил фигуры по горизонтали в первые две клетки
        if (player.get_visibility(3 * i) && player.get_visibility(1 + 3 * i) && !filled_cells[2 + 3 * i]) {
            result = 2 + 3 * i;
            smart_choice = true;
        }

        //Если противник поставил фигуры по горизонтали в последние две клетки
        if (player.get_visibility(2 + 3 * i) && player.get_visibility(1 + 3 * i) && !filled_cells[3 * i]) {
            result = 3 * i;
            smart_choice = true;
        }

        //Если противник поставил фигуры по горионтали в первую и последнюю клетки
        if (player.get_visibility(2 + 3 * i) && player.get_visibility(3 * i) && !filled_cells[1 + 3 * i]) {
            result = 1 + 3 * i;
            smart_choice = true;
        }
    }

    //Если противник выигрывает по главной диагонали и поставил фигуры в первые две клетки
    if (player.get_visibility(0) && player.get_visibility(4) && !filled_cells[8]) {
        result = 8;
        smart_choice = true;
    }

    //Если противник выигрывает по главной диагонали и поставил фигуры в последние две клетки
    if (player.get_visibility(8) && player.get_visibility(4) && !filled_cells[0]) {
        result = 0;
        smart_choice = true;
    }

    //Если противник выигрывает по главной диагонали и поставил фигуры в первую и последнюю клетки
    if (player.get_visibility(8) && player.get_visibility(0) && !filled_cells[4]) {
        result = 4;
        smart_choice = true;
    }

    //Если противник выигрывает по побочной диагонали и поставил фигуры в первые две клетки
    if (player.get_visibility(2) && player.get_visibility(4) && !filled_cells[6]) {
        result = 6;
        smart_choice = true;
    }

    //Если противник выигрывает по побочной диагонали и поставил фигуры в последние две клетки
    if (player.get_visibility(6) && player.get_visibility(4) && !filled_cells[2]) {
        result = 2;
        smart_choice = true;
    }

    //Если противник выигрывает по побочной диагонали и поставил фигуры в первую и последнюю клетки
    if (player.get_visibility(2) && player.get_visibility(6) && !filled_cells[4]) {
        result = 4;
        smart_choice = true;
    }

    if (!smart_choice)
        result = generate_random_bot_cell(filled_cells);

    return result;
}
