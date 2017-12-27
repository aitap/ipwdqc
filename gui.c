#include "passwdqc.h"
#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

passwdqc_params_t params;
Ihandle *password, *random_bits;

int gen_passwd(Ihandle* button) {
	(void)button; // only the text fields matter
	params.qc.random_bits = IupGetInt(random_bits, "VALUE");
	char *pass = passwdqc_random(&params.qc);
	IupSetStrAttribute(password, "VALUE", pass); // let IUP itself manage the string memory
	free(pass);
	return IUP_DEFAULT;
}

int main(int argc, char** argv) {
	passwdqc_params_reset(&params);
	IupOpen(&argc, &argv);

	password = IupSetAttributes(IupText(NULL), "READONLY=YES,EXPAND=YES,VISIBLECOLUMNS=20,ALIGNNEMT=ACENTER");
	// magic numbers taken from the manual, unlikely to change ever, defined by the size of the word list
	random_bits = IupSetAttributes(IupText(NULL), "SPINMIN=24,SPINMAX=85,SPIN=YES");
	IupSetInt(random_bits, "VALUE", params.qc.random_bits);

	IupShow(
		IupDialog(
			IupVbox(
				password,
				IupHbox(
					IupSetAttributes(IupLabel("Random bits:"),"PADDING=10x20"),
					random_bits,
					IupFill(),
					IupSetCallbacks(
						IupButton("Generate", NULL),
						"ACTION",
						&gen_passwd,
					NULL),
				NULL),
			NULL)
		)
	);

	IupMainLoop();
	IupClose();
	return 0;
}
