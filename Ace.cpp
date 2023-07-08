#include <iostream>
#include <cstdlib>
#include<ctime>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include"Classes.h"
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//Using handle function
COORD CursorPosition;
using namespace std;
using namespace sf;
int points=0;


bool checkPowerUp(Vector2f pellet)//Function to check Power up
{
        if (pellet.x == 0 && pellet.y == 0)
        {
                return true;
        }
        else
                return false;
}
void eat(sf::Vector2f pelletPos[], sf::Vector2f heroPos, int size)//Function to Eat pellets
{
        for (int i = 0; i < size; i++)
        {
                if ((pelletPos[i].x >= heroPos.x-10 && pelletPos[i].x <= heroPos.x + 50) && (pelletPos[i].y >= heroPos.y-10 && pelletPos[i].y <= heroPos.y + 50))
                {
                        pelletPos[i].x = 0;
                        pelletPos[i].y = 0;
                        points++;
                }
        }
}
bool collision(sf::Vector2f enemyPos[],sf::Vector2f heroPos,int size)//Function to check collision
{
        for (int i = 0; i < size; i++)
        {
                if ((enemyPos[i].x >= heroPos.x-15&& enemyPos[i].x <= heroPos.x+40)&& (enemyPos[i].y >= heroPos.y-20 && enemyPos[i].y <= heroPos.y + 40))
                {
                        return true;
                }
        }
        return false;
}
int start()//Function to ask player to start game(used from previous project)
{
        int option;
        system("cls");
        SetConsoleTextAttribute(hStdOut, 3);//Changing Colors
        cout << "\n\n\n\t\t\t-------------------------\n";
        cout << "\t\t\t|      WELCOME TO       |\n";
        cout << "\t\t\t|        Pac Man        |\n";
        cout << "\t\t\t-------------------------\n";
        SetConsoleTextAttribute(hStdOut, 9);//Changing Colors
        cout << "\n\n\t\t\tBy\n\t\t\tAbdul Rafay(21L-5497)\n";
        SetConsoleTextAttribute(hStdOut, 8);//Changing Colors
        cout << "\n\t\t\tPress 1 to play \n\t\t\tPress 0 to exit\n\t\t\t";
        SetConsoleTextAttribute(hStdOut, 7);//Changing Colors
        cin >> option;
        return option;
}
int main() 
{
        int option;
        option = start();
        if (option != 1)
        {
                system("cls");
                cout << "Thankyou for Exiting\n";
                return 0;
        }
        system("cls");
        RenderWindow window(VideoMode(1280, 720), "Gamescreen");//Window for game screen
        window.setFramerateLimit(60);//Setting Fps(frames per second of the window)
        points = 0;//Points in Game
        int power = 0;//Vairable for power up boost


        //Making Of Hero
        Hero hero;//Object of Hero
        sf::Texture heroTexture;//Object for hero texture
        heroTexture.loadFromFile("D:\\SFML Template\\sfml_template\\icons\\hero R.png");
        hero.setTexture(&heroTexture);
        sf::Vector2f heroPos(50, 50);//Setting initial position of hero
        hero.setpos(heroPos);
        float heroVelocityX = 0, heroVelocityY = 0;//float variables for velocity of hero


        //Making of Enemies
        Enemy enemy[3];//Object of enemy
        sf::Vector2f enemyPos[3];
        float enemyVelocityX[3], enemyVelocityY[3];
        sf::Texture enemyTexture[3];
        enemyTexture[0].loadFromFile("D:\\SFML Template\\sfml_template\\icons\\enemy red.jpg");
        enemyTexture[1].loadFromFile("D:\\SFML Template\\sfml_template\\icons\\enemy green.png");
        enemyTexture[2].loadFromFile("D:\\SFML Template\\sfml_template\\icons\\enemy pink.jpg");
        for (int i = 0; i < 3; i++)
        {
                enemyPos[i].x = 620;
                enemyPos[i].y = 340;
                enemyVelocityX[i] = 0;
                enemyVelocityY[i] = 0;
                enemy[i].setTexture(&enemyTexture[i]);//Setting Texture
        }


        //MAZE
        Maze block[5];//Object of block for maze
        for (int i = 0; i < 2; i++)//Blocks on X axis
        {
                block[i].setSize(sf::Vector2f(1280, 50));
        }
        for (int i = 2; i < 4; i++)//Blocks on Y Axis
        {
                block[i].setSize(sf::Vector2f(50, 720));
        }
        block[4].setSize(sf::Vector2f(300, 210));//Blocks inside maze
        block[0].setpos(sf::Vector2f(0, 0));
        block[2].setpos(sf::Vector2f(1230, 0));
        block[3].setpos(sf::Vector2f(0, 0));
        block[1].setpos(sf::Vector2f(0, 670));


        //Pellets
        Pellet pellet[29];//Object for pellets
        sf::Vector2f pelletPos[29];
        for (int i = 0; i < 29; i++)
        {
                pellet[i].setRadius(5);
                
        }
        for (int i = 0; i < 9; i++)
        {
                pelletPos[i].x = (120 + (i * 130));
                pelletPos[i].y = 65;
                pellet[i].setpos(pelletPos[i]);
                pelletPos[i+9].x = (120 + (i * 130));
                pelletPos[i+9].y = 340;
                pellet[i+9].setpos(pelletPos[i+9]);
                pelletPos[i+18].x = (120 + (i * 130));
                pelletPos[i+18].y = 620;
                pellet[i+18].setpos(pelletPos[i+18]);
        }
        for (int i = 0; i < 2; i++)
        {
                pellet[27 + i].setRadius(7.5);
                pelletPos[27 + i].x = 428 + (i * 400);
                pelletPos[27 + i].y = 250;
                pellet[27 + i].setpos(pelletPos[27 + i]);
        }
        
        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)window.close();


                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();//Condition to close the game when Esc is pressed


                }


                //BOUNDARY CONDITIONS
                if ((heroVelocityX == -2 && heroPos.x <= 50) || (heroVelocityX == 2 && heroPos.x >= 1180))//Condition To stop hero from exeeding boundaries of X axis
                {
                        heroVelocityX = 0;
                }
                if ((heroVelocityY == -2 && heroPos.y <= 50) || (heroVelocityY == 2 && heroPos.y >= 620))//Condition to stop hero from exeeding boundaries of Y axis
                {
                        heroVelocityY = 0;
                }
                
                //MOVEMENT KEYCONDITIONS
                if (heroPos.x == 50 || (heroPos.x >= 415&&heroPos.x<=435) || (heroPos.x >= 785 && heroPos.x <= 825) || heroPos.x == 1180)
                {
                        if (!(heroPos.y <= 50))//Check for boundary
                        {
                                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//condition for up key 
                                        {
                                                heroTexture.loadFromFile("D:\\SFML Template\\sfml_template\\icons\\hero up.png");
                                                heroVelocityY = -2;
                                                heroVelocityX = 0;
                                        }
                        }
                        if (!(heroPos.y >= 620))//Check for boundary
                        {
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//condition for Down key 
                                {
                                        heroTexture.loadFromFile("D:\\SFML Template\\sfml_template\\icons\\hero down.png");
                                        heroVelocityY = +2;
                                        heroVelocityX = 0;
                                }
                        }
                }
                if (heroPos.y == 50 || (heroPos.y >= 318 && heroPos.y <= 345) || (heroPos.y>=618&&heroPos.y <=620))
                {
                        if (!(heroPos.x >= 1180))//Check for boundary
                        {
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//condition for Right key  
                                {
                                        heroTexture.loadFromFile("D:\\SFML Template\\sfml_template\\icons\\hero R.png");
                                        heroVelocityY = 0;
                                        heroVelocityX = +2;
                                }
                        }
                        if (!(heroPos.x <= 50))//Check for boundary
                        {
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//condition for Left key  
                                {
                                        heroTexture.loadFromFile("D:\\SFML Template\\sfml_template\\icons\\hero L.png");
                                        heroVelocityY = 0;
                                        heroVelocityX = -2;
                                }
                        }
                }


                //MOVEMENT OF enemy
                srand(time(0));
                for (int i = 0; i < 3; i++)
                {
                        if ((enemyVelocityX[i] == -2 && enemyPos[i].x <= 50) || (enemyVelocityX[i] == 2 && enemyPos[i].x >= 1180))//Condition To stop hero from exeeding boundaries of X axis
                        {
                                enemyVelocityX[i] = 0;
                        }
                        if ((enemyVelocityY[i] == -2 && enemyPos[i].y <= 50) || (enemyVelocityY[i] == 2 && enemyPos[i].y >= 620))//Condition to stop hero from exeeding boundaries of Y axis
                        {
                                enemyVelocityY[i] = 0;
                        }
                        
                        if (enemyPos[i].x == 50 || (enemyPos[i].x >= 415 && enemyPos[i].x <= 435) || (enemyPos[i].x >= 785 && enemyPos[i].x <= 825) || enemyPos[i].x == 1180)
                        {
                                if (!(enemyPos[i].y <= 50))//Check for boundary
                                {
                                        if (rand() % 4 == 0)//condition for up key 
                                        {
                                                enemyVelocityY[i] = -2;
                                                enemyVelocityX[i] = 0;
                                        }
                                }
                                if (!(enemyPos[i].y >= 620))//Check for boundary
                                {
                                        if (rand() % 4 == 1)//condition for Down key 
                                        {
                                                enemyVelocityY[i] = +2;
                                                enemyVelocityX[i] = 0;
                                        }
                                }
                        }
                        if (enemyPos[i].y == 50 || (enemyPos[i].y >= 318 && enemyPos[i].y <= 345) || (enemyPos[i].y >= 618 && enemyPos[i].y <= 620))
                        {
                                if (!(enemyPos[i].x >= 1180))//Check for boundary
                                {
                                        if (rand() % 4 == 2)//condition for Right key  
                                        {
                                                enemyVelocityY[i] = 0;
                                                enemyVelocityX[i] = +2;
                                        }
                                }
                                if (!(enemyPos[i].x <= 50))//Check for boundary
                                {
                                        if (rand() % 4 == 3)//condition for Left key  
                                        {
                                                enemyVelocityY[i] = 0;
                                                enemyVelocityX[i] = -2;
                                        }
                                }
                        }
                        enemyPos[i].x += enemyVelocityX[i];
                        enemyPos[i].y += enemyVelocityY[i];
                        enemy[i].setpos(enemyPos[i]);
                }


                heroPos.x += heroVelocityX;
                heroPos.y += heroVelocityY;
                hero.setTexture(&heroTexture);
                hero.setpos(heroPos);
                window.clear();


                //Printing Display


                //Pellet
                for (int i = 0; i < 29; i++)
                {
                        pellet[i].setpos(pelletPos[i]);
                        pellet[i].drawPellet(window);
                }


                //Blocks
                float x = 100,y=100;
                for (int i = 0; i < 3; i++)
                {
                        for (int j = 0; j < 2; j++)
                        {
                                block[4].setpos(sf::Vector2f(x, y));
                                block[4].drawBlock(window);
                                y = y + 295;
                        }
                        x = x + 385;
                        y = 100;
                }


                for (int i = 0; i < 4; i++)
                {
                        block[i].drawBlock(window);
                }


                //Enemies
                for (int i = 0; i < 3; i++)
                {
                        enemy[i].drawEnemy(window);
                }


                //Function to Eat pellets
                eat(pelletPos, heroPos, 29);


                //Condition To check power up
                if (checkPowerUp(pelletPos[28]))
                {
                        pelletPos[28].x = 1230;
                        pelletPos[28].y = 690;
                        power = 1;
                }
                if (checkPowerUp(pelletPos[27]))
                {
                        pelletPos[27].x = 1230;
                        pelletPos[27].y = 690;
                        power = 1;
                }
                
                //Hero
                hero.drawHero(window);
                window.display();


                //Collision Condition
                if (collision(enemyPos, heroPos,3))
                {
                        //Collision without power boost
                        if (power == 0)
                        {
                                window.clear();
                                block[4].setpos(sf::Vector2f(490, 255));
                                enemyTexture[0].loadFromFile("D:\\SFML Template\\sfml_template\\icons\\game over.png");
                                block[4].setTexture(&enemyTexture[0]);
                                block[4].drawBlock(window);
                                window.display();
                                cout << "POINTS: " << points << endl;
                                system("pause");
                        }
                        //Collision with power boost
                    else
                    {
                            for (int i = 0; i < 3; i++)
                            {
                                        if (collision(&enemyPos[i], heroPos, 1))
                                        {
                                                enemyPos[i].x = 1180;
                                                enemyPos[i].y = 620;
                                                power = 0;
                                        }
                            }
                    }
                }
                //Winning Condition
                if (points == 29)
                {
                        window.clear();
                        block[4].setpos(sf::Vector2f(490, 255));
                        enemyTexture[0].loadFromFile("D:\\SFML Template\\sfml_template\\icons\\win.png");
                        block[4].setTexture(&enemyTexture[0]);
                        block[4].drawBlock(window);
                        window.display();
                        cout << "POINTS: " << points << endl;
                        system("pause");
                }
        }
}