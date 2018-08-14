#include "tiams.h"
#include "%prjname%.h"
#include "%prjname%_interface.h"


/*
Function prototypes
*/

static void AP_app (pFrame self, PEvent e);
DWORD NoCallBack (WORD DlgId, DWORD Value);


/*
App object frame
*/

FRAME(appObj, OO_SYSTEM_FRAME, 0, OO_APP_FLAGS, 4)
	ATTR(OO_APP_FLAGS, APP_INTERACTIVE)
	ATTR(OO_APP_NAME, "%prjname%")
	ATTR(OO_APP_PROCESS_EVENT, &AP_app)
	ATTR(OO_APP_DEFAULT_MENU, &AppMenu )
ENDFRAME


/*
Global variables
*/

pFrame pAppObj = (pFrame)&appObj; // must be 1st!
WINDOW appW;
char buf[22];


/*
Main function, called by the OS with the event as a parameter
*/

static void AP_app (pFrame self, PEvent e) {
	Access_AMS_Global_Variables;
	HANDLE hPopup;
	short key;
	WORD options[3];

	switch (e->command) {
		case CM_START:
			MO_currentOptions ();

			if (WinOpen (&appW, e->info.startInfo.startRect, WF_TTY | WF_DUP_SCR | (MO_option[MO_OPT_SPLIT_SCREEN] == D_MODE_SPLIT_FULL? WF_NOBORDER : 0))) {
				WinClr (&appW);
			} else {
				EV_quit ();
			}
			strcpy (buf, "FIRST");
			strcpy (buf + 11, "SECOND");
			break;

		case CM_ACTIVATE:
			EV_defaultHandler (e);
			EV_disableCmd (ACM_NOTHING);
			WinBeginPaint (&appW);
			WinActivate (&appW);
			WinStr (&appW, "Just activated\n");
			break;

		case CM_DEACTIVATE:
			WinEndPaint (&appW);
			EV_defaultHandler (e);
			break;

		case CM_QUIT:
			if (appW.Next) {
				WinClose (&appW);
				appW.Next = NULL;
			}
			break;

		case CM_KEY_PRESS:
			key = e->info.keyInfo.keyCode;
			if ((key <= 0xFF && isprint(key)) || KB_ENTER == key) {
				WinChar (&appW, key);
			} else {
				EV_defaultHandler (e);
			}
			break;

		case CM_WPAINT:
			DrawWinBorder (&appW, &appW.Window);
			WinBackupToScr (&appW);
			break;

		case ACM_WINSTR:
			WinStr (&appW, "APP1 CMD1\n");
			break;

		case ACM_DIALOG:
			options[0] = 1; // default to 1st popup item
			options[1] = 1;
			if (KB_ENTER == Dialog (&tDialog, -1, -1, buf, options)) {
				char outStr[256];

				sprintf (outStr, "Edit1: %%s\nEdit 2: %%s\nPopup1: %%d\nPopup2: %%d", buf, buf + 11, options[0], options[1]);
				DlgNotice ("tDialog", outStr);
			}
			break;

		case ACM_POPUP:
			if (hPopup = PopupNew ("DYNAMIC POPUP", 0)) {
				DynMenuAdd (hPopup, 0, buf, 1, DMF_TEXT | DMF_TOP);
				DynMenuAdd (hPopup, 0, buf + 11, 2, DMF_TEXT | DMF_TOP);
				DynMenuAdd( hPopup, 0, "LAST ITEM", 3, DMF_TEXT | DMF_TOP );
				if (!(MenuFlags (hPopup) & MF_ERROR)) {
					char outStr[256];
					short vSelect;

					vSelect = PopupDo (hPopup, -1, -1, 0);
					sprintf (outStr, "Selected %%s", PopupText (hPopup, vSelect));
					DlgNotice ("dPopup", outStr);
				}
				HeapFree (hPopup);
			}
			break;

		case ACM_HFONT:
			WinFont (&appW, F_8x10);
			break;

		default:
			EV_defaultHandler(e);
			break;
	}
}


/*
Callback function for dialogs
This function is provided as a callback function when a dialog is opened.
Because we don't need a callback function here, we just leave it empty.
*/

DWORD NoCallBack (WORD DlgId, DWORD Value) {
	return TRUE;
}
