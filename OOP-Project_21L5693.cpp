
#include "mygraphics.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
using namespace std;
class Map
{
protected:
	char** map{};
	int row, cols;
	int w, h;
	int total_score;
public:
	Map(int r = 0, int c = 0, int w = 0, int h = 0) {
		row = r;

		cols = c;

		this->w = w;
		this->h = h;
		map = new char* [row];
		for (int i = 0; i < row; i++) {
			map[i] = new char[cols];
		}
	
		total_score = 0;
	}
	int getRow() {
		return row;
	}
	int getCol() {
		return cols;
	}

	 void GridMaking();
	virtual bool Movement() { return true; }
	virtual void print();
	virtual ~Map();
	virtual void scoreCal(){}
	virtual int getscore() { return 0; }
	virtual int getLife() { return 0; }
	virtual int getTotalScore();
};
class Ghost :public Map {
	int a1, b1;//for ghost chasing pacman
	int* x1, * y1;
	int state;

public:
	Ghost(int r = 0, int c = 0, int w = 0, int h = 0, int x = 0, int y = 0) :Map(r, c, w, h) {
		this->b1 = cols - 2;
		this->x1 = new int;
		*x1 = (cols - 2) * 5;
		this->a1 = row - 2;
		this->y1 = new int;
		*y1 = (row - 2) * 25;
		state = 0;
		GridMaking();
	}
	int getX1() {
		return *x1;
	}
	int getY1() {
		return *y1;
	}
	bool GhostMovementRandom(int,int,char);
	bool GhostMovementFastest(int, int, char);
	
	//void printghost();
	~Ghost() {
		delete x1;
		x1 = nullptr;
		delete y1;
		y1 = nullptr;
	}
};
void Map::GridMaking()
{
	for (int r = 0; r < row; r+=2) {
		for (int c = 0; c < cols; c+=2) {
			map[r][c] = '0';
		}
	}

	map[row - 1][0] = '#'; //for energizer;
	for (int r = 4; r <= 6; r++) { //wall1
		for (int c = 0; c <= (cols / 4) - 3; c++) {
			if (r == 6 || r == 4) {
				map[r][c] = '-';
			}
			else {
				map[r][c] = '\0';
			}
		}
	}
	
	for (int c = 0; c <= 5; c++) {
		map[2][c] = '-';
	}
	for (int r = 2; r <= 6; r++) {
		map[r][5] = '|';
	}
	for (int i = 4; i <= 6; i++) { //wall1
		map[i][(cols / 4) - 3] = '|';
	}
	//for (int r = 4; r <= 6; r += 2) { //wall1
	//	for (int c = 0; c <= (row / 4) - 3; c++) {
	//		map[r][c] = '-';
	//	}
	//}
	for (int r = row / 2 - 2; r <= (row / 2 - 2) + 6; r++) { //block1
		for (int c = (cols / 4) + 4; c <= ((cols / 4)) + 16; c++) {
			if (r == (row / 2 - 2) + 6 || r == row / 2 - 2) {
				map[r][c] = '-';
			}
			else map[r][c] = '\0';
		}
	}
	for (int r = row / 2 - 2; r <= (row / 2 - 2) + 6; r++) { //block1
		map[r][(cols / 4) + 16] = '|';
	}
	for (int r = row / 2 - 2; r <= (row / 2 - 2) + 6; r++) { //block1
		map[r][((cols / 4) + 4)] = '|';
	}

	for (int c = cols - 6; c < cols; c++) { //block2
		map[row - 5][c] = '-';
	}
	map[row - 5][cols - 1] = '^';
	for (int r = row - 5; r >= row - 10; r--) { //block2
		map[r][cols - 6] = '|';
	}
	map[row - 10][cols - 5] = '-';
	for (int c = cols - 3; c < cols - 1; c++) { //block2
		map[row - 7][c] = '-';
	}
	map[row - 7][cols - 1] = '^';
	for (int r = row - 10; r < row - 6; r++) { //block2
		map[r][cols - 4] = '|';
	}
	for (int r = row - 9; r < row - 5; r++) { //block2
		map[r][cols - 5] = '\0';
	}
	for (int c = cols - 5; c < cols; c++) { //block2
		map[row - 6][c] = '\0';
	}
	for (int r = row - 10; r < row - 7; r++) { //block2
		for (int c = cols - 3; c < cols; c++) {
			map[r][c] = '\0';
		}
	}
	for (int r = row - 1; r >= row - 6; r--) {
		for (int c = 1; c <= 5; c++) {
			if (c == 1 || c == 5) {
				map[r][c] = '|';
			}
			else if (r != row - 6) {
				map[r][c] = '\0';
			}
		}
	}
	for (int c = 2; c <= 4; c++) {
		map[row - 6][c] = '-';
	}
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < cols; c++) {
			if (map[r][c] == '0') {
				(total_score)++;
			}
		}
	}

}
class Energizer:Map{
	int* x;
	int* y;
	char* state;

public:
	Energizer(int a=0,int b=0,int r = 0, int c = 0, int w = 0, int h = 0, int x = 0, int y = 0) :Map(r, c, w, h) {
		this->x = new int;
		this->y = new int;
		*this->x = a;
		*this->y = b;
		state = new char;
		*state = 'p';//p for print
		
	}
	void setState(char c);
	char getstate();
	int getXE();
	int getYE();
	~Energizer() {
		delete x;
		x = NULL;
		delete y;
		y = NULL;
		delete state;
		state = NULL;
	}
};
void Energizer::setState(char c)
{
	*state = c;
}
char Energizer::getstate()
{
	return *state;
}
int Energizer::getXE()
{
	return *x;
}
int Energizer::getYE()
{
	return *y;
}
class Pacman :public Map {
	int x, y, a, b;
	int score;
	char state;
	Ghost* g1;
	Ghost* g2;
	int life;
	int walltime = 1;
	Energizer* e1;
	Energizer* e2;
	int moves;
public:
	Pacman(int r = 0, int c = 0, int w = 0, int h = 0) :Map(r, c, w, h) {
		moves = 20;
		a = 0;
		b = 0;
		score = 0;
		this->x = 0;
		this->y = 0;
		life = 3;
		g1 = new Ghost(r, c, w, h);
		g2 = new Ghost(r, c, w, h);
		e1 = new Energizer((cols-2)*5,10*25, 0, r, c, w, h);
		e2 = new Energizer(0, (row-1)*25, 0, r, c, w, h);
		state = 'a'; //a for alive and d for dead
		GridMaking();
	}
	//void check() {};
	bool Movement() override;
	void print() override;
	void scoreCal();
	int getscore();
	int getLife()override;
	~Pacman() {
		delete g1;
		delete g2;
		
		score = NULL;
	}
	int getTotalScore() override;


};
int Pacman::getLife()
{
	return life;
}
int Pacman::getTotalScore()
{
	return total_score;
}
int Pacman::getscore() {
	return score;
}
void Pacman::scoreCal() {
	score = 0;
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < cols; c++) {
			if (map[r][c] == '*') {
				score++;
			}
		}
	}
}
bool Ghost::GhostMovementFastest(int p_a, int p_b, char status)
{

	int distanceUp = 0, distanceR = 0, distanceL = 0, distanceD = 0, up = 0, down = 0, right = 0, left = 0;
	int state = 0;
	distanceUp = a1 - 1;
	distanceR = b1 + 1;
	distanceL = b1 - 1;
	distanceD = a1 + 1;
	if (p_a == a1 && p_b == b1 && status == 'a') {
		return false;
	}
	

	int l = 0, k = 0, y = 0, g = 0; //disabling keys
	
	if (*x1 == 0) {
		g++;
	}
	if (*x1 == (cols - 1) * 5) {
		l++;
	}
	if (*y1 == 0) {
		y++;
	}
	if (*y1 == (row - 1) * 25) {
		k++;
	}
	if (b1 <= cols-2) {
		if (map[a1][b1 + 1] == '|' || map[a1][b1 + 1] == '-' || map[a1][b1 + 1] == '^')
		l++;
	}
	if (b1 > 0) {
		if (map[a1][b1 - 1] == '|' || map[a1][b1 - 1] == '-' || map[a1][b1 - 1] == '^')
		g++;
	}
	if (a1 <= row - 2) {
		if ((map[a1 + 1][b1] == '|' || map[a1 + 1][b1] == '-') || map[a1 + 1][b1] == '^')
			k++;
	}
	if (a1 > 0) {
		if ((map[a1 - 1][b1] == '|' || map[a1 - 1][b1] == '-')|| map[a1 - 1][b1] == '^')
		y++;
	}

	if (p_a < a1 && p_b < b1) {

		if (distanceUp <= distanceL) {
			if (y == 0) {
				a1--;
				*this->y1 -= 25;
				state++;
			}
			else if (g == 0) {
				b1--;
				*this->x1 -= 5;
				state++;
			}
		}

		else if (distanceUp > distanceL) {
			if (g == 0) {
				b1--;
				*this->x1 -= 5;
				state++;
			}
			else if (y == 0) {
				a1--;
				*this->y1 -= 25;
				state++;
			}

		}


	}
	else if (p_b > b1 && p_a < a1) {

		if (distanceUp <= distanceR) {
			if (y == 0) {
				a1--;
				*this->y1 -= 25;
				state++;
			}
			else if (l == 0) {
				b1++;
				*this->x1 += 5;
				state++;
			}
		}
		else if (distanceUp > distanceR) {
			if (l == 0) {
				b1++;
				*this->x1 += 5;
				state++;
			}
			else if (y == 0) {
				a1--;
				*this->y1 -= 25;
				state++;
			}

		}
	}

	else if (p_a > a1 && p_b < b1) {

		if (distanceD <= distanceL) {
			if (k == 0) {
				a1++;
				*this->y1 += 25;
				state++;
			}
			else if (g == 0) {
				b1--;
				*this->x1 -= 5;
				state++;
			}
		}
		else if (distanceD > distanceL) {
			if (g == 0) {
				b1--;
				*this->x1 -= 5;
				state++;
			}
			else if (k == 0) {
				a1++;
				*this->y1 += 25;
				state++;
			}

		}

	}
	else if (p_b > b1 && p_a > a1) {
		if (distanceD <= distanceR) {
			if (k == 0) {
				a1++;
				*this->y1 += 25;
				state++;
			}
			else if (l == 0) {
				b1++;
				*this->x1 += 5;
				state++;
			}
		}
		else if (distanceD > distanceR) {
			if (l == 0) {
				b1++;
				*this->x1 += 5;
				state++;
			}
			else if (k == 0) {
				a1++;
				*this->y1 += 25;
				state++;
			}

		}
	}
	else if (p_b == b1 && p_a > a1) {
		if (k == 0) {
			a1++;
			*this->y1 += 25;

			state++;
		}
		else if (y == 0) {
			a1--;
			*this->y1 -= 25;
			state++;
		}
	}
	else if (p_b == b1 && p_a < a1) {
		if (y == 0) {
			a1--;
			*this->y1 -= 25;
			state++;
		}
		else if (k == 0) {
			a1++;
			*this->y1 += 25;

			state++;
		}
	}
	else if (p_a == a1 && p_b < b1) {
		if (g == 0) {
			b1--;
			*this->x1 -= 5;
			state++;
		}
		else if (y == 0) {
			a1--;
			*this->y1 -= 25;
			state++;
		}
	}
	else if (p_a == a1 && p_b > b1) {
		if (l == 0) {
			b1++;

			*this->x1 += 5;
			state++;
		}
		else if (y == 0) {
			a1--;
			*this->y1 -= 25;
			state++;
		}
	}
	return true;
}
void Map::print()
{

}
Map::~Map()
{
	for (int i = 0; i < row; i++) {
		delete[] map[i];
	}
	delete[] map;
	map = nullptr;

}
int Map::getTotalScore()
{
	return 0;
}
bool Pacman::Movement()
{
	
	if (moves == 0) {
		state = 'a';
    }
	if (x == e1->getXE() && y == e1->getYE()) {
		state = 'P';
		e1->setState('d');
		moves += 20;
		PlaySound(TEXT("pacman_eatfruit.wav"), NULL, SND_SYNC);
	}
	if (x == e2->getXE() && y == e2->getYE()) {
		state = 'P';
		e2->setState('d');
		moves += 20;
		PlaySound(TEXT("pacman_eatfruit.wav"), NULL, SND_SYNC);
	}
	if (state == 'P' && moves >0) {
		g1->GhostMovementRandom(a, b, state);
		g2->GhostMovementRandom(a, b, state);
	}
	else {
		bool flag1 = g1->GhostMovementFastest(a, b, state);
		bool flag2 = g2->GhostMovementRandom(a, b, state);

		if (flag1 == false) {
			a = 0; b = 0; x = 0; y = 0;
			life--;
			PlaySound(TEXT("pacman_death.wav"), NULL, SND_SYNC);
		}
		if (flag2 == false) {
			a = 0; b = 0; x = 0; y = 0;
			life--;
			PlaySound(TEXT("pacman_death.wav"), NULL, SND_SYNC);
		}
	}
	if (life == 0) {
		return false;
	}

	int l = 0, k = 0, y = 0, g = 0; //disable keys
	char c = 0;
	c = getKey();

	if (x == 0) {
		g++;
	}
	if (x == (cols - 1) * 5) {
		l++;
	}
	if (this->y == 0) {
		y++;
	}
	if (this->y == (row - 1) * 25) {
		k++;
	}
	if (b <= cols-2) {
		if ((map[a][b + 1] == '|' || map[a][b + 1] == '-') || map[a][b + 1] == '^')
		l++;
	}
	if (b > 0) {
		if (map[a][b - 1] == '|' || map[a][b - 1] == '-' || map[a][b - 1] == '^')
		g++;
	}
	if (a <= row-2 ) {
			if ((map[a + 1][b] == '|' || map[a + 1][b] == '-')|| map[a + 1][b] == '^')
				k++;
	}
	if (a > 0 ) {
		if (map[a - 1][b] == '|' || map[a - 1][b] == '-' || map[a - 1][b] == '^')
		y++;
	}
	if (c == 'q') return false;
	if (g == 0) {
		if (c == 'j') {
			this->x -= 5;
			if (b > 0) {
				if (state == 'P') {
					moves--;
				}
				map[a][b] = '*';
				b--;
				map[a][b] = state;

			}

		}
	}
	if (l == 0) {
		if (c == 'l') {
			this->x += 5;
			if (b < getCol()) {
				if (state == 'P') {
					moves--;
				}
				map[a][b] = '*';
				b++;
				map[a][b] = state;




			}
		}
	}
	if (k == 0) {
		if (c == 'k') {
			this->y += 25;
			if (a < getRow()) {
				if (state == 'P') {
					moves--;
				}
				map[a][b] = '*';
				a++;
				map[a][b] = state;
				
			}
		}
	}
	if (y == 0) {
		if (c == 'i') {
			this->y -= 25;
			if (a > 0) {
				if (state == 'P') {
					moves--;
				}
				map[a][b] = '*';
				a--;
				map[a][b] = state;
			}
		}
	}

	return true;

}
void Pacman::print()
{
	drawLine(0, 0, w, 0, 255);
	drawLine(0, 0, w, 0, 255);
	drawLine(w, h, w, -h, 255);
	drawLine(0, h, w, h, 255);
	drawLine(0, h, 0, -h, 255);
	drawLine(0, 2 * 25, 0, -h, 255);
	drawRectangle(0, 2*25-10, (25*cols / 4)-50, 7*25-10, 255, 128, 0);
	// main event loop
	if (e1->getstate() == 'p') {
		drawEllipse(5 * e1->getXE() + 5, e1->getYE() + 5, 5 * e1->getXE() + 30, e1->getYE() + 30, 255, 255, 255, 0, 128, 0);
	}
	if (e2->getstate() == 'p') {
		drawEllipse(5 * e2->getXE() + 5, e2->getYE() + 5, 5 * e2->getXE() + 30, e2->getYE() + 30, 255, 255, 255, 0, 128, 0);
	}
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < cols; c++) {
			if (map[r][c] == '0') {
				drawEllipse(25 * c + 12, 25 * r + 12, 25 * c + 23, 25 * r + 23, 0, 0, 255, 255, 255, 255);
			}
			if (walltime >0) {
				if (map[r][c] == '-' /*&& map[r][c+1] == '-'*/) {
					if (c <= cols - 1) {
						drawLine(25 * c - 12, 25 * r + 12, ((c + 1) * 25) + 23, (25 * r) + 12, 255);
					}
				}
			}
			if (walltime >0) {
				if (map[r][c] == '|' /*&& (map[r+1][c] == '|'*/) {
					if (r <= row - 2) {
						if ((map[r + 1][c] == '|'))
							drawLine(25 * c + 23, 25 * r + 12, (c * 25) + 23, (25 * (r + 1)) + 12, 255);
					}
				}
			}
			if (walltime == 1) {
				if (map[r][c] == '|') {
					if (r > 0) {
						if (map[r - 1][c] == '|')
							drawLine(25 * c + 23, 25 * r + 12, (c * 25) + 23, (25 * (r - 1)) + 12, 255);
					}
				}
			}
		}
	}
	walltime++;
	
	//Pacman
	

	
	

	drawEllipse(5 * x + 5, y + 5, 5 * x + 30, y + 30, 255, 255, 255, 255, 255, 0);
	delay(100);
	drawRectangle(5 * g1->getX1() + 5, g1->getY1() + 5, 5 * g1->getX1() + 30, g1->getY1() + 30, 0, 0, 0, 255, 0, 0);
	drawRectangle(5 * g2->getX1() + 5, g2->getY1() + 5, 5 * g2->getX1() + 30, g2->getY1() + 30, 0, 0, 0, 255, 0, 255);
	delay(100);
	drawEllipse(5 * x + 5, y + 5, 5 * x + 30, y + 30, 0, 0, 0, 0, 0, 0);
	drawRectangle(5 * g2->getX1() + 5, g2->getY1() + 5, 5 * g2->getX1() + 30, g2->getY1() + 30, 0, 0, 0, 0, 0, 0);
	drawRectangle(5 * g1->getX1() + 5, g1->getY1() + 5, 5 * g1->getX1() + 30, g1->getY1() + 30, 0, 0, 0, 0, 0, 0);
	
	

}
bool Ghost::GhostMovementRandom(int p_a, int p_b, char status) {
	if (p_a == a1 && p_b == b1 && status == 'a') {
		return false;
	}
	else if (p_a == a1 && p_b == b1 && status == 'P') {
		PlaySound(TEXT("pacman_chomp.wav"), NULL, SND_SYNC);
		*x1 = (cols - 1) * 5;
		this->a1 = row - 2;
		this->b1 = cols - 1;
		*y1 = (row - 2) * 25;
	}
	
	int l = 0, k = 0, y = 0, g = 0;

	int random = 0;

	srand(time(0));
	if (state == 0) {
		do {
			/*if (state > 0) {
				break;
			}*/


			random = rand() % 4 + 1;

			if (*x1 == 0) {
				if (random == 3) {
					random = 0;
				}
				//left
				g++;
			}
			if (*x1 == (cols - 1) * 5) {
				if (random == 4) {
					random = 0;
				}
				//right
				l++;
			}
			if (*y1 == 0) {
				if (random == 1) {
					random = 0;
				}
				//up
				y++;
			}
			if (*y1 == (row - 1) * 25) {
				if (random == 2) {
					random = 0;
				}
				//down
				k++;
			}
			if (b1 <= cols - 2) {
				if (map[a1][b1 + 1] == '|' || map[a1][b1 + 1] == '-') {
					if (random == 4) {
						random = 0;
					}
					l++;
					//right
				}
			}
			if (b1 > 0 && (map[a1][b1 - 1] == '|' || map[a1][b1 - 1] == '-')) {
				if (random == 3) {
					random = 0;
				}

				g++;
			}
			if (a1 <= row - 2) {
				if ((map[a1 + 1][b1] == '|' || map[a1 + 1][b1] == '-')) {
					if (random == 2) {
						random = 0;
					}
					k++;

				}
			}
			if (a1 > 0 && (map[a1 - 1][b1] == '|' || map[a1 - 1][b1] == '-')) {
				if (random == 1) {
					random = 0;
				}
				y++;

			}

			//1:up,2:down,3:left,4:right.

			state = random;
		} while (state == 0);
	}
	if (state > 0) {
		if (state == 1) {
			if (a1 == 0) {
				state = 0;
			}
			if (a1 > 0) {
				if (map[a1 - 1][b1] == '|' || map[a1 - 1][b1] == '-' || map[a1 - 1][b1] == '^') {
					state = 0;
				}
				else {
					a1--;
					*this->y1 -= 25;
				}
			}
			
			
		}
		else if (state == 2) {
			if (a1 == row - 1) {
				state = 0;
			}
			else if (a1 <= row - 2) {
				if (map[a1 + 1][b1] == '|' || map[a1 + 1][b1] == '-' || map[a1 + 1][b1] == '^') {
					state = 0;
				}
				else {
					a1++;
					*this->y1 += 25;
				}
			}
		}
		else if (state == 3) {
			if (b1 == 0) {
				state = 0;
			}
			else if (b1 > 0) {
				if (map[a1][b1 - 1] == '|' || map[a1][b1 - 1] == '-' || map[a1][b1 - 1] == '^') {
					state = 0;
				}
				else {
					b1--;
					*this->x1 -= 5;
				}
			}
			
			 

		}
		else if (state == 4) {
			if (b1 == cols - 1) {
				state = 0;
			}
			else if (b1 <= cols - 2) {
				if (map[a1][b1 + 1] == '|' || map[a1][b1 + 1] == '-' || map[a1][b1 + 1] == '^') {
					state = 0;
				}
				else {
					b1++;
					*this->x1 += 5;
				}
			}
		}

	}
	
return true;
}
int main() {
	// Initialising
	int w = 0, h = 0;
	int l = 0, k = 0, y = 0, g = 0; //disabling keys
	getWindowDimensions(w, h);
	
	cout << "ARE YOU READY!" << endl;
	PlaySound(TEXT("pacman_beginning.wav"), NULL, SND_SYNC);
	cls();
	showConsoleCursor(false);
	
	
	int i = 0, j = 0;
	int nofcols = w / 25;
	
	int numofrows = h / 25;
	
	Map* m1 = new Pacman(numofrows, nofcols, w, h);
	m1->GridMaking();
	while (true) {
		
		m1->print();
		bool state = m1->Movement();
		if (state == false) {
			break;
		}
		m1->scoreCal();
		gotoxy(5, 25);
		
		cout << "The score is: " << m1->getscore()*10<<" ";
		for (int i = 0; i < m1->getLife(); i++) {
			drawEllipse(5 * ((30 + i + i) * 5) + 5, 21 * 25 + 5, 5 * ((30 + i + i) * 5) + 30, 21 * 25 + 30, 255, 255, 255, 255, 0, 0);
		}
		for (int i = m1->getLife(); i < 3; i++) {
			drawEllipse(5 * ((30 + i + i) * 5) + 5, 21 * 25 + 5, 5 * ((30 + i + i) * 5) + 30, 21 * 25 + 30, 0,0, 0, 0, 0, 0);
		}
		
	}
	cls();
	cout << "Your Final Score is: " << m1->getscore()*10 << endl;
	showConsoleCursor(true);
	delete m1;
	return 0;
}