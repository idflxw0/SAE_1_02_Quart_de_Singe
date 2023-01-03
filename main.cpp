/**
 * @file main.cpp
 * @author Gobigan MATHIALAHAN et Eric ZHANG
 * @brief Le main pour lancer le jeu
 * @version 0.1
 * @date 2022-12-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include "joueur.h"

int main(int argc, char** argv)
{
    GameState gameState;
    Joueur joueur;
    initialiserGameState(&gameState, &joueur);

    if (argc < 2) {
        cerr << "Pas assez joueur" << endl;
        return 1;
    }

    char* playerTypeString = argv[1];

    saisirJoueur(&gameState, playerTypeString);
    while (!gameState.fin_jeu)
    {
        Joueur* joueur_index = &gameState.joueur[gameState.index_joueur];
        cout << joueur_index->num << joueur_index->nature << ", (";
        for (int i = 0; i < gameState.numLettre; ++i)
        {
            cout << gameState.lettre[i];
        }
        cout << ") > ";
        char input = getPlayerInput(&gameState, joueur_index);
        switch (input)
        {
        case '!':
            pointExclamation(&gameState);
            break;
        case '?':
            pointInterrogation(&gameState, &joueur);
            break;
        default:
            inputLettre(input, &gameState, &joueur);
            break;
        }
        gameState.index_joueur = (gameState.index_joueur) % gameState.numJoueur;
        checkGameOver(&gameState);
    }
    cout << "La partie est finie" << endl;
    deleteallo(&gameState, &joueur);
    return 0;
}
