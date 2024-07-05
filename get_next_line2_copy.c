#include "get_next_line.h" 

// Duplicate a string by allocating memory and copying the content
char *ft_strdup(const char *s1) {
    size_t len = strlen(s1);          // Get the length of the input string
    char *s2 = malloc(len + 1);       // Allocate memory for the duplicate string
    if (s2) {                         // If allocation was successful
        strcpy(s2, s1);               // Copy the input string to the allocated memory
    }
    return s2;                        // Return the pointer to the duplicated string
}

// Read data from file into buffer
ssize_t read_into_buffer(int fd, char *buffer) {
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
    }
    return bytes_read;
}

// Allocate or reallocate memory for the line being constructed
char *reallocate_line(char *line, size_t new_size) {
    char *new_line = realloc(line, new_size);
    if (!new_line) {
        free(line);
    }
    return new_line;
}

// Copy chunk of data from buffer to line
void copy_chunk_to_line(char *line, size_t line_length, char *ptr, size_t chunk_length) {
    strncpy(line + line_length, ptr, chunk_length);
    line[line_length + chunk_length] = '\0';
}

// Function to handle newline found in buffer
char *handle_newline_found(char *line, char **ptr, size_t *line_length, size_t chunk_length, ssize_t *bytes_remaining) {
    char *new_line = reallocate_line(line, *line_length + chunk_length + 1);
    if (!new_line) {
        return NULL;
    }
    line = new_line;
    copy_chunk_to_line(line, *line_length, *ptr, chunk_length);
    *line_length += chunk_length;
    *ptr += chunk_length;
    *bytes_remaining -= chunk_length;
    return line;
}

// Function to handle no newline in buffer
char *handle_no_newline(char *line, char **ptr, size_t *line_length, ssize_t *bytes_remaining) {
    size_t chunk_length = *bytes_remaining;
    char *new_line = reallocate_line(line, *line_length + chunk_length + 1);
    if (!new_line) {
        return NULL;
    }
    line = new_line;
    copy_chunk_to_line(line, *line_length, *ptr, chunk_length);
    *line_length += chunk_length;
    *bytes_remaining = 0;
    return line;
}

// Function to read from file and return the next line
char *read_from_file(int fd) {
    static char buffer[BUFFER_SIZE + 1];
    static char *ptr = buffer;
    static ssize_t bytes_remaining = 0;
    char *line = NULL;
    size_t line_length = 0;

    while (1) {
        if (bytes_remaining == 0) {
            bytes_remaining = read_into_buffer(fd, buffer);
            if (bytes_remaining <= 0) {
                return (line && line_length > 0) ? line : NULL;
            }
            ptr = buffer;
        }

        char *newline_ptr = strchr(ptr, '\n');
        if (newline_ptr) {
            size_t chunk_length = newline_ptr - ptr + 1;
            return handle_newline_found(line, &ptr, &line_length, chunk_length, &bytes_remaining);
        } else {
            line = handle_no_newline(line, &ptr, &line_length, &bytes_remaining);
            if (!line) {
                return NULL;
            }
        }
    }
}

// Function to get the next line from the file
char *get_next_line(int fd) {
    return read_from_file(fd);
}

int main(void) {
    int fd;                                  // File descriptor
    char *next_line;                         // Pointer to hold the next line
    int count = 0;                           // Line counter

    printf("Opening file...\n");
    fd = open("example.txt", O_RDONLY);      // Open the file in read-only mode
    if (fd == -1) {                          // If file opening fails
        printf("Error opening file\n");
        return 1;
    }

    printf("Reading lines from file...\n");
    while ((next_line = get_next_line(fd)) != NULL) { // Read lines until EOF
        count++;                            // Increment the line counter
        printf("[%d]: %s", count, next_line); // Print the line with its number
        free(next_line);                    // Free the memory allocated for the line
    }

    printf("Closing file...\n");
    close(fd);                              // Close the file
    return 0;
}
