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

char ** faces = {
					" ͡° ͜ʖ ͡°",
					" ͡☉ ͜ʖ ͡☉",
					"°□°",
					"✧Д✧",
					"◉Д◉",
					"°益°"
				};


struct options{
	char * line;
	char * rage;
	char * calm;
	char list;
	int rageFace;
	int calmFace;
	struct winsize w;
};

char run;

void signal_handler(int);
int parseArgs(int,char**,struct options*);
int buildFace(char**,char*,int);
void listFaces( void );


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

	if(opts.list){
		listFaces();
		return 0;
	}

	if(buildFace(&opts.rage,ARM,opts.rageFace) == -1)
		return 1;
	if(buildFace(&opts.calm,"  ",opts.calmFace) == -1)
		return 1;

	run = 1;

	int i;
	i=0;
	while(run){
		int len = opts.w.ws_col;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &opts.w);
		if(opts.w.ws_col != len){
			free(opts.line);
			if((opts.line = (char*)malloc(opts.w.ws_col/sizeof(char))) == NULL){
				free(opts.rage);
				free(opts.calm);
				return 1;
			}
			memset(opts.line,' ',opts.w.ws_col);
			opts.line[opts.w.ws_col-1] = '\0';
		}
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

void signal_handler(int signo){
	run=0;
	printf("\r%s%s Respect the tables!\n",TABLE,RESPECT);
}

int buildFace(char** face, char* arms, int rage){
	int len = 5;		// (ノ)ノ\0
	len += strlen(faces[rage-1]);
	len *= 2;

	if((*face = (char*)malloc(len/sizeof(char))) == NULL)
		return -1;
	strncpy(*face,"(",len);
	strncat(*face,arms,len);
	strncat(*face,faces[rage-1],len);
	strncat(*face,")",len);
	strncat(*face,arms,len);
	return 0;
}

void listFaces( void ){
	int i;
	for(i = 1 ; i < MAX_FACE ; i++){
		printf("%-5d%s\n",i,faces[i-1]);
	}
}

int parseArgs(int argc, char ** argv, struct options* opts){
	char c = 0;
	int i = 0;
	while((c = getopt(argc,argv,"lr:c:")) != -1){
		switch(c){
			case 'l':
				opts->list = 1;
				break;
			case 'r':
				i = atoi(optarg);
				if( MIN_FACE > i || i > MAX_FACE ){
					fprintf(stderr,"Invalid argument to -r: %d\n",i);
					return -1;
				}
				opts->rageFace = i;
				break;
			case 'c':
				i = atoi(optarg);
				if( MIN_FACE > i || i > MAX_FACE ){
					fprintf(stderr,"Invalid argument to -c: %d\n",i);
					return -1;
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
