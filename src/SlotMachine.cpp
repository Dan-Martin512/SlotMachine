#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <iterator>
#include <cmath>
#include <chrono>
#include "include/SlotMachine/SlotMachine.h"

using namespace MySlotMachine;

SlotMachine::SlotMachine(ResourceManager &rManager){
    money = 0.0;
    cost = 0.10;
    std::cout << "--> Powering on Slot Machine" << std::endl;
    addMoney(5);
    txt_funds.setFont( rManager.getFont("arial") );  
    txt_funds.setCharacterSize(17);
    txt_funds.setPosition(260, 225);
    txt_funds.setFillColor(sf::Color::White);

    txt_clickme.setFont( rManager.getFont("arial") );  
    txt_clickme.setCharacterSize(16);
    txt_clickme.setPosition(575, 225);
    txt_clickme.setString("Click Me");
    txt_clickme.setFillColor(sf::Color::White);

    txt_winner.setFont( rManager.getFont("arial") );  
    txt_winner.setCharacterSize(30);
    txt_winner.setPosition(160, 190);
    txt_winner.setFillColor(sf::Color::White);

    reel1.loadTextures( rManager );
    reel2.loadTextures( rManager );
    reel3.loadTextures( rManager );
    sprite.setTexture( rManager.getTexture("chassis") );
    std::cout<< "--> Machine Ready!" << std::endl;
};

SlotMachine::~SlotMachine(){
};

void SlotMachine::addMoney(float _money){
    std::cout << "Adding funds.." << std::endl;
    money += _money;
    std::cout << "\x9C" << _money << " added" << std::endl;
};

void SlotMachine::pullHandle(){

    // check not already spinning
    if (rolling){
        std::cout << "still rolling...." << std::endl;
        return;
    }

    // check if enough funds in machine
    if (!checkFunds()){
        std::cout << "Not enough funds" << std::endl;
        return;
    }


    // remove cost of spin from machine funds
    payRound();

    // spin wheels
    std::cout << "Spinning wheels......" << std::endl;
    rolling = true;
    reel1.roll();
    reel2.roll();
    reel3.roll();  

}

void SlotMachine::draw(sf::RenderWindow *window){
    window->draw( sprite );
    reel1.draw( window, 3, 6 );
    reel2.draw( window, 3, 6 );
    reel3.draw( window, 3, 6 );

    std::string tmp_str = "Funds: \xA3";
    tmp_str += std::to_string( money );
    std::string rounded = tmp_str.substr(0, tmp_str.find(".")+3);
    txt_funds.setString( rounded);

    if (lastWin > 0.01){
        if (lastWin == 5){
            txt_winner.setString("\x24\x24 JACKPOT \x24\x24");
        }else{
            txt_winner.setString("  -- WINNER --  ");
        }
        window->draw( txt_winner );
    }

    window->draw( txt_funds );
    window->draw( txt_clickme );

    if (!reel1.isRolling() && !reel2.isRolling() && !reel3.isRolling()){
        if (rolling){
            checkWin();
            std::cout << "Winnings = " << lastWin << std::endl;
        }
        rolling = false;
    }
}

void SlotMachine::cashOut(){
    float profit = totalWinnings - moneyPlundered;
    std::roundf(profit);

    std::cout << std::endl << "Money plundered: \x9C" << moneyPlundered << " Total Profit: \x9C" << profit;
    
    if (profit < 0)
    {
        std::cout << " Gambling doesnt pay, dont give up your day job!!!!!" ;
    }
    else if (profit > 10)
    {
        std::cout << " Good game!!" ;
        
    }
    
    std::cout << std::endl;
}

void SlotMachine::eventsHandler(sf::Event* event, sf::Vector2i mouse){

    if (event->type == sf::Event::KeyReleased)
        if (event->key.code == sf::Keyboard::Numpad1)
            addMoney(1);
        if (event->key.code == sf::Keyboard::Numpad2)
            pullHandle();
        if (event->key.code == sf::Keyboard::Numpad3)
            cashOut();

    if (event->type == sf::Event::MouseButtonPressed){

        sf::Vector2i handle(600, 230);
        sf::Vector2i handle_dif = handle - mouse;

        float dist = std::sqrt( std::pow(handle_dif.x, 2) + std::pow(handle_dif.y, 2) );

        if (dist < 40){
            pullHandle();
        }
        
    }
    
}