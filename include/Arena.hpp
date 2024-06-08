#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstdint>
#include "Collidable.hpp"
#include "Player.hpp"
#include "ContactListener.hpp"

class Arena
{
public:
    Arena();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    b2World world;
    Collidable ground;
    Collidable LimIz;
    Collidable LimDer;
    Collidable LimSup;
    Player player1;
    Player player2;

    float desiredSpeed;
    ContactListener contactListener;
};

Arena::Arena()
    : window(sf::VideoMode(1280, 720), "Spadotas"),
      world(b2Vec2(0.0f, 9.81f)),
      ground(world, 640.0f, 635.0f, 1280.0f, 170.0f),
      LimIz(world, 0.0f, 360.0f, 1.0f, 720.0f),
      LimDer(world, 1280.0f, 360.0f, 1.0f, 720.0f),
      LimSup(world, 640.0f, 0.0f, 1280.0f, 1.0f),
      player1(world, 400.0f, 300.0f, 50.0f, 50.0f),
      player2(world, 800.0f, 300.0f, 50.0f, 50.0f),
      desiredSpeed(14.0f)
{
    window.setFramerateLimit(60);

    // Configurar identificadores de usuario para los cuerpos
    ground.getBody()->GetUserData().pointer = static_cast<uintptr_t>(2); // Identificador del suelo
    player1.getBody()->GetUserData().pointer = static_cast<uintptr_t>(1); // Identificador del jugador 1
    player2.getBody()->GetUserData().pointer = static_cast<uintptr_t>(3); // Identificador del jugador 2

    world.SetContactListener(&contactListener); // Registrar el contact listener
}

void Arena::run() {
    while (window.isOpen()) {
        update();
        processEvents();
        render();
    }
}

void Arena::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    // Manejar la entrada del teclado Player 1
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player2.getBody()->ApplyLinearImpulse(
                b2Vec2(0, 2.0f), 
                player2.getBody()->GetWorldCenter(), 
                true);
    if (contactListener.isPlayer1OnGround())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//El evento al que responde
            player1.getBody()->ApplyLinearImpulse(
                b2Vec2(-0.5f, 0),//Fuerza que se aplica
                player1.getBody()->GetWorldCenter(),
                true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//El evento al que responde
            player1.getBody()->ApplyLinearImpulse(
                b2Vec2(0.5f, 0),//Fuerza que se aplica
                player1.getBody()->GetWorldCenter(),
                true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//El evento al que responde
            player1.getBody()->ApplyLinearImpulse(
                b2Vec2(0, -2.0f),//Fuerza que se aplica
                player1.getBody()->GetWorldCenter(), 
                true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//El evento al que responde
            player1.getBody()->ApplyLinearImpulse(
                b2Vec2(0.5f, -2.0f),//Fuerza que se aplica
                player1.getBody()->GetWorldCenter(), 
                true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//El evento al que responde
            player1.getBody()->ApplyLinearImpulse(
                b2Vec2(-0.5f, -2.0f),//Fuerza que se aplica
                player1.getBody()->GetWorldCenter(), 
                true);
    }

    if (contactListener.isPlayer2OnGround())
    {
        // Manejar la entrada del teclado Player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player2.getBody()->ApplyLinearImpulse(b2Vec2(-0.1f, 0), player2.getBody()->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player2.getBody()->ApplyLinearImpulse(b2Vec2(0.1f, 0), player2.getBody()->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player2.getBody()->ApplyLinearImpulse(b2Vec2(0, -0.1f), player2.getBody()->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player2.getBody()->ApplyLinearImpulse(b2Vec2(0, 0.1f), player2.getBody()->GetWorldCenter(), true);
    }
}

void Arena::update() {
    // Limitar la velocidad máxima del jugador 1
    b2Vec2 velocity1 = player1.getBody()->GetLinearVelocity();
    if (velocity1.Length() > desiredSpeed&&contactListener.isPlayer1OnGround()) {
        velocity1.Normalize(); // Normalizar el vector de velocidad
        velocity1 *= desiredSpeed; // Escalar la velocidad al valor máximo
        player1.getBody()->SetLinearVelocity(velocity1); // Aplicar la velocidad limitada al jugador
    }

    // Limitar la velocidad máxima del jugador 2
    /*b2Vec2 velocity2 = player2.getBody()->GetLinearVelocity();
    if (velocity2.Length() > desiredSpeed) {
        velocity2.Normalize(); // Normalizar el vector de velocidad
        velocity2 *= desiredSpeed; // Escalar la velocidad al valor máximo
        player2.getBody()->SetLinearVelocity(velocity2); // Aplicar la velocidad limitada al jugador
    }*/

    // Avanzar la simulación de Box2D
    world.Step(1.0f / 60.0f, 6, 2);
}

void Arena::render() {
    window.clear();

    ground.draw(window); // Dibujar el suelo
    LimIz.draw(window);
    LimDer.draw(window);
    LimSup.draw(window);
    player1.draw(window);
    player2.draw(window);

    window.display();
}