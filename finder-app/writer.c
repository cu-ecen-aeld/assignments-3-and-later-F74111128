#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID|LOG_CONS, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Error: Two arguments required: <file_path> <text_string>");
        closelog();
        return 1;
=======
#include <syslog.h>

int main(int argc, char *argv[]) {
    // Check if correct number of arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        exit(EXIT_FAILURE);
>>>>>>> 36427d2c9f66ba46565b46f0221c85349785c4de
    }

    char *writefile = argv[1];
    char *writestr = argv[2];
<<<<<<< HEAD
    FILE *file = fopen(writefile, "w");

    fputs(writestr, file);
    syslog(LOG_DEBUG, "Writing '%s' to '%s'", writestr, writefile);

    fclose(file);
=======

    // Write to file
    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Failed to open '%s' for writing.", writefile);
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", writestr);
    fclose(file);

    // Log the action
    syslog(LOG_DEBUG, "Writing '%s' to '%s'", writestr, writefile);

>>>>>>> 36427d2c9f66ba46565b46f0221c85349785c4de
    closelog();

    return 0;
}
