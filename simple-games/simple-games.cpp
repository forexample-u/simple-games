#include <iostream>
#include <string>
#include "move_test.h"
#include "Snake.h"
#include "interface.h"

int main(){
	test::collide_test();
	test::move_player();
	test::button_auto_scale();
	start_snake();
}