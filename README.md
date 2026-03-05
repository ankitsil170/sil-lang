# sil-lang

A tiny interpreted programming language built from scratch in **C++17**.

sil-lang reads `.sil` source files and executes them through a classic interpreter pipeline:

Lexer → Parser → AST → Interpreter

The project demonstrates how programming languages actually work internally — from tokenizing raw text to executing an Abstract Syntax Tree.

This repository is a minimal but complete implementation of a scripting language written entirely in modern C++ with **no external dependencies**.

---

## Example

hello.sil

print("Hello from sil!")

Output:

Hello from sil!

---

## Features

• Custom programming language syntax  
• Hand written lexer  
• Recursive descent parser  
• Abstract Syntax Tree (AST) execution  
• Variable system  
• Arithmetic expressions  
• Conditional statements  
• String and number support  

Everything runs inside a lightweight interpreter written in pure C++.

---

## Language Overview

### Printing


print("Hello World")
print(42)


### Variables


a = 5
b = 10

print(a + b)


### Arithmetic


x = 20
y = 4

print(x + y)
print(x - y)
print(x * y)
print(x / y)


### Conditions


a = 10
b = 3

if a > b {
print("a is bigger")
}


Supported comparison operators:


< >= <= == !=


### Strings


name = "Ankit"
print(name)


### Comments

this is a comment

a = 5 # inline comment


---

## How sil-lang Works

sil-lang follows the classic interpreter architecture used in many real programming languages.


Source Code (.sil)
 -> 
Lexer
(Tokenization)
 -> 
Parser
(AST Construction)
 -> 
Interpreter
(Code Execution)


### 1. Lexer

The lexer reads raw characters and converts them into tokens.

Example:


print("Hello")


becomes


PRINT ( STRING:"Hello" )


---

### 2. Parser

The parser converts the token stream into an **Abstract Syntax Tree (AST)**.

Example AST:


PrintStatement
└── StringLiteral("Hello")


---

### 3. Interpreter

The interpreter walks the AST and executes each node.

Variables are stored in a runtime environment (a key-value map).

Expressions are evaluated recursively.

---

## Runtime Value System

sil-lang uses:


std::variant<double, std::string>


to represent runtime values.

This allows the interpreter to store **numbers and strings dynamically**, similar to scripting languages.

---

## Example Program


name = "Ankit"
print(name)

x = 42
y = 8

print(x + y)

if x > y {
print("x is bigger")
}


Output:


Ankit
50
x is bigger


---

## Future Improvements

Possible features for the next version:

• else blocks  
• while loops  
• user defined functions  
• multi-scope environments  
• better error messages  
• string utilities  

---

## Why This Project Exists

sil-lang was built to explore how programming languages are implemented internally.

Instead of relying on existing frameworks or libraries, everything here is written manually to keep the architecture transparent and educational.

---

## Author

Ankit Sil

Clone the repository
