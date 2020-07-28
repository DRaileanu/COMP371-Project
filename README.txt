Assignment #2 for COMP371-DD

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
Camera Zoom	-> right Control + mouse movement in y direction (up to zoom-in, down to zoom-out)
Move Forward	-> UP Arrow
Move Backward	-> DOWN arrow
Strafe Left	-> LEFT arrow
Strafe Right	-> Right arrow

---Render Modes---

P		-> points
L		-> lines
T		-> triangles (fill mode)
B		-> toggle shadows
V		-> toggle textures


---World Orientation---

Left Arrow + Right_Shift	-> rotate world clockwise around y-axis
Right Arrow + Right_Shift	-> rotate world counter-clockwise around y-axis
Up Arrow + Right_Shift		-> rotate world counter-clockwise around x axis
Down Arrow + Right_Shift	-> rotate world clockwise around x axis
Home Button			-> resets world orientation, position and camera


---Selecting Model to Transform---

1		-> Dan Raileanu's Letter Model (N)
2		-> Dan Raileanu's Digit Model (1)
3		-> Mohamed-Yasser's Letter Model (H)
4		-> Mohamed-Yasser's Digit Model (5)
5		-> Muherthan Thalayasingam's Letter Model (H)
6		-> Muherthan Thalayasingam's Digit Model (2)
7		-> Radhep Sabapathipillai's Leter Model (D)
8		-> Radhep Sabapathipillai's Digit Model (3)
9		-> Mohd Tanvir's Letter Model (H)
0		-> Mohd Tanvir's Digit Model (1)
BACKSPACE	-> Point Light Source (default selected)

---Transforming Model---

U		-> Scale up continously
U+Left_Control	-> Scale up incrementally by 15%

J		-> Scale down continously
J+Left_Control	-> Scale down incrementally by 15%

A		-> Strafe left continously (-x direction)
A+Left_Control	-> Strafe left incrementally by 5 units

D		-> Strafe right continously (+x direction)
D+Left_Control	-> Strafe right incrementally by 5 units

W		-> Move forward continously (-z direction)
W+Left_Control	-> Move forward incrementally by 5 units

S		-> Move backwards continously (+z direction)
S+Left_Control	-> Move backwards incrementally by 5 units

W+Left_Shift	-> Move up continously (+y direction)
S+Left_Shift	-> Move down continously (-y direction)

Q		-> Rotate left continously(counter-clockwise around y-axis)
Q+Left_Control	-> Rotate left incrementally by 5 degrees (counter-clockwise around y-axis)

E		-> Rotate right continously(clockwise around y-axis)
E+Left_Control	-> Rotate right incrementally by 5 degrees(clockwise around y-axis)

SPACE		-> Places Model somewhere randomly on the grid

R		-> Pitch forward top side of model
F		-> Pitch backwards top side of model

Z		-> Shear top side of model to the left along -x direction
X		-> Shear top side of model to the right along x direction



----------------

Additional Notes

----------------

Pressing several keys at once to select models results in selecting model with highest associated number.
