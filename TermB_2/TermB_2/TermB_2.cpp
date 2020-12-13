#include <iostream>
#include <random>
#include "Minesweeper.h"

using namespace std;

class Player {
private:
    int act = 0;
    int win = 0;
    int lose = 0;
    int x;
    int y;
    int bomb;
    int blocked;
    int hint;
    Mine m;
    void play();
    void rule_1();
    void playing_game(int n);
    void print_result();
public:
    void run_simulator(int n);
};

Player::Player() {
    m.initialize();
    this->x = m.x;
    this->y = m.y;
    this->bomb = m.bomb;
    this->blocked = m.blocked;
    this->hint = m.hint;
}

void Player::play() {
    return;
}

void Player::rule_1() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> r(1, this->m.insert.length);

}

void Player::playing_game(int n) {
    if (n == 0) return;
    else {
        this->rule_1();
        return playing_game(--n);
    }
}

void Player::print_result() {
    cout << "총 진행 횟수 : " << this->act << endl;
    cout << "이긴 횟수 : " << this->win << endl;
    cout << "진 횟수 : " << this->lose << endl;
    printf("승률 : %.2f\n", (double)(this->win / this->act));
}

void Player::run_simulator(int n) {
    this->playing_game(n);
    this->print_result();
}

int main()
{
    
}

