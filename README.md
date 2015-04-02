# chargedispersion

-- KD, Mar 31, 2015 --
 
Simulation of MPGD charge dispersion for various readout structures.
Pad structure:

y/ ^           pad index
mm |           ^
   |          /
12 |--|--|--|/
   |4 |5 |6 |
 6 |--|--|--|
   |1 |2 |3 |
 0 |-------------------->x/mm
   0  2  4  6  8  10

The pad "index" runs from 1 at (0,0) in a meander up to 6 at (4,6) with pad-size
2x6 mm^2
Typical center for the charge cloud should be in the center of pad 3: (1,3).
Pads 1 - 6 see more or less charge. All other pads left and below (1,3) "see"
symmetric distributions.

--How to run the program:--
You can start off with a fresh compilation and it is worth to remove all older
shared-object (*.so) and dependency (*.d) files. Then just start 'root' and
execute the macro 'macroRunLoop.C'.
Altogether:
[~/directory] rm *.d *.so; nice root -l // nice for shared systems
root [0] .x macroRunLoop.C

The macro takes as input the parameters given in 'prfinput.dat'. The parameters
are 'x0 y0 lx ly stpSzx stpSzy' with x0 = x-center of charge cloud;
y0 = y-center of charge cloud; lx = number of steps in x-dir;
ly = number of steps in y-dir; stpSzx = step-size in x; stpSzy = step-size
in y-dir. Change these numbers as you like. Note, the larger lx and ly the
more calculations have to be performed and the more computing time is required.
The output is a file (.root) that contains a series of histograms, which are
named according to their li (padindex), lx, and ly. For convenience it also
shows the pad-coordinates relative to the center of the charge cloud.
Each histogram contains the charge "seen" on that particular pad as a function
of sampling-time of the electronics.

To-do:
- change the pad-size parameters from integer to double so that it can take on
any shape and size we want. This also requires rewriting the loops for pads
1 - 10.
