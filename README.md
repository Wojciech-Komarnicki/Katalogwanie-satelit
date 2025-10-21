🛰️ System Zarządzania Katalogiem Satelitów (C++)
Ten projekt to konsolowa aplikacja napisana w C++, służąca do zarządzania katalogiem satelitów. Został zaimplementowany z wykorzystaniem obiektowości (OOP), w tym dziedziczenia i polimorfizmu, aby efektywnie obsługiwać różne typy satelitów (np. Satelita Podstawowy i Satelita Komunikacyjny).

🚀 Kluczowe Funkcjonalności
Zarządzanie Danymi:

Dodawanie nowych satelitów (z podziałem na typy: podstawowy i komunikacyjny).

Wyświetlanie pełnego katalogu satelitów.

Edycja i usuwanie istniejących obiektów z katalogu.

Hierarchia Klas (OOP): Wykorzystuje klasę bazową Satelita oraz klasę pochodną SatelitaKomunikacyjny, demonstrując dziedziczenie i metody wirtualne (wyswietlInfo()).

Trwałość Danych: Umożliwia zapis całego katalogu do pliku tekstowego oraz wczytywanie danych z pliku.

Analiza: Generowanie prostych statystyk katalogu (np. średnia wysokość orbity, maksymalna prędkość).

Zarządzanie Pamięcią: Zastosowanie inteligentnych wskaźników (std::unique_ptr) do bezpiecznego zarządzania dynamicznie alokowanymi obiektami.

🛠️ Technologie
Język: C++ (z wykorzystaniem bibliotek standardowych: <iostream>, <fstream>, <vector>, <algorithm>, <sstream>).

Środowisko: Aplikacja konsolowa, zawiera również funkcje specyficzne dla Windows (<windows.h>) do obsługi plików.

👥 Użycie
Program jest obsługiwany za pomocą menu w konsoli, oferującego opcje od 1 do 7, umożliwiające interaktywne zarządzanie zbiorem satelitów.
