# Gynvael-Misja009
CTF challenge http://gynvael.vexillium.org/ext/3e2998dccb887cfdffd86ec658bd42d44ea4e477_misja009.txt

# Rozwiązanie
## RTTY
Pierwsze co zrobiłem po pobraniu pliku to otworzyłem go w Audacity.
Mając doświadczenie z RTL-SDR odrazu rozpoznałem ten sygnał to RTTY o niestandardowych parametrach i strasznie wolne.


![](http://i.imgur.com/sIX2OIv.png)

Nie udało mi się znaleźć nic podobnego na http://www.sigidwiki.com/wiki/Signal_Identification_Guide

## Gotowe rozwiązania
Próbowałem dekodować za pomocą MultiPSK ale nie pozwalał dekodować tak wolno.
Drugim narzędziem które przyszło mi do głowy był [Universal Radio Hacker](https://github.com/jopohl/urh). Jestem pewnie że poradził by sobie z tym zadaniem, ale chciałem napisać coś samemu. ;)

## Sekret
Po zdekodowaniu dostałem zwyczajny ciąg ASCII

![](http://i.imgur.com/qRl031d.png)
