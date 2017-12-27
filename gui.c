#include <passwdqc.h>
#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

int main(int argc, char** argv) {
	passwdqc_params_t params;
	passwdqc_params_reset(&params);
	char *pass = passwdqc_random(&params.qc);
	printf("%s\n", pass);
	const char *diag = passwdqc_check(&params.qc, pass, "", NULL);
	free(pass);
	if (!diag) diag = "OK";
	printf("%s\n", diag);
	return 0;
}
