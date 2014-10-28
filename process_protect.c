#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define PROCESS_PID "/tmp/test_process.pid"

int process_exists()
{
    int fd;
    struct flock lock;
    char buffer[32];

    fd = open(PROCESS_PID, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd < 0)
        return 0;
        
    lock.l_type   = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start  = 0;
    lock.l_len    = 0;

    if (fcntl(fd, F_SETLK, &lock) != 0) {
        close(fd);
        return 1;
    }

    ftruncate(fd, 0);
    snprintf(buffer, sizeof(buffer), "%d", getpid());
    write(fd, buffer, strlen(buffer));

    return 0;
}

int main(int argc,char *argv[])
{
	int i = 0;

	if(process_exists()) {
		fprintf(stdout,"This process already exists.\n");
		exit(1);
	}
	
	while(i <= 30) {
		printf("test process pid persistant.\n");
		sleep(1);
		i++;
	}
	
	return 0;
}
