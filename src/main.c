#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *read_instructions(char *input)
{
    char *token;

    // get first line
    token = strtok(input, "\n");

    // walk through each line
    while (token != NULL)
    {
        // iterate over token, ignore everything after //
        for (int i = 0; i < strlen(token); i++)
        {
            if (token[i] == '/' && token[i + 1] == '/')
            {
                token[i] = '\0';
                break;
            }
            // print everything before //
            printf("%c", token[i]);
        }
        printf("\n");

        token = strtok(NULL, "\n");
    }

    return input;
}

int main(int argc, char **argv)
{
    // check that we have at least one argument
    if (argc < 2)
    {
        printf("Usage: <input file>\n");
        return 1;
    }

    // check if input filename ends with ".bbvv"
    char *input_filename = argv[1];
    char *input_filename_end = input_filename + strlen(input_filename) - 5;
    if (strcmp(input_filename_end, ".bbvv") != 0)
    {
        printf("Input file must end with \".bbvv\"\n");
        return 1;
    }

    // open the input file
    FILE *input = fopen(input_filename, "r");
    if (input == NULL)
    {
        printf("Error: could not open input file '%s'\n", input_filename);
        return 1;
    }

    char *buffer = 0;
    long length;

    fseek(input, 0, SEEK_END);
    length = ftell(input);
    fseek(input, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer)
    {
        fread(buffer, 1, length, input);
    }
    fclose(input);

    if (buffer)
    {
        char *instructions = read_instructions(buffer);
    }
    else
    {
        printf("Error: could not read input file '%s'\n", input_filename);
        return 1;
    }
}
