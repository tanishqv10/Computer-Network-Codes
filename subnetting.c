#include <stdio.h>
#include <math.h>

int main()
{

    int argc;
    char *argv[1000];

    int IP1, IP2, IP3, IP4, CIDR, bitborrowed, bitremained, subnet, host, mask, blocksize;
    char class1;

    printf(" Please enter IP address in the form of \"0.0.0.0\": \n");

    scanf("%i.%i.%i.%i", &IP1, &IP2, &IP3, &IP4);

    do
    {
        if ((IP1 > 255 || IP2 > 255 || IP3 > 255 || IP4 > 255) || (IP1 == 127 || IP1 == 191 || IP1 == 223) || (IP1 == 0 && IP2 == 0 && IP3 == 0 && IP4 == 0))
        {

            printf("| Warning!! IP address invalid, please enter a valid IP address: |\n");

            scanf("%d.%d.%d.%d", &IP1, &IP2, &IP3, &IP4);
        }
    } while ((IP1 > 255 || IP2 > 255 || IP3 > 255 || IP4 > 255) || (IP1 == 127 || IP1 == 191 || IP1 == 223) || (IP1 == 0 && IP2 == 0 && IP3 == 0 && IP4 == 0));

    printf(" Enter CIDR in the format of decimal CIDR: \n");

    scanf("%d", &CIDR);
    do
    {

        if (CIDR > 32 || CIDR == 0)
        {

            printf("| Invalid CIDR, please enter a valid CIDR: |\n");

            scanf("%d", &CIDR);
        }
    } while (CIDR > 32);

    if (IP1 <= 127)
    {
        class1 = 'A';
    }
    else if (IP1 <= 191)
    {
        class1 = 'B';
    }
    else if (IP1 <= 223)
    {
        class1 = 'C';
    }
    else
    {
        printf("Class D or E \n");
    }

    switch (class1)
    {
    case 'A':
        if (CIDR >= 8)
        {
            bitborrowed = CIDR - 8;
        }
        else
        {
            bitborrowed = 8 - CIDR;
        }
        break;
    case 'B':
        if (CIDR >= 16)
        {
            bitborrowed = CIDR - 16;
        }
        else
        {
            bitborrowed = 16 - CIDR;
        }
        break;
    case 'C':
        if (CIDR >= 24)
        {
            bitborrowed = CIDR - 24;
        }
        else
        {
            bitborrowed = 24 - CIDR;
        }
    }

    //Let Find the number of bits that remained
    switch (class1)
    {
    case 'A':
        bitremained = 32 - CIDR;
        break;
    case 'B':
        bitremained = 32 - CIDR;
        break;
    case 'C':
        bitremained = 32 - CIDR;
        break;
    }

    //Now Let Calculate the number of Subnets
    subnet = pow(2, bitborrowed);

    //And then we calculate the number of usable hosts
    host = pow(2, bitremained) - 2;

    //Here we determine the block size
    switch (bitborrowed)
    {
    case 1:
        blocksize = 128;
        break;
    case 2:
        blocksize = 64;
        break;
    case 3:
        blocksize = 32;
        break;
    case 4:
        blocksize = 16;
        break;
    case 5:
        blocksize = 8;
        break;
    case 6:
        blocksize = 4;
        break;
    case 7:
        blocksize = 2;
        break;
    case 8:
        blocksize = 1;
        break;
    }

    printf("Answer\n");

    printf("your IP %i.%i.%i.%i/%i is of class1 %c\n", IP1, IP2, IP3, IP4, CIDR, class1);

    printf("Number of bit borrowed is:\t%d \n", bitborrowed);

    printf("Number of bits remained is:\t%d \n", bitremained);

    printf("Subnet:\t%d \n", subnet);

    printf("host:\t%d \n", host);

    printf("blocksize:\t%d \n", blocksize);

    return (0);
}