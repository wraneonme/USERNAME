#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    //BITMAPFILEHEADER bf;



    typedef uint8_t BYTE;// defines a byte as 8 bits

    FILE *jpgread = fopen(argv[1], "r");
    FILE *jpgwrit = NULL;
    BYTE buffer[512];
    int filenumber = 0;
    //bool newjpg = false;

    char imgname[8];

    if (argc != 2)
    {
        printf("usage error");
        return 1;
    }

    if (jpgread == NULL)
    {
        printf("usage error");
        fclose(jpgwrit);
        printf("file %s could not be created", imgname);
    }

    while (fread(buffer, 512, 1, jpgread))
    {
        //newjpg = false;
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpgwrit != NULL)
            {
                fclose(jpgwrit);
            }
            sprintf(imgname, "%03i.jpg", filenumber);
            jpgwrit = fopen(imgname, "w");

            if (jpgwrit == NULL)
            {
                fclose(jpgwrit);
                printf("file %s could not be created", imgname);
                return 2;
            }
            filenumber++;
        }
        if (filenumber > 0)
        {
            fwrite(buffer, 512, 1, jpgwrit);//this line is different from your original?
            //are they reversed or not... does it matter?
        }
    }
    fclose(jpgread);
    fclose(jpgwrit);
    return 0;
}
