
#include "get_next_line.h" 

char *ft_strdup(const char *s1) {
    size_t len = strlen(s1);
    char *s2 = malloc(len + 1);
    if (s2) {
        strcpy(s2, s1);
    }
    return s2;
}

// Function to read from file and return the next line
char *read_from_file(int fd) {
    static char buffer[BUFFER_SIZE + 1];
    static char *ptr = buffer;
    static ssize_t bytes_remaining = 0;
    char *line = NULL;
    char *newline_ptr;
    size_t line_length = 0;

    while (1) {
        if (bytes_remaining == 0) {
            bytes_remaining = read(fd, buffer, BUFFER_SIZE);
            if (bytes_remaining <= 0) {
                if (line && line_length > 0) {
                    return line;
                }
                return NULL;
            }
            buffer[bytes_remaining] = '\0';
            ptr = buffer;
        }

        newline_ptr = strchr(ptr, '\n');
        if (newline_ptr) {
            size_t chunk_length = newline_ptr - ptr + 1;
            char *new_line = realloc(line, line_length + chunk_length + 1);
            if (!new_line) {
                free(line);
                return NULL;
            }
            line = new_line;
            strncpy(line + line_length, ptr, chunk_length);
            line_length += chunk_length;
            line[line_length] = '\0';
            ptr = newline_ptr + 1;
            bytes_remaining -= chunk_length;
            return line;
        } else {
            size_t chunk_length = bytes_remaining;
            char *new_line = realloc(line, line_length + chunk_length + 1);
            if (!new_line) {
                free(line);
                return NULL;
            }
            line = new_line;
            strncpy(line + line_length, ptr, chunk_length);
            line_length += chunk_length;
            line[line_length] = '\0';
            bytes_remaining = 0;
        }
    }
}

// Function to get the next line from the file
char *get_next_line(int fd) {
    return read_from_file(fd);
}

int main(void) {
    int fd;
    char *next_line;
    int count = 0;

    printf("Opening file...\n");
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }

    printf("Reading lines from file...\n");
    while ((next_line = get_next_line(fd)) != NULL) {
        count++;
        printf("[%d]: %s", count, next_line);
        free(next_line);
    }

    printf("Closing file...\n");
    close(fd);
    return 0;
}