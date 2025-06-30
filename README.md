# 🧮 Mini Calculator - University Project

A simple, terminal-based arithmetic expression evaluator built in C++ that supports addition, subtraction, multiplication, and division. Designed to showcase core concepts of **lexical analysis**, **parsing**, and **expression evaluation** using object-oriented programming.

---

## 📌 Features

- ✅ Handles integer arithmetic expressions (e.g., `3 + 5 * 2 - 8 / 4`)
- ✅ Implements operator precedence (e.g., `*` and `/` before `+` and `-`)
- ✅ Clear, colorful CLI interface with ASCII art
- ✅ Graceful error handling for:
  - Division by zero
  - Unexpected tokens or syntax
  - Empty input

---

## 🗂️ Code Structure

| Component      | Description |
|----------------|-------------|
| `TokenType`    | Enum for token types like `NUMBER`, `PLUS`, etc. |
| `Token`        | Structure holding a token and optional value |
| `Lexer`        | Converts raw input string into a sequence of tokens |
| `Interpreter`  | Evaluates the expression using recursive descent parsing |
| `main()`       | Manages user interface, input, and output |

---

## 💻 Sample Output

```bash
***********************************************
            Welcome to the Mini Calculator     
             For University Project           
***********************************************
    A simple calculator that supports         
    addition, subtraction, multiplication,    
    and division operations.                  
***********************************************

Enter an arithmetic expression (e.g., 3 + 5 * 2):
-----------------------------------------------
2 + 5 * 3 - 4

Result = 13
