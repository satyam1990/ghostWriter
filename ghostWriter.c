/******************************************************************************
 *
 * ghostWriter.c
 *
 * Author: mSatyam
 *
 * April, 2014
 *
 * Run and have fun.
 *
 *****************************************************************************/

#include <unistd.h>
#include <sys/termios.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	struct termios initial_settings, new_settings;

	// get initial terminal settings
	tcgetattr(fileno(stdin), &initial_settings);

	// copy settings to new_settings
	new_settings = initial_settings;

	// toggle canonical mode (i.e. process character as soon as inputted)
	new_settings.c_lflag &= ~ICANON;

	// toogle echo
	new_settings.c_lflag &= ~ECHO;

	// apply new settings
	if (tcsetattr(fileno(stdin), TCSAFLUSH, &new_settings) != 0)
		fprintf(stderr, "Unable to set new terminal settings\n");

	int ch, real;
	FILE *in;

	// open file to be written to look geek
	in = fopen("geek.c", "r");
	
	// clear the screen
	system("clear");

	while((ch = getchar()) != 27) // 27 represents ESC key
	{
		real = fgetc(in);
		putchar(real);
	}

	// reset initial terminal settings
	tcsetattr(fileno(stdin), TCSAFLUSH, &initial_settings);

	// clean up
	fclose(in);

return 0;
}
