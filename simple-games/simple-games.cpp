#include <iostream>
#include <string>
#include "move_test.h"
#include "Snake.h"
#include "Breakout.h"
#include "PingPong.h"
#include "main_menu.h"


int main(){
	main_menu();

	ping_pong();
	breakout();

	test::collide_test();
	test::menu_test();
	test::move_player();
	test::button_auto_scale();
	start_snake();
}