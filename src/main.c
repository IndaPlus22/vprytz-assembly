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
}

void read_instructions(char *input, int *instructions)
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

        // add instruction to instructions
        instructions[counter] = *instruction;

        // check that this was invalid instruction, only increase counter if so
        if (instruction[0] != -1)
        {
            counter++;
        }
    }
}

void run_instructions(int *instructions)
{
    // registers
    int registers[4] = {0, 0, 0, 0};

    // instruction pointer
    int ip = 0;

    // run instructions
    while (ip < 1000)
    {
        // get current instruction as int array fron instructions (using ip)
        int *instruction = &instructions[ip];

        // instruction convertion
        // add -> 0
        // sub -> 1
        // set -> 2
        // jeq -> 3
        // j -> 4
        // input -> 5
        // print -> 6
        // exit -> 7

        // set op, rt, rs, imm
        int op = instruction[0];
        int rt = instruction[1];
        int rs = instruction[2];
        int imm = instruction[3];

        // print whole instruction
        printf("running instruction: %d, %d, %d, %d\n", op, rt, rs, imm);

        // print registers
        printf("registers: %d, %d, %d, %d\n", registers[0], registers[1], registers[2], registers[3]);

        // add
        if (op == 0)
        {
            registers[rt] = registers[rt] + registers[rs] + imm;
        }

        // sub
        if (op == 1)
        {
            registers[rt] = registers[rt] - registers[rs] - imm;
        }

        // set
        if (op == 2)
        {
            registers[rt] = registers[rs] + imm;
        }

        // jeq
        if (op == 3)
        {
            if (registers[rt] == registers[rs] && imm)
            {
                ip += 1;
            }
            if (registers[rt] != registers[rs] && !imm)
            {
                ip += 1;
            }
        }

        // j
        if (op == 4)
        {
            ip = ip + imm;
        }

        // input
        if (op == 5)
        {
            int input;
            scanf("%d", &input);
            registers[1] = input;
        }

        // print
        if (op == 6)
        {
            printf("%d", registers[1]);
        }

        // exit
        if (op == 7)
        {
            exit(0);
        }

        ip++;
    }
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
        int *instructions = malloc(100000 * sizeof(int) * 4);

        read_instructions(buffer, instructions);
        run_instructions(instructions);
    }
    else
    {
        printf("Error: could not read input file '%s'\n", input_filename);
        return 1;
    }
}
