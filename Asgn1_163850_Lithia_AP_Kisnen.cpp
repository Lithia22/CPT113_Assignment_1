#include <iostream>
#include <string>
#include <limits> 
#include <iomanip>
using namespace std;

class Base_Info {
private:
    double Price_PerTon;
    double Subsidy_PerTon;
    double Cost_PerRelong;

public:
    Base_Info() {
        // Constructor 
        Price_PerTon = 0.0;
        Subsidy_PerTon = 0.0;
        Cost_PerRelong = 0.0;
    }

    // Destructor
    ~Base_Info() {}

    // Mutators to set private member variables
    void setPrice_PerTon(const double &price) { Price_PerTon = price; }
    void setSubsidy_PerTon(const double &subsidy) { Subsidy_PerTon = subsidy; }
    void setCost_PerRelong(const double &cost) { Cost_PerRelong = cost; }

    // Accessors to get private member variables
    double getPrice_PerTon() const { return Price_PerTon; }
    double getSubsidy_PerTon() const { return Subsidy_PerTon; }
    double getCost_PerRelong() const { return Cost_PerRelong; }

    // Declaration of friend function
    friend void input_BaseInfo(Base_Info &base_info); 
};

class Sale_Info {
private:
    string Farmer_Name;
    string Farmer_ID;
    double Field_Size;
    double Weight;
    double Weight_Deduction;
    string Productivity_Rate;

public:
    Sale_Info() {
        // Constructor
        Farmer_Name = "";
        Farmer_ID = "";
        Field_Size = 0.0;
        Weight = 0.0;
        Weight_Deduction = 0.0;
        Productivity_Rate = "";
    }

    // Destructor
    ~Sale_Info() {}

    // Mutators to set private member variables
    void setFarmer_Name(const string &name) { Farmer_Name = name; }
    void setFarmer_ID(const string &id) { Farmer_ID = id; }
    void setField_Size(const double &size) { Field_Size = size; }
    void setWeight(const double &weight) { Weight = weight; }
    void setWeight_Deduction(const double &deduction) { Weight_Deduction = deduction; }
    void setProductivity_Rate(const string &rate) { Productivity_Rate = rate; }

    // Accessors to get private member variables
    string getFarmer_Name() const { return Farmer_Name; }
    string getFarmer_ID() const { return Farmer_ID; }
    double getField_Size() const { return Field_Size; }
    double getWeight() const { return Weight; }
    double getWeight_Deduction() const { return Weight_Deduction; }
    string getProductivity_Rate() const { return Productivity_Rate; }

    // Function to display paddy information
    void Display_Paddy_Info() {
        cout << "Farmer's Name: " << Farmer_Name << endl;
        cout << "Farmer's ID: " << Farmer_ID << endl;
        cout << "Paddy Field Size: " << Field_Size << " relong" << endl;
        cout << "Paddy Weight: " << Weight << " metric tons" << endl;
        cout << "Weight Deduction: " << Weight_Deduction << "%" << endl;
        cout << "Net Weight: " << (Weight - (Weight * Weight_Deduction / 100)) << " metric tons" << endl;
    }
};

//Income_Calculator is inheriting from the Base_Info
class Income_Calculator : public Base_Info { 
private:
    Sale_Info saleInfo; // Composition: Income_Calculator has an instance of Sale_Info
    double Total_Price;
    double Total_Subsidy;
    double Incentive;
    double Total_Cost;
    double Net_Income;
    string Productivity_Rate;

public:
    Income_Calculator() {
        // Constructor
        Total_Price = 0.0;
        Total_Subsidy = 0.0;
        Incentive = 0.0;
        Total_Cost = 0.0;
        Net_Income = 0.0;
        Productivity_Rate = "";
    }

    // Destructor
    ~Income_Calculator() {}

    // Accessors to get private member variables
    double getTotal_Price() const { return Total_Price; }
    double getTotal_Subsidy() const { return Total_Subsidy; }
    double getIncentive() const { return Incentive; }
    double getTotal_Cost() const { return Total_Cost; }
    double getNet_Income() const { return Net_Income; }
    string getProductivity_Rate() const { return Productivity_Rate; }
	
    // Function to calculate income based on sales information
    void Calculate_Income(Sale_Info &saleInfo, double pricePerTon, double subsidyPerTon, double costPerRelong) {
    	
    	cout << fixed <<setprecision(2);
    	
        double Net_Weight = saleInfo.getWeight() - (saleInfo.getWeight() * saleInfo.getWeight_Deduction() / 100);
        Total_Price = Net_Weight * pricePerTon;
        Total_Subsidy = Net_Weight * subsidyPerTon;
        Incentive = 200 * saleInfo.getField_Size();

        if (saleInfo.getField_Size() > 1.5) {
            Productivity_Rate = "High";
        } else if (saleInfo.getField_Size() >= 1 && saleInfo.getField_Size() <= 1.5) {
            Productivity_Rate = "Moderate";
        } else {
            Productivity_Rate = "Low";
        }

        Total_Cost = saleInfo.getField_Size() * costPerRelong;
        Net_Income = Total_Price + Total_Subsidy + Incentive - Total_Cost;
    }

    // Function to display income information
    void Display_Income_Info() {
        cout << "Total Paddy Price: RM" << getTotal_Price() << endl;
        cout << "Total Subsidy: RM" << getTotal_Subsidy() << endl;
        cout << "Productivity Rate: " << getProductivity_Rate() << endl;
        cout << "Incentive: RM" << getIncentive() << endl;
        cout << "Total Planting Cost: RM" << getTotal_Cost() << endl;
        cout << "Net Income: RM" << getNet_Income() << endl;
    }
};

// Function declarations
void Display_Menu();
void Input_Base_Info(Base_Info &baseInfo);
void Input_Sale_Info(Sale_Info &saleInfo);
void Display_Farmers_By_Productivity(Income_Calculator &incomeCalc, Sale_Info Info_Array[]);

const int MAX_FARMERS = 10;
Sale_Info Info_Array[MAX_FARMERS];

int main() {
    int choice;
    Base_Info paddy0;
    Income_Calculator incomeCalc;
    string enter;

	system("Color 0B");
    do {
        Display_Menu();
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");
		
		if (cin.fail()) {
            cout << "Invalid input. Please try again with a number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            continue; 
        }
        
        switch (choice) {
            case 1:
                Input_Base_Info(paddy0);
                cout << "Press enter to return to the main menu";
                cin.ignore();
                getline(cin, enter); 
                Display_Menu();
                system("cls");
                break;
            case 2:
                for (int i = 0; i < MAX_FARMERS; i++) {
                    if (Info_Array[i].getFarmer_Name().empty()) {
                        Input_Sale_Info(Info_Array[i]);
                        if (Info_Array[i].getField_Size() > 1.5) {
                            Info_Array[i].setProductivity_Rate("High");
                        } else if (Info_Array[i].getField_Size() >= 1 && Info_Array[i].getField_Size() <= 1.5) {
                            Info_Array[i].setProductivity_Rate("Moderate");
                        } else {
                            Info_Array[i].setProductivity_Rate("Low");
                        }
                        break;
                    }
                }
                cout << "Press enter to return to the main menu";
                cin.ignore();
                getline(cin, enter);
                Display_Menu();
                system("cls");
                break;
            case 3:
                for (int i = 0; i < MAX_FARMERS; i++) {
                    if (!Info_Array[i].getFarmer_Name().empty()) {
                        Info_Array[i].Display_Paddy_Info();
                       incomeCalc.Calculate_Income(Info_Array[i], paddy0.getPrice_PerTon(), paddy0.getSubsidy_PerTon(), paddy0.getCost_PerRelong());
                        incomeCalc.Display_Income_Info();
                        cout << "-------------------------------------------" << endl;
                    }
                }
                cout << "Press enter to return to the main menu";
                cin.ignore();
                getline(cin, enter); 
                Display_Menu();
                system("cls");
                break;
            case 4:
                Display_Farmers_By_Productivity(incomeCalc, Info_Array);
				cout << "Press enter to return to the main menu";
                cin.ignore();
                getline(cin, enter);
                Display_Menu();
                system("cls"); 
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
		}      
    } while (choice != 5);

    return 0;
}

void Display_Menu() {
    cout << "************* MyPaddy Apps *************" << endl;
    cout << "1. Input Paddy Base Information" << endl;
    cout << "2. Input Paddy Sale Information" << endl;
    cout << "3. Display Paddy Sale Information" << endl;
    cout << "4. Display Farmers by Productivity" << endl; 
    cout << "5. Exit" << endl; 
    cout << "****************************************" << endl;
}

void Input_Base_Info(Base_Info &baseInfo) {
    double price, subsidy, cost;
    cout << "Paddy price per ton: ";
    cin >> price;
    cout << "Subsidy per ton: ";
    cin >> subsidy;
    cout << "Cost planting paddy per Relong: ";
    cin >> cost;
    baseInfo.setPrice_PerTon(price);
    baseInfo.setSubsidy_PerTon(subsidy);
    baseInfo.setCost_PerRelong(cost);
}

void Input_Sale_Info(Sale_Info &saleInfo) {
    string name, id;
    double fieldSize, weight, deduction;

    cout << "Enter farmer's name: ";
    cin.ignore();
    getline(cin, name);
    saleInfo.setFarmer_Name(name);

    cout << "Enter farmer's ID: ";
    cin >> id;
    saleInfo.setFarmer_ID(id);

    cout << "Enter size of the paddy field (in relong): ";
    cin >> fieldSize;
    saleInfo.setField_Size(fieldSize);

    cout << "Enter paddy weight (in metric tons): ";
    cin >> weight;
    saleInfo.setWeight(weight);

    cout << "Enter weight deduction (%): ";
    cin >> deduction;
    saleInfo.setWeight_Deduction(deduction);
}

void Display_Farmers_By_Productivity(Income_Calculator &incomeCalc, Sale_Info Info_Array[]) {
    cout << "-------------------------------------------" << endl;
    cout << "      High Productivity Farmers" << endl;
    cout << "-------------------------------------------" << endl;
    for (int i = 0; i < MAX_FARMERS; i++) {
        if (Info_Array[i].getFarmer_Name() != "" && Info_Array[i].getProductivity_Rate() == "High") {
            cout << Info_Array[i].getFarmer_Name() << endl;
        }
    }

    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "    Moderate Productivity Farmers" << endl;
    cout << "-------------------------------------------" << endl;
    for (int i = 0; i < MAX_FARMERS; i++) {
        if (Info_Array[i].getFarmer_Name() != "" && Info_Array[i].getProductivity_Rate() == "Moderate") {
            cout << Info_Array[i].getFarmer_Name() << endl;
        }
    }

    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "      Low Productivity Farmers" << endl;
    cout << "-------------------------------------------" << endl;
    for (int i = 0; i < MAX_FARMERS; i++) {
        if (Info_Array[i].getFarmer_Name() != "" && Info_Array[i].getProductivity_Rate() == "Low") {
            cout << Info_Array[i].getFarmer_Name() << endl;
        }
    }
}

