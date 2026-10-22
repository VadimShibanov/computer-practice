#include <iostream>
#include <windows.h>

using namespace std;

struct node {
	int a;
	struct node* next;
};

typedef struct node* Node_ptr;

Node_ptr input(int n)
{
	Node_ptr p = NULL, pred = NULL;

	for (int i = 0; i < n; i++) {
		p = new struct node;
		p->a = rand() / 1000 - 100;
		cout << "Случайное число: " << p->a << endl;
		p->next = pred;
		pred = p;
	}

	return p;
}

void printList(Node_ptr head) {
	cout << "Список случайных чисел: ";
	Node_ptr current = head;
	while (current != NULL) {
		cout << current->a << " -> ";
		current = current->next;
	}
	cout << "NULL" << endl;
}

void del_node(Node_ptr p, int E) {
	Node_ptr x = p;
	while (x != NULL) {
		if (x->a == E) {
			if (x->next != NULL) {
				Node_ptr y = x->next;
				x->next = x->next->next;
				delete y;
			}
		}

		x = x->next;
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_CTYPE, "Russian");

	int n = 5;
	cout << "Создаем список из " << n << " элементов..." << endl;

	Node_ptr myList = input(n);

	printList(myList);

	del_node(myList, -81);

	printList(myList);

	return 0;
}