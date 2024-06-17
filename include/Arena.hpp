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
    Arena(sf::RenderWindow* window);
    int run();

private:
    void processEvents();
    void update();
    void render();

    b2World world;
    Collidable ground;
    Collidable LimIz;
    Collidable LimDer;
    Collidable LimSup;
    Player player1;
    Player player2;
    sf::RenderWindow* window;
    sf::Texture player1Texture;
    sf::Texture player2Texture;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    ContactListener contactListener;

    float desiredSpeed;
    int gameInProgres=1;
};

Arena::Arena(sf::RenderWindow* win)
    : window(win),
      world(b2Vec2(0.0f, 12.0f)),
      ground(world, 640.0f, 682.5f, 1280.0f, 75.0f),
      LimIz(world, 0.0f, 360.0f, 1.0f, 720.0f),
      LimDer(world, 1280.0f, 360.0f, 1.0f, 720.0f),
      LimSup(world, 640.0f, 0.0f, 1280.0f, 1.0f),
      desiredSpeed(12.0f)
{

    if (!player1Texture.loadFromFile("assets/images/idle.png")) {
        std::cout << "No se cargo correctamente";
    }
    if (!player2Texture.loadFromFile("assets/images/idle.png")) {
        std::cout << "No se cargo correctamente";
    }
    if (!fondoTexture.loadFromFile("assets/images/arenaBackground.png")) {
        std::cout << "No se cargó correctamente la textura del fondo" << std::endl;
    }
fondoSprite.setTexture(fondoTexture);

    player1 = Player(world, 800.0f, 300.0f, 50.0f, 50.0f, &player1Texture),
    player2 = Player(world, 400.0f, 300.0f, 50.0f, 50.0f, &player2Texture),

    // Configurar identificadores de usuario para los cuerpos
    ground.getBody()->GetUserData().pointer = static_cast<uintptr_t>(2);  // Identificador del suelo
    player1.getBody()->GetUserData().pointer = static_cast<uintptr_t>(1); // Identificador del jugador 1
    player2.getBody()->GetUserData().pointer = static_cast<uintptr_t>(3); // Identificador del jugador 2

    world.SetContactListener(&contactListener); // Registrar el contact listener
}

int Arena::run()
{
    while (gameInProgres==1)
    {
        update();
        processEvents();
        render();
    }
    return 0;
}

void Arena::processEvents()
{
    static bool mKeyWasPressed = false;
    static bool spaceKeyPressed = false;
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }

    if (player1.AreYouLive()||player2.AreYouLive()){
        gameInProgres=0;
    }

    //! Manejar la entrada del teclado Player 1

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        if (!mKeyWasPressed && player1.isDashAvailable() && !player1.isPlayerDashing())
        {
            player1.startDash();
            player1.dash(4.0f);
            player1.increaseDashCounter();
        }
        mKeyWasPressed = true;
    }
    else
    {
        mKeyWasPressed = false;
    }

   // Limitar la velocidad máxima del jugador 1
    b2Vec2 velocity1 = player1.getBody()->GetLinearVelocity();
    if (abs(velocity1.x) > desiredSpeed && !player1.isPlayerDashing())
    {
        velocity1.x = (velocity1.x > 0 ? 1 : -1) * desiredSpeed; // Ajusta la velocidad en X manteniendo el signo
        player1.getBody()->SetLinearVelocity(velocity1);         // Aplicar la velocidad limitada al jugador
    }
    if (velocity1.y > -10.0f)
    {
        player1.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 10.0f), true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !player1.isPlayerDashing()) // El evento al que responde
        player1.getBody()->ApplyLinearImpulse(
            b2Vec2(-0.5f, 0), // Fuerza que se aplica
            player1.getBody()->GetWorldCenter(),
            true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !player1.isPlayerDashing()) // El evento al que responde
        player1.getBody()->ApplyLinearImpulse(
            b2Vec2(0.5f, 0), // Fuerza que se aplica
            player1.getBody()->GetWorldCenter(),
            true);
    if (contactListener.isPlayer1OnGround())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // El evento al que responde
            player1.getBody()->ApplyLinearImpulse(
                b2Vec2(0, -3.5f), // Fuerza que se aplica
                player1.getBody()->GetWorldCenter(),
                true);
    }

    //! Manejar la entrada del teclado Player 2

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!spaceKeyPressed && player2.isDashAvailable() && !player2.isPlayerDashing())
        {
            player2.startDash();
            player2.dash(4.0f);
            player2.increaseDashCounter();
        }
        spaceKeyPressed = true;
    }
    else
    {
        spaceKeyPressed = false;
    }

    // Limitar la velocidad máxima del jugador 2

    b2Vec2 velocity2 = player2.getBody()->GetLinearVelocity();
    if (abs(velocity2.x) > desiredSpeed&& !player2.isPlayerDashing())
    {
        velocity2.x = (velocity2.x > 0 ? 1 : -1) * desiredSpeed; // Ajusta la velocidad en X manteniendo el signo
        player2.getBody()->SetLinearVelocity(velocity2);         // Aplicar la velocidad limitada al jugador
    }
    if (velocity2.y > -10.0f)
    {
        player2.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 10.0f), true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !player2.isPlayerDashing()) // El evento al que responde
        player2.getBody()->ApplyLinearImpulse(
            b2Vec2(-0.5f, 0), // Fuerza que se aplica
            player2.getBody()->GetWorldCenter(),
            true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !player2.isPlayerDashing()) // El evento al que responde
        player2.getBody()->ApplyLinearImpulse(
            b2Vec2(0.5f, 0), // Fuerza que se aplica
            player2.getBody()->GetWorldCenter(),
            true);

    if (contactListener.isPlayer2OnGround())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // El evento al que responde
            player2.getBody()->ApplyLinearImpulse(
                b2Vec2(0, -3.5f), // Fuerza que se aplica
                player2.getBody()->GetWorldCenter(),
                true);
    }

    //! Respawn de los jugadores o choque de espadas
    if (contactListener.arePlayersInContact() && player2.isPlayerDashing() && player1.isPlayerDashing())
    {
        // Si ambos jugadores están dashing hacia el otro, aplicar un impulso para separarlos
        if ((velocity2.x > 0.0f && velocity1.x < 0.0f) || (velocity2.x < 0.0f && velocity1.x > 0.0f))
        {
            // Aplicar un impulso hacia afuera basado en la dirección de cada jugador
            b2Vec2 impulseToPlayer2 = player2.getBody()->GetWorldCenter() - player1.getBody()->GetWorldCenter();
            impulseToPlayer2.Normalize(); // Normalizar para obtener solo la dirección
            impulseToPlayer2 *= 4.0f;    // Ajustar la magnitud del impulso

            b2Vec2 impulseToPlayer1 = -impulseToPlayer2; // Impulso opuesto para el otro jugador

            player2.getBody()->ApplyLinearImpulse(impulseToPlayer2, player2.getBody()->GetWorldCenter(), true);
            player1.getBody()->ApplyLinearImpulse(impulseToPlayer1, player1.getBody()->GetWorldCenter(), true);
        }
    }
    else
    {
        if (contactListener.arePlayersInContact() && player1.isPlayerDashing())
        {
            player2.reset(world, 200.0f, 100.0f, 50.0f, 50.0f, &player2Texture);
            player2.getBody()->GetUserData().pointer = static_cast<uintptr_t>(3); // Identificador del jugador 2
        }

        if (contactListener.arePlayersInContact() && player2.isPlayerDashing())
        {
            player1.reset(world, 1000.0f, 100.0f, 50.0f, 50.0f, &player1Texture);
            player1.getBody()->GetUserData().pointer = static_cast<uintptr_t>(1); // Identificador del jugador 2
        }
    }
}

void Arena::update()
{
    // Avanzar la simulación de Box2D
    world.Step(1.0f / 60.0f, 6, 2);
    player1.update(0.0f);
    player2.update(0.0f);

    if (player1.isPlayerDashing())
    {
        player1.dashState();
    }

    if (player1.getDashCounter() >= 2 && !player1.isPlayerDashing())
    {
        //std::cout << "Cooldown\n";
        player1.startCoolDown();
    }

    if(!player1.isDashAvailable()){
        player1.coolDown();
    }

    if (player2.isPlayerDashing())
    {
        player2.dashState();
    }

    if (player2.getDashCounter() >= 2 && !player2.isPlayerDashing())
    {
        //std::cout << "Cooldown\n";
        player2.startCoolDown();
    }

    if(!player2.isDashAvailable()){
        player2.coolDown();
    }

}

void Arena::render()
{
    window->clear();

    // Dibujar el fondo (no cambia, por lo que no se actualiza)
    window->draw(fondoSprite);

    // Dibujar el frente dinámico
    ground.draw(*window); // Dibujar el suelo
    player1.draw(*window);
    player2.draw(*window);

    window->display();
}