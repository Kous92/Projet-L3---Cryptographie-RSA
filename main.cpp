#include <iostream>
#include <limits>
#include "cryptage_rsa.h"
#include "menu.h"

using namespace std;

int main(void)
{
	system("clear");

	int choix = 0, option = 0;

	do
	{
		choix = menu_principal();

		switch (choix)
		{
			case 1:
			{
				vector<long long> n = saisie_securisee_n();
				// n est vérifié tel qu'il donne exactement 2 facteurs de nombres premiers
				RSA rsa1(n[2]);
				rsa1.generationClePrivee();
				Pause();

				// Cryptage et décryptage
				do
				{
					option = menu_cryptage();

					switch (option)
					{
						// Cryptage d'un message
						case 1:
						{
							long message = saisie_securisee_message();
							rsa1.cryptageRSA(message);
							break;
						}

						// Décryptage d'un message
						case 2:
						{
							long message = saisie_securisee_message();
							rsa1.decryptageRSA(message);
							break;
						}

						case 0:
						break;

						default:
						break;
					}
					Pause();

				} while (option != 0);

				break;
			}

			case 2:
			{
				vector<long long> n = saisie_securisee_n();
				long long e = saisie_securisee_e(n);

				// n et e sont vérifiés tel que e premier avec phi(n)
				RSA rsa2(n[2], e);
				rsa2.generationClePrivee();
				Pause();

				// Cryptage et décryptage
				do
				{
					option = menu_cryptage();

					switch (option)
					{
						// Cryptage d'un message
						case 1:
						{
							long message = saisie_securisee_message();
							rsa2.cryptageRSA(message);
							break;
						}

						// Décryptage d'un message
						case 2:
						{
							long message = saisie_securisee_message();
							rsa2.decryptageRSA(message);
							break;
						}

						case 0:
						break;

						default:
						break;
					}
					Pause();

				} while (option != 0);

				break;
			}

			case 3:
			{
				long long p = saisie_securisee_pq("p");
				long long q = saisie_securisee_pq("q");
				long long e = saisie_securisee_e(p, q);

				// p, q et e sont vérifiés tel que e premier avec phi(n) -> n = p * q
				RSA rsa3(p, q, e);
				rsa3.generationClePrivee();
				Pause();

				// Cryptage et décryptage
				do
				{
					option = menu_cryptage();

					switch (option)
					{
						// Cryptage d'un message
						case 1:
						{
							long message = saisie_securisee_message();
							rsa3.cryptageRSA(message);
							break;
						}

						// Décryptage d'un message
						case 2:
						{
							long message = saisie_securisee_message();
							rsa3.decryptageRSA(message);
							break;
						}

						case 0:
						break;

						default:
						break;
					}
					Pause();

				} while (option != 0);

				break;
			}

			case 0:
			cout << endl << ">>> Projet Cryptage RSA - Juin 2017" << endl << endl;
			break;

			default:
			break;
		}
		Pause();

	} while (choix != 0);	

	// RSA rsa1(12743417, 15997);
	// rsa1.generationClePublique();
	// rsa1.cryptageRSA(2160);
	// rsa1.decryptageRSA(34571);

	return 0;
}