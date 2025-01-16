#include <iostream>
#include <vector>
using namespace std;

class Bottle {
private:
    double volume;

public:
    // Имплицитен конструктор
    Bottle() : volume(0) {}

    // Експлицитен конструктор
    Bottle(double vol) : volume(vol) {}

    // Гетър за обема
    double getVolume() const {
        return volume;
    }

    // Сетър за обема
    void setVolume(double vol) {
        volume = vol;
    }
};

class Cabinet {
private:
    vector<Bottle> bottles;

public:
    // Оператор за добавяне на бутилка в шкафа
    void operator+=(const Bottle& bottle) {
        bottles.push_back(bottle);
    }

    // Функция за проверка дали комбинация от бутилки може да съвпадне с даден обем
    bool canMatchVolume(double targetVolume) {
        return canMatchVolumeHelper(targetVolume, 0);
    }

private:
    // Помощна функция за проверка на комбинации рекурсивно
    bool canMatchVolumeHelper(double targetVolume, size_t index) {
        if (targetVolume == 0) return true;
        if (targetVolume < 0 || index >= bottles.size()) return false;

        // Включи текущата бутилка и провери
        if (canMatchVolumeHelper(targetVolume - bottles[index].getVolume(), index + 1)) {
            return true;
        }

        // Изключи текущата бутилка и провери
        return canMatchVolumeHelper(targetVolume, index + 1);
    }
};

int main() {
    Cabinet cabinet;
    int numBottles;
    cout << "Въведете броя на бутилките: ";
    cin >> numBottles;

    for (int i = 0; i < numBottles; ++i) {
        double volume;
        cout << "Въведете обема на бутилка " << i + 1 << ": ";
        cin >> volume;
        Bottle bottle(volume);
        cabinet += bottle;
    }

    double targetVolume;
    cout << "Въведете целевия обем за проверка: ";
    cin >> targetVolume;

    if (cabinet.canMatchVolume(targetVolume)) {
        cout << "Съществува комбинация от бутилки, която съвпада с обема " << targetVolume << " литра." << endl;
    } else {
        cout << "Няма комбинация от бутилки, която съвпада с обема " << targetVolume << " литра." << endl;
    }

    return 0;
}
