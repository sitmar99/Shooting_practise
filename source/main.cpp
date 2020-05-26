#include "functions.h"

int main()
{
    //Ustawienie ziarna
    srand(time(NULL));

    //Zmienne
    int option = 0;
    int points = 0;
    sf::Event event;
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;

    //Lista entities oraz dodanie celownika
    std::deque<std::shared_ptr<Entity>> entities;
    entities.push_back(std::make_shared<Crosshair>("sprites&fonts/crosshair.png", 50.0, 512));

    //Lista spritow menu
    std::deque<std::shared_ptr<Entity>> menuEntities;
    menuEntities.push_back(std::make_shared<menuOption>(sf::Vector2f(width - 340, height - 240), "sprites&fonts/exit.png", -1));
    menuEntities.push_back(std::make_shared<menuOption>(sf::Vector2f(width/2 - 276,10), "sprites&fonts/!shooting_practise!.png", 0));
    menuEntities.push_back(std::make_shared<menuOption>(sf::Vector2f(width/3,height/3), "sprites&fonts/play.png", 1));
    menuEntities.push_back(std::make_shared<menuOption>(sf::Vector2f(10,height - 240), "sprites&fonts/hi-score.png", 2));

    //Czcionki i tekst
    sf::Font font;
    font.loadFromFile("sprites&fonts/western.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Points: 0");
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Black);

    //Dzwieki
    sf::SoundBuffer buffer;
    buffer.loadFromFile("sprites&fonts/gun_sound_shoot.wav");
    sf::Sound gunShoot;
    gunShoot.setBuffer(buffer);


    //Okno
    sf::RenderWindow window(sf::VideoMode(), "!shooting practice!", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (option)
            {
            case -1:
                window.close();
                break;
            case 0:
                option = Menu(event, menuEntities, gunShoot);
                break;
            case 1:
                option = Game(event, entities, points, gunShoot);
                break;
            case 2:
                option = HiScore(event);
                break;
            }
        }

        //dodanie celu
        addTarget(entities, width, height);

        //update wszystkich celow i celownika
        update(entities, width, height, points);

        window.clear(sf::Color::White);
        
        //rysowanie wszystkich celow i celownika
        for (auto ent: entities)
            window.draw(*ent);

        switch (option)
        {
        case 0:
            //update spritow menu i ich rysowanie
            updateMenu(menuEntities);
            drawMenu(window, menuEntities);

            //ponowne rysowanie celownika, aby zawsze byl na wierzchu
            window.draw(*entities.back());

            break;
        case 1:
            //rysowanie punktow i liczby strzalow
            drawPoints(window, text, height, width, points, entities);
            break;
        case 2:
            //wypisywanie hiscor'a
            drawHiScore(window, text, height, width);
            break;
        }


        window.display();
    }

    return 0;
}