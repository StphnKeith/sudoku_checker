#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check arguments
    if (argc > 2) {
        fprintf(stderr, "USAGE: most_processes [ppid]\n");
        return 1;
    }
    int select_ppid = 0;
    int ppid;
    if (argc == 2) {
        select_ppid = 1;
        ppid = strtol(argv[1], NULL, 10);
    }

    // Loop through input
    // Keep track of the current UID and count processes owned by current UID
    // Keep track of current max processes and UID owner
    // If processes of current UID exceeds current max processes
    // change current max processes and UID owner
    char line[1024];
    char current_UID[32];
    int current_count = 1;
    char max_UID[32] = "";
    int max_count = 0;
    while (fgets(line, 1024, stdin)) {
        // Get new UID and PPID
        char new_UID[32];
        int new_PPID;
        sscanf(line, "%s %*s %i", new_UID, &new_PPID);
        // printf("current_UID: %s, current_count: %d\n", current_UID, current_count);

        // Continue to next loop if PPID says so
        if (select_ppid && ppid != new_PPID) {
            continue;
        }

        // Check if new UID is current UID, if yes increment, else reset
        if (strcmp(current_UID, new_UID) == 0) {
            current_count += 1;
        } else {
            strcpy(current_UID, new_UID);
            current_count = 1;
        }

        // Compare current count and max count, overwrite if necessary
        if (current_count > max_count) {
            max_count = current_count;
            if (strcmp(max_UID, current_UID) != 0) {
                strcpy(max_UID, current_UID);
            }
        }
    }

    // Only print if max_UID has been overwritten
    // This way it doesn't print if the input is empty or it skips every
    // line due to no occurences of the given PPID
    if (strcmp(max_UID, "") != 0) {
        printf("%s %d\n", max_UID, max_count);
    }

    return 0;
}
