#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void pr(char *value) {
    printf("%s\n", value);
}

double evaluate_expression(char **expr);

double evaluate_value(char **expr) {
    double result;

    if (**expr == '(') {
        (*expr)++; // Пропустить открывающую скобку '('
        result = evaluate_expression(expr);
        (*expr)++; // Пропустить закрывающую скобку ')'
    } else {
        result = strtod(*expr, expr);
    }

    return result;
}

double evaluate_term(char **expr) {
    double left = evaluate_value(expr);

    while (**expr == '*' || **expr == '/') {
        char op = **expr;
        (*expr)++; // Пропустить оператор

        double right = evaluate_value(expr);

        switch (op) {
            case '*':
                left *= right;
                break;
            case '/':
                left /= right;
                break;
            default:
                break;
        }
    }

    return left;
}

double evaluate_expression(char **expr) {
    double left = evaluate_term(expr);

    while (**expr == '+' || **expr == '-') {
        char op = **expr;
        (*expr)++; // Пропустить оператор

        double right = evaluate_term(expr);

        switch (op) {
            case '+':
                left += right;
                break;
            case '-':
                left -= right;
                break;
            default:
                break;
        }
    }

    return left;
}

int main() {
    char input[100];
    while (1) {
        printf(">>> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '@') {
            pr(input + 1);
        } else {
            char *expr = input;
            double result = evaluate_expression(&expr);
            printf("%f\n", result);
        }
    }
    return 0;
}