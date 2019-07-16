#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h> 
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

/*struct message{
	//0 = ADD, 1 = SUP, 2 = POS
	int type;
	float x;
	float y;
};*/

struct message{
	int type;
	float x;
	float y;
	int left;
	int top;
	int width;
	int height;
};

//  protocolbuffer json