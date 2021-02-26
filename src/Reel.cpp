#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "include/SlotMachine/ResourceManager.h"
#include "include/SlotMachine/ReelItem.h"
#include "include/SlotMachine/Reel.h"


using namespace MySlotMachine;

Reel::Reel(int reelNumber, sf::Vector2i _position, unsigned int _seed, bool _spinPolarity ){

    reelNum = reelNumber;
    position = _position;
    spinPolarity = _spinPolarity;

    items.push_back(&lemon);
    items.push_back(&bell);
    items.push_back(&cherry);
    items.push_back(&bar);
    items.push_back(&jackpot);
    items.push_back(&lose);
    items.push_back(&seven);
    items.push_back(&dollar);
    seed = _seed;

    std::default_random_engine rng = std::default_random_engine(_seed);

    std::shuffle(items.begin(), items.end(), rng);

    for (int i = 0; i < 8; i++)
    {
        float tmp_y = position.y;
        if (i > 0)
            tmp_y = position.y + (i * 90);

        items.at(i)->setPosition( position.x, tmp_y);
    }
}

void Reel::loadTextures(ResourceManager &resourceMGR){
    lemon.setTexture( resourceMGR.getTexture("lemon") );
    cherry.setTexture( resourceMGR.getTexture("cherry") );
    dollar.setTexture( resourceMGR.getTexture("dollar") );
    bar.setTexture( resourceMGR.getTexture("bar") );
    bell.setTexture( resourceMGR.getTexture("bell") );
    jackpot.setTexture( resourceMGR.getTexture("jackpot") );
    lose.setTexture( resourceMGR.getTexture("lose") );
    seven.setTexture( resourceMGR.getTexture("seven") );
}

void Reel::spin(bool clockwise){

    // shift all items in vector by 1 forwards or backwards based on bool 

    if (clockwise){
        std::rotate(items.begin(), items.begin() + 1, items.end());
    }
    else{
        std::rotate(items.begin(), items.begin() + 7, items.end());
    }


    for (int i = 0; i < 8; i++)
    {
        float tmp_y = position.y;
        if (i > 0)
            tmp_y = position.y + (i * 90);

        items.at(i)->setPosition( position.x, tmp_y);
    }
}

void Reel::roll(){
    rolling = true;
    //rand int between 1200 and 1700
    rollCount = std::rand() %700 + 1000;
}

void Reel::draw(sf::RenderWindow *window, int begin, int end){
    
    if (rolling){
        if (rollCount < 1)
            rolling = false;
        
        if (rollCount % 70 == 0)
            spin(spinPolarity);

        rollCount --;
    }

    // draw items from begin(including) to end(not including)
    for (int i = begin; i < end; i++)
        items.at(i)->draw(window);
}



