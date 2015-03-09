#include"vk.h"
#include"c2k.h"
#include<linux/uinput.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

void err(const char *msg){
	printf("%s\n", msg);
	exit(0);
}

vk::vk(void){

	fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if(fd < 0)	err("failed to open uinput.");

	if(ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)	err("err set evbit");
	if(ioctl(fd, UI_SET_EVBIT, EV_SYN) < 0)	err("err set evbit");
	for(int i=0;i<128;i++){
		if(ioctl(fd, UI_SET_KEYBIT, i) < 0)	err("err set kwybit");
	}

	struct uinput_user_dev uidev;
	memset(&uidev, 0, sizeof(uidev));
	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-sample");
	uidev.id.bustype = BUS_USB;
	uidev.id.vendor  = 0x1;
	uidev.id.product = 0x1;
	uidev.id.version = 1;
	if(write(fd, &uidev, sizeof(uidev)) < 0)	err("err wrt dev");

	if(ioctl(fd, UI_DEV_CREATE, NULL) < 0) err("err create");
	
}


void vk::press(char key){

	struct input_event evt;
	struct timeval t;
	gettimeofday(&t, NULL);

	evt.time = t;
	evt.type = EV_KEY;
	evt.code = c2k[key];
	evt.value = 1;

	write(fd, &evt, sizeof(evt));
	printf("press %c\n", key);

	gettimeofday(&t, NULL);
	evt.time = t;
	evt.type = EV_SYN;
	evt.code = 0;
	evt.value = 0;
	write(fd, &evt, sizeof(evt));

}


void vk::release(char key){

	struct input_event evt;
	struct timeval t;
	gettimeofday(&t, NULL);

	evt.time = t;
	evt.type = EV_KEY;
	evt.code = c2k[key];
	evt.value = 0;

	write(fd, &evt, sizeof(evt));
	printf("release %c\n", key);

	gettimeofday(&t, NULL);
	evt.time = t;
	evt.type = EV_SYN;
	evt.code = 0;
	evt.value = 0;
	write(fd, &evt, sizeof(evt));

}



