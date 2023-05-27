/* ============================================================================
 *  LQuickFind.c
 * ============================================================================

 *  Author:         (C) 2005 Andrea Ribichini
 *  License:        See the end of this file for license information
 *  Created:        September 2, 2005
 *  Module:         LL

 *  Last changed:   $Date: 2006/03/19 15:55:52 $  
 *  Changed by:     $Author: goldberg $
 *  Revision:       $Revision: 1.2 $
*/

#include "LQuickFind.h"
#include "LArray.h"
#include "LMemory.h"

/* PUBLIC METHODS */

/* ---------------------------------------------------------------------------------
*  LQuickFind_New
*  ---------------------------------------------------------------------------------
*  Constructor */

LQuickFind* LQuickFind_New () 
{
	LQuickFind theObject={0};
	
	theObject.mHashTable=LHash_New ();
    
	return LMemory_NewObject (LQuickFind, theObject);
}

/* ---------------------------------------------------------------------------------
*  LQuickFind_Delete
*  ---------------------------------------------------------------------------------
*  Destructor */

void LQuickFind_Delete (LQuickFind** ThisA)
{
	LArray* theItems;
	ui4 theNumItems;
	ui4 i;
	LArray** theTreePtr;	
	LHash* theTmpHashTable;
	
	/*creates tmp hash table...*/
	theTmpHashTable=LHash_New ();

	/*retrieves pointers to all trees (larrays)...*/
	theItems=LHash_GetAllItems ((*ThisA)->mHashTable);
	
	/*deletes all larrays...*/
	theNumItems=LArray_GetItemsCount (theItems);
	for (i=0; i<theNumItems; i++)
	{
		/*retrieves pointer to tree...*/
		theTreePtr=(LArray **)LArray_ItemAt (theItems, i);
		/*if not in tmp hash table...*/
		if (!LHash_IsInTable (theTmpHashTable, (ui4)*theTreePtr))
		{
			/*insert in tmp hash table...*/
			LHash_InsertItem (theTmpHashTable, NULL, (ui4)*theTreePtr);
			/*delete tree...*/
			LArray_Delete (theTreePtr);
		}		
	}
	
	/*deletes tmp hash table...*/
	LHash_Delete (&theTmpHashTable);
	
	/*must be manually deleted...*/
	LArray_Delete (&theItems);
	
	/*deletes hash table...*/
	LHash_Delete (&((*ThisA)->mHashTable));
		
	/*deletes object...*/
	LMemory_DeleteObject (ThisA);
}

/* ---------------------------------------------------------------------------------
*  LQuickFind_MakeSet
*  ---------------------------------------------------------------------------------
*  MakeSet */
void LQuickFind_MakeSet (LQuickFind* This, ui4 inItem)
{
	LArray* theNewTree;
	
	/*parameter checking...*/
	if (inItem==LQuickFind_BAD_ITEM)
		return;
	
	/*if set already exists...*/
	if (LQuickFind_Find (This, inItem)!=LQuickFind_BAD_ITEM)
		return; /*does nothing!*/
	
	/*creates new 1-level tree...size of each leaf is 4 bytes...*/
	theNewTree=LArray_New (4);
	
	/*inserts first item in new tree (this also identifies the tree)...*/
	LArray_AppendItem (theNewTree, &inItem);
	
	/*inserts pointer to tree (LArray) into hash table (key = node id)*/
	LHash_InsertItem (This->mHashTable, (void *)theNewTree, inItem);
}

/* ---------------------------------------------------------------------------------
*  LQuickFind_Find
*  ---------------------------------------------------------------------------------
*  Find */
ui4 LQuickFind_Find (LQuickFind* This, ui4 inItem)
{
	LArray *thelarray;
	
	/*parameter checking...*/
	if (inItem==LQuickFind_BAD_ITEM)
		return LQuickFind_BAD_ITEM;
	
	/*if not found...*/
	if (!LHash_IsInTable (This->mHashTable, inItem))
		return LQuickFind_BAD_ITEM; /*not a valid node id...*/
	
	/*retrieves tree (LArray) from node id...*/
	thelarray=(LArray *)LHash_GetItemByKey (This->mHashTable, inItem);
		
	/*returns node id...*/
	return *((ui4 *)LArray_ItemAt (thelarray, 0));
}

/* ---------------------------------------------------------------------------------
*  LQuickFind_Union
*  ---------------------------------------------------------------------------------
*  Union */
ui4 LQuickFind_Union (LQuickFind* This, ui4 inItem1, ui4 inItem2)
{
	ui4 thelength1, thelength2;
	LArray *thelarray1, *thelarray2;
	ui4 i;
	ui4 *thecur_item;
	ui4 theset1, theset2;
	
	/*parameter checking...*/
	if ((inItem1==LQuickFind_BAD_ITEM) || (inItem2==LQuickFind_BAD_ITEM))
		return LQuickFind_BAD_ITEM;
	
	theset1=LQuickFind_Find (This, inItem1);
	theset2=LQuickFind_Find (This, inItem2);

	/*if either set doesn't exist...*/
	if ((theset1==LQuickFind_BAD_ITEM) || (theset2==LQuickFind_BAD_ITEM))
		return LQuickFind_BAD_ITEM; /*returns an invalid id...*/
		
	/*if already in same set...*/
	if (theset1==theset2)
		return theset1;
	
	/*retrieves 1st tree (LArray)...*/
	thelarray1=(LArray *)LHash_GetItemByKey (This->mHashTable, inItem1);
	
	/*retrieves 2nd tree (LArray)...*/
	thelarray2=(LArray *)LHash_GetItemByKey (This->mHashTable, inItem2);
	
	/*gets lengths...*/
	thelength1=LArray_GetItemsCount (thelarray1);
	thelength2=LArray_GetItemsCount (thelarray2);
	/*performs (balanced) union...*/
	if (thelength1 >= thelength2)
	{
		for (i=0; i<thelength2; i++)
		{
			thecur_item=LArray_ItemAt (thelarray2, i);
			LArray_AppendItem (thelarray1, thecur_item);
			/*replaces item in hash table...*/
			LHash_InsertItem (This->mHashTable, (void *)thelarray1, *thecur_item);
		}	
		LArray_Delete (&thelarray2);
	}
	else
	{
		/*renames tree as well...*/
		thecur_item=LArray_ItemAt (thelarray1, 0);
		LArray_InsertItemAt (thelarray2, thecur_item, 0);
		/*replaces item in hash table...*/
		LHash_InsertItem (This->mHashTable, (void *)thelarray2, *thecur_item);
		for (i=1; i<thelength1; i++)
		{
			thecur_item=LArray_ItemAt (thelarray1, i);
			LArray_AppendItem (thelarray2, thecur_item);
			/*replaces item in hash table...*/
			LHash_InsertItem (This->mHashTable, (void *)thelarray2, *thecur_item);
		}
		LArray_Delete (&thelarray1);
	}

	/*returns appropriate set name...*/
	if (thelength1 >= thelength2)
		return theset1;
	else
		return theset2;
}

/* ---------------------------------------------------------------------------------
*  LQuickFind_GetUsedMem
*  ---------------------------------------------------------------------------------
*  GetUsedMem */
ui4 LQuickFind_GetUsedMem (LQuickFind* This)
{
	ui4 theHashTableUsedMem=0;
	ui4 theQuickFindStructUsedMem=0;
	ui4 theLArraysUsedMem=0;
	
	LArray* theItems;
	ui4 theNumItems;
	LArray** theTreePtr;
	ui4 i;
	LHash* theTmpHashTable;
	
	/*creates tmp hash table...*/
	theTmpHashTable=LHash_New ();
	
	/*size of hash table...*/
	theHashTableUsedMem=LHash_GetUsedMem (This->mHashTable);
	
	/*size of struct LQuickFind...*/
	theQuickFindStructUsedMem=sizeof (struct LQuickFind);
	
	/*size of all larrays...*/
	theItems=LHash_GetAllItems (This->mHashTable);
	theNumItems=LArray_GetItemsCount (theItems);
	for (i=0; i<theNumItems; i++)
	{	
		/*retrieves pointer to tree...*/
		theTreePtr=(LArray **)LArray_ItemAt (theItems, i);
		/*if not in tmp hash table...*/
		if (!LHash_IsInTable (theTmpHashTable, (ui4)*theTreePtr))
		{
			/*insert in tmp hash table...*/
			LHash_InsertItem (theTmpHashTable, NULL, (ui4)*theTreePtr);
			/*take size into account...*/
			theLArraysUsedMem=theLArraysUsedMem + LArray_GetUsedMem(*theTreePtr);
		}	
	}
	
	/*deletes tmp hash table...*/
	LHash_Delete (&theTmpHashTable);
	
	/*must be manually deleted...*/
	LArray_Delete (&theItems);
		
	return (theHashTableUsedMem + theQuickFindStructUsedMem + theLArraysUsedMem);
}

/* ---------------------------------------------------------------------------------
*  LQuickFind_GetAllItems
*  ---------------------------------------------------------------------------------
*  GetAllItems */
LArray* LQuickFind_GetAllItems (LQuickFind* This)
{
	/*items in LQuickFind are keys in LHash...*/
	return LHash_GetAllKeys (This->mHashTable);
}


/* Copyright (C) 2005 Andrea Ribichini

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
