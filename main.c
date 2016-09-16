#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

float eval_numeric_expr(char** input);
float addition(char** input);
float subtraction(char** input);
float multiplication(char** input);
float division(char** input);
float modulus(char** input);
float number(char** input);

bool eval_boolean_expr(char** input);
bool conjunction(char** input);
bool disjunction(char** input);
bool negation(char** input);
bool boolean(char** input);

int main() {
    const size_t input_size = 130;

    char* input = calloc(input_size, sizeof(char));
    char* resp = calloc(3, sizeof(char));

    puts("Enter your expression:");
    fgets(input, input_size, stdin);

    puts("Is it a numeric (1) or boolean (2) expression?");
    fgets(resp, 3, stdin);

    puts("It results in:");

    if (*resp == '1') {
        printf("%f\n", eval_numeric_expr(&input));
    } else {
        printf("%d\n", eval_boolean_expr(&input));
    }

    free(input);
    free(resp);

    return EXIT_SUCCESS;
}

float eval_numeric_expr(char** input) {
    if (**input == ' ') {
        (*input)++;
    }

    switch (**input) {
    case '+':
        return addition(input);
    case '-':
        if (*((*input) + 1) == ' ') {
            return subtraction(input);
        }

        return number(input);
    case '*':
        return multiplication(input);
    case '/':
        return division(input);
    case '%':
        return modulus(input);
    default:
        return number(input);
    }
}

float addition(char** input) {
    (*input)++;

    return eval_numeric_expr(input) + eval_numeric_expr(input);
}


float subtraction(char** input) {
    (*input)++;

    return eval_numeric_expr(input) - eval_numeric_expr(input);
}


float multiplication(char** input) {
    (*input)++;

    return eval_numeric_expr(input) * eval_numeric_expr(input);
}


float division(char** input) {
    (*input)++;

    return eval_numeric_expr(input) / eval_numeric_expr(input);
}

float modulus(char** input) {
    (*input)++;

    float first = eval_numeric_expr(input);

    return fmod(first, eval_numeric_expr(input));
}

float number(char** input) {
    char* new_start;

    float result = strtof(*input, &new_start);

    *input = new_start;

    return result;
}

bool eval_boolean_expr(char** input) {
    if (**input == ' ') {
        (*input)++;
    }

    switch (**input) {
    case '+':
        return disjunction(input);
    case '*':
        return conjunction(input);
    case '!':
        return negation(input);
    default:
        return boolean(input);
    }
}

bool conjunction(char** input) {
    (*input)++;

    bool first = eval_boolean_expr(input);

    return first & eval_boolean_expr(input);
}

bool disjunction(char** input) {
    (*input)++;

    bool first = eval_boolean_expr(input);

    return first | eval_boolean_expr(input);
}

bool negation(char** input) {
    (*input)++;

    return !eval_boolean_expr(input);
}

bool boolean(char** input) {
    char c = **input;

    (*input)++;

    return c != '0';
}
