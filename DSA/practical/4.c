#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure
typedef struct Stack {
    int top;
    char items[MAX];
} Stack;

// Function to initialize the stack
void initStack(Stack* s) {
    s->top = -1;
}

// Function to check if the stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Function to push an element to the stack
void push(Stack* s, char value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    } else {
        printf("Stack Overflow!\n");
    }
}

// Function to pop an element from the stack
char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    } else {
        printf("Stack Underflow!\n");
        return -1;
    }
}

// Function to peek the top element of the stack
char peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    } else {
        return -1;
    }
}

// Function to check precedence of operators
int precedence(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '*' || operator == '/') {
        return 2;
    } else if (operator == '^') {
        return 3;
    }
    return 0;
}

// Function to perform infix to postfix conversion
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0, k = 0;
    char symbol;

    while ((symbol = infix[i++]) != '\0') {
        if (isalnum(symbol)) {  // If the symbol is an operand, add it to the result
            postfix[k++] = symbol;
        } else if (symbol == '(') {  // If it's an opening parenthesis, push it onto the stack
            push(&s, symbol);
        } else if (symbol == ')') {  // If it's a closing parenthesis, pop and add operators to the result until '(' is found
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s);  // Pop the '('
        } else {  // If it's an operator
            while (!isEmpty(&s) && precedence(symbol) <= precedence(peek(&s))) {
                postfix[k++] = pop(&s);
            }
            push(&s, symbol);
        }
    }

    // Pop all remaining operators from the stack
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }

    postfix[k] = '\0';
}

// Function to evaluate the postfix expression
int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0;
    char symbol;

    while ((symbol = postfix[i++]) != '\0') {
        if (isdigit(symbol)) {  // If it's a digit, push it onto the stack
            push(&s, symbol - '0');
        } else {  // If it's an operator, pop two operands and perform the operation
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            int result;

            switch (symbol) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                case '^': result = operand1 ^ operand2; break;
                default: result = 0;
            }
            push(&s, result);
        }
    }

    return pop(&s);  // The final result will be the only item left in the stack
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Evaluation result: %d\n", result);

    return 0;
}
