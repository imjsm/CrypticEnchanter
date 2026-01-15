#!/bin/bash

echo "Select an option:"
echo "1. Encrypt a file"
echo "2. Decrypt a file"
echo "3. Exit"
read choice

case $choice in
  1)
    echo "Enter the file name to encrypt:"
    read file_name
    ./ENCRYPT_file "$file_name"
    ;;
  2)
    echo "Enter the file name to decrypt:"
    read file_name
    echo "Enter the 8-character password:"
    read password
    ./DECRYPT_file "$file_name" "$password"
    ;;
  3)
    exit 0
    ;;
  *)
    echo "Invalid choice"
    ;;
esac
