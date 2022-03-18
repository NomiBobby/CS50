#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    // Check command line arguements
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open the input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // initialize a block with a size of 512B
    BYTE block[512];
    FILE *outptr;
    int image_id = 0;
    char outfile[10];

    // Read 1 block until reaching the end of the file
    while (fread(&block, sizeof(block), 1, inptr) == 1)
    {
        // If header, open new file
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff)
        {
            if (block[3] >= 0xe0 && block[3] <= 0xef)
            {

                //If there is a previous file, close it -- check if outptr
                if (outptr != NULL)
                {
                    fclose(outptr);
                    image_id++;
                }

                // Then open a new file
                sprintf(outfile, "%03i.jpg", image_id);
                outptr = fopen(outfile, "w");
                if (inptr == NULL)
                {
                    fprintf(stderr, "Could not open %s.\n", outfile);
                    return 4;
                }
                fwrite(&block, sizeof(block), 1, outptr);
            }
        }
        // If not header, write to file
        else
        {
            // if there is a open file, write to it
            if (outptr != NULL)
            {
                fwrite(&block, sizeof(block), 1, outptr);
            }
        }
    }

    fclose(outptr);
    fclose(inptr);

    return 0;
}