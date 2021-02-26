#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>


#ifndef ResourceManager_H
#define ResourceManager_H

namespace MySlotMachine{

    class ResourceManager{
        private:
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _fonts;

        public:
            ResourceManager() { }
            ~ResourceManager() { }
            
            void loadTexture( std::string name, std::string texture_file);
            sf::Texture &getTexture( std::string name );

            void loadFont( std::string name, std::string font_file);
            sf::Font &getFont( std::string name );

    };

}

#endif
