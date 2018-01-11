# RingFinderRobot

This repository includes the code that was used to build Gollum, an outdoor mobile robot to perform GPS following, obstacle avoiding, wall following, color detection, parallel alignment and robotic arm manipulation.

# Task:

The robot starts from within the starting circle of 1m in radius. Out of three pre-defined target locations, one location is chosen at random and give to us in the start. We input the target location using a keypad/set of 3 switches. The robot should the follow GPS and visit the target, which is 20m away. On the way, there is a "forest" of obstracles (30 cm cubes) which the robot should avoid. Target is marked by a circle of white line (3cm thickness) 2m in radius around the target point.

At the target point, lies a cylindar, 50cm in radius. The cyclindar has 40 cm wide entrance on one side.The robot should find the cylindar, move to meet it, follow the wall around it, find the entrance, move in. Inside the cylindar lies a 5 cm high, 40cm diameter plate that contains a metal ring og 6cm diameter anywhere in it. The robot should be able to search and pick up the ring with an arm.

Then then robot should return to the starting location and stop.
