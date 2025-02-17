#include <stdio.h>
#include <string.h>
#include "incbin.h"

// Import the sample text file
IMPORT_BIN(".rodata", "sample.txt", sample_text);

// Declare the symbols that will be defined by the assembler
extern const char sample_text[], _sizeof_sample_text[];

int main() {
    int sizeof_sample_text = (int)_sizeof_sample_text;

    printf("Embedded text content (%u bytes):\n", sizeof_sample_text);
    printf("-------------------\n");
    // Note: The embedded text is not null-terminated, so we use fwrite
    fwrite(sample_text, 1, sizeof_sample_text, stdout);
    printf("\n-------------------\n");

    // Verify the content matches our expectations
    // const char expected[] = "Hello, this is a sample text file.\n"
    //                       "It contains multiple lines of text\n"
    //                       "that will be embedded into our C program.\n"
    //                       "We will verify this content at runtime.\n";
    
    // read the file dynamically
    char expected[1000];
    FILE *fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fread(expected, 1, file_size, fp);
    expected[file_size] = '\0';
    fclose(fp);

    if (sizeof_sample_text != strlen(expected)) {
        printf("Size mismatch! Expected %zu bytes but got %u bytes\n",
               strlen(expected), sizeof_sample_text);
        return 1;
    }

    if (memcmp(sample_text, expected, sizeof_sample_text) != 0) {
        printf("Content mismatch!\n");
        return 1;
    }

    printf("Content verification successful!\n");
    return 0;
}
