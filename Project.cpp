#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <stack>

using namespace std;

// Define token types
enum TokenType
{
    NUMBER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    END,
    INVALID
};

// Token structure
struct Token
{
    TokenType type;
    int value; // only used if type == NUMBER
};

// Lexer (Tokenizer) Class
class Lexer
{
    string text;
    int pos;
    char current_char;

public:
    Lexer(string input) : text(input), pos(0)
    {
        current_char = text[pos];
    }

    // Move to next character
    void advance()
    {
        pos++;
        if (pos < text.size())
            current_char = text[pos];
        else
            current_char = '\0'; // End of input
    }

    // Skip whitespace
    void skip_whitespace()
    {
        while (isspace(current_char))
        {
            advance();
        }
    }

    // Get a full number (multi-digit)
    int integer()
    {
        int result = 0;
        while (isdigit(current_char))
        {
            result = result * 10 + (current_char - '0');
            advance();
        }
        return result;
    }

    // Get next token
    Token get_next_token()
    {
        while (current_char != '\0')
        {
            if (isspace(current_char))
            {
                skip_whitespace();
                continue;
            }
            if (isdigit(current_char))
            {
                return Token{NUMBER, integer()};
            }
            if (current_char == '+')
            {
                advance();
                return Token{PLUS, 0};
            }
            if (current_char == '-')
            {
                advance();
                return Token{MINUS, 0};
            }
            if (current_char == '*')
            {
                advance();
                return Token{MUL, 0};
            }
            if (current_char == '/')
            {
                advance();
                return Token{DIV, 0};
            }

            return Token{INVALID, 0};
        }
        return Token{END, 0};
    }
};

// Parser and Evaluator Class
class Interpreter
{
    Lexer lexer;
    Token current_token;

public:
    Interpreter(Lexer lex) : lexer(lex)
    {
        current_token = lexer.get_next_token();
    }

    // Eat token and move to next
    void eat(TokenType type)
    {
        if (current_token.type == type)
        {
            current_token = lexer.get_next_token();
        }
        else
        {
            cerr << "\033[1;31mError: Unexpected token!\033[0m\n"; // Red text for errors
            exit(1);
        }
    }

    // Factor = NUMBER
    int factor()
    {
        Token token = current_token;
        eat(NUMBER);
        return token.value;
    }

    // Term = factor ((MUL | DIV) factor)*
    int term()
    {
        int result = factor();
        while (current_token.type == MUL || current_token.type == DIV)
        {
            if (current_token.type == MUL)
            {
                eat(MUL);
                result *= factor();
            }
            else if (current_token.type == DIV)
            {
                eat(DIV);
                int divisor = factor();
                if (divisor == 0)
                {
                    cerr << "\033[1;31mError: Division by zero!\033[0m\n";
                    exit(1);
                }
                result /= divisor;
            }
        }
        return result;
    }

    // Expression = term ((PLUS | MINUS) term)*
    int expr()
    {
        int result = term();
        while (current_token.type == PLUS || current_token.type == MINUS)
        {
            if (current_token.type == PLUS)
            {
                eat(PLUS);
                result += term();
            }
            else if (current_token.type == MINUS)
            {
                eat(MINUS);
                result -= term();
            }
        }
        return result;
    }
};

// Function to display a neat and beautiful welcome and interface
void display_interface()
{
    // Display a colorful, eye-catching header with a bit of ASCII art
    cout << "\033[1;34m";
    cout << "***********************************************\n";
    cout << "            Welcome to the Mini Calculator     \n";
    cout << "             For University Project           \n";
    cout << "***********************************************\n";
    cout << "    A simple calculator that supports         \n";
    cout << "    addition, subtraction, multiplication,    \n";
    cout << "    and division operations.                  \n";
    cout << "***********************************************\n";
    cout << "\033[0m";
    cout << "\nEnter an arithmetic expression (e.g., 3 + 5 * 2):\n";
    cout << "-----------------------------------------------\n";
}

// Function to handle the error gracefully with colors
void handle_error(const string &message)
{
    cerr << "\033[1;31m" << message << "\033[0m\n"; // Red text for errors
}

int main()
{
    string input;
    display_interface(); // Show intro with a clean, engaging interface

    // Get user input
    getline(cin, input);

    // Input validation
    if (input.empty())
    {
        handle_error("Error: Empty input detected. Please enter an expression.");
        return 1;
    }

    // Create lexer and interpreter objects
    Lexer lexer(input);
    Interpreter interpreter(lexer);

    // Process the expression and handle any exceptions gracefully
    try
    {
        int result = interpreter.expr();
        cout << "\033[1;32m\nResult = " << result << "\033[0m\n"; // Green text for success
    }
    catch (...)
    {
        handle_error("Error: Something went wrong while evaluating the expression.");
    }

    return 0;
}
