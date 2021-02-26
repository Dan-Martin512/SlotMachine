#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "ReelItem.h"
#include "ResourceManager.h"

#ifndef Reel_H
#define Reel_H


namespace MySlotMachine{
        
    class Reel {

    private:
        int reelNum;
        bool rolling = false;
        int rollCount = 0;
        bool spinPolarity = false;
        
        sf::Vector2i position;
        std::vector<ReelItem*> items;
        unsigned int seed = 0;
        
        ReelItem lemon = ReelItem("lemon", 0.10);
        ReelItem cherry = ReelItem("cherry", 0.50);
        ReelItem dollar = ReelItem("dollar", 1);
        ReelItem bar = ReelItem("bar", 1.50);
        ReelItem seven = ReelItem("seven", 2);
        ReelItem bell = ReelItem("bell", 3);
        ReelItem jackpot = ReelItem("jackpot", 5);
        ReelItem lose = ReelItem("lose", 0);
        
        
    public:
        // constructors
        Reel() {}
        Reel( int, sf::Vector2i, unsigned int, bool );

        // methods
        void loadTextures(ResourceManager &);
        void draw(sf::RenderWindow*, int, int );
        void spin(bool);
        void roll();

        // getters
        std::vector<ReelItem*> getItems() { return items; };
        ReelItem* getItem(int reelSlot){ return items.at(reelSlot); }
        float getPrizeAt(int pos) { return items.at(pos)->getPrize(); };
        bool isRolling() { return rolling; };
    };
};

#endif