COMMIT: implement destructors, this pointers and class refactoring

Zarządzanie pamięcią: Wprowadzono destruktory we wszystkich klasach. Wdrożono kaskadowe usuwanie obiektów w klasie Customer (automatyczne czyszczenie profilu, adresu i zamówienia).

Refaktoryzacja this: Zastosowano wskaźnik this w konstruktorach i setterach, co pozwoliło na ujednolicenie nazw parametrów z nazwami pól.

Hermetyzacja i Walidacja: Ustandaryzowano gettery/settery oraz dodano logikę sprawdzającą poprawność danych (np. limity ocen i rabatów).

Const Correctness: Oznaczono metody odczytu danych jako const dla zwiększenia stabilności kodu.

Zmiany w modelu danych
Rozszerzenie klas o brakujące atrybuty: email (User), description (Category), country (Supplier).

Dodanie logiki stanowej w klasie Store (otwarcie/zamknięcie sklepu).

Implementacja klasy DiscountCard obsługującej rabaty procentowe.

--------------------------------------------------------------------------------