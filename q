[33mcommit 65729cfae0758cf64f4571c62cd99c508cc4753b[m[33m ([m[1;36mHEAD -> [m[1;32mtesty[m[33m, [m[1;31morigin/testy[m[33m)[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Mon Jan 24 13:07:36 2022 +0100

    Zmieniona nazwa glownego pliku na hermit.c
    Wprowadzono niezbedne zmiany w Makefile

[33mcommit c1b70c233c289892cb746d3607d4d90154aaec97[m
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Mon Jan 24 12:56:35 2022 +0100

    Nieistotne

[33mcommit 05b828893008df6c918e07aa2d7617a1fc4a83d9[m
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Mon Jan 24 11:53:06 2022 +0100

    NAPRAWIONE WYCIEKI PAMIECI WOOOO!!

[33mcommit 402bbc81c3b2e584d0825ffe5007f0ca24476fc7[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Mon Jan 24 00:17:21 2022 +0100

    Usunieto zbedne linie pogarszajace czytelnosc programu

[33mcommit 8aaa218f2eb5d8cf36fdd268b6b8d45e4be8cc9f[m
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Sun Jan 23 23:51:56 2022 +0100

    Drobne zmiany

[33mcommit 4aa7c8c245d7213f77c250fcc462a330225f71ce[m
Merge: 40ad786 a344fea
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Sun Jan 23 23:50:20 2022 +0100

    Kosmetyczne zmiany

[33mcommit 40ad7863f258825993ab514d57d6dba12ed28bd9[m
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Sun Jan 23 23:49:24 2022 +0100

    Naprawa alloc_spl

[33mcommit a344fea96c58835aa41dd907ebe34009ffe4541b[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sun Jan 23 23:46:16 2022 +0100

    Kosmetyczne zmiany w main.c i gaus/matrix.c

[33mcommit 5b59435eba66d446eed29a82e54828a915a8dd60[m
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Sun Jan 23 23:40:44 2022 +0100

    Naprawa wycieków pamięci w alloc_spl

[33mcommit b808e7fce6a8bbdc87018a26ae326eac57678eed[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sun Jan 23 23:28:42 2022 +0100

    Naprawione wycieki pamieci w funkcji read_pts_failed

[33mcommit f82cee4f4c66877fbde7c2cd4f09973d47e7d549[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sun Jan 23 23:20:28 2022 +0100

    Znowu zmieniona funkcja realloc_pts_failed (nic to nie dalo)

[33mcommit 4db7f184d803995066547f126a236e79a8f5da43[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sun Jan 23 23:09:09 2022 +0100

    Zmienione dane testowe 2

[33mcommit 292506edccc626cfe45ff375c074cef691f18158[m
Merge: 96b1fb8 f4332d2
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Sun Jan 23 22:28:45 2022 +0100

    Nieistotne zmiany w aproksymatorze (DEBUG)

[33mcommit 96b1fb8832b65ca70b3a8629ef175cbb119cbd07[m
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Sun Jan 23 22:23:08 2022 +0100

    Zmiany make_spl

[33mcommit f4332d2ff8d65ec6d85ccccb6a69622ab73ec7c2[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sun Jan 23 22:21:56 2022 +0100

    Przerobiony make_spl dostosowany do naszych funkcji bazowych

[33mcommit 2a46fb2fa059863224ed9b4ef426a6c197fda184[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sun Jan 23 22:03:08 2022 +0100

    Dodalem trzecia pochodna wielomianu hermita.

[33mcommit a3b118212593e5e7cc1f67d8e459fff334dbc35a[m
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Sun Jan 23 21:55:56 2022 +0100

    Implementacja pochodnej pochodnej wielomianów Hermite'a

[33mcommit c2ce279e6b4a77a3218cd9786d301bf462794bd9[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sun Jan 23 21:41:05 2022 +0100

    Dodana pierwsza pochodna wielomianu hermita

[33mcommit 56ea157e7d3a7f01445d1f0dd7e06e217375928f[m
Author: Antoni Zajac <zajac.antek@o2.pl>
Date:   Sun Jan 23 21:31:59 2022 +0100

    Napisanie funkcji fi -> tworzącej bazę wielomianów Hermite'a

[33mcommit e8929b01c2c2229f6715fc09cb95fa69d4b2a4a5[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sat Jan 22 23:43:08 2022 +0100

    W pliku "matrix.h" dodalem naglowek funkcji free_matrix, ktora jest w pliku "matrix.c".
    Naprawilem funkcje "realloc_pts_failed" w pliku "points.c"
    Teraz bazowy program przynajmniej dziala.

[33mcommit 8569ee67aa28443162891611bd39f96eaae91b82[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sat Jan 22 22:13:10 2022 +0100

    Dodalem dwa dodatkowe pliki testowe: dane.2 ma 1000 punktow z zakresu <0,500> a dane.3 1000 punktow z zakresu <100,5000>

[33mcommit 0b63c31247e99b16d1157c9897288ad4f3b8d3d9[m
Author: Pioter17 <piotrwisnie@wp.pl>
Date:   Sat Jan 22 21:47:48 2022 +0100

    realloc w funkcji "read_pts_failed" nie działał prawidłowo. (linie 36 i 44) Poprawiłem go

[33mcommit 24dc09fcb386fe9c2b157459cd3e6c8b72ec8269[m[33m ([m[1;31morigin/main[m[33m, [m[1;31morigin/HEAD[m[33m, [m[1;32mmain[m[33m)[m
Author: Pioter17 <44977082+Pioter17@users.noreply.github.com>
Date:   Thu Jan 13 13:31:45 2022 +0100

    bazowe pliki

[33mcommit 2ad134b715a4807996a247c8c6c289e641071c85[m
Author: Pioter17 <44977082+Pioter17@users.noreply.github.com>
Date:   Thu Jan 13 13:29:22 2022 +0100

    Initial commit
