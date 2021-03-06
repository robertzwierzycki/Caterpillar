// Projekt 1 AiSD Robert Zwierzycki 172121

#include "stdafx.h"
#include <iostream>

bool koniec = false;

struct module {
	char znak;
	module* next;
	module* prev;
	module() {
		next = NULL;
	}
};

struct caterpillar {
	module *first;
	module *last;
	char* ciag;
	caterpillar() {
		first = NULL;
		last = NULL;
	}
	void addFirst(char znak) {
		module *nowyModul = new module;
		nowyModul->znak = znak;
		nowyModul->next = first;
		nowyModul->prev = NULL;
		if (first != NULL) {
			first->prev = nowyModul;
		}
		first = nowyModul;
	}
	void addLast(char znak) {
		module *nowyModul = new module;
		nowyModul->znak = znak;
		nowyModul->prev = last;
		if (first != NULL) {
			last->next = nowyModul;
			last = nowyModul;
		}
		else {
			first = nowyModul;
			last = first;
		}
		last = nowyModul;
	}
	void removeFirst() {
		if (first->next == NULL) {
			first = NULL;
			last = NULL;
			koniec = true;
		}
		else {
			first = first->next;
			first->prev = NULL;
		}
	}
	void removeLast() {
		if (last->prev == NULL) {
			first = NULL;
			last = NULL;
			koniec = true;
		}
		else {
			last = last->prev;
			last->next = NULL;
		}
	}
	void PrintCaterpillar() {
		module *tmp = first;
		while (tmp != NULL)
		{
			printf("%c", tmp->znak);
			tmp = tmp->next;
		}
	}
};

void funkcja(caterpillar *xyz, char *znak, char *kierunek);

int main()
{
	// n - width
	// m - height
	// c - number of moves
	// x - pozX
	// y - pozY
	// d - length

	int n, m, c, x, y, d, tmp;
	char kierunek, q;
	scanf("%d %d %d %d %d %d", &n, &m, &c, &x, &y, &d);
	x = x - 1;
	y = y - 1;
	caterpillar *xyz = new caterpillar;
	for (int i = 0; i < d; i++) {
		scanf(" %c", &q);
		xyz->addLast(q);
	}
	char **tab;
	if (m > n) {
		tab = (char**)malloc(n * sizeof(char*));
		for (int i = 0; i < n; i++)
		{
			tab[i] = (char*)malloc(m * sizeof(char));
		}
		tmp = m;
		m = n;
		n = tmp;
		tmp = x;
		x = y;
		y = tmp;
	}
	else {
		tab = (char**)malloc(m * sizeof(char*));
		for (int i = 0; i < m; i++)
		{
			tab[i] = (char*)malloc(n * sizeof(char));
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf(" %c", &tab[i][j]);
		}
	}
	//operation of the loop
	//1.I take a character from poz x,y
	//2.I move x,y
	kierunek = '4';
	for (int i = 0; i < c; i++) {
		if (koniec == false) {
			funkcja(xyz, &tab[y][x], &kierunek);
			switch (kierunek)
			{
			case ('1'):	//up
				y--;
				if (y < 0) {
					y = m - 1;
				}
				break;

			case ('2'):	//down
				y++;
				if (y >= m) {
					y = 0;
				}
				break;

			case ('3'):	//left
				x--;
				if (x < 0) {
					x = n - 1;
				}
				break;

			case ('4'):	//right
				x++;
				if (x >= n) {
					x = 0;
				}
				break;
			}
		}
		else {
			xyz->addFirst('#');
			break;
		}
	}
	//I move back x, y positions by one move
	switch (kierunek)
	{
	case ('2'):	//up -> down
		y--;
		if (y < 0) {
			y = m - 1;
		}
		break;

	case ('1'):	//down -> up
		y++;
		if (y >= m) {
			y = 0;
		}
		break;

	case ('4'):	//left -> right
		x--;
		if (x < 0) {
			x = n - 1;
		}
		break;

	case ('3'):	//right -> left
		x++;
		if (x >= n) {
			x = 0;
		}
		break;
	}
	x++;
	y++;
	if (m > n) {
		tmp = x;
		x = y;
		y = tmp;
	}
	printf("%d %d ", x, y);
	xyz->PrintCaterpillar();
	printf("\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (tab[i][j] == '!') {
				tab[i][j] = '@';
			}
		}
	}
	for (int i = 0; i < m; i++) {
		fwrite(tab[i], 1, n, stdout);
		printf("\n");
	}
	//freeing memory
	for (int i = 0; i < m - 1; i++) {
		free(tab[i]);
	}
	free(tab);
	//system("pause");
	return 0;
}

void funkcja(caterpillar *xyz, char *znak, char *kierunek) {
	if (*znak >= 'a' && *znak <= 'z') {
		if (*znak == 'a') {
			xyz->addFirst(*znak);
			*znak = '@';
		}
		else {
			xyz->addFirst(*znak);
			*znak -= 1;
		}
	}
	else if (*znak >= 'A' && *znak <= 'Z') {
		if (*znak == 'A') {
			xyz->addLast(*znak + 32);
			*znak = '!';
		}
		else {
			xyz->addLast(*znak + 32);
			*znak -= 1;
		}
	}
	else if (*znak >= '1' && *znak <= '4') {
		*kierunek = *znak;
	}
	else if (*znak == '!') {
		xyz->removeLast();
	}
	else if (*znak == '@') {
		xyz->removeFirst();
	}
}


