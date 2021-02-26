#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>

#include "ResourceManager.h"
#include "Reel.h"


#ifndef SlotMachine_H
#define SlotMachine_H




namespace MySlotMachine{
        
    class SlotMachine {

    private:
        float moneyPlundered = 0;
        float totalWinnings = 0;
        float money;
        float cost;
        bool running = true;
        bool rolling = false;
        float lastWin = 0;
        sf::Text txt_funds;
        sf::Text txt_winner;
        sf::Text txt_clickme;
        sf::Sprite sprite;
        std::random_device seed;

        Reel reel1 = Reel( 1, sf::Vector2i( 120,20 ), seed(), true ); 
        Reel reel2 = Reel( 2, sf::Vector2i( 220,20 ), seed(), false );
        Reel reel3 = Reel( 3, sf::Vector2i( 320,20 ), seed(), true );

        void payRound()
        { 
            moneyPlundered += cost;
            money -= cost;
            std::cout << cost << "£ deducted from funds" << std::endl; 
        };

        bool checkFunds() 
        {
            if (money > cost)
                return true;
            return false;
        };

        void checkWin(){
            //check rows 3, 4, 5 for win horizontal and diagonal
            // add prize funds
            lastWin = 0;
            // check reels here

            if (compareItems(*reel1.getItem(3), *reel2.getItem(3), *reel3.getItem(3))){
                lastWin += reel1.getPrizeAt(3);
            }
            else if (compareItems(*reel1.getItem(4), *reel2.getItem(4), *reel3.getItem(4))){
                lastWin += reel1.getPrizeAt(4);
            }
            else if (compareItems(*reel1.getItem(5), *reel2.getItem(5), *reel3.getItem(5))){
                lastWin += reel1.getPrizeAt(5);
            }
            else if (compareItems(*reel1.getItem(3), *reel2.getItem(4), *reel3.getItem(5))){
                lastWin += reel1.getPrizeAt(3);
            }
            else if (compareItems(*reel1.getItem(5), *reel2.getItem(4), *reel3.getItem(3))){
                lastWin += reel1.getPrizeAt(5);
            }


            money += lastWin;
            totalWinnings += lastWin;
        }

        bool compareItems( ReelItem r1, ReelItem r2, ReelItem r3){
            return r1.getName() == r2.getName() && r2.getName() == r3.getName();
        }

    public:
        // constructor
        SlotMachine(ResourceManager&);
        ~SlotMachine();

        // methods
        void addMoney(float _money);
        void pullHandle();
        void reset();
        void cashOut();
        void draw(sf::RenderWindow*);
        float getMoney() { return money;};
        void eventsHandler(sf::Event*, sf::Vector2i);
    };

};
#endif