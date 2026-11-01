#include <iostream>
#include <windows.h>

using namespace std;

struct node {
	int a;
	struct node* next;
};

typedef struct node* Node_ptr;

Node_ptr input(int n) {
	Node_ptr curr = NULL, pred = NULL;

	cout << "Список:" << endl;
	for (int i = 0; i < n; i++) {
		curr = new struct node;
		cout << "Введи число ";
		cin >> curr->a;
		cout << "Элемент:" << curr->a << endl;
		curr->next = pred;
		pred = curr;
	}
	cout << endl;
	return pred;
}

Node_ptr del_node(Node_ptr head) {
	if (head == NULL) return NULL;

	Node_ptr x = head->next;
	int min = head->a;

	while (x != NULL) {
		if (x->a < min) min = x->a;
		x = x->next;
	}

	Node_ptr toDelete = NULL;

	while (head != NULL && head->a == min) {
		toDelete = head;
		head = head->next;
		delete toDelete;
	}

	if (head == NULL) return NULL;

	Node_ptr curr = head;
	
	while (curr->next != NULL) {
		if (curr->next->a == min) {
			toDelete = curr->next;
			curr->next = curr->next->next;
			delete toDelete;
		}
		else {
			curr = curr->next;
		}
	}

	return head;
}

void printList(Node_ptr head) {
	if (head == NULL) {
		cout << "Список пуст!";
		cout << endl;
		return;
	}

	cout << "Вывод элементов:" << endl;

	Node_ptr curr = head;

	while (curr != NULL) {
		cout << "Элемент: " << curr->a << endl;
		curr = curr->next;
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_CTYPE, "Russian");

	Node_ptr list = input(5);
	printList(list);

	Node_ptr listNew = del_node(list);

	cout << endl;

	printList(listNew);

	return 0;
}