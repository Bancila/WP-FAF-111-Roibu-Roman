Windows Programming Laboratory Work #5
======================================

Title
-----
FAF Hack Day.

Introduction
------------
For this laboratory work, instead of a Win32 API application, I will present the web-app we (a team of 6, mostly FAF students) developed during the FAF Hack Day event. 
The application resides in repository, on [GitHub](https://github.com/DTailor/Lore-Square).

Mandatory Objectives
--------------------
- You have to have a working application/prototype after hackaton.
- During hackaton use a public repository on GitHub for your project.

Development Process
-------------------
During the development of the application, we were divided mainly into 2 sub-teams: front-end development team (3 people) and back-end development team (3 people). 
This aided the speed and efficiency of the development process, as we had to work on a smaller piece of the application, and not worry about the other. 
The separation of front-end and back-end was so efficient, that after working separately for more than 5 hours, having 2 main branches (1 for front, and 1 for back), we merged these 2 branches without a single conflict. :white_check_mark:
Also, we used [Asana](https://asana.com) as a management tool, where we posted new tasks which needed to get done, assign the right people (usually, the ones that were free at the moment) to each task, and mark them upon comletion. 
However, due to using a previously unknown tool, and having some issues with it, after about 5 AM, the entire team had to focus on front-end (JavaScript). 

LoreSquare
----------
The idea of LoreSquare is somewhat similar to Foursquare (hence the name), the major difference being that a user, rather than checking-in into a place, checks-in a piece of knowledge, that belongs to a classification. 
The classifications were developed by [Association for Computing Machinery](http://www.acm.org/). There are a few top categories, which are divided into subcategories (in a Tree-like structure), at the lowest level being the classifications to wich the check-in-able pieces of knowledge (a book, course, blog post, talk, etc.) belong. 
Every check-in of a user raises his level of expertise in the coresponding classification. 
The user with the highest level of expertise (expressed in rank points), is declared Mayor of this classification, untill another user with a higher rank steals this title. 

Result Application
------------------
The result of the FAF Hack Day is a prototype application, with core functionalities (as well as some additional ones, like Search autocomplete). 
At this moment, a user can perform basic sign-in / sign-out actions, as well as sign-in using his Facebook account. 
On the home page, a user can show / hide his profile information, by clicking the top left button. 
He can also browse the different classifications, by clicking on a square and having it expand. 
To zoom back out of the current classification, the user must click the Up button, on the top panel. 
The user can also perform an autocompleted search of the classifications. He is then taken to the classification, from the top classifications (although this feature works only on a test page). 

Screen Shots
------------

![Homepage](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%235/screens/homepage.png) 

![SignIn](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%235/screens/signin.png) 

Conclusions
-----------
The idea of this application (credits to Mr. Dumitru Ciorbă) was very interesting, and it was a tackle to bring it to life. 
Although having to confront some problems, the development process was a smooth and fast one. 
Given a limited (24 h) amount of time and a huge project, our team managed to put together a functional prototype, even with some additional features, that lacks only a few importaint features. 

The participation in FAF Hack Day event was very rewarding and fun. 
Hope to see more such events in the near future, and I'll be sure to participate again. 

