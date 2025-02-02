#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <write_file> <write_str> \n", argv[0]);
        return 1;
    }

    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        syslog(LOG_ERR, "Failed opening file %s",argv[1]);
        return 1;
    }

    if (write(fd, argv[2], strlen(argv[2])) == -1) {
        syslog(LOG_ERR, "Failed creation file %s",argv[1]);
        close(fd);
        return 1;
    }
    syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);

    close(fd);
    closelog();
    return 0;
}