#ifndef VK_H
#define VK_H

#include<unistd.h>
#include<linux/input.h>

class vk{
	public:
		int fd;
		
		vk(void);
		void press(char key);
		void release(char key);


	private:

};

#endif
