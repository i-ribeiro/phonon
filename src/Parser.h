/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Hilary Johnson, Isaac Ribeiro
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
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern phonon_intg line;
extern Token tokenizer();
extern phonon_char* keywordTable[];
phonon_intg syntaxErrorNumber = 0;

#define STR_LANGNAME	"phonon"
#define LANG_WRTE		"print$"
#define LANG_MAIN		"main$"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_while,
	KW_if,
	KW_else,
	KW_return,
	KW_void,
	KW_out,
	KW_in,
	KW_real,
	KW_int,
	KW_bool
};

/* Function definitions */
phonon_void startParser();
phonon_void matchToken(phonon_intg, phonon_intg);
phonon_void syncErrorHandler(phonon_intg);
phonon_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
phonon_void codeSession();
phonon_void dataSession();
phonon_void optVarListDeclarations();
phonon_void optionalStatements();
phonon_void outputStatement();
phonon_void outputVariableList();
phonon_void program();
phonon_void statement();
phonon_void statements();
phonon_void statementsPrime();

#endif
