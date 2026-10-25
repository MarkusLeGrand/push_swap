# push_swap

> Trier une pile d'entiers avec un jeu d'instructions très limité et deux piles, en produisant la suite d'opérations la plus courte possible.

![Langage C](https://img.shields.io/badge/langage-C-blue)
![École 42](https://img.shields.io/badge/école-42-black)

## À propos

push_swap est un projet algorithmique de l'école 42. Le programme reçoit une liste d'entiers (la pile **a**), dispose d'une pile auxiliaire vide (**b**) et doit afficher sur la sortie standard la suite d'instructions qui trie **a** par ordre croissant. Le score dépend du **nombre d'instructions** produites, pas du temps d'exécution.

Les seules opérations autorisées :

| Instruction | Effet |
|-------------|-------|
| `sa` / `sb` / `ss` | échange les deux premiers éléments de a / b / des deux |
| `pa` / `pb` | déplace le sommet de b vers a / de a vers b |
| `ra` / `rb` / `rr` | rotation vers le haut (le premier devient le dernier) |
| `rra` / `rrb` / `rrr` | rotation vers le bas (le dernier devient le premier) |

## Fonctionnalités

- Accepte les nombres en **arguments séparés** (`./push_swap 3 2 1`) ou dans **une seule chaîne** (`./push_swap "3 2 1"`).
- **Validation des entrées** : libère la pile, affiche `Error` et quitte si un argument n'est pas un entier valide, dépasse les bornes d'un `int` ou apparaît en double.
- N'affiche rien si la pile est déjà triée.
- Cas particuliers optimisés : 2 éléments (un `sa`), 3 éléments (au plus 2 instructions).
- Algorithme général par **calcul de coût** pour les tailles supérieures.

## Compilation & utilisation

Le code se trouve dans le dossier `pushswapv1/` :

```bash
cd pushswapv1
make        # compile la libft (libftV2/) puis l'exécutable push_swap
make clean  # supprime les objets (projet + libft)
make fclean # supprime aussi push_swap et libft.a
make re     # recompile entièrement
```

Exemples :

```bash
$ ./push_swap 3 2 1
ra
sa

$ ./push_swap "4 67 3 87 23"
pb
pb
rra
sa
rra
pa
rra
pa
rra

$ ./push_swap 1 2 a
Error

$ ./push_swap 1 1
Error
```

Vérification avec le checker fourni par 42 (`checker_linux`, non versionné) :

```bash
ARG=$(shuf -i 1-100000 -n 100 | tr '\n' ' ')
./push_swap $ARG | wc -l               # nombre d'instructions
./push_swap $ARG | ./checker_linux $ARG  # OK / KO
```

### Performances mesurées

Sur 5 tirages aléatoires par taille, tous validés `OK` par le checker :

| Nombre d'éléments | Moyenne d'instructions | Maximum observé |
|-------------------|------------------------|-----------------|
| 3                 | ~1                     | 2               |
| 5                 | ~8                     | 10              |
| 100               | ~583                   | 610             |
| 500               | ~5300                  | 5629            |

## Approche technique : l'algorithme « Turk » (tri par coût minimal)

Plutôt qu'un tri par découpage en tranches (*chunks*) ou un radix sort, j'ai implémenté un **algorithme glouton basé sur le coût** : à chaque étape, on calcule pour chaque élément combien d'instructions coûterait son placement au bon endroit, et on déplace le moins cher.

### 1. Phase a → b

- On pousse d'abord deux éléments dans **b** sans réfléchir (`pb`, `pb`).
- Tant que **a** contient plus de 3 éléments, on répète (`init_nodes_a`, puis `move_a_to_b`) :
  1. **Index et médiane** (`current_index`) : chaque nœud connaît sa position et s'il est dans la moitié haute ou basse de sa pile. Cela décide s'il vaut mieux l'amener au sommet par `ra` ou par `rra`.
  2. **Cible** (`set_target_a`) : pour chaque élément de a, sa cible dans b est le **plus grand élément plus petit que lui**. S'il n'y en a pas, la cible est le maximum de b. Ainsi, b reste trié par ordre **décroissant** (à une rotation près).
  3. **Coût** (`cost_analysis_a`) : nombre de rotations pour amener l'élément au sommet de a + nombre de rotations pour amener sa cible au sommet de b, en choisissant à chaque fois le sens le plus court.
  4. **Le moins cher** (`set_cheapest`) est déplacé. Si l'élément et sa cible sont du même côté de la médiane, on utilise **`rr` ou `rrr`** pour faire tourner les deux piles en même temps et économiser des instructions, puis on termine avec `ra`/`rra` et `rb`/`rrb`, et enfin `pb`.

### 2. Tri des 3 derniers éléments de a

`sort_three` place le maximum en bas de pile (`ra` ou `rra`) puis corrige l'ordre des deux premiers (`sa`) si besoin : au plus 2 instructions.

### 3. Phase b → a

Chaque élément de b est renvoyé dans a (`init_nodes_b`, puis `move_b_to_a`). Sa cible dans a est le **plus petit élément plus grand que lui** (ou le minimum de a à défaut) ; on amène cette cible au sommet de a puis `pa`.

### 4. Finalisation

On fait tourner a jusqu'à ce que le minimum soit au sommet (`min_on_top`), en choisissant `ra` ou `rra` selon sa position par rapport à la médiane.

### Structure de données

Les piles sont des **listes doublement chaînées**. Chaque nœud embarque les informations utiles à l'algorithme, recalculées à chaque tour :

```c
typedef struct s_stack_node
{
    int                  nbr;          // valeur
    int                  index;        // position dans la pile
    int                  push_cost;    // coût total du déplacement
    bool                 above_median; // moitié haute ou basse
    bool                 cheapest;     // élément choisi à ce tour
    struct s_stack_node *target_node;  // position cible dans l'autre pile
    struct s_stack_node *next;
    struct s_stack_node *prev;
}   t_stack_node;
```

## Structure du projet

```
push_swap/
├── pushswapv1/
│   ├── Makefile
│   ├── inc/push_swap.h        # structure de nœud et prototypes
│   ├── init_prep/
│   │   ├── handle_errors.c     # validation syntaxe, doublons, libération
│   │   ├── stack_init.c        # atol, construction de la pile a, prep_for_push
│   │   ├── split.c             # découpage de l'argument unique
│   │   ├── stack_utils.c       # longueur, min, max, test « trié »
│   │   ├── init_a_to_b.c       # index/médiane, cibles, coûts, plus faible coût
│   │   └── init_b_to_a.c       # cibles pour le retour vers a
│   ├── instructions/           # swap.c, push.c, rotate.c, rev_rotate.c
│   ├── sort/
│   │   ├── push_swap.c         # main
│   │   ├── sort_three.c        # cas à 3 éléments
│   │   ├── sort_stacks.c       # algorithme principal
│   │   └── sort_utils.c        # rr / rrr combinés
│   └── libftV2/                # ma libft (avec ft_printf), compilée en libft.a
├── Push-Swap-Tester/           # référence vers un dépôt externe de test
└── pushandpray/                # référence vers un dépôt externe
```

## Ce que j'ai appris

- Concevoir un **algorithme glouton** et raisonner en coût d'opérations plutôt qu'en complexité temporelle.
- Exploiter les **opérations combinées** (`rr`, `rrr`) et le choix du sens de rotation via la médiane pour réduire le nombre d'instructions.
- Implémenter et manipuler des **listes doublement chaînées** (push, swap, rotations) sans fuite mémoire.
- **Valider rigoureusement des entrées utilisateur** : format, dépassement d'`int` (lecture en `long`), doublons.
- Organiser un projet C de taille moyenne en modules et **réutiliser ma propre libft** via un Makefile qui la compile en dépendance.
