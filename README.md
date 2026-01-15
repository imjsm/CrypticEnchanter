# CrypticEnchanter

# 🔐 SecureShield

![C](https://img.shields.io/badge/Language-C-blue)
![Linux](https://img.shields.io/badge/Platform-Linux-important)
![Crypto](https://img.shields.io/badge/Crypto-AES--256%20%7C%20SHA--256-success)
![Status](https://img.shields.io/badge/Project-Academic-green)
![License](https://img.shields.io/badge/License-Academic-lightgrey)

**SecureShield** is a Linux-based file encryption & decryption system that secures files using **AES-256-CBC encryption** with **SHA-256 key derivation**, providing strong security with minimal storage overhead.

---

## 🚀 Highlights

- 🔐 AES-256-CBC encryption
- 🧂 SHA-256 based key & IV derivation
- 🔑 Random 8-character password generation
- ♻️ In-place file encryption (no duplicate files)
- 🖥️ Simple CLI using Bash
- ⚡ Efficient for files up to 10MB+

---

## 🧠 How It Works

### Encryption
1. User selects a file  
2. System generates a random password  
3. SHA-256 derives AES key & IV  
4. File is encrypted and overwritten  

### Decryption
1. User provides encrypted file & password  
2. Key regenerated using SHA-256  
3. File is decrypted back to original form  

📄 *Detailed system design is available in the project report.*

---

## 🗂️ Project Structure
SecureShield/
├── ENCRYPT_file.c
├── DECRYPT_file.c
├── CrypticEnchanter.sh
├── README.md
└── Project_Report.pdf

---

## ⚙️ Setup & Run

### Install Dependencies
```bash
sudo apt install openssl libssl-dev gcc
Compile
bash

gcc ENCRYPT_file.c -o ENCRYPT_file -lcrypto
gcc DECRYPT_file.c -o DECRYPT_file -lcrypto

Run
bash

chmod +x CrypticEnchanter.sh
./CrypticEnchanter.sh
```
##🧪 Tested & Verified
Supports text, image, PDF & media files

Integrity verified using sha256sum

Linear performance scaling with file size

##📸 Screenshots

![Menu Screenshot](screenshots/menu.png)
![Encryption Output](screenshots/encryption.png)
![Decryption Output](screenshots/decryption.png)



##🔮 Future Improvements
AES-GCM (authenticated encryption)

PBKDF2 key derivation

Chunk-based encryption

Multithreading support

