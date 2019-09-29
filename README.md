# Tedit - Terminal Text Editor 

This is a simple terminal text editor, that I have written to get a bit used to C++.
It displays line numbers and can open multiple files at the same time.

## Build
On Ubuntu:
```
sudo apt-get install build-essential
sudo apt-get install cmake
sudo apt-get install ncurses-dev

git clone https://github.com/FlexW/tedit.git ~/tedit
cd ~/tedit
mkdir build && cd build
cmake ..
make
sudo make install
```

## Run program
```
tedit
```

## Usage
Commands:
```
Ctrl-o      Open file
Ctrl-s      Save file
Ctrl-n      Next buffer
Ctrl-p      Previous buffer
Ctrl-q      Quit editor
```
