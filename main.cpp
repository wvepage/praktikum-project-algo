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

void bersihkanLayar() {
    system("cls");
}

void tekanEnter() {
    cout << "\n[ Tekan ENTER untuk kembali ke Menu Utama ]";
    cin.ignore();
    cin.get();
}

void cetakGarisGanda() {
    cout << setfill('=') << setw(90) << "=" << setfill(' ') << endl;
}

void cetakGarisTabel() {
    cout    << "+" << string(30, '-') << "+" << string(22, '-') 
            << "+" << string(10, '-') << "+" << string(8, '-') 
            << "+" << string(13, '-') << "+\n";
}

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

void tambahKoleksi() {
    bersihkanLayar();
    Koleksi* baru = new Koleksi;
    baru->prev = NULL;
    baru->next = NULL;

    cetakGarisGanda();
    cout << "  TAMBAH KOLEKSI LITERATUR BARU\n";
    cetakGarisGanda();

    cout << "Judul Buku/Novel : ";
    cin >> ws; getline(cin, baru->judul);
    
    cout << "Nama Penulis     : ";
    getline(cin, baru->penulis);
    
    int pilKat;
	do {
		cout << "Kategori [ (1) Buku | (2) Novel ] : ";
        cin >> pilKat;
    } while (pilKat < 1 || pilKat > 2);
    baru->kategori = (pilKat == 1) ? "Buku" : "Novel";

    cout << "Tahun Terbit     : ";
    cin >> baru->tahunTerbit;
    
    do {
        cout << "Rating Pribadi (1.0 - 5.0)    : ";
        cin >> baru->rating;
    } while (baru->rating < 1.0 || baru->rating > 5.0);

    // Otomatis Sisip di Akhir
    if (head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
    
    cout << "\n[!] Data berhasil ditambahkan ke rak!\n";
    cetakGarisGanda();
    tekanEnter();
}

void tampilkanRak(string filter) {
    bersihkanLayar();
    cetakGarisGanda();
    cout << "  DAFTAR KOLEKSI (" << filter << ")\n";
    cetakGarisGanda();

    if (head == NULL) {
        cout << "\n[!] Rak masih kosong.\n";
        tekanEnter();
        return;
    }

    cetakGarisTabel();
    cout << "| " << left << setw(28) << "Judul Literatur"
        << " | " << setw(20) << "Penulis"
        << " | " << setw(8) << "Kategori"
        << " | " << setw(6) << "Tahun"
        << " | " << setw(11) << "Rating/5.0" << " |\n";
    cetakGarisTabel();

    Koleksi* bantu = head;
    while (bantu != NULL) {
        if (filter == "Semua" || bantu->kategori == filter) {
            cout << "| " << left << setw(28) << bantu->judul.substr(0, 28)
                << " | " << setw(20) << bantu->penulis.substr(0, 20)
                << " | " << setw(8) << bantu->kategori
                << " | " << setw(6) << bantu->tahunTerbit
                << " | " << setw(11) << fixed << setprecision(1) << bantu->rating << " |\n";
        }
        bantu = bantu->next;
    }
    cetakGarisTabel();
    tekanEnter();
}

int main() {
    muatDataDariFile();   // Muat data awal dari file .txt

    int pilihan;
    do {
        bersihkanLayar();
        cetakGarisGanda();
        cout << "      SISTEM PENGELOLAAN KOLEKSI BUKU & NOVEL PRIBADI\n";
        cetakGarisGanda();
        cout << "	[1] Tambah Koleksi Baru\n";
        cout << "	[2] Tampilkan Semua Koleksi\n";
        cout << "	[3] Tampilkan Khusus Novel\n";
        cout << "	[4] Tampilkan Khusus Buku\n";
        cout << "	[5] Urutkan Rak (Sorting)\n";
        cout << "	[6] Cari Koleksi (Searching)\n";
        cout << "	[0] Simpan & Keluar\n";
        cetakGarisGanda();
        cout << ">> Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahKoleksi(); break;
            case 2: tampilkanRak("Semua"); break;
            case 3: tampilkanRak("Novel"); break;
            case 4: tampilkanRak("Buku"); break;
            case 0:
                cout << "\n[!] Menyimpan data...";
                cout << "\nTerimakasih.. Sampai Jumpa!\n";
                simpanDataKeFile();
                break;
            default:
                cout << "\n[!] Pilihan tidak valid!\n";
                tekanEnter();
         }
    } while (pilihan != 0);

    return 0;
}


