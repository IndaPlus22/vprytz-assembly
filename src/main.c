#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// valid instructions
static char *valid_instructions[8] = {"add", "sub", "set", "jeq", "j", "input", "print", "exit"};

// instruction convertion
// add -> 0
// sub -> 1
// set -> 2
// jeq -> 3
// j -> 4
// input -> 5
// print -> 6
// exit -> 7
int map_instruction_int(char *instruction)
{
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(instruction, valid_instructions[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int num_lines(char *input)
{
    int count = 0;
    char *line = strtok(input, "\n");
    while (line != NULL)
    {
        count++;
        line = strtok(NULL, "\n");
    }
    return count;
}

// function that parses rs, rt, imm
void parse_rs_rt_imm(char *line, char *rs, char *rt, char *imm)
{

    // get rs, rt, imm
    int i = 0;
    int x = 0;
    for (int j = 4; j < strlen(line); j++)
    {
        if (line[j] == ' ')
        {
            x++;
            i = -1;
        }

        if (x == 0)
        {
            rs[i] = line[j];
        }
        else if (x == 1)
        {
            rt[i] = line[j];
        }
        else if (x == 2)
        {
            imm[i] = line[j];
        }

        i++;

        if (x == 3)
        {
            break;
        }
    }

    // free up memory
}

int *read_instructions(char *input)
{
    // get first line
    char *line = strtok(input, "\n");

    // char str[10000];
    // char *instructions = str;

    // example:
    // instructions = [
    //      add #1 #2 0
    //     [0,   1,2,0]
    // ]

    int *instructions; // array of instructions
    int counter = 0;

    // walk through other lines
    while (line != NULL)
    {
        char *word = malloc(sizeof(char) * 100);
        int instruction[4];
        // int *instruction[4] = malloc(sizeof(int) * 4);

        // iterate through line[i] until " " is found
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == ' ')
            {
                break;
            }
            word[i] = line[i];
        }

        // map instruction word to int
        instruction[0] = map_instruction_int(word);
        instruction[1] = 0;
        instruction[2] = 0;
        instruction[3] = 0;

        // allocate rs, rt, imm
        char *rs = malloc(sizeof(char) * 2);
        char *rt = malloc(sizeof(char) * 2);
        char *imm = malloc(sizeof(char) * 2);

        if (strcmp(word, "add") == 0)
        {
            // example: add #1 #2 0
            // above will set #1 = #2 + 0
            // we want to get rs, rt, imm
            // without modifying the original string

            // get rs, rt, imm
            parse_rs_rt_imm(line, rs, rt, imm);

            instruction[1] = atoi(&rs[1]);
            instruction[2] = atoi(&rt[1]);
            instruction[3] = atoi(imm);
        }
        if (strcmp(word, "sub") == 0)
        {
            // example: sub #3 #0 1
            // above will set #3 = #0 - 1
            // we want to get rs, rt, imm
            // without modifying the original string

            // get rs, rt, imm
            parse_rs_rt_imm(line, rs, rt, imm);

            instruction[1] = atoi(&rs[1]);
            instruction[2] = atoi(&rt[1]);
            instruction[3] = atoi(imm);
        }

        if (strcmp(word, "set") == 0)
        {
            // example: set #3 #0 1
            // above will set #3 = #0 + 1
            // we want to get rs, rt, imm
            // without modifying the original string

            // get rs, rt, imm
            parse_rs_rt_imm(line, rs, rt, imm);

            instruction[1] = atoi(&rs[1]);
            instruction[2] = atoi(&rt[1]);
            instruction[3] = atoi(imm);
        }

        if (strcmp(word, "jeq") == 0)
        {
            // example: jeq #2 #0 0
            // above will jump one line if #2 == #0 && 0
            // we want to get rs, rt, imm
            // without modifying the original string

            // get rs, rt, imm
            parse_rs_rt_imm(line, rs, rt, imm);

            instruction[1] = atoi(&rs[1]);
            instruction[2] = atoi(&rt[1]);
            instruction[3] = atoi(imm);
        }

        if (strcmp(word, "j") == 0)
        {
            // example: j 0
            // above will jump 0 lines
            // we want to get imm
            // without modifying the original string

            // get imm
            int i = 0;
            for (int j = 2; j < strlen(line); j++)
            {
                if (line[j] == ' ')
                {
                    break;
                }
                imm[i] = line[j];
                i++;
            }

            instruction[1] = atoi(imm);
        }

        line = strtok(NULL, "\n");

        // free up memory
        free(word);
        free(rs);
        free(rt);
        free(imm);

        // print instruction
        printf("instruction: %d, %d, %d, %d\n", instruction[0], instruction[1], instruction[2], instruction[3]);
    }

    return instructions;
}

// char *read_instructions1(char *input)
// {
//     char *token;
//     // 12
//     char *instructions = malloc(120 * num_lines(input) * sizeof(char));

//     // get first line
//     token = strtok(input, "\n");

//     // walk through each line
//     while (token != NULL)
//     {
//         // iterate over token, ignore everything after //
//         for (int i = 0; i < strlen(token); i++)
//         {
//             if (token[i] == '/' && token[i + 1] == '/')
//             {
//                 token[i] = '\0';
//                 break;
//             }
//             // print everything before //
//             // printf("%c", token[i]);
//             strncat(instructions, token[i], 1);
//         }
//         strncat(instructions, "\n", 1);

//         token = strtok(NULL, "\n");
//     }

//     return input;
// }

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
        int *instructions = read_instructions(buffer);
    }
    else
    {
        printf("Error: could not read input file '%s'\n", input_filename);
        return 1;
    }
}
