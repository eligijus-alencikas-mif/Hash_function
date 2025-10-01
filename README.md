# Hash Function Laboratorinis Darbas be AI pagalbos

**Padarė:** Eligijus Alenčikas  
**Grupė:** 1 grupė, 1 pogrupis  
**Universitetas:** VU ISI

## Aprašymas

Šis projektas efektyviai įgyvendina hash funkciją, kuri atitinka visus reikalavimus:
- Deterministiškumas
- Avalanche effect (lavinos efektas)
- Negrįžtamumas
- Fiksuoto dydžio išvestis (64 simbolių)

## Algoritmo savybės

Hash funkcija atitinka visas iškeltas hash funkcijos savybes

### Algoritmo esmė žingsnis po žingsnio:

1. Hash funkcija gavus įvestį jo dįdį paverčia į 64 simbolių seką išemant paskutinius simbolius, bet tuo pačiu sujugenčius juos su pirmais simboliais.
2. Hash funkcija pradedant nuo įvesties pradžios paima simbolių porą, jas algoritmu sujungia į vieną simbolį ir pirmąjį poros simbolį pakeičia nauju sujungtu simboliu. Taip algoritmas tesiasi iki įvesties pabaigos.
3. Hasho algoritmas tą patį pakartoją, bet pradedant nuo įvesties pabaigos
4. Sugeneruotas Hashas išvedamas

## Eksperimentų rezultatai

### 1. Testinių failų rezultatai

**Išvados:**
-  Visi hash'ai yra tiksliai 64 simboliai (64 baitai)
-  Mažas pokytis (tarkim simbolio a pakeitimas į b) sukelia dramatišką hash skirtumą
-  Su tuščiu failu programa užlūšta
-  Didelis failas ir jo maža modifikacija turi skirtingus hash'us

### 2. Išvedimo dydžio patikrinimas
#### Išvedimo dydis su konstitucija.txt file - 64 simboliai:
![img.png](img.png)
#### Išvedimo dydis su bet kokiu žodžiu (pvz. Eligijus) - 64 simboliai:
![img_1.png](img_1.png)
**Rezultatas:** ATITINKA
- Visi hash'ai yra **tiksliai 64 simbolių** ilgio
- Nepriklausomai nuo įvesties dydžio (0-1504 simboliai), išvestis visada vienodo dydžio

### 3. Deterministiškumo patikrinimas

**Rezultatas:**  ATITINKA
```
Pirmas paleidimas: @L#w;F35nW`fVERts0QuWxMyHeNXtsH:A8!y!,99jYl~2_pH?HWA{lM/tWLflmvO
Antras paleidimas:  @L#w;F35nW`fVERts0QuWxMyHeNXtsH:A8!y!,99jYl~2_pH?HWA{lM/tWLflmvO
```
- Tas pats įvedimas visada duoda tą patį rezultatą
- Funkcija nenaudoja jokių atsitiktinių elementų