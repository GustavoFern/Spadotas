#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "animation.hpp"

class Player
{
public:
    Player() {}
    Player(b2World &world, float x, float y, float width, float height, sf::Texture *texture1, sf::Texture *texture2) : dashCounter(0), lives(5), dashAvailable(true), isDashing(false)
    {
        runIdle = Animation(texture1, sf::Vector2u(3, 2), 0.3f);
        jumpDash = Animation(texture2, sf::Vector2u(9, 2), 0.11f);
        // Definir el cuerpo dinámico en Box2D
        b2BodyDef bodyDef;
        bodyDef.position.Set(x / 30.0f, y / 30.0f);
        bodyDef.type = b2_dynamicBody;
        body = world.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(width / 2 / 30.0f, height / 2 / 30.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 0.15f;
        fixtureDef.friction = 0.7f;
        body->CreateFixture(&fixtureDef);

        // Definir la forma en SFML
        sprite1.setTexture(*texture1);
        sprite1.setOrigin(width / 2, height / 2);
        sprite1.setPosition(x, y);

        sprite2.setTexture(*texture2);
        sprite2.setOrigin(width / 2, height / 2);
        sprite2.setPosition(x, y);
    }

    //! Método para dibujar el jugador
    void draw(int spt, sf::RenderWindow &window)
    {
        // Actualizar la posición del sprite
        b2Vec2 position = body->GetPosition();
        sprite1.setPosition(position.x * 30.0f, position.y * 30.0f);
        sprite2.setPosition(position.x * 30.0f, position.y * 30.0f);

        if (spt == 0)
        {
            // Dibujar el sprite
            window.draw(sprite1);
        }

        if (spt == 1)
        {
            window.draw(sprite2);
        }
    }

    //! Actualizador de animacion
    void update(int spt, int row, float deltaTime)
    {
        deltaTime = clock.restart().asSeconds();
        if (spt == 0)
        {
            // Actualizar la animación
            runIdle.Update(row, deltaTime); // Asumiendo que la fila 0 es la animación deseada

            // Actualizar el rectángulo de textura del sprite
            sprite1.setTextureRect(runIdle.uvRect);
        }

        if (spt == 1)
        {
            // Actualizar la animación
            jumpDash.Update(row, deltaTime); // Asumiendo que la fila 0 es la animación deseada

            // Actualizar el rectángulo de textura del sprite
            sprite2.setTextureRect(jumpDash.uvRect);
        }
    }

    //! Metodo para iniciar el dash
    void startDash()
    {
        if (!isDashing) // Asegurarse de que no estamos ya en un dash
        {
            isDashing = true;
            dashDurationTimer.restart(); // Iniciar el temporizador al comenzar el dash
            // std::cout << "Dashing\n";
        }
    }

    //! Metodo para iniciar el cooldawn
    void startCoolDown()
    {
        dashAvailable = false; // Habilitar el dash
        dashCounter = 0;       // Reiniciar el contador
        dashTimer.restart();   // Reiniciar el temporizador
    }

    //! Metodo para actualizar el estado del dash
    void dashState()
    {
        if (isDashing && dashDurationTimer.getElapsedTime().asSeconds() >= 1.0f)
        {
            // std::cout << "Is not Dashing\n";
            isDashing = false;
        }
        // No es necesario establecer isDashing a true aquí, ya que eso se maneja en startDash
    }

    //! Método para inicializar el temporizador del dash
    void coolDown()
    {
        if (dashTimer.getElapsedTime().asSeconds() >= 5.0f)
        {
            std::cout << "Dash available\n";
            dashAvailable = true; // Habilitar el dash
        }
    }

    //! Método para acceder al cuerpo del jugador
    b2Body *getBody()
    {
        return body;
    }

    //! Método para realizar un dash
    void dash(float dashForce)
    {
        // Obtener la dirección en la que el jugador está mirando o quiere desplazarse
        b2Vec2 direction = body->GetLinearVelocity();
        direction.Normalize(); // Asegurarse de que la dirección es un vector unitario
                               // Aplicar un impulso en esa dirección
        if (direction.x > 0.0f)
            body->ApplyLinearImpulseToCenter(b2Vec2(dashForce, 0.0f), true);
        if (direction.x < 0.0f)
            body->ApplyLinearImpulseToCenter(b2Vec2(-dashForce, 0.0f), true);
    }

    //! Método para reiniciar el jugador
    void reset(b2World &world, float x, float y, float width, float height, sf::Texture *texture1, sf::Texture *texture2)
    {
        // Primero, destruye el cuerpo actual si existe
        if (body != nullptr)
        {
            world.DestroyBody(body);
            body = nullptr; // Asegúrate de invalidar el puntero después de destruir el cuerpo
        }

        // Definir el cuerpo dinámico en Box2D
        b2BodyDef bodyDef;
        bodyDef.position.Set(x / 30.0f, y / 30.0f);
        bodyDef.type = b2_dynamicBody;
        body = world.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(width / 2 / 30.0f, height / 2 / 30.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 0.15f;
        fixtureDef.friction = 0.5f;
        body->CreateFixture(&fixtureDef);

        // Definir la forma en SFML
        sprite1.setTexture(*texture1);
        sprite1.setOrigin(width / 2, height / 2);
        sprite1.setPosition(x, y);

        sprite2.setTexture(*texture2);
        sprite2.setOrigin(width / 2, height / 2);
        sprite2.setPosition(x, y);

        dashCounter = 0; // Reiniciar el contador
        dashTimer.restart();
        dashDurationTimer.restart();
        dashAvailable = true;
        isDashing = false;
        lives--;
        // std::cout << lives << std::endl;
    }

    //! Métodos para acceder/modificar el contador y el temporizador
    int getDashCounter() const
    {
        return dashCounter;
    }

    void increaseDashCounter()
    {
        dashCounter++;
        // std::cout << "\nDash counter increased" << dashCounter;
    }

    bool isDashAvailable()
    {
        return dashAvailable;
    }

    bool isPlayerDashing()
    {
        return isDashing;
    }

    bool AreYouLive()
    {
        return lives == 0;
    }

private:
    b2Body *body;
    sf::Sprite sprite1, sprite2;
    Animation runIdle, jumpDash;
    sf::Clock dashTimer, dashDurationTimer, clock;
    int dashCounter, lives;
    bool dashAvailable;
    bool isDashing;
};