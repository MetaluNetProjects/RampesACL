/*********************************************************************
 *               DMX master example for Versa2
 *	Output DMX frames to AUXSERIAL_TX  (K11 for Versa)
 *********************************************************************/
#define BOARD Versa2
#include <fruit.h>
#include <dmx.h>

//----------- Setup ----------------
void setup(void) {	
	fruitInit();			
	DMXInit();        // init DMX master module
}

// ---------- Main loop ------------
void loop() {
	fraiseService();// listen to Fraise events
	DMXService();	// DXM management routine
}


// ---------- Receiving ------------
void fraiseReceive() // receive raw bytes
{
	int i;
	unsigned char c=fraiseGetChar(); // get first byte
	unsigned char l = fraiseGetLen();
	switch(c) {
		case 30:
			i = fraiseGetInt();
			l -= 3;
			while(l) {
				DMXSet(i, fraiseGetChar());
				i++;
				l--;
			}
			break;
		//PARAM_INT(30,i); DMXSet(i, fraiseGetChar()); break; // if first byte is 30 then get DMX channel (int) and value (char).
	}
}

