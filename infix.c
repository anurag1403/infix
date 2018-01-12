#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stack.h"
#define OPERAND 10 
#define OPERATOR 20
#define	END	30
#define ERROR	40
#define MAX 128
int readline(char *arr, int len) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n' && i < len - 1) {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}
typedef struct token {
	int type; // type takes values OPERAND/OPERATOR/END/
	int number;
	char op;
}token;
enum states { SPC, DIG, OPR, STOP, ERR };
token *getnext(char *arr) {
	static int currstate = SPC;
	int nextstate;
	static int i = 0;
	int num;
	token *t = (token *)malloc(sizeof(token));
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': 
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%':
				nextstate = OPR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERR;
				break;
		}	

		switch(currstate) {
			case SPC:
				if(nextstate == DIG)
					num = arr[i] - '0';			
				break;
			case DIG:
				if(i > 1) {
					if(arr[i-2] == '+' || arr[i-2] =='-' || arr[i-2] == '/' || arr[i-2] == '*' || arr[i-2] == '%')
						num = arr[i-1] - '0';
					if(nextstate == DIG) {
						num = num * 10 + arr[i] - '0';
					}
					else {
						currstate = nextstate;
						t->type = OPERAND;
						t->number = num;
						if(nextstate != STOP)
							i++;
						return t;
					}
					if(nextstate == STOP) {
						currstate = nextstate;
						t->type = OPERAND;
						t->number = num;
						return t;
					}
				}
				else {
					if(nextstate == DIG)
						num = num * 10 + arr[i - 1] - '0';
					else  {
						t->type = OPERAND;
						t->number = num;
						currstate = nextstate;
						i++;
						return t;
					}
				}
				break;
			case OPR:
				t->type = OPERATOR;
				t->op = arr[i - 1];	
				currstate = nextstate;
				i++;
				return t;
				break;
			case STOP:
				t->type = END;
				currstate = nextstate;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				return t;
				break;
		}
		currstate = nextstate;
		i++;
	}
}
int infix(char *str) {
	token *t;
	stack a, b;
	int result, x, y;
	init(&a);
	init(&b);
	while(1) {
		t = getnext(str);
		if(t->type == OPERAND) {
			push(&a, t->number);
		}
		else if(t->type == OPERATOR) {
			if(t->op == '*') {
				t = getnext(str);
				push(&a, t->number);
				if(!empty(&a))
					x = pop(&a);
				else 
					return INT_MIN;
				if(!empty(&a))
					y = pop(&a);
				else 
					return INT_MIN;
				result = y * x;
				push(&a, result);
			} 
			else if(t->op == '/') {
				t = getnext(str);
				push(&a, t->number);
				if(!empty(&a))
					x = pop(&a);
				else 
					return INT_MIN;
				if(!empty(&a))
					y = pop(&a);
				else 
					return INT_MIN;
				result = y / x;
				push(&a, result);
			} 
			else if(t->op == '%') {
				t = getnext(str);
				push(&a, t->number);
				if(!empty(&a))
					x = pop(&a);
				else 
					return INT_MIN;
				if(!empty(&a))
					y = pop(&a);
				else 
					return INT_MIN;
				result = y % x;
				push(&a, result);
			}
			else
				push(&b, t->op); 
		}
		else if (t->type == ERROR) 
			return INT_MIN; 
		else {
			if(empty(&b)) {
				if(!empty(&a))
					result = pop(&a);
				else
					return INT_MIN;
				if(empty(&a))
					return result;
				else
					return INT_MIN;
			}
			else if(t->type == END)
				break; 
		}
	}
	while(1) {
		if(!empty(&b)) {
			c = pop(&b);
			if(!empty(&a)) 
				x = pop(&a); 
			else
				return INT_MIN;
			if(!empty(&a)) 
				y = pop(&a); 
			else
				return INT_MIN;
			switch(c) {
				case '+':
					result = y + x;
					break;
				case '-':
					result = y - x;
					break;
			}	
			push(&a, result);
		}
		else {
			if(!empty(&a))
 				result = pop(&a);
			else
				return INT_MIN;
			if(empty(&a))
				return result;
			else
				return INT_MIN;
		}
	}
}	
int main() {
	char str[128];
	int x, ans;
	while((x = readline(str, 128))) {
		ans = infix(str);
		if(ans == INT_MIN) {
			fprintf(stderr, "Erorr in expression\n");
		}  else
			fprintf(stdout, "%d\n", ans);
	}
	return 0;
}			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
