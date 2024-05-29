# Compiler and Interpreter

A small compiler that builds an abstract syntax tree (AST) and executes it using an interpreter.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)

## Introduction

This project is a simple compiler and interpreter that processes a custom programming language. It builds an abstract syntax tree (AST) from the input source code and then interprets the AST to execute the program.

## Features

- **Lexical Analysis**: Tokenizes the source code.
- **Syntax Analysis**: Parses tokens into an AST.
- **Semantic Analysis**: Checks for semantic errors.
- **Code Generation**: Emits intermediate code.
- **Interpreter**: Executes the intermediate code.

## Installation

To build and run the project, ensure you have a C++ compiler and make installed. Clone the repository and use the provided Makefile:

```sh
git clone https://github.com/loiclgrx/compiler-and-interpreter.git
cd compiler-and-interpreter
make
```

## Usage

After building the project, you can run the compiler with:

```sh
./compiler <source_file>
```

Replace <source_file> with the path to your source code file.

## File Structure
- bookparser.cpp: Contains the main logic for parsing.
- emitter.cpp: Handles code emission.
- error.cpp: Manages error reporting.
- global.hpp: Defines global variables and constants.
- init.cpp: Initialization routines.
- language.l: Flex file for lexical analysis.
- language.ypp: Bison file for syntax analysis.
- lexer.cpp: Lexical analyzer.
- main.cpp: Entry point of the application.
- parser.cpp: Parser implementation.
- symbol.cpp: Symbol table management.
