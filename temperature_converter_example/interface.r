#include "temperature_converter.h"
#include "tiams.h"

TOOLBOX AppMenu, RC_NO_IDS, 0, 240 {
	"To Celsius",		ACM_CELC
	"To Fahrenheit",	ACM_FAHR
}

DIALOG cels_to_fahr, 0, 0, NoCallBack {
	EDIT, {0, 12, 14}, "Celsius:    ", 0, 9, 11
	HEADER, {0, 0, 0}, "Celsius -> Fahrenheit", PDB_OK, PDB_CANCEL
}

DIALOG fahr_to_cels, 0, 0, NoCallBack {
	EDIT, {DF_TAB_SPACES, 12, 14}, "Fahrenheit: ", 0, 9, 11
	HEADER, {0, 0, 0}, "Fahrenheit -> Celsius", PDB_OK, PDB_CANCEL
}