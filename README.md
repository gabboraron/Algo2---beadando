# Fa átmérője

Egy T=(V,E) fa átmérője a fában előforduló legrövidebb út távolságok legnagyobbika, azaz:
![alt text](https://github.com/gabboraron/Algo2-beadando/blob/master/kep11.JPG "keplet")

Adjunk hatékony algoritmust egy fa átmérőjének kiszámítására. Elemezzük az algoritmus futási idejét!
(A fát irányítatlan, összefüggő gráfként kezeljük.) (Lehet találni O( V + E ) algoritmust!)

## Bemenet:

Az INP.TXT állományban több fa leírása található. Az első szám adja meg, hány fa leírását találjuk a fájlban, majd az egyes fák megadása következik. A fák leírását a pontjai számának megadásával kezdjük, a csúcsokat egytől, egyesével számozzuk. Majd az élek megadása történik számpárok formájában, (az éleket csak egyszer adjuk meg, például az 1-es és 4-ea csúcs közti élet 1 4 vagy 4 1 formában), a 0 0 számpár jelzi az élek megadásának végét. (A fa tulajdonságot nem kell ellenőrizni.)

## Kimenet:

Írjuk az eredményeket az OUT.TXT nevű állományba! Minden fához jelenítsük meg az átmérő nagyságát.

### input:
 **INP.TXT**
> 3
> 3 1 2 1 3 0 0
> 6 1 2 5 1 3 1 6 3 4 2 0 0
> 11 6 4 5 6 10 7 7 3 4 3 2 4 8 2 9 8 1 5 6 11 0 0

### output:
> 1. fa: 2
> 2. fa: 4
> 3. fa: 6

*Kiegészíthetjük a feladatot az (egyik) átmérőn található csúcsok kiíratásával is.*
