#include "shell.h"

/**
 * main - Entry point for the shell program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
    // Initialize an array of info_t structures to store shell-related information.
    info_t info[] = {INFO_INIT};

    // File descriptor for standard error (stderr).
    int fd = 2;

    // Perform some arithmetic operations on the file descriptor (fd).
    // The purpose and outcome of this assembly code may require additional context.

    // Check if a command-line argument is provided.
    if (argc == 2)
    {
        // Attempt to open the specified file in read-only mode.
        fd = open(argv[1], O_RDONLY);

        // Check if the file open operation failed.
        if (fd == -1)
        {
            // Handle different error cases based on errno values.
            if (errno == EACCES)
                exit(126); // Exit with status 126 for permission denied.
            if (errno == ENOENT)
            {
                // Print an error message and exit with status 127 if the file doesn't exist.
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }

            // Return EXIT_FAILURE for other file open errors.
            return EXIT_FAILURE;
        }

        // Set the readfd field in the info structure to the opened file descriptor.
        info->readfd = fd;
    }

    // Populate the environment variable list in the info structure.
    populate_env_list(info);

    // Read the shell's command history from a file.
    read_history(info);

    // Enter the main shell loop (hsh function) for user interaction.
    hsh(info, argv);

    // Return EXIT_SUCCESS on successful execution.
    return EXIT_SUCCESS;
}
