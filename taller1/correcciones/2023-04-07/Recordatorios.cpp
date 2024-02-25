#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(int mes, int dia);

    int mes();
    int dia();

    string imprimir_fecha();

    void incrementar_dia();

    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif

  private:
    int _mes;
    int _dia;
};

// Constructor
Fecha::Fecha(int mes, int dia) : _mes(mes), _dia(dia) {}

int Fecha::mes() {
    return _mes;
}

int Fecha::dia() {
    return _dia;
}

string Fecha::imprimir_fecha() {
    return to_string(_dia) + "/" + to_string(_mes);
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    bool igual_mes = this->mes() == o.mes();
    return igual_dia and igual_mes;
}
#endif

ostream &operator<<(ostream &os, Fecha f) {
    os << f.imprimir_fecha();
    return os;
}

void Fecha::incrementar_dia() {
    _dia++;
    if (_dia > dias_en_mes(_mes)) {
        _dia = 1;
        _mes++;
        if (_mes > 12) _mes = 1;
    }
}

// Ejercicio 11, 12

// Clase Horario
class Horario {
public:
    Horario(uint hora, uint min);

    uint hora();
    uint min();

    string imprimir_horario();

    bool operator==(Horario o);
    bool operator<(Horario o);


private:
    uint _hora;
    uint _min;
};

// Constructor
Horario::Horario(uint hora, uint min) : _hora(hora), _min(min) {}

uint Horario::hora() {
    return _hora;
}

uint Horario::min() {
    return _min;
}

string Horario::imprimir_horario() {
    return to_string(_hora) + ":" + to_string(_min);
}

bool Horario::operator==(Horario o) {
    bool igual_hora = this->hora() == o.hora();
    bool igual_min = this->min() == o.min();
    return igual_hora and igual_min;
}

bool Horario::operator<(Horario o) {
    bool menor_hora = this->hora() < o.hora();
    bool menor_min = this->min() < o.min();
    return menor_hora or (_hora  == o.hora() and menor_min);
}

ostream &operator<<(ostream &os, Horario h) {
    os << h.imprimir_horario();
    return os;
}

// Ejercicio 13

// Clase Recordatorio
class Recordatorio {
public:
    Recordatorio(Fecha fecha,  Horario horario, string asunto);

    Fecha fecha();
    Horario horario();
    string asunto();

    string imprimirRecordatorio();

private:
    Fecha _fecha;
    Horario _horario;
    string _asunto;
};

// Constructor
Recordatorio::Recordatorio(Fecha fecha,  Horario horario, string asunto) : _fecha(fecha), _horario(horario), _asunto(asunto) {}

Fecha Recordatorio::fecha() {
    return _fecha;
}

Horario Recordatorio::horario() {
    return _horario;
}

string Recordatorio::asunto() {
    return _asunto;
}

string Recordatorio::imprimirRecordatorio() {
    return asunto() + " @ " + fecha().imprimir_fecha() + " " + horario().imprimir_horario();
}

ostream &operator<<(ostream &os, Recordatorio r) {
    os << r.imprimirRecordatorio();
    return os;
}

// Ejercicio 14

// Clase Agenda
class Agenda {
public:
    Agenda(Fecha fecha_desde);

    void agregar_recordatorio(Recordatorio r);

    void incrementar_dia();

    list<Recordatorio> recordatorios_hoy();

    Fecha hoy();

private:
    Fecha _hoy;
    map<string, list<Recordatorio>> _recordatorios;
};

Agenda::Agenda(Fecha fecha_desde) : _hoy(fecha_desde) {}

void Agenda::agregar_recordatorio(Recordatorio r) {
    list<Recordatorio> recordatorios = _recordatorios[r.fecha().imprimir_fecha()];
    auto pos = recordatorios.begin();
    while (pos != recordatorios.end()) {
        if (r.horario() < pos->horario()) {
            recordatorios.insert(pos, r);
            break;
        }
        pos++;
    }
    if (pos == recordatorios.end()) recordatorios.push_back(r);
    _recordatorios[r.fecha().imprimir_fecha()] = recordatorios;
}

void Agenda::incrementar_dia() {
    _hoy.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_hoy() {
    return _recordatorios[_hoy.imprimir_fecha()];
}

Fecha Agenda::hoy() {
    return _hoy;
}

ostream &operator<<(ostream &os, Agenda a) {
    os << a.hoy() << endl;
    os << "=====" << endl;
    for (Recordatorio r: a.recordatorios_hoy()) {
        os << r << endl;
    }
    return os;
}