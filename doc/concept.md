# concept
nex a pour objectif de construire des réseaux de données structurés, génériques et paramètrables.

## définition
- **Ressource** : donnée conceptuelle qui représente une information, une idée
- **Type** : permet de catégoriser une ressource
- **Interface** : permet de visualiser une ressource
- **Propriété** : permet d'identifier une donnée avec un format spécifique
- **Donnée brut** : donnée identifiée par une ressource, un type et une propriété
- **Modules** : permettent d'effectuer des traitements sur les ressources
- **Connection** : permet de connecter une ressource à une autre via un type de connexion

## structure
- une ressource possède des types, des interfaces, des modules
- un type possède des propriétés, des interfaces, des modules
- une interface peut utiliser différents moteurs de rendus
- les modules lient des actions aux ressources

## idéologie
Le but est d'identifier chaque information et de l'encapsuler dans une structure (ressource) avec un modèle proche
de celui de la mémoire humaine. Il y a donc une séparation entre une information abstraite, et une information brute.

Par exemple, pour un film, on différencie les informations du film (réalisateur, acteur) du film en lui même.

Chaque ressource est connectée à une autre via un ou plusieurs types de connexions. Par exemple, un film sera connecté
à un acteur qui sera connecté à une pub qui sera connectée à un parfum etc ...

### ressource générique
une ressource possèdera certaines propriétés génériques pouvant permettre une autorégulation du réseau
- expiration : date à laquelle l'information est invalidée
- fiabilité : spécifie si les informations contenues dans la ressource sont fiables
(définit par les utilisations ou une source de controle)
- qualité : les informations fournies sont bien présentées (définit par les utilisateurs)
-  réseau : classifie la ressource d'après des domaines classifiés 
(permet de faire le lien entre la ressource et d'autres réseaux de données, ex: )
- auteur : créateurs de la ressources
- source : origine de l'information
- accessibilité
- langue : langue/langage requis pour comprendre l'information 



## réseau
L'unité sur un réseau est un serveur. Les serveurs peuvent communiquer entre eux pour former un réseau.
Un serveur possède ses propres types de ressources ainsi que ses propriétés spécifiques.

L'échange de donnée entre serveur se fait par des régles génériques de conversion, des déductions via les propriétés
ou des règles spécifiques définies par l'utilisateur.

Les clients se connectent au réseau en se connectant à un serveur qui peut être un server local, distant (personnel)
ou un serveur de centralisation.
Les échangent peuvent donc être P2P ou centralisés selon les choix de l'utilisateur.

# systèmes
## notification
### connexions
### propriétés

## recherche
## partage
## synchronisation
## virtualisation
## sécurité

# exemples d'application
## connexion
Soit un forum avec des questions et des réponses.
Une connexion de type "résolution" permet d'associer une question au message 

## news
soit une ressource locale *news*

on connecte la ressource à la ressource *news* de 3 autres serveurs qui fournissent des news dans différents domaines

on peut choisir de :
- visualiser les ressources sur le serveur distant
- synchroniser la ressource via les connexions (téléchargement local des ressources)
- être notifié selon les types de news lors de la création de nouvelles connexions
- partager une ressource *news* avec un autre serveur central ou P2P via envoi direct ou création de connexion
- commenter la news en créant une ressource liée à la news sur les serveurs distants ou local
 
## conversions
soit un gestionnaire de bibliothèque local qui contient entre autre des films et livres



# idées futures
- utilisation d'un réseau de donnée par une IA
- auto régulation d'un réseau de donnée (gestion des redondances, accessibilité, fiabilité, logique des connexions)

# nxi : client

# nex : server