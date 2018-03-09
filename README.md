# Projet de cryptographie RSA- L3 (Théorie des Groupes et applications)
- Programmé en C++ avec les notions d'orienté objet et avec la STL

Configuration
- Version compatible pour Mac OS et Linux à utiliser EXCLUSIVEMENT avec un terminal
- NON COMPATIBLE AVEC WINDOWS !
- EXTRÊMEMENT IMPORTANT POUR L'AFFICHAGE: DÉFINIR L'ENCODAGE DU TEXTE SUR ISO-LATIN 1.

Sur le terminal en ciblant le bon dossier:

Compilation: g++ *.cpp -o main
Exécution: ./main

# Cryptographie RSA avec certaines notions de maths du module Théorie des Groupes et Applications que voici:
- Algorithme d'Euclide et PGCD
- Algorithme d'Euclide étendu et relation de Bézout (coefficients u et v)
- Exponentiation rapide modulaire
- Nombres premiers, décomposition en facteurs de nombres premiers.
- Indicatrice d'Euler φ(n) = (p - 1) x (q - 1)
Avec ces notions, on peut ainsi concevoir le cryptage RSA, un cryptage asymétrique à clé publique et à clé privée:
- La clé publique se compose de 2 éléments: n et e avec n un nombre entier qui se factorise en produit de 2 nombres premiers, et e, un nombre entier qui est premier avec φ(n) (de sorte que le PGCD soit égal à 1). Cette clé publique (n, e) permet le cryptage d'un message.
- La clé privée se compose en 4 éléments: d, p, q et φ(n). Avec p et q, les facteurs premiers de n. φ(n) l'indicatrice d'Euler, et d, la clé privée de décryptage, l'élément le plus important de la clé privée pour décrypter un message (à conserver secret).
- La clé privée d se calcule à l'aide de la clé publique (n, e) et des 3 éléments p, q, φ(n). Elle se détermine avec la relation de Bézout telle que (u x φ(n)) + (v x e) = 1 avec l'algorithme d'Euclide étendu. La clé privée d sera le plus petit entier v positif (v = v + φ(n) / PGCD(φ(n), e), si v négatif).

Ainsi, le cryptage et le décryptage d'un message M se fait avec l'exponentiation rapide modulaire:
- Cryptage: M^e mod(n), M puissance e qui est congru à n.
- Décryptage: M^d mod(n), M puissance d qui est congru à n.

Un projet qui est très intéressant, du fait que ce cryptage est extrêmement utilisé dans l'échange de données confidentielles sur Internet et que sa sécurité augmente s'il est plus en plus difficile de factoriser n en p et q. Plus p et q sont grands (de même pour e), plus forte sera la sécurité du cryptage pour donner plus de fil à retordre aux hackers !
Actuellement, le cryptage RSA utilise des nombres de plus de 600 chiffres !!!