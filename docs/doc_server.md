# Projet Zappy - Partie Serveur

## Introduction

Le projet Zappy est un jeu en réseau où plusieurs équipes s'affrontent sur une carte composée de cases contenant des ressources. Le serveur, codé en C, gère le monde du jeu, les interactions des joueurs, et la communication avec les interfaces graphiques (GUI) et les IA.

## Installation

### Prérequis

Le serveur Zappy utilise la bibliothèque `json-c` pour envoyer des informations au tableau de bord (dashboard). Vous devez installer cette bibliothèque avant de compiler le projet.

#### Debian/Ubuntu

```sh
sudo apt-get install libjson-c-dev
```

#### Fedora

```sh
sudo dnf install json-c-devel
```

### Compilation

Pour compiler le serveur, le GUI et les clients IA, exécutez la commande suivante à la racine du projet :

```sh
make
```

## Architecture

L'architecture du projet Zappy est conçue pour gérer de manière efficace un environnement de jeu multijoueur en réseau. Voici les principaux composants :

1. **Serveur** : Gère le monde du jeu, les interactions entre les joueurs, et les ressources. Utilise des sockets TCP pour communiquer avec les clients (IA et GUI).
2. **Clients IA** : Contrôlent les joueurs dans le jeu, en envoyant des commandes au serveur.
3. **GUI** : Fournit une interface graphique pour visualiser l'état du jeu en temps réel.
4. **Dashboard** : Affiche des informations de débogage et des statistiques de performance. Ce composant est optionnel et peut être activé pour des diagnostics avancés.

### Communication entre Composants

- **Serveur et Clients IA** : Utilisent des sockets TCP pour échanger des commandes et des états. Les clients IA envoient des commandes pour déplacer les joueurs, collecter des ressources, etc., et le serveur envoie des réponses avec l'état du jeu.
- **Serveur et GUI** : Utilisent des sockets TCP pour envoyer des mises à jour en temps réel sur l'état du jeu, y compris les positions des joueurs et les ressources disponibles.
- **Serveur et Dashboard** : Utilisent des sockets TCP et la bibliothèque `json-c` pour envoyer des informations structurées en JSON sur l'état du serveur, les joueurs, et les équipes.

## Structures Principales

### Structure `struct_t`

La structure principale `struct_t` contient tous les éléments nécessaires à la gestion du serveur et du jeu. Elle regroupe les informations sur les joueurs, les équipes, la carte, les commandes en cours, et bien plus encore. Voici une description détaillée de ses composants :

- **Paramètres généraux** : Informations sur le port, la taille de la carte, le nombre de clients, etc.
- **État du jeu** : Indicateurs de démarrage/arrêt du serveur, état actuel du jeu.
- **Carte** : Structure de données représentant la carte du jeu, avec les ressources disponibles.
- **Joueurs et équipes** : Listes chaînées contenant les informations sur les joueurs et les équipes.
- **Incantations** : Informations sur les incantations en cours.
- **Dashboard** : Informations sur les performances et l'utilisation des ressources du serveur.

### Autres Structures

- **player_t** : Représente un joueur dans le jeu, contenant ses ressources, son état, et ses commandes en cours.
- **team_t** : Représente une équipe dans le jeu, contenant les informations sur les joueurs de l'équipe et les positions des œufs.
- **map_element_t** : Représente une case de la carte, contenant les ressources présentes et les joueurs sur la case.
- **incantation_t** : Représente une incantation en cours, contenant les IDs des joueurs impliqués et la position de l'incantation.
- **dashboard_t** : Représente les informations du tableau de bord, telles que l'utilisation du CPU et de la RAM.

## Communication du Serveur

### Communication avec les IA

La communication entre le serveur et les IA se fait via des sockets TCP. Voici un exemple de séquence de communication :

1. **Connexion de l'IA** :
   - L'IA ouvre une socket sur le port du serveur.
   - Le serveur envoie un message de bienvenue.
   - L'IA envoie le nom de l'équipe.
   - Le serveur envoie le numéro de client et les dimensions du monde.

2. **Envoi de commandes** :
   - L'IA peut envoyer jusqu'à 10 commandes sans attendre de réponse.
   - Le serveur exécute les commandes dans l'ordre de réception et envoie des réponses de confirmation.

### Communication avec le GUI

Le GUI utilise le même protocole de communication que les IA, mais il s'authentifie en tant que GUI en envoyant le nom d'équipe "GRAPHIC". Le GUI reçoit des mises à jour en temps réel sur l'état du jeu, les positions des joueurs, et les ressources.

### Communication avec le Dashboard

Le dashboard est un bonus qui permet d'envoyer des informations de debug et de performance. Le serveur utilise la bibliothèque `json-c` pour formater les données en JSON et les envoyer au dashboard. Les informations envoyées incluent l'état de la carte, les joueurs, les équipes, et des statistiques de performance telles que l'utilisation du CPU et de la RAM.

## Conclusion

Cette documentation couvre l'architecture du serveur Zappy, les structures principales utilisées, et les protocoles de communication avec le GUI, les IA et le dashboard. Le serveur est conçu pour gérer efficacement les connexions multiples et les interactions complexes entre les joueurs et les différentes interfaces, tout en assurant un suivi précis des ressources et des commandes.