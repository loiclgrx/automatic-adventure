/* parser.c -- without the optimizations */

#include "global.hpp"

int lookahead;

void match(int);
void start(), list(), expr(), moreterms(), term(), morefactors(), factor(), assignment(), exponential_arguments(), more_exponential_arguments();

#define MAX_STACK_SIZE 100
int stack[MAX_STACK_SIZE];
int top = -1;

void push(int value)
{
    if (top < MAX_STACK_SIZE - 1)
    {
        stack[++top] = value;
    }
    else
    {
        error("Stack overflow");
    }
}

int pop()
{
    if (top >= 0)
    {
        return stack[top--];
    }
    else
    {
        error("Stack underflow");
        return 0; // Return a default value in case of underflow
    }
}

void parse() // parses and translates expression list
{
    lookahead = lexan();
    start();
}

void start()
{
    // Just one production for start, so we don't need to check lookahead
    list();
    match(DONE);
}

void list()
{
    if (lookahead == '(' || lookahead == ID || lookahead == NUM)
    {
        assignment();
        match(';');
        list();
    }
    else
    {
        // Empty
    }
}

void assignment()
{
    if (lookahead == ID)
    {
        int id_number = token_value;
        match(ID);
        emit(ID, id_number);
        match('=');
        expr();
        int result = pop();
        emit('=', token_value);
        symtable[id_number].value = result;
        printf("%s = %d\n", symtable[id_number].lexeme, result); // Print the assigned value
    }
    else
    {
        error("syntax error in assignment");
    }
}

void expr()
{
    // Just one production for expr, so we don't need to check lookahead
    term();
    moreterms();
}

void moreterms()
{
    if (lookahead == '+')
    {
        match('+');
        term();

        int b = pop();
        int a = pop();
        push(a + b);

        emit('+', token_value);
        moreterms();
    }
    else if (lookahead == '-')
    {
        match('-');
        term();

        int b = pop();
        int a = pop();
        push(a - b);

        emit('-', token_value);
        moreterms();
    }
    else
    {
        // Empty
    }
}

void term()
{
    // Just one production for term, so we don't need to check lookahead
    factor();
    morefactors();
}

void morefactors()
{
    if (lookahead == '*')
    {
        match('*');
        factor();

        int b = pop();
        int a = pop();
        push(a * b);

        emit('*', token_value);
        morefactors();
    }
    else if (lookahead == '/')
    {
        match('/');
        factor();

        int b = pop();
        int a = pop();
        if (b == 0)
        {
            error("Division by zero");
            push(0); // Push a default value on error
        }
        else
        {
            push(a / b);
        }

        emit('/', token_value);
        morefactors();
    }
    else if (lookahead == DIV)
    {
        match(DIV);
        factor();

        int b = pop();
        int a = pop();
        if (b == 0)
        {
            error("Division by zero");
            push(0); // Push a default value on error
        }
        else
        {
            push(a / b);
        }

        emit(DIV, token_value);
        morefactors();
    }
    else if (lookahead == MOD)
    {
        match(MOD);
        factor();

        int b = pop();
        int a = pop();
        if (b == 0)
        {
            error("Division by zero");
            push(0); // Push a default value on error
        }
        else
        {
            push(a % b);
        }

        emit(MOD, token_value);
        morefactors();
    }
    else
    {
        // Empty
    }
}

void factor()
{
    exponential_arguments();
    more_exponential_arguments();
}

void more_exponential_arguments()
{
    if (lookahead == '^')
    {
        match('^');
        exponential_arguments();

        int exp = pop();
        int base = pop();
        int result = 1;

        for (int i = 0; i < exp; i++)
        {
            result *= base;
        }

        push(result);

        emit('^', token_value);
        more_exponential_arguments();
    }
    else
    {
        // Empty
    }
}

void exponential_arguments()
{
    if (lookahead == '(')
    {
        match('(');
        expr();
        match(')');
    }
    else if (lookahead == ID)
    {
        int id_number = token_value;
        match(ID);
        int var_value = symtable[id_number].value;
        push(var_value);

        emit(ID, id_number);
    }
    else if (lookahead == NUM)
    {
        int num_value = token_value;
        match(NUM);

        push(num_value);

        emit(NUM, num_value);
    }
    else
        error("syntax error in factor");
}

void match(int t)
{
    if (lookahead == t)
        lookahead = lexan();
    else
        error("syntax error in match");
}