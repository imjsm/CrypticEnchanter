#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

#define AES_BLOCK_SIZE 16

/*void generate_random_password(char *password) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 8; i++) {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[8] = '\0';  // Null-terminate the string
}*/

#include <time.h>

void generate_random_password(char *password) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Seed the random number generator only once
    srand(time(NULL));

    for (int i = 0; i < 8; i++) {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[8] = '\0';  // Null-terminate the string
}


void encrypt_file(const char *filename, const char *password) {
    FILE *input_file = fopen(filename, "rb");
    if (input_file == NULL) {
        perror("Unable to open file");
        return;
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *file_data = (unsigned char *)malloc(file_size);
    fread(file_data, 1, file_size, input_file);
    fclose(input_file);

    unsigned char aes_key[32];
    unsigned char aes_iv[AES_BLOCK_SIZE];

    // Generate AES key and IV using the password
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, (unsigned char *)password, strlen(password), 1, aes_key, aes_iv);

    // Allocate memory for encrypted file
    unsigned char *encrypted_data = (unsigned char *)malloc(file_size + AES_BLOCK_SIZE);
    int encrypted_data_len;

    // Perform AES encryption
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);
    EVP_EncryptUpdate(ctx, encrypted_data, &encrypted_data_len, file_data, file_size);
    int final_len;
    EVP_EncryptFinal_ex(ctx, encrypted_data + encrypted_data_len, &final_len);
    encrypted_data_len += final_len;
    EVP_CIPHER_CTX_free(ctx);

    // Overwrite the original file with the encrypted data
    FILE *output_file = fopen(filename, "wb");
    fwrite(encrypted_data, 1, encrypted_data_len, output_file);
    fclose(output_file);

    printf("File encrypted successfully. Encrypted data saved to '%s'.\n", filename);
}

int main() {
    char password[9];
    generate_random_password(password);
    printf("Generated password: %s\n", password);
    printf("Please save this password for future use.\n");

    char filename[256];
    printf("Enter the file name to encrypt: ");
    scanf("%s", filename);

    encrypt_file(filename, password);
    return 0;
}
