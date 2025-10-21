🛰️ SYSTEM ZARZĄDZANIA KATALOGIEM SATELITÓW W C++
Ten projekt to konsolowa aplikacja opracowana w języku C++ do efektywnego zarządzania danymi o satelitach. Implementacja ściśle wykorzystuje paradygmat Programowania Obiektowego (OOP), w tym dziedziczenie i polimorfizm.

🚀 KLUCZOWE ASPEKTY OOP I ARCHITEKTURA
Wykorzystanie nowoczesnego C++ do stworzenia hierarchii klas:

Klasa Bazowa Satelita: Przechowuje podstawowe parametry (nazwa, orbita, prędkość).

Klasa Pochodna SatelitaKomunikacyjny: Dziedziczy cechy bazowe i dodaje unikalny atrybut: częstotliwość komunikacji.

Polimorfizm: Zaimplementowany poprzez metodę wirtualną wyswietlInfo(), zapewniającą poprawne wyświetlanie różnych typów satelitów.

💾 ZARZĄDZANIE DANYMI I PAMIĘCIĄ
### TRWAŁOŚĆ I PLIKI

Funkcje zapiszDoPliku i wczytajZPliku umożliwiają pełną trwałość danych, zapisując i odtwarzając cały katalog z plików tekstowych.

### INTELIGENTNE WSKAŹNIKI

Bezpieczne i efektywne zarządzanie dynamiczną pamięcią dzięki zastosowaniu std::unique_ptr.
