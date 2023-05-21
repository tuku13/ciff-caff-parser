# CIFF and CAFF parser

The program parses [CIFF](./docs/CIFF.txt) and [CAFF](./docs/CAFF.txt) files, then converts them
into [WebP](https://developers.google.com/speed/webp) format.

![Banner image created by converting 1.caff](./banner-image.webp)

# Compile

You can compile the program easily with the included Makefile.

> You need to install `g++` and `make` if you don't have them installed.

Compile: 
`make`

# Usage

Parsing a CAFF file
`./parser -caff file-name.caff`

Parsing a CIFF file
`./parser -ciff file-name.ciff`

# Tests

The `test-files` directory contains some invalid inputs. The files in it must start with `valid-` or `invalid-` prefix.
The script assumes the files with prefix `valid-` are valid and return 0.
It also assumes the files with prefix `invalid-` are invalid and return 255 which is -1.

## Running tests

The test runner script `test.sh` calls the program with inputs from the `test-files` folder.

Running the test:
`./test.sh`

## Regenerating tests

If you want, to regenerate the default caff test files, you should run the test-file generator by this
command: `java -jar create-test-caff-files.jar`

> To run the test creator program, you need to have [Java JDK](https://www.java.com/en/) installed on your system.