//Nick Menendez
//CISP 400
//Final Project
//Genetic Algorithm Robots

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <ctime>

using namespace std;

class Map
{
private:
    int map[10][10];
    
public:
    Map()
    {
        //Create the initial grid with all 0's
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                map[i][j] = 0;
        //populate 40% of the map with batteries (9 represents a battery)
        for (int i = 0; i < 40; i++)
        {
            int x = rand() % 10;
            int y = rand() % 10;
            while (map[x][y] != 0)
            {
                x = rand() % 10;
                y = rand() % 10;
            }
            map[x][y] = 9;
        }
    }
    
    void displayMap()
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    void placeRobot(int &x, int &y)
    {
        do
        {
            x = rand() % 10;
            y = rand() % 10;
        } while (map[x][y] == 9);
        map[x][y] = 5;
    }
    
    void readSensors(int x, int y, int &north, int &east, int &south, int &west)
    {
        //For the sensors: 0 is no object in square, 1 is battery, 2 is wall
        
        if (x == 0)
            north = 2;
        else if (map[x - 1][y] == 9)
            north = 1;
        else
            north = 0;
        
        if (x == 9)
            south = 2;
        else if (map[x + 1][y] == 9)
            south = 1;
        else
            south = 0;
        
        if (y == 0)
            west = 2;
        else if (map[x][y - 1] == 9)
            west = 1;
        else
            west = 0;
        
        if (y == 9)
            east = 2;
        else if (map[x][y + 1])
            east = 1;
        else
            east = 0;
    }
    
    void moveRobot(int &x, int &y, int moveAction)
    {
        
    }
};

class Robot
{
private:
    int power;
    int turnsSurvived;
    int gene[16][5];
    
public:
    int positionX, positionY;
    int sNorth, sEast, sSouth, sWest;
    
    Robot()
    {
        //Start with 5 power
        power = 5;
        turnsSurvived = 0;
        //Randomly give the robot its genes
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 4; j++)
                //3 sensor states: nothing, wall, battery
                gene[i][j] = rand() % 3;
            //5 actions: N, S, E, W, R
            gene[i][4] = rand() % 5;
        }
        positionX = rand() % 10;
        positionY = rand() % 10;
    }
    
    void printRobot()
    {
        cout << power << endl;
        cout << turnsSurvived << endl;
        cout << "x: " << positionX << endl;
        cout << "y: " << positionY << endl;
        cout << sNorth << sSouth << sEast << sWest << endl;
        for (int i = 0; i < 16; i ++)
        {
            for (int j = 0; j < 5; j++)
            {
                cout << gene[i][j];
            }
            cout << endl;
        }
    }
    
    int compareGenes()
    {
        for (int i = 0; i < 16; i++)
            if (sNorth == gene[i][0] && sSouth == gene[i][1] && sEast == gene[i][2] && sWest == gene[i][3])
                return gene[i][4];
        
        return gene[15][4];
    }
};

//**************************************************************************************************************
int main() {
    // time seed the random number generator
    srand(time(NULL));
    //Variable Declarations
    
    
    Map map1;
    //Map map2;
    map1.displayMap();
    cout << endl;
    //map2.displayMap();
    //cout << endl;
    
    Robot robot1;
    //Robot robot2;
    
    //Place the robots on the map
    map1.placeRobot(robot1.positionX, robot1.positionY);
    //map2.placeRobot(robot2.positionX, robot2.positionY);
    map1.displayMap();
    cout << endl;
    
    //Read the sensors
    map1.readSensors(robot1.positionX, robot1.positionY, robot1.sNorth, robot1.sEast, robot1.sSouth, robot1.sWest);
    //map2.readSensors(robot2.positionX, robot2.positionY, robot2.sNorth, robot2.sEast, robot2.sSouth, robot2.sWest);
    
    //int moveAction = robot1.compareGenes();********************
    map1.moveRobot(robot1.positionX, robot1.positionY, robot1.compareGenes());
    

    map1.displayMap();
    cout << endl;
    //map2.displayMap();
    //cout << endl;
    
    robot1.printRobot();
    cout << endl;
    //robot2.printRobot();
    //cout << endl;
    
    
    
    return 0;
}
//**************************************************************************************************************

