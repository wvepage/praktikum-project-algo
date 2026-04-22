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
