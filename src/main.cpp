#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button.h"
#include "QuestionManager.h"

Question currentQuestion;
bool hasCurrentQuestion = false;
std::string screenMessage = "Choose an option to begin.";

std::string wrapText(const std::string& text, int maxLineLength)
{
    std::string result;
    std::string currentLine;
    std::string word;

    for (char character : text)
    {
        if (character == ' ')
        {
            if (static_cast<int>(currentLine.length() + word.length()) > maxLineLength)
            {
                result += currentLine + "\n";
                currentLine = word + " ";
            }
            else
            {
                currentLine += word + " ";
            }

            word.clear();
        }
        else
        {
            word += character;
        }
    }

    if (!word.empty())
    {
        if (static_cast<int>(currentLine.length() + word.length()) > maxLineLength)
        {
            result += currentLine + "\n";
            currentLine = word;
        }
        else
        {
            currentLine += word;
        }
    }

    result += currentLine;

    return result;
}

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
    questionText.setString("Question #" + std::to_string(currentQuestion.id) + ":\n" + wrapText(currentQuestion.text, 75));

    sf::RectangleShape button({300.f, 70.f});    
    button.setPosition({290.f, 550.f});
    button.setFillColor(sf::Color(60, 60, 90));

    sf::Text buttonText(font);
    buttonText.setString("Get Random Question");
    buttonText.setCharacterSize(28);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition({330.f, 568.f});

    QuestionManager manager;

    std::string userAnswer;
    bool answerBoxActive = false;

    sf::RectangleShape answerBox({900.f, 120.f});
    answerBox.setPosition({190.f, 390.f});
    answerBox.setFillColor(sf::Color(35, 35, 50));
    answerBox.setOutlineColor(sf::Color(90, 90, 130));
    answerBox.setOutlineThickness(2.f);

    sf::Text answerText(font);
    answerText.setCharacterSize(22);
    answerText.setFillColor(sf::Color::White);
    answerText.setPosition({210.f, 410.f});
    answerText.setString("Click here to type your response...");

    sf::RectangleShape saveButton({260.f, 60.f});
    saveButton.setPosition({730.f, 550.f});
    saveButton.setFillColor(sf::Color(60, 90, 70));

    sf::Text saveButtonText(font);
    saveButtonText.setString("Save Answer");
    saveButtonText.setCharacterSize(26);
    saveButtonText.setFillColor(sf::Color::White);
    saveButtonText.setPosition({775.f, 565.f});

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
                    wrapText(currentQuestion.text, 75)
                );
            }

            if (answerBox.getGlobalBounds().contains(mousePos))
            {
                answerBoxActive = true;

                if (userAnswer.empty())
                {
                    answerText.setString("");
                }
            }
            else
            {
                answerBoxActive = false;
            }

            if (saveButton.getGlobalBounds().contains(mousePos))
            {
                if (hasCurrentQuestion && !userAnswer.empty())
                {
                    manager.saveResponse("data/responses.txt", currentQuestion, userAnswer);
                    manager.markCurrentQuestionAnswered();
                    manager.saveProgress("data/progress.txt");

                    questionText.setString("Answer saved. Click for another question.");
                    userAnswer.clear();
                    answerText.setString("Click here to type your response...");
                    hasCurrentQuestion = false;
                }
            }
        }

        if (answerBoxActive)
        {
            if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
            {
                char32_t unicode = textEntered->unicode;

                if (unicode == 8)
                {
                    if (!userAnswer.empty())
                    {
                        userAnswer.pop_back();
                    }
                }
                else if (unicode >= 32 && unicode < 127)
                {
                    userAnswer += static_cast<char>(unicode);
                }

                answerText.setString(wrapText(userAnswer, 80));
            }
        }
    }

    window.clear(sf::Color(25, 25, 35));

    window.draw(title);
    window.draw(subtitle);
    window.draw(questionText);
    window.draw(button);
    window.draw(buttonText);

    window.draw(answerBox);
    window.draw(answerText);
    window.draw(saveButton);
    window.draw(saveButtonText);

    window.display();
}