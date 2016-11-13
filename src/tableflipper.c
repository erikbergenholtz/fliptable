#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/ioctl.h>

#define TABLE			"┳━┳"
#define FLIPPEDTABLE	"┻━┻"

#define RESPECT			"ノ(°_°ノ)"

#define THROW			"彡"
#define ARM				"ノ"

#define UBERRAGE		"°益°"
#define TOPRAGE			"◉Д◉"
#define STARRAGE		"✧Д✧"
#define RAGE			"°□°"
#define CRAYZYLENNY		" ͡☉ ͜ʖ ͡☉"
#define LENNY			" ͡° ͜ʖ ͡°"


void signal_handler();
int buildFace(char**,char*,int);

char run;

int main(int argv, char ** argc){
	signal(SIGINT,signal_handler);

	char * line = NULL;
	char * rage = NULL;
	char * calm = NULL;
	int rageFace = 6;
	int calmFace = 3;
	struct winsize w;



	ioctl(STDOUT_FILENO, TIOCGWINSZ, w);
	run = 1;

	if((line = (char*)malloc(w.ws_col)) == NULL)
		return 1;
	if(buildFace(&rage,ARM,rageFace) == -1)
		return 1;
	if(buildFace(&calm,"  ",calmFace) == -1)
		return 1;

	ioctl(0, TIOCGWINSZ, &w);
	memset(line,' ',w.ws_col);

	int i;
	i=0;
	while(run){
		printf("\r%s",line);
		if(i%2==0)
			printf("\r%s%s",calm,TABLE);
		else
			printf("\r%s%s%s",rage,THROW,FLIPPEDTABLE);
		fflush(stdout);
		i++;
		sleep(1);
	}
	free(line);
	free(rage);
	free(calm);
	line = NULL;
	rage = NULL;
	calm = NULL;
	return 0;
}

void signal_handler(){
	run=0;
	printf("\r%s%s Respect the tables!\n",TABLE,RESPECT);
}

int buildFace(char** face, char* arms, int rage){
	int len = 5;		// (ノ)ノ\0
	char* tmpFace;
	switch(rage){
		case 1:
			tmpFace = LENNY;
			break;
		case 2:
			tmpFace = CRAYZYLENNY;
			break;
		case 3:
			tmpFace = RAGE;
			break;
		case 4:
			tmpFace = STARRAGE;
			break;
		case 5:
			tmpFace = TOPRAGE;
			break;
		case 6:
			tmpFace = UBERRAGE;
			break;
	}
	len += strlen(tmpFace);
	len *= 2;

	if((*face = (char*)malloc(len)) == NULL)
		return -1;
	strncpy(*face,"(",len);
	strncat(*face,arms,len);
	strncat(*face,tmpFace,len);
	strncat(*face,")",len);
	strncat(*face,arms,len);
	return 0;
}
