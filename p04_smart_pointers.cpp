// Practical 04 - RAII and Smart Pointers
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

struct Sensor {
    static int alive;
    string name;
    Sensor(string n) : name(n) { alive++; }
    ~Sensor() { alive--; }
};
int Sensor::alive = 0;

// one Logger used by two different modules -> real shared ownership
struct Logger {
    vector<string> lines;
    void log(const string& s) { lines.push_back(s); }
    ~Logger() { cout << "  Logger destroyed (" << lines.size() << " lines written)\n"; }
};

struct TemperatureModule {
    shared_ptr<Logger> logger;
    TemperatureModule(shared_ptr<Logger> l) : logger(l) {}
    void run() { logger->log("temperature = 31C"); }
};

struct HumidityModule {
    shared_ptr<Logger> logger;
    HumidityModule(shared_ptr<Logger> l) : logger(l) {}
    void run() { logger->log("humidity = 64%"); }
};

void rawPointerVersion(int iterations) {
    for (int i = 0; i < iterations; i++) {
        Sensor* s = new Sensor("raw");
        if (i % 2 == 0) continue;   // early exit path -> delete gets skipped (bug!)
        delete s;
    }
}

void uniquePtrVersion(int iterations) {
    for (int i = 0; i < iterations; i++) {
        auto s = make_unique<Sensor>("smart");
        if (i % 2 == 0) continue;   // same early exit, but unique_ptr still cleans up
    }
}

int main() {
    cout << "1) unique_ptr - single owner\n";
    {
        unique_ptr<Sensor> p1 = make_unique<Sensor>("rain-sensor");
        cout << "  p1 owns: " << p1->name << "\n";
        unique_ptr<Sensor> p2 = std::move(p1);   // can't copy, only move
        cout << "  after move, p1 is " << (p1 ? "not null" : "null")
             << ", p2 owns: " << p2->name << "\n";
        cout << "  Sensors alive inside block: " << Sensor::alive << "\n";
    }
    cout << "  Sensors alive after block: " << Sensor::alive << "\n\n";

    cout << "2) shared_ptr - shared Logger\n";
    {
        auto logger = make_shared<Logger>();
        cout << "  use_count after creating: " << logger.use_count() << "\n";
        TemperatureModule t(logger);
        HumidityModule h(logger);
        cout << "  use_count with 2 modules: " << logger.use_count() << "\n";
        t.run();
        h.run();
        logger.reset();   // main gives up its copy
        cout << "  main released its pointer, use_count now: "
             << t.logger.use_count() << "\n";
    }   // last two owners go out of scope here -> Logger destroyed
    cout << "\n3) Raw pointer vs unique_ptr (100000 iterations each)\n";
    rawPointerVersion(100000);
    int leakedByRaw = Sensor::alive;
    cout << "  raw pointer  -> objects never deleted: " << leakedByRaw << "\n";
    uniquePtrVersion(100000);
    cout << "  unique_ptr   -> objects never deleted: " << Sensor::alive - leakedByRaw << "\n";
    return 0;
}
