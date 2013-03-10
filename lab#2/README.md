Windows Programming Laboratory Work #2
======================================

Title
-----
Advanced Form Elements. Child Windowses. Basics of Working With Keyboard.

Contents
--------
- The Keyboard
- Child Window Controls
  - Scroll Bar
  - Listbox
- Menus and Other Resources
- Dialog Boxes

Mandatory Objectives (completed)
--------------------------------
- Display a dialog box on some event.
- Add a system menu to your application with at least 3 items.
- Add a scroll bar that will change any visible parameter of any other element.
- Hook keyboard input. Add 2 custom events for 2 different keyboard combinations.

Objectives With Points (completed)
----------------------------------
- Add a listbox and attach some events when any element is accessed (double-clicked). **(2 pt)**
- Add 2 scroll bars that will manage main window size or position. **(1 pt)**
- Customize your application by adding an icon and using different cursor in application. **(1 pt)**
- Use a scroll bar to scroll through application working space. Scroll should appear only when necessary. **(1 pt)**

Application Creation Steps
--------------------------
In the development process, I consulted the recommanded book (["Programming Windows, 5th Edition", by Charles Petzold](http://www.charlespetzold.com/pw5/)).
Also, I found myself consulting the documentation on the [MSDN](http://msdn.microsoft.com) page very often.

First of all, I made wireframe models of the application's window and dialogbox, with general layout and functionality, using the [MockFlow](http://mockflow.com/) tool. 

![Window Mockup](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%232/pictures/window_mockup.png)

![Dialogbox Mockup](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%232/pictures/dialog_mockup.png)

Result Application
------------------
This is a screen shot of the application's window and dialogbox in the virtual Windows 8 environment:

![Window screenshot](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%231/pictures/window_screen.png)

![Dialogbox screenshot](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%231/pictures/dialog_screen.png)

Building is tricky
------------------
Since I've done almost all my development in my MacOS environment, I have all my source files in the lab#2 directory. 
However, to make sure that the DialogBox works properly, the application should be built in a Windows environment, inside a CodeBlocks project. 
The file tree of the project is provided. 

![Project file tree](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%231/pictures/filetree.png)

As long as this hierarchy is ensured, without any modifications made to the files (main.cpp, resource.h, resource.rc), the project should build properly, and the dialog box should work as expected. 
The screenshots prove the above statement.

Conclusions
-----------
This laboratory work was a lot more chalenging than the last one. Although I experienced some issues working with scrollbars and the dialogbox, I managed to implement all the features I had planed (all mandatory, as well as additional tasks). 

The main difficulty was working with resource (.rc) files without a proper IDE :). I developed almost 
the entire application in a text editor (Sublime Text 2), but when I got to the part when I had to work with resource files, I switched to my vitrual machine, Windows 8, and continued developing in CodeBlocks (you can find more info on how to build my application in CodeBlock in the previous section). 

This laboratory work went a lot more in depth, covering some more advanced topics (dialogboxes, window menus, scrollbars, listboxes, keyboard events), and it was challenging to complete all the tasks. This broadened and deepened my understanding of Event-Driven Programming, message-sending, and Win32 API in particular.
