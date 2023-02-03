echo off
cls

echo: & echo: & echo: & echo:
echo ********** Running test: Empty file ********** & echo:
PhononCompiler.exe R test-inputs/reader/test_empty.txt
echo: & pause

echo: & echo: & echo: & echo:
echo ********** Running test: Hello World ********** & echo:
PhononCompiler.exe R test-inputs/reader/test_hello-world.txt
echo: & pause

echo: & echo: & echo: & echo:
echo ********** Runnning test: One character ********** & echo:
PhononCompiler.exe R test-inputs/reader/test_one.txt
echo: & pause

echo: & echo: & echo: & echo:
echo ********** Runnning test: Six characters ********** & echo:
PhononCompiler.exe R test-inputs/reader/test_six.txt
echo: & pause

echo: & echo: & echo: & echo:
echo ********** Runnning test: Large file (FIXED MODE) ********** & echo:
PhononCompiler.exe R test-inputs/reader/test_large.txt
echo: & pause

echo: & echo: & echo: & echo:
echo ********** Runnning test: Large file (ADDITIVE MODE) ********** & echo:
PhononCompiler.exe R test-inputs/reader/test_large.txt A 1 10
echo: & pause

echo: & echo: & echo: & echo:
echo ********** Runnning test: Large file (MULTIPLY MODE) ********** & echo:
PhononCompiler.exe R test-inputs/reader/test_large.txt M 1 2
echo: & pause

echo: & echo: & echo: & echo:
echo ********** Runnning test: Invalid characters ********** & echo:
PhononCompiler.exe R test-inputs/reader/test_invalid.txt