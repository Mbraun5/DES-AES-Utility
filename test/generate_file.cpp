#include<stdio.h>
#include<string>

using namespace std;

#define BUFSIZE 1024

void txt_gen(unsigned char *buf, int offset) {
        // const char *hex_digits = "0123456789abcdefghijklmnopqrstuvwxyz!@#$%^&*()-_=+[{]}";
        for (int i = 0; i < BUFSIZE+offset; i++) {
            buf[i] = 32 + (rand() % (126-32+1))
        }
        // printf("%s\n", buf);
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    unsigned char* buf;
    FILE* outfile = fopen("test_file", "wb+");

    if (argc != 2) {
        fprintf(stderr, "Invalid argc size. Need to pass offset parameter.");
        exit(-1);
    }

    int offset = stoi(argv[1], NULL, 10);
    printf("%d\n", offset);
    buf = new unsigned char [BUFSIZE + offset];

    if (outfile == NULL) { /* If error is thrown, system is unable to create new file in working directory */
        fprintf(stderr, "Unable to create any more files in directory\n");
        exit(-1);	
    }

    for (long long int j=0; j < 20000; j++) {
        txt_gen(buf, i);
        if (fwrite(buf, sizeof(unsigned char), BUFSIZE+offset, outfile) != BUFSIZE+offset) {
            fprintf(stderr, "ERROR [%s %s %d]: Did not write correct bytes to file\n",	
                            __FILE__, __FUNCTION__, __LINE__);
            exit(-1);
        }
    }
    return 0;
}
