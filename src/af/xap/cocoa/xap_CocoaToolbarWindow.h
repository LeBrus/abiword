/* AbiSource Program Utilities
 * Copyright (C) 2002 Hubert Figuiere
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
 
 
/* XAP_CocoaToolbarWindow */

#import <Cocoa/Cocoa.h>
#include "ut_vector.h"

class EV_CocoaToolbar;
@class XAP_CocoaFrameController;

@interface XAP_CocoaToolbarWindow : NSWindowController
{
	id			m_current;
	UT_Vector * m_toolbarVector;
	BOOL		m_lock;
}
+ (XAP_CocoaToolbarWindow *)sharedToolbar;
+ (XAP_CocoaToolbarWindow *)create;
- (id)initWithWindow:(NSWindow *)window;
- (void)dealloc;
- (void)removeAllToolbars;
- (void)redisplayToolbars:(XAP_CocoaFrameController*)frame;
- (void)autoResize;

/* lock and unlock redraw for batch toolbar changes, at initialization */
- (void)lock;
- (void)unlock;

- (void)_showAllToolbars:(XAP_CocoaFrameController*)frame;

- (void)showToolbarNotification:(NSNotification*)notif;
- (void)hideToolbarNotification:(NSNotification*)notif;
@end
