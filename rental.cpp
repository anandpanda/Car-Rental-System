#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include <cstring>

using namespace std;
void adminLogin();
void adminPage();
void addCar();
class Cars
{
public:
    char plate_no[15]; // eg. UP15AA0000 & we right code to make it unique
    char company_name[20];
    char model_name[20];
    char fuel_type; // have only three option :- P for petrol, D for desile, C for CNG
    char seater;    // have only two option 5, 7 seater
    char color[15];

public:
    void entry()
    {
        cout << "Enter company name              : ";
        fflush(stdin);
        cin.getline(company_name, 18);
        cout << "Enter model name                : ";
        fflush(stdin);
        cin.getline(model_name, 18);
        cout << "Enter plate number              : ";
        fflush(stdin);
        cin.getline(plate_no, 12);
        cout << "Capacity (5 or 7 seater)        : ";
        fflush(stdin);
        cin >> seater;
        cout << "Fuel(P petrol, D diesel, C CNG) : ";
        fflush(stdin);
        cin >> fuel_type;
        cout << "Color                           : ";
        fflush(stdin);
        cin.getline(color, 14);
    }
    friend bool check(char plate_no[], char mode);
    friend int displaydata();
};
template <class T>
class customer
{
public:
    char name[25];
    char phone_no[15];
    char plate_no[15];
    T time_per;
    T charges;
    void getData()
    {
        cout << "Enter Customer Details." << endl;
        cout << "Customer Name       : ";
        fflush(stdin);
        cin.getline(name, 20);
        cout << "Contact Number      : ";
        fflush(stdin);
        cin.getline(phone_no, 12);
    }
    friend void requestcar();
};
int displaydata(char opt)
{
    Cars show;
    int counting = 0;
    try
    {
        ifstream input;
        if (opt == '*')
        {
            input.open("carsDatabas.dat", ios ::binary | ios ::in);
        }
        else
        {
            input.open("carsAvailable.dat", ios ::binary | ios ::in);
        }
        if (!input.is_open())
        {
            throw 1;
        }
        input.seekg(ios ::beg);
        system("CLS");
        cout << "\t Showing all available Cars." << endl
             << endl;
        cout << "   --------------------------------------------------------------- " << endl;
        while (input.read((char *)&show, sizeof(show)))
        { 
            counting++;

            cout << "  |company name                    : " << setw(30) << left << show.company_name << "|" << endl;
            cout << "  |model name                      : " << setw(30) << left << show.model_name << "|" << endl;
            cout << "  |plate number                    : " << setw(30) << left << show.plate_no << "|" << endl;
            cout << "  |Capacity (5 or 7 seater)        : " << setw(30) << left << show.seater << "|" << endl;
            cout << "  |Fuel(P petrol, D diesel, C CNG) : " << setw(30) << left << show.fuel_type << "|" << endl;
            cout << "  |Color                           : " << setw(30) << left << show.color << "|" << endl;
            cout << "  -----------------------------------------------------------------" << endl;
        }
        if (input.eof() && counting != 0)
        {
            cout << "  |                     NO FURTHURE RECORDS                        |" << endl;
            cout << "   ----------------------------------------------------------------" << endl;
        }
        else if (input.eof() && counting == 0)
        {
            cout << "  |                   ADD NEW CARS TO DATABASE                     |" << endl;
            cout << "   ----------------------------------------------------------------" << endl;
        }
        cout << "Total cars : " << counting << endl;
        input.close();
    }
    catch (...)
    {
        cout << "Some Technical Error occurred, contact Developer ASAP." << endl;
        system("PAUSE");
    }
    system("PAUSE");
    return counting; 
}
bool check(char plate_no[], char mode)
{
    Cars chek;
    try
    {
        ifstream input;
        if (mode == '*')
        {
            input.open("carsDatabas.dat", ios ::binary | ios ::in);
        }
        else
        {
            input.open("carsAvailable.dat", ios ::binary | ios ::in);
        }
        if (!input.is_open())
        {
            throw 1;
        }
        input.seekg(ios ::beg);
        while (!input.eof())
        {
            input.read((char *)&chek, sizeof(chek));

            if (strcmp(plate_no, chek.plate_no) == 0)
            {
                input.close();
                return 0;
            }
        }
        input.close();
        return 1;
    }
    catch (...)
    {
        cout << "Some Technical Error occurred, contact Developer ASAP." << endl;
        system("PAUSE");
    }
    return 0;
}
void update(char plate_no[])
{
    Cars chek;
    try
    {
        ifstream input;
        ofstream temp;
        input.open("carsAvailable.dat", ios ::binary | ios ::in);
        temp.open("temporary.dat", ios ::binary | ios ::out | ios ::trunc);
        if (!input.is_open())
        {
            throw 1;
        }
        input.seekg(ios ::beg); // temp.seekp(ios :: end);
        while (input.read((char *)&chek, sizeof(chek)))
        {
            // input.read((char *)&chek, sizeof(chek));

            if (strcmp(plate_no, chek.plate_no) != 0)
            {
                temp.write((char *)&chek, sizeof(chek));
            }
        }
        input.close();
        remove("carsAvailable.dat");
        temp.close();

        // newrec();
        ofstream out;
        ifstream in;
        Cars copyy;
        out.open("carsAvailable.dat", ios ::binary | ios ::out | ios ::trunc);
        // cout << "Checkpoint 1" << endl;
        in.open("temporary.dat", ios ::binary | ios ::in);
        in.seekg(ios ::beg); // out.seekp(ios :: end);
        while (in.read((char *)&copyy, sizeof(copyy)))
        {
            out.write((char *)&copyy, sizeof(copyy));
        }
        out.close();
        in.close();
    }
    catch (...)
    {
        cout << "Some Technical Error occurred, contact Developer ASAP." << endl;
        system("PAUSE");
    }
}
void begintrip(customer<float> confirm)
{
    ofstream out;
    cout << endl;
    out.open("ongoingTrips.dat", ios ::binary | ios ::out | ios ::app);
    out.seekp(ios ::beg);
    try
    {
        if (!out.is_open())
        {
            throw 1;
        }
        out.write((char *)&confirm, sizeof(confirm));
        update(confirm.plate_no);
        cout << "Trip has been started." << endl;
        cout << "List of available cars has been updated." << endl;
    }
    catch (...)
    {
        cout << "Some technical error occurred, contact developer ASAP." << endl;
    }
    out.close();
}
void requestcar()
{
    Cars req;
    int empty = 0;
    customer<float> cust;
    char choice = 'y';
starting:
    fflush(stdout);
    // cout << "Customer is requesting for car." << endl;

    empty = displaydata('0');
    cout << "Customer is requesting for a car." << endl;
    if (empty != 0)
    {
        cust.getData();
        cout << "Choose plate number : ";
        fflush(stdin);
        cin.getline(cust.plate_no, 12);
        if (!check(cust.plate_no, 'a'))
        {
            cout << "Car of plate number " << cust.plate_no << " is available." << endl;
            cout << "Enter Time period(in hours or in days) : ";
            fflush(stdin);
            cin >> cust.time_per;
            cout << "Enter charges(per hours or per day)    : ";
            fflush(stdin);
            cin >> cust.charges;
            cout << "Total charges(including 10%Tax)        : " << (cust.time_per * cust.charges) + (0.10 * cust.time_per * cust.charges) << endl;
            begintrip(cust);
        }
        else
        {
            cout << "Sorry Car of requested plate number is not registered with us." << endl;
        }
        cout << "Have a new customer (y or n) : ";
        fflush(stdin);
        cin >> choice;
        if (choice == 'y')
        {
            goto starting;
        }
    }
    else
    {
        cout << "Sorry no service available. Come back later." << endl;
    }
    system("PAUSE");
}
int showtrips()
{
    customer<float> show;
    int counting = 0;
    try
    {
        ifstream input;
        input.open("ongoingTrips.dat", ios ::binary | ios ::in);
        if (!input.is_open())
        {
            throw 1;
        }
        input.seekg(ios ::beg);
        system("CLS");
        cout << "\t Showing all ongoing trips." << endl
             << endl;
        cout << "  -----------------------------------------------------------------" << endl;
        while (input.read((char *)&show, sizeof(show)))
        {
            counting++;

            cout << "  |Customer name               : " << setw(30) << left << show.name << "|" << endl;
            cout << "  |Customer contact number     : " << setw(30) << left << show.phone_no << "|" << endl;
            cout << "  |Rented car plate number     : " << setw(30) << left << show.plate_no << "|" << endl;
            cout << "  |Time period                 : " << setw(30) << left << show.time_per << "|" << endl;
            cout << "  |Charges                     : " << setw(30) << left << show.charges << "|" << endl;
            cout << "  |Total charges(including tax): " << setw(30) << left << (show.time_per * show.charges) + (0.10 * show.time_per * show.charges) << "|" << endl;
            cout << "  -----------------------------------------------------------------" << endl;
        }
        if (input.eof() && counting != 0)
        {
            cout << "  |                     NO FURTHURE RECORDS                        |" << endl;
            cout << "   ----------------------------------------------------------------" << endl;
        }
        else if (input.eof() && counting == 0)
        {
            cout << "  |                   ADD CUSTOMER TO DATABASE                     |" << endl;
            cout << "   ----------------------------------------------------------------" << endl;
        }
        cout << "Total cars : " << counting << endl;
        input.close();
    }
    catch (...)
    {
        cout << "Some Technical Error occurred, contact Developer ASAP." << endl;
        system("PAUSE");
    }

    system("PAUSE");
    return counting;
}
void returncar()
{

    int empty;
    int exist;
    char choice;
    char plate_no[15];
    customer<float> rtrn;
    Cars back;
starting:
    empty = showtrips();
    exist = 0;
    choice = 'y';
    if (empty != 0)
    {
        cout << endl
             << "Enter plate number of returned car : ";
        fflush(stdin);
        cin.getline(plate_no, 12);
        ifstream input;
        input.open("ongoingTrips.dat", ios ::binary | ios ::in);
        ofstream temp;
        temp.open("temporary.dat", ios ::binary | ios ::out | ios ::trunc);
        while (input.read((char *)&rtrn, sizeof(rtrn)))
        {
            if (strcmp(plate_no, rtrn.plate_no) == 0)
            {
                exist = 1;
                cout << "\tShowing details of trips." << endl
                     << endl;
                cout << "  ----------------------------------------------------------------- " << endl;
                cout << "  |Customer name               : " << setw(30) << left << rtrn.name << "|" << endl;
                cout << "  |Customer contact number     : " << setw(30) << left << rtrn.phone_no << "|" << endl;
                cout << "  |Rented car plate number     : " << setw(30) << left << rtrn.plate_no << "|" << endl;
                cout << "  |Time period                 : " << setw(30) << left << rtrn.time_per << "|" << endl;
                cout << "  |Charges                     : " << setw(30) << left << rtrn.charges << "|" << endl;
                cout << "  |Total charges(including tax): " << setw(30) << left << (rtrn.time_per * rtrn.charges) + (0.10 * rtrn.time_per * rtrn.charges) << "|" << endl;
                cout << "  ----------------------------------------------------------------- " << endl;
            }
            else
            {
                temp.write((char *)&rtrn, sizeof(rtrn));
            }
        }
        temp.close();
        input.close();
        if (exist == 1)
        {

            input.open("carsDatabas.dat", ios ::binary | ios ::in);
            input.seekg(ios ::beg);
            while (input.read((char *)&back, sizeof(back)))
            {
                if (strcmp(plate_no, back.plate_no) == 0)
                {
                    ofstream editt;
                    editt.open("carsAvailable.dat", ios ::binary | ios ::out | ios ::app);
                    editt.seekp(ios ::end);
                    editt.write((char *)&back, sizeof(back));
                    editt.close();
                    cout << "List of available has been updated." << endl;
                }
            }
            input.close();

            // Updating ontrip list.
            remove("ongoingTrips.dat");
            ofstream updat;
            updat.open("ongoingTrips.dat", ios ::binary | ios ::out);
            input.open("temporary.dat", ios ::binary | ios ::in);
            input.seekg(ios ::beg);
            while (input.read((char *)&rtrn, sizeof(rtrn)))
            {
                updat.write((char *)&rtrn, sizeof(rtrn));
            }
            cout << "Ongoing trips has been updated." << endl;
        }
        else
        {
            cout << "Car of " << plate_no << " is not gone for trip." << endl;
        }
    }
stop2:
    cout << "Is their another trip to end(y/n) : ";
    fflush(stdin);
    cin >> choice;
    if (choice != 'y' && choice != 'n')
    {
        cout << "\t Invalid input. Try again" << endl;
        goto stop2;
    }
    else if (choice == 'y')
    {
        goto starting;
    }
    system("PAUSE");
}
void deletecar()
{
    char plate_no[15];
    displaydata('0');
    cout << endl
         << "Enter plate number : ";
    fflush(stdin);
    cin.getline(plate_no, 12);
    if (!check(plate_no, '0'))
    {
        update(plate_no);
        Cars chek;
        try
        {
            ifstream input;
            ofstream temp;
            input.open("carsDatabas.dat", ios ::binary | ios ::in);
            temp.open("temporary.dat", ios ::binary | ios ::out | ios ::trunc);
            if (!input.is_open())
            {
                throw 1;
            }
            input.seekg(ios ::beg); // temp.seekp(ios :: end);
            while (input.read((char *)&chek, sizeof(chek)))
            {
                // input.read((char *)&chek, sizeof(chek));

                if (strcmp(plate_no, chek.plate_no) != 0)
                {
                    temp.write((char *)&chek, sizeof(chek));
                }
            }
            input.close();
            remove("carsDatabas.dat");
            temp.close();

            // newrec();
            ofstream out;
            ifstream in;
            Cars copyy;
            out.open("carsDatabas.dat", ios ::binary | ios ::out | ios ::trunc);
            // cout << "Checkpoint 1" << endl;
            in.open("temporary.dat", ios ::binary | ios ::in);
            in.seekg(ios ::beg); // out.seekp(ios :: end);
            while (in.read((char *)&copyy, sizeof(copyy)))
            {
                out.write((char *)&copyy, sizeof(copyy));
            }
            out.close();
            in.close();
        }
        catch (...)
        {
            cout << "Some Technical Error occurred, contact Developer ASAP." << endl;
            system("PAUSE");
        }
    }
    else
    {
        cout << "Car of plate number " << plate_no << " is not available.";
    }

    system("PAUSE");
}
void addCar()
{
    Cars regis;
    char choice = 'y';
    char ans;
    ofstream out;
    ofstream extra;
    ofstream extra2;
    system("cls");
    cout << endl;
    cout << "\t Registering new cars to our Database." << endl;
    cout << "\t -------------------------------------" << endl;
    cout << endl;
    cout << endl;
    cout << "Would you like to delete all previous records(y or n) ? ";
    fflush(stdin);
    cin >> ans;
    if (ans == 'n')
    {
        out.open("carsDatabas.dat", ios ::binary | ios ::out | ios ::app);
        cout << "In append mode." << endl;
        out.seekp(ios ::end);
    }
    else
    {
        out.open("carsDatabas.dat", ios ::binary | ios ::out | ios ::trunc);
        extra.open("carsAvailable.dat", ios ::binary | ios::out | ios ::trunc);
        extra2.open("ongoingTrips.dat", ios ::binary | ios::out | ios ::trunc);
        cout << "In new file" << endl;
    }
    try
    {
        if (!out.is_open())
        {
            throw 1;
        }
        do
        {
        stop1:
            regis.entry();
            extra.close();
            out.close();
            if (check(regis.plate_no, '*'))
            {
                cout << "\t Car added to database successfully." << endl;
                out.open("carsDatabas.dat", ios ::binary | ios ::out | ios ::app);
                extra.open("carsAvailable.dat", ios ::binary | ios ::out | ios ::app);
                extra.seekp(ios ::end);
                out.seekp(ios ::end);
                out.write((char *)&regis, sizeof(regis));
                extra.write((char *)&regis, sizeof(regis));
                out.close();
                extra.close();
            }
            else
            {
                cout << "A car with this plate number is already registered.";
            }
        stop2:
            cout << "Would you like to enter new car to database(y or n): ";
            fflush(stdin);
            cin >> choice;
            if (choice != 'y' && choice != 'n')
            {
                cout << "\t Invalid input. Try again" << endl;
                goto stop2;
            }

        } while (choice != 'n');
    }
    catch (...)
    {
        cout << "Some technical error occurred, contact developer ASAP." << endl;
    }
    system("PAUSE");
}
void adminLogin()
{
    system("CLS");
    char pasd[6] = {'a', 'b', 'c', '1', '2', '3'};
    char inpas[6];
    cout << "\n\n\t\t\t\t\t\t\tWELCOME\n\n\n"
         << endl;
    cout << "\t\t\t\t\t ------------------------------------ " << endl;
    cout << "\t\t\t\t\t|\t      ADMIN LOGIN            |" << endl;
    cout << "\t\t\t\t\t ------------------------------------ " << endl;
    cout << "\t\t\t\t\t \t Password : ";
    for (int i = 0; i < 6; i++)
    {
        inpas[i] = getch(); // a getch() function in a C/ C++ program to hold the output screen for some time until the user passes a key from the keyboard to exit the console screen.
        cout << "*";
    }
    cout << endl;

    if (pasd[0] == inpas[0] && pasd[1] == inpas[1] && pasd[2] == inpas[2] && inpas[3] == pasd[3] && inpas[4] == pasd[4] && inpas[5] == pasd[5])
    {
        cout << endl
             << "\t\t\t\t\t Log In successful." << endl;
    }
    else
    {
        cout << "\t\t\t\t\t Try Again" << endl;
        system("PAUSE");
        // pause() is a C++ method used to pause a program during execution. It allows the user to input or read data.
        // The pause approach makes the system more readable and user-friendly by allowing the user to read the instructions before performing any task.
        adminLogin();
    }
}
void adminPage()
{
    char choice;
mainPage:
    system("CLS");
    cout << "\t\t CAR RENTAL MANAGEMENT SYSTEM." << endl;
    cout << "\t\t -----------------------------" << endl;
    cout << "\t What would you like to do Sir/Mam?" << endl;
    cout << "\t 1. Register new car to the Database." << endl;
    cout << "\t 2. See all registered cars." << endl;
    cout << "\t 3. Customer request for a car." << endl;
    cout << "\t 4. Customer wants to return a car." << endl;
    cout << "\t 5. See all ongoing trips." << endl;
    cout << "\t 6. Delete a car from database." << endl;
    cout << "\t 7. LogOut." << endl;
    cout << endl
         << endl;
    cout << "\t Enter your choice : ";
    fflush(stdin);
    cin >> choice;
    switch (choice)
    {
    case '1':
        addCar();
        break;
    case '2':
        displaydata('*');
        break;
    case '3':
        requestcar();
        break;
    case '4':
        returncar();
        break;
    case '5':
        showtrips();
        break;
    case '6':
        deletecar();
        break;
    case '7':
        adminLogin();
        break;
    default:
        cout << "Invalid input" << endl;
        cout << "Try again." << endl;
        system("PAUSE");
    }

    goto mainPage;
}

int main()
{
    adminLogin();
    adminPage();
    return 0;
}
