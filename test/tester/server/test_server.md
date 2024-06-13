# test_server.js

## Description

`test_server.js` est un programme en Node.js conçu pour se connecter à un serveur via TCP, envoyer les messages "GRAPHIC\n" et "GRAPHIC", et afficher les réponses reçues du serveur. Ce programme est utile pour tester et déboguer les connexions GUI avec le serveur.

## Prérequis

- Node.js installé sur votre machine. Vous pouvez télécharger et installer Node.js depuis [nodejs.org](https://nodejs.org/).

## Installation

1. Clonez ce dépôt ou téléchargez le fichier `test_server.js`.
2. Assurez-vous que Node.js est installé en exécutant la commande suivante dans votre terminal :

```sh
node -v
```

Cette commande devrait afficher la version de Node.js installée.

## Utilisation

### Lancer le programme

Pour lancer le programme, exécutez la commande suivante dans votre terminal :

```sh
node test_server.js <hostname> <port>
```

Remplacez `<hostname>` par l'adresse IP ou le nom de domaine du serveur, et `<port>` par le numéro de port. Par exemple :

```sh
node test_server.js 127.0.0.1 8080
```

### Exemple de sortie

```sh
Connected to server
Response from server: [réponse du serveur après "GRAPHIC\n"]
Second response from server: [réponse du serveur après "GRAPHIC"]
Connection closed
```

## Modification

### Changer les messages envoyés

Si vous souhaitez modifier les messages envoyés au serveur, vous pouvez éditer les lignes suivantes dans `test_server.js` :

```javascript
// Envoi du message "GRAPHIC\n"
client.write('GRAPHIC\n');

// Envoi du message "GRAPHIC"
client.write('GRAPHIC');
```

Remplacez `'GRAPHIC\n'` et `'GRAPHIC'` par les messages que vous souhaitez envoyer.

### Ajouter des étapes supplémentaires

Si vous souhaitez ajouter des étapes supplémentaires après l'envoi des messages, vous pouvez le faire en ajoutant des handlers pour les événements `data` et `close` du client. Par exemple :

```javascript
client.on('data', (data) => {
    console.log('Response from server: ' + data.toString());

    // Ajoutez ici des étapes supplémentaires

    // Envoi du message "GRAPHIC"
    client.write('GRAPHIC');
    
    client.on('data', (newData) => {
        console.log('Second response from server: ' + newData.toString());
        
        // Ajoutez ici des étapes supplémentaires

        client.destroy(); // Fermer la connexion
    });
});
```

## Dépannage

### Erreurs courantes

- **ERROR: connect ECONNREFUSED** : Assurez-vous que le serveur est en cours d'exécution et que l'adresse IP et le port sont corrects.
- **ERROR: invalid hostname/IP address** : Vérifiez que le nom d'hôte ou l'adresse IP fournis sont valides.
- **Usage: node test_server.js <hostname> <port>** : Assurez-vous de fournir à la fois le nom d'hôte et le port lors de l'exécution du programme.

### Questions et contributions

Si vous avez des questions ou des suggestions, veuillez ouvrir une issue sur le dépôt GitHub. Les contributions sont également les bienvenues. Pour contribuer, veuillez créer une branche avec vos modifications et ouvrir une pull request.

## Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus de détails.
