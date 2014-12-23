#include"wackey.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

extern void err(const char *);

pad::pad(){
	init_keys((char*)".wackeyrc");
	set_touch(true);
	printf("pad inited\n");

}


void pad::init_keys(char *fname){
	FILE *rc = fopen(fname, "r");
	
	fscanf(rc, "%s\n", dev_name);
	printf("%s\n", dev_name);
	dev = open(dev_name, O_RDONLY);
	if(dev < 0) err("cannot open wacom dev.");

	fscanf(rc, "%d %d\n", &realx, &realy);
	fscanf(rc, "%d %d\n", &resx, &resy);

	int xtmp, ytmp, rtmp;
	char ntmp;
	
	num_keys = 0;
	while(fscanf(rc, "%c %d,%d %d\n", &ntmp, &xtmp, &ytmp, &rtmp)!=EOF){
		num_keys++;
	}
	
	rewind(rc);
	printf("%d\n", num_keys);
	keys = new key[num_keys];
	
	fscanf(rc, "%s\n", dev_name);
	fscanf(rc, "%d %d\n", &realx, &realy);
	fscanf(rc, "%d %d\n", &resx, &resy);
	printf("%s, %d %d %d %d\n", dev_name, realx, realy, resx, resy);
	for(int i=0;i<num_keys;i++){
		fscanf(rc, "%c %d,%d %d\n", &keys[i].name, &keys[i].x, &keys[i].y, &keys[i].rsqr);
		keys[i].rsqr *= keys[i].rsqr;
		keys[i].press_ct = -1;
		printf("%c %d,%d %d\n", keys[i].name, keys[i].x, keys[i].y, keys[i].rsqr);
	}

	for(int i=0; i<15; i++){
		fingers[i].x = fingers[i].y = 0;
		fingers[i].id = -1;
	}
	num_fingers = 0;
	
	return;
}

void pad::dump(char *fname){

	FILE *rc = fopen(fname, "w");
	
	fprintf(rc, "%s\n", dev_name);
	fprintf(rc, "%d %d\n", realx, realy);
	fprintf(rc, "%d %d\n", resx, resy);

	for(int i=0;i<num_keys;i++){
		int root = (int)sqrt((float)keys[i].rsqr);
		fprintf(rc, "%c %d,%d %d\n", keys[i].name, keys[i].x, keys[i].y, root);
	}

	fclose(rc);

}

void pad::set_touch(bool v){
	if(v){
		touchable = true;
		printf("SetToutchTrue\n");
	}
	else{
		touchable = false;
		printf("SetToutchFalse\n");
	} 
}


key* finger::test_keys(key *keys, int n){
	key *nearest = NULL;
	int dis_sqr_min = 99999;
	
	for(int i=0; i<n ;i++){
		int x_diff = this->x - keys[i].x;
		int y_diff = this->y - keys[i].y;
		int dis_sqr = x_diff*x_diff + y_diff*y_diff;
		
		if(dis_sqr > keys[i].rsqr)	continue;
		
		if(dis_sqr < dis_sqr_min){
			dis_sqr_min = dis_sqr;
			nearest = keys+i;
		}
	}

	return nearest;
}


