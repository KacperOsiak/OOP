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

COMMIT : Implement class friendship mechanism and friend functions

W tym etapie skupiłem się na wdrożeniu relacji przyjaźni, które pozwalają na kontrolowane współdzielenie prywatnych danych między różnymi komponentami systemu bez użycia publicznych getterów.

1. Przyjaźń między klasami (friend class)
Zaimplementowano mechanizm przyjaźni dla 7 klas, tworząc logiczne pary obiektów ściśle ze sobą współpracujących:

Customer otrzymał uprawnienia do klas: User, Address, Order, DiscountCard.

Product otrzymał uprawnienia do klas: Category, Supplier.

Store otrzymał uprawnienia do klasy: Product.

Zastosowanie: Dzięki temu klasa Customer w metodzie processPayment ma bezpośredni dostęp do prywatnych pól, takich jak profile->name czy card->discount, co upraszcza kod i zwiększa wydajność.

2. Zaprzyjaźnione funkcje zewnętrzne (friend void/bool)
Dla 5 wybranych klas zdefiniowano zewnętrzne funkcje zaprzyjaźnione, które pełnią rolę "narzędzi administracyjnych" i audytowych:

compareCities – porównuje prywatne pola lokalizacji.

printSensitiveData – umożliwia logowanie wrażliwych danych użytkownika.

isTopRated – zewnętrzna weryfikacja oceny produktu.

adminResetDiscount – administracyjny reset rabatów.

forceOrderStatus – ręczne nadpisywanie statusów zamówień.

3. Prezentacja w main
Funkcja główna została rozbudowana o testy wszystkich powyższych mechanizmów. Pokazano:

Wykorzystanie "wytrychów" (funkcji zaprzyjaźnionych) do modyfikacji i odczytu prywatnych stanów obiektów.

Bezpośrednią manipulację danymi wewnątrz metod klas zaprzyjaźnionych.

Poprawność działania kaskadowych destruktorów przy usuwaniu złożonych struktur obiektów.