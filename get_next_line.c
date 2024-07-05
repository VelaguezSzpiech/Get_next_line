
#include "get_next_line.h" 


char *read_from_file(int fd)
{
    static char *cup_buffer = NULL;
    static char *ptr = NULL;
    static ssize_t read_size = 0;
    char *newline_ptr;
    char *line;

    if (read_size == 0)
    {
        cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        if (cup_buffer == NULL)
            return NULL;
        read_size = read(fd, cup_buffer, BUFFER_SIZE);
        if (read_size <= 0)
            return NULL;
        cup_buffer[read_size] = '\0';
        ptr = cup_buffer;
    }

    newline_ptr = strchr(ptr, '\n');
    if (newline_ptr == NULL)
    {
        line = strdup(ptr);
        read_size = 0;
    }
    else
    {
        *newline_ptr = '\0';
        line = strdup(ptr);
        ptr = newline_ptr + 1;
    }

    return line;
}

char *get_next_line(int fd)
{
    char *basin_buffer;

    basin_buffer = read_from_file(fd);
    return (basin_buffer);
}

int main(void)
{
    int fd;
    char *next_line;
    int count = 0;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file");
        return 1;
    }

    while ((next_line = get_next_line(fd)) != NULL)
    {
        count++;
        printf("[%d]:%s\n", count, next_line);
        free(next_line);
    }

    close(fd);
    return 0;
}
