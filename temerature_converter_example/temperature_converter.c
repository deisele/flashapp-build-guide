#include <tiams.h>
#include "temperature_converter.h"
#include "interface.h"

static void AP_app(pFrame self, PEvent e);
BOOL is_str_a_long_int(const char *str);
long int str_to_long_int(const char *str);

static void AP_app(pFrame self, PEvent e);
FRAME(appObj, OO_SYSTEM_FRAME, 0, OO_APP_FLAGS, 4)
   ATTR(OO_APP_FLAGS, APP_INTERACTIVE)
   ATTR(OO_APP_NAME, "Temperature converter")
   ATTR(OO_APP_PROCESS_EVENT, &AP_app)
   ATTR(OO_APP_DEFAULT_MENU, &AppMenu )
ENDFRAME

pFrame pAppObj = (pFrame)&appObj; // must be 1st!
WINDOW appW;
char buf_cels[11];
char buf_fahr[11];


/*
Main function, called by the OS with the event as a parameter
*/

static void AP_app(pFrame self, PEvent e) {
	Access_AMS_Global_Variables;

	switch (e->command) {
		case CM_START:
			MO_currentOptions();

			if (WinOpen(&appW, e->info.startInfo.startRect, (MO_option[MO_OPT_SPLIT_SCREEN] == D_MODE_SPLIT_FULL? WF_NOBORDER : 0) )) {
				WinClr(&appW);
			} else {
				EV_quit();
			}
			break;

		case CM_ACTIVATE:
			EV_defaultHandler(e);
			WinBeginPaint(&appW);
			WinActivate(&appW);
			break;

		case CM_DEACTIVATE:
			WinEndPaint(&appW);
			EV_defaultHandler(e);
			break;

		case CM_QUIT:
			if (appW.Next) {
				WinClose(&appW);
				appW.Next = NULL;
			}
			break;

		case CM_WPAINT:
			DrawWinBorder(&appW, &appW.Window);
			WinBackupToScr(&appW);
			break;

		case ACM_CELC:
			// If you want to expand this demo app, you could do the input and output in the main window instead of in a dialog.
			// You could also do all of the calculations on the expression stack (estack) to make the app more flexible (better integration into the OS, bigger numbers).
			if (KB_ENTER == Dialog(&fahr_to_cels, -1, -1, buf_fahr, NULL)) {
				long int input;

				if (is_str_a_long_int(buf_fahr) == FALSE) {
					DlgNotice("Error", "Invalid input.");
				} else if ((input = str_to_long_int(buf_fahr)) < -459) {
					DlgNotice("Error", "Temperature is lower than absolute zero (-459.67" RF_DEGREES "F).");
				} else {
					char out_str[256];
					double result;

					result = ((double)input - 32) / 1.8;

					sprintf(out_str, "%li" RF_DEGREES "F are %.1f" RF_DEGREES "C.", input, result);
					DlgNotice("Result", out_str);
				}
			}
			break;

		case ACM_FAHR:
			if (KB_ENTER == Dialog(&cels_to_fahr, -1, -1, buf_cels, NULL)) {
				long int input;

				if (is_str_a_long_int(buf_cels) == FALSE) {
					DlgNotice("Error", "Invalid input.");
				} else if ((input = str_to_long_int(buf_cels)) < -273) {
					DlgNotice("Error", "Temperature is lower than absolute zero (-273.15" RF_DEGREES "C).");
				} else {
					char out_str[256];
					double result;

					result = (double)input * 1.8 + 32;

					sprintf(out_str, "%li" RF_DEGREES "C are %.1f" RF_DEGREES "F.", input, result);
					DlgNotice("Result", out_str);
				}
			}
			break;

		default:
			EV_defaultHandler(e);
			break;
	}
}


/*
Checks whether a string can be converted to a long int (32 bit)
*/

BOOL is_str_a_long_int(const char *str) {
	Access_AMS_Global_Variables;

	// check for minus character
	if ((unsigned char)*str == SF_NEGATIVE) {
		str++;
	}

	// check for empty string or only a single minus
	if (*str == '\0') {
		return FALSE;
	}

	// check if all characters are digits
	while (*str != '\0') {
		if (!isdigit(*str)) {
			return FALSE;
		}

		str++;
	}
	
	return TRUE;
}


/*
Converts a string to a long int (32 bit)
*/

long int str_to_long_int(const char *str) {
	long int number;
	BOOL negative;

	number = 0;
	negative = FALSE;

	if ((unsigned char)*str == SF_NEGATIVE) {
		negative = TRUE;
		str++;
	}

	while (*str != '\0') {
		number = (number * 10) + (*str) - '0';
		str++;
	}

	if (negative) {
		number = -number;
	}

	return number;
}
