#include <iostream>
#include <limits>
#include <cmath>
#include <sstream>
#include <vector>
#include <iomanip>
#include "cryptage_rsa.h"

using namespace std;

bool testPrimaliteNombre(long long n)
{
	// On ne compte pas le nombre 1
    if (n < 2)
  	{
        return false;
  	}
	
	// 2 est premier
	if (n == 2)
	{
        return true;
	}

	// Si un nombre est divisible par 2, il n'est pas premier
    if (n % 2 == 0)
    {
        return false;
    }

    // On teste tous les nombres de 3 à racine(n) avec itérations de 2.
    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
    	// Si n est divisible par i, il n'est pas premier
        if ((n % i) == 0)
        {
            return false;
        }
    }

    return true;
}

long long PGCD(long long a, long long b)
{
	long long temp, q, r;

	// Commutation: a devient b et b devient a si b > a
	if (a < b)
	{
		temp = b; // Sauvegarde de b dans une variable temporaire
		b = a; // b devient a (la plus grande valeur, le dividende)
		b = temp; // La variable temporaire devient b (le diviseur)
	}

	// Méthode itérative pour le calcul du PGCD: l'algorithme d'Euclide
	do
	{
		q = (long long)(a/ b); // Le quotient est la partie entière du dividende/diviseur (q = partie entière de a/b) -> Troncature du résultat par transtypage. 
		r = a % b; // Le reste de la division euclidienne s'obtient par le modulo de a et de b d'ou r = a - bq.
		
		if (r != 0) // Prochaine division si le reste n'est pas nul
		{
			a = b; // Le diviseur deviendra le dividende
			b = r; // Le reste deviendra le diviseur
		}

	} while (r != 0); // Tant que le reste ne sera pas nul, on continue l'algorithme d'Euclide
	
	return b; // PGCD = diviseur ou avant-dernier reste = 1
}

vector<long long> decompositionFacteursNombresPremiers(long long n)
{
	bool premier = true;
	long long dividende = n;
	int nombre_facteurs_premiers = 0;
	vector <long long> facteurs;

    for (int i = 2; i <= (dividende / i); i++) 
    {
        while ((dividende % i) == 0)
        {
            facteurs.push_back(i);
            nombre_facteurs_premiers++;
            dividende = dividende / i;
        }
    }
    
    if (dividende > 1) 
    {
        facteurs.push_back(dividende);
        nombre_facteurs_premiers++;
    }

   return facteurs;
}

// Retourne n, p et q
vector<long long> saisie_securisee_n()
{
	system("clear");

	long long n;
	bool check = false, premier = false;

	vector<long long> verification_facteurs_premiers;

	do
	{
		cout << ">>> Votre nombre n: ";
		cin >> n;

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
			verification_facteurs_premiers = decompositionFacteursNombresPremiers(n);

			if (verification_facteurs_premiers.size() > 2)
		   	{
		   		wcout << L" -> ERREUR: Votre nombre " << n << L" a plus de 2 facteurs premiers !" << endl << endl;
		   		premier = false;
		   		verification_facteurs_premiers.clear();
		   	}
		   	else if (verification_facteurs_premiers.size() < 2)
		   	{
		   		wcout << L" -> ERREUR: Votre nombre " << n << L" est facteur premier unique !" << endl << endl;
		   		premier = false;
		   		verification_facteurs_premiers.clear();
		   	}
		   	else
		   	{
		   		// Ici on a exactement 2 facteurs de nombres premiers, on peut donc avec p et q
		   		cout << " -> Votre nombre est valide." << endl << endl;
		   		premier = true;
		   		verification_facteurs_premiers.push_back(n);
		   	}

			check = true;
		}

	} while ((check == false) || (premier == false));

	return verification_facteurs_premiers;
}

long long saisie_securisee_e(vector<long long> n)
{
	system("clear");

	long long e, phi_n;
	bool check = false, premier = false;
	phi_n = (n[0] - 1) * (n[1] - 1);

	do
	{
		wcout << L">>> Votre nombre e (doit être premier avec " << phi_n << "): ";
		cin >> e;

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
			if (PGCD(phi_n, e) != 1)
			{
				wcout << L" -> ERREUR: Votre nombre " << e << L" n'est pas premier à " << phi_n << L" (PGCD = " << PGCD(phi_n, e) << ") !" << endl << endl;
				premier = false;
			}
			else if (e >= phi_n)
			{
				wcout << L" -> ERREUR: Votre nombre " << e << L" doit être strictement inférieur à " << phi_n << L" !" << endl << endl;
				premier = false;
			}
			else
			{ 
				premier = true;
			}

			check = true;
		}

	} while ((check == false) || (premier == false));

	return e;
}

long long saisie_securisee_e(long long p, long long q)
{
	system("clear");

	long long e, phi_n;
	bool check = false, premier = false;
	phi_n = (p - 1) * (q - 1);

	do
	{
		wcout << L">>> Votre nombre e (doit être premier avec " << phi_n << "): ";
		cin >> e;

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
			if (PGCD(phi_n, e) != 1)
			{
				wcout << L" -> ERREUR: Votre nombre " << e << L" n'est pas premier à " << phi_n << L" (PGCD = " << PGCD(phi_n, e) << ") !" << endl << endl;
				premier = false;
			}
			else if (e >= phi_n)
			{
				wcout << L" -> ERREUR: Votre nombre " << e << L" doit être strictement inférieur à " << phi_n << L" !" << endl << endl;
				premier = false;
			}
			else
			{ 
				premier = true;
			}

			check = true;
		}

	} while ((check == false) || (premier == false));

	return e;
}

long long saisie_securisee_pq(string str)
{
	system("clear");

	long long valeur;
	bool check = false, premier = false;

	do
	{
		cout << ">>> Votre nombre " << str;
		wcout << L" (doit être premier): ";
		cin >> valeur;

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
			if (!testPrimaliteNombre(valeur))
			{
				cout << " -> ERREUR: Votre nombre " << valeur << " n'est pas premier !" << endl << endl;
				premier = false;
			}
			else
			{ 
				premier = true;
			}

			check = true;
		}

	} while ((check == false) || (premier == false));

	return valeur;
}

long long saisie_securisee_message()
{
	system("clear");

	long long message;
	bool check = false;

	do
	{
		cout << ">>> Votre message (sous forme de nombre): ";
		cin >> message;

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
			check = true;
		}

	} while (check == false);

	return message;
}

RSA::RSA(long long n)
{
	system("clear");

	cout << ">>> Initialisation avec n = " << n << endl;
	this->n = n;

	decompositionNombresPremiers();
	phiN();
	generationClePublique();
}

RSA::RSA(long long n, long long e)
{
	system("clear");

	wcout << L">>> Initialisation avec n = " << n << L" et la clé publique e = " << e << endl;
	this->n = n;
	this->e = e;

	decompositionNombresPremiers();
	phiN();
}

RSA::RSA(long long p, long long q, long long e)
{
	system("clear");

	wcout << L">>> Initialisation avec p = " << p << L" , q = " << q << L" et la clé publique e = " << e << endl;
	this->p = p;
	this->q = q;
	this->e = e;
	n = p * q;

	cout << ">>> Initialisation de n = p x q = " << p << " x " << q << " = " << n << endl << endl;
	phiN();
}

long long RSA::exponentiationRapideModulaire(long long base, long long exposant, long long modulo)
{
	cout << ">>> Exponentiation rapide modulaire de " << base << "^" << exposant << "[" << modulo << "]" << endl;
	
	// Complexité Olog(e)
	if (modulo == 1)
	{
		return 0;
	}

	if (exposant == 1)
	{
		return 0;
	}

	// Méthode récursive
	long long p;

	for (p = 1; exposant > 0; exposant = (exposant / 2))
	{
		if ((exposant % 2) != 0)
		{
			p = (p * base) % modulo;
		}

		base = (base * base) % modulo;
	}

	return p;
}

void RSA::calculBezoutEuclideEtendu()
{
	wcout << L">>> Calcul des coefficients de Bézout u et v..." << endl;
	wcout << L" -> Opération: (phi(n) * u) + (e * v) = 1" << endl;
	cout << " -> (" << phi_n << " * u) + (" << e << " * v) = " << PGCD(phi_n, e) << endl << endl;
	long long x, y, q1, r, tmp, a, b, verification;
	a = phi_n;
	b = e;

	// Clé privée d dans phi(n) * u + e * d = 1 -> On fera phi(n) * u + e * v = 1; 

	// Initialisation des restes x et y et des coefficients de Bézout
	u = 1;
	v = 0;
	x = 0;
	y = 1;
	q1 = 1;
	
	wcout << L" -> Application de l'algorithme d'Euclide étendu: " << endl << endl;

	cout << setw(20) << left << "u" << "|" << setw(20) << left << "v" << "|" << setw(20) << left << "r" << "|" << setw(20) << left << "q" << "|" << endl;
	cout << setw(20) << left << u << "|" << setw(20) << left << v << "|" << setw(20) << left << phi_n << "|" << setw(20) << left << " " << "|" << endl;
	cout << setw(20) << left << v << "|" << setw(20) << left << u << "|" << setw(20) << left << e << "|" << setw(20) << left << (a / b) << "|" << endl;

	while (b > 0)
	{
		q1 = (a / b);
		r = (a % b);
		a = b;
		b = r;
		tmp = x;
		x = u - (q1 * x);
		u = tmp;
		tmp = y;
		y = v - (q1 * y);
		v = tmp;

		if (r > 0)
		{
			cout << setw(20) << left << x << "|" << setw(20) << left << y << "|" << setw(20) << left << r << "|" << setw(20) << left << (a / b) << "|" << endl;
		}
		else
		{
			cout << setw(20) << left << "" << "|" << setw(20) << left << "" << "|" << setw(20) << left << r << "|" << setw(20) << left << "" << "|" << endl << endl;
		}
	}

	verification = (phi_n * u) + (e * v);

	wcout << L">>> Les coefficients de Bézout sont: u = " << u << L", v = " << v << endl;
	cout << " -> Preuve: (" << phi_n << " * " << u << ") + (" << e << " * " << v << ") = " << (phi_n * u) << " + " << (e * v) << " = " << verification << endl << endl; 
}

void RSA::phiN()
{
	cout << ">>> Calcul de Phi(" << n << ") = (" << p << " - 1) * (" << q << " - 1)" << endl;
	phi_n = ((p - 1) * (q - 1)); // La formule de phi(n) = (p - 1) * (q - 1)
	cout << " -> Phi(" << n << ") = " << phi_n << endl << endl;
}

void RSA::decompositionNombresPremiers()
{
	bool premier = true;
	long long dividende = n;
	int nombre_facteurs_premiers = 0;
	vector <long long> facteurs;

	wcout << L">>> Décomposition de n = " << n << " en facteurs de nombres premiers..." << endl;

    for (int i = 2; i <= (dividende / i); i++) 
    {
        while ((dividende % i) == 0)
        {
            facteurs.push_back(i);
            nombre_facteurs_premiers++;
            dividende = dividende / i;
        }
    }
    
    if (dividende > 1) 
    {
        facteurs.push_back(dividende);
        nombre_facteurs_premiers++;
    }

    cout << " -> " << n << " = ";

    // Affichage des facteurs premiers
    for (int i = 0; i < facteurs.size(); i++)
    {
    	if (i < facteurs.size() - 1)
    	{
    		cout << facteurs[i] << " x ";
    	}
    	else
    	{
    		cout << facteurs[i] << endl;
    	}
    }

    if (nombre_facteurs_premiers > 2)
   	{
   		wcout << L" -> ERREUR: Il y a plus de 2 facteurs premiers, impossible de générer une clé publique !" << endl << endl;
   	}
   	else if (nombre_facteurs_premiers < 2)
   	{
   		wcout << L" -> ERREUR: facteur premier unique, impossible de générer une clé publique !" << endl << endl;
   	}
   	else
   	{
   		// Ici on a exactement 2 facteurs de nombres premiers, on peut donc avec p et q
   		p = facteurs[0];
   		q = facteurs[1];
   		wcout << L" -> p = " << p << L" et q = " << q << endl << endl;
   	}
}

void RSA::generationClePublique()
{
	wcout << L">>> Génération de la clé publique de cryptage..." << endl;
	cout << " -> Recherche d'un nombre premier entre " << q << " et " << phi_n << "..." << endl;

	long long i = q + 1;
	bool cle_generee = false;

	/* Par exemple, on va générer une clé publique en cherchant un nombre premier
	   On part de q + 1 et on prend le premier nombre premier qu'on trouve (la clé publique doit être différent de q) */
	while (cle_generee == false)
	{
		// On a trouvé notre clé publique
		if (testPrimaliteNombre(i))
		{
			wcout << L" -> Nombre premier trouvé. La clé publique sera e = " << i << endl << endl;
			e = i;
			cle_generee = true;
		}
		else
		{
			i++;
		}
	}
}

void RSA::generationClePrivee()
{
	wcout << L">>> Détermination de la clé privée de décryptage..." << endl;
	wcout << L" -> Clé publique: n = " << n << " et e = " << e << endl;
	wcout << L" -> Éléments privés: p = " << p << ", q = " << q << " et phi(" << n << ") = " << phi_n << endl << endl;

	calculBezoutEuclideEtendu();

	wcout << L">>> La clé privée d sera le plus petit entier positif v, ici v = " << v << ": ";

	if (v < 0)
	{
		wcout << L"il est négatif !" << endl;
		wcout << L" -> Détermination du plus petit entier positif v tel que v = (v + (" << phi_n << " / PGCD(" << phi_n << ", " << e << ")): " << endl;

		while (v < 0)
		{
			cout << "    * v = " << v << " + (" << phi_n << " / " << PGCD(phi_n, e) << ") = ";
			v = v + (phi_n / PGCD(phi_n, e));
			cout << v << endl;
		}
	}
	else
	{
		wcout << L"il est déja positif." << endl;
	}

	d = v; // La clé privée est v tel que 

	wcout << L" -> La clé privée secrète de décryptage sera d = " << d << endl << endl;
}

void RSA::cryptageRSA(long long message)
{
	system("clear");

	wcout << L">>> Cryptage du message " << message << L" avec la clé publique: n = " << n << L" et e = " << e << endl;
	message_crypte = exponentiationRapideModulaire(message, e, n);

	wcout << L" -> Votre message crypté: " << message_crypte << endl << endl;
}

void RSA::decryptageRSA(long long message_code)
{
	system("clear");

	wcout << L">>> Décryptage du message " << message_code << L" avec la clé privée: d = " << d << endl;
	message_decrypte = exponentiationRapideModulaire(message_code, d, n);

	wcout << L" -> Votre message décrypté: " << message_decrypte << endl << endl;
}
