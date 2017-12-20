# Menorah for Chanukah.
Arduino implementation of IR driven Chanukiah/Menorh for the holiday.
This could easily be fit into the printable menorah from here https://www.thingiverse.com/thing:1984191
## IR Library dependency
IRremote - https://github.com/shirriff/Arduino-IRremote.git
Remember that each IR remote has its own codes and timing. there is a wait on the loop to make sure the read is of the first press and there is also an ignore multi click code in the case.
you will need to adjust the IR output to your remote if the numbers dont produce the same code.
Also remember that the IR is faster so a useage of Serial.println is going to affect the code output and you might be getting the wrong output.
I have left the Serial.println for each number but use them when experimenting with your ID's and remove them once you are ready.
##Acknoledgements
Code was derived from the Mitzvah Bot project https://github.com/elahd/MitzvahBot