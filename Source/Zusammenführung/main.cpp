#include "stdafx.h"


int main() {
	try
	{

		int Method;
		long long Wiederholungen;

		if (!dirExists("C:\\Seminar"))
		{
			system("mkdir C:\\Seminar"); std::cout << "Used mkdir to create C:\\Seminar" << std::endl << std::endl;
		}

	Start:
		std::cout << "<1> Mittquadrat Generator (MS)" << std::endl
			<< "<2> Linearer Kongruenzgenerator (LC)" << std::endl
			<< "<3> Mersenne Twister (MT)" << std::endl
			<< "<4> Kolmogorov-Smirnov-Test" << std::endl
			<< "<5> RUN-Test" << std::endl
			<< "<6> POKER-Test" << std::endl << std::endl;

		std::cout << "<0> Close" << std::endl << std::endl << std::endl;

		std::cin >> Method;
		std::cin.get();
		if (!Method) { return 0; }
		std::cout << std::endl << "Wiederholungen: ";
		std::string strbuff;
		std::cin >> strbuff;
		if (strbuff == "m")
		{
			Wiederholungen = MAXWIEDERHOLUNG;
		}
		else { Wiederholungen = stoll(strbuff); }
		std::cin.get();


		switch (Method)
		{
			case 11:
				break;

			case 1:	MidSquare(Wiederholungen);			//MIDSQUARE
				break;

			case 2: LC(Wiederholungen);					//LINEAR
				break;

			case 3:	MT(Wiederholungen);					//MT
				break;


			case 44:
			{
				long double KS_Point[4] = { 0,0,0,0 };
				std::ofstream KSLaunchFile;
				std::string Generator;
				std::cout << "Generator: ";
				std::cin >> Generator;
				go44:
				KSLaunchFile.open("C:\\Seminar\\temp.smnr");
				MidSquare(Wiederholungen);
				MT(Wiederholungen);
				LC(Wiederholungen);

				KSLaunchFile
					<< "set terminal svg" << std::endl
					<< "set style line 1 linecolor 'black'" << std::endl
					<< "set output 'C:\\Seminar\\graph.svg'" << std::endl
					<< "set autoscale" << std::endl
					<< "set grid" << std::endl
					<< "set key left top" << std::endl
					<< "plot 'C:\\Seminar\\KS_" + Generator + ".nmbs' title '" + Generator + "' with step, x/100000";

				KS_Test(Wiederholungen, Generator, KS_Point);
				if (KS_Point[0] != 0) { KSLaunchFile << ", '+' using (" << KS_Point[1] << "):(" << KS_Point[0] << ") ls 1 notitle"; }
				if (KS_Point[2] != 0) { KSLaunchFile << ", '+' using (" << KS_Point[3] << "):(" << KS_Point[2] << ") ls 1 notitle"; }


				long double K_95 = 1.2239 - (1 / 6) * (1 / sqrt(Wiederholungen));

				std::cout << "K_95: " << K_95 << std::endl;


				KSLaunchFile << std::endl << "set terminal wxt size 1000, 600" << std::endl
					<< "replot" << std::endl
					<< "pause - 1" << std::endl;
				KSLaunchFile.close();

				std::cout << "KS done!" << std::endl;
				std::system("gnuplot -e load'C:\\Seminar\\temp.smnr'");
				goto go44;
			}
			break;

			case 4:										//Kolmogorov-Smirnov-Test
			{
				long double KS_Point[4] = { 0,0,0,0 };		//0-High CPF	1-High Number	2-Low CPF	3-Low Number
				std::ofstream KSLaunchFile;
				KSLaunchFile.open("C:\\Seminar\\ALL.smnr");
				MidSquare(Wiederholungen);
				MT(Wiederholungen);
				LC(Wiederholungen);

				KSLaunchFile
					<< "set terminal svg" << std::endl
					<< "set style line 1 linecolor 'black'" << std::endl
					<< "set output 'C:\\Seminar\\graph.svg'" << std::endl
					<< "set autoscale" << std::endl
					<< "set grid" << std::endl
					<< "set key left top" << std::endl
					<< "plot "
					<< "'C:\\Seminar\\KS_MS.nmbs' title 'MS' with step"
					<< ", 'C:\\Seminar\\KS_LC.nmbs' title 'LC' with step"
					<< ", 'C:\\Seminar\\KS_MT.nmbs' title 'MT' with step"
				
					<< ", x/100000";

				KS_Test(Wiederholungen, "MS", KS_Point);
				if (KS_Point[0] != 0) { KSLaunchFile << ", '+' using (" << KS_Point[1] << "):(" << KS_Point[0] << ") ls 1 notitle"; }
				if (KS_Point[2] != 0) { KSLaunchFile << ", '+' using (" << KS_Point[3] << "):(" << KS_Point[2] << ") ls 1 notitle"; }

				KS_Test(Wiederholungen, "MT", KS_Point);
				if (KS_Point[0] != 0) { KSLaunchFile << ", '+' using (" << KS_Point[1] << "):(" << KS_Point[0] << ") ls 1 notitle"; }
				if (KS_Point[2] != 0) { KSLaunchFile << ", '+' using (" << KS_Point[3] << "):(" << KS_Point[2] << ") ls 1 notitle"; }

				KS_Test(Wiederholungen, "LC", KS_Point);
				if (KS_Point[0] != 0) { KSLaunchFile << ", '+' using (" << KS_Point[1] << "):(" << KS_Point[0] << ") ls 1 notitle"; }
				if (KS_Point[2] != 0) { KSLaunchFile << ", '+' using (" << KS_Point[3] << "):(" << KS_Point[2] << ") ls 1 notitle"; }

				long double K_95 = 1.2239 - (1 / 6) * (1 / sqrt(Wiederholungen));

				std::cout << "K_95: " << K_95 << std::endl;


				KSLaunchFile << std::endl << "set terminal wxt size 1000, 600" << std::endl
					<< "replot" << std::endl
					<< "pause - 1" << std::endl;
				KSLaunchFile.close();

				std::cout << "KS done!" << std::endl;
				std::system("gnuplot -e load'C:\\Seminar\\ALL.smnr'");
			}
			break;

			case 5:										//RUN-Test

				std::cout << "Generator (PRNG_XX.nmbs): ";
				std::cin >> strbuff;
				std::cin.get();
				RUN_Test(Wiederholungen, strbuff);
								
				break;

			case 55:
				std::cout << "Generator (PRNG_XX.nmbs): ";
				std::cin >> strbuff;
				std::cin.get();
				while(true)
				{
					MidSquare(Wiederholungen);
					MT(Wiederholungen);
					LC(Wiederholungen);
					RUN_Test(Wiederholungen, strbuff);
					std::cin.get();
					std::system("cls");
				}
				break;

			case 6:										//POKER-Test

				std::cout << "Generator (PRNG_XX.nmbs): ";
				std::cin >> strbuff;
				std::cin.get();
				PokerTest(Wiederholungen, strbuff);

				break;

			case 66:

				std::cout << "Generator (PRNG_XX.nmbs): ";
				std::cin >> strbuff;
				std::cin.get();
				while (true)
				{
					//MidSquare(Wiederholungen);
					MT(Wiederholungen);
					//LC(Wiederholungen);
					PokerTest(Wiederholungen, strbuff);
					std::cin.get();
					std::system("cls");
				}


			default: std::cout << "Kek" << std::endl;
				system("cls");
				goto Start;
				break;

		}


		std::cout << std::endl << "Press Return to continue!" << std::endl;
		std::cin.get();
		system("cls");
		goto Start;
	}
	catch (const std::exception&)
	{
		//system("cls");
		std::cout << "FATAL ERROR!" << std::endl;
		system("pause");
		return 1;
	}
}
