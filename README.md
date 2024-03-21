# PROJET RAY TRACER

_Par Jules Peyrache et Benoît Boero_

## Utilisation du programme
_Le programme prend en argument un nom de fichier parametrant la simulation_

### Format de fichier
On définit un format de fichier qui contient des `flags` sous la forme `.nom_flag(val_flag1, val_flag2, ...);`. Chaque flag correspond en fait à un paramètre, qui est définit en utilisant une ou plusieurs valeurs. Chacun de ces flags commence par le caractère `.` et se termine par le caractère `;`, les caractères `(`, `)`, `,` sont aussi importants. Les espaces superflus sont ignorés.

### Commentaires
Les lignes commençant par le caractère `#` sont considérées comme commentaires et sont affichées lors du chargement du fichier pour donner du context. Par exemple :

```
# Definition de la largeur de l'image
.width(100);
```

Résultera en :

```
>  Definition de la largeur de l'image
flag name : width
values : #100
```

### Paramètres géométriques
Le repère local de la caméra est définit avec l'axe z s'éloignant de la scène, et l'axe y vertical ascendant.

```python
# définit la hauteur de l'image produite
# valeur par défaut : 720
.height(int);

# définit la largeur de l'image produite
# valeur par défaut : 360
.width(int);

# définit le nombre de rayons utilisés pour l'antialiasing
# valeur par défaut : 10
.ns(int);

# définit la position de la caméra (position depuis laquelle on regarde la scène).
# valeur par défaut : 0.0, 0.0, 0.0
.camera_origin(float, float, float);

# définit la position du point vers lequel la caméra est dirigée (quel point on regarde).
# valeur par défaut : 0.0, 0.0, -1.0
.camera_subject(float, float, float);

# définit le vecteur vertical de la caméra
# valeur par défaut : 0.0, 1.0, 0.0
.camera_vertical(float, float, float);

# définit le FOV (field of view) de la caméra en degrés
# valeur par défaut : 90
.camera_fov(float)

```

### Paramètres objets

#### Matières
Chaque objet peut être constitué d'une certaine matière, voici la liste des différentes matières disponibles :
* Matte : `.material_matte(R_r, R_g, R_b, tag);`
* Métalique : `.material_metal(R_r, R_g, R_b, fuzziness, tag);`
* Diélectrique : `.material_dielectric(ref_index, tag);`

Explication des champs :

* Le champ `tag` correspond à la réference que l'on utilisera dans la definition des sphères, c'est une chaine de caractères (sans les guillemets).
* Les champs `R_x` correspondent à la réflexion de chaque couleur par l'objet, ils sont compris entre 0 et 1.
* Le champ `fuzziness` correspond à l'ajout d'aléatoire dans la reflexion de la lumière à la surface du métal, il est compris entre 0 et 1. 0 correspond à une reflexion déterministe et 1 correspond à une quantité assez conséquente d'aléatoire. (Plus précisément on modifie la direction du rayon réfléchi en choisisant un nouveau point-cible dans la sphère de rayon `fuzziness` qui est centrée au bout du vecteur unitaire réfléchi).
* Le champ `ref_index` correspond à l'indice de refraction de la matière diéléctrique.

#### Sphères
Ce paramètre correspond à ajouter une sphère sur la scène:
```python
# Ajoute une sphère constituée d'une certaine matière (dont le tag est mat), centrée en (x,y,z) et de rayon r sur la scène.
.sphere(x,y,z,r,mat);
```

Note: la matière doit avoir été définie avant d'être utilisée, ainsi ceci renvera une erreur :
```python
.sphere(0,0,0,1,acier);
.material_metal(0.5,0.5,0.2,0.5,acier);
```
On écrira plutôt :
```python
.material_metal(0.5,0.5,0.2,0.5,acier);
.sphere(0,0,0,1,acier);
```

### Exemples de fichier valide
Quelques exemples concrets de fichiers `.ray` sont fournits avec le projet. En voici un exemple :

```
---[france.ray]---
# A nos enfants !!
#
# anti alisasing
.ns(20);
# dim
.width(1000);
.height(1000);
# camera
.camera_origin(0,0,-2);
# material
.material_metal(1,0,0,0,m1);
.material_metal(1,1,1,0,m2);
.material_metal(0,0,1,0,m3);
# objects
.sphere(-1,0.25,0,0.5,m1);
.sphere(0,0.25,0,0.5,m2);
.sphere(1,0.25,0,0.5,m3);

```

Résultat :

![france.pnm](/img/france.png "France.png")

## Utilisation du Makefile
_Le projet contient un Makefile basique pour rendre plus simple la création de l'executable_

### make
Pour utiliser le Makefile il faut que la commande `make` soit installée, il suffit ensuite d'executer la commande `make` pour compiler les fichiers source et créer le fichier `raytracer` qui est l'executable principal.

### clean
Pour nettoyer les fichiers `*.o`, `*.h*.gch` et `raytracer` la commande `make clean` peut être utilisée. 

## vector.h
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

La classe dispose de deux méthodess: le calcul de la norme, et la mise à la norme d'un vecteur.

```c++
float norm();
void make_unit_vector();

```


Le fichier contient par ailleurs la definition de deux fonctions implémentant respectivement le produit scalaire et vectoriel :

```c++
vector<T> cross(const vector<T>&, const vector<T>&);
float dot(const vector<T>&, const vector<T>&);
```

## ray.h
_Ce fichier contient une implémentation assez simple d'un 'rayon'. Un rayon est constitué d'un point origine et d'une direction :_
```c++
vector A; // origine
vector B; // direction
```

### Initialisation
Pour initialiser un nouveau rayon, on doit lui fournir une origine et une direction :
```c++
ray myRay = ray(Rvector origine, Rvector direction);
```

### Accesseurs
L'objet dispose de deux accesseurs :
```c++
Rvector origin();
Rvector direction();
```

### Méthodes
Une seule méthode est définie, et sert à renvoyer les coordonées d'un point paramétré sur la droite engendrée par le vecteur direction et passant par l'origine :
```c++
Rvector point_at_parameter(float t); //return A + t*B
```

## drawing.h
_Ce fichier contient une classe permettant de faciliter la création d'une image_

### couleurs
Le format de couleurs utilisé est celui définit dans le fichier `vector.h`.
Ainsi pour définir la couleur noire on écrira simplement :

```c++
color black = color(0,0,0);
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
