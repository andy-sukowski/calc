/* See LICENSE file for copyright and license details. */

#define _POSIX_C_SOURCE	199309L
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node_float *operands = NULL;
struct node_char *operators = NULL;

/* Can store an operator or a token */
struct token {
	char operator;
	float operand;
};

/* Return precedence of a given operator */
int prec(char op)
{
	switch (op) {
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case '^':
		return 4;
	default:
		printf("Invalid operator: %c\n", op);
		exit(EXIT_FAILURE);
	}
}

/* Check if given token is an operand */
bool is_operand(char *token)
{
	char *foo;
	strtod(token, &foo);
	if (token != foo)
		return true;
	else
		return false;
}

/* Check if given token is an operator */
bool is_operator(char token)
{
	if (token == '+' ||
	    token == '-' ||
	    token == '*' ||
	    token == '/' ||
	    token == '^')
		return true;
	else
		return false;
}

/* Apply mathematical operation to top two elements on the stack */
float eval(char op)
{
	float tmp = pop_float(&operands);
	switch (op) {
	case '+':
		return pop_float(&operands) + tmp;
	case '-':
		return pop_float(&operands) - tmp;
	case '*':
		return pop_float(&operands) * tmp;
	case '/':
		return pop_float(&operands) / tmp;
	case '^':
		return pow(pop_float(&operands), tmp);
	default:
		printf("Invalid operator: %c\n", op);
		exit(EXIT_FAILURE);
	}
}

/* Remove leading spaces from string */
void rmspaces(char **str)
{
	while (isspace(**str))
		(*str)++;
}

/* Return first token of given arithmetic expression */
struct token *tokenize(char **expr)
{
	static bool op_allowed = false;
	struct token *token = (struct token*) malloc(sizeof(struct token));

	if (op_allowed && is_operator(*expr[0])) {
		token->operator = *expr[0];
		op_allowed = false;
		(*expr)++;
	} else if (!op_allowed && *expr[0] == '(') {
		token->operator = *expr[0];
		(*expr)++;
	} else if (op_allowed && *expr[0] == ')') {
		token->operator = *expr[0];
		(*expr)++;
	} else {
		char *rest;
		token->operand = strtof(*expr, &rest);
		if (*expr == rest) {
			printf("Invalid expression\n");
			exit(EXIT_FAILURE);
		}
		strcpy(*expr, rest);
		op_allowed = true;
	}

	rmspaces(expr);

	return token;
}

/* Handle a given token, which might be an operand or an operator */
void handle_token(struct token *token)
{
	if (token->operator == '\0') { // token is operand
		push_float(&operands, token->operand);
	} else if (is_operator(token->operator)) {
		while (operators != NULL && operators->data != '(' &&
			prec(token->operator) <= prec(operators->data)) {
			float result = eval(pop_char(&operators));
			push_float(&operands, result);
		}
		push_char(&operators, token->operator);
	} else if (token->operator == '(') {
		push_char(&operators, token->operator);
	} else if (token->operator == ')') {
		while (operators != NULL && operators->data != '(') {
			float result = eval(pop_char(&operators));
			push_float(&operands, result);
		}
		pop_char(&operators);
	} else {
		printf("Ivalid operator: %c\n", token->operator);
		exit(EXIT_FAILURE);
	}
}

/* Handle command line arguments */
int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage:   %s <arith_expr>\n"
			"Example: %s \"5 2 3 * +\"\n",
			argv[0], argv[0]);
		exit(EXIT_FAILURE);
	}

	char *expr = argv[1];
	rmspaces(&expr);
	struct token *token;
	while (expr[0] != '\0') {
		token = tokenize(&expr);
		handle_token(token);
	}
	while (operators != NULL) {
		float result = eval(pop_char(&operators));
		push_float(&operands, result);
	}
	if (operands == NULL || operands->next != NULL) {
		printf("Too many operands on stack\n");
		exit(EXIT_FAILURE);
	}

	printf("Result: %f\n", operands->data);

	return 0;
}
