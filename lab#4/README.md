Windows Programming Laboratory Work #3
======================================

Title
-----
Basics of Working with Mouse. GDI Primitives. Bezier Curve.

Contents
--------
- Mouse
- Device context
- GDI Primitives
   - Line
   - Curve
   - Plane
   - Bitmap image
- Bezier curve

Mandatory Objectives (completed)
--------------------------------
- Draw few lines of different colors and weights.
- Draw a Bezier curve.
- Draw few plane objects of different colors, weights, filled and not.
- Draw 2 different objects using mouse.

Objectives With Points (completed)
----------------------------------
- Draw a custom bitmap image. **(1 pt)**
- Add a switch that will change mouse ability to draw objects. **(2 pt)**
- Draw a Bezier curve using mouse. **(1 pt)**
- Fill an object with a gradient. **(1 pt)**
- Delete objects using mouse clicking. **(2 pt)**
- Use mouse as an eraser of an adjustable width. **(2 pt)**

Application Creation Steps
--------------------------
In the development process, I consulted the recommanded book (["Programming Windows, 5th Edition", by Charles Petzold](http://www.charlespetzold.com/pw5/)).
Also, I found myself consulting the documentation on the [MSDN](http://msdn.microsoft.com) page very often.

First of all, I made wireframe models of the application's window and dialogbox, with general layout and functionality, using the [MockFlow](http://mockflow.com/) tool. 

NOTE: In the mockup it was specified the hotkeys for zooming, but this feature was not implemented, and I do not claim points for this.

![Window Mockup](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%233/screens/mockup.png)

Result Application
------------------
This is a screen shot of the application's window in my native Mac OS X enviroment, running the app using [Wine](http://www.winehq.org/).

![Window screenshot](https://raw.github.com/TUM-FAF/WP-FAF-111-Roibu-Roman/master/lab%233/screens/screenshot.png)

Using the app
-------------
The user specifies the tool he wants to use, selecting it from the `Tools` group. How to draw: 

- `Pen` tool will draw a continuous line with the stroke weight equal to 1, and the selectable stroke color, by selecting this tool, and **left-clicking** on the drawing area. 
- `Line` tool will draw a straight line between two points, with the selectable stroke weight and color, by **left-clicking** on the drawing area (start point), and **draging & releasing** the mouse botton (end point). 
- `Polygon` tool will draw a rectangle, with selectable stroke weight and color, filled with a selectable color, or not, by **left-clicking** on the drawing area (top left corner), and **draging & releasing** the mouse botton (bottom right corner). 
- `Ellipse` tool will draw an ellipse, with selectable stroke weight and color, filled with a selectable color, or not, by **left-clicking** on the drawing area (top left corner), and **draging & releasing** the mouse botton (bottom right corner). 
- `Bezier` tool will draw a Bezier curve, with selectable stroke weight and color. It is done in the following manner:
   - **Left-clicking**  - start point.
   - **Drag & Releas**  - 1st control point.
   - **Right-clicking** - 2st control point.
   - **Drag & Releas**  - end point.
- `Eraser` tool will erase the drawing area, with a selectable weight, leaving the drawing area clean. 

By **Ctrl + Shift + Left Click**ing, the last **polygon** or **ellipse** will be erased from the drawing area.

Conclusions
-----------
This laboratory work was an interesting one. I had the opportunity to buid an applications will a lot of basic drawing features, somewhat resembling the MS Paint application. 

The main difficulty I encountered was with limiting the allowed draing area, but I managed to solve this issue.

In this laboratory work I familiarized myself with all the drawing posibilities the Windows API gives us, and with the right way of working with the mouse, and letting the user control the application features using mouse clicks. 
This laboratory work layed an important base ground for future laboratory works, especialy in working with animations.

