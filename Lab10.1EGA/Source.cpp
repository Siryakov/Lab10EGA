#include <fstream>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <iomanip>
#include <conio.h.>
#include <Windows.h>
#include <string>
#include <numeric>
using namespace std;
int K = 15; // Количество Предметов
int PopSize;//Размер популяций
int Wmax = 96; //Максимальный вес ранца
int mutationProb = 15; // Вероятность мутации

vector<vector<double>> itemsAll1;

enum Colors {
    Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
    DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
template<Colors txt = LightGray, Colors bg = Black>

ostream& color(ostream& text) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
    return text;
}


//Вывод начальных предметов
void printItems(vector<vector<double>> arr) { // Выводит доступные предметы
    cout << color<Cyan, Black> << "Вывод данных о предметах" << color << endl;
    cout << "№\tЦена\tВес\tУдельная стоимость" << endl;
    for (int i = 0; i < K; i++) //Выводим матрицу
    {
        for (int j = 0; j < 4; j++)
            cout << setprecision(3) << arr[i][j] << "\t";
        cout << endl;
    }
}


// рандом от 0 до 1
double DoubleRand()
{
    return 0.010 * (rand() % 100);
}


// удаление по индексу
void remove(std::vector<string>& v, size_t index) {
    v.erase(v.begin() + index);
}


// Удаление элимента вектора 
void Erase(vector<vector<double>> m, size_t i, size_t j)
{
    // TODO: check if i and j are not out of range

    m.erase(m.begin() + i);
    for (auto& line : m)
    {
        line.erase(line.begin() + j);
    }
}

//Удаление дубликатов
void hasDublicate(std::vector<string>& v)
{
    for (size_t i = 0; i < v.size(); ++i)
        for (size_t j = i + 1; j < v.size(); ++j)
            if (v[i] == v[j]) {
                remove(v, j);
            }

}

// Рулетка по секциям
int Rulete(vector<double> udel)
{
    std::discrete_distribution<size_t> distr(udel.begin(), udel.end());
    vector<double> p = distr.probabilities();
    double sumP = 0;
    double r = DoubleRand();
    int c = 0; //счётчик
    do
    {
        sumP += p[c];
        c++;
    } while (sumP < r && c < p.size());
    sumP = 0;
    return (c - 1);
}


// возвращает вес
int GetWeight(string str)
{
    int W = 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] == '1') W = W + itemsAll1[i][2];
    return W;
}


// возвращает цену
int GetPrice(string str)
{
    int P = 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] == '1') P = P + itemsAll1[i][1];
    return P;
}


// Создает начальную популяцию
vector<string>  MadePopulation(int metod, int PopSize, vector<string> population, vector<int>& vecW, vector<int>& vecPrice, vector<double>& vecUdelPrice) {
    vector<vector<double>> itemsAll;
    vector<double> udel;
    int W = 0;
    int a = 0;
    int Price = 0;
    string str = "000000000000000";


    if (metod == 1)
    {
        for (int i = 0; i < PopSize; i++)
        {
            itemsAll = itemsAll1;
            for (int i = 0; i < K; i++)
            {
                udel.push_back(itemsAll[i][3]);
            }
            for (int i = 0; i < K; i++)
            {
                int index = Rulete(udel);
                if (Wmax >= W + itemsAll[index][2])
                {
                    str[itemsAll[index][0] - 1] = '1';

                    W = W + itemsAll[index][2];
                    Price = Price + itemsAll[index][1];
                    a = a + 1;
                    itemsAll.erase(itemsAll.begin() + index);//Удаляем предмет из набора
                    udel.erase(udel.begin() + index);//Удаляем его удельное знач
                }
                else {
                    itemsAll.erase(itemsAll.begin() + index);//Удаляем предмет из набора
                    udel.erase(udel.begin() + index);//Удаляем его удельное знач
                }

            }
            vecW.push_back(W);
            vecPrice.push_back(Price);
            double temp = (static_cast<double>(Price) / W);
            vecUdelPrice.push_back(temp);


            itemsAll.clear();
            udel.clear();
            W = 0;
            Price = 0;
            temp = 0;

            population.push_back(str);
            str = "000000000000000";
        }
    }
    else if (metod == 2)
    {
        for (int i = 0; i < PopSize; i++)
        {
            itemsAll = itemsAll1;
            for (int i = 0; i < K; i++)
            {
                udel.push_back(itemsAll[i][3]);
            }
            for (int i = 0; i < K; i++)
            {
                int index = rand() % itemsAll.size();
                if (Wmax >= W + itemsAll[index][2])
                {
                    str[itemsAll[index][0] - 1] = '1';

                    W = W + itemsAll[index][2];
                    Price = Price + itemsAll[index][1];
                    a = a + 1;
                    itemsAll.erase(itemsAll.begin() + index);//Удаляем предмет из набора
                    udel.erase(udel.begin() + index);//Удаляем его удельное знач
                }
                else {
                    itemsAll.erase(itemsAll.begin() + index);//Удаляем предмет из набора
                    udel.erase(udel.begin() + index);//Удаляем его удельное знач


                }

            }
            vecW.push_back(W);
            vecPrice.push_back(Price);
            double temp = (static_cast<double>(Price) / W);
            vecUdelPrice.push_back(temp);


            itemsAll.clear();
            udel.clear();
            W = 0;
            Price = 0;
            temp = 0;

            population.push_back(str);
            str = "000000000000000";
        }
    }
    return population;
}


//2 Кроссовера
string kros(string par1, string par2)
{
    string child = "";
    int rnd = rand() % 2;
    if (rnd == 0) //Одноточечный кроссовер
    {
        int rnd2 = rand() % par1.size();
        for (int i = 0; i < rnd2; i++)
            child = child + par1[i];
        for (int i = rnd2; i < par2.size(); i++)
            child = child + par2[i];
    }
    else //Двухточечный кроссовер
    {
        int rnd2 = rand() % (par1.size() / 2);
        int rnd3 = rand() % (par1.size() / 2) + 7;
        for (int i = 0; i < rnd2; i++)
            child = child + par1[i];
        for (int i = rnd2; i < rnd3; i++)
            child = child + par2[i];
        for (int i = rnd3; i < par2.size(); i++)
            child = child + par1[i];
    }
    return child;
}





// воспроизводство поколения
vector<string> MadePair(int metod2, vector<string> population, vector<double> vecUdelPrice)
{
    cout << "Родительские пары: " << endl;
    string par1 = "";
    string par2 = "";
    vector<string> child1;

    for (int i = 0; i < (int)population.size(); i++)
    {

        if (metod2 == 1)//Панмиксия
        {

            int rnd2 = rand() % population.size();
            int rnd3 = rand() % population.size();
            if (rnd2 == rnd3)
                if (rnd2 + 1 < population.size()) rnd2++;
                else if (rnd2 != 0) rnd2--;
            par1 = population[rnd2];
            par2 = population[rnd3];
            cout << par1 << "\t" << par2 << endl;
        }
        else if (metod2 == 2) // Положительное ассоциативное скрещивание
        {
            int index = 0, index1 = 0;
            while (index == index1)
            {
                index = rand() % population.size();
                index1 = rand() % population.size();
            }

            par1 = population[index];
            par2 = population[index1];
            cout << par1 << "\t" << par2 << endl;
        }
        string temp = "";


        for (int i = 0; i < 2; i++) // Надо подумать , что сделать , что бы количество особей было больше
        {
            temp = kros(par1, par2);
            if (GetWeight(temp) < Wmax)
            {
                child1.push_back(temp);
            }
        }




    }
    return child1;
}

//2 мутации
vector <string> mutation(vector <string> child)
{

    for (int i = 0; i < child.size(); i++)
    {
        int chance = rand() % 100;
        if (chance > mutationProb)
        {
            string temp = child[i];

            int rnd = rand() % 2;
            if (rnd == 0) //Генная точечная
            {
                do {
                    int rnd2 = rand() % child[i].size();

                    if (temp[rnd2] == '1')
                    {
                        temp[rnd2] = '0';
                    }
                    else
                    {
                        temp[rnd2] = '1';
                    }
                } while (GetWeight(temp) > Wmax);
            }
            else if (rnd == 1) //Сальтация
            {

                do {
                    int rnd2 = (rand() % (child[i].size() / 2)) + 1;
                    char tmp;
                    tmp = temp[rnd2];
                    temp[rnd2] = temp[temp.size() - rnd2];
                    temp[temp.size() - rnd2] = tmp;

                } while (GetWeight(temp) > Wmax);
            }
            child[i] = temp;
        }
    }
    return child;
}

//возвращает вес , цену , удельный всс
void GetWeightAndPrice(vector<string> child, vector<int>& childPrice, vector<int>& childW, vector<double>& childUdel)
{
    for (int i = 0; i < child.size(); i++)
    {
        int tempP = 0;
        int tempW = 0;
        for (int j = 0; j < child[i].size(); j++)
        {
            if (child[i][j] == '1')
            {
                tempP += itemsAll1[j][1];
                tempW += itemsAll1[j][2];


            }
        }
        childPrice.push_back(tempP);
        childW.push_back(tempW);
        childUdel.push_back((double)childPrice[i] / (double)childW[i]);
        tempP = 0;
        tempW = 0;
    }
}


// ищет максимум в векторе и возвращает индекс
int serchMax(vector<int> v)
{
    int index = 0;
    std::vector<int>::const_iterator find_it = std::max_element(v.begin(), v.end());
    if (find_it != v.end())
    {
        index = find_it - v.begin();
    }
    return index;
}


vector <string> selection(vector <string> vecChild, vector <string> vecMutant, vector<string>& Population, int metodSelection)
{
    vector <string> reproduct;

    for (int i = 0; i < vecChild.size(); i++)
    {
        reproduct.push_back(vecChild[i]);

    }
    for (int i = 0; i < vecMutant.size(); i++)
    {
        reproduct.push_back(vecMutant[i]);
    }
    if (metodSelection == 1) // сравниваем 2 особи по цене и отбираем лучшую
    {
        int k = 0;
        vector <string> B(2);



        for (int i = 0; i < PopSize; i++)
        {
            for (int j = 0; j < 1; j++)	// Выбираем 2 особи с равной вероятностью и записываем в массив В
            {
                k = rand() % reproduct.size();
                while (j > 0 && reproduct[k] == B[j - 1])
                {
                    k = rand() % reproduct.size();
                }
                B[j] = reproduct[k];
            }

            if (GetPrice(B[0]) > GetPrice(B[1])) Population.push_back(B[0]);
            else Population.push_back(B[1]);
        }
    }
    else if (metodSelection == 2) // чем лучше ранг , тем больше шанс попасть в след популяцию 
    {
        vector<int> rang;
        for (int j = 0; j < reproduct.size(); j++)
            rang.push_back(0);
        int sum = 0;
        for (int j = 0; j < reproduct.size(); j++) //Сортируем детей по рангам
        {
            int max = 0, number = 0;
            for (int k = 0; k < reproduct.size(); k++)
                if (GetPrice(reproduct[k]) >= max && rang[k] == 0)
                {
                    max = GetPrice(reproduct[k]);
                    number = k;
                }
            rang[number] = j + 1;
            sum = sum + max;
        }
        vector<float> proc;
        for (int j = 0; j < reproduct.size(); j++)
            proc.push_back((float)GetPrice(reproduct[j]) / sum);
        for (int j = 1; j < PopSize + 1; j++) //тут возможно надо заменить PopSize 
        {

            //Селекция, пропорциональная схем

            for (int k = 0; k < reproduct.size(); k++)
            {
                //float rnd2 = DoubleRand();
                float rnd2 = (float)(rand() % 100) / 100;
                if (proc[k] > rnd2)
                {

                    if (GetPrice(reproduct[k]) == 0)
                        continue;
                    Population.push_back(reproduct[k]);

                    proc[k] = -1;
                    break;

                }
            }

        }




        reproduct.clear();
    }
    return Population;
}//Отбор для лучшего поколения


void Delete(vector<int>& populationPrice, vector<int>& populationW, vector<double>& populationUdel, vector<int>& childPrice, vector<int>& childW, vector<double>& childUdel, vector<int>& mutantPrice, vector<int>& mutantW, vector<double>& mutantUdel)
{
    populationPrice.clear();
    populationW.clear();
    populationUdel.clear();
    childPrice.clear();
    childW.clear();
    childUdel.clear();
    mutantPrice.clear();
    mutantW.clear();
    mutantUdel.clear();
} // очистка



int main1()
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    ifstream in("text.txt");


    int metod = 0;
    int metod2 = 0;
    int metodSelection;
    int numberOfPopulations;
    vector<string> population;
    vector<int> populationPrice;
    vector<int> populationW;
    vector<double> populationUdel;
    vector<string> child;
    vector<int> childPrice;
    vector<int> childW;
    vector<double> childUdel;
    vector<string> mutant;
    vector<int> mutantPrice;
    vector<int> mutantW;
    vector<double> mutantUdel;
    vector<string> BestChoise;
    vector<string> BestOfTheBest;


    if (in.is_open())
    {
        for (int i = 0; i < K; i++) //Выделяем память 
        {
            vector<double> temp;
            for (int j = 0; j < 4; j++)
            {
                temp.push_back(1);
            }
            itemsAll1.push_back(temp);

        }

        for (int i = 0; i < K; i++) //Считаем матрицу из файла 
            for (int j = 0; j < 3; j++) {
                in >> itemsAll1[i][j];
                itemsAll1[i][3] = itemsAll1[i][1] / itemsAll1[i][2];
            }
        printItems(itemsAll1);
    }
    else
    {
        cout << color<Red, Black> << "Файл не открыт!!!" << color;
        return (0);
    }
    cout << color<Green, Black> << "Введите колчиество популяций : "; cin >> numberOfPopulations;; cout << color << endl;
    cout << color<Green, Black> << "Введите колчиество особей в популяции : "; cin >> PopSize; cout << color << endl;
    cout << color<Green, Black> << "Введите метод (1-Жадный ,2-Слуайный): "; cin >> metod; cout << color << endl;
    cout << color<Green, Black> << "способ формирования родительской пары (1-Панмиксия ,2-Положительное ассоциативное скрещивание):";  cin >> metod2; cout << color << endl;
    cout << color<Green, Black> << "способ селекции (1-турнир ,2-пропорциональная схема):";  cin >> metodSelection; cout << color << endl;


    population = MadePopulation(metod, PopSize, population, populationW, populationPrice, populationUdel); // Создаем начальную популяцию
    hasDublicate(population);
    cout << endl << "Популяция" << "\t" << "Цена" << "\t" << "Вес" << "\t" << "Удельный цена";
    for (int i = 0; i < population.size(); i++)
    {
        cout << endl << population[i] << "\t" << populationPrice[i] << "\t" << populationW[i] << "\t" << populationUdel[i];
    }

    int MaxPopulation = serchMax(populationPrice); // Ищем лучшего среди начальной популяции по цене

    cout << endl << color<Red, Black> << "Лучший из популяции: " << population[MaxPopulation] << "\t" << populationPrice[MaxPopulation] << "\t" << populationW[MaxPopulation] << "\t" << populationUdel[MaxPopulation] << color << endl << endl;
    BestChoise.push_back(population[MaxPopulation]); //Отбираем лучшего в отдельный вектор 


    for (int i = 0; i < numberOfPopulations; i++)
    {


        child = MadePair(metod2, population, populationUdel); // Создаём детей
        hasDublicate(child);
        GetWeightAndPrice(child, childPrice, childW, childUdel); //Записываем у каждого цену ,вес , удельную стоимость В отделные вектора 
        int MaxChild = serchMax(childPrice);//Ищем лучшего ребенка по цене
        cout << endl << "Потомки :" << endl;
        for (int i = 0; i < child.size(); i++)
        {
            cout << child[i] << "\t" << childPrice[i] << "\t" << childW[i] << "\t" << childUdel[i] << endl;
        }
        cout << color<Red, Black> << "Лучший потомок: " << child[MaxChild] << "\t" << childPrice[MaxChild] << "\t" << childW[MaxChild] << "\t" << childUdel[MaxChild] << color << endl << endl;
        BestChoise.push_back(child[MaxChild]);//Отбираем лучшего в отдельный вектор 


        mutant = mutation(child);
        hasDublicate(mutant);
        cout << endl << "Потомки после мутации: " << endl;
        GetWeightAndPrice(mutant, mutantPrice, mutantW, mutantUdel);
        int MaxMutant = serchMax(mutantPrice);
        for (int i = 0; i < mutant.size(); i++)
        {
            cout << mutant[i] << "\t" << mutantPrice[i] << "\t" << mutantW[i] << "\t" << mutantUdel[i] << endl;
        }
        cout << color<Red, Black> << "Лучший мутант: " << mutant[MaxMutant] << "\t" << mutantPrice[MaxMutant] << "\t" << mutantW[MaxMutant] << "\t" << mutantUdel[MaxMutant] << color << endl << endl;
        BestChoise.push_back(mutant[MaxMutant]);//Отбираем лучшего в отдельный вектор 


        Delete(populationPrice, populationW, populationUdel, childPrice, childW, childUdel, mutantPrice, mutantW, mutantUdel);
        population.clear();

        cout << "Новая популяция №" << i + 1 << endl;




        selection(child, mutant, population, metodSelection);
        hasDublicate(population);



       
        hasDublicate(population);
        GetWeightAndPrice(population, populationPrice, populationW, populationUdel);
        int MaxnewPopulation = serchMax(populationPrice);
        for (int i = 0; i < population.size(); i++)
        {
            cout << population[i] << "\t" << populationPrice[i] << "\t" << populationW[i] << "\t" << populationUdel[i] << endl;
        }
        cout << color<Red, Black> << "Лучший среди новой популяции: " << population[MaxnewPopulation] << "\t" << populationPrice[MaxnewPopulation] << "\t" << populationW[MaxnewPopulation] << "\t" << populationUdel[MaxnewPopulation] << color << endl << endl;
        hasDublicate(BestChoise);


        BestChoise.push_back(population[MaxnewPopulation]);
        for (int i = 0; i < BestChoise.size(); i++)
        {
            BestOfTheBest.push_back(BestChoise[i]);
        }
        hasDublicate(population);
        BestChoise.clear();
        child.clear();
        mutant.clear();
    }
    vector<int> weightBest;
    vector<int> priceBest;
    vector<double> udelBest;

    GetWeightAndPrice(BestOfTheBest, priceBest, weightBest, udelBest);
    int sirtchMaxBest = serchMax(priceBest);
    cout << color<Green, Black> << "Ответ : " << "Кодировка " << BestOfTheBest[sirtchMaxBest] << "\t Цена :" << priceBest[sirtchMaxBest] << "\t Вес :" << weightBest[sirtchMaxBest] << "\t Удельный вес :" << udelBest[sirtchMaxBest] << color << endl;

    system("pause");
    return(0);
}

int main2()
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    ifstream in("text.txt");


    int metod = 0;
    int metod2 = 0;
    int metodSelection;
    int numberOfPopulations;
    vector<string> population;
    vector<int> populationPrice;
    vector<int> populationW;
    vector<double> populationUdel;
    vector<string> child;
    vector<int> childPrice;
    vector<int> childW;
    vector<double> childUdel;
    vector<string> mutant;
    vector<int> mutantPrice;
    vector<int> mutantW;
    vector<double> mutantUdel;
    vector<string> BestChoise;
    vector<string> BestOfTheBest;


    if (in.is_open())
    {
        for (int i = 0; i < K; i++) //Выделяем память 
        {
            vector<double> temp;
            for (int j = 0; j < 4; j++)
            {
                temp.push_back(1);
            }
            itemsAll1.push_back(temp);

        }

        for (int i = 0; i < K; i++) //Считаем матрицу из файла 
            for (int j = 0; j < 3; j++) {
                in >> itemsAll1[i][j];
                itemsAll1[i][3] = itemsAll1[i][1] / itemsAll1[i][2];
            }
        printItems(itemsAll1);
    }
    else
    {
        cout << color<Red, Black> << "Файл не открыт!!!" << color;
        return (0);
    }
    cout << color<Green, Black> << "Введите колчиество популяций : "; cin >> numberOfPopulations;; cout << color << endl;
    cout << color<Green, Black> << "Введите колчиество особей в популяции : "; cin >> PopSize; cout << color << endl;
    cout << color<Green, Black> << "Введите метод (1-Жадный ,2-Слуайный): "; cin >> metod; cout << color << endl;
    cout << color<Green, Black> << "способ формирования родительской пары (1-Панмиксия ,2-Положительное ассоциативное скрещивание):";  cin >> metod2; cout << color << endl;
    cout << color<Green, Black> << "способ селекции (1-турнир ,2-пропорциональная схема):";  cin >> metodSelection; cout << color << endl;


    population = MadePopulation(metod, PopSize, population, populationW, populationPrice, populationUdel); // Создаем начальную популяцию
    hasDublicate(population);//проверяем на повторы в популяции (если есть удаляем)
    cout << endl << "Популяция" << "\t" << "Цена" << "\t" << "Вес" << "\t" << "Удельный цена";
    for (int i = 0; i < population.size(); i++)
    {
        cout << endl << population[i] << "\t" << populationPrice[i] << "\t" << populationW[i] << "\t" << populationUdel[i];
    }

    int MaxPopulation = serchMax(populationPrice); // Ищем лучшего среди начальной популяции по цене

    cout << endl << color<Red, Black> << "Лучший из популяции: " << population[MaxPopulation] << "\t" << populationPrice[MaxPopulation] << "\t" << populationW[MaxPopulation] << "\t" << populationUdel[MaxPopulation] << color << endl << endl;
    BestChoise.push_back(population[MaxPopulation]); //Отбираем лучшего в отдельный вектор 


    for (int i = 0; i < numberOfPopulations; i++)
    {


        child = MadePair(metod2, population, populationUdel); // Создаём детей
        int sirtchMax = serchMax(populationPrice);
        child.push_back(population[sirtchMax]);// добавляем лучшего к детям
        hasDublicate(child);// ищем дубликаты 
        GetWeightAndPrice(child, childPrice, childW, childUdel); //Записываем у каждого цену ,вес , удельную стоимость В отделные вектора 
        int MaxChild = serchMax(childPrice);//Ищем лучшего ребенка по цене
        cout << endl << "Потомки :" << endl;

        for (int i = 0; i < child.size(); i++)
        {
            cout << child[i] << "\t" << childPrice[i] << "\t" << childW[i] << "\t" << childUdel[i] << endl;
        }
        cout << color<Red, Black> << "Лучший потомок: " << child[MaxChild] << "\t" << childPrice[MaxChild] << "\t" << childW[MaxChild] << "\t" << childUdel[MaxChild] << color << endl << endl;
        BestChoise.push_back(child[MaxChild]);//Отбираем лучшего в отдельный вектор 


        mutant = mutation(child);
        hasDublicate(mutant);
        cout << endl << "Потомки после мутации: " << endl;
        mutant.push_back(child[MaxChild]);
        GetWeightAndPrice(mutant, mutantPrice, mutantW, mutantUdel);

        int MaxMutant = serchMax(mutantPrice);

        for (int i = 0; i < mutant.size(); i++)
        {
            cout << mutant[i] << "\t" << mutantPrice[i] << "\t" << mutantW[i] << "\t" << mutantUdel[i] << endl;
        }
        cout << color<Red, Black> << "Лучший мутант: " << mutant[MaxMutant] << "\t" << mutantPrice[MaxMutant] << "\t" << mutantW[MaxMutant] << "\t" << mutantUdel[MaxMutant] << color << endl << endl;
        BestChoise.push_back(mutant[MaxMutant]);//Отбираем лучшего в отдельный вектор 


        Delete(populationPrice, populationW, populationUdel, childPrice, childW, childUdel, mutantPrice, mutantW, mutantUdel);
        population.clear();

        cout << "Новая популяция №" << i + 1 << endl;




        selection(child, mutant, population, metodSelection);
        hasDublicate(population);



       
        population.push_back(mutant[MaxMutant]);
        hasDublicate(population);
        GetWeightAndPrice(population, populationPrice, populationW, populationUdel);
        int MaxnewPopulation = serchMax(populationPrice);
        for (int i = 0; i < population.size(); i++)
        {
            cout << population[i] << "\t" << populationPrice[i] << "\t" << populationW[i] << "\t" << populationUdel[i] << endl;
        }
        cout << color<Red, Black> << "Лучший среди новой популяции: " << population[MaxnewPopulation] << "\t" << populationPrice[MaxnewPopulation] << "\t" << populationW[MaxnewPopulation] << "\t" << populationUdel[MaxnewPopulation] << color << endl << endl;
        hasDublicate(BestChoise);


        BestChoise.push_back(population[MaxnewPopulation]);
        for (int i = 0; i < BestChoise.size(); i++)
        {
            BestOfTheBest.push_back(BestChoise[i]);
        }
        hasDublicate(population);
        BestChoise.clear();
        child.clear();
        mutant.clear();
    }
    vector<int> weightBest;
    vector<int> priceBest;
    vector<double> udelBest;

    GetWeightAndPrice(BestOfTheBest, priceBest, weightBest, udelBest);
    int sirtchMaxBest = serchMax(priceBest);
    cout << color<Green, Black> << "Ответ : " << "Кодировка " << BestOfTheBest[sirtchMaxBest] << "\t Цена :" << priceBest[sirtchMaxBest] << "\t Вес :" << weightBest[sirtchMaxBest] << "\t Удельный вес :" << udelBest[sirtchMaxBest] << color << endl;

    system("pause");
    return(0);
}
int main() {
    using namespace std;
    setlocale(LC_ALL, "rus");
    cout << "Используем элитарную схему ? " << endl << "1 - да" << "\t 2 - нет ";
    int p = 0;
    cin >> p;
    if (p == 1)
    {
        return main2();
    }
    else main1();
}

