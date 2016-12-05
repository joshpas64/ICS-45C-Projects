// InteractionProcessor.cpp
//
// ICS 45C Fall 2016
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"
#include "CommandStack.hpp"
#include <vector>

// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

void InteractionProcessor::run()
{
    view.refresh();
    CommandStack undoStack = CommandStack(); //Current undo history, doing 'redo' deletes a command from undo history
    CommandStack redoStack = CommandStack(); //Redo history, starts empty, but calls to undo or redo after 1 undo will set its contents

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            if(undoStack.getSize() > 0) //Dont bother processing if there are no commands to undo
            {
                Command* tempCommand = undoStack.getTopCommand(); //Get top command and execute it before adding it to the stack, especially if the command raises exceptions
                try
                {
                    tempCommand->undo(model); //Use polymorphism to run the undo method of the DERIVED command object pointer
                    undoStack.exchange(redoStack, true); //Add to undostack and if possible, pop from redo
                    model.clearErrorMessage(); //If no exceptions, clear error messages
                }
                catch(EditorException &e)
                {
                    model.setErrorMessage(e.getReason()); //Set the error message in status window to specific exception reason
                    delete tempCommand; //Since the exception was raised, Command was not added to any stack, so pointer must be deleted 
                }
            }
            view.refresh(); //Update view with updated model information
        }
        else if (interaction.type() == InteractionType::redo)
        {
            if(redoStack.getSize() > 0)
            {
                Command* tempCommand = redoStack.getTopCommand(); //Get top command and execute it before adding it to the stack, especially if the command raises exceptions
                try
                {
                    tempCommand->execute(model); //Use polymorphism to access and run the DERIVED Command ptr's execute method on the model
                    undoStack.exchange(redoStack,false); //If valid with no exceptions, add to redoStack and pop from undoStack
                }
                catch(EditorException &e)
                {
                    model.setErrorMessage(e.getReason());//Set the error message in status window to specific exception reason
                    delete tempCommand; //Since the exception was raised, Command was not added to any stack, so pointer must be deleted 
                }
            }
            view.refresh(); //Update
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();
            try
            {
                if(command == nullptr) //Case ctrl+not a valid shortcut command character
                {
                    delete command; //Do nothing and just delete command and clear message
                }
                else
                {
                    command->execute(model); //Run the command ptr's derived execute
                    undoStack.push(command); // Add to undo history
                    redoStack.clear(); //Since a new command changes the whole command, undo ,redo history, redoStack must be cleared
                }
                model.clearErrorMessage();
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());//If exception get specific reason and it to appropriate place in editormodel and delete command
                delete command;
            }

            view.refresh(); //Update view with any modified model contents

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
            
        }
    }
}

