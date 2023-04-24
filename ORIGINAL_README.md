#
#Student Name: YE Hongran
#Student ID: [REDACTED]
#

## Synopsis
Assignment-01 of UCP

## Overview
A simple ASCII-based game where the player moves through a maze map while collecting the key. The game is played in a terminal window and relies on continuous input without the need for the Enter key.

## Syntax
Usage: ./maze [<visibility distance>]
(<visibility distance> only works with conditional compilation -D DARK)
[<visibility distance>] is optional and must be a non-negative integer.
When <visibility distance> is set to 0 (default as 0)., visibility is unlimited.

## Contents
main.c: 
Initialises the game and passes data between modules.
game.c: 
Handles player movement, provides a quick reference to player coordinates, modifies the map data, and manages the game state.
map.c: 
Handles the translation and printing of map data.
algorithm.c: 
provides utility functions to determine the minimum and maximum values of two given integers.
terminal.c: 
Enables continuous input without the need for the Enter key. Downloaded from assessment attachments, no comments made.
world.c: 
Generates the map data. Downloaded from assessment attachments, no comments made.
how_this_works.png: 
A screenshot of the program in developer mode.

## Dependencies
None

## Version information
24/04/2023  - final version of Assignment 01 maze game programs

