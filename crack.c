#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hash = md5(plaintext, strlen(plaintext));
    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");
    if (!hash) {
        printf("Failed to create MD5 hash for %s\n", plaintext);
        free(hash);
        exit(1);
    }
    // Loop through the hash file, one line at a time.
    char line[HASH_LEN];
    while (fgets(line, sizeof(line), hashFile)) {
    // Attempt to match the hash from the file to the
    // hash of the plaintext.
    char *nl = strchr(line, '\n');
    if (nl) *nl = '\0';

    if(strcmp(line, hash) == 0) {
        fclose(hashFile);
        return hash;
        free(hash);
    }
    // If there is a match, you'll return the hash.
    // If not, return NULL.
    }
    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?
    fclose(hashFile);
    free(hash);

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    char *found = tryWord("hello", "hashes00.txt");
    printf("%s %s\n", found, "hello");


    // Open the dictionary file for reading.
    FILE *dict = fopen(argv[2], "r");
    if (!dict) {
        printf("Could not open %s\n", argv[2]);
        exit(1);
    }
    // // For each dictionary word, pass it to tryWord, which
    // // will attempt to match it against the hashes in the hash_file.
    char word[PASS_LEN];
    int count = 0;
    while(fgets(word, 256, dict) != NULL) {
    // // If we got a match, display the hash and the word. For example:
    // //   5d41402abc4b2a76b9719d911017c592 hello
    char *nl = strchr(word, '\n');
    if (nl) *nl = '\0';

    char *found = tryWord(word, argv[1]);
    if(found) {
        printf("%s %s\n", found, word);
        count++;
        free(found);
    }
    }
    
    // Close the dictionary file.
    fclose(dict);

    // Display the number of hashes that were cracked.
    printf("%d hashes cracked!", count);
    
    // Free up any malloc'd memory?
    free(found);
}

