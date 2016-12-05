// KeypressInteractionReader.cpp
//
// ICS 45C Fall 2016
// Project #4: People Just Want to Play with Words
//
// Implementation of the KeypressInteractionReader
//
// YOU WILL NEED TO IMPLEMENT SOME THINGS HERE

#include "KeypressInteractionReader.hpp"
//New Commands all derived from Command class defined in Command.hpp
#include "DelLine.hpp"
#include "newLine.hpp"
#include "insertChar.hpp"
#include "backspace.hpp"
#include "upArrow.hpp"
#include "downArrow.hpp"
#include "leftArrow.hpp"
#include "rightArrow.hpp"
#include "HomeCommand.hpp"
#include "endOfLine.hpp"

// You will need to update this member function to watch for the right
// keypresses and build the right kinds of Interactions as a result.
//
// The reason you'll need to implement things here is that you'll need
// to create Command objects, which you'll be declaring and defining
// yourself; they haven't been provided already.
//
// I've added handling for "quit" here, but you'll need to add the others.

Interaction KeypressInteractionReader::nextInteraction()
{
    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();
        Command* newCommand = nullptr;
        //Since Command can be anything have it be null to start
        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly
            // Use pointers and inheritance to pass different commands as the same type, if no case is Satisfied in the switch statement
            // This method will return an interaction with a nullptr, which will either cause an EditorException or an if statement to be satisfied where in that
            // case outside the scope of this method newCommand will be deleted
            switch (keypress.code())
            {
            case 'A':
                return Interaction::redo();
            case 'D':
                newCommand = new DelLine();
                break;
            case 'H':
                newCommand = new BackSpace();
                break;
            case 'I':
                newCommand = new UpArrow();
                break;
            case 'J':
                newCommand = new NewLine();
                break;
            case 'K':
                newCommand = new DownArrow();
                break;
            case 'M':
                newCommand = new NewLine();
                break;
            case 'O':
                newCommand = new RightArrow();
                break;
            case 'P':
                newCommand = new EndOfLine();
                break;
            case 'U':
                newCommand = new LeftArrow();
                break;
            case 'Y':
                newCommand = new HomeCommand();
                break;
            case 'Z':
                return Interaction::undo();
            case 'X':
                return Interaction::quit();
            default:
                break;
            }
            return Interaction::command(newCommand); //If not quit,undo, redo, return an Interaction with a command that points to and can'execute' and 'undo' 
            // any of its derived class

        }
        else
        {
            // The user pressed a normal key (e.g., 'h') without holding
            // down Ctrl; react accordingly
            InsertChar *newChar = new InsertChar(); //Command will point to derived InsertChar Command object 
            newChar->setChar(keypress.code()); //have the InsertChar's addKey set to the key that was pressed
            Command *newCommand = newChar;
            return Interaction::command(newCommand);
        }
    }
}

