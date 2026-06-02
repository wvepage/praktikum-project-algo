<div align="center">
  <h1>Praktikum Algoritma & Struktur Data || Projek Final</h1>
</div>

<div align="center">
  <p>─ <i>Sistem Pengelolaan Koleksi Katalog Buku & Novel Pribadi</i> ─</p>
</div>

## ★ CONTRIBUTORS
**KELOMPOK 8 SI-G**
* **Bintang Fergiawan** - 124250143
* **Yunita Rachmawati** - 124250151

---

## 📚 Tentang Proyek

Proyek ini merupakan implementasi **Sistem Pengelolaan Koleksi Katalog Buku & Novel Pribadi** yang dikembangkan menggunakan bahasa pemrograman C++ berbasis antarmuka Command Line Interface (CLI). Sistem ini dibangun untuk memenuhi tugas akhir praktikum **Algoritma dan Struktur Data (ASD)**.

Sistem dirancang dengan memanfaatkan berbagai struktur data dan algoritma fundamental untuk memastikan penyimpanan data sementara pada memori berjalan secara dinamis dan efisien, serta menyediakan persistensi data agar katalog koleksi yang ditambahkan tidak hilang ketika program dihentikan.

---

## 🔬 Implementasi Materi Praktikum

### 1. Pointer dan Struct (Modul I)
Materi alokasi memori dinamis dan variabel penunjuk alamat diimplementasikan pada:
*   **Deklarasi Tipe Data Bentukan:** `struct Koleksi` digunakan untuk membungkus karakteristik objek buku/novel (judul, penulis, kategori, tahun, rating).
*   **Variabel Pointer:** Penggunaan pointer dengan tanda bintang seperti `Koleksi* prev`, `Koleksi* next`, serta pointer global `Koleksi* head` dan `Koleksi* tail` bertindak sebagai penyimpan alamat memori dari node lain.
*   **Alokasi Dinamis:** Penggunaan kata kunci `new Koleksi` saat menambah data berfungsi untuk memesan ruang memori baru di dalam Heap selama program berjalan.
*   **Dealkokasi Memori:** Instruksi `delete hapus;` pada fungsi penyimpanan data digunakan untuk menghancurkan node dan membebaskan kembali memori agar tidak terjadi kebocoran memori (*memory leak*).

### 2. Doubly Linked List (Modul V & VI)
Program ini menggunakan Linked List Ganda dinamis non-circular sebagai basis penyimpanan struktur datanya di dalam RAM:
*   **Komponen Dua Arah:** Ditunjukkan dengan adanya dua pointer link di dalam struct, yaitu `prev` (menunjuk node sebelum) dan `next` (menunjuk node sesudah).
*   **Pointer Utama:** Menggunakan `head` sebagai penanda ujung depan list dan `tail` sebagai penanda ujung belakang list.
*   **Operasi Sisip Akhir (Insert Last):** Diimplementasikan pada fungsi `tambahKoleksi()` dan secara internal saat `muatDataDariFile()`. Logikanya: jika `head == NULL`, maka `head = tail = baru`. Jika sudah ada isi, maka list akan disambungkan di ujung belakang: `tail->next = baru; baru->prev = tail; tail = baru;`.
*   **Penelusuran (Traversal):** Terlihat pada fungsi `tampilkanRak()` menggunakan pointer bantuan (`Koleksi* bantu = head`) yang bergeser maju melalui perintah `bantu = bantu->next` hingga menemui nilai NULL.

### 3. Operasi File / File Handling (Modul IV)
Materi penyimpanan permanen eksternal (Pointer Style) diimplementasikan pada fungsi `muatDataDariFile()` dan `simpanDataKeFile()`:
*   **Representasi Berkas:** Menggunakan pointer bertipe `FILE* file`.
*   **Membuka & Menutup Berkas:** Fungsi `fopen("katalog_pribadi.txt", "r")` digunakan untuk mode membaca data, `fopen("katalog_pribadi.txt", "w")` untuk mode menulis/menimpa data baru, serta `fclose(file)` untuk menutup aliran data berkas.
*   **Pola Delimiter:** Menggunakan simbol pipe (`|`) sebagai pemisah antardata. Proses pembacaannya memanfaatkan teknik format specifier `%[^|]` pada fungsi `fscanf` agar karakter spasi pada string, seperti judul buku atau nama penulis, tidak terpotong saat dibaca oleh sistem.

### 4. Pengurutan Data / Sorting (Modul III)
Algoritma pengurutan data diimplementasikan di dalam fungsi `urutkanKoleksi()` untuk menyusun koleksi rak:
*   **Algoritma Bubble Sort:** Menggunakan metode penukaran bertetangga secara berulang-ulang (*exchange method*). Pola ini ditandai dengan penggunaan variabel kontrol boolean `ditukar` serta perulangan `while (ptr1->next != lptr)`.
*   **Kondisi Pengurutan Multikriteria:** Pengurutan dibuat dinamis berdasarkan pilihan pengguna:
    *   *Ascending* (Urut Naik) berdasarkan **Abjad Judul** menggunakan operator `>`.
    *   *Descending* (Urut Turun) berdasarkan **Tahun Terbit** menggunakan operator `<`.
    *   *Descending* (Urut Turun) berdasarkan **Rating** menggunakan operator `<`.
*   **Fungsi Swap Data:** Pertukaran isi informasi antar node dilakukan oleh fungsi pembantu `tukarData()` melalui instruksi bawaan `swap()`.

### 5. Pencarian Data / Searching (Modul II)
Algoritma pencarian data diimplementasikan di dalam fungsi `cariKoleksi()`:
*   **Algoritma Sequential Search / Linear Search:** Menggunakan metode penelusuran linier dari satu elemen ke elemen berikutnya secara berurutan.
*   **Logika Pencocokan:** Menggunakan perulangan `while (bantu != NULL)` untuk memeriksa setiap node dari ujung `head`. Jika kondisi `bantu->judul == target` terpenuhi, maka data sukses ditemukan, rincian buku dicetak ke layar, variabel boolean `ketemu` diubah menjadi `true`, dan pencarian dihentikan paksa menggunakan instruksi `break` demi efisiensi proses komputasi.

---

## 💻 Cara Menjalankan Program

1.  Pastikan environment C++ compiler (misal: GCC/MinGW) sudah terinstal di komputer.
2.  Jalankan perintah berikut pada terminal di folder direktori yang sama:
    ```bash
    g++ main.cpp -o KatalogBuku
    ```
3.  Jalankan hasil build program:
    *   Untuk **Windows**: `KatalogBuku.exe` atau `.\KatalogBuku`

---
<div align="center">
  <p><i>Sistem ini ditujukan untuk memenuhi evaluasi Praktikum Algoritma & Struktur Data (ASD) Semester 2.</i></p>
</div>