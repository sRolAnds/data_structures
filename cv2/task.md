Úloha

Pri určovaní marketingovej stratégie je veľmi dôležité zistiť,. ktorá pizza je najlacnejšia. Dalo by sa to síce zistiť jednoduchým prečítaním jedálneho lístka, ale vieme to robiť aj inak - strojovým spracovaním. Nová verzia jedálneho lístka by mala byť zoradená podľa ceny tak, aby najlacnejšia pizza bola na prvom mieste. V prípade, že je cena rovnaká, zoraďte položky podľa abecedy. Špeciálne znaky s diakritikou nemusíte brať do úvahy.

Jedálny lístok je vo formáte:

    Názov 1
    Cena 1
    Názov 2
    Cena 2
    atd.

Názov je ľubovoľný neprázdny reťazec neprázdnych znakov. Názov nie je dlhší ako 100 znakov. Cena je číslo s desatinnou čiarkou zadané na dva miesta. Žiadna cena v jedálnom lístku nemôže byť nulová. Jedálny lístok je ukončený neplatnou položkou (nesprávne zadaný názov alebo cena) alebo koncom vstupu. Inak povedané, budeme načítavať až pokiaľ sa dá.

Práca s programom môže vyzerať napríklad takto:

Vstup:

    Salamovo Fazulova pizza
    7.96
    Sunkova pizza
    5.77
    Bryndzova pizza
    8.67
    Zelerova pizza
    8.86
    Slaninovo Sunkova pizza
    7.55
    Slaninova pizza
    5.16

Na výstupe by sa mal objaviť načítaný jedálny lístok, ale v poradí podľa ceny. Najprv sa zobrazí najlacnejšia položka, potom druhá najlacnejšia a na koniec najdrahšia. V prípade, že má viac položiek rovnakú cenu tak ich zoraďte podľa abecedy.

Výstup:

    Slaninova pizza
    5.160000
    Sunkova pizza
    5.770000
    Slaninovo Sunkova pizza
    7.550000
    Salamovo Fazulova pizza
    7.960000
    Bryndzova pizza
    8.670000
    Zelerova pizza
    8.860000
