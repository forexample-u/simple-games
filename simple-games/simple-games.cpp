#include <iostream>
#include <string>
#include "move_test.h"
#include "Snake.h"
#include "Breakout.h"
#include "Snake.h"

int main(){
	//start_snake();
	breakout();
	
	test::collide_test();
	test::menu_test();
	test::move_player();
	test::button_auto_scale();
	start_snake();
}