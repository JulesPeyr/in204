# PROJET RAY TRACER

_Par Jules Peyrache et Benoît Boero_

## Utilisation du Makefile

### make
Pour utiliser le Makefile il faut que la commande `make` soit installée, il suffit ensuite d'executer la commande `make` pour compiler les fichiers source et créer le fichier `raytracer` qui est l'executable principal.

### clean
Pour nettoyer les fichiers `*.o`, `*.h*.gch` et `raytracer` la commande `make clean` peut être utilisée. 

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
0------>

```

### Envoyer l'image vers std::cout
```c++
tableau.print_image(x,y,c);
```

### Sauvegarde de l'image au format .pnm
Enfin pour sauvegarder l'image vers un fichier on utilise :
```c++
tableau.draw_image("nom.pnm");
```
