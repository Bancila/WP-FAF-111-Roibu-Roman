Windows Programming Laboratory Work #4
======================================

Title
-----
Windows Timer. Animation.

Contents
--------
- Windows timer

Mandatory Objectives (completed)
--------------------------------
- Create an animation based on Windows timer which involves at least 5 different drawn objects.

Objectives With Points (completed)
----------------------------------
- Increase and decrease animation speed using mouse wheel. **(2 pt)**
- Add animated objects which interact with each other. **(2-6 pt)**

John Conway's "Game Of Life"
----------------------------
The Game Of Life is a zero-player game (meaning that its evolution is determined by its initial state, requiring no further input), developed in 1970 by the British mathematician, John Horton Conway. 
The rules are pretty straight forward:
1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overcrowding.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

![Game Of Life](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%234/screens/about.jpg)


I won't go into details about this game, but I will include few links if you are currious. 
In the research process, I found this "game" to be very interesting, and pretty philosiphical actually. 
You'll see what I'm talking about in the YouTube links below.

[Wikipedia](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)  
[YouTube (part 1)](http://youtu.be/FdMzngWchDk)  
[YouTube (part 2)](http://youtu.be/k2IZ1qsx4CM)  

Application Creation Steps
--------------------------
In the development process, I consulted the recommanded book (["Programming Windows, 5th Edition", by Charles Petzold](http://www.charlespetzold.com/pw5/)).
Also, I found myself consulting the documentation on the [MSDN](http://msdn.microsoft.com) page very often.

First of all, I made wireframe models of the application's window and dialogbox, with general layout and functionality, using the [MockFlow](http://mockflow.com/) tool. 

![Window Mockup](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%234/screens/mockup.png)

Result Application
------------------
This is a screen shot of the application's window in my native Mac OS X enviroment, running the app using [Wine](http://www.winehq.org/).

![Window Screenshot 1](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%234/screens/screen1.png)

![Window Screenshot 2](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%234/screens/screen2.png)

Using the app
-------------
To start using the application, you must select a configuration from the `Life Form` dropdown list. 
There are 5 predefined configurations, and a `Draw Some!` option, which allows the user to set the living cells himself. 
Confirm your choice by pressing the `Set` button.

After a configuration is selected, the animation can be controled by the `Start` and `Stop` buttons. 
The mouse wheel controls the speed. 
The `Color` checkbox adds color randomization to the game, for additional awesomeness.

Conclusions
-----------
This laboratory work was pretty interesting. 
I didn't implement all my ideas, due to the lack of time, but I found out about this amazing game. 

I also didn't use double buffering, or another flicker solving technique, because it won't make any difference - the application doesn't draw an image, so it would be hard to perceive the flicker free randomly appearing squares.

The laboratory work was interesting because I got to implement a great concept, and I look forward to the next lab.
