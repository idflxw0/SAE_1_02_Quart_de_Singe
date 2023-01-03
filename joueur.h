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
 * @param gameState: Pointeur vers la structure `GameState` � initialiser.
 * @param joueur: Pointeur vers la structure `Joueur` � initialiser
 */
void initialiserGameState(GameState* gameState, Joueur* joueur);
/**
 * @brief Cette fonction Renvoie une liste de mots d'un dictionnaire qui correspondent � un pr�fixe donn�.
 *L'appelant est responsable de la lib�ration de la m�moire allou�e au tableau et � ses �l�ments.
 * @param prefix une cha�ne repr�sentant le pr�fixe � rechercher.
 * @param prefixLength un entier repr�sentant la longueur du pr�fixe.
 * @param numMatchingWords Un pointeur vers un entier o� le nombre de mots correspondants sera stock�.
 * @return char** : Un tableau de cha�nes allou� dynamiquement contenant les mots correspondants.
 */
char** getMatchingWords(char* prefix, int prefixLength, int* numMatchingWords);

/**
 * @brief Invite l'utilisateur � saisir le nombre de joueurs et leur type (humain ou robot).
 *
 * @param gameState Un pointeur vers la structure GameState contenant des informations sur la partie en cours.
 */
void saisirJoueur(GameState* gameState, char* playerTypeString);

/**
 * @brief Obtient l'entr�e du joueur, soit de l'entr�e humaine, soit du robot.
 *
 * @param gameState  un pointeur vers l'�tat actuel du jeu
 * @param player un pointeur vers le joueur actuel
 * @return l'entr�e du joueur, soit une lettre ou un mot si le joueur pr�c�dent a saisi '?'
 */
char getPlayerInput(GameState* gameState, Joueur* player);

/**
 * @brief V�rifier si un mot donn� existe dans le dictionnaire.
 *
 * @param word : Le mot � rechercher dans le dictionnaire.
 * @return true : si le mot existe
 * @return false : sinon
 */
bool wordExists(const char* word);

/**
 * @brief fonction qui g�re le cas o� le joueur actuel saisit '!' dans le jeu.
 * Il v�rifie si le mot form� par les lettres annonc�es existe dans le dictionnaire, et si c'est le cas, le joueur prend un quart de singe
 *  Si la mot n'existe pas, le joueur prend un quart de singe vie.
 * @param gameState un pointeur vers l'�tat actuel du jeu
 */
void pointExclamation(GameState* gameState);

/**
 * @brief G�re l'action "?" dans le jeu.
 * Le joueur pr�c�dant le joueur actuel doit entrer un mot auquel il pense que le joueur actuel pense.
 * Si le mot ne commence pas par les lettres annonc�es jusqu'ici, le joueur pr�c�dent prend un quart de singe.
 * Si le mot n'existe pas, le joueur pr�c�dent prend un quart de singe.
 * @param gameState : pointeur vers l'�tat actuel du jeu.
 * @param index_joueur : pointeur vers le joueur actuel.
 */
void pointInterrogation(GameState* gameState, Joueur* index_joueur);

/**
 * @brief Cette fonction traite la lettre d'entr�e donn�e par un joueur pendant le jeu. Si le mot form� par les lettres pr�c�dentes
 * et que la nouvelle lettre d'entr�e existe dans le dictionnaire, le joueur qui a donn� la lettre d'entr�e perd un quart de singe.
 * Si le mot n'existe pas, la lettre saisie est ajout�e � la liste des lettres qui ont �t� jou�es.
 * @param input : La lettre d'entr�e donn�e par le joueur.
 * @param gameState : L'�tat actuel du jeu.
 * @param index_jouer : Le joueur qui a donn� la lettre d'entr�e.
 */
void inputLettre(char input, GameState* gameState, Joueur* index_jouer);

/**
 * @brief Fonction qui permet � un joueur robot d'effectuer un mouvement dans le jeu.
 *
 * @param gameState : gameState Pointeur vers l'�tat actuel du jeu.
 * @return char : La lettre que le joueur robot a choisi d'ajouter au mot courant.
 */
char playRobot(GameState* gameState);
/**
 * @brief V�rifiez si le jeu est termin�.
 * La partie est termin�e si le quart de singe d'un joueur atteint 1.
 * @param gameState: Pointeur vers la structure GameState.
 */
void checkGameOver(GameState* gameState);

/**
 * @brief Cette fonction affiche le quart de singe que chaque joueur a pris � la fin de la partie.
 *
 * @param gameState un pointeur vers l'�tat actuel du jeu
 */
void showQuartSinge(GameState* gameState);


void deleteallo(GameState* gameState, Joueur* joueur);

#endif // SINGE_JOUEUR_H
