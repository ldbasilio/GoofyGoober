#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        "GoofyGoober Journal"
    );

    std::cout << "UPDATED UI CODE IS RUNNING\n";

    sf::Font font;

    if (!font.openFromFile("assets/fonts/AIK-ErikHolm.otf"))
    {
        std::cout << "Error loading font.\n";
        return 1;
    }

    sf::Text title(font);
    title.setString("LOCAL BUILD TEST");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition({350.f, 80.f});

    sf::Text subtitle(font);
    subtitle.setString("A Personal Question & Reflection Experience");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(sf::Color(180, 180, 180));
    subtitle.setPosition({320.f, 150.f});

    sf::RectangleShape button({300.f, 70.f});
    button.setPosition({490.f, 300.f});
    button.setFillColor(sf::Color(60, 60, 90));

    sf::Text buttonText(font);
    buttonText.setString("Get Random Question");
    buttonText.setCharacterSize(28);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition({530.f, 318.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* mousePressed =
                event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2f mousePos(
                    static_cast<float>(mousePressed->position.x),
                    static_cast<float>(mousePressed->position.y)
                );

                if (button.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Button clicked!\n";
                }
            }
        }

        sf::RectangleShape testBox({300.f, 120.f});
        testBox.setPosition({100.f, 100.f});
        testBox.setFillColor(sf::Color::Red);

        window.clear(sf::Color(25, 25, 35));
        window.draw(testBox);

        window.draw(title);
        window.draw(subtitle);
        window.draw(button);
        window.draw(buttonText);

        window.display();
    }

    return 0;
}