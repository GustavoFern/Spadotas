#pragma once

#include <iostream>
#include <Box2D/Box2D.h>
#include <cstdint>

class ContactListener : public b2ContactListener
{
public:
    ContactListener() : player1OnGround(false), player2OnGround(false) {}

    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;

    bool isPlayer1OnGround() const;
    bool isPlayer2OnGround() const;

private:
    bool player1OnGround;
    bool player2OnGround;
};

void ContactListener::BeginContact(b2Contact *contact)
{
    // std::cout << "BeginContact called" << std::endl;
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    b2Body *bodyA = fixtureA->GetBody();
    b2Body *bodyB = fixtureB->GetBody();

    uintptr_t bodyUserDataA = static_cast<uintptr_t>(bodyA->GetUserData().pointer);
    uintptr_t bodyUserDataB = static_cast<uintptr_t>(bodyB->GetUserData().pointer);

    if ((bodyUserDataA == static_cast<uintptr_t>(1) && bodyUserDataB == static_cast<uintptr_t>(2)) ||
        (bodyUserDataA == static_cast<uintptr_t>(2) && bodyUserDataB == static_cast<uintptr_t>(1)))
    {
        player1OnGround = true;
    }

    if ((bodyUserDataA == static_cast<uintptr_t>(3) && bodyUserDataB == static_cast<uintptr_t>(2)) ||
        (bodyUserDataA == static_cast<uintptr_t>(2) && bodyUserDataB == static_cast<uintptr_t>(3)))
    {
        player2OnGround = true;
    }
}

void ContactListener::EndContact(b2Contact *contact)
{
    // std::cout << "EndContact called" << std::endl;
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    b2Body *bodyA = fixtureA->GetBody();
    b2Body *bodyB = fixtureB->GetBody();

    uintptr_t bodyUserDataA = static_cast<uintptr_t>(bodyA->GetUserData().pointer);
    uintptr_t bodyUserDataB = static_cast<uintptr_t>(bodyB->GetUserData().pointer);

    if ((bodyUserDataA == static_cast<uintptr_t>(1) && bodyUserDataB == static_cast<uintptr_t>(2)) ||
        (bodyUserDataA == static_cast<uintptr_t>(2) && bodyUserDataB == static_cast<uintptr_t>(1)))
    {
        player1OnGround = false;
    }

    if ((bodyUserDataA == static_cast<uintptr_t>(3) && bodyUserDataB == static_cast<uintptr_t>(2)) ||
        (bodyUserDataA == static_cast<uintptr_t>(2) && bodyUserDataB == static_cast<uintptr_t>(3)))
    {
        player2OnGround = false;
    }
}

bool ContactListener::isPlayer1OnGround() const
{
    return player1OnGround;
}

bool ContactListener::isPlayer2OnGround() const
{
    return player2OnGround;
}