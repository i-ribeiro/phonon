:: COMPILERS COURSE - SCRIPT ---------------------------------------------
:: SCRIPT A22 - CST8152 - Winter 2023


cls
SET COMPILER=src\out\build\x64-Debug\PhononCompiler.exe

SET FILE1=test_empty
SET FILE2=test_err
SET FILE3=test_general
SET FILE4=test_large
SET FILE5=main
SET FILE6=Test
SET FILE7=test_invalid_tokens

SET TESTPATH=test-inputs\scanner
SET ASSIGNMENT=32
SET EXTENSION=ph
SET OUTPUT=out
SET ERROR=err
SET OUTDIR=out

SET PARAM=P

:: ---------------------------------------------------------------------
:: Begin of Tests (A22 - W22) ------------------------------------------
:: ---------------------------------------------------------------------
@echo on
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "@@@@                                                               @@@@"
ECHO "@@          /        ==============================        /         @@"
ECHO "@         ////     @@@@@ @@    @@@@@ @@@@@ @@@@@ @@@@@    ////        @"
ECHO "@         ////*    @@ @@ @@    @@ @@ @@ @@ @@ @@ @@ @@   /////        @"
ECHO "@     ((( ////)))) @@@@@ @@@@@ @@ @@ @@ @@ @@ @@ @@ @@///////( ///    @"
ECHO "@     ((((, / )))))@@    @@ @@ @@@@@ @@ @@ @@@@@ @@ @@///// ,/////    @"
ECHO "@     (((((/)))((    ------------------------------    ((((./////*    @"
ECHO "@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @"
ECHO "@    ///// / /////   ==============================  * ////* / ////   @"
ECHO "@     ///// ///// ((                               (( ///// /////     @"
ECHO "@    ((((   / , (((((                             (((((  //   /(((    @"
ECHO "@    (((((((/ . (((((                          (((((* / (((((((       @"
ECHO "@      (((((( //((((/((((                    *((((/((((/( (((((/      @"
ECHO "@       .//,   * /   (((((                   (((((  ///    .//.       @"
ECHO "@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @"
ECHO "@         //////// ,// ((( /////,     ////// ((( //  /////// *        @"
ECHO "@            (((((((((,// * /////     /////   (//(((((((((            @"
ECHO "@            ((((((((((((/////         //.///  (((((((((((.           @"
ECHO "@                   (///////// //(   (//.//////////                   @"
ECHO "@                  (/////////             //////////                  @"
ECHO "@                                                                     @"
ECHO "@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@"
ECHO "@@@@                                                               @@@@"
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "                                                                       "
ECHO "[PARSER SCRIPT .......................................................]"
ECHO "                                                                       "

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A22 - W22) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %TESTPATH%\%FILE1%.%EXTENSION%	> %OUTDIR%\%FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %OUTDIR%\%FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %TESTPATH%\%FILE2%.%EXTENSION%	> %OUTDIR%\%FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %OUTDIR%\%FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %TESTPATH%\%FILE3%.%EXTENSION%	> %OUTDIR%\%FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %OUTDIR%\%FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %TESTPATH%\%FILE4%.%EXTENSION%	> %OUTDIR%\%FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %OUTDIR%\%FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %TESTPATH%\%FILE5%.%EXTENSION%	> %OUTDIR%\%FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %OUTDIR%\%FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %TESTPATH%\%FILE6%.%EXTENSION%	> %OUTDIR%\%FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %OUTDIR%\%FILE6%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
CD %OUTDIR%
DIR *.OUT
DIR *.ERR
CD ..

:: ---------------------------------------------------------------------
:: End of Tests (A22 - W23) --------------------------------------------
:: ---------------------------------------------------------------------
