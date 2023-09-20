/**
 * is_cmd - Checks if a file is an executable command.
 * @info: Pointer to the info struct.
 * @path: Path to the file to be checked.
 *
 * This function determines whether the file specified by 'path' exists and is
 * marked as an executable regular file (S_IFREG) using the stat function. It is
 * used to verify if a given file can be executed as a command.
 *
 * Return: 1 if 'path' points to an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info; // Unused parameter.
    if (!path || stat(path, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * dup_chars - Duplicates characters from a string based on start and stop indices.
 * @pathstr: The source string.
 * @start: Starting index (inclusive).
 * @stop: Stopping index (exclusive).
 *
 * This function creates a new string by copying characters from 'pathstr' within
 * the range specified by 'start' and 'stop'. It is used to extract a substring
 * from a larger string.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024]; // Static buffer to store the result.
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = 0; // Null-terminate the result string.
    return (buf);
}

/**
 * find_path - Finds the full path of a command in the PATH environment variable.
 * @info: Pointer to the info struct.
 * @pathstr: The PATH environment variable string.
 * @cmd: The command to find in the PATH.
 *
 * This function searches for the specified 'cmd' within the directories listed
 * in the 'pathstr' string (typically the PATH environment variable). It constructs
 * the full path of 'cmd' by combining it with each directory in 'pathstr' and checks
 * if the resulting path is an executable command using the 'is_cmd' function.
 *
 * Return: Pointer to the full path of 'cmd' if found, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return (path);
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}
