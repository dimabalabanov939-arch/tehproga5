#include<iostream>

using namespace std;
class graph
{
private:
	int size;
	int maxSize;
	int** matrix;
	void addEdgeInternal(int u, int v)
	{
		if (u < 0 || u >= size || v < 0 || v >= size)
		{
			cout << "Ошибка: неверные номера вершин!\n";
			return;
		}

		if (matrix[u][v] == 1)
		{
			cout << "Ребро уже существует!\n";
			return;
		}

		matrix[u][v] = 1;
		matrix[v][u] = 1;
		cout << "Ребро добавлено!\n";
	}
	void removeEdgeInternal(int u, int v)
	{
		if (u < 0 || u >= size || v < 0 || v >= size)
		{
			cout << "Ошибка: неверные номера вершин!\n";
			return;
		}

		if (matrix[u][v] == 0)
		{
			cout << "Ошибка! Ребра между " << u + 1 << " и " << v + 1 << " не существует.\n";
			return;
		}

		matrix[u][v] = 0;
		matrix[v][u] = 0;
		cout << "Ребро между " << u + 1 << " и " << v + 1 << " успешно удалено!\n";
	}
	void DFSInternal(int vertex, bool* visited)
	{
		visited[vertex] = true;
		cout << vertex + 1 << " ";
		for (int i = 0; i < size; i++)
		{
			if (matrix[vertex][i] == 1 && !visited[i])
			{
				DFSInternal(i, visited);
			}
		}
	}
public:

	graph()
	{
		size = 0;
		maxSize = 2;
		matrix = new int* [maxSize];
		for (int i = 0; i < maxSize; i++)
		{
			matrix[i] = new int[maxSize];
			for (int j = 0; j < maxSize; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}
	void printMatrix()
	{
		if (size == 0)
		{
			cout << "Граф пуст!\n";
			return;
		}

		cout << "\nМатрица смежности:\n    ";
		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << " ";
		}
		cout << "\n";

		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << "   ";
			for (int j = 0; j < size; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
	void inputGraph()
	{
		if (size > 0)
		{
			cout << "Очищаем текущий граф...\n";
			for (int i = 0; i < maxSize; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
			size = 0;
			maxSize = 2;
			matrix = new int* [maxSize];
			for (int i = 0; i < maxSize; i++)
			{
				matrix[i] = new int[maxSize];
				for (int j = 0; j < maxSize; j++)
				{
					matrix[i][j] = 0;
				}
			}
		}
		int n;
		cout << "Введите количество вершин: ";
		cin >> n;
		while (n <= 0)
		{
			cout << "Количество вершин должно быть больше 0! Повторите ввод: ";
			cin >> n;
		}
		if (n > maxSize)
		{
			int** newMatrix = new int* [n];
			for (int i = 0; i < n; i++)
			{
				newMatrix[i] = new int[n];
				for (int j = 0; j < n; j++)
				{
					newMatrix[i][j] = 0;
				}
			}
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					newMatrix[i][j] = matrix[i][j];
				}
			}
			for (int i = 0; i < maxSize; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
			matrix = newMatrix;
			maxSize = n;
		}
		size = n;
		int m;
		int maxEdges = n * (n - 1) / 2;
		cout << "Введите количество рёбер (максимум " << maxEdges << "): ";
		cin >> m;
		while (m < 0 || m > maxEdges)
		{
			cout << "Некорректное количество рёбер! Введите число от 0 до " << maxEdges << ": ";
			cin >> m;
		}
		if (m == 0)
		{
			cout << "Граф без рёбер создан.\n";
			printMatrix();
			return;
		}
		cout << "\nВведите рёбра (каждое ребро - две вершины через пробел):\n";
		cout << "Пример: 1 2 означает ребро между вершиной 1 и вершиной 2\n\n";
		for (int i = 0; i < m; i++)
		{
			int u, v;
			cout << "Ребро " << i + 1 << ": ";
			cin >> u >> v;
			if (u < 1 || u > n || v < 1 || v > n)
			{
				cout << "Ошибка! Вершины должны быть от 1 до " << n << ". Повторите ввод ребра " << i + 1 << ".\n";
				i--;
				continue;
			}
			if (u == v)
			{
				cout << "Ошибка! Петли запрещены (вершина не может быть соединена сама с собой). Повторите ввод.\n";
				i--;
				continue;
			}
			u--;
			v--;
			if (matrix[u][v] == 1)
			{
				cout << "Ошибка! Ребро между " << u + 1 << " и " << v + 1 << " уже существует. Повторите ввод.\n";
				i--;
				continue;
			}
			matrix[u][v] = 1;
			matrix[v][u] = 1;
		}
		cout << "\nГраф успешно создан!\n";
		printMatrix();
	}
	void addVertex()
	{
		int newSize = size + 1;
		int** newMatrix = new int* [newSize];

		for (int i = 0; i < newSize; i++)
		{
			newMatrix[i] = new int[newSize];
			for (int j = 0; j < newSize; j++)
			{
				newMatrix[i][j] = 0;
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				newMatrix[i][j] = matrix[i][j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = newMatrix;
		size = newSize;

		cout << "Вершина " << size << " добавлена!\n";
		printMatrix();
	}
	void addEdgeFromUser()
	{
		if (size == 0)
		{
			cout << "Граф пуст! Сначала создайте граф.\n";
			return;
		}
		cout << "Текущее количество вершин: " << size << " (от 1 до " << size << ")\n";
		cout << "Введите две вершины для добавления ребра: ";
		int u, v;
		cin >> u >> v;
		if (u < 1 || u > size || v < 1 || v > size)
		{
			cout << "Ошибка! Вершины должны быть от 1 до " << size << ".\n";
			return;
		}
		if (u == v)
		{
			cout << "Ошибка! Нельзя добавить петлю.\n";
			return;
		}
		addEdgeInternal(u - 1, v - 1);
	}
	void removeEdgeFromUser()
	{
		if (size == 0)
		{
			cout << "Граф пуст! Сначала создайте граф.\n";
			return;
		}
		cout << "Текущее количество вершин: " << size << " (от 1 до " << size << ")\n";
		cout << "Введите две вершины для удаления ребра: ";
		int u, v;
		cin >> u >> v;
		if (u < 1 || u > size || v < 1 || v > size)
		{
			cout << "Ошибка! Вершины должны быть от 1 до " << size << ".\n";
			return;
		}
		if (u == v)
		{
			cout << "Ошибка! Петли не существует (вершина не может быть соединена сама с собой).\n";
			return;
		}
		removeEdgeInternal(u - 1, v - 1);
		if (size > 0)
		{
			printMatrix();
		}
	};
	void generateRandomGraph()
	{
		int n;
		cout << "Введите количество вершин: ";
		cin >> n;
		while (n <= 0)
		{
			cout << "Количество вершин должно быть больше 0! Повторите ввод: ";
			cin >> n;
		}
		int maxPossibleEdges = n * (n - 1) / 2;
		int m;
		cout << "Введите количество рёбер (максимум " << maxPossibleEdges << "): ";
		cin >> m;
		while (m < 0 || m > maxPossibleEdges)
		{
			cout << "Некорректное количество рёбер! Введите число от 0 до " << maxPossibleEdges << ": ";
			cin >> m;
		}
		for (int i = 0; i < maxSize; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		size = n;
		maxSize = n;
		matrix = new int* [maxSize];
		for (int i = 0; i < maxSize; i++)
		{
			matrix[i] = new int[maxSize];
			for (int j = 0; j < maxSize; j++)
			{
				matrix[i][j] = 0;
			}
		}
		if (m == 0)
		{
			cout << "\nСлучайный граф без рёбер создан!\n";
			printMatrix();
			return;
		}
		cout << "\nГенерация случайных рёбер...\n";

		int edgesAdded = 0;
		int maxAttempts = m * 10;
		int attempts = 0;

		while (edgesAdded < m && attempts < maxAttempts)
		{
			int u = rand() % n;
			int v = rand() % n;
			if (u != v && matrix[u][v] == 0)
			{
				matrix[u][v] = 1;
				matrix[v][u] = 1;
				edgesAdded++;
				cout << "Ребро " << edgesAdded << ": " << u + 1 << " - " << v + 1 << "\n";
			}

			attempts++;
		}
		if (edgesAdded < m)
		{
			cout << "\nВнимание! Удалось сгенерировать только " << edgesAdded
				<< " рёбер из " << m << " (слишком много попыток).\n";
			cout << "Возможно, граф уже достиг максимальной плотности.\n";
		}
		else
		{
			cout << "\nСлучайный граф успешно создан!\n";
		}
		printMatrix();
	}
	void DFS()
	{
		if (size == 0)
		{
			cout << "Граф пуст! Сначала создайте граф (пункт 1 или 5).\n";
			return;
		}
		cout << "\n=== ОБХОД ГРАФА В ГЛУБИНУ (DFS) ===\n";
		cout << "Количество вершин в графе: " << size << "\n";
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;
		}
		int startVertex;
		cout << "Введите стартовую вершину (от 1 до " << size << "): ";
		cin >> startVertex;
		while (startVertex < 1 || startVertex > size)
		{
			cout << "Ошибка! Введите число от 1 до " << size << ": ";
			cin >> startVertex;
		}
		startVertex--;
		cout << "\nПорядок обхода вершин: ";
		DFSInternal(startVertex, visited);
		bool allVisited = true;
		for (int i = 0; i < size; i++)
		{
			if (!visited[i])
			{
				allVisited = false;
				break;
			}
		}
		if (!allVisited)
		{
			cout << "\n\nВНИМАНИЕ: Граф несвязный!\n";
			cout << "Были посещены не все вершины.\n";
			cout << "Непосещённые вершины: ";
			for (int i = 0; i < size; i++)
			{
				if (!visited[i])
				{
					cout << i + 1 << " ";
				}
			}
			cout << "\n";
			cout << "\nХотите обойти оставшиеся компоненты связности? (1 - да, 0 - нет): ";
			int answer;
			cin >> answer;

			if (answer == 1)
			{
				cout << "\nОбход остальных компонент:\n";
				for (int i = 0; i < size; i++)
				{
					if (!visited[i])
					{
						cout << "Компонента с вершины " << i + 1 << ": ";
						DFSInternal(i, visited);
						cout << "\n";
					}
				}
			}
		}
		else
		{
			cout << "\n\nГраф связный, все вершины посещены!";
		}
		cout << "\n===============================\n";
		delete[] visited;
	}
};
int main()
{
	graph g;
	srand(time(NULL));
	setlocale(LC_ALL, "ru_RU.UTF-8");
	while (1)
	{
		cout << "Меню\n";
		cout << "1. Начальный ввод графа с клавиатуры\n";
		cout << "2. Добавление вершины в граф\n";
		cout << "3. Добавление ребра\n";
		cout << "4. Удаление ребра\n";
		cout << "5. Генерация случайного графа с заданным количеством вершин и ребер\n";
		cout << "6. Вывод текущего графа в виде матрицы смежности\n";
		cout << "7. Реализация заданного алгоритма обработки графа\n";
		cout << "0. Выход\n";
		cout << "Введите число: \n";
		int choice;
		cin >> choice;
		while (cin.fail())
		{
			cout << "Неккоректный ввод." << endl;
			cin.clear();
			cin.ignore(10000000, '\n');
			cin >> choice;
		}
		switch (choice)
		{
		case(1):
		{
			g.inputGraph();
			break;
		}
		case(2):
		{
			g.addVertex();
			break;
		}
		case(3):
		{
			g.addEdgeFromUser();
			break;
		}
		case(4):
		{
			g.removeEdgeFromUser();
			break;
		}
		case(5):
		{
			g.generateRandomGraph();
			break;
		}
		case(6):
		{
			g.printMatrix();
			break;
		}
		case(7):
		{
			g.DFS();
			break;
		}
		case(0):
		{
			exit(0);
			break;
		}
		default:
		{
			cout << "Неккоректный ввод.\n";
			break;
		}
		return 0;
		}
	}
}