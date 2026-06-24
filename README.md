[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/3SRI_-8J)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=23362254)
# Proiect PA 2025

Repository-ul conține scheletul proiectului și testele publice.

## Structură

`include/`
Headerele pentru modulele cerute.

`src/`
Fișierele pe care trebuie să le completați.

`tests/public/`
Teste publice pentru fiecare pas. Aici găsiți fișierele de intrare și ieșirea așteptată.

`build/`
Conține binarele pentru rularea testelor publice:
- `build/public_pas1`
- `build/public_pas2`
- `build/public_pas3`
- `build/public_pas4`

## Rulare teste publice

Pentru a rula toate testele publice:

```bash
make public-test
```

Pentru a rula testele publice doar pentru un pas:

```bash
./build/public_pas1 tests/public/pas1/entitati.csv tests/public/pas1/relatii.csv tests/public/pas1/interogari.txt
./build/public_pas2 tests/public/pas2/entitati.csv tests/public/pas2/relatii.csv tests/public/pas2/interogari.txt
./build/public_pas3 tests/public/pas3/entitati.csv tests/public/pas3/relatii.csv tests/public/pas3/interogari.txt
./build/public_pas4 tests/public/pas4/entitati.csv tests/public/pas4/relatii.csv tests/public/pas4/interogari.txt
```

Fiecare test public are și un fișier `expected.txt` cu rezultatul așteptat.

## Teste publice și teste private

Există două tipuri de teste:
- teste publice, incluse în acest repository;
- teste private, folosite la evaluare.

Faptul că testele publice trec nu garantează punctaj maxim.

## Documentație implementare

## Descriere generală
Aplicația implementează un graf de cunoștințe ponderat care stochează entități, reprezentate de persoane, companii, locații sau evenimente, și relațiile între acestea. Datele se citesc din fișierele CSV, indexate pentru căutare, iar interogările sunt puse într-o coadă.

## Structuri de date utilizate

### 1.Graf cu liste de adiacență
Structurile: Graph, GraphNode și EdgeNode.
Graful este reprezentat printr-un tablou alocat dinamic de noduri, fiecare nod având propria listă de adiacență. Fiecare entitate devine un nod al grafului, inițial cu lista de muchii vidă.

De ce este eficient?
Graful este sparse(are numărul de muchii < n²). O matrice de adiacență ar fi ocupat mai multă memorie indiferent de numărul de muchii, iar în cazul nostru listele de adiacență ocupă O(n+m) spațiu.

### 2.Listă simplu înlănțuită de entități
Pe măsura citirii fiecare entitate este adăugată într-o listă simplu înlănțuită, care servește ca un fel de registru al tuturor entităților.

De ce este eficient?
Lista permite acces repetat la toate entitățile fără a le distruge și de aceea folosirea ei este mai eficientă în locul unei cozi spre exemplu.

### 3.Binary Search Tree indexat după nume
Structurile: BST și BSTNode.
Nodurile grafului sunt indexate într-un BST după numele entităților. Nodurile din BST conțin doar pointeri în tabloul grafului fără a duplica datele.

De ce este eficient?
Pentru a căuta prin lista de entități acesta este mai eficient deoarece reduce căutarea la O(log n) într-un caz mediu.

### 4.Coadă
Structurile: Queue și QueueNode.
Interogările citite din fișier sunt stocate într-o coadă implementată cu listă simplu înlănțuită și procesate în ordinea primirii.

De ce este eficient?
Interogările trebuiesc procesate în ordinea procesării, iar această structură este cea mai adecvată. Inserarea și extragerea sunt ambele O(1).

### 5.Min-Heap
Structurile: MinHeap și HeapNode.
Folosit în algoritmul Dijkstra pentru a găsi eficient nodul cu distanța minimă față de sursă.

De ce este eficient?
Extragerea minimului dintr-un vector nesortat este O(n). Min-Heap-ul oferă O(log n) atât pentru inserare cât și pentru extragere, reducând complexitatea totală pentru Dijkstra.

## Complexitatea operațiilor pentru interogare
Operație: 'EXISTS'
Complexitate: O(log n)
Justificare: Caută în BST după nume

Operație: 'EDGE'
Complexitate: O(log n + număr de muchii ale sursei)
Justificare: Caută în BST pentru nodul sursă și parcurge lista acestuia de muchii

Operație: 'NEIGHBORS'
Complexitate: O(log n + numărul de muchii ale sursei)
Justificare: Caută în BST și parcurge lista completă de muchii de ieșire

## Complexitatea algoritmilor de drum

### PATH - BFS
Complexitate: O(n+m)
Justificare: BFS vizitează fiecare nod și fiecare muchie maxim o singură dată. Folosește o coadă pentru a explora graful pe nivele, garantând că primul drum găsit are numărul minim de muchii. Drumul este reconstruit parcurgând vectorul de părinți reținut din timpul BFS-ului.

### Dijkstra
Complexitate: O((n+m) * log n)
Justificare:
- n extrageri din heap, fiecare cu O(log n)
- m relaxări de muchii, fiecare cu O(log n)
=> Total: O((n+m) * log n)
O căutare liniară ar implica O(n) per extragere fiind ineficient. Min-heap-ul reduce selecția la O(log n) obținând eficiență.