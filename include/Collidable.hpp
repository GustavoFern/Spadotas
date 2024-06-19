#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Collidable
{
public:
    Collidable(b2World &world, float x, float y, float width, float height)
    {
        // Definir el cuerpo estático en Box2D
        b2BodyDef bodyDef;
        bodyDef.position.Set(x / 30.0f, y / 30.0f); // Divide por 30 para convertir a metros
        bodyDef.type = b2_staticBody;
        body = world.CreateBody(&bodyDef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox(width / 2 / 30.0f, height / 2 / 30.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &groundBox;
        fixtureDef.friction = 0.5f; // Ajusta el coeficiente de fricción aquí
        body->CreateFixture(&fixtureDef);

        // Definir la forma en SFML
        shape.setSize(sf::Vector2f(width, height));
        shape.setOrigin(width / 2, height / 2);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Transparent);
    }
    void Draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }

    b2Body *GetBody()
    {
        return body;
    }

private:
    b2Body *body;
    sf::RectangleShape shape;
};