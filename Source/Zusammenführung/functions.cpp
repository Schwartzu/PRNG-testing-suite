#include "stdafx.h"

void MidSquare(int n) {
	const int cilength = 5;
	unsigned long long base;/* = 651268435*/;		//651268435
	std::string basetest = "12345";
	int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed);
	for (int i = 0; i < cilength; i++)
	{
		basetest[i] = (rand() % 10) + '0';
		while (basetest[0] == '0')
		{
			basetest[0] = (rand() % 10) + '0';
		}
	}
	base = std::stoull(basetest);
	int LENGTH;
	int blockcount = 1;
	int strlength;
	int hin;
	std::string output;
	std::stringstream ss;
	std::ofstream file;
	file.open("C:\\Seminar\\PRNG_MS.nmbs");
	file << base << std::endl;
	ss << base;
	output = ss.str();
	char RN[cilength];
	char outputchar[2 * cilength + 1];
	LENGTH = output.length();
	int umbruch = 0;

	hin = LENGTH / 2;
	if (LENGTH % 2 > 0)
	{
		hin = ceil(LENGTH / 2) + 1;
	}

	for (int i = LENGTH - 1; i >= 0; i--)
	{
		RN[i] = '0';
		RN[i] = output[i];
	}


	for (int i = 0; blockcount <= n; i++)
	{
		base = base * base;
		output = std::to_string(base);
		strlength = output.length();

		for (int i = LENGTH - 1; i >= 0; i--)
		{
			RN[i] = '0';
		}
		for (int i = LENGTH * 2; i >= 0; i--)
		{
			if (i - (LENGTH * 2 - strlength) < 0)
			{
				outputchar[i] = '0';
			}
			else {
				outputchar[i] = output[i - (LENGTH * 2 - strlength)];
			}
		}

		for (int i = LENGTH - 1; i >= 0; i--)
		{

			RN[i] = outputchar[LENGTH * 2 - hin - (LENGTH - i)];
			base = std::stoll(RN);
		}

		for (int i = 0; i < LENGTH; i++)
		{
			file << RN[i];
			umbruch++;
			if (umbruch == 5) { file << std::endl; umbruch = 0; blockcount++; }
			if (blockcount == n) { file.close(); std::cout << "MS done!" << std::endl; return; }

		}
	}
	std::cout << "ERROR" << std::endl;
	std::system("Pause");
	return;
}

void LC(int n) {


	unsigned long long a = 214013;
	unsigned long long c = 2531011;
	unsigned long long p = pow(2, 32);
	unsigned long long x = 12345;
	int blockcount = 0;
	int umbruch = 0;

	int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	x = seed;
	std::stringstream ss;
	ss << x;

	std::string buffer;
	for (int i = 0; i < 5; i++)
		buffer.push_back('0');

	std::ofstream file;
	file.open("C:\\Seminar\\PRNG_LC.nmbs");
	x %= 99999;
	ss << x;

	for (int i = 0; i < 5; i++)
	{
		if(i<=ss.str().size())
			buffer.at(4 - i) = ss.str().at(ss.str().size() - 1 - i);
	}
	file << buffer << std::endl;

	std::cout << "LC working" << std::endl;
	for (int i = 0; i < n; i++)
	{
		ss.str(std::string());
		x = (a*x + c) % p;
		ss << x;
		buffer = ss.str();
		std::string shiftstring;
		ss.str(std::string());
		ss << x % 99999;
		shiftstring = "00000";
		for (int j = ss.str().length() - 1; j >= 0; j--)
		{
			shiftstring[j + (5 - ss.str().length())] = ss.str()[j];
		}
		file << shiftstring << std::endl;
	}
	file.close();
	std::cout << "LC done!" << std::endl;
	return;

}

void PokerTest(int n, std::string Name)
{
	std::fstream file;
	file.open("C:\\Seminar\\PRNG_" + Name + ".nmbs");
	std::string Line;
	int cdiff = 0, conepair = 0, ctwopairs = 0, cdrilling = 0, cfullhouse = 0, cpoker = 0, cgrande = 0;
	float abcde, aabcd, aabbc, aaabc, aaabb, aaaab, aaaaa;
	abcde = 0.3024f;
	aabcd = 0.5040f;
	aabbc = 0.1080f;
	aaabc = 0.0720f;
	aaabb = 0.0090f;
	aaaab = 0.0045f;
	aaaaa = 0.0001f;


	for (int i = 0; i < n; i++)
	{
		int numbers[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		std::getline(file, Line);

		for (int j = 0; j < 5; j++)
		{
			switch ((int)Line[j] - '0')		// ASCII konvertierung
			{
				case 0: numbers[0]++;
					break;
				case 1: numbers[1]++;
					break;
				case 2: numbers[2]++;
					break;
				case 3: numbers[3]++;
					break;
				case 4: numbers[4]++;
					break;
				case 5: numbers[5]++;
					break;
				case 6: numbers[6]++;
					break;
				case 7: numbers[7]++;
					break;
				case 8: numbers[8]++;
					break;
				case 9: numbers[9]++;
					break;
				default:std::cout << "ERROR" << std::endl; std::system("Pause");
					break;
			}
		}
		int tpairs = 0, tdrilling = 0, tdiff = 0;
		for (int j = 0; j < 10; j++)
		{
			switch (numbers[j])
			{
				case 2: tpairs++;
					break;
				case 3: tdrilling++;
					break;
				case 4: cpoker++;
					break;
				case 5: cgrande++;
					break;
				default: tdiff++;
					break;
			}

		}

		if (tdiff == 10) { cdiff++; }
		if (tpairs == 2) { ctwopairs++; }
		if (tdrilling == 1 && tpairs == 1) { cfullhouse++; }
		if (tdrilling == 0 && tpairs == 1) { conepair++; }
		if (tpairs == 0 && tdrilling == 1) { cdrilling++; }

	}

	std::system("cls");

	std::cout << std::endl << std::endl;
	std::cout << "ALL DIFFERENT: " << cdiff << " , OF EXPECTED: " << abcde*n << std::endl;
	std::cout << "ONE PAIR: " << conepair << " , OF EXPECTED: " << aabcd*n << std::endl;
	std::cout << "TWO PAIRS: " << ctwopairs << " , OF EXPECTED: " << aabbc*n << std::endl;
	std::cout << "DRILLING: " << cdrilling << " , OF EXPECTED: " << aaabc*n << std::endl;
	std::cout << "FULL HOUSE: " << cfullhouse << " , OF EXPECTED: " << aaabb*n << std::endl;
	std::cout << "POKER: " << cpoker << " , OF EXPECTED: " << aaaab*n << std::endl;
	std::cout << "GRANDE: " << cgrande << " , OF EXPECTED: " << aaaaa*n << std::endl;
	std::cout << std::endl << std::endl;


	//CHI-QUADRAT
	//FREIHEITSGRAD f = 5; GRANDE UND POKER WERDEN ZUSAMMENGEFASST

	float chifpa95 = 11.07f, chifpa99 = 15.09f, chifpa999 = 20.52f;


	float chipr =

		pow((cdiff - abcde*n), 2) / (abcde*n)
		+
		pow((conepair - aabcd*n), 2) / (aabcd*n)
		+
		pow((ctwopairs - aabbc*n), 2) / (aabbc*n)
		+
		pow((cdrilling - aaabc*n), 2) / (aaabc*n)
		+
		pow((cfullhouse - aaabb*n), 2) / (aaabb*n)
		+
		pow(((cpoker + cgrande) - (aaaab*n + aaaaa*n)), 2) / (aaaab*n + aaaaa*n);

	std::cout << "Chi-quadrat Pruefwert: " << chipr << std::endl;

	if (chipr <= chifpa95) { std::cout << "Es gibt keinen ersichtlichen Grund an der Qualitaet des PRNG zu zweifeln" << std::endl; }
	if (chipr <= chifpa99 && chipr > chifpa95) { std::cout << "Es besteht ein Verdacht, dass die 'Zufallszahlen' schlecht sind" << std::endl; }
	if (chipr <= chifpa999 && chipr > chifpa99) { std::cout << "Der PRNG ist als unbrauchbar zu bezeichnen!" << std::endl << "Die Irrtumswahrscheinlichkeit betraegt <= 1%" << std::endl; }
	if (chipr > chifpa999) { std::cout << "Der PRNG ist als unbrauchbar zu bezeichnen!" << std::endl << "Die Irrtumswahrscheinlichkeit betraegt <= 0,1%" << std::endl; }

}

void KS_Test(int n, std::string Generator, long double KS_Point[]) {
	int Numbers[MAXWIEDERHOLUNG];
	long double PMF[MAXWIEDERHOLUNG][2];
	long double CPF[MAXWIEDERHOLUNG][2];
	long double KSHigh = 0.f;
	long double KSLow = 0.f;

	int Multiple = 0;
	std::ifstream readfile("C:\\Seminar\\PRNG_" + Generator + ".nmbs");

	//	LESEN AUS DATEI


	for (int i = 0; i < n; i++)
	{
		std::string Buffer;
		getline(readfile, Buffer);
		Numbers[i] = stoi(Buffer);
	}
	readfile.close();
	std::sort(Numbers, Numbers + n);
	int i = 1;


	for (int i = 0; i < n; i++)
	{
		if ((Numbers[i - 1] == Numbers[i]) && i != 0)
		{
			Multiple++;
		}
	}

	//	BERECHNEN VON PMF									Probability Mass Function


	int tempcounter = 0;
	for (int i = 0; i < n - Multiple; i++)
	{
		PMF[i][0] = (long double)1 / (n);
		PMF[i][1] = 0;
		while (Numbers[i + tempcounter] == Numbers[i + tempcounter + 1])
		{
			PMF[i][0] += (long double)1 / (n);
			tempcounter++;
			PMF[i][1]++;
		}
	}


	//	BERECHNEN VON CPF UND SCHREIBEN IN DATEI			Cumulative Probability Function


	std::ofstream writefile("C:\\Seminar\\KS_" + Generator + ".nmbs");

	for (int i = 0; i < n - Multiple; i++)
	{
		CPF[i][0] = 0;
		int woop = 0;
		for (int j = 0; j <= i; j++)
		{
			CPF[i][0] += PMF[j][0];
			woop += PMF[j][1];
		}
		CPF[i][1] = Numbers[i + woop];
		if (CPF[0][0] != 0 && i == 0) { writefile << 0 << "\t" << 0 << std::endl; }
		writefile << CPF[i][1] << "\t" << CPF[i][0] << std::endl;
	}
	writefile << 100000 << "\t" << 1 << std::endl;

	writefile.close();

	for (int i = 0; i < n - Multiple; i++)
	{
		if ((CPF[i][1] / 100000 < CPF[i][0]) && ((CPF[i][0] - CPF[i][1] / 100000) > KSHigh))
		{
			KSHigh = CPF[i][0] - CPF[i][1] / 100000;
			KS_Point[0] = CPF[i][0];
			KS_Point[1] = CPF[i][1];
		}

	}

	if (CPF[0][1] / 100000 > CPF[0][0]) { KS_Point[2] = 0; KS_Point[3] = CPF[0][1]; }
	for (int i = 1; i < n - Multiple; i++)
	{
		if ((CPF[i][1] / 100000 > CPF[i - 1][0]) && ((CPF[i][1] / 100000 - CPF[i - 1][0]) > KSLow))
		{
			KSLow = CPF[i][1] / 100000 - CPF[i - 1][0];
			KS_Point[2] = CPF[i - 1][0];
			KS_Point[3] = CPF[i][1];
		}

	}
	KSHigh *= sqrt(n);
	KSLow *= sqrt(n);
	long double KSMax = max(KSHigh, KSLow);
	std::cout << Generator + "_KSMax: " << KSMax << std::endl;


	return;

}

void RUN_Test(int n, std::string Generator) {



	std::ifstream file;
	file.open("C:\\Seminar\\PRNG_" + Generator + ".nmbs");

	std::string Buffer;
	std::vector<std::string> sfile;
	std::vector<std::string> sfilebackup;
	std::vector<int> filenum;

	sfile.reserve(400000);
	sfilebackup.reserve(400000);
	filenum.reserve(400000);


	int median;
	int runs = 1;
	int n1 = 0;			/// 0 for x < median
	int n2 = 0;			/// 1 for x > median

	long double Expected;
	long double z;
	long double var;


	std::string sbuffer;

	for (int i = 0; i < n; i++)
	{
		std::getline(file, sbuffer);
		sfile.push_back(sbuffer);
		filenum.push_back(stoi(sfile.at(i)));
	}

	sfilebackup = sfile;


	std::sort(filenum.begin(), filenum.end());

	if (n % 2 == 0) { median = filenum.at(n / 2); }
	else { median = filenum.at((n + 1) / 2); }

	file.close();

	for (int i = 0; i < n; i++)
	{
		filenum.at(i) = stoi(sfilebackup.at(i)) - median;
		if (filenum.at(i) < 0) { filenum.at(i) = 0; n1++; }
		else { filenum.at(i) = 1; n2++; }
		if (i != 0 && filenum.at(i) != filenum.at(i - 1)) { runs++; }
	}

	var = (long double)2 * n1 * n2 * (2 * n1 * n2 - n) / (n * n * (n1 + n2 - 1));
	Expected = (long double)((2 * n1 * n2) / n) + 1;
	z = abs((long double)(runs - Expected) / sqrt(var));


	std::cout << std::endl;

	if (z > 1.96)
	{
		std::cout << "Die Hypothese wird bei einem Signifikanzniveu von 0.05 abgelehnt." << std::endl
			<< "Die Zufallszahlen scheinen 'schlecht' zu sein!" << std::endl;
	}
	else
	{
		std::cout << "Die Hypothese wird bei einem Signifikanzniveu von 0.05 nicht abgelehnt." << std::endl
			<< "Die Zufallszahlen scheinen 'gut' zu sein!" << std::endl;
	}
	return;
}

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

void init_genrand(unsigned long s)
{
	mt[0] = s & 0xffffffffUL;
	for (mti = 1; mti < P; mti++) {
		mt[mti] = (1664525UL * mt[mti - 1] + 1UL);
		mt[mti] &= 0xffffffffUL;
	}
}

unsigned long genrand(void)
{
	unsigned long y;
	static unsigned long mag01[2] = { 0x0UL, MATRIX_A };

	if (mti >= P) {
		int kk;

		if (mti == P + 1)
			init_genrand(5489UL);

		for (kk = 0; kk < P - Q; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + Q] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (; kk < P - 1; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + (Q - P)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[P - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[P - 1] = mt[Q - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		mti = 0;
	}

	y = mt[mti++];


	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}

void MT(int n)
{
	long r;
	long long i;
	int j;
	int rmax;
	int rmin;
	std::vector<int> irseq;
	std::vector<float> rseq;

	float chi2;
	int df;
	int k;
	float knalpha;
	float D;
	unsigned long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	init_genrand(seed);
	rmax = 0;
	rmin = 1000000;

	for (i = 0; i < n; i++) {
		r = (long)(genrand() >> 1);
		if (rmax < r) {
			rmax = r;
		}
		if (rmin > r) {
			rmin = r;
		}
		irseq.push_back(r);
		rseq.push_back(r);

	}


	rmax = rmax + 10000;
	for (i = 0; i < n; i++) {
		rseq.at(i) /= rmax;
	}

	int counter5 = 0;
	int blockcount = 0;
	std::ofstream file;
	file.open("C:\\Seminar\\PRNG_MT.nmbs");
	std::stringstream ss;
	std::string shiftstring;
	for (long long i = 0; i < n; i++)
	{
		ss.str(std::string());
		ss << irseq[i] % 99999;
		shiftstring = "00000";
		for (int j = ss.str().length() - 1; j >= 0; j--)
		{
			shiftstring[j + (5 - ss.str().length())] = ss.str()[j];
		}
		file << shiftstring << std::endl;
	}

	file.close();


}
