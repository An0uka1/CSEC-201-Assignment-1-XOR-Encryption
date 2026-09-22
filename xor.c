#include <stdio.h>
#include <string.h>

void xorEncryptDecrypt(char *data, char *key) {
    int keyLen = strlen(key);
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= key[i % keyLen];
    }
}

int main() {
    char choice[10], message[256], filename[256], key[256];
    
    printf("Do you want to encrypt or decrypt? ");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';
    
    if (strcmp(choice, "encrypt") == 0) {
        printf("Enter the string to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline character
        printf("Enter the filename to save encrypted data: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';
        printf("Enter the key: ");
        scanf("%s", key);
        
        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return 1;
        }
        
        xorEncryptDecrypt(message, key);
        fprintf(file, "%s", message);
        fclose(file);
    } else if (strcmp(choice, "decrypt") == 0) {
        printf("Enter the filename to read encrypted data: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';
        printf("Enter the key: ");
        scanf("%s", key);
        
        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Error opening file for reading.\n");
            return 1;
        }
        
        fgets(message, sizeof(message), file);
        fclose(file);
        
        xorEncryptDecrypt(message, key);
        printf("Decrypted message: %s\n", message);
    } else {
        printf("Invalid choice. Please enter 'encrypt' or 'decrypt'.\n");
        return 1;
    }
    
    return 0;
}