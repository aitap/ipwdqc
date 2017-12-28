#include "passwdqc.h"
#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

passwdqc_params_t params;
Ihandle *password, *random_bits;

static void gen_passwd(void) {
	params.qc.random_bits = IupGetInt(random_bits, "VALUE");

	char *pass = passwdqc_random(&params.qc);
	IupSetStrAttribute(password, "VALUE", pass); // let IUP itself manage the string memory
	free(pass);

	IupSetStrAttribute(password, "SELECTION", "ALL");
	IupSetStrAttribute(password, "CLIPBOARD", "COPY");
}

static int button_cb(Ihandle* button) {
	(void)button;
	gen_passwd();
	return IUP_DEFAULT;
}

static int spin_callback(Ihandle* spin, int value) {
	(void)spin; (void)value;
	gen_passwd();
	return IUP_DEFAULT;
}

int main(int argc, char** argv) {
	passwdqc_params_reset(&params);
	IupOpen(&argc, &argv);

	password = IupSetAttributes(IupText(NULL), "READONLY=YES,EXPAND=YES,VISIBLECOLUMNS=20,ALIGNMEMT=ACENTER");

	// magic numbers taken from the manual, unlikely to change ever, defined by the size of the word list
	random_bits = IupSetAttributes(IupText(NULL), "SPINMIN=24,SPINMAX=85,SPIN=YES");
	IupSetInt(random_bits, "VALUE", params.qc.random_bits);
	// IUP will cast the SPIN_CB callback back to correct
	IupSetCallback(random_bits, "SPIN_CB", (Icallback)&spin_callback);

	Ihandle *button = IupSetCallbacks(
		IupButton("Generate", NULL),
		"ACTION",
		&button_cb,
	NULL);
	IupSetHandle("generate_button", button);

	IupShow(
		IupSetAttributes(
			IupDialog(
				IupVbox(
					password,
					IupHbox(
						IupSetAttributes(IupLabel("Random bits:"),"ALIGNMENT=ACENTER:ACENTER"),
						random_bits,
						IupFill(),
						button,
					NULL),
				NULL)
			),
			"TITLE=pwqgen,STARTFOCUS=generate_button"
		)
	);

	gen_passwd();

	IupMainLoop();
	IupClose();
	return 0;
}
