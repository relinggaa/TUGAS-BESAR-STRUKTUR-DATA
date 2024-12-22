#include "graph.h"


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#ifdef _WIN32
#include <windows.h>  /
#else
#include <unistd.h>
#include <sys/ioctl.h>  /
#endif

using namespace std;

// Mendapatkan lebar terminal
int getTerminalWidth() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}

// Menampilkan teks di tengah
void printCentered(const string& text, int color = 37) {  // Default warna: Putih
    int width = getTerminalWidth();
    int padding = (width - text.length()) / 2;
    if (padding < 0) padding = 0;
    cout << "\033[" << color << "m";  // Warna teks
    cout << string(padding, ' ') << text << "\033[0m" << endl;  // Reset warna
}

// Menampilkan teks "Pilih menu:" di tengah, sejajar dengan input
void printCenteredInput(const string& text, int color = 37) {
    int width = getTerminalWidth();
    int padding = (width - text.length()) / 2;
    if (padding < 0) padding = 0;
    cout << "\033[" << color << "m";  // Warna teks
    cout << string(padding, ' ') << text;  // Cetak teks tanpa newline
    cout << "\033[0m";  // Reset warna
}

// Membersihkan layar
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Header dengan warna
void printHeader() {
    printCentered("+------------------------------------+", 34);
    printCentered("|        SISTEM GRAF PERJALANAN      |", 32);
    printCentered("+------------------------------------+\n", 34);
}

// Menu dengan warna
void printMenu() {
    printCentered("+------------------------------------+", 33);  // Kuning
    printCentered("|               MENU                |", 33);  // Kuning
    printCentered("+------------------------------------+", 33);
    printCentered("| 1. Tambahkan Kota                 |", 36);  // Cyan
    printCentered("| 2. Tambahkan Rute                 |", 36);
    printCentered("| 3. Tampilkan Rute                 |", 36);
    printCentered("| 4. Jalankan Dijkstra              |", 36);
    printCentered("| 5. Tampilkan Kota                 |", 36);
    printCentered("| 6. Hapus Rute                     |", 36);
    printCentered("| 7. Hapus Kota                     |", 36);
    printCentered("| 8. Cari Rute                      |", 36);
    printCentered("| 9. Cari Kota                      |", 36);
    printCentered("| 10. Keluar                        |", 36);
    printCentered("+------------------------------------+\n", 33);
}

int main() {
    Graf L;
    createGraph(L);

    int pilihan;
    do {
        clearScreen();
        printHeader();
        printMenu();
        printCenteredInput("Pilih menu: ", 37);
        cin >> pilihan;

        clearScreen();
        printHeader();

        switch (pilihan) {
            case 1: {
                string nama;
                printCentered("Masukkan nama kota: ", 37);
                cin >> nama;
                tambahKota(L, nama);
                break;
            }
            case 2: {
                string asal, tujuan;
                int waktu, biaya;
                printCentered("Masukkan kota asal: ", 37);
                cin >> asal;
                printCentered("Masukkan kota tujuan: ", 37);
                cin >> tujuan;
                printCentered("Masukkan waktu tempuh/jam: ", 37);
                cin >> waktu;
                printCentered("Masukkan biaya: ", 37);
                cin >> biaya;
                tambahRute(L, asal, tujuan, waktu, biaya);
                break;
            }
            case 3:
                tampilkanRute(L);
                break;
            case 4: {
                printCentered("Daftar Kota yang Tersedia:\n", 36);
                tampilkanKota(L);
                string start;
                printCentered("Masukkan kota asal untuk Dijkstra: ", 37);
                cin >> start;
                printCentered("Pilih jalur:\n1. Tercepat\n2. Termurah\nPilihan: ", 37);
                int mode;
                cin >> mode;
                dijkstra(L, start, mode == 1);
                break;
            }
            case 5:
                tampilkanKota(L);
                break;
            case 6: {
                string asal, tujuan;
                printCentered("Masukkan kota asal: ", 37);
                cin >> asal;
                printCentered("Masukkan kota tujuan: ", 37);
                cin >> tujuan;
                hapusRute(L, asal, tujuan);
                break;
            }
            case 7: {
                string namaKota;
                printCentered("Masukkan nama kota yang ingin dihapus: ", 37);
                cin >> namaKota;
                hapusKota(L, namaKota);
                break;
            }
            case 8: {
                string asal, tujuan;
                printCentered("Masukkan kota asal: ", 37);
                cin >> asal;
                printCentered("Masukkan kota tujuan: ", 37);
                cin >> tujuan;
                cariRute(L, asal, tujuan);
                break;
            }
            case 9: {
                string namaKota;
                printCentered("Masukkan nama kota: ", 37);
                cin >> namaKota;
                cariKota(L, namaKota);
                break;
            }
            case 10:
                printCentered("+------------------------------------+", 31);
                printCentered("|   Keluar dari program. Terima     |", 31);
                printCentered("|   kasih telah menggunakan!        |", 31);
                printCentered("+------------------------------------+\n", 31);
                break;
            default:
                printCentered("+------------------------------------+", 31);
                printCentered("|   Pilihan tidak valid. Coba lagi! |", 31);
                printCentered("+------------------------------------+\n", 31);
        }


        if (pilihan != 10) {
            printCentered("\nTekan Enter untuk kembali ke menu...", 37);
            cin.ignore();
            cin.get();
        }
    } while (pilihan != 10);

    return 0;
}
