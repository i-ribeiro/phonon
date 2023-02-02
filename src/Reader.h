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
* Purpose: This file is the main header for Reader (.h)
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
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG	0b0		 	/* (0000.0000)_2 = (000)_10 */
#define READER_FULL			0b10000000
#define READER_EMP			0b01000000
#define READER_REL			0b00100000
#define READER_END			0b00010000

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	phonon_intg mark;			/* the offset to the mark position (in chars) */
	phonon_intg read;			/* the offset to the get a char position (in chars) */
	phonon_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	phonon_char*	content;			/* pointer to the beginning of character array (character buffer) */
	phonon_intg		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	phonon_intg		increment;			/* character array increment factor */
	phonon_intg		mode;				/* operational mode indicator */
	phonon_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;			/* Offset / position field */
	phonon_intg		histogram[NCHAR];	/* Statistics of chars */
	phonon_intg		numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(phonon_intg, phonon_intg, phonon_intg);
ReaderPointer	readerAddChar		(ReaderPointer const, phonon_char);
phonon_boln		readerClear		    (ReaderPointer const);
phonon_boln		readerFree		    (ReaderPointer const);
phonon_boln		readerIsFull		(ReaderPointer const);
phonon_boln		readerIsEmpty		(ReaderPointer const);
phonon_boln		readerSetMark		(ReaderPointer const, phonon_intg);
phonon_intg		readerPrint		    (ReaderPointer const);
phonon_intg		readerLoad			(ReaderPointer const, FILE* const);
phonon_boln		readerRecover		(ReaderPointer const);
phonon_boln		readerRetract		(ReaderPointer const);
phonon_boln		readerRestore		(ReaderPointer const);
/* Getters */
phonon_char		readerGetChar		(ReaderPointer const);
phonon_char*	readerGetContent	(ReaderPointer const, phonon_intg);
phonon_intg		readerGetPosRead	(ReaderPointer const);
phonon_intg		readerGetPosWrte	(ReaderPointer const);
phonon_intg		readerGetPosMark	(ReaderPointer const);
phonon_intg		readerGetSize		(ReaderPointer const);
phonon_intg		readerGetInc		(ReaderPointer const);
phonon_intg		readerGetMode		(ReaderPointer const);
phonon_byte		readerGetFlags		(ReaderPointer const);
phonon_intg		readerShowStat		(ReaderPointer const);
phonon_intg		readerNumErrors		(ReaderPointer const);
/* Utility */
phonon_boln		charValid			(phonon_char const);

#endif
