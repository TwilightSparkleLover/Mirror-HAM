/*
---------------------------
HAMlib simple C++ example
---------------------------
*/

#include "mygba.h"

MULTIBOOT


class Player 
{
private:
	int health;
	int strength;
	

public:
	//constructor
	Player();
	//destructor
	~Player();
	//member functions
	void DisplayStats();

};

//implementation of member functions

Player::Player() 
{
	health=50;
	strength=100;
}
Player::~Player() 
{
	health=0;
	strength=0;
}
void Player::DisplayStats() 
{

	ham_DrawText(2,2,"HAMlib simple CPP Test");
	ham_DrawText(2,5,"health  : %d",this->health);
	ham_DrawText(2,6,"strength: %d",this->strength);
}




int main(void)
{
    // initialize HAMlib
    ham_Init();

    // init the Text display system on the bg of your choice
    ham_InitText(0);

	Player *myplayer = new Player;

	myplayer->DisplayStats();

    while(1)
    {
    }    
}


