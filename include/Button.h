#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
private:
    sf::RectangleShape shape;
    sf::Text text;

    sf::Color normalColor;
    sf::Color hoverColor;

public:
    Button(const sf::Font& font,
           const std::string& label,
           const sf::Vector2f& size,
           const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);
    void update(const sf::Vector2f& mousePosition);
    bool isClicked(const sf::Vector2f& mousePosition) const;
};