#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    // Check if correct number of arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *writefile = argv[1];
    char *writestr = argv[2];

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

    closelog();

    return 0;
}
