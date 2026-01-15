#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

#define AES_BLOCK_SIZE 16

void decrypt_file(const char *filename, const char *password) {
    FILE *input_file = fopen(filename, "rb");
    if (input_file == NULL) {
        perror("Unable to open file");
        return;
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *encrypted_data = (unsigned char *)malloc(file_size);
    fread(encrypted_data, 1, file_size, input_file);
    fclose(input_file);

    unsigned char aes_key[32];
    unsigned char aes_iv[AES_BLOCK_SIZE];

    // Generate AES key and IV using the password
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, (unsigned char *)password, strlen(password), 1, aes_key, aes_iv);

    // Allocate memory for decrypted file
    unsigned char *decrypted_data = (unsigned char *)malloc(file_size);
    int decrypted_data_len;

    // Perform AES decryption
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);
    EVP_DecryptUpdate(ctx, decrypted_data, &decrypted_data_len, encrypted_data, file_size);
    int final_len;
    EVP_DecryptFinal_ex(ctx, decrypted_data + decrypted_data_len, &final_len);
    decrypted_data_len += final_len;
    EVP_CIPHER_CTX_free(ctx);

    // Open the original file to overwrite it with decrypted data
    input_file = fopen(filename, "wb");
    if (input_file == NULL) {
        perror("Unable to open file for writing decrypted data");
        return;
    }

    // Save the decrypted data back to the original file
    fwrite(decrypted_data, 1, decrypted_data_len, input_file);
    fclose(input_file);

    // Cleanup
    free(encrypted_data);
    free(decrypted_data);

    printf("File decrypted successfully and saved back to the original file '%s'.\n", filename);
}

int main() {
    char filename[256];
    printf("Enter the file name to decrypt: ");
    scanf("%s", filename);

    char password[9];
    printf("Enter the 8-character password: ");
    scanf("%s", password);

    decrypt_file(filename, password);
    return 0;
}
