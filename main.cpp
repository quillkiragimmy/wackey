#include"wackey.h"
#include"c2k.h"
#include"vk.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern void err(const char *msg);

int main(int argc, char **argv){

	pad *wacom = new pad();
	vk *ukey = new vk();
	init_c2k();

	struct input_event evt;
	int slot = 0;
	float xratio = wacom->realx/(float)wacom->resx;
	float yratio = wacom->realy/(float)wacom->resy;

	if(argc == 3){
		char *keystr = argv[2];

		delete [] wacom->keys;
		wacom->num_keys = strlen(keystr);
		wacom->keys = new key[wacom->num_keys];

		printf("old keys cleared.\n");

		for(int i=0;i<wacom->num_keys;i++){
			printf("touch for key \'%c\'\n", keystr[i]);
			for(;;){
				read(wacom->dev, &evt, sizeof(evt));
				if(evt.type == EV_ABS){
					switch(evt.code){
						case 0x2f:
							slot = evt.value;
							break;
						case 0x35:
							wacom->fingers[slot].x = evt.value*xratio;
							break;
						case 0x36:
							wacom->fingers[slot].y = evt.value*yratio;
							break;
						case 0x39:
							wacom->fingers[slot].id = evt.value;
							break;
					}

				}
				else if(evt.type == EV_SYN){
					bool nofg = true;
					for(int j=0;j<15;j++){
						if(wacom->fingers[j].id != -1){	nofg = false; break; }
					}
					if(nofg){
						wacom->keys[i].name = keystr[i];
						wacom->keys[i].x = wacom->fingers[slot].x;
						wacom->keys[i].y = wacom->fingers[slot].y;
						wacom->keys[i].rsqr = 225;
						break;
					}
				}
			}
		}

		wacom->dump(argv[1]);

	}
	else if(argc == 2){
		delete [] wacom->keys;
		wacom->init_keys(argv[1]);
	}

	printf("new keys applied.\n");

	for(;;){
		if(read(wacom->dev, &evt, sizeof(evt)) < 1){
			err("read error");
		}

		if(evt.type == EV_KEY && evt.code == 0x110 && evt.value == 0){
			printf("butted.\n");
			if(wacom->touchable)	wacom->set_touch(false);
			else	wacom->set_touch(true);
		}
		else if(evt.type == EV_ABS){
			switch(evt.code){
				case 0x2f:
					slot = evt.value;
					break;
				case 0x35:
					wacom->fingers[slot].x = evt.value*xratio;
					break;
				case 0x36:
					wacom->fingers[slot].y = evt.value*yratio;
					break;
				case 0x39:
					wacom->fingers[slot].id = evt.value;	// unique id per finger touch.
					break;
			}

		}
		else if(evt.type == EV_SYN){
			if(!wacom->touchable)	continue;

			for(int i=0;i<15;i++){
				finger *fg = wacom->fingers + i;
				if(fg->id == -1 && fg->pressed != NULL){
					ukey->release(fg->pressed->name);
					fg->pressed = NULL;
				}
				else if(fg->id != -1){
					key *hit = fg->test_keys(wacom->keys, wacom->num_keys);
					if(hit == NULL){ }
					else{
						if(fg->pressed == NULL){ // fresh touch.
							ukey->press(hit->name);
							fg->pressed = hit;
						}
						else if(fg->pressed != hit){ // sliding touch.
							ukey->release(fg->pressed->name);
							ukey->press(hit->name);
							fg->pressed = hit;
						}
					}
				}
			}
		}
	}

	return 0;
}


