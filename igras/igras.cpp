#include <iostream>
#include <string>
#include <Windows.h>
#include <stdexcept>

using namespace std;

class Geroy
{
private:
    string imya;
    int hp;
    int uron;

public:
    virtual ~Geroy() {}
    // Конструктор
    Geroy(string imyaGeroya, int zdorovie, int sila)
    {
        imya = imyaGeroya;
        hp = zdorovie;
        uron = sila;
    }

    string getImya() const
    {
        return imya;
    }

    int getHp() const
    {
        return hp;
    }

    int getUron() const
    {
        return uron;
    }

    virtual int ataka() const
    {
        return uron;
    }
    void poluchitUron(int silaAtaki)
    {
        if (silaAtaki < 0)
            throw invalid_argument("Урон не может быть отрицательным");

        hp -= silaAtaki;

        if (hp < 0)
            hp = 0;
    }
};

class Voin : public Geroy
{
public:
    Voin() : Geroy("Воин", 120, 20)
    {
    }

    int ataka() const override
    {
        return getUron();
    }
};

class Luchnik : public Geroy
{
public:
    Luchnik() : Geroy("Лучник", 90, 25)
    {
    }

    int ataka() const override
    {
        return getUron() + 5;
    }
};

class Mag : public Geroy
{
public:
    Mag() : Geroy("Маг", 80, 30)
    {
    }

    int ataka() const override
    {
        return getUron() + 4;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try
    {
        Voin voin;
        Luchnik luchnik;
        Mag mag;

        Geroy* geroi[] = { &voin, &luchnik, &mag };

        int viborGeroya;
        int viborProtivnika;

        cout << "Арена героев\n";

        cout << "\nВыберите героя:\n";
        cout << "1. Воин\n";
        cout << "2. Лучник\n";
        cout << "3. Маг\n";
        cout << "0. Выход\n";

        while (true)
        {
            cout << "Выберите героя (1-3): ";
            cin >> viborGeroya;

            if (cin && viborGeroya >= 0 && viborGeroya <= 3)
                break;

            cout << "Введите число от 1 до 3.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        if (viborGeroya == 0)
            return 0;

        cout << "\nВы выбрали: "
            << geroi[viborGeroya - 1]->getImya() << "\n";

        cout << "\nВыберите противника:\n";

        for (int i = 0; i < 3; i++)
        {
            if (i != viborGeroya - 1)
            {
                cout << i + 1 << ". "
                    << geroi[i]->getImya() << "\n";
            }
        }

        while (true)
        {
            cout << "Выберите противника (1-3): ";
            cin >> viborProtivnika;

            if (cin && viborProtivnika >= 1 &&
                viborProtivnika <= 3 &&
                viborProtivnika != viborGeroya)
            {
                break;
            }

            cout << "Выберите другого героя от 1 до 3.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        Geroy* igrok = geroi[viborGeroya - 1];
        Geroy* protivnik = geroi[viborProtivnika - 1];

        cout << "\n Забив \n";
        cout << igrok->getImya() << " VS "
            << protivnik->getImya() << "\n";

        int deystvie;

        while (igrok->getHp() > 0 && protivnik->getHp() > 0)
        {
            cout << "\n------------------------\n";
            cout << igrok->getImya() << " | HP: "
                << igrok->getHp() << "\n";
            cout << protivnik->getImya() << " | HP: "
                << protivnik->getHp() << "\n";

            cout << "\nВаш ход:\n";
            cout << "1. Атаковать\n";
            cout << "2. Защищаться\n";

            while (true)
            {
                cout << "Выберите действие (1 или 2): ";
                cin >> deystvie;

                if (cin && (deystvie == 1 || deystvie == 2))
                    break;

                cout << "Введите только 1 или 2.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            if (deystvie == 1)
            {
                protivnik->poluchitUron(igrok->ataka());

                cout << "\nВы нанесли "
                    << igrok->getUron() << " урона\n";
            }
            else
            {
                cout << "\nВы защищаетесь\n";
            }

            if (protivnik->getHp() <= 0)
            {
                cout << "\nGG EZ\n";
                break;
            }

            int uronProtivnika = protivnik->ataka();

            if (deystvie == 2)
            {
                uronProtivnika /= 2;
            }

            igrok->poluchitUron(uronProtivnika);

            cout << "Противник нанёс "
                << uronProtivnika << " урона\n";

            if (igrok->getHp() <= 0)
            {
                cout << "\n лох проиграл (Тимофей Александрович не лох).\n";
                cout << "Игра окончена.\n";
                break;
            }
        }
    }
    catch (const exception& oshibka)
    {
        cout << "Ошибка: " << oshibka.what() << "\n";
        return 1;
    }

    return 0;
}