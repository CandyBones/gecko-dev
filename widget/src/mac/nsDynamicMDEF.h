/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
 
// MDEF for doing dynamic menu construction

#ifndef nsDynamicMDEF_h__
#define nsDynamicMDEF_h__

#include "nsSupportsArray.h"
#include "nsIMenu.h"

#include <Menus.h>

pascal void nsDynamicMDEFMain(
  short message,
  MenuHandle theMenu, 
  Rect * menuRect, 
  Point hitPt, 
  short * whichItem);

void nsPreviousMenuStackUnwind(
  nsIMenu * aMenuJustBuilt, 
  MenuHandle aMenuHandleJustBuilt);
  

// helper class useful for counting instances
class nsInstanceCounter
{
public:
        nsInstanceCounter(const char* inDesc)
        : mInstanceCount(0)
        , mDescription(inDesc)
        {
        }
        
        ~nsInstanceCounter()
        {
          printf("%s %ld\n", mDescription, mInstanceCount);
        }

        nsInstanceCounter& operator ++()          // prefix
        {
          ++ mInstanceCount;
          return *this;                
        }

        nsInstanceCounter& operator -- ()        // prefix
        {
          -- mInstanceCount;
          return *this;
        }

protected:

  PRInt32     mInstanceCount;
  const char* mDescription;

};


//------------------------------------------------------------------------------

class nsMenuStack
{
public:
                nsMenuStack();
                ~nsMenuStack();


  PRInt32       Count()
                {
                  PRUint32  num;
                  mMenuArray.Count(&num);
                  return (PRInt32)num;
                }
                
                // returns addreffed nsIMenu
  nsresult      GetMenuAt(PRInt32 aIndex, nsIMenu **outMenu);
  PRBool        HaveMenuAt(PRInt32 aIndex);
  PRBool        RemoveMenuAt(PRInt32 aIndex);                       // no release
  PRBool        InsertMenuAt(nsIMenu* aElement, PRInt32 aIndex);    // no addrefs; weak ref.
  
protected:

  nsSupportsArray   mMenuArray;     // array of weak refs to nsIMenus

};



#endif nsDynamicMDEF_h__
