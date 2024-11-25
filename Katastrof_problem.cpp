#include <iostream>
#include <vector>
#include <string>

class Katastrofa {
protected:
    std::string nazev;
    std::vector<std::string> oblasti;

public:
    Katastrofa(const std::string& nazev, const std::vector<std::string>& oblasti)
        : nazev(nazev), oblasti(oblasti) {}

    virtual bool isRisky() const = 0; // Чисто виртуальный метод
    virtual std::string getTyp() const = 0; // Тип катастрофы
    std::string getNazev() const { return nazev; }
    const std::vector<std::string>& getOblasti() const { return oblasti; }

    virtual ~Katastrofa() {}
};

class Zemetreseni : public Katastrofa {
    double magnituda;

public:
    Zemetreseni(const std::string& nazev, const std::vector<std::string>& oblasti, double magnituda)
        : Katastrofa(nazev, oblasti), magnituda(magnituda) {}

    bool isRisky() const override {
        return magnituda > 6.5; // Рискованное, если магнитуда больше 6.5
    }

    std::string getTyp() const override {
        return "Zemetreseni";
    }
};

class Tornado : public Katastrofa {
    int fujitaSkala;

public:
    Tornado(const std::string& nazev, const std::vector<std::string>& oblasti, int fujitaSkala)
        : Katastrofa(nazev, oblasti), fujitaSkala(fujitaSkala) {}

    bool isRisky() const override {
        return fujitaSkala >= 3; // Рискованное, если категория ≥ 3
    }

    std::string getTyp() const override {
        return "Tornado";
    }
};

class EvidenceKatastrof {
    std::vector<Katastrofa*> seznam; // Используем массив сырых указателей

public:
    ~EvidenceKatastrof() {
        for (Katastrofa* katastrofa : seznam) {
            delete katastrofa; // Освобождение памяти
        }
    }

    void pridatKatastrofu(Katastrofa* katastrofa) {
        seznam.push_back(katastrofa);
    }

    void vypisKatastrofyVOblasti(const std::string& oblast) const {
        std::cout << "Katastrofy v oblasti: " << oblast << "\n";
        for (const Katastrofa* katastrofa : seznam) {
            for (const std::string& o : katastrofa->getOblasti()) {
                if (o == oblast) {
                    std::cout << " - " << katastrofa->getNazev() << " (" << katastrofa->getTyp() << ")\n";
                    break;
                }
            }
        }
    }

    void vypisRizikoveKatastrofy(bool rizikove) const {
        std::cout << (rizikove ? "Rizikove" : "Nerizikove") << " katastrofy:\n";
        for (const Katastrofa* katastrofa : seznam) {
            if (katastrofa->isRisky() == rizikove) {
                std::cout << " - " << katastrofa->getNazev() << " (" << katastrofa->getTyp() << ")\n";
            }
        }
    }
};

int main() {
    EvidenceKatastrof evidence;

    // Создание катастроф
    evidence.pridatKatastrofu(new Zemetreseni("Brno Quake", {"Brno", "Olomouc"}, 7.0));
    evidence.pridatKatastrofu(new Tornado("Olomouc Tornado", {"Olomouc", "Brno"}, 4));
    evidence.pridatKatastrofu(new Zemetreseni("Small Quake", {"Praha"}, 5.0));

    // Вывод катастроф в Брно
    evidence.vypisKatastrofyVOblasti("Brno");

    // Вывод рискованных катастроф
    evidence.vypisRizikoveKatastrofy(true);

    // Вывод нерискованных катастроф
    evidence.vypisRizikoveKatastrofy(false);

    return 0;
}