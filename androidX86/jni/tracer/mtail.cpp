/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mtail.cpp
 * Author: kwang
 *
 * Created on January 3, 2019, 9:54 AM
 */
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int pageSize = 1024*4;
    if(argc!=2){
	printf("Usage %s file\n",argv[0]);
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd > 0){
	int size = lseek(fd, 0, SEEK_END);
	if(size > pageSize){
	    lseek(fd, -pageSize, SEEK_CUR);
	}else{
	    lseek(fd, 0, SEEK_SET);
	}
	char buf[pageSize];	
	while(true){
	    while(true){
		//int numread write(filedesc,"This will be output to testfile.txt\n", 36) != 36)

		int numread = read (fd,&buf[0],sizeof(buf));
		//printf("%d\n",numread);
		if(numread<=0){
		    break;
		}
		write(1,&buf[0],numread);
	    }
	    sleep(1);
	}
	close(fd);
    }
    return 0;
}

