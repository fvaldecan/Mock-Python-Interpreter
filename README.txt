Author: Franco Dominic Valdecanas
Class: CS460
Professor: Dr. Kooshesh
Assignment: Final Project

Things that work:
    Everything should be working properly. There is a bit of a mix up in function calling within functions itself. It can run without parameters and execute those functions although everything from data types, arrays, if and for statements should be working like they should.

A very little thing that doesn't work:
    One weird error I catch revolves around the input. If you notice input3.py and run it, it will work properly. But if you run input4.py with the exact same code but take out the last statement it will come out "Unknown character in input. -><-". This means it read a character that is unknown but what is it? In Clion char c seems to pick up a character 0'\0' so I'm not sure what the problem is and why it doesn't get that it's the end of the file. So ending with indentated statements seems to be a small error but if it ends a statement without and indent it works. It expects an end of file or end of line for each simple statement.

Tests include:
    input1.py
    input2.py
    input3.py
    input4.py
How to run:
    1. make clean
    2. make
    3. ./statement.x {inputFileName}
   		   or
    1. Run normally on CLion
