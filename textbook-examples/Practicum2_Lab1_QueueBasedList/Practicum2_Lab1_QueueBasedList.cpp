#include <iostream>
#include <windows.h>

using namespace std;

struct node {
	int a;
	struct node* next;
};

typedef struct node* Node_ptr;

Node_ptr input_1(int n) {
	Node_ptr p = NULL, head = NULL, pred = NULL;

	for (int i = 0; i < n; i++) {
		if (head == NULL) {
			head = new struct node;
			head->a = rand() / 100 - 100;
			head->next = NULL;
			pred = head;
		}
		else {
			p = new struct node;
			p->a = rand() / 100 - 100;
			p->next = NULL;
			pred->next = p;
			pred = p;
		}

		cout << "Элемент " << pred->a << endl;
	}

	return head;
}

void sort(Node_ptr p) {
	Node_ptr x, max, y;
	y = p;

	while (y != NULL) {
		max = y;
		x = y;
		while (x != NULL) {
			if (x->a > max->a) max = x;
			x = x->next;
		}

		int b = max->a;
		max->a = y->a;
		y->a = b;
		y = y->next;
	}
}

void printList(Node_ptr head) {
	cout << "Очередь: ";
	Node_ptr current = head;

	while (current != NULL) {
		cout << current->a << " -> ";
		current = current->next;
	}

	cout << "NULL" << endl;
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_CTYPE, "Russian");

	int n = 5;
	cout << "Создаем очередь из " << n << " элементов..." << endl;

	Node_ptr myQueue = input_1(n);
	printList(myQueue);

	sort(myQueue);
	printList(myQueue);
	return 0;
}