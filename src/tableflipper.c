#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <sys/ioctl.h>

#define TABLE			"┳━┳"
#define FLIPPEDTABLE	"┻━┻"

#define RESPECT			"ノ(°_°ノ)"

#define THROW			"彡"
#define ARM				"ノ"

#define MIN_FACE		1
#define MAX_FACE		6

#define UBERRAGE		"°益°"
#define TOPRAGE			"◉Д◉"
#define STARRAGE		"✧Д✧"
#define RAGE			"°□°"
#define CRAYZYLENNY		" ͡☉ ͜ʖ ͡☉"
#define LENNY			" ͡° ͜ʖ ͡°"


struct options{
	char * line;
	char * rage;
	char * calm;
	int rageFace;
	int calmFace;
	struct winsize w;
};

char run;

void signal_handler();
int parseArgs(int,char**,struct options*);
int buildFace(char**,char*,int);


int main(int argc, char ** argv){
	signal(SIGINT,signal_handler);

	struct options opts;

	opts.line= NULL;
	opts.rage = NULL;
	opts.calm = NULL;
	opts.rageFace = 6;
	opts.calmFace = 3;

	if(parseArgs(argc,argv,&opts) == -1)
		return 1;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, opts.w);
	run = 1;

	if((opts.line = (char*)malloc(opts.w.ws_col)) == NULL)
		return 1;
	if(buildFace(&opts.rage,ARM,opts.rageFace) == -1)
		return 1;
	if(buildFace(&opts.calm,"  ",opts.calmFace) == -1)
		return 1;

	ioctl(0, TIOCGWINSZ, &opts.w);
	memset(opts.line,' ',opts.w.ws_col);

	int i;
	i=0;
	while(run){
		printf("\r%s",opts.line);
		if(i%2==0)
			printf("\r%s%s",opts.calm,TABLE);
		else
			printf("\r%s%s%s",opts.rage,THROW,FLIPPEDTABLE);
		fflush(stdout);
		i++;
		sleep(1);
	}
	free(opts.line);
	free(opts.rage);
	free(opts.calm);
	opts.line = NULL;
	opts.rage = NULL;
	opts.calm = NULL;
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

int parseArgs(int argc, char ** argv, struct options* opts){
	char c = 0;
	int i = 0;
	while((c = getopt(argc,argv,"r:c:")) != -1){
		switch(c){
			case 'r':
				i = atoi(optarg);
				if( MIN_FACE > i || i > MAX_FACE ){
					fprintf(stderr,"Invalid argument to -r: %d\n",i);
				}
				opts->rageFace = i;
				break;
			case 'c':
				i = atoi(optarg);
				if( MIN_FACE > i || i > MAX_FACE ){
					fprintf(stderr,"Invalid argument to -r: %d\n",i);
				}
				opts->calmFace = i;
				break;
			case '?':
				if(optopt == 'c' || optopt == 'r'){
					fprintf(stderr,"Option -%c requires an arugment\n",optopt);
				}else if( isprint(optopt) ){
					fprintf(stderr,"Unknown option -%c\n",optopt);
				}else{
					fprintf(stderr,"Unknow character '\\x%x'\n",c);
				}
				return -1;
			default:
				abort();
		}
	}
	return 0;
}
