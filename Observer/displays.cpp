#include <iostream>
#include <list>

using namespace std;

class Display {
public:
    virtual void ShowInfo(const string&) = 0;
    virtual ~Display() {};
};

class LCDDisplay : public Display {
public:
    void ShowInfo(const string& info) override {
        cout << "LCDDisplay: " << info << endl;
    }
};

class CRTDisplay : public Display {
public:
    void ShowInfo(const string& info) override {
        cout << "CRTDisplay: " << info << endl;
    }
};

class Controller {
public:
    void DoWork() {
        // do some work
        PrintOnDisplay("Hello");
    }

    void PrintOnDisplay(const string& info) {
        for (auto* display: displays_) {
            display->ShowInfo(info);
        }
    }

    void RegisterDisplay(Display* display) {
        displays_.push_back(display);
    }
    void UnregisterDisplay(Display* display) {
        displays_.remove(display);
    }
private:
    list<Display*> displays_;
};

int main() {
    Controller controller;
    
    Display* lcd_display = new LCDDisplay;
    Display* crt_display = new CRTDisplay;

    controller.RegisterDisplay(lcd_display);
    controller.RegisterDisplay(crt_display);

    controller.DoWork();

    controller.UnregisterDisplay(crt_display);
    controller.DoWork();

    delete lcd_display;
    delete crt_display;

    return 0;
}
