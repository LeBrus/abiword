/* AbiSource Program Utilities
 * Copyright (C) 1998 AbiSource, Inc.
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

#ifndef EV_UNIXMENU_H
#define EV_UNIXMENU_H

#include "ut_types.h"
#include "ut_vector.h"
#include "xap_Types.h"
#include "ev_Menu.h"

class AV_View;
class AP_UnixApp;
class XAP_UnixFrame;


/*****************************************************************/

class EV_UnixMenu : public EV_Menu
{
public:
	EV_UnixMenu(AP_UnixApp * pUnixApp,
				XAP_UnixFrame * pUnixFrame,
				const char * szMenuLayoutName,
				const char * szMenuLabelSetName);
	virtual ~EV_UnixMenu(void);

	UT_Bool				synthesizeMenu(GtkWidget * wMenuRoot);
	UT_Bool				menuEvent(AP_Menu_Id id);
	virtual UT_Bool		refreshMenu(AV_View * pView) = 0;

	XAP_UnixFrame * 	getFrame(void);

protected:

	UT_Bool				_refreshMenu(AV_View * pView, GtkWidget * wMenuRoot);
	UT_Bool				_isItemPresent(AP_Menu_Id id) const;

	AP_UnixApp *		m_pUnixApp;
	XAP_UnixFrame *		m_pUnixFrame;

	// Menu accelerator group, dynamically filled on synth()
	GtkAccelGroup * 	m_accelGroup;
	
	// actual GTK menu widgets
	UT_Vector			m_vecMenuWidgets;
};

/*****************************************************************/

class EV_UnixMenuBar : public EV_UnixMenu
{
public:
	EV_UnixMenuBar(AP_UnixApp * pUnixApp,
				   XAP_UnixFrame * pUnixFrame,
				   const char * szMenuLayoutName,
				   const char * szMenuLabelSetName);
	virtual ~EV_UnixMenuBar(void);

	UT_Bool				synthesizeMenuBar(void);
	virtual UT_Bool		refreshMenu(AV_View * pView);

protected:
	GtkWidget *			m_wMenuBar;
	GtkWidget * 		m_wHandleBox;
};

/*****************************************************************/

class EV_UnixMenuPopup : public EV_UnixMenu
{
public:
	EV_UnixMenuPopup(AP_UnixApp * pUnixApp,
					 XAP_UnixFrame * pUnixFrame,
					 const char * szMenuLayoutName,
					 const char * szMenuLabelSetName);
	virtual ~EV_UnixMenuPopup(void);

	UT_Bool				synthesizeMenuPopup(void);
	virtual UT_Bool		refreshMenu(AV_View * pView);
	virtual GtkWidget *	getMenuHandle(void) const;

protected:
	GtkWidget *			m_wMenuPopup;
};

#endif /* EV_UNIXMENU_H */
