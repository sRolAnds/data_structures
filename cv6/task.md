Stanica Peklo

Ďalšou pracovnou úlohou na pozícii riaditeľa vlakovej stanice bude spočítať koľko cestujúcich cestuje do každej stanice. Úloha to nie je jednoduchá, lebo databáza musí byť pekelne rýchla. Lineárne vyhľadávanie musíme obmedziť na minimum. V oddelení vývoja vymysleli geniálny zlepšovák - vyhľadávanie pri ktorom je jedno v akej veľkej stanici vyhľadávane, vždy bude trvať rovnaký čas. Vzniklo nové perpettum mobile?

Hešovacia tabuľka so zreťazením
Na účel vyhľadávania si vytvoríme asociatívne pole, ktoré stanici priradí počet cestujúcich ktorí do nej cestujú. Asociatívne pole viete používať podobne ako klasické pole, ale ako kľúč môžete využiť ľubovoľný objekt, napr. reťazec. Pri vonkajšom pohľade, asociatívne pole vyzerá takto:

    Kľúč         Hodnota

    Prešov       20
    Košice       3
    Bratislava   11
Asociatívne pole ale nie je súčasťou jazyka C a tak si ho budeme musieť vytvoriť. Klasický spojkový zoznam na vytvorenie asociatívneho poľa nebude stačiť, lebo operácia vyhľadania je neefektívna - silno (lineárne) závisí od počtu prvkov. Možným riešením je použiť hešovaciu tabuľku so zreťazením. Namiesto jedného spojkového zoznamu použijeme viacero spojkových zoznamov, ktoré uložíme do poľa.

Jeden spojkový zoznam si môžeme predstaviť ako vlak, hešovaciu tabuľku si vieme predstaviť ako celú stanicu, kde sa naraz nachádza viac vlakov, každý na svojej koľaji. Do jednej stanice je smerovaný práve jeden vozeň (cieľové stanice sa nemôžu opakovať). Podobne ako na stanici, musíme povedať, na ktorej trati sa vlak bude nachádzať. To nám povie hešovacia funkcia, ktorá názvu cieľovej stanice priradí nejaké celé číslo. Dôležíté je, aby výsledné číslo bolo čo najviac "nepredvídateľné", ale stále rovnaké pre rovnaký reťazec. Množstvo všetkých možných reťazcov je väčšie ako množstvo celých čísel typu int a tak je možné, že viac rôznych reťazcov bude mať priradenú rovnakú hodnotu - nastane "kolízia". V prípade kolízie nám pomôže spojkový zoznam, ktorý umožní na jednu "koľaj" uchovať viac hodnôt.

Príklad stanice s viacerými vlakmi:

                hash 0: Prešov -> Košice -> Liptovský Mikuláš -> NULL
    stanica     hash 1: Spišská Nová Ves -> Margecany -> NULL
                hash 2: NULL
                hash 3: Kysak-> Dobšiná -> Levoča -> NULL
                hash 4: NULL
Hešovacia funkcia nám hovorí na ktorej koľaji nájdeme vozeň do niektorej cieľovej stanice. Prehľadanie jedného zoznamu bude trvať podstatne kratší čas, lebo vo väčšine prípadov sa záznam bude nachádzať hneď na prvom mieste.

Úloha

Vytvorte databázu na uloženie informácií o počte cestujúcich do rôznych staníc. Databázu vytvorte pomocou hešovacej tabuľky so zreťazením. V databáze môže byť o každej stanici maximálne jeden záznam o počte cestujúcich ktorí do nej cestujú.

Podľa dokumentácie v hlavičkovom súbore implementujte všetky funkcie.
