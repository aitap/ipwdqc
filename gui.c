#include "passwdqc.h"
#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

passwdqc_params_t params;
Ihandle *password, *random_bits;

int gen_passwd(Ihandle* button) {
	(void)button; // I don't need it
	params.qc.random_bits = IupGetInt(random_bits, "VALUE");
	char *pass = passwdqc_random(&params.qc);
	IupSetStrAttribute(password, "VALUE", pass);
	free(pass);
}

int main(int argc, char** argv) {
	IupOpen(&argc, &argv);

	password = IupSetAttributes(IupText(NULL), "READONLY=YES,EXPAND=YES,VISIBLECOLUMNS=20,ALIGNNEMT=ACENTER");
	random_bits = IupSetAttributes(IupText(NULL), "SPINMIN=24,SPINMAX=85,SPIN=YES,VALUE=47");

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

	passwdqc_params_reset(&params);

	IupMainLoop();
	IupClose();
	return 0;
}
