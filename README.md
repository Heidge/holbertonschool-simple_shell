# holbertonschool-simple_shell

Un mini shell en C capable d'exécuter des commandes comme `ls`, `cd`, `exit`, etc.

## Commandes internes :
- `cd [dir]` : changer de dossier
- `exit` : quitter le shell
- `help` : afficher l’aide

## Compilation :
```bash
make
```

## Flowchart
```mermaid
flowchart TD
    1((Démarrage du shell.c)) --> 2[Affiche #cisfun$]
    2 --> 3[Recupere l'entree]
    3 -->|Commande entree| 3A{Commande 'exit' ?}
    3A -->|Oui| 3B((Sortir de shell.c))
    3A -->|Non| 4{Commande du shell ?}
    4 -->|Oui| 5A[Executer la commande shell] -->|Boucle infinie| 2
    4 -->|Non| 5B[Chercher la commande dans 'PATH']
    5B --> 5C{Commande repertoriee ?}
    5C -->|Oui| 6A[Executer la commande repertoriee] -->|Boucle infinie| 2
    5C -->|Non| 6B[Erreur execve] -->|Boucle infinie| 2
```
