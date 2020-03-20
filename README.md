# AStar

A projektben a 3*3-as kirakójáték megoldását implementáltuk le, bemenetnek egy txt fájlban kell megadni a kezdeti állapotot 
0-tól 8-ig számozva, a számok közt szóközt teszünk, a méretet nem kell megadni.
A csomópontok tárolását egy kétdimenziós mátrixban oldottuk meg, ahol a mátrix minden sorának elsõ 9 eleme tartalmazza magát a csomópontot,
a kilences sorszámú elemben figyeljük le, hogy az a csomópont volt-e már aktuális, a 10-ik elemben a csomópont értéke kerül a megjelölt heurisztikák alapján,
a 11 és 12-ik elemben tárolva van az üres mezõ koordinátája a csomópontban, a 13-as elembe a költség és az utolsó elembe pedig annak a csomópontnak a sorszáma kerül,
amelybõl elértuk a jelenlegi csomópontunkat.

A futtatás a következő képpen történik: ./astar.exe -file be.txt (-solseq vagy -pcost vagy -nvisited) (-h<1 vagy 2>)

Példa: ./astar.exe -file be.txt -solseq -h<2>
