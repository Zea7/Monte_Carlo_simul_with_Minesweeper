#include <iostream>
#include <stdlib.h>
#include <random>
#include "Minesweeper.h"
#include <queue>
#include <utility>
#pragma warning(disable: 4996)
using namespace std;

void Mine::initialize() {
	if (this->bomb >= (this->x) * (this->y) || this->blocked >= (this->x) * (this->y) - this->bomb) {
		cout << "Wrong input." << endl;
		*this = Mine();
		return initialize();
	}
	int x = this->x;
	int y = this->y;
	this->blocks = new char* [x];
	for (int i = 0; i < x; i++) {
		this->blocks[i] = new char[y];
	}
	random_device rd;
	mt19937 gen(rd());

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			this->blocks[i][j] = 'O';
			Node* a = new Node();
			*a = { i,j,NULL };
			this->n.add(a);
			this->insert.add(a);
		}
	}


	for (int i = 0; i < this->blocked; i++) {
		uniform_int_distribution<int> r(1, this->n.length);
		int x = r(gen);
		Node p = this->n.ele(x);
		this->n.del(p.x, p.y);
		this->insert.del(p.x, p.y);
		this->blocks[p.x][p.y] = 'X';
	}
	this->board = new char* [x];
	for (int i = 0; i < x; i++) {
		this->board[i] = new char[y];
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (this->blocks[i][j] == 'X') this->board[i][j] = 'X';
			else this->board[i][j] = 'O';
		}
	}

}
void Mine::start() {
	random_device rd;
	mt19937 gen(rd());
	for (int i = 0; i < this->bomb; i++) {
		uniform_int_distribution<int> r(1, this->n.length);
		int x = r(gen);
		Node p = this->n.ele(x);
		this->n.del(p.x, p.y);
		this->blocks[p.x][p.y] = 'B';
	}
}


void Mine::mark(int x, int y) {
	if (this->board[x][y] == 'O') {
		this->board[x][y] = 'm';
		m++;
		if (this->blocks[x][y] == 'B')
			this->bomb--;
	}
	else if (this->board[x][y] == 'm') {
		this->board[x][y] = 'O';
		m--;
		if (this->blocks[x][y] == 'B')
			this->bomb++;
	}
	return this->game();

}

int Mine::check_the_number(int x, int y) {
	int p = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			if (!is_valid((x + i), (y + j))) continue;
			if (this->blocks[(x + i)][(y + j)] == 'B')
				p++;

		}
	}
	return p;
}
bool Mine::is_valid(int x, int y) {
	if (x >= this->x || y >= this->y || x < 0 || y < 0 || this->blocks[x][y] == 'X')
		return false;
	return true;
}

void Mine::game_for_player(int x, int y, char e) {
	if (e == 'o') return this->open_for_player(x, y);
	else if (e == 'm') return this->mark(x, y);
	else if (e == 'h') return this->hint_for_player();

	return;
}

void Mine::open_for_player(int x, int y) {
	int p;
	if (this->blocks[x][y] == 'B') {
		this->blocks[x][y] = 'B';
	}
	else {
		this->n.del(x, y);
		if (k == 0) {
			this->start();
			k++;
		}
		if ((p = check_the_number(x, y)) == 0) return this->open_stack_for_player(x, y);
		else {
			this->board[x][y] = p + 48;
		}
	}
	return ;
}

void Mine::hint_for_player() {
	if (hint == 0) return;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int>r(1, this->n.length);
	int x = r(gen);
	Node p = this->n.ele(x);
	hint--;
	this->open_for_player(p.x, p.y);
}

void Mine::open_stack_for_player(int x, int y) {
	this->board[x][y] = '0';
	queue<pair<int, int>> q;
	q.push(pair<int, int>(x, y));
	int x_, y_;
	while (!q.empty()) {
		pair<int, int> r = q.front();
		x_ = r.first;
		y_ = r.second;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (!is_valid((x_ + i), (y_ + j))) continue;
				if (this->check_the_number((x_ + i), (y_ + j)) == 0 && this->n.find((x_ + i), (y_ + j)))
					q.push(pair<int, int>((x_ + i), (y_ + j)));

				this->board[(x_ + i)][(y_ + j)] = this->check_the_number((x_ + i), (y_ + j)) + 48;
				this->n.del((x_ + i), (y_ + j));
			}
		}
		q.pop();
	}
	return;
}

void start_game() {
	Mine m = Mine();
	m.initialize();
	m.game();
}