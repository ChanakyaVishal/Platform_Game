Graphics Assignment 1
======================

Game
====
The world consists of a floor with a small semicircular pond and a trampoline. Flying balls of
different colours (each corresponding to certain points) will traverse the screen above the
ground at various heights (random) from left to right. The balls need to be densely located so
that its possible to destroy multiple balls using the boost obtained by destroying one. Some
of the flying balls should have a rectangular slab attached at different angles, if the players
lands on these slopes he/she would be launched at an angle of reflection from the
perpendicular to the slab following the laws of reflection. Later, a magnet should appear and
disappear randomly on either sides of the game which will cause the player’s motion to be
influenced (make sure projectile like motion [constant horizontal acceleration] is followed). At
a later level, spiked porcupines should appear which if the player lands on will result in a
penalty incurred and the porcupine disappears. Your initial game can have fixed boundaries
where attempting to cross the boundaries would not work and you would be reflected back.

Objects and Physics:
==============
You should incorporate the basic laws of motion (Newton’s Laws) into the behaviour/ motion
of the objects. The minimum set of factors you need to consider are:
1. Water: When the player is inside the water body, movement speed is slowed down
and the height reached by jumping from inside is also shorter. The floor of the water
should be a semi-circle and the player on falling in the water shouldn’t bounce off, but
follow the curve until the lowermost point is reached (provided the player isn’t
explicitly moving it sideways). If the player is moving left or right, he should follow the
path along the semi-circle.
2. Inclined slopes on some flying balls: If the player lands on these slopes, he/she
would be launched at an angle of reflection from the perpendicular to the slab
following the laws of reflection.
3. Trampoline: Landing on the trampoline will cause the player to jump higher than
usual (Make sure the player starts off faster and eventually slows down and doesn’t
just reach a higher point with the same speed).
4. Magnet: The player’s path needs to be influenced by the magnet. Assume magnet
causes a constant attractive force in its direction.

Controls:
============
	A - Left
	D - Right
	Space - Jump
	Arrow Up - Zoom in
	Arrow Down - Zoom out
	W - Special power up if collected (unlocked when you get points which are a multiple of 100)
	P - Pause

Miscellaneous
===============
1. The camera moves with the player enabling a larger play area in a given screen real estate.
2. The score is displayed at the title screen of the window.
3. The player speed is hindered when he reaches the top layer with the green balls, these balls push you downwards so that it is more difficult to obtain them.
4. There is a power up which can be used by clicking 'W' after you have obtained the special ball which appears everytime you get a score which is a multiple of 100. You can hold only one of this power up 	at a time.
6. Score:
	Yellow Ball = 5
	Blue Ball = 10
	Green Ball = 20
 
