/*
  This File is copied from
  
  http://www.oreilly.com/catalog/masteralgoc/index.html
  Mastering Algorithms with C
  By Kyle Loudon
  ISBN: 1-56592-453-3
  Publishd by O'Reilly
  
  Updated O'Reilly's copyright notice follows :

  Copyright (c) 1999 O'Reilly & Associates, Inc.

  Mastering Algorithms with C
  Kyle Loudon

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE OR THE USE, OR ANY OTHER
  DEALINGS IN THE SOFTWARE.

 */

/*****************************************************************************
 *                                                                            *
 *  -------------------------------- list.c --------------------------------  *
 *                                                                            *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <common/config.h>
#include <common/list.h>

/*****************************************************************************
*                                                                            *
*  ------------------------------- list_init ------------------------------  *
*                                                                            *
*****************************************************************************/

void list_init(List *list, void (*destroy)(void *data)) {

	/*********************************************************************
	 *                                                                    *
	 *  Initialize the list.                                              *
	 *                                                                    *
	 *********************************************************************/

	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	return;
} /* end list_init() */

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- list_destroy -----------------------------  *
 *                                                                            *
 *****************************************************************************/

void list_destroy(List *list) {

	void               *data;
	int rc; 

	/*********************************************************************
	 *                                                                    *
	 *  Remove each element.                                              *
	 *                                                                    *
	 *********************************************************************/

	while (list_size(list) > 0) {
    
		rc = list_rem_next(list, NULL, (void **)&data);
    
		if (( rc == 0) && (list->destroy != NULL)) { 

			/*******************************************************************
			 *                                                                  *
			 *  Call a user-defined function to free dynamically allocated data.*
			 *                                                                  *
			 *******************************************************************/

			list->destroy(data);
		}/* end if() */
	}/* end while() */

	/**************************************************************************
	 *                                                                         *
	 *  No operations are allowed now, but clear the structure as a precaution.*
	 *                                                                         *
	 **************************************************************************/

	memset(list, 0, sizeof(List));
	return;
} /* void list_destroy(List *list) */

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- list_ins_next ----------------------------  *
 *                                                                            *
 *****************************************************************************/

int list_ins_next(List *list, ListElmt *element, const void *data) {

	ListElmt           *new_element;

	/*********************************************************************
	 *                                                                    *
	 *  Allocate storage for the element.                                 *
	 *                                                                    *
	 *********************************************************************/

	if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
		return -1;

	/*********************************************************************
	 *                                                                    *
	 *  Insert the element into the list.                                 *
	 *                                                                    *
	 *********************************************************************/

	new_element->data = (void *)data;

	if (element == NULL) {

		/*************************************************************
		 *                                                            *
		 *  Handle insertion at the head of the list.                 *
		 *                                                            *
		 *************************************************************/

		if (list_size(list) == 0)
			list->tail = new_element;

		new_element->next = list->head;
		list->head = new_element;
	}/* end if (element == NULL) */
	else {

		/*************************************************************
		 *                                                            *
		 *  Handle insertion somewhere other than at the head.        *
		 *                                                            *
		 *************************************************************/

		if (element->next == NULL)
			list->tail = new_element;

		new_element->next = element->next;
		element->next = new_element;
	}/* end else */

	/*********************************************************************
	 *                                                                    *
	 *  Adjust the size of the list to account for the inserted element.  *
	 *                                                                    *
	 *********************************************************************/

	list->size++;
	return 0;
} /* end list_ins_next() */

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- list_rem_next ----------------------------  *
 *                                                                            *
 *****************************************************************************/

int list_rem_next(List *list, ListElmt *element, void **data) {

	ListElmt           *old_element;

	/*********************************************************************
	 *                                                                    *
	 *  Do not allow removal from an empty list.                          *
	 *                                                                    *
	 *********************************************************************/

	if (list_size(list) == 0)
		return -1;

	/*********************************************************************
	 *                                                                    *
	 *  Remove the element from the list.                                 *
	 *                                                                    *
	 *********************************************************************/

	if (element == NULL) {

		/*************************************************************
		 *                                                            *
		 *  Handle removal from the head of the list.                 *
		 *                                                            *
		 *************************************************************/

		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1)
			list->tail = NULL;
	}/* end if (element == NULL) */
	else {

		/*************************************************************
		 *                                                            *
		 *  Handle removal from somewhere other than the head.        *
		 *                                                            *
		 *************************************************************/

		if (element->next == NULL)
			return -1;

		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if (element->next == NULL)
			list->tail = element;
	}/* end else */

	/*********************************************************************
	 *                                                                    *
	 *  Free the storage allocated by the abstract data type.             *
	 *                                                                    *
	 *********************************************************************/

	free(old_element);

	/*********************************************************************
	 *                                                                    *
	 *  Adjust the size of the list to account for the removed element.   *
	 *                                                                    *
	 *********************************************************************/

	list->size--;
	return 0;
}

/*
 * Local variables:
 *  c-indent-level: 8
 *  c-basic-offset: 8
 * End:
 */