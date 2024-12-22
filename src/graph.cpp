#include "graph.h"


#include <algorithm>

// Membuat graph baru
void createGraph(Graf& L) {
    first(L) = nullptr;
}

// Alokasi kota baru
Kota* allocateKota(const string& nama) {
    Kota* P = new Kota;
    P->nama = nama;
    P->firstRute = nullptr;
    P->next = nullptr;
    return P;
}
void tampilkanKota(const Graf& L) {
    cout << "\nDaftar Kota:\n";
    Kota* kota = first(L);
    if (kota == nullptr) {
        cout << "Tidak ada kota dalam graf.\n";
        return;
    }
    while (kota != nullptr) {
        cout << "  - " << kota->nama << "\n";
        kota = kota->next;
    }
}
void hapusRute(Graf& L, const string& asal, const string& tujuan) {
    Kota* kotaAsal = first(L);
    while (kotaAsal != nullptr && kotaAsal->nama != asal) {
        kotaAsal = kotaAsal->next;
    }

    if (kotaAsal == nullptr) {
        cout << "Kota asal tidak ditemukan!\n";
        return;
    }

    Rute* prevRute = nullptr;
    Rute* currRute = kotaAsal->firstRute;

    while (currRute != nullptr && currRute->tujuan != tujuan) {
        prevRute = currRute;
        currRute = currRute->nextRute;
    }

    if (currRute == nullptr) {
        cout << "Rute tidak ditemukan!\n";
        return;
    }

    if (prevRute == nullptr) {
        kotaAsal->firstRute = currRute->nextRute;
    } else {
        prevRute->nextRute = currRute->nextRute;
    }

    delete currRute;
    cout << "Rute dari " << asal << " ke " << tujuan << " berhasil dihapus.\n";
}

// Alokasi rute baru
Rute* allocateRute(const string& tujuan, int waktu, int biaya) {
    Rute* P = new Rute;
    P->tujuan = tujuan;
    P->waktuTempuh = waktu;
    P->biaya = biaya;
    P->nextRute = nullptr;
    return P;
}

// Menambahkan kota ke graph
void tambahKota(Graf& L, const string& nama) {
    Kota* P = allocateKota(nama);
    P->next = first(L);
    first(L) = P;
}

// Menambahkan rute antar kota
void tambahRute(Graf& L, const string& asal, const string& tujuan, int waktu, int biaya) {
    Kota* kotaAsal = first(L);
    while (kotaAsal != nullptr && kotaAsal->nama != asal) {
        kotaAsal = kotaAsal->next;
    }

    if (kotaAsal == nullptr) {
        cout << "Kota asal tidak ditemukan!\n";
        return;
    }

    Rute* ruteBaru = allocateRute(tujuan, waktu, biaya);
    ruteBaru->nextRute = kotaAsal->firstRute;
    kotaAsal->firstRute = ruteBaru;
}

// Menampilkan semua rute
void tampilkanRute(const Graf& L) {
    Kota* kota = first(L);
    while (kota != nullptr) {
        cout << "Kota: " << kota->nama << "\n";
        Rute* rute = kota->firstRute;
        while (rute != nullptr) {
            cout << "  Tujuan: " << rute->tujuan << ", Waktu: " << rute->waktuTempuh
                 << " jam, Biaya: " << rute->biaya << " Rp\n";
            rute = rute->nextRute;
        }
        kota = kota->next;
    }
}
void hapusKota(Graf& L, const string& namaKota) {
    Kota* prevKota = nullptr;
    Kota* currKota = first(L);

    // Cari kota yang ingin dihapus
    while (currKota != nullptr && currKota->nama != namaKota) {
        prevKota = currKota;
        currKota = currKota->next;
    }

    if (currKota == nullptr) {
        cout << "Kota tidak ditemukan!\n";
        return;
    }

    // Hapus semua rute dari kota tersebut
    Rute* rute = currKota->firstRute;
    while (rute != nullptr) {
        Rute* temp = rute;
        rute = rute->nextRute;
        delete temp;
    }

    // Hapus referensi kota dalam graf
    if (prevKota == nullptr) {
        first(L) = currKota->next;
    } else {
        prevKota->next = currKota->next;
    }

    delete currKota;

    // Hapus semua rute menuju kota yang dihapus
    Kota* kota = first(L);
    while (kota != nullptr) {
        Rute* prevRute = nullptr;
        Rute* currRute = kota->firstRute;

        while (currRute != nullptr) {
            if (currRute->tujuan == namaKota) {
                if (prevRute == nullptr) {
                    kota->firstRute = currRute->nextRute;
                } else {
                    prevRute->nextRute = currRute->nextRute;
                }
                delete currRute;
                break; // Pindah ke rute berikutnya
            }
            prevRute = currRute;
            currRute = currRute->nextRute;
        }
        kota = kota->next;
    }

    cout << "Kota " << namaKota << " berhasil dihapus.\n";
}
bool cariRute(const Graf& L, const string& asal, const string& tujuan) {
    Kota* kotaAsal = first(L);
    while (kotaAsal != nullptr && kotaAsal->nama != asal) {
        kotaAsal = kotaAsal->next;
    }

    if (kotaAsal == nullptr) {
        cout << "Kota asal tidak ditemukan!\n";
        return false;
    }

    Rute* rute = kotaAsal->firstRute;
    while (rute != nullptr) {
        if (rute->tujuan == tujuan) {
            cout << "Rute ditemukan: " << asal << " -> " << tujuan
                 << ", Waktu: " << rute->waktuTempuh
                 << " jam, Biaya: " << rute->biaya << " Rp\n";
            return true;
        }
        rute = rute->nextRute;
    }

    cout << "Rute dari " << asal << " ke " << tujuan << " tidak ditemukan.\n";
    return false;
}
bool cariKota(const Graf& L, const string& namaKota) {
    Kota* kota = first(L);
    while (kota != nullptr) {
        if (kota->nama == namaKota) {
            cout << "Kota " << namaKota << " ditemukan dalam graf.\n";
            return true;
        }
        kota = kota->next;
    }
    cout << "Kota " << namaKota << " tidak ditemukan dalam graf.\n";
    return false;
}

// Algoritma Dijkstra
void dijkstra(const Graf& L, const string& start, bool pilihWaktu) {
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    Kota* kota = first(L);
    while (kota != nullptr) {
        dist[kota->nama] = numeric_limits<int>::max();
        prev[kota->nama] = "";
        kota = kota->next;
    }

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto top = pq.top();
        int currentDist = top.first;
        string currentNama = top.second;
        pq.pop();

        if (currentDist > dist[currentNama]) continue;

        Kota* currKota = first(L);
        while (currKota != nullptr && currKota->nama != currentNama) {
            currKota = currKota->next;
        }

        if (currKota == nullptr) continue;

        Rute* rute = currKota->firstRute;
        while (rute != nullptr) {
            int jarakBaru = dist[currentNama] + (pilihWaktu ? rute->waktuTempuh : rute->biaya);

            if (jarakBaru < dist[rute->tujuan]) {
                dist[rute->tujuan] = jarakBaru;
                prev[rute->tujuan] = currentNama;
                pq.push({jarakBaru, rute->tujuan});
            }
            rute = rute->nextRute;
        }
    }

    // Salin dan urutkan hasil berdasarkan jarak
    vector<pair<string, int>> sortedDist(dist.begin(), dist.end());
    sort(sortedDist.begin(), sortedDist.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second; // Urutkan berdasarkan jarak
    });

    cout << "\n**Jalur " << (pilihWaktu ? "Tercepat" : "Termurah") << " dari " << start << " ke kota lain:**\n";
    for (const auto& [kota, jarak] : sortedDist) {
        if (jarak == numeric_limits<int>::max()) {
            cout << "  " << kota << " : Tidak terjangkau\n";
        } else {
            string pathStr = kota;
            string prevKota = prev[kota];
            while (!prevKota.empty()) {
                pathStr = prevKota + " -> " + pathStr;
                prevKota = prev[prevKota];
            }
            cout << "  " << start << " -> " << pathStr << " : " << jarak << (pilihWaktu ? " jam" : " Rp") << "\n";
        }
    }
}

