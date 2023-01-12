#include "game.h"

Game::Game() {
    try {
        /*Загружаем изображение в текстуру из файла
         *Обрабатываем исключения, если ресурс не удалось загрузить*/
        if (!tictactoe_texture.loadFromFile("../resources/img/crnol.png"))
            throw std::runtime_error("Failed to load resource");

        if (!play_grid_texture.loadFromFile("../resources/img/grid.png"))
            throw std::runtime_error("Failed to load resource");

        //Загружаем шрифт
        if (!font.loadFromFile("../resources/fonts/impact2.ttf"))
            throw std::runtime_error("Failed to load resource");

        //Инициализируем игроков
        player1 = new Player(tictactoe_texture);
        bot = new Bot(tictactoe_texture);

        //Устанавливаем спрайтам текстуры
        play_grid.setTexture(play_grid_texture);
        for (int i = 0; i != 2; i++) {
            choice[i].setTexture(tictactoe_texture);
            choice[i].setPosition(50 + 300 * i, 180);
        }

    } catch (const std::runtime_error ex) {
        std::cout << ex.what() << std::endl;
    }
}

Game::~Game() {
    if (player1 != nullptr)
        delete player1;
    if (bot != nullptr)
        delete bot;
}

/*Функция игрового процесса*/
void Game::game_running() {
    Game game;
    //Если функция запуска игры вернула true, то мы рекурсивно перезапускаем игру
    if (game.start_game())
        game_running();
}

void Game::check_winning() {
/*Заполняем массив выигрышных случаев, всего есть 8 вариантов выигрыша*/
    for (int i = 0; i != 8; i++) {

        //Проверяем поставлены ли три фигуры в ряд по горизонтали
        if (i < 3) {
            winning_case[i][0] =
                    (*player1).get_visibility(3 * i) && (*player1).get_visibility(1 + 3 * i) &&
                    (*player1).get_visibility(2 + 3 * i);
            winning_case[i][1] =
                    (*bot).get_visibility(3 * i) && (*bot).get_visibility(1 + 3 * i) &&
                    (*bot).get_visibility(2 + 3 * i);
        }
            //Проверяем поставлены ли три фигуры в ряд по вертикали
        else if (i < 6) {
            winning_case[i][0] = (*player1).get_visibility(i - 3) && (*player1).get_visibility(i) &&
                                 (*player1).get_visibility(i + 3);
            winning_case[i][1] =
                    (*bot).get_visibility(i - 3) && (*bot).get_visibility(i) && (*bot).get_visibility(i + 3);
        }
            //Проверяем поставлены ли три фигуры в ряд по диагонали
        else {
            winning_case[i][0] =
                    (*player1).get_visibility(2 * (i - 6)) && (*player1).get_visibility(4) &&
                    (*player1).get_visibility(8 - 2 * (i - 6));
            winning_case[i][1] =
                    (*bot).get_visibility(2 * (i - 6)) && (*bot).get_visibility(4) &&
                    (*bot).get_visibility(8 - 2 * (i - 6));
        }

        //После каждой итерации заполнения массива выигрышных случаев, одержана ли победа
        for (int j = 0; j != 2; j++)
            if (winning_case[i][j])
                /* В случае, если победа одержана, меняем значение пермеенной win на true*/
                win = true;
    }
}

void Game::init_labels(std::string result_info) {
    label = sf::Text(result_info, font, 100);

    //В зависимости от содержимого label устанавливаем соответсвующий цвет
    if (!result_info.compare("Dead heat"))
        label.setFillColor(sf::Color::Magenta);
    else if (!result_info.compare("You win"))
        label.setFillColor(sf::Color::Green);
    else if (!result_info.compare("Bot win"))
        label.setFillColor(sf::Color::Red);
    else
        label.setFillColor(sf::Color::Black);

    //Выравниваем текст по центру
    sf::FloatRect text_rect = label.getLocalBounds();
    label.setOrigin(text_rect.left + text_rect.width / 2.0f,
                    text_rect.top + text_rect.height / 2.0f);
    label.setPosition(sf::Vector2f(600 / 2.0f, 600 / 2.0f));

    //Отображение надписи для рестарта
    restart_label = sf::Text("Press space to restart", font);
    restart_label.setFillColor(sf::Color::Black);
    sf::FloatRect restart_text_rect = restart_label.getLocalBounds();
    restart_label.setOrigin(restart_text_rect.left + restart_text_rect.width / 2.0f,
                            restart_text_rect.top + restart_text_rect.height / 2.0f);
    restart_label.setPosition(sf::Vector2f(600 / 2.0f, 600 / 2.0f + text_rect.height));
}

/*Функция возвращает true, если нужно начать игру заново,
* и false, если нужно просто ее завершить */
bool Game::start_game() {
    try {
        //Создаем и отрисовываем новое окно размером 600 на 600, задаем title, делаем размер окна неизменяемым
        sf::RenderWindow main_window(sf::VideoMode(600, 600), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close);

        /*Действия, выполняющиеся до тех пора окно открыто*/
        while (main_window.isOpen()) {

            //Записываем координаты курсора в векторную переменнную
            sf::Vector2i mouse_position = sf::Mouse::getPosition(main_window);

            sf::Event event;

            //Просматриваем очередь событий окна
            while (main_window.pollEvent(event)) {

                //Если нажат пробел, возвращаем значение true
                if (event.key.code == sf::Keyboard::Space)
                    return true;

                //Если пользователь создает запрос на закрытие окна (тип события close)
                if (event.type == sf::Event::Closed)
                    main_window.close(); //закрываем окно

                //Обрабатываем выбор крестика или нолика (выбор пользователя, чем он хочет играть)
                //По сути обрабатываем нажаите кнопки мыши
                if (event.type == sf::Event::MouseButtonPressed) {

                    /*Если в тот момент, когда нажат левая кнопка мыши,
                     * и координаты курсора были на крестике или нолике мы выибраем соотвествующую фигуру*/
                    if (event.key.code == sf::Mouse::Left) {
                        //Если пользователь еще не выбрал фигур
                        if ((*player1).get_selected_figure() == 0) {
                            for (int i = 0; i != 2; i++)
                                if (choice[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                                    (*player1).set_selected_figure(i + 1); //1 - крестик, 2 - нолик
                        }

                            //Если пользователь выбрал фигуру (то есть игра идет), но еще никто не победил
                        else if (!win) {
                            for (int i = 0; i != 9; i++)
                                //Если пользователь нажал на свободную клетку
                                if ((*player1).get_game_cell(i).getGlobalBounds().contains(mouse_position.x,
                                                                                           mouse_position.y)
                                    && !filled_cells[i]) {
                                    //Устанавливаем видимость клтеки, в которую нажал пользователь (чтобы отобразился его ход)
                                    (*player1).set_visibility(i, true);

                                    //Записываем данные о том, что клетка поля теперь заполнена
                                    filled_cells[i] = true;
                                    count_filled_cells++;

                                    //Разрешаем боту ходить
                                    next_players_turn = true;
                                }
                        }
                    }
                }
            }

            /*В ресурсах лежит картинка с крестиками и ноликами (нижнюю часть решил не использовать),
             *  для каждого спрайта мы устанавливаем соответсвующую фигуру
             * делается это через метод setTextureRect
             * (по сути мы вырезаем попиксильно нужную нам фигуру из общей картинки)*/
            for (int i = 0; i != 2; i++)
                choice[i].setTextureRect(sf::IntRect(200 * i, 0, 200, 200));

            //Заполняем клетки нужными текстурами для пользователя
            (*player1).update();

            /*Если победа не одержана, сейчас ход бота и еще не все клетки поля заполнены,
             * бот делает ход*/
            if (!win && next_players_turn && count_filled_cells < 9) {
                int bot_choice = (*bot).generate_bot_cell((*player1), reinterpret_cast<bool *>(filled_cells));
                (*bot).set_visibility(bot_choice, true);
                filled_cells[bot_choice] = true;
                count_filled_cells++;

                //Делаем ход бота запрещенным, чтобы он не начал ходить вместо игрока
                next_players_turn = false;
            }

            check_winning(); //Проверяем, не одержана ли победа

            //Устанавливаем фигуру, которой будет играть бот (она противоположна фигуре, которой играет пользователь
            (*bot).set_selected_figure(((*player1).get_selected_figure()) % 2 + 1);
            //Заполняем клетки нужными текстурами для бота
            (*bot).update();

            //Очищаем содержимое окна, чтобы изображения не накладывались друг на друга (у нас же все в цикле)
            main_window.clear(sf::Color::White);

            /*Если не выбрана ни одна из фигур, то снова отрисовываем выбор,
             * иначе отрисовываем игровую сетку */
            if ((*player1).get_selected_figure() == 0)
                for (int i = 0; i != 2; i++)
                    main_window.draw(choice[i]);
            else {
                main_window.draw(play_grid); //Отрисовываем сетку
                //В цикле отрисовываем фигуры, если им в соотвествие в массиве видимости установлено значение true
                for (int i = 0; i != 9; i++) {
                    if ((*player1).get_visibility(i))
                        main_window.draw((*player1).get_game_cell(i));
                    if ((*bot).get_visibility(i))
                        main_window.draw((*bot).get_game_cell(i));
                }
            }

            //Вывод ничьей
            if (!win && count_filled_cells == 9) {
                init_labels("Dead heat");
                main_window.clear(sf::Color::White);
                main_window.draw(label);
                main_window.draw(restart_label);
            }

            //Вывод сведений о победе
            if (win) {
                bool player_winning = false; //Переменная, показывающая победил ли пользователь

                //Проверка на победу пользователя
                for (int i = 0; i != 8; i++)
                    player_winning += winning_case[i][0];

                //В зависимости от того, кто победил, выводим соответсвующую надпись
                if (player_winning)
                    init_labels("You win");
                else
                    init_labels("Bot win");

                main_window.clear(sf::Color::White);
                main_window.draw(label);
                main_window.draw(restart_label);
            }

            //Отображаем содержимое окна
            main_window.display();
        }

    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }

    return false;
}
