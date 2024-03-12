# PROJET RAY TRACER

_Par Jules Peyrache et Benoît Boero_

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
