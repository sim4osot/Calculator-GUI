#include <wx/wx.h>
#include <cmath>
#include <sstream>

class Calculator {
public:
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) {
        if (b == 0) return NAN;
        return a / b;
    }

    double power(double base, double exponent) { return pow(base, exponent); }

    double squareRoot(double value) {
        if (value < 0) return NAN;
        return sqrt(value);
    }

    int mod(int a, int b) {
        if (b == 0) return 0;
        return a % b;
    }

    double factorial(int n) {
        if (n < 0) return NAN;
        double result = 1;
        for (int i = 2; i <= n; ++i)
            result *= i;
        return result;
    }

    double logarithm(double x) {
        if (x <= 0) return NAN;
        return log10(x);
    }

    double ln(double x) {
        if (x <= 0) return NAN;
        return log(x);
    }

    double sine(double x) { return sin(x); }
    double cosine(double x) { return cos(x); }
    double tangent(double x) { return tan(x); }
};

class CalculatorFrame : public wxFrame {
public:
    CalculatorFrame() : wxFrame(nullptr, wxID_ANY, "OOP Calculator GUI", wxDefaultPosition, wxSize(400, 500)) {
        wxPanel* panel = new wxPanel(this);
        display = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(360, 50), wxTE_RIGHT);

        wxGridSizer* grid = new wxGridSizer(6, 4, 5, 5);

        wxString buttons[] = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", "-",
            "0", ".", "=", "+",
            "C", "^", "r", "%",
            "!", "log", "ln", "sin",
            "cos", "tan"
        };

        for (auto& label : buttons) {
            wxButton* btn = new wxButton(panel, wxID_ANY, label);
            grid->Add(btn, 1, wxEXPAND);
            btn->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        }

        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(display, 0, wxEXPAND | wxALL, 10);
        vbox->Add(grid, 1, wxEXPAND | wxALL, 10);

        panel->SetSizer(vbox);
    }

private:
    wxTextCtrl* display;
    Calculator calc;
    wxString currentInput;
    double firstOperand = 0;
    wxString operation;

    void OnButtonClicked(wxCommandEvent& evt) {
        wxString label = static_cast<wxButton*>(evt.GetEventObject())->GetLabel();

        if (label.IsNumber() || label == ".") {
            currentInput += label;
            display->SetValue(currentInput);
        } else if (label == "C") {
            currentInput = "";
            operation = "";
            firstOperand = 0;
            display->Clear();
        } else if (label == "=") {
            double secondOperand = wxAtof(currentInput);
            double result = 0;

            if (operation == "+") result = calc.add(firstOperand, secondOperand);
            else if (operation == "-") result = calc.subtract(firstOperand, secondOperand);
            else if (operation == "*") result = calc.multiply(firstOperand, secondOperand);
            else if (operation == "/") result = calc.divide(firstOperand, secondOperand);
            else if (operation == "^") result = calc.power(firstOperand, secondOperand);
            else if (operation == "%") result = calc.mod((int)firstOperand, (int)secondOperand);
            else result = NAN;

            currentInput = wxString::Format("%.10g", result);
            display->SetValue(currentInput);
            operation = "";
        } else if (label == "!" || label == "log" || label == "ln" || label == "sin" || label == "cos" || label == "tan" || label == "r") {
            double input = wxAtof(currentInput);
            double result = 0;

            if (label == "!") result = calc.factorial((int)input);
            else if (label == "log") result = calc.logarithm(input);
            else if (label == "ln") result = calc.ln(input);
            else if (label == "sin") result = calc.sine(input);
            else if (label == "cos") result = calc.cosine(input);
            else if (label == "tan") result = calc.tangent(input);
            else if (label == "r") result = calc.squareRoot(input);

            currentInput = wxString::Format("%.10g", result);
            display->SetValue(currentInput);
        } else {
            firstOperand = wxAtof(currentInput);
            currentInput = "";
            operation = label;
        }
    }
};

class CalculatorApp : public wxApp {
public:
    bool OnInit() override {
        CalculatorFrame* frame = new CalculatorFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(CalculatorApp);
