/** EL2008 Pemecahan Masalah dengan C 2022/2023
 *   Hari dan Tanggal    : Selasa, 23 Mei 2023
 *   Nama (NIM)          : Mochamad Arif Firdaus
 *   Nama File           : main.c
 *   Deskripsi           : Mendekripsi dengan algoritma RSA
 */

#include <stdio.h>
#include <math.h>

// Fungsi untuk memeriksa apakah suatu bilangan prima
int isPrime(int num) {
    if (num <= 1) {
        return 0;
    }
    
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    
    return 1;
}

// Fungsi untuk mencari bilangan prima p dan q berdasarkan nilai n
void findPrimes(int n, int *p, int *q) {
    for (int i = 2; i <= n / 2; i++) {
        if (isPrime(i) && isPrime(n / i)) {
            *p = i;
            *q = n / i;
            break;
        }
    }
}

// Fungsi untuk menghitung nilai phi (ϕ)
int calculatePhi(int p, int q) {
    return (p - 1) * (q - 1);
}

// Fungsi untuk mencari kunci privat d
int findPrivateKey(int phi, int e) {

    int k = 1;
    int d;

    while (1) {
        d = (k * phi + 1) / e;
        if ((k * phi + 1) % e == 0)
            break;
        k++;
    }

    return d;
}

// Fungsi untuk mendekripsi pesan menggunakan kunci privat d
void decryptMessage(int *encryptedData, int dataSize, int d, int n) {
    for (int i = 0; i < dataSize; i++) {
        int decryptedValue = 1;
        int c = encryptedData[i];

        // Menggunakan algoritma eksponensiasi modular untuk mendekripsi
        for (int j = 0; j < d; j++) {
            decryptedValue = (decryptedValue ^ c) % n;
        }

        printf("%d ", decryptedValue);
    }
    printf("\n");
}

int main() {
    int n = 253; // Nilai n
    int e = 7;   // Nilai e

    int p, q;   
    findPrimes(n, &p, &q);

    int phi = calculatePhi(p, q);

    int encryptedData[] = {43, 101, 176, 23, 94};
    int dataSize = sizeof(encryptedData) / sizeof(encryptedData[0]);

    printf("Encrypted Message: ");
    for (int i = 0; i < dataSize; i++) {
        printf("%d ", encryptedData[i]);
    }
    printf("\n");

    // Mencetak kunci publik (n, e), p, q, dan phi
    printf("Public Key (n, e): (%d, %d)\n", n, e);
    printf("p: %d\n", p);
    printf("q: %d\n", q);
    printf("phi: %d\n", phi);

    // Mencari kunci privat d
    int d = findPrivateKey(phi, e);
    printf("Private Key (d): %d\n", d);

    // Mendekripsi pesan menggunakan kunci privat (d, n)
    printf("Decrypted Message: ");
    decryptMessage(encryptedData, dataSize, d, n);

    return 0;
}
