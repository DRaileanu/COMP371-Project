Assignment #1 for COMP371-DD


For clarity, Student Model refers to the letter and digit models each student had to create.
Letter/Digit Model refers to the letter/digit in the Student Model.



-----
Build
-----

Build using Visual Studio 2017, SDK version: 10.0
Used 32-bit libraries, so run in x86 mode.
Open Assignment1.sln from base directory. Debug->Start without debugging.
If error, try Project->Target Solution, chose SDK version: 10.0.16299.0 (or latest)

All dependencies are included in the project already.

---------

CONTROLS:

---------



---Camera---

Camera Pan 	-> right mouse button + mouse movement in x direction

Camera Tilt 	-> left mouse button + mouse movement in y direction

Camera Zoom	-> left Control + mouse movement in y direction (up to zoom-in, down to zoom-out)



---Render Modes---

P		-> points

L		-> lines

T		-> triangles (fill mode)



---World Orientation---

Left Arrow	-> anti-clockwise rotation about positive x-axis

Right Arrow	-> clockwise rotation about positive x-axis

Up Arrow	-> anti-clockwise rotation about positive y-axis

Down Arrow	-> clockwise rotation about positive y-axis

Home Button	-> resets world orientation and camera (comment line 325-326 to not reset camera, but only world orientation)



---Selecting Model to Transform---

1		-> Dan Raileanu's Student Model (N1)

2		-> Mohamed-Yasser Houssein's Student Model (H5)

3		-> Muherthan Thalayasingam's Student Model (H2)

4		-> Radhep Sabapathipillai's Student Model (D3)

5		-> Mohd Tanvir's Student Model (H1)

6		-> Letter Model of currently selected Student Model

7		-> Digit Model of currently selected Student Model



---Transforming Model---

A		-> Move in negative x direction

D		-> Move in positive x direction
W		-> Move in negative z direction
S		-> Move in positive z direction
Q		-> Rotate anti-clockwise about Model's Y-axis
E		-> Rotate clockwise about Model's Y-axis

U		-> Scale-Up

J		-> Scale-Down




----------------

Additional Notes

----------------

When testing program on remote Concordia lab computers, glfw returns larger mouse position offsets compared to our own computers for same mouse movement.
If experiencing this, consider lowering mouse sensetivity on line 61.

By default, Mohd Tanvir's Student Model is selected (same as pressing 5).

If selected letter/digit of given Student Model and want to switch back to moving both at once, select Student Model again.

Pressing several keys at once to select models results in selecting model with highest associated number.
