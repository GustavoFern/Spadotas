#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Player
{
public:
    Player(b2World &world, float x, float y, float width, float height) : dashCounter(0), dashAvailable(true), isDashing(false)
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
        fixtureDef.density = 0.15f;
        fixtureDef.friction = 0.9f;
        body->CreateFixture(&fixtureDef);

        // Definir la forma en SFML
        shape.setSize(sf::Vector2f(width, height));
        shape.setOrigin(width / 2, height / 2);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);
    }

    //! Método para dibujar el jugador
    void draw(sf::RenderWindow &window)
    {
        // Obtener la posición del jugador
        b2Vec2 position = body->GetPosition();

        // Actualizar la posición de la forma en SFML
        shape.setPosition(position.x * 30.0f, position.y * 30.0f);

        // Dibujar la forma
        window.draw(shape);
    }

    //! Metodo para iniciar el dash
    void startDash()
    {
        if (!isDashing) // Asegurarse de que no estamos ya en un dash
        {
            isDashing = true;
            dashDurationTimer.restart(); // Iniciar el temporizador al comenzar el dash
            //std::cout << "Dashing\n";
        }
    }

    //! Metodo para iniciar el cooldawn
    void startCoolDown(){
        dashAvailable = false; // Habilitar el dash
        dashCounter = 0;      // Reiniciar el contador
        dashTimer.restart();  // Reiniciar el temporizador
    }

    //! Metodo para actualizar el estado del dash
    void update()
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
        if (dashTimer.getElapsedTime().asSeconds() >= 15.0f)
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
    void reset(b2World &world, float x, float y, float width, float height)
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
        fixtureDef.friction = 0.9f;
        body->CreateFixture(&fixtureDef);

        // Definir la forma en SFML
        shape.setSize(sf::Vector2f(width, height));
        shape.setOrigin(width / 2, height / 2);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);

        dashCounter = 0; // Reiniciar el contador
        dashTimer.restart();
        dashDurationTimer.restart();
        dashAvailable = true;
        isDashing =false;
    }

    //! Métodos para acceder/modificar el contador y el temporizador
    int getDashCounter() const
    {
        return dashCounter;
    }

    void increaseDashCounter()
    {
        dashCounter++;
        //std::cout << "\nDash counter increased" << dashCounter;
    }

    bool isDashAvailable()
    {
        return dashAvailable;
    }

    bool isPlayerDashing()
    {
        return isDashing;
    }

private:
    b2Body *body;
    sf::RectangleShape shape;
    sf::Clock dashTimer, dashDurationTimer;
    int dashCounter;
    bool dashAvailable;
    bool isDashing;
};