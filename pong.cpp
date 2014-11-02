// PONG by Jeremy Long (2014)
// Build with: g++  -std=gnu++11 pong.cpp -lncursesw -o pong

#include <stdio.h>
#include <iostream>
#include <string>
#include <ncursesw/ncurses.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;
const int BKCOLOR=COLOR_RED;

// Global state variable go here:
float ballX, ballY;
float ballV_X, ballV_Y;
int paddleX;
int count;
int h,w;
int timesHit;
const int paddleWidth=18+2;

void setupGame(){
	initscr();
	cbreak();
	noecho();
	timeout(0) ;
	start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, BKCOLOR);
	init_pair(3, COLOR_MAGENTA, COLOR_RED);
	init_pair(4, COLOR_GREEN, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	init_pair(6, COLOR_BLUE, COLOR_GREEN);
	init_pair(7, COLOR_RED, COLOR_MAGENTA);
	init_pair(8, COLOR_BLUE, BKCOLOR);
	curs_set(0);
	bkgd(COLOR_PAIR(8));
	ballX=0;
	ballY=0;
	ballV_X=1;
	ballV_Y=1;
	timesHit=0;
	getmaxyx(stdscr, h,w);
	paddleX = w/2-(paddleWidth/2);
	count=0;
}

void drawScreen(){
	
	getmaxyx(stdscr, h,w);

	move(ballY,ballX);
	addstr(" ");



	ballX=ballX+ballV_X;
	ballY=ballY+ballV_Y;
	move(ballY,ballX);
	attron(COLOR_PAIR(2));
	addstr("O");
	attroff(COLOR_PAIR(2));
	if(trunc(ballX)>(w-2) || trunc(ballX)<=0) ballV_X= -ballV_X;
	if(trunc(ballY)>(h-2) || trunc(ballY)<=0) ballV_Y= -ballV_Y;

	move(h-4,paddleX);
	addstr(" ");
	attron(COLOR_PAIR(1));
	addstr("                  ");
	attroff(COLOR_PAIR(1));
	addstr(" ");

	refresh();
	count++;
	move(0,0);
	string mesg="Score:"; mesg+=to_string(timesHit).data();
	addstr(mesg.data());
}

bool updateState(){
	char ch=getch();
	if(ch=='a' || ch=='A'){if(paddleX > 0) paddleX--;}
	else if(ch=='d' || ch=='D'  ){if(paddleX < (w-paddleWidth)) paddleX++;}
	
	if(ballY==(h-4) && ballX > paddleX && ballX < (paddleX+paddleWidth)){
		timesHit++;
		ballV_Y= -ballV_Y;
	}

	if(timesHit==10S)return true;
	return false;
}

void shutDown(){
	for(int i=0; i<100; i++){
		move(h/2,w/2);
		attron(COLOR_PAIR((i%5)+3));
		addstr("you won !!!");
		attroff(COLOR_PAIR((i%5)+3));
		refresh();		
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	endwin();
	printf("times displayed:%i\n",count);
	
}

int main(int argc, char **argv){
	setupGame();
	drawScreen();
	bool done=false;
	while(! done){
		done=updateState();
		drawScreen();
		this_thread::sleep_for(chrono::milliseconds(55));
	}
	shutDown();
	return 0;
}
