#include "Input.hpp"

int main()
{
	int choice{};
	Gauss<double> my_Gauss;
	my_Gauss = static_cast<Gauss<double>>(load_from_csv_file<double>("1.csv"));
	Choleski<double> my_Choleski;
	my_Choleski = static_cast<Choleski<double>>(load_from_csv_file<double>("3.csv"));
	
	while (true)
	{
		std::cout
			<< "1. Podstawowa metoda eliminacji Gaussa\n"
			<< "2. Metoda eliminacji Gaussa z wyborem kolumny\n"
			<< "3. Metoda eliminacji Gaussa z wyborem wiersza\n"
			<< "4. Metoda Choleskiego\n"
			<< "5. Wyjscie\n";
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				my_Gauss.solve_matrixes();
				my_Gauss.calculate_results(choice);
				my_Gauss.print_matrix();
				my_Gauss.print_results();
			}
			break;
			case 2:
			{
				my_Gauss.elimination_by_column();
				my_Gauss.solve_matrixes();
				my_Gauss.calculate_results(choice);
				my_Gauss.print_matrix();
				my_Gauss.print_results();
			}
			break;
			case 3:
			{
				my_Gauss.elimination_by_row();
				my_Gauss.solve_matrixes();
				my_Gauss.calculate_results(choice);
				my_Gauss.print_matrix();
				my_Gauss.print_results();
			}
			break;
			case 4:
			{
				if (my_Choleski.check_symmetry())
				{
					if (my_Choleski.check_minors())
					{
						my_Choleski.solve_matrixes();
						my_Choleski.print_matrix();
						my_Choleski.print_results();
					}
					else 
						std::cout << "Ktorys z minorow jest ujemny\n";
				}
				else
					std::cout << "Macierz niesymetryczna\n";
			}
			break;
			case 5:
			{
				return 0;
			}
		}
		std::cin.get();
	}
	return 0;
}