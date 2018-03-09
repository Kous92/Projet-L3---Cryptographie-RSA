#ifndef CRYPTAGE_RSA_H
#define CRYPTAGE_RSA_H

#include <iostream>
#include <vector>

using namespace std;

bool testPrimaliteNombre(long long n);
long long PGCD(long long a, long long b);
vector<long long> saisie_securisee_n();
long long saisie_securisee_e(vector<long long> n);
long long saisie_securisee_e(long long p, long long q);
long long saisie_securisee_pq(string str);
long long saisie_securisee_message();
vector<long long> decompositionFacteursNombresPremiers(long long n);

class RSA
{
	private:
	long long n; // Émetteur: produit de 2 nombres premiers p et q
	long long e; // Clé publique de cryptage, nombre premier avec phi(n)

	// Facteurs premiers de n (p et q), éléments privés
	long long p;
	long long q;

	long long d; // Clé privée de décryptage

	// Coefficients de Bézout
	long long u;
	long long v; // Elle donne la clé privée
	long long phi_n; // Indicatrice d'Euler, élément privé

	// Messages
	long long message_crypte;
	long long message_decrypte;

	public:
	RSA(long long n);
	RSA(long long n, long long e);
	RSA(long long p, long long q, long long e);
	long long exponentiationRapideModulaire(long long base, long long exposant, long long modulo);
	void calculBezoutEuclideEtendu();	
	void phiN();
	void decompositionNombresPremiers();
	void generationClePublique();
	void generationClePrivee();
	void cryptageRSA(long long message_code);
	void decryptageRSA(long long message_crypte);
};

#endif