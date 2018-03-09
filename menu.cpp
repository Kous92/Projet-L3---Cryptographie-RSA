#include <iostream>
#include <limits>
#include "menu.h"

using namespace std;

void Pause()
{
    wcout << L"Appuyer sur entrée pour continuer ";
    cin.ignore().get(); // Cette commande de saisie sécurisée ordonne a l'utilisateur d'appuyer sur entrée (et seul entrée marche)
    cout << endl;
    
    return;
}

int menu_principal()
{
	system("clear");

	cout << "********************************************************************" << endl;
	wcout << L"*** Mini-projet Théorie des groupes et application: Cryptage RSA ***" << endl;
	wcout << L"***                 Créé par Koussaïla BEN MAMAR                 ***" << endl;
	cout << "********************************************************************" << endl << endl;

	int choix = 0;
	bool check = false;

	wcout << L"1 - Démarrer avec n" << endl;
	wcout << L"2 - Démarrer avec n et e" << endl;
	wcout << L"3 - Démarrer avec p, q et e (recommandé)" << endl;
	cout << "0 - Quitter" << endl << endl;

	// Saisie sécurisée
	do
	{
		cout << "Votre choix: ";
		cin >> choix;

		if (cin.fail())
		{
			cerr << "Erreur: SAISIE INVALIDE !" << endl;
			// Les 2 lignes suivantes permettent de vider le buffer: cela assure une nouvelle saisie sans avoir de boucle infinie !!!
 			cin.clear(); // Effacer les bits d'erreurs
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Supprimer la ligne erronée dans le buffer

			check = false;
		}
		else 
		{
			if ((choix < 0) || (choix > 3))
			{
				cerr << "Erreur: CHOIX INVALIDE !" << endl;
			}

			check = true;
		}

	} while (((choix < 0) || (choix > 3)) || (check == false));

	return choix;
}

int menu_cryptage()
{
	system("clear"); // system("cls") sur Windows

	cout << "********************************************************************" << endl;
	wcout << L"*** Mini-projet Théorie des groupes et application: Cryptage RSA ***" << endl;
	wcout << L"***                 Créé par Koussaïla BEN MAMAR                 ***" << endl;
	cout << "********************************************************************" << endl << endl;

	int choix = 0;
	bool check = false;

	wcout << L"1 - Saisir un message (nombre) à crypter" << endl;
	wcout << L"2 - Saisir un message (nombre) à décrypter" << endl;
	cout << "0 - Retour au menu principal" << endl << endl;

	// Saisie sécurisée
	do
	{
		cout << "Votre choix: ";
		cin >> choix;

		if (cin.fail())
		{
			cerr << "Erreur: SAISIE INVALIDE !" << endl;
			// Les 2 lignes suivantes permettent de vider le buffer: cela assure une nouvelle saisie sans avoir de boucle infinie !!!
 			cin.clear(); // Effacer les bits d'erreurs
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Supprimer la ligne erronée dans le buffer

			check = false;
		}
		else 
		{
			if ((choix < 0) || (choix > 2))
			{
				cerr << "Erreur: CHOIX INVALIDE !" << endl;
			}

			check = true;
		}

	} while (((choix < 0) || (choix > 2)) || (check == false));

	return choix;
}