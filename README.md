# Elsword Tournament Controller
This is a small program designed to streamline the many actions a streamer must take care of when hosting an Elsword tournament.

## Features
Currently, the Elsword Tournament Controller can do the following functions:
- Update a "scoreboard" represented through text files that can be dynamically read by a livestreaming program (ex. OBS)
- Support for three extra files for misc. purposes (Tournament Name, Round Info, Best of X, Brackets, etc) to be dynamically read by a livestreaming program
- Retrieve tournaments/matches from Challonge and update those matches with scores/winners, can reopen closed matches as well
- Clip your stream on Twitch for lag calls and other noteworthy moments
- Random Map Picker
- Misc. QoL functions

## Download
Download the compiled binary (.exe file) here: https://github.com/Synai/elstourneycontroller/releases.
If you want the latest version, download the .zip file from the release tagged as "Latest Release".

### Preview
![alt text](https://i.imgur.com/wZRGUWQ.gif)
## Planned Features
The following features are planned to be added (in order of priority, somewhat):
- ~~Display completed matches and allow for re-opening of matches for when someone mistakenly reports the wrong winner (in the current build once you report the winner it's considered final)~~
- ~~Create a LAG CALL Button that will clip the Twitch stream at the current time when pressed. Allows for easier time to view lag calls where the decision is not immediately obvious.~~
- Create a new tab: "Misc." to allow for easy access to copy-paste messages that can be custom set (ex. default messages for lag calls, or rules, etc)
- Strawpoll Integration - easy creation of Strawpolls for when viewer votes are requested to make a decision (?)
- Feel free suggest your own ideas/suggestions to me

## Help
There is a wiki page for this repo here: https://github.com/Synai/elstourneycontroller/wiki.
It contains some guides such as getting a Challonge API key, setting up Scoreboard/Overlay, etc.

## Building
If for some reason you want to actually build this on your machine, this is what I used/what you'll need (Windows):
- Qt Creator 4.6.1
- Qt 5.10.1 MSVC2017 64 bit
- Microsoft Visual C++ Compiler 2015/2017
- CMake/QMake

I'm no expert on Qt Creator IDE but you should be able to open this project from the IDE with all the files, run qmake, and then build.
