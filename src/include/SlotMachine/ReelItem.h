#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef ReelItem_H
#define ReelItem_H


namespace MySlotMachine{
        
    class ReelItem {

    private:
        sf::Sprite sprite;
        std::string name;
        float prize;

    public:
        //constructors
        ReelItem() {};
        ReelItem( std::string, sf::Texture & );
        ReelItem( std::string, float );
        ReelItem( std::string );

        // draw
        void draw( sf::RenderWindow*);
        
        //getters
        sf::Vector2f getPosition() { return sprite.getPosition(); };
        float getPrize() { return prize; };
        std::string getName() { return name; };

        //setters
        void setPosition( float, float );
        void setTexture(sf::Texture&);
        
    };
};

#endif