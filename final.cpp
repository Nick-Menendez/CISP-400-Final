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
    int fitness;
    int positionX, positionY;
    int sNorth, sEast, sSouth, sWest;
public:
    int gene[16][5];
    
    Robot();
    void displayMap();
    void placeRobot();
    void printRobot();
    void readSensors();
    int compareGenes();
    void moveRobot(int geneCode);
    void resetRobots();
    int getPower()
    {
        return power;
    }
    
    int getTurnsSurvived()
    {
        return turnsSurvived;
    }
    
    int getFitness()
    {
        return fitness;
    }
    
   void getSensors()
    {
        cout << sNorth << " " << sSouth << " " << sEast << " " << sWest << endl;
    }
};

Robot::Robot()
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
    fitness = 0;
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

void Robot::displayMap()
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

void Robot::placeRobot()
{
    do
    {
        positionX = rand() % 10;
        positionY = rand() % 10;
    } while (map[positionX][positionY] == 9);
    map[positionX][positionY] = 5;
}

void Robot::printRobot()
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

void Robot::readSensors()
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

int Robot::compareGenes()
{
    for (int i = 0; i < 16; i++)
        if (sNorth == gene[i][0] && sSouth == gene[i][1] && sEast == gene[i][2] && sWest == gene[i][3])
            return gene[i][4];
    
    return gene[15][4];
}

void Robot::moveRobot(int geneCode)
{
    int moveAction;
    
    power -= 1;
    turnsSurvived += 1;
    
    if (geneCode == 4)
        moveAction = rand() % 4;
    else
        moveAction = geneCode;
    
    if (positionX == 0 && moveAction == 0)
        return;
    if (positionX == 9 && moveAction == 1)
        return;
    if (positionY == 0 && moveAction == 3)
        return;
    if (positionY == 9 && moveAction == 2)
        return;
    
    //Need to finish robot movement here!
    if (moveAction == 0)
    {
        map[positionX][positionY] = 0;
        positionX = positionX - 1;
        if(map[positionX][positionY] == 9)
        {
            power += 5;
            fitness += 5;
        }
        map[positionX][positionY] = 5;
    }
    else if (moveAction == 1)
    {
        map[positionX][positionY] = 0;
        positionX = positionX + 1;
        if(map[positionX][positionY] == 9)
        {
            power += 5;
            fitness += 5;
        }
        map[positionX][positionY] = 5;
    }
    else if (moveAction == 2)
    {
        map[positionX][positionY] = 0;
        positionY = positionY + 1;
        if(map[positionX][positionY] == 9)
        {
            power += 5;
            fitness += 5;
        }
        map[positionX][positionY] = 5;
    }
    else if (moveAction == 3)
    {
        map[positionX][positionY] = 0;
        positionY = positionY - 1;
        if(map[positionX][positionY] == 9)
        {
            power += 5;
            fitness += 5;
        }
        map[positionX][positionY] = 5;
    }
}

void Robot::resetRobots()
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
    fitness = 0;
    positionX = rand() % 10;
    positionY = rand() % 10;
}




//Function Prototypes
//bool compareTurnsSurvived(Robot, Robot);
bool compareTurnsSurvived(shared_ptr<Robot>, shared_ptr<Robot>);
void programGreeting();


//**************************************************************************************************************
int main() {
    // time seed the random number generator
    srand(time(NULL));
    //Variable Declarations
    float avgFitness = 0;
    int totFitness = 0;
    int generation = 1;
    
    //Program Greeting
    programGreeting();
    
    //Instantiate the robot vector and fill it with maps with a randomly placed robot
    vector<shared_ptr<Robot>> population;
    for (int i = 0; i < 200; i++)
    {
        population.push_back(make_shared<Robot>());
    }
    
    //Generational loop here ***************************
    for (int n = 0; n < 1000; n ++)
    {
        //Reset the Robot's data but DO NOT touch the genes
        for (int i = 0; i < population.size(); i++)
        {
            population[i]->resetRobots();
            population[i]->placeRobot();
        }
        
        //Move each robot through the simulation
        for (int i = 0; i < population.size(); i++)
        {
            while (population[i]->getPower() > 0)
            {
                population[i]->readSensors();
                population[i]->moveRobot(population[i]->compareGenes());
            }
        }
        
        //Sort the vector in descending order by the number of turns survived
        sort(population.begin(), population.end(), compareTurnsSurvived);
        
        //Calculate the average fitness for this generation
        totFitness = 0;
        for (int i = 0; i < population.size(); i++)
            totFitness += population[i]->getFitness();
        avgFitness = static_cast<float>(totFitness) / population.size();
        
        //Write to the console the average fitness
        //For testing purposes, change the % number to print more or less data to the console.
        if (generation == 1 || generation % 1 == 0)
            cout << "Average Fitness of Generation " << generation << ": " << avgFitness << endl;
        
        //Kill of the bottom 50% of the robots
        population.erase(population.begin() + 100, population.end());
        
        //Repopulate 100 Robots to the vector
        for (int i = 0; i < 100; i += 2)
        {
            //2 robots at a time here
            population.push_back(make_shared<Robot>());
            population.push_back(make_shared<Robot>());
            population[i + 100]->placeRobot();
            population[i + 101]->placeRobot();
            
            //50% of genes from one parent
            for (int j = 0; j < 8; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    population[i + 100]->gene[j][k] = population[i]->gene[j][k];
                    population[i + 101]->gene[j][k] = population[i + 1]->gene[j][k];
                }
                //5% of the time mutations occur - randomly change one character in the gene
                if(rand() % 100 < 5)
                    population[i + 100]->gene[j][rand() % 5] = rand() % 3;
                if(rand() % 100 < 5)
                    population[i + 101]->gene[j][rand() % 5] = rand() % 3;
            }
            //50% of genes from the other parent
            for (int j = 8; j < 16; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    population[i + 100]->gene[j][k] = population[i + 1]->gene[j][k];
                    population[i + 101]->gene[j][k] = population[i]->gene[j][k];
                }
                //Mutations
                if(rand() % 100 < 5)
                    population[i + 100]->gene[j][rand() % 5] = rand() % 3;
                if(rand() % 100 < 5)
                    population[i + 101]->gene[j][rand() % 5] = rand() % 3;
            }
        }
        
        //Increment the generation count
        generation += 1;
    }
    
    
    return 0;
}
//**************************************************************************************************************

void programGreeting()
{
    string start = "";
    cout << "Welcome to the Genetic Algorithm Robots program." << endl;
    cout << "In this program, we will study the evolution of a population of robots." << endl;
    cout << "There are 200 robots in a population.  50% will die off after each generation." << endl;
    cout << "They will be replaced with robots that are bred from the survivors." << endl;
    cout << "The fitness score is a measure of how successful the robots harvested energy and survived." << endl << endl;
    cout << "This program will simulate 1000 generations of robots and will print the average" << endl;
    cout << "fitness of each generation to the console." << endl << endl;
    cout << "Please press the ENTER key to begin the simulation." << endl;
    getline(cin, start);
}

bool compareTurnsSurvived(shared_ptr<Robot> r1, shared_ptr<Robot> r2)
{
    return (r1->getTurnsSurvived() > r2->getTurnsSurvived());
}
