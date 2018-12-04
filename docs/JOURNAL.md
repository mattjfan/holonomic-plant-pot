# Build Journal
Wanted to try this new thing of keeping a markdown journal for my projects. We'll see how this goes.

## 11/2/18
Decided to start maintaining this Journal. Officially, I started the build last week (10/26/18). The prints for the first prototype, and some of the code, have already finished, and been assembled. Currently working on putting together the electronics. I started with a resistor pull-down board to connect to the light-sensing array, but accidentally neglected to include the reading wires on the board ☹ Will need to either adjust the designs, or redo the board.

## 11/23/18
Soldered the motor controller board. Was able to get movement, but sporadically. Could be an issue with wires crossing, or not enough current.

## 12/1/18
Trying to finish by Monday. Resoldered the light-sensing board. Getting intermittent connection issues, with some of the inputs zeroing out. My suspicion is that it's an issue with the easy-connect wire terminals. Was still able to get a proof of concept out, testing basic light source detection through processing. Got the entire set-up connected.

Planning on running the first full-system test by EOD tonight.
Was able to get some simple motion, but now I'm getting nothing from the wheel base. Will check again tomorrow.

Still need to build a tether for more comprehensive systems tests.
Also, will need to build the solder the attiny control board if I want it to run untethered.

## 12/2/18
Update: It's currently 1:47 AM. I identified an issue in the motor control board, in that I forgot to connect the pwm control pins on for the h-bridge pairs on each chip. Also, some connections are coming loose again. Will fix this in the morning, and try another systems test.

3:41 AM: Still no luck. Soldered the pwm control pins, but now there's no movement. Seems to be an issue at least with one of the jumpers routing power, as it seems the point where it's soldered is impeding current flow. My guess is that there's some layer built up between the pin and the solder. Will look into it in the morning.

11:01 AM: Fixed on issue on the motor control board with a broken transistor on the right forward control sub-assembly. Also, identified an incorrect transistor used in left strafe control sub-assembly (accidentally mixed in C1815 instead of 2n3904).

12:30 PM: Thought I burnt out another transistor, swapped it out (that's 3/4 transistors swapped). After I made the switch, noticed that the inverting wire from the collector was actually soldered to the base. Swapped it out, and was able to get movement. Will do a full systems test in an hour.

3:09 PM: Ran another movement test. Was able to get motion in forward and backwards directions, however the direction enums aren't properly corresponding to the output directions. Furthermore, after additional testing, enums aren't able to produce an output state corrsponding to a left turn (CAN do forward, backwards, and right). Also, brake command doesn't seem to work after prolonged use, and I think I saw motors reverse without command. This is only with subsystem A. Will try for subsystem B, and log results as well.

3:16 PM: Subsystem B test is succesful, and operational (turns might be inverted, but we can fix that n the code). Seems likely that there's something wrong with subsystem A. 

3:38 PM: Noticed unintended contact between two solder traces. Used a razor to seperate the traces, and both subsystems are operational!

3:42 PM: 💩 One of the motor terminals snapped off.
