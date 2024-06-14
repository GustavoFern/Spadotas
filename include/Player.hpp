#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Player
{
public:
    Player(b2World &world, float x, float y, float width, float height)
    {
        // Definir el cuerpo dinámico en Box2D
        b2BodyDef bodyDef;
        bodyDef.position.Set(x / 30.0f, y / 30.0f);
        bodyDef.type = b2_dynamicBody;
        body = world.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(width / 2 / 30.0f, height / 2 / 30.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 0.1f;
        fixtureDef.friction = 0.9f;
        body->CreateFixture(&fixtureDef);

        // Definir la forma en SFML
        shape.setSize(sf::Vector2f(width, height));
        shape.setOrigin(width / 2, height / 2);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);
    }
    void draw(sf::RenderWindow &window)
    {
        // Obtener la posición del jugador
        b2Vec2 position = body->GetPosition();

        // Actualizar la posición de la forma en SFML
        shape.setPosition(position.x * 30.0f, position.y * 30.0f);

        // Dibujar la forma
        window.draw(shape);
    }
    void update();
    b2Body *getBody()
    {
        return body;
    }

private:
    b2Body *body;
    sf::RectangleShape shape;
};