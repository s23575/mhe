# mhe

## MHE Zaoczne 2023: problem kliki

**Klika** w grafie nieskierowanym _G_ o wierzchołkach _V_ i krawędziach _E_ ( _G = (V, E)_ ) jest podzbiorem
wierzchołków _V'_ należacych do V ( _V' ⊆ V_ ), w którym każda para wierzchołków jest połączona krawędzią należącą do
E – klika jest pełnym podgrafem grafu G. Rozmiarem kliki jest liczba wierzchołków, które klika zawiera.

Mianem **problemu kliki** określa się optymalizacyjny problem znalezienia w danym grafie kliki o maksymalnym rozmiarze.
W wersji decyzyjnej problem ten sprowadza się do odpowiedzi na pytanie, czy w grafie _G_ istnieje klika o rozmiarze _k_.

Algorytm „naiwny“ dla problemu kliki w wersji decyzyjnej – dla odpowiedzi na pytanie, czy graf _G = (V, E)_ (o liczności
zbioru wierzchołków _|V|_ ) zawiera klikę rozmiaru _k_ – sprowadza się do przejrzenia wszystkich _k_-podzbiorów zbioru
_V_ i sprawdzenia każdego z nich, czy nie tworzy on kliki.

Czas działania powyższego algorytmu wynosi Ω ( C ( _|V|_ , _k_ ) k^2 ) i jest to czas wielomianowy, o ile _k_ jest wartością
stałą. Jeśli natomiast _k_ nie ma stałej wartości – może się zmieniać – czas działania algorytmu będzie czasem
wykładniczym. Efektywny algorytm dla rozwiązania problemu kliki najprawodpodobniej nie istnieje.

Przygotowano w oparciu o: T. H. Carmen, C. E. Leiserson, R. L. Rivest, C. Stein, _Wprowadzenie do algorytmów_, tłum. K,
Diks, A. Malinowski, D. Roszkowska i W. Rytter, wyd. VII, Warszawa 2021.