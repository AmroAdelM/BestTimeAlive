# BestTimeAlive
## Description
From a txt file with dataset, get arbitrary range of years with most composers alive

## Input
In macros, you can change:
1- The path for the txt file
2- Range of years to search for

## GTest
It uses google test library for unit and behavioral testing, you can run the tests by uncommenting the line in main;

## Design
There was no much calss design needed, other than just separating the part where we read from the file and the part where we check for the range

## Performance and choices
I intianlly user unordered_map, as it is faster in inserting and searching, but later realised that having is order is key to fulfill the "most recent" need.
