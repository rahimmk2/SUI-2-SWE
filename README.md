# Final-Project

## Organization
The repository has two main folders - the "data" folder and, the "app" folder.

The data folder holds the csv files and the python scripts that are used to parse the csv files.

The app folder holds the bulk of the code for the project - the main, the algorithm code, the makefile, and the tests for the code can all be found in this folder.

The the project proposal, team contract, and final writeup can all be found within the main folder of the repository and the presention can be found by following the link below:

https://drive.google.com/file/d/1XZUIKHDdjzOKCItMMNGwrqCs6Az64ifL/view?usp=sharing

## Running Instructions
The code runs on the workspace provided by the CS225 docker, thus the running insturctions are very similar.

Once you are in the project directory, run the following commands to build the executeable:

mkdir build && cd build

cmake ..

and use 

make test && ./test

to simulate the local test cases or 

make main && ./main

to run the code on the real dataset from the Sui blockchain
