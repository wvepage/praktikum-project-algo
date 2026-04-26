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

void tukarData(Koleksi* a, Koleksi* b) {
    swap(a->judul, b->judul);
    swap(a->penulis, b->penulis);
    swap(a->kategori, b->kategori);
    swap(a->tahunTerbit, b->tahunTerbit);
    swap(a->rating, b->rating);
}

void urutkanKoleksi() {
    if (head == NULL || head->next == NULL) return;

    bersihkanLayar();
    cetakGarisGanda();
    cout << "  URUTKAN RAK BUKU\n";
    cetakGarisGanda();
    cout << "1. Berdasarkan Abjad Judul (A-Z)\n";
    cout << "2. Berdasarkan Tahun Terbit (Terbaru)\n";
    cout << "3. Berdasarkan Rating (Tertinggi)\n";
    cout << "Pilih kriteria: ";
    
    int kriteria;
    cin >> kriteria;

    bool ditukar;
    Koleksi* ptr1;
    Koleksi* lptr = NULL;

    // Algoritma Bubble Sort
    do {
        ditukar = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            bool kondisiTukar = false;
            if (kriteria == 1 && ptr1->judul > ptr1->next->judul) kondisiTukar = true;
            else if (kriteria == 2 && ptr1->tahunTerbit < ptr1->next->tahunTerbit) kondisiTukar = true;
            else if (kriteria == 3 && ptr1->rating < ptr1->next->rating) kondisiTukar = true;

            if (kondisiTukar) {
                tukarData(ptr1, ptr1->next);
                ditukar = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (ditukar);

    cout << "\n[!] Rak berhasil dirapikan!\n";
    tekanEnter();
}

void cariKoleksi() {
    bersihkanLayar();
    cetakGarisGanda();
    cout << "  CARI KOLEKSI BUKU/NOVEL\n";
    cetakGarisGanda();

    string target;
    cout << "Masukkan Judul yang dicari: ";
    cin >> ws; getline(cin, target);

    Koleksi* bantu = head;
    bool ketemu = false;

    // Algoritma Sequential Search
    while (bantu != NULL) {
        if (bantu->judul == target) {
            cout << "\n[!] Data Ditemukan!\n";
            cetakGarisTabel();
            cout << "| " << left << setw(28) << bantu->judul.substr(0, 28)
                << " | " << setw(20) << bantu->penulis.substr(0, 20)
                << " | " << setw(8) << bantu->kategori
                << " | " << setw(6) << bantu->tahunTerbit
                << " | " << setw(11) << fixed << setprecision(1) << bantu->rating << " |\n";
            cetakGarisTabel();
            ketemu = true;
            break;
        }
        bantu = bantu->next;
    }

    if (!ketemu) cout << "\n[!] Literatur tidak ditemukan di dalam rak.\n";
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
