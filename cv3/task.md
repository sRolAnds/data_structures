Úloha

Vytvorte zásobníkovú kalkulačku. Zásobník bude mať veľkosť 10 miest na uloženie čísla s desatinnou čiarkou.

Jeden vstup do kalkulačky bude zadaný na jednom riadku. Vstup do kalkulačky môže byť číslo s desatinnou čiarkou alebo jedna z operácií +-*/. Ak je na vstupe platné číslo, pridajte ho na koniec zásobníka. Ak je vstup operácia, vyberte dva posledné čísla zo zásobníka, vykonajte operáciu a výsledok vložte do zásobníka. Na konci každého úspešného vstupu alebo operácie zobrazte na nový riadok hodnoty v zásobníku oddelené medzerou.

V prípade, že sa nepodarilo načítať číslo alebo operáciu, vypíšte chybové hlásenie a ukončite program. V prípade, že je zásobník plný alebo v ňom nie je dostatok hodnôt, vypíšte chybovú správu a ukončite program.

Ak chceme v reverznej notácii vypočítať výraz (1 + 2), bude to vyzerať takto:

    1
    > 1
    2
    > 1 2
    +
    > 3
Ak chceme vypočítať (2 * (4 + 5)), musíme trochu porozmýšľať. Zadáme:

    2
    > 2
    4
    > 2 4
    5
    > 2 4 5
    +
    > 2 9
    *
    > 18
[https://hackaday.com/2017/10/24/reverse-polish-notation-and-its-mildly-confusing-elegance/](Viac informácií o poľskej kalkulačke)
