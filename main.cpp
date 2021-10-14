#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14f
using namespace std;
struct PLAYER : public sf::CircleShape
{
    float angle = 0;
};
int main()
{
    sf::RenderWindow window({640,480}, "GAME");
    string map[] = {
            "####################",
            "#..................#",
            "#.#######..........#",
            "#.#................#",
            "#.#................#",
            "#.#..........#.....#",
            "#.#........###.....#",
            "#.#................#",
            "#.#................#",
            "#.#........##......#",
            "#.#........##......#",
            "#.#................#",
            "#.#############....#",
            "#...............####",
            "####################"

    };
    sf::Clock clock;
    PLAYER player;
    player.setPosition(320, 240);
    player.setRadius(8);
//    window.setFramerateLimit(144);
    while(window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        deltaTime *= 60;
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2f lastPosPlayer = player.getPosition();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(cos(player.angle * PI / 180) * 4.f * deltaTime, sin(player.angle * PI / 180) * 4.f * deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(sin(player.angle * PI / 180) * 4.f * deltaTime, -cos(player.angle * PI / 180) * 4.f * deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(-cos(player.angle * PI / 180) * 4.f * deltaTime, -sin(player.angle * PI / 180) * 4.f * deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(-sin(player.angle * PI / 180) * 4.f * deltaTime, cos(player.angle * PI / 180) * 4.f * deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            player.angle -= 5 * deltaTime;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            player.angle += 5 * deltaTime;

        if(player.angle < 0)
            player.angle = 360;
        if(player.angle > 360)
            player.angle = 0;

        if(map[ int(player.getPosition().y+8) / 32] [int(player.getPosition().x+8) / 32] == '#' || map[ int(player.getPosition().y) / 32] [int(player.getPosition().x) / 32] == '#')
            player.setPosition(lastPosPlayer);

        window.clear();

        sf::RectangleShape sky;
        sky.setSize({640, 240});
        sky.setPosition(0,0);
        sky.setFillColor(sf::Color::Cyan);
        window.draw(sky);

        sf::RectangleShape floor;
        floor.setSize({640, 240});
        floor.setPosition(0, 240);
        floor.setFillColor({124, 252, 0});
        window.draw(floor);

        float countAngle = player.angle - 45.f;
        for(int i = 0; i < 90; ++i)
        {
            float dist = 1;
            for(; dist < 640.f; dist += 2)
            {
                if(map[int(((player.getPosition().y+player.getRadius()) + dist * sin(countAngle * PI / 180.f)) / 32.f)][int(((player.getPosition().x+player.getRadius()) + dist * cos(countAngle * PI / 180.f)) / 32.f)] == '#')
                    break;
            }
            sf::Vertex line[2];
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
            line[0].position = {player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius()};
            line[1].position = {(player.getPosition().x+player.getRadius()) + dist * cos(countAngle * PI / 180.f),
                                (player.getPosition().y+player.getRadius()) + dist * sin(countAngle * PI / 180.f)};
//            window.draw(line, 2, sf::Lines);
            float distance = pow(line[0].position.x - line[1].position.x ,2) + pow(line[0].position.y - line[1].position.y ,2);
            distance = sqrt(distance);
            sf::RectangleShape cube;
            cube.setSize({3850 / distance, 7000 / distance});
            cube.setOrigin(0, cube.getSize().y / 2);
            cube.setPosition(i * (640.f / 90.f), 240);
            cube.setFillColor({sf::Uint8(255 / (1 + distance * distance * 0.0001f)),
                               sf::Uint8(255 / (1 + distance * distance * 0.0001f)),
                               sf::Uint8(255 / (1 + distance * distance * 0.0001f))});

            window.draw(cube);
            countAngle += 1;
        }

        sf::RectangleShape cb;
        cb.setSize({4*20,4*15});
        cb.setPosition(0,0);
        cb.setFillColor(sf::Color::Black);
        cb.setOutlineThickness(1);
        cb.setFillColor({120, 120, 120});
        window.draw(cb);
        for(int i = 0; i < 15; ++i)
        {
            for(int j = 0; map[i][j] != '\0'; ++j)
            {
                if(map[i][j] == '#')
                {
                    sf::RectangleShape cube;
                    cube.setSize({4,4});
                    cube.setPosition(j * 4, i * 4);
                    cube.setFillColor(sf::Color::Black);
                    cube.setOutlineThickness(1);
                    cube.setOutlineColor(sf::Color::White);
                    window.draw(cube);
                }
//                else
//                {
//                    sf::RectangleShape cube;
//                    cube.setSize({4,4});
//                    cube.setPosition(j * 4, i * 4);
//                    cube.setFillColor({120,120,120});
//                    window.draw(cube);
//                }
            }
        }


        PLAYER copyPlayer = player;
        copyPlayer.setPosition(player.getPosition().x / 8 , player.getPosition().y / 8 );
        copyPlayer.setRadius(2);
        sf::Vertex ln[2];
        ln[0].color = sf::Color::Red;
        ln[1].color = sf::Color::Red;
        ln[0].position = {copyPlayer.getPosition().x + copyPlayer.getRadius(), copyPlayer.getPosition().y + copyPlayer.getRadius()};
        ln[1].position = {(copyPlayer.getPosition().x+copyPlayer.getRadius()) + 10 * cos(copyPlayer.angle * PI / 180.f),
                          (copyPlayer.getPosition().y+copyPlayer.getRadius()) + 10 * sin(copyPlayer.angle * PI / 180.f)};
        window.draw(ln, 2, sf::Lines);
        window.draw(copyPlayer);

        window.display();
        cout << 1.f / (deltaTime / 60) << endl;
    }
    return 0;
}