/**
 * @file joueur.h
 * @author Gobigan MATHIALAHAN et Eric ZHANG
 * @brief Composant des Joueur et GameState
 * @version 0.1
 * @date 2022-12-31
 *
 * @copyright Copyright (c) 2022
 */

#ifndef SINGE_JOUEUR_H
#define SINGE_JOUEUR_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <ctype.h>
#pragma warning(disable : 4996)

using namespace std;
const int MAX_lettre = 26;
const int MAX_LIGNES = 369085;

struct Joueur
{
    int num;
    char nature;
    float life;
};

struct GameState
{
    enum
    {
        MAX_LETTRE = 26,
    };
    char lettre[MAX_LETTRE];
    int numLettre;               // le nombre de lettre annoncees
    Joueur* joueur;              // Garder les joueur
    int numJoueur;               // nombre de joueur
    int index_joueur;            // position du joueur courant
    char chosenWord[MAX_lettre]; // Garder le mot choisi par le robot
    bool fin_jeu;
};

/**
 * @brief Initialise les structures `gameState` et `joueur`.
 * @param gameState: Pointeur vers la structure `GameState` à initialiser.
 * @param joueur: Pointeur vers la structure `Joueur` à initialiser
 */
void initialiserGameState(GameState* gameState, Joueur* joueur);
/**
 * @brief Cette fonction Renvoie une liste de mots d'un dictionnaire qui correspondent à un préfixe donné.
 *L'appelant est responsable de la libération de la mémoire allouée au tableau et à ses éléments.
 * @param prefix une chaîne représentant le préfixe à rechercher.
 * @param prefixLength un entier représentant la longueur du préfixe.
 * @param numMatchingWords Un pointeur vers un entier où le nombre de mots correspondants sera stocké.
 * @return char** : Un tableau de chaînes alloué dynamiquement contenant les mots correspondants.
 */
char** getMatchingWords(char* prefix, int prefixLength, int* numMatchingWords);

/**
 * @brief Invite l'utilisateur à saisir le nombre de joueurs et leur type (humain ou robot).
 *
 * @param gameState Un pointeur vers la structure GameState contenant des informations sur la partie en cours.
 */
void saisirJoueur(GameState* gameState, char* playerTypeString);

/**
 * @brief Obtient l'entrée du joueur, soit de l'entrée humaine, soit du robot.
 *
 * @param gameState  un pointeur vers l'état actuel du jeu
 * @param player un pointeur vers le joueur actuel
 * @return l'entrée du joueur, soit une lettre ou un mot si le joueur précédent a saisi '?'
 */
char getPlayerInput(GameState* gameState, Joueur* player);

/**
 * @brief Vérifier si un mot donné existe dans le dictionnaire.
 *
 * @param word : Le mot à rechercher dans le dictionnaire.
 * @return true : si le mot existe
 * @return false : sinon
 */
bool wordExists(const char* word);

/**
 * @brief fonction qui gère le cas où le joueur actuel saisit '!' dans le jeu.
 * Il vérifie si le mot formé par les lettres annoncées existe dans le dictionnaire, et si c'est le cas, le joueur prend un quart de singe
 *  Si la mot n'existe pas, le joueur prend un quart de singe vie.
 * @param gameState un pointeur vers l'état actuel du jeu
 */
void pointExclamation(GameState* gameState);

/**
 * @brief Gère l'action "?" dans le jeu.
 * Le joueur précédant le joueur actuel doit entrer un mot auquel il pense que le joueur actuel pense.
 * Si le mot ne commence pas par les lettres annoncées jusqu'ici, le joueur précédent prend un quart de singe.
 * Si le mot n'existe pas, le joueur précédent prend un quart de singe.
 * @param gameState : pointeur vers l'état actuel du jeu.
 * @param index_joueur : pointeur vers le joueur actuel.
 */
void pointInterrogation(GameState* gameState, Joueur* index_joueur);

/**
 * @brief Cette fonction traite la lettre d'entrée donnée par un joueur pendant le jeu. Si le mot formé par les lettres précédentes
 * et que la nouvelle lettre d'entrée existe dans le dictionnaire, le joueur qui a donné la lettre d'entrée perd un quart de singe.
 * Si le mot n'existe pas, la lettre saisie est ajoutée à la liste des lettres qui ont été jouées.
 * @param input : La lettre d'entrée donnée par le joueur.
 * @param gameState : L'état actuel du jeu.
 * @param index_jouer : Le joueur qui a donné la lettre d'entrée.
 */
void inputLettre(char input, GameState* gameState, Joueur* index_jouer);

/**
 * @brief Fonction qui permet à un joueur robot d'effectuer un mouvement dans le jeu.
 *
 * @param gameState : gameState Pointeur vers l'état actuel du jeu.
 * @return char : La lettre que le joueur robot a choisi d'ajouter au mot courant.
 */
char playRobot(GameState* gameState);
/**
 * @brief Vérifiez si le jeu est terminé.
 * La partie est terminée si le quart de singe d'un joueur atteint 1.
 * @param gameState: Pointeur vers la structure GameState.
 */
void checkGameOver(GameState* gameState);

/**
 * @brief Cette fonction affiche le quart de singe que chaque joueur a pris à la fin de la partie.
 *
 * @param gameState un pointeur vers l'état actuel du jeu
 */
void showQuartSinge(GameState* gameState);


void deleteallo(GameState* gameState, Joueur* joueur);

#endif // SINGE_JOUEUR_H
