# Elsword Tournament Controller
This is a small program designed to streamline the many actions a streamer must take care of when hosting an Elsword tournament.

## Features
Currently, the Elsword Tournament Controller can do the following functions:
- Update a "scoreboard" represented through text files that can be dynamically read by a livestreaming program (ex. OBS)
- Support for three extra files for misc. purposes (Tournament Name, Round Info, Best of X, Brackets, etc) to be dynamically read by a livestreaming program
- Retrieve tournaments/matches from Challonge and update those matches with scores/winners, can reopen closed matches as well
- Random Map Picker

## Download
Download link will be made available shortly. Most likely after the re-open matches planned feature is finished.

### Preview Images
![alt text](https://i.imgur.com/EVmsdzZ.png) ![alt text](https://i.imgur.com/IgCa1XP.png)
## Planned Features
The following features are planned to be added (in order of priority, somewhat):
- ~~Display completed matches and allow for re-opening of matches for when someone mistakenly reports the wrong winner (in the current build once you report the winner it's considered final)~~
- Create a third tab: "Misc." to allow for easy access to copy-paste messages that can be custom set (ex. default messages for lag calls, or rules, etc)
- Create a LAG CALL Button that will clip the Twitch stream at the current time when pressed. Allows for easier time to view lag calls where the decision is not immediately obvious.

## Motivation
Everyone wants to just watch the action in tournaments, no one wants to watch streamers fiddle with their overlays, update matches on Challonge, or spend 5 min picking a random map, hence this program.
Now if only participants in tournaments could show up on time prepared...

## Building
If for some reason you want to actually build this on your machine, this is what I used/what you'll need (Windows):
- Qt Creator 4.6.1
- Qt 5.10.1 MSVC2017 64 bit
- Microsoft Visual C++ Compiler 2015/2017
- CMake/QMake

I'm no expert on Qt Creator IDE but you should be able to open this project from the IDE with all the files, run qmake, and then build.
