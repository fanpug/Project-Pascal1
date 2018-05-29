#include<iostream>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<thread>

using namespace std;
bool dank = false;
void monikaprint();// this is for the monika easter egg
void boxhud(); // declaring the function for the main hud box
void gotoXY(int, int); // declaring the goto function which is set up below
void cloc(); // in-game clock
int currentparty = 1; // current party ammount of the player
void battlelog();// this is for the battle processing log
void movehud(); // this is for the hud for choosing battle actions
int movemenu(int member); // this is for the menu for choosing the move for a party member
void shopmenu();


// this is going to output a message in the upper part of the screen
void upper_message(string msg){
	boxhud();
	gotoXY(3,2); cout << msg;
}

// this is going to output a message on the main hud of the game
void main_message(string msg){
	system("CLS");
	boxhud();
	gotoXY(3,16); cout << msg;
}

void overhud();
//this is for the
void Talkmessage();
// this is the title screen on the game
void titlescreen();
// battle handling function
void Battleprocessing();
// pause and item handling
void pauseMenu();
//this is the function for the shop
void ShopMenu();




// creating the handlers for the goto function which allows us to move the
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

//actor class for all of the characters in the game
class actor{
	public:
	//these are the actor's stats
	string ActorName;
	int strength;
	int speed;
	float health;
	int vitality;
	int endurance;
	int dexterity;
	string GunName;
	string MeleeName;
	int money;
	bool alive;
	float Fullhealth;
	int bandages;
	int AidKit;
	int Defib;


	void ShowStats(){
		gotoXY(1,2);cout << ActorName << "'s stats are:"
		<< "\n Gun:       " << GunName
		<< "\n Melee:     " << MeleeName
		<< "\n Health:    " << health
		<< "\n Strength:  " << strength
		<< "\n Speed :    " << speed
		<< "\n Endurance: " << endurance
		<< "\n Dexterity: " << dexterity;

	}

	int Attack(int targetEnd, int targetSpeed){
		int chance, hit, ammount;
		chance = 5 + (speed - targetSpeed);
		hit = rand() %15;
		if ( hit <= 15){
			ammount =  10 + (2*strength) - targetEnd;
			return ammount;
		}
		else{
			return 0;
		}
	}

	int gun(int targetspeed, int targetEnd){
		int chance, hit, ammount;
		chance = 5 + dexterity - speed;
		hit = rand()%15;
		if ( hit <= 15){
			ammount =  20 + (strength) - targetEnd;
			return ammount;
		}
		else{
			return 0;
		}
	}
	int run(){
		int succ;
		succ = rand()%10;
		if (succ <5){
			return 0;
		}
		else{
			return 1;
		}
	}
};
actor party[3];

// this function sets up the party's stats
void partystat(){
	// no one's stats, just filling the empty space
	party[0].ActorName = "pascal";
	party[0].vitality = 0;
	party[0].Fullhealth = party[0].vitality * 10;
	party[0].strength = 0;
	party[0].speed = 0;
	party[0].endurance = 0;
	party[0].dexterity = 0;
	party[0].alive = true;
	party[0].GunName = "none";
	party[0].MeleeName = "none";
	// start of pascal's stats
	party[2].ActorName = "pascal";
	party[2].vitality = 5;
	party[2].Fullhealth = party[2].vitality * 10;
	party[2].health = party[2].Fullhealth;
	party[2].strength = 5;
	party[2].speed = 7;
	party[2].endurance = 5;
	party[2].dexterity = 6;
	party[2].alive = true;
	party[2].GunName = "agi";
	party[2].MeleeName = "bite";
	// end of pascal the dog's stats
}

//this is the class for the intems on the game, type reffers to the kind of effect iw will have
class Recover_item{
	public:
	string ItemName;
	int effectammount;
	int type;

	void use(int which){
		if(type == 1){
			if(party[which].health < party[which].Fullhealth ){
				if(effectammount + party[which].health <= party[which].Fullhealth){
				party[which].health = effectammount + party[which].health;
				}
				if(effectammount + party[which].health > party[which].health){
				party[which].health = party[which].Fullhealth;
				}
				else{
				gotoXY(3,1);cout << "this member is at full health";
				}
			}
		}
		if(type == 0){
			if(party[which].alive == false){
				party[which].health = party[which].Fullhealth;
			}
			else{
				gotoXY(3,11); cout << "this member is not dead";
			}
		}
	}
};
Recover_item items[3];

//this array is meant to represent the overworld in the game
int map[20][30]{
	{1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // row 0
	{3,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // row 1
	{0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,7,0,0,0,0,0,1}, // row 2
	{1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // row 3
	{1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // row 4
	{1,0,0,0,4,1,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1}, // row 5
	{1,0,6,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}, // row 6
	{1,0,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,8,0,0,0,0,0,0,0,0,0,0}, // row 7
	{1,1,1,1,8,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0}, // row 8		0000000
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,0,0,0,0,0}, // row 9	   000000000
	{1,1,0,0,0,0,0,0,1,1,1,8,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0}, // row 10   000020000
	{1,1,1,8,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}, // row 11   000000000
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}, // row 12	0000000
	{1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0}, // row 13
	{1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,1,0,1,1,0,0,1,1,1,1,1,1,3,0,0}, // row 14
	{1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,3,0,1,1,1,1,1,1,1,0,0,0,0,0,0}, // row 15
	{1,1,1,1,1,1,1,1,1,0,0,8,1,1,0,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0}, // row 16
	{1,0,0,1,1,1,1,1,8,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0}, // row 17
	{1,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3}, // row 18
	{2,1,1,1,1,1,1,1,1,1,1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // row 19
	};

// this is going to transfor the in variable for the overworld array and turn it into a character
char getCharAt(int x, int y) {
	if(x < 0 || y < 0)
		return 254;
	if(x >= 20 || y >= 30)
		return 254;
	if(map[x][y] == 1)
	return ' ';
	if(map[x][y] == 0)
	return 254;
	if(map[x][y] == 2)
	return 'P';
	if(map[x][y] == 3)
	return 'I';
	if(map[x][y] == 4)
	return 'M';
	if(map[x][y] == 5)
	return 'S';
	if(map[x][y] == 7)
	return 'X';
	if(map[x][y] == 8)
	return 'T';
	if(map[x][y] == 6)
	return '$';
	return 254;
}

// this is the overworld, from here movement, encounter rates, and function calling are called
void overworld(){
	thread InGameTime(&cloc);
    InGameTime.detach();
	int positionx, positiony, Broll;
	bool Onthemove = true;
	system("CLS");
	/*
	the numerical codes for the array are:
	wall: 			0
	nothing: 		1
	player: 		2
	item: 			3
	party memeber:  4
	shoppe: 		6
	finish state:   7
	speaker:        8
	*/
	while(Onthemove){

		overhud();
	//this finds the position of the player
		for(int n = 0; n < 20; n++){
			for (int h = 0; h  < 30; h++){
				if(map[n][h] == 2){
	 				positionx = n;
					positiony = h;
				}
			}
		}

		// this is going to print the map
		int radius = 3;
		int count = 0;
		for(int k = -radius; k <= radius; k++){
			for(int j = -radius; j <= radius; j++) {
				if((k == -radius || k  == radius) && (j == -radius || j == radius)) {
					gotoXY(9, 3 + count);
					continue;
				}

				cout << getCharAt(positionx + k, positiony + j);
			}
			cout << endl;
			count++;
			gotoXY(8,3 + count);
		}
        system("pause>nul");
		if(Broll == 5){
			Battleprocessing();
		}


		if(GetAsyncKeyState(VK_UP) && getCharAt(positionx-1,positiony) != (char) 254){
			if(getCharAt(positionx-1,positiony) == 'T'){
				Talkmessage();
				continue;
			}
			if(getCharAt(positionx-1,positiony) == 'M'){
				currentparty++;
				map[positionx-1][positiony] = 2;
				map[positionx][positiony] = 1;
				continue;
			}
			if(getCharAt(positionx-1,positiony) == '$'){
				ShopMenu();
				continue;
			}
			if(getCharAt(positionx,positiony+1) == 'I'){
				party[1].money = party[1].money + 100;
				map[positionx-1][positiony] = 2;
				map[positionx][positiony] = 1;
				continue;
			}
			else{
				map[positionx-1][positiony] = 2;
				map[positionx][positiony] = 1;
				Broll = rand() %20;
			}
		}
		else if(GetAsyncKeyState(VK_DOWN) && getCharAt(positionx+1,positiony) != (char)254){
			if(getCharAt(positionx+1,positiony) == 'T'){
				Talkmessage();
				continue;
			}
			if(getCharAt(positionx+1,positiony) == 'M'){
				currentparty++;
				map[positionx+1][positiony] = 2;
				map[positionx][positiony] = 1;
				continue;
			}
			if(getCharAt(positionx,positiony+1) == 'I'){
				party[1].money = party[1].money + 100;
				map[positionx+1][positiony] = 2;
				map[positionx][positiony] = 1;
				continue;
			}
			else{
				map[positionx+1][positiony] = 2;
				map[positionx][positiony] = 1;
				Broll = rand() %20;
			}
		}
		else if(GetAsyncKeyState(VK_LEFT) && getCharAt(positionx,positiony-1) != (char)254){
			if(getCharAt(positionx, positiony-1) == 'T'){
				Talkmessage();
				continue;
			}
			if(getCharAt(positionx,positiony-1) == 'M'){
				currentparty++;
				map[positionx][positiony-1] = 2;
				map[positionx][positiony] = 1;
				continue;
			}
			if(getCharAt(positionx,positiony-1) == 'I'){
				party[1].money = party[1].money + 100;
				map[positionx][positiony-1] = 2;
				map[positionx][positiony] = 1;
				continue;
			}
			else{
				map[positionx][positiony-1] = 2;
				map[positionx][positiony] = 1;
				Broll = rand() %20;
			}
		}
		else if(GetAsyncKeyState(VK_RIGHT) && getCharAt(positionx,positiony+1) != (char)254){
			if(getCharAt(positionx,positiony+1) == 'T'){
				Talkmessage();
				continue;
			}
			if(getCharAt(positionx,positiony+1) == 'M'){
				currentparty++;
				map[positionx][positiony+1] = 2;
				map[positionx][positiony] = 1;
				continue;
			}
			if(getCharAt(positionx,positiony+1) == 'I'){
				party[1].money = party[1].money + 100;
				map[positionx][positiony+1] = 2;
				map[positionx][positiony] = 1;
				continue;
			}
			if(getCharAt(positionx,positiony+1) == 'X'){
                try{throw 0;}
                catch(int x){
                    main_message("you have finally escaped... with pascal.")
                    exit(0);
                }
			}
			else{
				map[positionx][positiony+1] = 2;
				map[positionx][positiony] = 1;
				Broll = rand() %20;
			}
		}
		if(GetAsyncKeyState(0x50)){
            pauseMenu();
		}
	}
}


// this is setting all of the properties of the items in the game
void setitems(){
	//this is the bandage object
	items[0].ItemName = "bandage";
	items[0].effectammount = 50;
	items[0].type = 1;
	// this is the first aid kit
	items[1].ItemName = "F.Aid:Kit";
	items[1].effectammount = 100;
	items[1].type = 1;
	// this is for the defib unit
	items[2].ItemName = "defibUnit";
	items[2].effectammount = 200;
	items[2].type = 0;
}



// creating all of the enemy's objects
actor EnemyPool[4];
actor specialenemy;

// this is the hud in the overworld
void overhud(){
	partystat();
	boxhud();
	if(currentparty == 1){
		gotoXY(3, 16);
		cout << party[1].ActorName << "  HP: " << party[1].health << "/" << party[1].Fullhealth;
	}
	if(currentparty == 2){
		gotoXY(3, 16);
		cout << party[1].ActorName << "  HP: " << party[1].health << "/" << party[1].Fullhealth;
		gotoXY(3, 17);
		cout << party[2].ActorName << "  HP: " << party[2].health << "/" << party[2].Fullhealth;
	}
}

// this is the function that handles the initial setup of the character's stats
void chose_stats(){
	int stat = 0, run, y = 3, points = 20, tempskill[5] = {1,1,1,1,1}, x = 3;
	bool choosing = true, noleft = false, secondrun = true;
	while (choosing){
		main_message("");
		gotoXY(3,y); cout << "->";
		upper_message("Please enter character's stats:");
		gotoXY(3,16); cout << "Points left: " << points;
		gotoXY(5,3); cout << "Strength:  " << std::string(tempskill[0], (char)254); // messages end at x = 14
		gotoXY(5,4); cout << "Speed:     " << std::string(tempskill[1], (char)254);  //character for the square (char)254
		gotoXY(5,5); cout << "Vitality:  " << std::string(tempskill[2], (char)254);
		gotoXY(5,6); cout << "Endurance: " << std::string(tempskill[3], (char)254);
		gotoXY(5,7); cout << "Dexterity: " << std::string(tempskill[4], (char)254);
		gotoXY(5,8); cout << "Finish";
		gotoXY(5,9); cout << "Current stat: " << tempskill[stat]  << "  stat: " << stat;
		if(noleft == true){
			gotoXY(3,17); cout << "You still have " << points << " points left";
		}
		system("pause>nul");
		gotoXY(3,16); cout << "Points left: " << points;
		if(GetAsyncKeyState(VK_DOWN)){
			if(y < 8){
			y++;
			stat = y-3;
			gotoXY(3,y); cout << "->";
		}
			continue;
		}
		if(GetAsyncKeyState(VK_UP)){
			if(y > 3){
				y--;
				stat = y-3;
				gotoXY(3,y); cout << "->";
			}
			continue;
		}
		if(GetAsyncKeyState(VK_RIGHT)){
			if(points > 0 && y < 8 && tempskill[stat] < 11){
			points--;
			tempskill[stat]++;
			}
			continue;
		}
		if(GetAsyncKeyState(VK_LEFT)){
			if(points < 21 && y < 8 && tempskill[stat] > 1){
			points++;
			tempskill[stat]--;
			}
			continue;
		}
		if(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(0x5A) ){
			if(y != 8){
				y = 8;
				gotoXY(3,y); cout << "->";
				continue;
			}
			if(points > 0){
				noleft = true;
				continue;
			}
			if(points == 0){
			//	secondrun = true;
				if(secondrun == true){
					system("pause>nul");
					main_message("Are these stats ok?");
					while(secondrun){

						gotoXY(6,17); cout << "Yes";
						gotoXY(17,17); cout << "No";
						gotoXY(x,17); cout << "->";
						system("pause>nul");
						if(GetAsyncKeyState(VK_RIGHT)){
							if(x != 15){
								gotoXY(x,17); cout <<"  ";
								x = 15;
								gotoXY(x,17); cout << "->";
								continue;
							}
						}
						if(GetAsyncKeyState(VK_LEFT)){
							if(x != 3){
								gotoXY(x,17); cout <<"  ";
								x = 3;
								gotoXY(x,17); cout << "->";
								continue;
							}
						}
						if(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(0x5A)){
							if(x == 3){
								party[1].GunName = "Handgun";
								party[1].MeleeName = "Knife";
								party[1].dexterity = tempskill[4];
								party[1].endurance = tempskill[3];
								party[1].vitality = tempskill[2];
								party[1].speed = tempskill[1];
								party[1].strength = tempskill[1];
								party[1].health = party[1].vitality * 20;
								party[1].alive = true;
								party[1].money = 100;
								secondrun = false;
								choosing = false;
								party[1].Fullhealth = party[1].vitality * 20;
								party[1].bandages = 2;
								party[1].AidKit = 1;
								party[1].Defib = 1;
							}
							if(x == 15){
								chose_stats();
							}
						}

					}
				}
			}
		}
	}
}

// this will be the intro cutscene
void intro(){
	main_message("I haven't seen the sun in weeks.");
	system("pause>nul");
	main_message("I've looked outside but no sun is out.");
	system("pause>nul");
	main_message("Sometimes i see blinking lights on the outside.");
	system("pause>nul");
	main_message("so i thought...");
	system("pause>nul");
	main_message("Maybe leaving would be better.");
	system("pause>nul");
	main_message("Right now my priority is to find Pascal.");
	system("pause>nul");
	main_message("Everything else is secondary...");
	system("pause>nul");
}
// this function is for setting the main character name
void playerstat(){
	main_message("Welcome. Press Enter to continue...");
	system("pause>nul");
	main_message("Enter your character's name:\n");
	gotoXY(3,17); cin >> party[1].ActorName;
	if(party[1].ActorName == "monika"){
		monikaprint();
		system("pause<null");
	}
	getchar();
	chose_stats();
}


// this is the main game loop
void gameloop(){
	system("CLS");
	bool fail_state = false;
	do {
		playerstat();
		intro();
		overworld();
	}
	while(fail_state = false);



}

//main menu function
int menu(){
	int menu_option = 0, run, x = 10;
	bool running = true;
	titlescreen();

	while (running){
		gotoXY(3,10);  cout << "1) begin";
		gotoXY(3,11);  cout << "2) exit program";
		gotoXY(1,x); cout << "->";
		system("pause>nul"); // the >nul bit causes it the print no message
		if(GetAsyncKeyState(VK_DOWN)){ //down button pressed
			if(x = 11){
				x = 10;
				menu_option = 0;
			}
			gotoXY(1,x); cout << "  ";
			x++;
			gotoXY(1,x); cout << "->";
			menu_option++;
			continue;
		}

		if(GetAsyncKeyState(VK_UP)){ //up button pressed
			if(x = 10){
				x = 11;
				gotoXY(1,x); cout << "->";
				menu_option = 1;
			}
			gotoXY(1,x); cout << "  ";
			x--;
			gotoXY(1,x); cout << "->";
			menu_option--;
			continue;
		}

		if(GetAsyncKeyState(VK_RETURN)){
			switch(menu_option){
				case 0:{
					return 1;
					break;
				}

				case 1:{
					return 2;
					break;
				}
			}
		}

	}
}

// this function is going to set up the stats of the enemy
void set_stats(){
	//start of bob's stats
	EnemyPool[0].ActorName = "bob";
	EnemyPool[0].vitality = 6;
	EnemyPool[0].Fullhealth = EnemyPool[0].vitality * 10;
	EnemyPool[0].strength = 5;
	EnemyPool[0].speed = 6;                //He is the generic bad guy
	EnemyPool[0].endurance = 8;
	EnemyPool[0].dexterity = 6;
	EnemyPool[0].alive = true;
	EnemyPool[0].GunName = "bob gun";
	EnemyPool[0].MeleeName = "fists";
	EnemyPool[0].money = 30;
	//end of bob's stats
	    //Start of Pepe's stats
	EnemyPool[1].ActorName = "Pepe the Frog";
	EnemyPool[1].vitality = 7;
	EnemyPool[1].Fullhealth = EnemyPool[1].vitality * 10;
	EnemyPool[1].strength = 10;
	EnemyPool[1].speed = 1;
	EnemyPool[1].endurance = 4;            //He is the slow heavy hitter with crippling depression
	EnemyPool[1].dexterity = 2;
	EnemyPool[1].alive = true;
	EnemyPool[1].GunName = "SadPepe";
	EnemyPool[1].MeleeName = "AngryPepe";
	EnemyPool[1].money = 80;
	//end of pepe's stats
	    //start of Doge's stats
	EnemyPool[2].ActorName = "Doge";
	EnemyPool[2].vitality = 6;
	EnemyPool[2].Fullhealth = EnemyPool[2].vitality * 10;
	EnemyPool[2].strength = 4;
	EnemyPool[2].speed = 10;
	EnemyPool[2].endurance = 3;             //A speedy boi
	EnemyPool[2].dexterity = 3;
	EnemyPool[2].alive = true;
	EnemyPool[2].GunName = "DogeLook";
	EnemyPool[2].MeleeName = "Bite";
	EnemyPool[2].money = 50;
	//end of Doge's stats
	    //start of Wendys' stats
	EnemyPool[3].ActorName = "Smug Anime Girl";
	EnemyPool[3].vitality = 9;
	EnemyPool[3].Fullhealth = EnemyPool[3].vitality * 10;
	EnemyPool[3].strength = 5;
	EnemyPool[3].speed = 6;
	EnemyPool[3].endurance = 7;             //She is a smug girl
	EnemyPool[3].dexterity = 6;
	EnemyPool[3].alive = true;
	EnemyPool[3].GunName = "Smug Smile";
	EnemyPool[3].MeleeName = "Smug Slap";
	EnemyPool[3].money = 50;
	//end of Wendys' stats
}


// this is how all of the game's functions are called
int main(){
	int option;
	set_stats();
	setitems();
	option = menu();
	switch (option){
		case 1:{
			cout << "\nSelected option 1";
			gameloop();
			break;
		}

		case 2:{
			cout << "\nSelected option 2";
			std::_Exit;
			break;
		}

	}
	return 0;
}

// this function is to be called when the player interacts with an NPC
void Talkmessage(){
	int which;
	if(dank == true){
		main_message("this is the dark hour");
	}
	which = rand() %10;
	if(dank == false){
		switch(which){
			case 0:{
				main_message("thou art god");
				break;
			}
			case 1:{
				main_message("I am looking for my sister, lisa");
				break;
			}
			case 2:{
				main_message("the sun just vanished a while ago");
				break;
			}
			case 3:{
				main_message("you have a heart of gold, don't let them take it");
				break;
			}
			case 4:{
				main_message("i like big butts, they never lie");
				break;
			}
			case 5:{
				main_message("is pascal the dog here?");
				break;
			}
			case 6:{
				main_message("one more god rejected");
				break;
			}
			case 7:{
				main_message(" i miss the sunlight...");
				break;
			}
			case 8:{
				main_message("i am devilman!!");
				break;
			}
			case 9:{
				main_message("despacito");
				break;
			}
			case 10:{
				main_message("i wish i could dissapear");
				break;
			}
		}
	}
	system("pause>nul");
	system("CLS");
}

// function for gotoXY function, allows us to set the cursor position
void gotoXY(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
}

//creating a function that outputs a box for dialogue and menus
void boxhud(){
	short int k = 16;
	//this box is currently 40*10 characters in dimention
	gotoXY(1,15);cout << "##################################################";
	while(k <= 21){
		gotoXY(1,k);cout << "#";
		k++;
	};
	k = 16;
	while(k <= 21){
		gotoXY(50,k);cout << "#";
		k++;
	};
	gotoXY(1,22);cout << "##################################################";
}

// just the title screen
void titlescreen(){
	 cout << "               _____   ______  _____  _____ _______ _______ _______" << endl;
	 cout << "              |_____] |_____/ |     |   |   |______ |          |   " << endl;
	 cout << "              |       |    \\_ |_____| __|   |______ |_____     |   " << endl;
	 cout << "\n";
	 cout << "                  _____  _______ _______ _______ _______       " << endl;
	 cout << "                 |_____] |_____| |______ |       |_____| |     " << endl;
	 cout << "                 |       |     | ______| |_____  |     | |_____" << endl;
	 cout << "\n" << endl;
}
// this is the function which handles the concurrent in-game clock
void cloc(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    short int ig_hour = ltm -> tm_hour;
    short int ig_min = 00;

    this_thread::sleep_for(std::chrono::seconds(4));
    while(true){
    if(ig_min == 60){
        ig_min = 00;
        ig_hour++;
        dank = false;
    }
    if(ig_hour == 24){
        ig_hour = 00; dank = true;
    }else{
        dank = false;
    }

    gotoXY(46,1);cout << ig_hour << ":";
    gotoXY(49,1);cout << ig_min;
    this_thread::sleep_for(std::chrono::seconds(5));
    ig_min += 5;
    gotoXY(46,1); cout << "     ";
    }
}

// this function handles the menu for the player's moves
int Movemenu(int member){
	bool choosing = true;
	int y = 6;
	while(choosing){
		movehud();
		gotoXY(27,5);cout << party[member].ActorName << "'s' move:";
		gotoXY(27,y);cout << "->";
		gotoXY(30,6);cout << "Atack";
		gotoXY(30,7);cout << "Gun";
		gotoXY(30,8);cout << "Item";
		gotoXY(30,9);cout << "Run";
		system("pause>nul");
       if(GetAsyncKeyState(VK_UP) && y >6){
	       	gotoXY(3,y); cout << "  ";
	        y--;
	        continue;
		}
		if(GetAsyncKeyState(VK_DOWN) && y <9){
			gotoXY(3,y); cout << "  ";
            y++;
            continue;
		}
		else if(GetAsyncKeyState(VK_RETURN)){
			return y-5;
		}
	}
}
// this is the function that handles the battles
void Battleprocessing(){
	int turn = 0, choice, which, runatt;
	bool beaten = false;
	int EAttack, who, damage, y = 6;
	which = rand()%5;
	float temporaryEHealth = EnemyPool[which].Fullhealth;
	system("CLS");
	gotoXY(16, 8); cout << "YOU ARE UNDER ATTACK!";
	system("pause>nul");
	gotoXY(14, 8); cout << "THE ENEMY IS ATTACKING...";
	system("pause>nul");
	system("CLS");
	turn = 0;

	while(beaten == false){

		gotoXY(27, 11); cout << EnemyPool[which].ActorName << "  " << temporaryEHealth << "/" << EnemyPool[which].Fullhealth;
        movehud();
        boxhud();
        overhud();
        battlelog();
        system("pause>nul");
        system("CLS");

        if(turn == 0){
            who = rand()%2;
            EAttack = rand()%2+1;
            switch(EAttack){
                case 1:{
                	damage = EnemyPool[which].Attack(party[who].endurance, party[who].speed);
                	party[who].health = party[who].health - damage;
                	gotoXY(28,12); cout << "The enemy is attacking";
                	movehud();
                    boxhud();
                    overhud();
                    battlelog();
                	system("pause>nul");
                	gotoXY(28,12); cout << "                      ";
                	gotoXY(28,12); cout << EnemyPool[which].ActorName << " swung " << EnemyPool[which].MeleeName;
                	system("pause>nul");
                	gotoXY(28,13); cout << damage << " damage made";
                	system("pause>nul");
                	turn++;
                	try{
                	if(currentparty == 1 && party[1].health < 0){
                        throw 0;
                	}
                	if(party[1].health < 0 && party[2].health < 0){
                        throw 0;
                	}
                	}
                	catch(int x){
                        if(x == 0){
                            main_message("...");
                            system("pause>nul");
                            main_message("You have died in battle...");
                            system("pause>nul");
                            exit(0);
                        }
                    }

					break;
				}
				case 2:{
	            damage = EnemyPool[which].gun(party[who].speed,party[who].endurance);
	            party[who].health = party[who].health - damage;
	            gotoXY(28,12); cout << "The enemy is attacking";
	            movehud();
                boxhud();
                overhud();
                battlelog();
	            system("pause>nul");
	            gotoXY(28,12); cout << "                      ";
	            gotoXY(28,12); cout << EnemyPool[which].ActorName << " shot " << EnemyPool[which].GunName;
	            system("pause>nul");
	            gotoXY(28,13); cout << damage << " damage made";
	            system("pause>nul");
	            turn++;
	            if(currentparty == 1 && party[1].health < 0){
                        throw 2;
                	}
	            if(party[1].health < 0 && party[2].health < 0){
                    throw 2;
                }
				break;
				}
			}
		}
        if(turn == 1){
            while(turn == 1){
                system("CLS");
                movehud();
                boxhud();
                overhud();
                battlelog();
                gotoXY(28, y); cout << "->";
		        gotoXY(27,5);cout << party[1].ActorName << "'s move:";
		        gotoXY(30,6);cout << "Atack";
		        gotoXY(30,7);cout << "Gun";
		        gotoXY(30,8);cout << "Run";
		        system("pause>nul");
		        if(GetAsyncKeyState(VK_DOWN)){
		            if(y == 8){
		                continue;
		            }
		            if(y < 8){
		                y++;
		              //  gotoXY(28, y); cout << "->";
		                continue;
		            }
		        }
		        else if(GetAsyncKeyState(VK_UP)){
		            if(y == 6){
		                continue;
		            }
		            if(y > 6){
		                y--;
		               // gotoXY(28, y); cout << "->";
		                continue;
		            }
		        }
		        if(GetAsyncKeyState(VK_RETURN)){
		            if(y == 6){
		                damage = party[1].Attack(EnemyPool[which].endurance, EnemyPool[which].speed);
		                temporaryEHealth = temporaryEHealth - damage;
		                if(currentparty == 2){
		                    turn = 2;
						}
						if(currentparty == 1){
		               		turn = 0;
						}
		      	  }
		      	  if(y == 7){
		                damage = party[1].gun(EnemyPool[which].endurance, EnemyPool[which].speed);
		                temporaryEHealth = temporaryEHealth - damage;
		                if(currentparty == 2){
		                    turn = 2;
						}
						if(currentparty == 1){
		               		turn = 0;
						}
		      	  }
		      	  if(y == 8){
		            runatt = party[1].run();
		            if(runatt == 1){
		            	main_message("You ran away like a coward");
		            	overworld();
					}
					else{
						if(currentparty == 2){
		                    turn = 2;
						}
						if(currentparty == 1){
		               		turn = 0;
						}
					}
		      	  }

	  			}
	  		}
		}
		if(turn == 2){
            while(turn == 2){
                system("CLS");
                movehud();
                boxhud();
                overhud();
                battlelog();
                gotoXY(28, y); cout << "->";
		        gotoXY(27,5);cout << party[2].ActorName << "'s move:";
		        gotoXY(30,6);cout << "Atack";
		        gotoXY(30,7);cout << "Gun";
		        gotoXY(30,8);cout << "Run";
		        system("pause>nul");
		        if(GetAsyncKeyState(VK_DOWN)){
		            if(y == 8){
		                continue;
		            }
		            if(y < 8){
		                y++;
		              //  gotoXY(28, y); cout << "->";
		                continue;
		            }
		        }
		        else if(GetAsyncKeyState(VK_UP)){
		            if(y == 6){
		                continue;
		            }
		            if(y > 6){
		                y--;
		               // gotoXY(28, y); cout << "->";
		                continue;
		            }
		        }
		        if(GetAsyncKeyState(VK_RETURN)){
		            if(y == 6){
		                damage = party[2].Attack(EnemyPool[which].endurance, EnemyPool[which].speed);
		                temporaryEHealth = temporaryEHealth - damage;
		               		turn = 0;
		      	  }
		      	  if(y == 7){
		                damage = party[2].gun(EnemyPool[which].speed,EnemyPool[which].endurance);
		                temporaryEHealth = temporaryEHealth - damage;
		               		turn = 0;
		      	  }
		      	  if(y == 8){
		      	  	runatt = party[2].run();
		            if(runatt == 1){
		            	main_message("you ran away like a coward");
		            	system("pause>nul");
		            	overworld();
					}
					else{
						 turn = 0;
                    }
                }
	  			}
	  		}
		}
		if(temporaryEHealth < 0){
			beaten = true;
			turn = 5;
			system("CLS");
            gotoXY(16, 8); cout << "YOU HAVE WON THE BATTLE!";
            system("pause>nul");
            system("CLS");
		}
	}


}
// this is for creating the secondary hud we can use the following coordinates:
//   27 < x < 49   11 < y < 15
void battlelog(){
	short int k = 11;
	gotoXY(26,10); cout <<"#########################";
	while(k <= 15){
		gotoXY(26,k); cout << "#";
		k++;
	}
	k = 11;
	while(k <= 15){
		gotoXY(50,k); cout << "#";
		k++;
	}
	gotoXY(1,1);
}

// the coordinates for this hud are 27 < x < 50 and 4 < y < 10
// during battle processing, ere we show the box for the move menu
void movehud(){
	short int k = 5;
	gotoXY(26, 4); cout << "#########################";
	while(k <= 9){
		gotoXY(26, k); cout << "#";
		k++;
	}
	k = 5;
	while(k <= 9){
		gotoXY(50, k); cout << "#";
		k++;
	}
}
// this is the menu for pause
void pauseMenu(){
    int y = 5;
    short int k = 12, j = 12;
    bool choosing = true, mini_choosing = true;
    system("CLS");
    gotoXY(3, 5); cout << "->";
    try{
    while(choosing == true){

        gotoXY(23, 2); cout << "PAUSE";
        gotoXY(5, 5); cout << "Continue";
        gotoXY(5, 6); cout << "Exit";
        gotoXY(5, 7); cout << "Bandages: " << party[1].bandages;
        gotoXY(5, 8); cout << "F.AidKit " << party[1].AidKit;
		gotoXY(5, 9); cout << "Defib unit: " << party[1].Defib;
        system("pause>nul");
        system("CLS");
        if(GetAsyncKeyState(VK_DOWN)){
            if(y == 9){
                gotoXY(3, 9); cout << "->";
            }
            if(y < 9){
                y++;
                gotoXY(3, y); cout << "->";
			}
			continue;
		}
		if(GetAsyncKeyState(VK_UP)){
		    if(y == 5){
                gotoXY(3, 5); cout << "->";
            }
            if(y > 5){
                y--;
                gotoXY(3, y); cout << "->";
			}
			continue;
		}
		if(GetAsyncKeyState(VK_RETURN)){
			switch(y){
				case 5:
                    choosing = false;
                break;

                case 6:
                    throw 1;
                break;

                case 7:
                    if(party[1].bandages > 0){
                    gotoXY(3, 12); cout << "->";
                    while(mini_choosing == true){
                        gotoXY(5, 11); cout << "Which member do you want to heal?";

                        for(short int l = 1; l <= currentparty; l++){
                            gotoXY(5, j); cout << party[l].ActorName;
                            j++;
                        }
                        j = 12;
                        system("pause>nul");
                        system("CLS");
                        if(GetAsyncKeyState(VK_DOWN)){
                            if(k == 13){
                                gotoXY(3, 13); cout << "->";
                            }
                            if(k < 13){
                                k++;
                                gotoXY(3, k); cout << "->";
                            }
                            continue;
                        }
                        if(GetAsyncKeyState(VK_UP)){
                            if(k == 12){
                                gotoXY(3, 12); cout << "->";
                            }
                            if(k > 12){
                                k--;
                                gotoXY(3, k); cout << "->";
                            }
                            continue;
                        }
                        if(GetAsyncKeyState(VK_RETURN)){
                            if(k == 12){
                                items[1].use(1);
                                mini_choosing = false;
                                party[1].bandages--;
                            }
                            if(k==13){
                                items[1].use(2);
                                mini_choosing = false;
                                party[1].bandages--;
                            }
                        }

                    }
                }
                    mini_choosing = true;

                break;

                case 8:
                    gotoXY(3, 12); cout << "->";
                    if(party[1].AidKit > 0){
                    while(mini_choosing == true){
                        gotoXY(5, 11); cout << "Which member do you want to heal?";

                        for(short int l = 1; l <= currentparty; l++){
                            gotoXY(5, j); cout << party[l].ActorName;
                            j++;
                        }
                        j = 12;
                        system("pause>nul");
                        system("CLS");
                        if(GetAsyncKeyState(VK_DOWN)){
                            if(k == 13){
                                gotoXY(3, 13); cout << "->";
                            }
                            if(k < 13){
                                k++;
                                gotoXY(3, k); cout << "->";
                            }
                            continue;
                        }
                        if(GetAsyncKeyState(VK_UP)){
                            if(k == 12){
                                gotoXY(3, 12); cout << "->";
                            }
                            if(k > 12){
                                k--;
                                gotoXY(3, k); cout << "->";
                            }
                            continue;
                        }
                        if(GetAsyncKeyState(VK_RETURN)){
                            if(k == 12){
                                items[1].use(1);
                                mini_choosing = false;
                                party[1].AidKit--;
                            }
                            if(k==13){
                                items[1].use(2);
                                mini_choosing = false;
                                party[1].AidKit--;
                            }
                        }

                    }
                    }
                    mini_choosing = true;

                break;

                case 9:
                    gotoXY(3, 12); cout << "->";
                    if(party[1].Defib > 0){
                    while(mini_choosing == true){
                        gotoXY(5, 11); cout << "Which member do you want to heal?";

                        for(short int l = 1; l <= currentparty; l++){
                            gotoXY(5, j); cout << party[l].ActorName;
                            j++;
                        }
                        j = 12;
                        system("pause>nul");
                        system("CLS");
                        if(GetAsyncKeyState(VK_DOWN)){
                            if(k == 13){
                                gotoXY(3, 13); cout << "->";
                            }
                            if(k < 13){
                                k++;
                                gotoXY(3, k); cout << "->";
                            }
                            continue;
                        }
                        if(GetAsyncKeyState(VK_UP)){
                            if(k == 12){
                                gotoXY(3, 12); cout << "->";
                            }
                            if(k > 12){
                                k--;
                                gotoXY(3, k); cout << "->";
                            }
                            continue;
                        }
                        if(GetAsyncKeyState(VK_RETURN)){
                            if(k == 12){
                                items[2].use(1);
                                mini_choosing = false;
                                party[1].Defib--;
                            }
                            if(k==13){
                                items[2].use(2);
                                mini_choosing = false;
                                party[1].Defib--;
                            }
                        }

                    }
                    }
                    mini_choosing = true;

                break;

                default:
                    choosing = false;
            }
        }
    }
    }
    catch(int what){
        cout << "You have chosen to exit the game";
        exit(0);
    }

}
// this is going to print the image if the player is named monika
void monikaprint(){
    printf("              `/::::--.                           \n");
    printf("              /-------:::-`                       \n");
    printf("              +--::::////:/:`    `............... \n");
    printf("           `.-////////++ooooo/-:-.`             / \n");
    printf("        `-////////////////+ooooo+-`             : \n");
    printf("      .:////////////////////++ooooo:..`        .- \n");
    printf("    ./////////////////////////+oooooo/.        :  \n");
    printf("  `:///////////////////////////+oooooo/       .-  \n");
    printf(" `://///////////////////////////+oooooo/     `+-  \n");
    printf(" :///////////////////////////////ooooooo-   `+oo. \n");
    printf(".////////////////////////////////+ooooooo  -oooo+ \n");
    printf("://///////:///////////////////////ooooooo:::/+ooo.\n");
    printf("/////////../////////-:////////////+oooooo/----/+o/\n");
    printf("////////:``.////////:`-////////////oooooo/-----:o+\n");
    printf(":///////-``.-:///////:.-.://///////+ooooo-----/ooo\n");
    printf("-///////.`````.:.-::///-```.-://///+oooo/----/oooo\n");
    printf("`/////////+++:.````````./ooo+/:////+oooo+---+oooo/\n");
    printf(" -///////yy+oy.````````.-y+:sy:////+oo+oo+:+ooooo.\n");
    printf(" `://///:/+-:+```````````//:+:-////oo--ooooooooo/ \n");
    printf("  ``-//o/`.-..```````````....`://///``+ooooooooo` \n");
    printf("     `.o+`````````````````````////-  /ooooooooo-  \n");
    printf("      `oo/.``````.``.````````.//// `/ooooooooo:   \n");
    printf("      /ooo+     ``..````    `////.`+ooooooooo:    \n");
    printf("     /oooo/     `.-...`    .////.-oooooooooo:     \n");
    printf("    -oooo/`   ./+osso+o/` .///:`-ooooooooo+.      \n");
    printf("    :ooo/    :oo/+o++//oo.//// `oooooooooo`     ` \n");
    printf("    `:.:+`   :/.:/o+/:.:/---::`-oooooooooo      /`\n");
    printf("             ```:/+//.```    ` /oooooooooo/.```:o \n");
    printf("             `/://s///++`      .ooooooooooooo+oo- \n");
    printf("            /yhyoyysossyo.      `:o/:+oooooooo/.  \n");
    printf("            .osoysssysso:          .   `....`     \n");
    printf("             ``-/::-/o+++                         \n");
    printf("               shy+  smNm                         \n");
    printf("               :hh+  `dNN:                        \n");
    printf("                yh+   -mNo                        \n");
    printf("                /h+    +Ny       ```````````````  \n");
    printf("                 s:     /:                        \n");
}

// this is the shop function
void ShopMenu(){
    short int y = 7, cost[3] = {50,100,150};
    bool choosing = true;
    system("CLS");
    gotoXY(3, 16); cout << "Shop Keeper:";
    gotoXY(3, 18); cout << "Welcome. What can I do for you?";
    gotoXY(3, 7); cout << "->";
    while(choosing == true){
        gotoXY(3, 16); cout << "Shop Keeper:";
        gotoXY(3, 18); cout << "...";
        gotoXY(23, 2); cout << "SHOP";
        gotoXY(3, 4); cout << "Use the Up and Down Arrows, and press Enter";
        gotoXY(3, 5); cout << "to buy the selected item.";
        gotoXY(38,14); cout << "You have: " << party[1].money << char(36);
        gotoXY(5, 12); cout << "Leave";
        gotoXY(5, 7); cout << "Bandages ";
        gotoXY(5, 8); cout << "F.AidKit ";
		gotoXY(5, 9); cout << "Defib unit ";
		gotoXY(3, y); cout << "->";
		boxhud();
        system("pause>nul");
        system("CLS");
        if(GetAsyncKeyState(VK_DOWN)){
            if(y == 12){
                gotoXY(3, 12); cout << "->";
            }

            if(y < 12){
                y++;
                if(y == 10){
                    y = 12;
                }

                gotoXY(3, y); cout << "->";
			}
			continue;
		}
		if(GetAsyncKeyState(VK_UP)){
		    if(y == 7){
                gotoXY(3, 7); cout << "->";
            }
            if(y > 7){
                y--;
                if(y == 11){
                    y = 9;
                }

                gotoXY(3, y); cout << "->";
			}

			continue;
		}

        if(GetAsyncKeyState(VK_RETURN)){
            switch(y){
                case 7:
                    if(party[1].money < cost[0]){
                        gotoXY(3, 18); cout << "You don't have enough money for that.";
                    }
                    else{
                        party[1].money  = party[1].money - cost[0];
                        gotoXY(3, 18); cout << "Thanks for your purchase!";
                        party[1].bandages++;
                    }
                break;

                case 8:
                    if(party[1].money < cost[1]){
                        gotoXY(3, 18); cout << "You don't have enough money for that.";
                    }
                    else{
                        party[1].money  = party[1].money - cost[1];
                        gotoXY(3, 18); cout << "Thanks for your purchase!";
                        party[1].AidKit++;
                    }
                break;
                case 9:
                    if(party[1].money < cost[2]){
                        gotoXY(3, 18); cout << "You don't have enough money for that.";
                    }
                    else{
                        party[1].money  = party[1].money - cost[2];
                        gotoXY(3, 18); cout << "Thanks for your purchase!";
                        party[1].Defib++;
                    }
                break;
                case 12:
                    choosing = false;
                    gotoXY(3, 16); cout << "Shop Keeper:";
                    gotoXY(3, 18); cout << "                                ";
                    gotoXY(23, 2); cout << "SHOP";
                    gotoXY(19, 4); cout << "Items Available";
                    gotoXY(38,14); cout << "You have: " << party[1].money << char(36);
                    gotoXY(5, 12); cout << "Leave";
                    gotoXY(5, 7); cout << "Bandages: ";
                    gotoXY(5, 8); cout << "F.AidKit: ";
                    gotoXY(5, 9); cout << "Defib unit: ";
                    boxhud();
                    gotoXY(3, 18); cout << "You are such a doll!";
                    this_thread::sleep_for(std::chrono::seconds(2));
                break;
                default:
                    choosing = false;
            }
        }
    }
	system("CLS");
}
