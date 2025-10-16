/*                                                                                                                                                                                                         
  File: Game.cpp                                                                                                                                                                                      
                                                                                                                                                                                                           
  Project: CMSC 202 Project 2, Spring 2025                                                                                                                                                                 
                                                                                                                                                                                                           
  Author: Elif Meral                                                                                                                                                                                       
                                                                                                                                                                                                           
  Date: 03/11/25                                                                                                                                                                                           
                                                                                                                                                                                                           
  Section: 10/14                                                                                                                                                                                           
                                                                                                                                                                                                           
  E-mail: elifm1@umbc.edu                                                                                                                                                                                  
                                                                                                                                                                                                          
  Description: This file contains the Game class function definitions                                                                                                                                 
               Which includes the functions for the game to be played                                                                                                                                  
*/

#include <iomanip>
#include "Game.h"      //Class for Game
#include "Element.h"   // Class for Element
#include "DoodleGod.h" //Class for Doodle God
//Game()
//Empty default constructor
Game::Game(){}

//Functions

//LoadRecipes()
//Loads each recipe from provided file
void Game::LoadRecipes(){
  
  ifstream recipe(PROJ2_RECIPES); //Opens the file to access the recipes
  int counter = 0;                //Counter for elements
  string name;                    //Name of the created element
  string element1;                //Name of the first element 
  string element2;                //Name of the second element

  //Runs as long as counter is below the array size
  while(counter < PROJ2_SIZE){
    //Gets the name
    getline(recipe, name, ',');
    //Gets the first element
    getline(recipe, element1, ','); 
    //Gets the second element
    getline(recipe, element2);
    
    //Adds the elements into the m_elements array
    m_elements[counter] = Element(name, element1, element2);
 
    counter++;
  }
  cout << "139 elements loaded." << endl;
}

//StartGame()
//Loads all recepies, asks user for their DoodleGod Name, Adds: fire, water, air, and eart as known element list in m_myDoodleGod, manages game itself with win conditions continually calling main menu
void Game::StartGame(){

  //Displays Doodle God Art
  GameTitle();

  //Loads all recepies
  LoadRecipes();

  string name; //Name for Doodle God
  cout << "What is the name of the Doodle God?" << endl;
  getline(cin, name);

  //Sets DoodleGods name
  m_myDoodleGod.SetName(name);

  //Adds: fire, water, air, and eart as known element list in m_myDoodleGod
  for (int i = 0; i < 4; i ++){
    m_myDoodleGod.AddElement(m_elements[i]);
  }

  //manages game itself with win conditions continually calling main menu
  int choice = MainMenu(); //The choice of the user on how they want to continue

  //runs as long as user does not choose 4
  while(choice != 4){
    
    switch(choice){
    case 1:
      //Displays know  elements
      DisplayElements();
      break;
    
    case 2:
      //Allows user to pick elements to combine
      CombineElements();
      break;
      
    case 3:
      //Calculates users score
      CalcScore();
      break;

    default:
      break;
    }
    //choice is set to users input
    choice = MainMenu();
  
  }
  cout << "Thanks for playing the Doodle God!" << endl;
}
//DisplayElements()
//Displays Known Elements
void Game::DisplayElements(){
  m_myDoodleGod.DisplayElements();
}

//MainMenu() 
//Displays the user to choose how they want to continue
int Game::MainMenu(){
  
  int choice; //choice of the user

  //Displays main menu
  cout << "What would you like to do?" << endl;
  cout << "1. Display the Doodle God's Elements" << endl;
  cout << "2. Attempt to Combine Elements" << endl;
  cout << "3. See Score" << endl;
  cout << "4. Quit" << endl;

  //sets input to choice
  cin >> choice;
  return choice;
}

//CombineElements()
//Attempts to combine elements chosen by user
void Game::CombineElements(){
  
  Element createdElement; //the newly found element
  int choice1 = 0;        //chosen element by number
  int choice2 = 0;        //chosen element by number
  
  //Request the first element
  RequestElement(choice1);
  string element1 = m_myDoodleGod.GetElement(choice1).m_name; //First element is set by the choice
  
  
  //Request the second element
  RequestElement(choice2);
  string element2 = m_myDoodleGod.GetElement(choice2).m_name; ////Second element is set by choice
  
  int search1 = SearchRecipes(element1, element2);  //Searches for the combination of element1 and element2 for element1 + element2
  int search2 = SearchRecipes(element2, element1);  //Searches for the combination of element1 and element2 for element2 + element1

  //If both searches did not find an element and attempt it added only
  if(search1 == -1 && search2 == -1){
    cout << "Nothing happened when you tried to combine " << element1  << " and " << element2   << endl;
    m_myDoodleGod.AddAttempt();
  }
  //If the first search finds an element it adds to createdElement
  else if(search1 > -1){
    createdElement = m_elements[search1];

    //If element was already in myElements, repeat is added
    if (m_myDoodleGod.CheckElement(createdElement)) {  
      m_myDoodleGod.AddRepeat();
      cout << createdElement.m_name << " is already known." << endl;
    }
    //If element was not already found, it is added to myElements and an attempt is added
    else {  
      cout << element1 << " combined with " << element2  << " to make "  << createdElement.m_name << "!" << endl;
      cout << "The Doodle God now knows " << createdElement.m_name << "." << endl;
      m_myDoodleGod.AddElement(m_elements[search1]);
      m_myDoodleGod.AddAttempt();
    }
  }
  //if the second search finds an element it adds to createdElement
  else if(search2 > -1){
    createdElement = m_elements[search2];

    //If element was already in myElements, repeat is added
    if (m_myDoodleGod.CheckElement(createdElement)) {
      m_myDoodleGod.AddRepeat();
      cout << createdElement.m_name << " is already known." << endl;
    }
    //If element was not already found, it is added to myElements and an attempt is added
    else {
      cout << element1 << " combined with " << element2  << " to make "  << createdElement.m_name << "!" << endl;
      cout << "The Doodle God now knows " << createdElement.m_name << "." << endl;
     
      m_myDoodleGod.AddElement(m_elements[search2]);
      m_myDoodleGod.AddAttempt();
    }
  }
}

//RequestElement(int)
//Asks the user to choose two elements to try and merge and checks to make sure it is in range
void Game::RequestElement(int &choice){
  //Asks user while their choice is either to display elements or  invalid by range of number of elements
  do{
  cout << "Which elements would you like to merge?" << endl;
  cout << "To list known elements, enter -1" << endl;
  cin >> choice;

  //If the user chooses -1, displays the elements
  if (choice == -1) {
    DisplayElements();  
  }
  
  //If the input is out of bounds, lets user know
  else if (choice < 1 || choice > m_myDoodleGod.GetNumElements()) {
    cout << "Invalid choice. Please select a valid element." << endl;
  }
  
  }while (choice == -1 || choice < 1 || choice > m_myDoodleGod.GetNumElements());
}

//SearchRecipes(string, string)
//Searches recipie for two strings passed
int Game::SearchRecipes(string element1, string element2){
  //Checks every recipe
  for (int i = 0; i < PROJ2_SIZE; ++i) {
    //If recipe exists, the index is returned 
    if (m_elements[i].m_element1 == element1 && m_elements[i].m_element2 == element2){
	return i;
      }
  }
  //Indicates recipe does not exist
  return -1;
}


//CalcScore()
//Displays the current score for Doodle God
void Game::CalcScore(){
  cout << "***The Doodle God***" << endl;
  //Uses the name set by user
  cout << "The Great Doodle God "  << m_myDoodleGod.GetName() << endl;
  //Displays with total attempts
  cout << "The Doodle God has tried to combine " << m_myDoodleGod.GetAttempts() << " elements" << endl;
  //Displays with total repeats
  cout << "The Doodle God has repeated attempts " << m_myDoodleGod.GetRepeats() << " times" << endl;
  //Displays with amount of elemnts found
  cout << "The Doodle God found " << m_myDoodleGod.GetNumElements() << " out of 139 elements" << endl;
  double percent = (m_myDoodleGod.GetNumElements() / 139.0) * 100; //percent of elements found by user
  //sets the percent to two decimal places
  cout << fixed << setprecision(2);
  cout << "You have completed " << percent << "% of the elements" << endl;
}

