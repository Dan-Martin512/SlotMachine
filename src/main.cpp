#include <SFML/Graphics.hpp>
#include "include/SlotMachine/SlotMachine.h"
#include "include/SlotMachine/ResourceManager.h"
#include <windows.h>
#include <iostream>



int main()
{
    HWND hWnd = GetConsoleWindow();
       
    
    MySlotMachine::ResourceManager *rManager = new MySlotMachine::ResourceManager;
    std::cout << "Loading Textures..." << std::endl;
    rManager->loadFont("arial", "obj/arial.ttf");
    rManager->loadTexture("chassis", "obj/chassis.png");
    rManager->loadTexture("lemon", "obj/lemon.png");
    rManager->loadTexture("bar", "obj/bar.png");
    rManager->loadTexture("bell", "obj/bell.png");
    rManager->loadTexture("cherry", "obj/cherry.png");
    rManager->loadTexture("dollar", "obj/dollar.png");
    rManager->loadTexture("jackpot", "obj/Jackpot.png");
    rManager->loadTexture("lose", "obj/lose.png");
    rManager->loadTexture("seven", "obj/seven.png");
    std::cout << "Textures loaded" << std::endl;

    MySlotMachine::SlotMachine *machine = new MySlotMachine::SlotMachine(*rManager);

   
    ShowWindow( hWnd, SW_HIDE );
    sf::RenderWindow window(sf::VideoMode(650, 800), "Slot Machine");
    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            // pass event to machine to check for machine relevant events
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            machine->eventsHandler(&event, mouse);
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything
        machine->draw(&window);  

        // update the screen
        window.display();
    }

    //cleanup
    delete machine;
    delete rManager;

    return 0;
}
