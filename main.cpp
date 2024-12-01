#include <iostream>
#include "graph.h"
using namespace std;

int main() {
    Graf L;
    First(L) = nullptr;

    int pilihan;
    bool pilihWaktu = true;
    do {
        cout << "\nMenu: \n";
        cout << "1. Tambahkan Kota\n";
        cout << "2. Tambahkan Rute\n";
        cout << "3. Hapus Rute\n";
        cout << "4. Tampilkan Rute\n";
        cout << "5. Jalankan Dijkstra\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahKota(L);
                break;
            case 2:
                tambahRuteDariPengguna(L);
                break;
            case 3:
                hapusRute(L);
                break;
            case 4:
                tampilkanRute(L);
                break;
            case 5:
                cout << "Masukkan kota asal untuk Dijkstra: ";
                string asal;
                cin >> asal;
                dijkstra(L, asal, pilihWaktu);
                break;
        }
    } while (pilihan != 6);

    return 0;
}
