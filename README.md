# Lady Herring
Lady Herring è un motore di analisi per le partite di dama italiana.

## Roadmap
- [x] Implementazione della damiera
- [x] Implementazione delle mosse possibili
- [ ] Implementazione di un algoritmo intelligente per la scelta delle mosse (bot)

## Informazioni
![Codifica Damiera](/README/damiera.png)

### Notare come:
- Mangiare
    - in alto a destra ->  pos - 7
    - in alto a sinistra ->  pos - 9
    - in basso a destra ->  pos + 9
    - in basso a sinistra ->  pos + 7

- Muoversi
    - Sulle righe dispari:
        - in alto a destra -> pos - 4
        - in alto a sinistra -> pos - 5
        - in basso a destra -> pos + 4
        - in basso a sinistra -> pos + 3
    - Sulle righe pari:
        - in alto a destra -> pos - 3
        - in alto a sinistra -> pos - 4
        - in basso a destra -> pos + 5
        - in basso a sinistra -> pos + 4

## Crediti
Questo progetto è stato sviluppato da:
- Emanuele Galardo
- Davide Pirrò 
