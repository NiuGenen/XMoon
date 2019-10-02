#!/bin/bash

# demo_div : shrink current window size into 1/4

# step 1
make clean
make

# step 2
sudo cp demo_div /usr/bin
sudo cp demo_mul /usr/bin

# step 3
# set the shotcut to run demo_div
# 
# 3.1 System Settings -> Keyboard -> Shortcuts -> Custom Shortcut
# 3,2 add shotcut for this little program
#     Name: whatever you like
#     Command: demo_div
# 3.3 click Apply and configure shortcut

# This works fine on non-fullscreen applications

