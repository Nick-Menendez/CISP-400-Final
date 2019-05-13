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

class Robot
{
private:
    int map[10][10];
    int power;
    int turnsSurvived;
    int gene[16][5];
    int positionX, positionY;
    int sNorth, sEast, sSouth, sWest;
public:
    
    Robot()
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
    
    void placeRobot()
    {
        do
        {
            positionX = rand() % 10;
            positionY = rand() % 10;
        } while (map[positionX][positionY] == 9);
        map[positionX][positionY] = 5;
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
    
    void readSensors()
    {
        //For the sensors: 0 is no object in square, 1 is battery, 2 is wall
        
        if (positionX == 0)
            sNorth = 2;
        else if (map[positionX - 1][positionY] == 9)
            sNorth = 1;
        else
            sNorth = 0;
        
        if (positionX == 9)
            sSouth = 2;
        else if (map[positionX + 1][positionY] == 9)
            sSouth = 1;
        else
            sSouth = 0;
        
        if (positionY == 0)
            sWest = 2;
        else if (map[positionX][positionY - 1] == 9)
            sWest = 1;
        else
            sWest = 0;
        
        if (positionY == 9)
            sEast = 2;
        else if (map[positionX][positionY + 1])
            sEast = 1;
        else
            sEast = 0;
    }
    
    int compareGenes()
    {
        for (int i = 0; i < 16; i++)
            if (sNorth == gene[i][0] && sSouth == gene[i][1] && sEast == gene[i][2] && sWest == gene[i][3])
                return gene[i][4];
        
        return gene[15][4];
    }
    
    void moveRobot()
    {
        
    }
};

//**************************************************************************************************************
int main() {
    // time seed the random number generator
    srand(time(NULL));
    //Variable Declarations
    
    
    Robot robot1;
    robot1.displayMap();
    cout << endl;
 
    
    //Place the robots on the map
    robot1.placeRobot();
    
    robot1.displayMap();
    cout << endl;
    
    //Read the sensors
    robot1.readSensors();
    
    //int moveAction = robot1.compareGenes();********************
    robot1.moveRobot();
    

    robot1.displayMap();
    cout << endl;
   
    
    robot1.printRobot();
    cout << endl;
    
    
    
    return 0;
}
//**************************************************************************************************************


