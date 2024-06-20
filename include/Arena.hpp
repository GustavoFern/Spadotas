#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstdint>
#include "Collidable.hpp"
#include "Player.hpp"
#include "ContactListener.hpp"
#include "Sound.hpp"

class Arena
{
public:
    Arena(sf::RenderWindow *window);
    int Run();

private:
    void ProcessEvents();
    void Update();
    void Render();

    b2World world;
    Collidable ground;
    Collidable limIz;
    Collidable limDer;
    Collidable limSup;
    Player player1;
    Player player2;
    sf::RenderWindow *window;
    sf::Texture player1TextureRunIdle;
    sf::Texture player2TextureRunIdle;
    sf::Texture player1TextureJumpDash;
    sf::Texture player2TextureJumpDash;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    ContactListener contactListener;

    float desiredSpeed;
    int gameInProgres = 1, row1 = 1, spt1 = 0, spt2 = 0, row2 = 1;
    bool right1 = true, right2 = true;
};

Arena::Arena(sf::RenderWindow *win)
    : window(win),
      world(b2Vec2(0.0f, 12.0f)),
      ground(world, 640.0f, 682.5f, 1280.0f, 75.0f),
      limIz(world, 0.0f, 360.0f, 1.0f, 720.0f),
      limDer(world, 1280.0f, 360.0f, 1.0f, 720.0f),
      limSup(world, 640.0f, 0.0f, 1280.0f, 1.0f),
      desiredSpeed(12.0f)
{
    Sound arenaMusic;
    arenaMusic.PlayMusic("assets/sounds/arenaMusic.wav");
    if (!player1TextureRunIdle.loadFromFile("assets/images/runIdle.png"))
    {
        std::cout << "No se cargo correctamente";
    }
    if (!player2TextureRunIdle.loadFromFile("assets/images/runIdleP2.png"))
    {
        std::cout << "No se cargo correctamente";
    }
    if (!player1TextureJumpDash.loadFromFile("assets/images/dashJump.png"))
    {
        std::cout << "No se cargo correctamente";
    }
    if (!player2TextureJumpDash.loadFromFile("assets/images/dashJumpP2.png"))
    {
        std::cout << "No se cargo correctamente";
    }
    if (!fondoTexture.loadFromFile("assets/images/arenaBackground.png"))
    {
        std::cout << "No se cargó correctamente la textura del fondo" << std::endl;
    }
    fondoSprite.setTexture(fondoTexture);

    player1 = Player(world, 800.0f, 300.0f, 50.0f, 50.0f, &player1TextureRunIdle, &player1TextureJumpDash);
    player2 = Player(world, 400.0f, 300.0f, 50.0f, 50.0f, &player2TextureRunIdle, &player2TextureJumpDash);

    // Configurar identificadores de usuario para los cuerpos
    ground.GetBody()->GetUserData().pointer = static_cast<uintptr_t>(2); // Identificador del suelo
    player1.GetBody()->GetUserData().pointer = static_cast<uintptr_t>(1);    // Identificador del jugador 1
    player2.GetBody()->GetUserData().pointer = static_cast<uintptr_t>(3);    // Identificador del jugador 2

    world.SetContactListener(&contactListener); // Registrar el contact listener
}

int Arena::Run()
{
    while (gameInProgres == 1)
    {
        Update();
        ProcessEvents();
        Render();
    }
    return 0;
}

void Arena::ProcessEvents()
{
    static bool mKeyWasPressed = false;
    static bool spaceKeyPressed = false;
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }

    if (player1.GetLiveState() || player2.GetLiveState())
    {
        gameInProgres = 0;
    }

    //! Manejar la entrada del teclado Player 1

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        if (!mKeyWasPressed && player1.GetDashAvailable() && !player1.GetDashState())
        {
            player1.StartDash();
            player1.Dash(4.0f);
            player1.IncreaseDashCounter();
        }
        mKeyWasPressed = true;
    }
    else
    {
        mKeyWasPressed = false;
    }

    if (player1.GetDashState())
    {
        spt1 = 1;
        row1 = 0;
    }
    else
    {
        spt1 = 0;
        row1 = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        row1 = 0;
    }

    // Limitar la velocidad máxima del jugador 1
    b2Vec2 velocity1 = player1.GetBody()->GetLinearVelocity();
    if (abs(velocity1.x) > desiredSpeed && !player1.GetDashState())
    {
        velocity1.x = (velocity1.x > 0 ? 1 : -1) * desiredSpeed; // Ajusta la velocidad en X manteniendo el signo
        player1.GetBody()->SetLinearVelocity(velocity1);         // Aplicar la velocidad limitada al jugador
    }
    if (velocity1.y > -10.0f)
    {
        player1.GetBody()->ApplyForceToCenter(b2Vec2(0.0f, 10.0f), true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !player1.GetDashState()) // El evento al que responde
        player1.GetBody()->ApplyLinearImpulse(
            b2Vec2(-0.5f, 0), // Fuerza que se aplica
            player1.GetBody()->GetWorldCenter(),
            true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !player1.GetDashState()) // El evento al que responde
        player1.GetBody()->ApplyLinearImpulse(
            b2Vec2(0.5f, 0), // Fuerza que se aplica
            player1.GetBody()->GetWorldCenter(),
            true);
    if (contactListener.GetIsPlayer1OnGround())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // El evento al que responde
            player1.GetBody()->ApplyLinearImpulse(
                b2Vec2(0, -3.5f), // Fuerza que se aplica
                player1.GetBody()->GetWorldCenter(),
                true);
    }

    //! Manejar la entrada del teclado Player 2

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!spaceKeyPressed && player2.GetDashAvailable() && !player2.GetDashState())
        {
            player2.StartDash();
            player2.Dash(4.0f);
            player2.IncreaseDashCounter();
        }
        spaceKeyPressed = true;
    }
    else
    {
        spaceKeyPressed = false;
    }

    if (player2.GetDashState())
    {
        spt2 = 1;
        row2 = 0;
    }
    else
    {
        spt2 = 0;
        row2 = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        row2 = 0;
    }

    // Limitar la velocidad máxima del jugador 2

    b2Vec2 velocity2 = player2.GetBody()->GetLinearVelocity();
    if (abs(velocity2.x) > desiredSpeed && !player2.GetDashState())
    {
        velocity2.x = (velocity2.x > 0 ? 1 : -1) * desiredSpeed; // Ajusta la velocidad en X manteniendo el signo
        player2.GetBody()->SetLinearVelocity(velocity2);         // Aplicar la velocidad limitada al jugador
    }
    if (velocity2.y > -10.0f)
    {
        player2.GetBody()->ApplyForceToCenter(b2Vec2(0.0f, 10.0f), true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !player2.GetDashState()) // El evento al que responde
        player2.GetBody()->ApplyLinearImpulse(
            b2Vec2(-0.5f, 0), // Fuerza que se aplica
            player2.GetBody()->GetWorldCenter(),
            true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !player2.GetDashState()) // El evento al que responde
        player2.GetBody()->ApplyLinearImpulse(
            b2Vec2(0.5f, 0), // Fuerza que se aplica
            player2.GetBody()->GetWorldCenter(),
            true);

    if (contactListener.GetIsPlayer2OnGround())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // El evento al que responde
            player2.GetBody()->ApplyLinearImpulse(
                b2Vec2(0, -3.5f), // Fuerza que se aplica
                player2.GetBody()->GetWorldCenter(),
                true);
    }

    //! Respawn de los jugadores o choque de espadas
    if (contactListener.GetArePlayersInContact() && player2.GetDashState() && player1.GetDashState())
    {
        // Si ambos jugadores están dashing hacia el otro, aplicar un impulso para separarlos
        if ((velocity2.x > 0.0f && velocity1.x < 0.0f) || (velocity2.x < 0.0f && velocity1.x > 0.0f))
        {
            // Aplicar un impulso hacia afuera basado en la dirección de cada jugador
            b2Vec2 impulseToPlayer2 = player2.GetBody()->GetWorldCenter() - player1.GetBody()->GetWorldCenter();
            impulseToPlayer2.Normalize(); // Normalizar para obtener solo la dirección
            impulseToPlayer2 *= 4.0f;     // Ajustar la magnitud del impulso

            b2Vec2 impulseToPlayer1 = -impulseToPlayer2; // Impulso opuesto para el otro jugador

            player2.GetBody()->ApplyLinearImpulse(impulseToPlayer2, player2.GetBody()->GetWorldCenter(), true);
            player1.GetBody()->ApplyLinearImpulse(impulseToPlayer1, player1.GetBody()->GetWorldCenter(), true);
        }
    }
    else
    {
        if (contactListener.GetArePlayersInContact() && player1.GetDashState())
        {
            player2.Reset(world, 200.0f, 100.0f, 50.0f, 50.0f, &player2TextureRunIdle, &player2TextureJumpDash);
            player2.GetBody()->GetUserData().pointer = static_cast<uintptr_t>(3); // Identificador del jugador 2
        }

        if (contactListener.GetArePlayersInContact() && player2.GetDashState())
        {
            player1.Reset(world, 1000.0f, 100.0f, 50.0f, 50.0f, &player1TextureRunIdle, &player1TextureJumpDash);
            player1.GetBody()->GetUserData().pointer = static_cast<uintptr_t>(1); // Identificador del jugador 2
        }
    }

    if (velocity1.x > 0)
    {
        right1 = true;
    }
    else
    {
        right1 = false;
    }

    if (velocity2.x > 0)
    {
        right2 = true;
    }
    else
    {
        right2 = false;
    }
}

void Arena::Update()
{
    // Avanzar la simulación de Box2D
    world.Step(1.0f / 60.0f, 6, 2);
    player1.Update(spt1, row1, 0.0f, right1);
    player2.Update(spt2, row2, 0.0f, right2);

    if (player1.GetDashState())
    {
        player1.SetDashState();
    }

    if (player1.GetDashCounter() >= 2 && !player1.GetDashState())
    {
        // std::cout << "Cooldown\n";
        player1.StartCoolDown();
    }

    if (!player1.GetDashAvailable())
    {
        player1.SetCoolDown();
    }

    if (player2.GetDashState())
    {
        player2.SetDashState();
    }

    if (player2.GetDashCounter() >= 2 && !player2.GetDashState())
    {
        // std::cout << "Cooldown\n";
        player2.StartCoolDown();
    }

    if (!player2.GetDashAvailable())
    {
        player2.SetCoolDown();
    }
}

void Arena::Render()
{
    window->clear();

    // Dibujar el fondo (no cambia, por lo que no se actualiza)
    window->draw(fondoSprite);

    // Dibujar el frente dinámico
    ground.Draw(*window); // Dibujar el suelo
    player1.Draw(spt1, *window);
    player2.Draw(spt2, *window);

    window->display();
}
