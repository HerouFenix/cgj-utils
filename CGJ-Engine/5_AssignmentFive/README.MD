During execution one could press the 'G' key in order to swap between Euler and Quaternion rotation modes.
The first of these modes computes the camera's rotation matrix by creating our Matrix4's RotationX and RotationY matrices. 

The second of these utilizes our Quaternion class instead to retrieve that class' rotation matrix (which is computed using the Quaternion's parameters as opposed to the Matrix 4 rotation matrices which use the angles directly).

When using Euler we have a specific rotation matrix for each of the axis on which we want to rotate around. This may cause the Gimball Lock problem when trying to manage a rotation in 2 or more axis which coincide. Basically what happens is that we lose one degree of rotation freedom and start rotating in a 2d environment instead of a 3d one, since one of the axis will inadvertadly be rotated to the one it is "locked" with. So the underlying cause of gimbal lock is actually being forced by the fact that Euler represents rotations and orientations using three axial rotations - Pitch, Roll, Yaw.

For Quaternions, however, this problem doesn't surface due to the fact that we aren't computing several different rotations matrices. There is no pitch, roll and yaw in quaternions. We instead pick a rotation axis, which can be a combination of the base world axis (x,y,z), and how much we want to rotate. In this all of our rotations are actually caused by one single rotation matrix rather than a combination of three different ones that could interfere with each other.

More specifically, any rotation around a fixed point is equivalent to a single rotation by a given angle about a fixed axis that runs thorugh the fixed point. So, any rotation or combination of rotations in three dimensions can be represented as a combination of a vector and a scalar. Our quaternions give us a constructor that allows us to create them using exactly this, encoding this "rotation information" into four numbers that can be then used to apply the corresponding rotation to the corresponding object.


// CONTROLS //
M - use mouse to control rotation
X - select "rotate over x mode"
Y - select "rotate over y mode"
Z - select "rotate over z mode"
UP/DOWN Keys - Rotate (depending on mode)

W - Zoom in (decrease radius)
S - Zoom out (increase radius)

F - Lock/Unlock mouse to middle of screen
R - Reset camera

G - Swap between Euller and Gimball rotation modes

Note: If "Mouse" mode is active than you can rotate the camera using your mouse. If X, Y, or Z mode is active you can rotate over the axis corresponding to the mode using the UP/DOWN keys. All these modes are mutually exclusive