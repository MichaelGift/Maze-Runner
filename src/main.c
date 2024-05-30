#include "../headers/main.h"


int main(void) {
	if (initializeWindow() == true) {
		printf("True");
	}
	else {
		printf("false");
	}
}