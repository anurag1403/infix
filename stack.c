#include<stdio.h>
#include "stack.h"
void push(stack *s, int num) {
	s->a[s->i]= num;
	(s->i)++;
}
int pop(stack *s) {
	int t = s->a[s->i - 1];
	(s->i)--;
	return t;
}
int empty(stack *s) {
	return s->i == 0;
}
int full(stack *s) {
	return s->i == MAX;
}
void init(stack *s) {
	s->i = 0;
}
