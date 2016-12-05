This was the last project assigned for ICS45C at UCI for Fall 2016. 

This project was mainly to test concepts relating to GUI's, Inheritance, polymorphism, exception handling, and how to use the C and C++ 
standard library to make a working text editor that could run, take input and update the view and properly catch any exceptions and run and
take any key inserted or any of the specified keyboard shortcuts without leaking memory.

It also had to be able to implement undo and redo features, meaning command history had to be tracked but be updated in a way similar to a 
tab in a web browser. I.e. when you navigate back a webpage, you can move back and forth up to the current page at your leisure unless, when 
on any previous page you issue a new command or navigate somewhere else, your forward history is deleted. Also the lines of strings had to be
stored, updated, and deleted at any time and go up to a certain amount that could change any time. The easiest ways I found to do this was 
to implement vector and strings, since they are already defined in a way where they do not leak memory, and have many useful built in methods.
A stack object was easiest data structure I found for the undo and redo history.

The files that are my own are 
1. HomeCommand.hpp and HomeCommand.cpp
2. DelLine.cpp and DelLine.hpp
3. insertChar.hpp and insertChar.cpp
4. backSpace.hpp and backSpace.cpp
5. endOfLine.hpp and endOfLine.cpp
6. newLine.hpp and newLine.cpp
7. CommandStack.hpp and CommandStack.cpp
8. leftArrow.hpp and leftArrow.cpp
9. rightArrow.hpp and rightArrow.cpp
10. upArrow.hpp and upArrow.cpp
11. downArrow.hpp and downArrow.cpp

All other files were created and written by either Professor Thornton and his TAs to act as templates for us to fill in or as needed files to
make the program run smoothly and to create a stable GUI object with a view, a model with coordinates and sections the view 
refers to and a redraw function that was a little reminiscent of Java. The cursor tracking was done with module ncurses.h

The files that needed editing were
1. EditorModel.hpp and EditorModel.cpp
2. InteractionProcessor.cpp
3. KeypressInteractionReader.cpp
