#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button.h"
#include "QuestionManager.h"

Question currentQuestion;
bool hasCurrentQuestion = false;
std::string screenMessage = "Choose an option to begin.";

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        "GoofyGoober Journal"
    );

    std::cout << "UPDATED UI CODE IS RUNNING\n";

    sf::Font font;

    if (!font.openFromFile("assets/fonts/Readfine Demo.ttf"))
    {
        std::cout << "Error loading font.\n";
        return 1;
    }

    sf::Text title(font);
    title.setString("GoofyGoober Journal");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition({300.f, 50.f});

    sf::Text subtitle(font);
    subtitle.setString("A Personal Question & Reflection Experience");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(sf::Color(180, 180, 180));
    subtitle.setPosition({320.f, 150.f});

    sf::Text questionText(font);
    questionText.setCharacterSize(22);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition({120.f, 260.f});
    questionText.setString("Question #" + std::to_string(currentQuestion.id) + ":\n" + currentQuestion.text);

    sf::RectangleShape button({300.f, 70.f});    button.setPosition({490.f, 500.f});
    button.setFillColor(sf::Color(60, 60, 90));

    sf::Text buttonText(font);
    buttonText.setString("Get Random Question");
    buttonText.setCharacterSize(28);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition({530.f, 518.f});

    QuestionManager manager;

    if (!manager.loadQuestions("data/questions.txt"))
    {
        std::cout << "Error: Could not load questions.txt\n";
        return 1;
    }

    manager.loadProgress("data/progress.txt");

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
                    currentQuestion = manager.getRandomQuestion();
                    hasCurrentQuestion = true;

                    questionText.setString(
                        "Question #" + std::to_string(currentQuestion.id) + ":\n" +
                        currentQuestion.text
                    );
                }
            }
        }

        window.clear(sf::Color(25, 25, 35));

        window.draw(title);
        window.draw(subtitle);
        window.draw(questionText);
        window.draw(button);
        window.draw(buttonText);

        window.display();
    }

    return 0;
}