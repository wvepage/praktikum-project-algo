#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>

using namespace std;

struct Koleksi {
    string judul;
    string penulis;
    string kategori; // "Buku" atau "Novel"
    int tahunTerbit;
    float rating;
    
    Koleksi* prev;
    Koleksi* next;
};

// Pointer Global
Koleksi* head = NULL;
Koleksi* tail = NULL;

void muatDataDariFile() {
    FILE* file = fopen("katalog_pribadi.txt", "r");
    if (file == NULL) return; 

    char bufferJudul[200], bufferPenulis[200], bufferKategori[50];
    int thn;
    float rtg;

    // Parsing data dengan pemisah delimiter |
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%f\n", bufferJudul, bufferPenulis, bufferKategori, &thn, &rtg) == 5) {
        
        Koleksi* baru = new Koleksi;
        baru->judul = bufferJudul;
        baru->penulis = bufferPenulis;
        baru->kategori = bufferKategori;
        baru->tahunTerbit = thn;
        baru->rating = rtg;
        baru->prev = NULL;
        baru->next = NULL;

        // Sisip Akhir (Insert Last)
        if (head == NULL) {
            head = tail = baru;
        } else {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
        }
    }
    fclose(file);
}

void simpanDataKeFile() {
    FILE* file = fopen("katalog_pribadi.txt", "w");
    if (file == NULL) {
        cout << "\n[!] Error: Tidak dapat membuat file penyimpanan.\n";
        return;
    }

    Koleksi* bantu = head;
    
    // Traversal untuk menulis data
    while (bantu != NULL) {
        fprintf(file, "%s|%s|%s|%d|%.1f\n", 
                bantu->judul.c_str(), 
                bantu->penulis.c_str(), 
                bantu->kategori.c_str(), 
                bantu->tahunTerbit, 
                bantu->rating);
            
        // Mencegah Memory Leak
        Koleksi* hapus = bantu;
        bantu = bantu->next;
        delete hapus; 
    }
    fclose(file);
}
