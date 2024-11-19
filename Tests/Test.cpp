#include "../Sequences/LinkedList.h"
#include "../Sorting/Sorting.h"
#include <cassert>
#include <iomanip>

// n c ðàâíîìåðíûì øàãîì ïî ïÿòè òî÷êàì è ïîñòîðèò ïî íèì êðàôèê, ãðàôèê îáÿçàòåëåí çàâèñèìîñòü âðåìåíè îò êëîîè÷åñòâà äàííûõ äîëæíà ïðîèëëþñòðèðîâàííà ãðàôè÷åñêè ìîæíî äàæå â åêñåëü
// ïåðåä òàì êàê ïîêàçûâàòü íàäî ïîêàçàòü êàê ìû ñ÷èòàëè
// èçó÷èòü êàê ñäêëàòü òàê ÷òîáû ýêñåëü ïîíÿë ÷òî ìû ñòðîêîâå ââåëè êàê ÷èñëî



	double loadTestINSERTION(int N) {  // Óáèðàåì 'const' äëÿ åäèíîîáðàçèÿ, õîòÿ îí äîïóñòèì
		LinkedList<int> List;
		InsertionSort<int> sorter;  // Ñîçäàåì îáúåêò êëàññà Sort

		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < N; ++i) {
			List.Append(rand());
		}

		// Íà÷èíàåì îòñ÷åò âðåìåíè
		auto start = std::chrono::high_resolution_clock::now();

		// Âûçûâàåì óêàçàííûé ìåòîä ñîðòèðîâêè ÷åðåç îáúåêò sorter
		sorter.Sort(&List);

		// Îñòàíàâëèâàåì îòñ÷åò âðåìåíè
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;

		return duration.count();
	}

	double loadTestBUBLE(int N) {  // Óáèðàåì 'const' äëÿ åäèíîîáðàçèÿ, õîòÿ îí äîïóñòèì
		LinkedList<int> List;
		BubbleSorter<int> sorter;  // Ñîçäàåì îáúåêò êëàññà Sort

		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < N; ++i) {
			List.Append(rand());
		}

		// Íà÷èíàåì îòñ÷åò âðåìåíè
		auto start = std::chrono::high_resolution_clock::now();

		// Âûçûâàåì óêàçàííûé ìåòîä ñîðòèðîâêè ÷åðåç îáúåêò sorter
		sorter.Sort(&List);

		// Îñòàíàâëèâàåì îòñ÷åò âðåìåíè
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;

		return duration.count();
	}

	double loadTestQUICK(int N) {  // Óáèðàåì 'const' äëÿ åäèíîîáðàçèÿ, õîòÿ îí äîïóñòèì
		LinkedList<int> List;

		QuickSort<int> sorter;  // Ñîçäàåì îáúåêò êëàññà Sort

		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < N; ++i) {
			List.Append(rand());
		}

		// Íà÷èíàåì îòñ÷åò âðåìåíè
		auto start = std::chrono::high_resolution_clock::now();

		// Âûçûâàåì óêàçàííûé ìåòîä ñîðòèðîâêè ÷åðåç îáúåêò sorter
		sorter.Sort(&List);

		// Îñòàíàâëèâàåì îòñ÷åò âðåìåíè
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;

		return duration.count();
	}
	/*
    void random_huge_data() {

        LinkedList<int> linkedList;

        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < 10000; ++i) {
               linkedList.Append(rand()); 
           }
        Sort<int> sorter;
        sorter.QuickSort(&linkedList);
}
*/
	void comparing() {

		cout << setw(47) << " BubbleSort "
			<< setw(19) << " QuickSort "
			<< setw(20) <<"InsertionSort" << endl;

		cout << "Testing with 100 elements:"
			<< setw(20) << loadTestBUBLE(100) << "s "
			<< setw(20) << loadTestQUICK(100) << "s "
			<< setw(15) << loadTestINSERTION(100) << "s " << endl;

		

		cout << "Testing with 500 elements:"
			<< setw(20) << loadTestBUBLE(500) << "s "
			<< setw(20) << loadTestQUICK(500) << "s "
			<< setw(16) << loadTestINSERTION(500) << "s " << endl;

		cout << "Testing with 1000 elements: "
			<< setw(17) << loadTestBUBLE(1000) << "s "
			<< setw(20) << loadTestQUICK(1000) << "s "
			<< setw(14) << loadTestINSERTION(1000) << "s " << endl;
	}

	//test sorts

	void BubbleSorter_test1()
	{
		BubbleSorter<int> sorter;
		int array[] = { 6,4,2,9,10,3,40,-10 };
		int size = 8;
		int sortedArray[] = { -10,2,3,4,6,9,10,40 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void BubbleSorter_test2()
	{
		BubbleSorter<int> sorter;
		int array[] = { 1,2,3,4,5,6,7,8,9 };
		int size = 9;
		int sortedArray[] = { 1,2,3,4,5,6,7,8 ,9};

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void BubbleSorter_test3()
	{
		BubbleSorter<int> sorter;
		int array[] = { 2 };
		int size = 1;
		int sortedArray[] = { 2 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	

	void BubbleSorter_test4()
	{
		BubbleSorter<int> sorter;
		int array[] = {9, 8,7,6,5,4,3,2,1 };
		int size = 9;
		int sortedArray[] = { 1,2,3,4,5,6,7,8,9 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}
	
	void BubbleSorter_test5()
	{
		BubbleSorter<int> sorter;
		int size = 100;
		LinkedList<int> list;

		for (int i = 0; i < size; i++)
		{
			list.Append(rand());
		}

		sorter.Sort(&list);

		for (int i = 0; i < size - 1; i++)
		{
			assert(list.GetElement(i) <= list.GetElement(i + 1));
		}
	}
	//ïðîâåðèòü íà îòñîðòèðîâàííîì ÷àñòè÷íî îòñîðòèðîâàííîì è íà îáðàòíî îòñîðòèðîâàííîì
	// / <summary>
	/// inserted_test
	/// </summary>
	
	void InsertionSort_test1()
	{
		InsertionSort<int> sorter;
		int array[] = { 6,4,2,9,10,3,40,-10 };
		int size = 8;
		int sortedArray[] = { -10,2,3,4,6,9,10,40 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void InsertionSort_test2()
	{
		InsertionSort<int> sorter;
		int array[] = { 1,2,3,4,5,6,7,8,9 };
		int size = 9;
		int sortedArray[] = { 1,2,3,4,5,6,7,8 ,9 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void InsertionSort_test3()
	{
		InsertionSort<int> sorter;
		int array[] = { 2 };
		int size = 1;
		int sortedArray[] = { 2 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}



	void InsertionSort_test4()
	{
		InsertionSort<int> sorter;
		int array[] = { 9, 8,7,6,5,4,3,2,1 };
		int size = 9;
		int sortedArray[] = { 1,2,3,4,5,6,7,8,9 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void InsertionSort_test5()
	{
		InsertionSort<int> sorter;
		int size = 100;
		LinkedList<int> list;

		for (int i = 0; i < size; i++)
		{
			list.Append(rand());
		}

		sorter.Sort(&list);

		for (int i = 0; i < size - 1; i++)
		{
			assert(list.GetElement(i) <= list.GetElement(i + 1));
		}
	}
	

	/// <summary>
	/// quick_sort
	/// </summary>
	

	void QuickSort_test1()
	{
		QuickSort<int> sorter;
		int array[] = { 6,4,2,9,10,3,40,-10 };
		int size = 8;
		int sortedArray[] = { -10,2,3,4,6,9,10,40 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void QuickSort_test2()
	{
		QuickSort<int> sorter;
		int array[] = { 1,2,3,4,5,6,7,8,9 };
		int size = 9;
		int sortedArray[] = { 1,2,3,4,5,6,7,8 ,9 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void QuickSort_test3()
	{
		QuickSort<int> sorter;
		int array[] = { 2 };
		int size = 1;
		int sortedArray[] = { 2 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void QuickSort_test4()
	{
		QuickSort<int> sorter;
		int array[] = { 9, 8,7,6,5,4,3,2,1 };
		int size = 9;
		int sortedArray[] = { 1,2,3,4,5,6,7,8,9 };

		LinkedList<int> list(array, size);

		sorter.Sort(&list);

		for (int i = 0; i < size; i++)
		{
			assert(list.GetElement(i) == sortedArray[i]);
		}
	}

	void QuickSort_test5()
	{
		QuickSort<int> sorter;
		int size = 100;
		LinkedList<int> list;

		for (int i = 0; i < size; i++)
		{
			list.Append(rand());
		}

		sorter.Sort(&list);

		for (int i = 0; i < size - 1; i++)
		{
			assert(list.GetElement(i) <= list.GetElement(i + 1));
		}
	}

	// Ðåàëèçàöèÿ îïåðàòîðà < 
	bool Person::operator<(const Person other) const {
		if (lastName != other.lastName)
			return lastName < other.lastName;
		if (firstName != other.firstName)
			return firstName < other.firstName;
		if (birthYear != other.birthYear)
			return birthYear < other.birthYear;
		if (height != other.height)
			return height < other.height;
		return weight < other.weight;
	}

	// Ðåàëèçàöèÿ îïåðàòîðà >
	bool Person::operator>(const Person other) const {
		return other < *this;
	}

	// Ðåàëèçàöèÿ îïåðàòîðà ==
	bool Person::operator==(const Person other) const {
		return lastName == other.lastName &&
			firstName == other.firstName &&
			birthYear == other.birthYear &&
			height == other.height &&
			weight == other.weight;
	}

	// Ðåàëèçàöèÿ îïåðàòîðà <=
	bool Person::operator<=(const Person other) const {
		return *this < other || *this == other;
	}

	// Ðåàëèçàöèÿ îïåðàòîðà >=
	bool Person::operator>=(const Person other) const {
		return !(*this < other);
	}

	// Ðåàëèçàöèÿ îïåðàòîðà !=
	bool Person::operator!=(const Person other) const {
		return !(*this == other);
	}

	// Ðåàëèçàöèÿ îïåðàòîðà âûâîäà
	ostream& operator<<(ostream& os, const Person& person) {
		os << "Person(" << person.firstName << " " << person.lastName
			<< ", Birth Year: " << person.birthYear
			<< ", Height: " << person.height << "m"
			<< ", Weight: " << person.weight << "kg)\n";
		return os;
	}

	void checking() {

		BubbleSorter_test1();
		BubbleSorter_test2();
		BubbleSorter_test3();
		BubbleSorter_test4();
		BubbleSorter_test5();

		InsertionSort_test1();
		InsertionSort_test2();
		InsertionSort_test3();
		InsertionSort_test4();
		InsertionSort_test5();

		QuickSort_test1();
		QuickSort_test2();
		QuickSort_test3();
		QuickSort_test4();
		QuickSort_test5();

		 loadTestINSERTION(100);
		 loadTestBUBLE(100);
		 loadTestQUICK(100);

	}
	