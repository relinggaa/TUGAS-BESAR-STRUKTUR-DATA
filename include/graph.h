#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define Null nullptr
#define Info(P) (P)->Info
#define Next(P) (P)->Next
#define NextClass(P) (P)->NextClass
#define First(L) (L).First


struct Rute {
    string tujuan;
    int waktuTempuh;
    int biaya;
    Rute* Next;
};


struct Kota {
    string nama;
    Rute* FirstRute;
    Kota* NextClass;
};

struct Graf {
    Kota* First;
};


void tambahKota(Graf& L);
void tambahRuteDariPengguna(Graf& L);
void hapusRute(Graf& L);
void tampilkanRute(const Graf& L);
void dijkstra(Graf& L, const string& start, bool pilihWaktu);

#endif
