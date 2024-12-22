#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <limits>
#include <queue>
#include <unordered_map>

using namespace std;

#define first(L) (L).first
#define info(P) (P)->info
#define nextKota(P) (P)->next
#define nextRute(P) (P)->nextRute

struct Rute {
    string tujuan;
    int waktuTempuh;
    int biaya;
    Rute* nextRute;
};

struct Kota {
    string nama;
    Rute* firstRute;
    Kota* next;
};

struct Graf {
    Kota* first;
};

void createGraph(Graf& L);
Kota* allocateKota(const string& nama);
Rute* allocateRute(const string& tujuan, int waktu, int biaya);
void tambahKota(Graf& L, const string& nama);
void tambahRute(Graf& L, const string& asal, const string& tujuan, int waktu, int biaya);
void tampilkanRute(const Graf& L);
void dijkstra(const Graf& L, const string& start, bool pilihWaktu);
void tampilkanKota(const Graf& L);
void hapusRute(Graf& L, const string& asal, const string& tujuan);
void hapusKota(Graf& L, const string& namaKota);
bool cariRute(const Graf& L, const string& asal, const string& tujuan);
bool cariKota(const Graf& L, const string& namaKota);


#endif
