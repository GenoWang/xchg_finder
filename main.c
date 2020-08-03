#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1024*1024

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("Usage: ./xchg_finder [path to chrome]\n");
		exit(1);
	}

	FILE* infile;
	infile = fopen(argv[1], "rb");
	if(!infile){
		printf("[-] Open file failed\n");
		exit(-1);
	}

	char buf[MAXLEN];

	int rc = 0;
	int offset = 0;
	while((rc = fread(buf, sizeof(char), MAXLEN, infile)) != 0){
		/*
		xchg rsp, rax         #4894 
		rex.WR xchg rsp,rax   #4c94
		ret                   #c3
		*/
		int index_1 = 0;
		int index_2 = 0;
		int of2ret = 0;
		for(index_1 = 0; index_1 < MAXLEN; index_1 += 2){
			if((buf[index_1] == '\x4c' || buf[index_1] == '\x48') 
				&& buf[index_1+1] == '\x94'){
				index_2 = index_1+2;
				of2ret = 0;
				while(buf[index_2] != '\xc3'){
					of2ret += 1;
					index_2++;
					if(of2ret > 20){
						break;
					}
				}
				if(of2ret < 6){
					printf("0x%x (ret @ 0x%x)\n", offset+index_1+0x1000, offset+index_2+0x1000);
				}
				
			}
			
		}
		offset += rc;
	}
	return 0;
/*
    0x55fbbbdbe000     0x55fbbeab5000 r--p  2cf7000 0      /home/wgn/Desktop/mojo/chrome
    0x55fbbeab5000     0x55fbc5cbf000 r-xp  720a000 2cf6000 /home/wgn/Desktop/mojo/chrome
    0x55fbc5cbf000     0x55fbc635c000 r--p   69d000 9eff000 /home/wgn/Desktop/mojo/chrome
    0x55fbc635c000     0x55fbc63b8000 rw-p    5c000 a59b000 /home/wgn/Desktop/mojo/chrome
    */
}