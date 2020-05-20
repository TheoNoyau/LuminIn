![](https://github.com/TheoNoyau/LuminIn/workflows/Test%20master/badge.svg)

# Projet LuminIn 2020

Projet de programmation effectué en groupe par Théo Kerneves et Aymeric Lavedrine.

LuminIn est une réplique du fameux site LinkedIn, en ligne de commande qui possède les principales fonctionnalités qu'a le site LinkedIn, notamment une gestion en base de données, différents status disponibles -entreprise, employé, chercheur d'emploi-, création de profils persistants, recherche d'emploi disponible, recherche de collègues, etc...

# Table des matières

- [Fonctionnement](#fonctionnement)
- [Spécifications pour chaque status](#spécifications-pour-chaque-status)
    - [Fonctionnalités pour une entreprise](#fonctionnalités-pour-une-entreprise)
    - [Fonctionnalités pour un chercheur d'emploi](#fonctionnalités-pour-un-chercheur-demploi)
    - [Fonctionnalités pour un employé](#fonctionnalités-pour-un-employé)
- [Support](#support)

# Fonctionnement {: #fonctionnement }

Pour une utilisation de la version 1.2.0 ou supérieur, installez sqlite3 : `sudo apt-get install sqlite3`

Pour compiler et executer, utilisez : `make app`

Au lancement de l'application, vous vous trouverez sur le menu principal. Plusieurs choix s'offrent à vous :
    - Si vous êtes nouveau sur l'application, vous pouvez créer votre profil. 
    :warning: **Attention à bien vous souvenir de votre identifiant pour une prochaine utilisation!**
    - Si vous êtes déjà inscrit, vous pouvez vous connecter.

Si vous ne trouvez pas l'entreprise pour laquelle vous travaillez, [contactez nous](#support) 

# Spécifications pour chaque status {: #spécifications-pour-chaque-status}

Dans cette section, vous pouvez retrouver les différentes fonctionnalités disponibles à chaque status.

## Fonctionalités pour une entreprise {: #fonctionnalités-pour-une-entreprise}

Vous êtes une entreprise, vous pourrez :

- [ ] Créer votre profil
- [ ] Supprimer votre profil
    - Supprime automatiquement les postes à pourvoir existant
- [ ] Créer le profil d'un poste à pourvoir
- [ ] Supprimer le profil d'un poste pourvu
- [ ] Rechercher parmi les chercheurs d'emploi 

## Fonctionalités pour un chercheur d'emploi {: #fonctionnalités-pour-un-chercheur-demploi}

Vous êtes en recherche d'emploi, vous pourrez :

- [ ] Créer votre profil
- [ ] Modifier votre profil
    - Ajouter des compétences
    - Ajouter un(e) ancien(ne) collègue de travail
    - Modifier votre code postal
- [ ] Transitionner le profil du status «chercheur d'emploi» à un profil «employé»
- [ ] Supprimer votre profil
- [ ] Rechercher parmi les postes à pourvoir qui correspondent à votre profil
- [ ] Rechercher parmi vos anciens collègues

## Fonctionalités pour un employé {: #fonctionnalités-pour-un-employé}

Vous êtes un employé, vous pourrez :

- [ ] Créer votre profil
- [ ] Modifier votre profil
    - Ajouter des compétences
    - Ajouter un(e) ancien(ne) collègue de travail
    - Modifier votre code postal
    - Modifier votre entreprise
- [ ] Transitionner votre profil du status «employé» vers «chercheur d'emploi»
- [ ] Supprimer votre profil
- [ ] Rechercher parmi les postes à pourvoir qui correspondent à votre profil
- [ ] Rechercher parmi vos anciens collègues

Lorsque vous quittez une entreprise, les personnes travaillant à cette entreprise seront ajoutés à votre liste de collègues

# Support {: #support}

- [ ] Pour toutes questions ou problèmes, veuillez contacter notre service support : [kerlav@gmail.com](mailto:kerlav@gmail.com?subject=[GitHub]%LumiIn)

- [ ] Pour en savoir plus sur ce projet, vous pouvez lire [les instructions de travail](https://github.com/TheoNoyau/LuminIn/blob/master/Instructions.md)