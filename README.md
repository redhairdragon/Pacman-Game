## Quick Video Demo

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/fAt11nO8gX4/0.jpg)](https://youtu.be/fAt11nO8gX4)



## Normal Gameplay

![image-20190205220833885](/Users/cocoastarrion/Documents/CSPROJECTS/C++/Pacman_Game/Pacman-Game/Image/1.png)



![image-20190205221242364](/Users/cocoastarrion/Documents/CSPROJECTS/C++/Pacman_Game/Pacman-Game/Image/2.png)

The UI is trying to resemble the original pacman game with similar control.

## Control Strategy

### Enemy

Ghosts move between two different modes alternativly.

#### Patrol Mode:

![image-20190205235629434](/Users/cocoastarrion/Library/Application Support/typora-user-images/image-20190205235629434.png)

They move around red paths. And if our main character gets close to their adjacent area, corresponding ghost will start to chase it.

#### Chase Mode:

![image-20190206000231735](/Users/cocoastarrion/Documents/CSPROJECTS/C++/Pacman_Game/Pacman-Game/Image/3.png)

Two ghosts try to reach two cells in front pacman's direction. The other two ghosts try to reach two cells behind pacman direction.

### Pacman AI

The logic is simpe which is trying to eat all pellets. It clears bot-left, bot-right,top right and top left meanwhile avoiding the ghosts.

![image-20190206001246512](/Users/cocoastarrion/Documents/CSPROJECTS/C++/Pacman_Game/Pacman-Game/Image/4.png)

When the ghosts are getting really closed, it will try to find the nearest ghosts and eat them. 

![image-20190206001548402](/Users/cocoastarrion/Documents/CSPROJECTS/C++/Pacman_Game/Pacman-Game/Image/5.png)

### Path finding

Implemented A* algorithm. It sets the weights of ghost really high, so Pacman will try to avoid all ghosts when it gets fed with next direction.

## Customize Mode

![image-20190206002003774](/Users/cocoastarrion/Documents/CSPROJECTS/C++/Pacman_Game/Pacman-Game/Image/6.png)

Player can get into customize mode by pressing C. In this mode, Left-Clicking with mouse will create a wall. And Right-Clicking with mouse will reset the cell.