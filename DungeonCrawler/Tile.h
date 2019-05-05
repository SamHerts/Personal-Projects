#pragma once

class Tile
{
public:
	Tile(int, int, char);
	~Tile();
	friend std::ostream& operator<<(std::ostream&,  Tile*);
	const char getChar() { return self; };
	void setChar(char temp) { self = temp; };
	void operator=(Tile*);
	

	int xpos;
	int ypos;
	


private:
	char self;
	
	
};
void swap(Tile*, Tile*);

Tile::Tile(int x, int y, char temp)
{
	xpos = x;
	ypos = y;
	setChar(temp);
}

Tile::~Tile()
{
}

std::ostream& operator<<(std::ostream& os,  Tile* Right) {
	os << Right->getChar();
	return os;
}
void Tile::operator=(Tile* Right) {
	xpos = Right->xpos;
	ypos = Right->ypos;
	setChar(Right->getChar());
}
void swap(Tile* Left, Tile* Right) {

	int tempx;
	int tempy;
	char tempc;

	tempx = Left->xpos;
	tempy = Left->ypos;
	tempc = Left->getChar();

	Left->xpos = Right->xpos;
	Left->ypos = Right->ypos;
	Left->setChar(Right->getChar());

	Right->xpos = tempx;
	Right->ypos = tempy;
	Right->setChar(tempc);

}
