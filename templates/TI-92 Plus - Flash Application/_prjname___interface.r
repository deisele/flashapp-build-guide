#include "%prjname%.h"
#include "tiams.h"

TOOLBOX AppMenu, RC_NO_IDS, 0, 240 {
	"Actions" {
		"WinStr",		ACM_WINSTR
		"Dialog",		ACM_DIALOG
		"Popup",		ACM_POPUP
		"Grayed-out",	ACM_NOTHING
	}
	"HFONT",			ACM_HFONT
}

DIALOG tDialog, 180, 70, NoCallBack {
	EDIT, {DF_TAB_SPACES, 12, 14}, "EDIT1", 0, 10, 11
	EDIT, {DF_TAB_SPACES, 12, 24}, "EDIT2", 11, 10, 11
	POPUP, {DF_TAB_ELLIPSES, 12, 34}, "FIRST POPUP", Popup1, 0
	POPUP, {DF_TAB_ELLIPSES, 12, 44}, "2ND POPUP", Popup2, 1
	HEADER, {0, 0, 0}, "DIALOG HEADER", PDB_OK, PDB_CANCEL
}

POPUP Popup1, RC_NO_IDS, 0 {
	"Item 1-1", 1
	"Item 1-2", 2
}

POPUP Popup2, RC_NO_IDS, 0 {
	"Item 2-1", 1
	"Item 2-2", 2
	"Item 2-3", 3
}
