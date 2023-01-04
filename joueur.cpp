/**
 * @file joueur.cpp
 * @author  Gobigan MATHIALAHAN et Eric ZHANG
 * @brief Composant des Joueur et GameState
 * @version 0.1
 * @date 2022-12-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "joueur.h"
void initialiserGameState(GameState *gameState, Joueur *joueur)
{
    gameState->numLettre = 0;
    gameState->numJoueur = 0;
    gameState->index_joueur = 0;
    gameState->fin_jeu = false;
    gameState->joueur = new Joueur[MAX_lettre];

    // Initialiser le strut joueur
    joueur->life = 0;
    joueur->nature = 0;
    joueur->num = 0;
}

bool wordExists(const char *word)
{
    bool found = false;
    ifstream dictionary("ods4.txt");
    char line[MAX_lettre];
    while (dictionary.getline(line, MAX_lettre))
    {
        if (strcmp(line, word) == 0)
        {
            found = true;
            break;
        }
    }
    dictionary.close();
    return found;
}

char **getMatchingWords(char *prefix, int prefixLength, int *numMatchingWords)
{
    const int MAX_MATCHING_WORDS = MAX_LIGNES;
    char **matchingWords = new char *[MAX_MATCHING_WORDS];
    *numMatchingWords = 0;

    ifstream dictionary("ods4.txt");
    char line[MAX_lettre];

    while (dictionary.getline(line, MAX_lettre))
    {
        line[strlen(line) - 1] = '\0';
        if (strncmp(line, prefix, prefixLength) == 0)
        {
            if (*numMatchingWords < MAX_MATCHING_WORDS)
            {
                matchingWords[*numMatchingWords] = new char[MAX_lettre];
                strcpy(matchingWords[*numMatchingWords], line);
                (*numMatchingWords)++;
            }
        }
    }
    dictionary.close();
    return matchingWords;
}

void saisirJoueur(GameState *gameState, char *playerTypeString)
{
    int numPlayers = strlen(playerTypeString);
    if (numPlayers < 2)
    {
        cerr << "Pas assez de joueur" << endl;
    }
    gameState->numJoueur = numPlayers;
    for (int i = 0; i < gameState->numJoueur; ++i)
    {
        playerTypeString[i] = toupper(playerTypeString[i]);
        if (playerTypeString[i] == 'H')
        {
            gameState->joueur[i].nature = 'H';
        }
        else if (playerTypeString[i] == 'R')
        {
            gameState->joueur[i].nature = 'R';
        }
        else
        {
            cerr << "Lettre invalide" << endl;
            break;
        }
        gameState->joueur[i].num = i + 1;
        gameState->joueur[i].life = 0;
    }
}

char getPlayerInput(GameState *gameState, Joueur *player)
{
    if (player->nature == 'H')
    {
        char input;
        cin >> input;
        return toupper(input);
    }
    else if (player->nature == 'R')
    {
        return playRobot(gameState);
    }
    else
    {
        cerr << "Invalide type joueur" << endl;
    }
    return 0;
}
void pointExclamation(GameState *gameState)
{
    Joueur *index_player = &gameState->joueur[gameState->index_joueur];
    index_player->life += 0.25;

    cout << "le joueur " << index_player->num << index_player->nature << " abandonne la manche et prend un quart de singe" << endl;
    showQuartSinge(gameState);

    // gameState->index_joueur = (gameState->index_joueur + gameState->numJoueur - 1) % gameState->numJoueur;
    // gameState->numLettre = 0;
    gameState->index_joueur = (gameState->index_joueur + gameState->numJoueur - 1) % gameState->numJoueur;
    gameState->index_joueur = (gameState->index_joueur + 1) % gameState->numJoueur; // give the next player a chance to play
    gameState->numLettre = 0;
}
void pointInterrogation(GameState *gameState, Joueur *index_joueur)
{
    Joueur *previousPlayer = &gameState->joueur[(gameState->index_joueur + gameState->numJoueur - 1) % gameState->numJoueur];
    Joueur *currentPlayer = &gameState->joueur[gameState->index_joueur];
    char word[MAX_lettre];
    if (previousPlayer->nature == 'H')
    {
        cout << previousPlayer->num << previousPlayer->nature << ", saisir le mot > ";
        cin >> word;
    }
    else if (previousPlayer->nature == 'R')
    {
        strcpy(word, gameState->chosenWord);
        cout << "Le mot choisi par " << previousPlayer->num << previousPlayer->nature << ": " << gameState->chosenWord << endl;
    }
    else
    {
        return;
    }
    for (int i = 0; i < strlen(word); i++)
    {
        word[i] = toupper(word[i]);
    }
    if ((strncmp(word, gameState->lettre, gameState->numLettre) != 0) && (strncmp(gameState->chosenWord, gameState->lettre, gameState->numLettre) != 0))
    {
        previousPlayer->life += 0.25;
        cout << "le mot " << word << " ne commence pas par les lettres attendues, le joueur " << previousPlayer->num << previousPlayer->nature << " prend un quart de singe" << endl;

        showQuartSinge(gameState);
    }
    else if (wordExists(word))
    {
        currentPlayer->life += 0.25;
        cout << "le mot " << word << " existe, le joueur " << currentPlayer->num << currentPlayer->nature << " prend un quart de singe" << endl;
        gameState->index_joueur++;
        showQuartSinge(gameState);
    }
    else if ((wordExists(word)) && (wordExists(gameState->chosenWord)))
    {
        currentPlayer->life += 0.25;
        cout << "Le mot " << word << " existe. Joueur " << currentPlayer->num << currentPlayer->nature << " prend un quart de singe" << endl;
        gameState->index_joueur++;
        showQuartSinge(gameState);
    }
    // Si le mot n'existe pas dand le dictionnaire
    else
    {
        previousPlayer->life += 0.25;
        cout << "le mot " << word << " n'existe pas. Joueur " << previousPlayer->num << previousPlayer->nature << " prends un quart de singe" << endl;
        showQuartSinge(gameState);
    }
    // gameState->index_joueur = (gameState->index_joueur +1) % gameState->numJoueur;
    gameState->index_joueur = (gameState->index_joueur + gameState->numJoueur - 1) % gameState->numJoueur;
    gameState->numLettre = 0;
}

void inputLettre(char input, GameState *gameState, Joueur *index_joueur)
{
    // const int MAX_MOT = 26;
    char word[MAX_lettre];
    strncpy(word, gameState->lettre, gameState->numLettre);
    word[gameState->numLettre] = input;
    word[gameState->numLettre + 1] = '\0';
    Joueur *currentPlayer = &gameState->joueur[gameState->index_joueur];
    if (wordExists(word) && gameState->numLettre > 2)
    {
        if (currentPlayer->nature == 'H' || currentPlayer->nature == 'R')
        {
            currentPlayer->life += 0.25;
        }
        // index_joueur->life += 0.25;
        cout << "le mot " << word << " existe, le joueur " << currentPlayer->num << currentPlayer->nature << " prend un quart de singe" << endl;
        showQuartSinge(gameState);

        // gameState->index_joueur = (gameState->index_joueur + gameState->numJoueur - 1) % gameState->numJoueur;
        // gameState->index_joueur = -1;
        gameState->index_joueur = (gameState->index_joueur + gameState->numJoueur - 1) % gameState->numJoueur;
        gameState->numLettre = 0;
        // gameState->index_joueur = (gameState->index_joueur + gameState->numJoueur) % gameState->numJoueur;
    }
    else
    {
        gameState->lettre[gameState->numLettre] = input;
        gameState->numLettre++;
    }
    gameState->index_joueur = (gameState->index_joueur + 1) % gameState->numJoueur;
}

char playRobot(GameState *gameState)
{
    char prefix[MAX_lettre];
    strncpy(prefix, gameState->lettre, gameState->numLettre);
    prefix[gameState->numLettre] = '\0';

    // Get a list of words that match the prefix
    int numMatchingWords;
    char **matchingWords = getMatchingWords(prefix, gameState->numLettre, &numMatchingWords);

    // choisir un mot au hasard dans la liste des mots correspondants
    if (numMatchingWords > 0)
    {
        int randomIndex = rand() % numMatchingWords;
        char *chosenWord = matchingWords[randomIndex];

        // Stocke le mot choisi dans gameState
        strcpy(gameState->chosenWord, chosenWord);
        if (gameState->lettre[gameState->numLettre - 1] == '?')
        {
            return chosenWord[0];
        }
        if (gameState->lettre[gameState->numLettre - 1] == '!')
        {
            cout << chosenWord[gameState->numLettre] << endl;
            return chosenWord[gameState->numLettre];
        }
        else
        {
            // Retourne la lettre suivante dans le mot choisi
            cout << chosenWord[gameState->numLettre] << endl;
            return chosenWord[gameState->numLettre];
        }
    }
    // Si aucun mot correspondant n'a �t� trouv� return '?'
    cout << '?' << endl;
    return '?';
}
void checkGameOver(GameState *gameState)
{
    for (int i = 0; i < gameState->numJoueur; i++)
    {
        if (gameState->joueur[i].life >= 1)
        {
            gameState->fin_jeu = true;
            return;
        }
    }
}
void showQuartSinge(GameState *gameState)
{
    for (int i = 0; i < gameState->numJoueur; i++)
    {
        Joueur player = gameState->joueur[i];
        cout << player.num << player.nature << " : " << player.life << "; ";
    }
    cout << " " << endl;
}

void deleteallo(GameState *gameState, Joueur *joueur)
{
    delete[] gameState->joueur;
}