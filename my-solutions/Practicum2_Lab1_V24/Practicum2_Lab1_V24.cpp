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
		curr->a = rand() / 1000 - 100;
		cout << "Элемент:" << curr->a << endl;
		curr->next = pred;
		pred = curr;
	}
	cout << endl;
	return pred;
}

void del_node() {

}

void printList(Node_ptr head) {
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

	printList(input(5));
	return 0;
}