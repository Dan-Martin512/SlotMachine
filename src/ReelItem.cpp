#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/SlotMachine/ReelItem.h"
#include "include/SlotMachine/ResourceManager.h"


using namespace MySlotMachine;

ReelItem::ReelItem( std::string _name, sf::Texture &texture )
    {
        name = _name;
        sprite.setTexture( texture );
    }

ReelItem::ReelItem( std::string _name, float _prize)
    {
        name = _name;
        prize = _prize;
    }

ReelItem::ReelItem( std::string _name)
    {
        name = _name;
    }

void ReelItem::draw( sf::RenderWindow *window ){
    window->draw( sprite );
}

void ReelItem::setPosition( float x, float y ){
    sprite.setPosition( x, y );
}

void ReelItem::setTexture(sf::Texture &text){
    this->sprite.setTexture( text ); 
} 