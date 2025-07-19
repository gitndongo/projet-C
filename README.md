```text
   ____           _         _   _       _        ____            _ _      
  / ___|___  _ __| |_ _   _| | | | __ _| |_ ___ / ___|___  _ __ (_) | ___ 
 | |   / _ \| '__| __| | | | |_| |/ _` | __/ _ \ |   / _ \| '_ \| | |/ _ \
 | |__| (_) | |  | |_| |_| |  _  | (_| | ||  __/ |__| (_) | | | | | |  __/
  \____\___/|_|   \__|\__, |_| |_|\__,_|\__\___|\____\___/|_| |_|_|_|\___|
                      |___/                                              
     📚 Gestion des Étudiants, Classes, Matières et Notes en C

## 🎯 Objectif

Ce projet est une **application en langage C** permettant de gérer :
- les **étudiants 👨‍🎓**
- les **classes 🏫**
- les **matières 📚**
- et les **notes 📊**

Le tout stocké dans des fichiers `.csv` pour une gestion simplifiée et durable.

---

## 🗂️ Arborescence du projet

```
gestion_scolarite/
│
├── main.c                         # Menu principal
├── classes.c / classes.h         # Gestion des classes
├── etudiants.c / etudiants.h     # Gestion des étudiants
├── matiere.c / matiere.h         # Gestion des matières
├── notes.c / notes.h             # Gestion des notes
│
├── fichiers CSV :
│   ├── classes.csv
│   ├── etudiants.csv
│   ├── matieres.csv
│   └── notes.csv
│
└── README.md                     # Ce fichier
```

---

## 🚀 Compilation

Compilez le projet avec `gcc` (ou tout compilateur C) :

```bash
gcc main.c classes.c etudiants.c matiere.c notes.c -o executable
```

---

## ▶️ Exécution

```bash
./executable
```

---

## 📌 Fonctionnalités

- 🔹 **Étudiants**
  - Ajouter / Modifier / Supprimer un étudiant
  - Lister les étudiants
  - Lister les étudiants d’une classe
- 🔸 **Classes**
  - Gérer les classes (code, nom, etc.)
- 🔹 **Matières**
  - Lister les matières d'une classe
  - Modifier les matières enseignées dans une classe
- 🔸 **Notes**
  - Ajouter / Modifier / Supprimer les notes
  - Afficher les notes par étudiant ou par classe

---

## 💾 Format des fichiers CSV

- `etudiants.csv` → `id,nom,prenom,codeClasse`
- `classes.csv` → `code,nom`
- `matieres.csv` → `id,nom`
- `notes.csv` → `etudiant_id,matiere_id,note_cc,note_ds`

---

## 🙌 Auteurs

- Projet réalisé par **m2d, Marame Der, Mouhamed Ndongo, Khady Diaw **
- Langage : `C`
- Encadré par : **M. ...**

---

## 📸 Aperçu

```bash
   ===== MENU PRINCIPAL =====
   📘 1. Gestion des Étudiants
   🏫 2. Gestion des Classes
   📚 3. Gestion des Matières
   📊 4. Gestion des Notes
   ❌ 0. Quitter
```
