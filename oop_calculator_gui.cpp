#include <wx/wx.h>
#include <cmath>
#include <sstream>
#include <stack>
#include <string>

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
    double squareRoot(double value) { if (value < 0) return NAN; return sqrt(value); }
    int mod(int a, int b) { if (b == 0) return 0; return a % b; }
    double factorial(int n) { if (n < 0) return NAN; double result = 1; for (int i = 2; i <= n; ++i) result *= i; return result; }
    double logarithm(double x) { if (x <= 0) return NAN; return log10(x); }
    double ln(double x) { if (x <= 0) return NAN; return log(x); }
    double sine(double x) { return sin(x); }
    double cosine(double x) { return cos(x); }
    double tangent(double x) { return tan(x); }

    double evaluateExpression(const std::string& expression) {
        std::stack<double> values;
        std::stack<char> ops;

        for (size_t i = 0; i < expression.size(); ++i) {
            if (isdigit(expression[i])) {
                double num = 0;
                while (i < expression.size() && isdigit(expression[i])) {
                    num = num * 10 + (expression[i] - '0');
                    i++;
                }
                values.push(num);
                i--; // To counteract the i++ in the loop
            } else if (expression[i] == '+') {
                ops.push(expression[i]);
            } else if (expression[i] == '-') {
                ops.push(expression[i]);
            } else if (expression[i] == '*') {
                ops.push(expression[i]);
            } else if (expression[i] == '/') {
                ops.push(expression[i]);
            } 
        }

        while (!ops.empty()) {
            char op = ops.top();
            ops.pop();

            double right = values.top();
            values.pop();

            double left = values.top();
            values.pop();

            double result = 0;
            if (op == '+') result = add(left, right);
            else if (op == '-') result = subtract(left, right);
            else if (op == '*') result = multiply(left, right);
            else if (op == '/') result = divide(left, right);

            values.push(result);
        }

        return values.top();
    }
};

class CalculatorFrame : public wxFrame {
public:
    CalculatorFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 400)),
          resultDisplayed(false) {

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        display = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(280, 40), wxTE_RIGHT);
        sizer->Add(display, 0, wxEXPAND | wxALL, 10);

        wxGridSizer* grid = new wxGridSizer(4, 4, 5, 5);

        wxButton* btn0 = new wxButton(this, 1000, "0");
        wxButton* btn1 = new wxButton(this, 1001, "1");
        wxButton* btn2 = new wxButton(this, 1002, "2");
        wxButton* btn3 = new wxButton(this, 1003, "3");
        wxButton* btn4 = new wxButton(this, 1004, "4");
        wxButton* btn5 = new wxButton(this, 1005, "5");
        wxButton* btn6 = new wxButton(this, 1006, "6");
        wxButton* btn7 = new wxButton(this, 1007, "7");
        wxButton* btn8 = new wxButton(this, 1008, "8");
        wxButton* btn9 = new wxButton(this, 1009, "9");

        wxButton* btnAdd = new wxButton(this, 1010, "+");
        wxButton* btnSubtract = new wxButton(this, 1011, "-");
        wxButton* btnMultiply = new wxButton(this, 1012, "*");
        wxButton* btnDivide = new wxButton(this, 1013, "/");
        wxButton* btnMod = new wxButton(this, 1016, "%");
        wxButton* btnSquareRoot = new wxButton(this, 1017, "√");
        wxButton* btnPower = new wxButton(this, 1018, "^");
        wxButton* btnFactorial = new wxButton(this, 1019, "!");
        wxButton* btnLog = new wxButton(this, 1020, "log");
        wxButton* btnLn = new wxButton(this, 1021, "ln");
        wxButton* btnSin = new wxButton(this, 1022, "sin");
        wxButton* btnCos = new wxButton(this, 1023, "cos");
        wxButton* btnTan = new wxButton(this, 1024, "tan");

        wxButton* btnEqual = new wxButton(this, 1014, "=");
        wxButton* btnClear = new wxButton(this, 1015, "C");

        grid->Add(btn1, 0, wxEXPAND);
        grid->Add(btn2, 0, wxEXPAND);
        grid->Add(btn3, 0, wxEXPAND);
        grid->Add(btnAdd, 0, wxEXPAND);

        grid->Add(btn4, 0, wxEXPAND);
        grid->Add(btn5, 0, wxEXPAND);
        grid->Add(btn6, 0, wxEXPAND);
        grid->Add(btnSubtract, 0, wxEXPAND);

        grid->Add(btn7, 0, wxEXPAND);
        grid->Add(btn8, 0, wxEXPAND);
        grid->Add(btn9, 0, wxEXPAND);
        grid->Add(btnMultiply, 0, wxEXPAND);

        grid->Add(btn0, 0, wxEXPAND);
        grid->Add(btnClear, 0, wxEXPAND);
        grid->Add(btnEqual, 0, wxEXPAND);
        grid->Add(btnDivide, 0, wxEXPAND);

        sizer->Add(grid, 1, wxEXPAND);
        SetSizerAndFit(sizer);

        btn0->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn1->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn2->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn3->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn4->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn5->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn6->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn7->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn8->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btn9->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnAdd->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnSubtract->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnMultiply->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnDivide->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnMod->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnSquareRoot->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnPower->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnFactorial->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnLog->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnLn->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnSin->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnCos->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnTan->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClicked, this);
        btnEqual->Bind(wxEVT_BUTTON, &CalculatorFrame::OnEqualClicked, this);
        btnClear->Bind(wxEVT_BUTTON, &CalculatorFrame::OnClearClicked, this);
    }

    void OnButtonClicked(wxCommandEvent& event) {
        wxButton* button = (wxButton*)event.GetEventObject();
        wxString label = button->GetLabel();

        // If user presses any operator or number after result is shown, clear the display
        if (resultDisplayed) {
            display->Clear();
            resultDisplayed = false; // Reset flag
        }

        display->AppendText(label);
    }

    void OnClearClicked(wxCommandEvent& event) {
        display->Clear();
        resultDisplayed = false; // Reset flag
    }

    void OnEqualClicked(wxCommandEvent& event) {
        wxString expression = display->GetValue();
        double result = calculator.evaluateExpression(expression.ToStdString());
        display->SetValue(wxString::Format("%f", result));
        resultDisplayed = true; 
    }

private:
    wxTextCtrl* display;
    Calculator calculator;
    bool resultDisplayed; // Flag to track if result was shown
};

class CalculatorApp : public wxApp {
public:
    virtual bool OnInit() {
        CalculatorFrame* frame = new CalculatorFrame("OOP Calculator");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(CalculatorApp);
