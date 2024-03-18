# PROJET RAY TRACER

_Par Jules Peyrache et Benoît Boero_

## Utilisation du Makefile
_Le projet contient un Makefile basique pour rendre plus simple la création de l'executable_

### make
Pour utiliser le Makefile il faut que la commande `make` soit installée, il suffit ensuite d'executer la commande `make` pour compiler les fichiers source et créer le fichier `raytracer` qui est l'executable principal.

### clean
Pour nettoyer les fichiers `*.o`, `*.h*.gch` et `raytracer` la commande `make clean` peut être utilisée. 

## Vector.h
_Ce fichier contient la definition de la classe `vector`. Cette classe est utilisée pour stocker des vecteurs de **R**x**R**x**R** mais aussi des couleurs rgb_
_La classe contient également une définition de type pour rendre plus rapide la definition de vecteurs et de couleurs :_

```c++
typedef vector<int> color;
typedef vector<float> Rvector;
```

### Initialisation d'un objet
Le constructeur à utiliser pour initialiser un nouveau vecteur prend en argument trois `float` correspondant aux coordonnées :
```c++
Rvector myVec = Rvector(float x, float y, float z);
```
Pour créer une nouvelle 'couleur' on utilisera :
```c++
color myColor = color(int r, int g, int b);
```

### Accesseurs
On dispose de différents accesseurs :
```c++
float x();
float y();
float z();
```
Pour récupérer les coordonnées d'un vecteur.
Ex:
```c++
Rvector myVec = Rvector(1.5, 0.0, 0.0);
std::cout << myVec.x() << std::endl; //prints 1.5
```

Ainsi que :
```c++
int r();
int g();
int b();
```
Pour récupérer les composantes d'une couleur (de la même manière).

### Affichage
Il y a surcharge des opérateurs `>>` et `<<` pour simplifier l'affichage des composantes d'un vecteur :

```c++
Rvector myVec = Rvector(1.5, 0.0, 0.0);
std::cout << myVec << std::endl; //prints 1.5 0.0 0.0
```

## Opérations sur les vecteurs
Les opérateurs `+,-,*,/,+=,-=,*=,/=` sont surchargés pour implémenter l'arithmétique composante par composante. 

LA classe dispose de deux méthodess: le calcul de la norme, et la mise à la norme d'un vecteur.

```c++
float norm();
void make_unit_vector();

```


Le fichier contient par ailleurs la definition de deux fonctions implémentant respectivement le produit scalaire et vectoriel :

```c++
vector<T> cross(const vector<T>&, const vector<T>&);
float dot(const vector<T>&, const vector<T>&);
```

## Utilisation de drawing.h

### couleurs
Le fichier contient une définition de type permettant de définir des couleurs rgb:

```c++
typedef struct color_ {
	unsigned char r,g,b;
} color;
```

Ainsi pour définir la couleur noire on écrira simplement :

```c++
color black = {0,0,0};
```

### Initialisation du tableau sur lequel on veut écrire
Pour initialiser le "tableau blanc" on utilise simplement :
```c++
drawing tableau(largeur, hauteur);
```
Où `largeur` et `hauteur` sont deux entiers positifs. Cela a pour effet de créer un tableau de taille largeur*hauteur.
La couleur par défaut des pixels est (255,255,255).

### Modification d'un pixel
Pour modifier un pixel on utilise :
```c++
tableau.draw_pixel(x,y,c);
```
Où `x,y` sont les coordonées entières et `c` la couleur. L'origine est en bas à gauche :
```
^
|
|
|
0-------->

```

### Envoyer l'image vers std::cout
```c++
tableau.print_image;
```

### Sauvegarde de l'image au format .pnm
Enfin pour sauvegarder l'image vers un fichier on utilise :
```c++
tableau.draw_image("nom.pnm");
```
