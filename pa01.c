/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Peter Petro  | PE310601 @ ucf.edu | 5448978
| Language: C
| To Compile: gcc -o pa01 pa01.c
| To Execute: c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Spring 2025
| Instructor: McAlpin
| Due Date: 02-24-2025
+===========================================================================*/

// LIBRARY IMPORT
#include <stdio.h>  // Input - output
#include <stdlib.h> // memory allocation
#include <ctype.h>  // character manipulation
#include <string.h> // string manipulation

// PREDEFINED GLOBAL VALUE
#define TEXT_LIMIT 10000

// Function prototypes
void readMatrix(const char *filename, int keyMatrix[9][9], int *n);
void readPT(const char *filename, char *plaintext, int *textLength, int n);
void ecryption(int keyMatrix[9][9], char *plaintext, int textLength, int n, char *ciphertext);
void printMatrix(int matrix[9][9], int n);
void printOUT(const char *text, int length);

// Main function
int main(int argc, char *argv[]) {

    int keyMatrix[9][9], n;
    char plaintext[TEXT_LIMIT], ciphertext[TEXT_LIMIT];
    int textLength = 0;

    // Read key matrix and plaintext
    readMatrix(argv[1], keyMatrix, &n);
    readPT(argv[2], plaintext, &textLength, n);  // Read the plaintext file for encryption

    // Function call for encryption to begin
    ecryption(keyMatrix, plaintext, textLength, n, ciphertext); // Encrypt the plaintext using the key matrix

    // Print key matrix
    printf("\nKey matrix:\n");
    printMatrix(keyMatrix, n);
    // print plaintext
    printf("\nPlaintext:\n");
    printOUT(plaintext, textLength);
    // print ciphertext
    printf("\nCiphertext:\n");
    printOUT(ciphertext, textLength);
    
    return 0;
}

// Function to read the encryption key matrix from the file
void readMatrix(const char *filename, int keyMatrix[9][9], int *n) {
    // Error handling for file opening
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening key file.\n");
        exit(1);
    }
    // Error handling for key size
    fscanf(file, "%d", n);
    if (*n < 2 || *n > 9) {
        fprintf(stderr, "Invalid key size. Must be between 2 (exclusive) and 9.(exclusive)\n");
        fclose(file);
        exit(1);
    }

    // Nested loop to read key matrix values
    for (int i = 0; i < *n; i++) {  // Loop through rows
        for (int j = 0; j < *n; j++) {  // Loop through columns
            fscanf(file, "%d", &keyMatrix[i][j]);
        }
    }
    fclose(file); // Close the file
}

// Function to read the plaintext file and process only alphabetic characters
void readPT(const char *filename, char *plaintext, int *textLength, int n) {
    FILE *file = fopen(filename, "r");
    // Error handling for file opening
    if (!file) {
        fprintf(stderr, "Error opening plaintext file.\n");
        exit(1);
    }
 
    char ch;    // Character to read from file
    *textLength = 0;  // text length pointer

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) { // Check if character is alphabetic to avoid special characters and numbers [isalpha T/F]
            plaintext[*textLength] = tolower(ch); // Convert to lowercase 
            (*textLength)++; // Increment the text length
        }
    }

    while (*textLength % n != 0) { // Pad the text with 'x' if the length is not a multiple of n
        plaintext[*textLength] = 'x';
        (*textLength)++; 
    }

    plaintext[*textLength] = '\0'; // Add null terminator
    fclose(file); // Close the file
}

// Function to encrypt the text using the Hill Cipher
void ecryption(int keyMatrix[9][9], char *plaintext, int textLength, int n, char *ciphertext) {
    for (int i = 0; i < textLength; i += n) { // Loop through the plaintext
        int vector[9] = {0}, result[9] = {0};  // Initialize vectors for matrix multiplication

        // Convert characters to numbers (0-25) 
        for (int j = 0; j < n; j++) {  // Loop through the key matrix
            vector[j] = plaintext[i + j] - 'a'; // Convert to numbers by subtracting 'a'
        }

        // Nested loop for Matrix multiplication
        for (int row = 0; row < n; row++) { 
            for (int col = 0; col < n; col++) {
                result[row] += keyMatrix[row][col] * vector[col];
            }
            result[row] %= 26; // Mod the result by 26
        }

        // Convert back to characters
        for (int j = 0; j < n; j++) {  // Loop through the key matrix
            ciphertext[i + j] = result[j] + 'a'; // Convert back to characters by adding 'a'
        }
    }

    ciphertext[textLength] = '\0'; // Add null terminator
}

// Function to print the key matrix
void printMatrix(int matrix[9][9], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to print formatted text (80 chars per line)
void printOUT(const char *text, int length) {
    for (int i = 0; i < length; i++) { 
        if (i > 0 && i % 80 == 0) {
            printf("\n");
        }
        printf("%c", text[i]);
    }
    printf("\n");
}

/*=============================================================================
| I Peter Petro (pe310601) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/