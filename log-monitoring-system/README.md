# Log Monitoring System — Struktur Data

Sistem monitoring dan log aktivitas aplikasi sederhana untuk membandingkan performa struktur data.

## Struktur Data yang Dibandingkan

| Struktur | Insert | Search by Level/Module | Search by Time Range | Delete Old |
|---|---|---|---|---|
| `vector` | O(1) amortized | O(n) | O(n) | O(n) |
| `unordered_map` | O(1) avg | **O(1) avg** | N/A | N/A |
| `std::map` (BST) | O(log n) | N/A | **O(log n)** | **O(log n)** |

## Cara Menjalankan (GitHub Codespace / Linux)

```bash
# 1. paste pada terminal untuk dijalankan
make && ./bin/logmon
# pilih menu 9 → masukkan jumlah log (contoh: 100000)

# 2. untuk operasi & benchmark
./bin/logmon
# pilih menu 8 untuk melihat perbandingan waktu eksekusi
```

## Struktur Folder

```
src/
├── main.cpp              ← menu utama
├── log.h                 ← definisi struct Log
├── file_handler.h/cpp    ← baca/tulis CSV
├── generate_data.h/cpp   ← pembuat data dummy
├── benchmark.h/cpp       ← perbandingan performa
└── ds/
    ├── vector_store      ← Struktur 1: baseline
    ├── hashmap_store     ← Struktur 2: cepat by level/module
    └── bst_store         ← Struktur 3: cepat by waktu
data/
└── logs.csv              ← dataset log
```

## Pembagian Tugas

| Anggota | Bagian |
|---|---|
| 1 | `log.h`, `file_handler`, `main.cpp` |
| 2 | `vector_store` |
| 3 | `hashmap_store` |
| 4 | `bst_store` |
| 5 | `benchmark`, dataset, laporan |
