/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Isaac Ribeiro, Hilary Johnson
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /        ==============================        /         @@
@         ////     @@@@@ @@    @@@@@ @@@@@ @@@@@ @@@@@    ////        @
@         ////*    @@ @@ @@    @@ @@ @@ @@ @@ @@ @@ @@   /////        @
@     ((( ////)))) @@@@@ @@@@@ @@ @@ @@ @@ @@ @@ @@ @@///////( ///    @
@     ((((, / )))))@@    @@ @@ @@@@@ @@ @@ @@@@@ @@ @@///// ,/////    @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Reader (.c)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(phonon_intg size, phonon_intg increment, phonon_intg mode) {
	ReaderPointer readerPointer;

	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the values according to parameters */
	if(size <= 0 ){
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;
	}
	if(increment <= 0){
		mode = MODE_FIXED;
	}
	
	if( (mode != MODE_FIXED) && (mode != MODE_ADDIT) && (mode != MODE_MULTI) ){
		return NULL;
	}
		
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	//ASK PROFESSOR
	

	readerPointer->content = (phonon_char*)malloc(size);

	// check allocation
	if (!readerPointer->content)
		return NULL;
	
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;

	// initialize position, histogram, flags, errors
	readerClear(readerPointer);
	
	//readerPointer->flags |= READER_DEFAULT_FLAG
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, phonon_char ch) {
	phonon_char* tempReader = NULL;
	phonon_intg newSize = 0;

	// guard against null reader pointer
	if (!readerPointer) return NULL;

	// char must be in 0..127 range
	if ( !charValid(ch) ) {

		readerPointer->numReaderErrors++;
		return NULL;
	}

	// set Rel flag since relocation is possible
	readerPointer->flags &= ~READER_REL;

	if (readerPointer->position.wrte * (phonon_intg)sizeof(phonon_char) < readerPointer->size) {
		// This buffer is NOT full
		readerPointer->flags &= ~READER_FULL;
	} else {

		/* Reader is full, set flag */
		readerPointer->flags |= READER_FULL;

		switch (readerPointer->mode) {
		case MODE_FIXED:
			/* Do not try to reallocate if mode is FIXED */
			return NULL;
		case MODE_ADDIT:
			/* Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			break;
		case MODE_MULTI:
			/* Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			break;
		default:
			return NULL;
		}

		// no inclusion can be done if newSize is negative or exceeds max reader size
		if (newSize <= 0 || newSize >= READER_MAX_SIZE)
			return NULL;

		/* New reader allocation */
		tempReader = (phonon_char*) realloc(readerPointer->content, newSize);

		/* Check Reallocation */
		if (!tempReader)
			return NULL;

		/* Set reallocation flag if content pointer has changed */
		if (tempReader != readerPointer->content)
			readerPointer->flags |= READER_REL;

		/* Reallocation successful; commit new ptr and size */
		readerPointer->content = tempReader;
		readerPointer->size = newSize;

		// unset Full flag
		readerPointer->flags &= ~READER_FULL;
	}

	/* Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;

	/* Update histogram */
	readerPointer->histogram[ch]++;

	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return PHONON_FALSE;
	/* TO_DO: Adjust flags original */
	readerPointer->flags = READER_EMP;
	readerPointer->position.mark= 0;
	readerPointer->position.read= 0;
	readerPointer->position.wrte= 0;

	for  (int i=0; i< NCHAR; i++){
		readerPointer->histogram[i] = 0;
	}
	readerPointer->numReaderErrors=0;

	readerPointer->content[0] = '\0';

	return PHONON_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_boln readerFree(ReaderPointer const readerPointer) {

	// cannot free if readerPointer is null
	if (!readerPointer)
		return PHONON_FALSE;

	/* Free pointers */

	if (readerPointer->content)
		free(readerPointer->content);

	free(readerPointer);

	return PHONON_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return PHONON_FALSE;

	/* TO_DO: Check flag if buffer is FUL */

	if ((phonon_boln) (readerPointer->flags & READER_FULL))
		return PHONON_TRUE;

	return PHONON_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
phonon_boln readerIsEmpty(ReaderPointer const readerPointer) {

	// default to reader empty if readerPointer is null
	if (!readerPointer)
		return PHONON_TRUE;

	// return true if Full flag is not set
	if ((phonon_boln)(READER_FULL & readerPointer->flags))
		return PHONON_TRUE;

	return PHONON_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_boln readerSetMark(ReaderPointer const readerPointer, phonon_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark<0 || mark >= readerPointer->position.wrte)
		return PHONON_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return PHONON_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
*************************************************************
*/
phonon_intg readerPrint(ReaderPointer const readerPointer) {
	phonon_intg cont = 0;
	phonon_char c;

	// guard against nullptr to reader
	if (!readerPointer)
		return PHONON_FALSE;

	/* iterate buffer */
	while (cont < readerPointer->position.wrte) {

		// end loop if EOB reached
		if (READER_END & readerPointer->flags)
			break;

		// end loop if invalid char encountered
		if ( charValid(c = readerGetChar(readerPointer)) )
			break;

		printf("%c", c);
		cont++;
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	phonon_intg size = 0;
	phonon_char c;
	/* TO_DO: Defensive programming */

	if (!(readerPointer) || !fileDescriptor || feof(fileDescriptor))
		return PHONON_FALSE;
	
	c = (phonon_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
	
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_boln readerRecover(ReaderPointer const readerPointer) {

	// guard against nullptr
	if (!readerPointer)
		return PHONON_FALSE;

	/* Recover positions */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;

	return PHONON_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer){
		return PHONON_FALSE;
	}
	if(readerPointer->position.read <= 0 ){
		return PHONON_FALSE;
	}
	readerPointer->position.read -= 1;
	
	/* TO_DO: Retract (return 1 pos read) */
	return PHONON_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
phonon_boln readerRestore(ReaderPointer const readerPointer) {
	
	// guard against nullptr
	if (!readerPointer)
		return PHONON_FALSE;

	phonon_intg const mark = readerPointer->position.mark;

	// guard against mark out of bounds
	if (mark < 0 || mark >= readerPointer->size)
		return PHONON_FALSE;

	/* Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;

	return PHONON_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
*************************************************************
*/
phonon_char readerGetChar(ReaderPointer const readerPointer) {

	// guard against...
	if (!readerPointer							// ...nullptr
		|| !readerPointer->content				// ...^
		|| readerPointer->position.read < 0		// ...below lower bound
		|| readerPointer->position.read)		// ...above upper bound
		return (phonon_char) READER_ERROR;

	// set EOB flag and return terminator if read meets or exceeds write
	if (readerPointer->position.read >= readerPointer->position.wrte) {

		readerPointer->flags |= READER_END;
		return READER_TERMINATOR;
	}

	// reset EOB flag
	readerPointer->flags &= ~READER_END;

	// return char and increment read position
	return readerPointer->content[ readerPointer->position.read++ ];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
*************************************************************
*/
phonon_char* readerGetContent(ReaderPointer const readerPointer, phonon_intg pos) {

	// guard against...
	if (!readerPointer							// ...nullptr
		|| !readerPointer->content				// ...^
		|| pos < 0								// pos below lower bound
		|| pos >= readerPointer->position.wrte)	// pos above upper bound
		return NULL;

	// return content offset by pos
	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return wrte */
	if (!readerPointer)
		return READER_ERROR;

	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mark */
	if (!readerPointer)
		return READER_ERROR;

	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return size */
	if (!readerPointer)
		return READER_ERROR;

	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return increment */
	if (!readerPointer)
		return READER_ERROR;

	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	if (!readerPointer)
		return READER_ERROR;

	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return flags */
	if (!readerPointer)
		return READER_ERROR;

	return readerPointer->flags;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerShowStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
	return 0;
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
phonon_intg readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
	return 0;
}

/*
***********************************************************
* Function name: charValid
* Purpose:	Returns PHONON_TRUE if a given char is valid and
			PHONON_FALSE if invalid.
* Parameters:
*	ch = char to test
* Return value:
*	Whether or not the char is valid (T/F)
***********************************************************
*/
phonon_boln charValid(phonon_char const ch) {

	return (phonon_boln)(ch >= 0 && ch < NCHAR);
}
