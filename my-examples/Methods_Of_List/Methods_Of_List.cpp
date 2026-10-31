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

Node_ptr del_node(Node_ptr head, int E) {
	if (head != NULL) {
		if (head->a == E) {
			Node_ptr toDelete = head;

			if (head->next != NULL) {
				head = head->next;
			}
			else head = NULL;

			delete toDelete;
		}
	}

	Node_ptr curr = head;

	while (curr != NULL) {
		if (curr->next != NULL) {
			if (curr->next->a == E) {
				Node_ptr toDelete = curr->next;
				curr->next = curr->next->next;
				delete toDelete;
			}
		}

		curr = curr->next;
	}

	return head;
}

Node_ptr del_nodeV24(Node_ptr head) {
	if (head == NULL) return NULL;

	Node_ptr x = head;
	int min = head->a;

	while (x != NULL) {
		if (x->a < min) {
			min = x->a;
		}
		x = x->next;
	}

	Node_ptr toDelete = NULL;

IfSearchingNumberHeadAgain:
	if (head != NULL) {
		if (head->a == min) {
			toDelete = head;

			if (head->next != NULL) {
				head = head->next;
			}
			else head = NULL;

			delete toDelete;
		}
	}

	if (head != NULL && head->a == min) goto IfSearchingNumberHeadAgain;

	Node_ptr curr = head;
	Node_ptr pred = NULL;

	while (curr != NULL) {
		if (curr->next != NULL) {
			if (curr->next->a == min) {
				toDelete = curr->next;
				curr->next = curr->next->next;
				delete toDelete;
			}
		}
		else {
			if (curr->a == min) {
				pred->next = NULL;
				delete curr;
				break;
			}
		}

		pred = curr;
		curr = curr->next;
	}

	return head;
}

Node_ptr del_nodeV24_Reafactoring(Node_ptr head) {
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

	Node_ptr listNew = del_node(list, -81);

	cout << endl;

	printList(listNew);

	return 0;
}