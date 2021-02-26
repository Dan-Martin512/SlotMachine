#include <iostream>
#include "include/SlotMachine/ResourceManager.h"


using namespace MySlotMachine;

void ResourceManager::loadTexture( std::string name, std::string texture_file){

    sf::Texture tmp_texture;

    if(tmp_texture.loadFromFile( texture_file ))
        this->_textures[name] = tmp_texture;
}

sf::Texture &ResourceManager::getTexture( std::string name ){
    return this->_textures.at( name );
}


void ResourceManager::loadFont( std::string name, std::string font_file){

    sf::Font tmp_font;

    if(tmp_font.loadFromFile( font_file ))
        this->_fonts[name] = tmp_font;
}

sf::Font &ResourceManager::getFont( std::string name ){
    return this->_fonts.at( name );
}