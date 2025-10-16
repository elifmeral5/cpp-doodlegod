/*                                                                                                                                                                                                      
  File: DoodleGod.cpp                                                                                                                                                                                      

  Project: CMSC 202 Project 2, Spring 2025                                                                                                                                                                

  Author: Elif Meral                                                                                                                                                                                      

  Date: 03/11/25                                                                                                                                                                            

  Section: 10/14                                                                                                                                                                                           

  E-mail: elifm1@umbc.edu

  Description: This file contains the DoodleGod class function definitions
               Which includes essentials parts of the game to be played. 
*/


#include "DoodleGod.h" //Include for the DoodleGod struct
#include "Element.h"   //Include for the element struct

//Constructors

//DoodleGod()
//Default Constructor - Creates a new DoodleGod and sets default values to 0 for all integers
DoodleGod::DoodleGod(){
  m_attempts = 0;
  m_repeats = 0;
  m_numElements = 0;
}

//DoodleGod(name)
//Overloaded Constructor - Creates a new DoodleGod and sets default values to 0 for all integers
DoodleGod::DoodleGod(string name){
  m_attempts = 0;
  m_repeats = 0;
  m_numElements = 0;
  m_myName = name;
}

//Functions

//GetName()
//Getter for DoodleGod name
string DoodleGod::GetName() {return m_myName;}

//SetName(string)
//Allows the user to change the name of the DoodleGod and set a new name                                                                                                                                 
void DoodleGod::SetName(string name) {m_myName = name;}

//DisplayElements()
//Displays a numbered list of all elements known by the DoodleGod
void DoodleGod::DisplayElements(){

  //Iterates through the number of elements known and adds elements known accordingly
  for(int i = 0; i < m_numElements; i++){
    cout << i + 1 << ". " << m_myElements[i].m_name << endl;
  }
}

//GetNumElements()
//Returns number of elements known by the DoodleGod
int DoodleGod::GetNumElements(){

  int numElements = 0; //resets the number of elements to 0

  //Checks every element in the array
  for(int i = 0; i < PROJ2_SIZE; i++){
    //if the element is not empty, the number of elements is increased
    if (m_myElements[i].m_name != ""){
      numElements++;
    }
  }
  
  //sets the complete number of elements
  m_numElements = numElements;
  
  return m_numElements;
}

//CheckElement(element)
//Checks to see if Doodle God had identified an element
bool DoodleGod::CheckElement(Element element){
  //checks every element in the aarray
  for(int i = 0; i < PROJ2_SIZE; i++){
    //if the element is already identified it is returned as true
    if (m_myElements[i].m_name == element.m_name){
     
      return true;
    }
  }
  //if the element is not already identified it is returned false
  return false;
}

//AddElement(element)
//Adds element to m_myElements if not known and increases numElements
void DoodleGod::AddElement(Element element){
  
  if(!CheckElement(element)){
    //Adds the new found element to myElements and increases number of elements known
    if (m_numElements <= PROJ2_SIZE) {

      m_myElements[m_numElements] = element;

      m_numElements++;
    }
  }
}

//GetElement(int)
//Checks to see if Doodle God has an elemen
Element DoodleGod::GetElement(int index){
  
  return m_myElements[index - 1];
}

//AddAttempt()
//Increments attempts by one
void DoodleGod::AddAttempt(){
  m_attempts++;
}

//GetAttempts()
//Returns number of attempts for that DoodleGod
int DoodleGod::GetAttempts(){return m_attempts;}

//AddRepeat()
//Increments repeats by one
void DoodleGod::AddRepeat(){
  m_repeats++; 
}

//GetRepeats()
//Returns number of repeats for that DoodleGod
int DoodleGod::GetRepeats(){return m_repeats;}
