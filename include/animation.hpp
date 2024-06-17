#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(){};
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime );
    ~Animation();

    void Update(int row, float deltaTime, bool faceRight);

public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    
    float totalTime;
    float switchTime;

};

//Declaracion de Metodos

// Metodo Constructor
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
   

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}
// Metodo Destructor
Animation::~Animation() {}

// Metodo Update
void Animation::Update(int row, float deltaTime, bool faceRight)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }

   
    uvRect.top = currentImage.y * uvRect.height;

    if (faceRight)
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else
    {
        uvrect.left = abs(currentImage.x + 1) * abs(uvRect.width);
        uvrect.width = -abs(uvRect.width);
    }
}
    
