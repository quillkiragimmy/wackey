#include<linux/input.h>
#ifndef WACKEY_H
#define WACKEY_H

class key{
	public:
		int x, y, rsqr;
		char name;
		int press_ct;
		
		void set(char name, int x, int y, int rsqr){
			this->name = name;
			this->x = x;
			this->y = y;
			this->rsqr = rsqr;
		}

	private:
};

class finger{
	public:
		int id;	// 0xFFFFFFFF-> none
		int x, y;	// real axises.
		key *pressed;
		
		key* test_keys(key *keys, int n);
	private:
};

class pad{
	public:		
		bool touchable;
		int realx, realy, resx, resy;		
		key *keys;
		int num_keys;
		finger fingers[15];
		int num_fingers;
		char dev_name[90];
		int dev;
		
		pad();
		void init_keys(char *fname);
		void dump(char *fname);
		void set_touch(bool v);
		
	private:
};

#endif
