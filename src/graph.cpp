#include "graph.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

void tambahKota(Graf& L) {
    Kota* kotaBaru = new Kota;
    cout << "Masukkan nama kota: ";
    cin >> kotaBaru->nama;
    kotaBaru->FirstRute = Null;
    kotaBaru->NextClass = First(L);
    First(L) = kotaBaru;
}

void tambahRuteDariPengguna(Graf& L) {
    string asal, tujuan;
    int waktu, biaya;

    cout << "Masukkan kota asal: ";
    cin >> asal;
    cout << "Masukkan kota tujuan: ";
    cin >> tujuan;
    cout << "Masukkan waktu tempuh: ";
    cin >> waktu;
    cout << "Masukkan biaya: ";
    cin >> biaya;

    Kota* kotaAsal = First(L);
    while (kotaAsal != nullptr && kotaAsal->nama != asal) {
        kotaAsal = kotaAsal->NextClass;
    }

    if (kotaAsal == nullptr) {
        cout << "Kota asal tidak ditemukan!\n";
        return;
    }

    Rute* ruteBaru = new Rute;
    ruteBaru->tujuan = tujuan;
    ruteBaru->waktuTempuh = waktu;
    ruteBaru->biaya = biaya;
    ruteBaru->Next = kotaAsal->FirstRute;
    kotaAsal->FirstRute = ruteBaru;
}


void hapusRute(Graf& L) {
    string asal, tujuan;
    cout << "Masukkan kota asal: ";
    cin >> asal;
    cout << "Masukkan kota tujuan: ";
    cin >> tujuan;

    Kota* kotaAsal = First(L);
    while (kotaAsal != nullptr && kotaAsal->nama != asal) {
        kotaAsal = kotaAsal->NextClass;
    }

    if (kotaAsal == nullptr) {
        cout << "Kota asal tidak ditemukan!\n";
        return;
    }

    Rute* rute = kotaAsal->FirstRute;
    Rute* prevRute = nullptr;
    while (rute != nullptr && rute->tujuan != tujuan) {
        prevRute = rute;
        rute = rute->Next;
    }

    if (rute == nullptr) {
        cout << "Rute tidak ditemukan!\n";
        return;
    }

    if (prevRute == nullptr) {
        kotaAsal->FirstRute = rute->Next;
    } else {
        prevRute->Next = rute->Next;
    }

    delete rute;
}


void tampilkanRute(const Graf& L) {
    Kota* kota = First(L);
    while (kota != nullptr) {
        cout << "Kota: " << kota->nama << "\n";
        Rute* rute = kota->FirstRute;
        while (rute != nullptr) {
            cout << "  Tujuan: " << rute->tujuan << ", Waktu: " << rute->waktuTempuh << " jam, Biaya: " << rute->biaya << " Rp\n";
            rute = rute->Next;
        }
        kota = kota->NextClass;
    }
}


struct Node {
    string nama;
    int jarak;
    bool operator>(const Node& other) const {
        return jarak > other.jarak;
    }
};

void dijkstra(Graf& L, const string& start, bool pilihWaktu) {
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;
    priority_queue<Node, vector<Node>, greater<Node>> pq;


    Kota* kota = First(L);
    while (kota != nullptr) {
        dist[kota->nama] = numeric_limits<int>::max();
        prev[kota->nama] = "";
        kota = kota->NextClass;
    }


    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.jarak > dist[current.nama]) continue;


        Kota* currKota = First(L);
        while (currKota != nullptr && currKota->nama != current.nama) {
            currKota = currKota->NextClass;
        }

        if (currKota == nullptr) continue;

        Rute* rute = currKota->FirstRute;
        while (rute != nullptr) {

            int jarakBaru = dist[current.nama] + (pilihWaktu ? rute->waktuTempuh : rute->biaya);


            if (jarakBaru < dist[rute->tujuan]) {
                dist[rute->tujuan] = jarakBaru;
                prev[rute->tujuan] = current.nama;
                pq.push({rute->tujuan, jarakBaru});
            }
            rute = rute->Next;
        }
    }

    cout << "\n**Jalur " << (pilihWaktu ? "Tercepat" : "Termurah") << " dari " << start << " ke kota lain:**\n";
    for (const auto& [kota, jarak] : dist) {
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

