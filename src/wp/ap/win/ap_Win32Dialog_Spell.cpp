/* AbiWord
 * Copyright (C) 1998,1999 AbiSource, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */


#include <windows.h>

#include "ut_string.h"
#include "ut_assert.h"
#include "ut_debugmsg.h"

#include "xap_App.h"
#include "xap_Win32App.h"
#include "xap_Win32Frame.h"

#include "ap_Strings.h"
#include "ap_Dialog_Id.h"
#include "ap_Dialog_Spell.h"
#include "ap_Win32Dialog_Spell.h"

#include "ap_Win32Resources.rc2"

/*****************************************************************/

XAP_Dialog * AP_Win32Dialog_Spell::static_constructor(XAP_DialogFactory * pFactory, XAP_Dialog_Id id)
{
   AP_Win32Dialog_Spell * p = new AP_Win32Dialog_Spell(pFactory,id);
   return p;
}

AP_Win32Dialog_Spell::AP_Win32Dialog_Spell(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id)
  : AP_Dialog_Spell(pDlgFactory,id)
{
}

AP_Win32Dialog_Spell::~AP_Win32Dialog_Spell(void)
{
}

/*****************************************************************/

void AP_Win32Dialog_Spell::runModal(XAP_Frame * pFrame)
{
   // call the base class method to initialize some basic xp stuff
   AP_Dialog_Spell::runModal(pFrame);

	// raise the dialog
	XAP_Win32App * pWin32App = static_cast<XAP_Win32App *>(m_pApp);
	XAP_Win32Frame * pWin32Frame = static_cast<XAP_Win32Frame *>(pFrame);

	LPCTSTR lpTemplate = NULL;

	UT_ASSERT(m_id == AP_DIALOG_ID_SPELL);

	lpTemplate = MAKEINTRESOURCE(AP_RID_DIALOG_SPELL);

	int result = DialogBoxParam(pWin32App->getInstance(),lpTemplate,
								pWin32Frame->getTopLevelWindow(),
								(DLGPROC)s_dlgProc,(LPARAM)this);
	UT_ASSERT((result != -1));
}

BOOL CALLBACK AP_Win32Dialog_Spell::s_dlgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	// This is a static function.

	AP_Win32Dialog_Spell * pThis;
	
	switch (msg)
	{
	case WM_INITDIALOG:
		pThis = (AP_Win32Dialog_Spell *)lParam;
		SetWindowLong(hWnd,DWL_USER,lParam);
		return pThis->_onInitDialog(hWnd,wParam,lParam);
		
	case WM_COMMAND:
		pThis = (AP_Win32Dialog_Spell *)GetWindowLong(hWnd,DWL_USER);
		return pThis->_onCommand(hWnd,wParam,lParam);
		
	default:
		return 0;
	}
}

#define _DS(c,s)	SetDlgItemText(hWnd,AP_RID_DIALOG_##c,pSS->getValue(AP_STRING_ID_##s))
#define _DSX(c,s)	SetDlgItemText(hWnd,AP_RID_DIALOG_##c,pSS->getValue(XAP_STRING_ID_##s))

BOOL AP_Win32Dialog_Spell::_onInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	const XAP_StringSet * pSS = m_pApp->getStringSet();
	
	SetWindowText(hWnd, pSS->getValue(AP_STRING_ID_DLG_Spell_SpellTitle));

	// localize controls
	_DSX(SPELL_BTN_CANCEL,		DLG_Cancel);

	_DS(SPELL_TEXT_NOT,			DLG_Spell_UnknownWord);
	_DS(SPELL_TEXT_CHANGE,		DLG_Spell_ChangeTo);
	_DS(SPELL_TEXT_SUGGEST,		DLG_Spell_Suggestions);
	_DS(SPELL_BTN_IGNORE,		DLG_Spell_Ignore);
	_DS(SPELL_BTN_IGNOREALL,	DLG_Spell_IgnoreAll);
	_DS(SPELL_BTN_ADD,			DLG_Spell_AddToDict);
	_DS(SPELL_BTN_CHANGE,		DLG_Spell_Change);
	_DS(SPELL_BTN_CHANGEALL,	DLG_Spell_ChangeAll);

	// set initial state
//	CheckDlgButton(hWnd, AP_RID_DIALOG_SPELL_RADIO_PAGE + m_break, BST_CHECKED);
#if 0
	_DS(SPELL_RICH_SENTENCE,	DLG_Spell_);
	_DS(SPELL_EDIT_CHANGE,		DLG_Spell_);
	_DS(SPELL_LIST_SUGGEST,		DLG_Spell_);
#endif

	return 1;							// 1 == we did not call SetFocus()
}

BOOL AP_Win32Dialog_Spell::_onCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);
	WORD wId = LOWORD(wParam);
	HWND hWndCtrl = (HWND)lParam;

	switch (wId)
	{
	case IDCANCEL:						// also AP_RID_DIALOG_SPELL_BTN_CANCEL
		EndDialog(hWnd,0);
		return 1;

	default:							// we did not handle this notification
		UT_DEBUGMSG(("WM_Command for id %ld\n",wId));
		return 0;						// return zero to let windows take care of it.
	}
}

