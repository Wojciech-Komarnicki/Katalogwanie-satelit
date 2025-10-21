🛰️ SYSTEM ZARZĄDZANIA KATALOGIEM SATELITÓW W C++
Ten projekt to konsolowa aplikacja opracowana w języku C++ do efektywnego zarządzania danymi o satelitach. Implementacja ściśle wykorzystuje paradygmat Programowania Obiektowego (OOP), w tym dziedziczenie i polimorfizm.

🌟 Kluczowe Cechy i Implementacja
🧬 Obiektowość i Hierarchia Klas
Główna klasa Satelita jest bazą, przechowującą podstawowe parametry (nazwa, wysokość orbity, prędkość, czas życia).

Klasa pochodna SatelitaKomunikacyjny dziedziczy podstawowe cechy i dodaje specjalistyczny atrybut: częstotliwość komunikacji.

Wykorzystanie Polimorfizmu (metoda wirtualna wyswietlInfo()) do poprawnego wyświetlania informacji o różnych typach satelitów.

💾 Trwałość Danych i I/O
Funkcje zapiszDoPliku i wczytajZPliku umożliwiają trwałe przechowywanie i odtwarzanie całego katalogu z plików tekstowych.

Zaimplementowano mechanizmy obsługi strumieni (std::ostringstream) oraz operator przeładowania operator<< dla prostego zapisu obiektów.

✨ Zaawansowane Elementy C++
Zarządzanie dynamicznymi obiektami satelitów odbywa się za pomocą Inteligentnych Wskaźników (std::unique_ptr), co zapewnia automatyczne i bezpieczne zarządzanie pamięcią.

Wykorzystanie algorytmów standardowych (std::find_if, std::remove_if) oraz wyrażeń lambda do wyszukiwania i usuwania satelitów.

📊 Funkcjonalności Użytkownika
CRUD (Tworzenie, Odczyt, Aktualizacja, Usuwanie) satelitów.

Edycja satelitów z walidacją wprowadzanych danych wejściowych, aby zapobiec błędom.

Generowanie prostych Statystyk (np. średnia wysokość orbity, maksymalna prędkość) dla całego katalogu.
