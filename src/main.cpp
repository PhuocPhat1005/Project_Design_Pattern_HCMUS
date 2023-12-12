#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cmath>

using namespace std;

class User;
class Manager;
class Bank;

class People
{
protected:
    string name, address, phone, mail;

public:
    People() {}
    People(string name, string address, string phone, string mail) : name(name), address(address), phone(phone), mail(mail) { set_email(); }
    People(string name, string address, string phone) : name(name), address(address), phone(phone) { set_email(); }
    void set_email()
    {
        if (mail == "")
        {
            mail = name + "@gmail.com";
            for (int i = 0; i < mail.length(); i++)
                if (mail[i] == ' ')
                    mail.erase(mail.begin() + i);
        }
    }
    void set_name(string name)
    {
        this->name = name;
    }
    string get_name()
    {
        return name;
    }
    string get_address()
    {
        return address;
    }
    string get_phone()
    {
        return phone;
    }
    string get_mail()
    {
        return mail;
    }
    void set_info()
    {
        cout << "Name: ";
        getline(cin, name);
        cout << "Address: ";
        getline(cin, address);
        cout << "Phone: ";
        getline(cin, phone);
        cout << "Email: ";
        getline(cin, mail);
    }
    void changeInfo()
    {
        string tmp = "";
        cout << "New Name (press -1 to giu nguyen): ";
        getline(cin, tmp);
        if (tmp != "-1")
            name = tmp;
        cout << "New Address (press -1 to giu nguyen): ";
        getline(cin, tmp);
        if (tmp != "-1")
            address = tmp;
        cout << "New Phone (press -1 to giu nguyen): ";
        getline(cin, tmp);
        if (tmp != "-1")
            phone = tmp;
        cout << "New Email (press -1 to giu nguyen): ";
        getline(cin, tmp);
        if (tmp != "-1")
            mail = tmp;
    }
    ~People() {}

    // virtual void showInfo()
    // {
    //     cout << "Name: " << name << endl;
    //     cout << "Address: " << address << endl;
    //     cout << "Phone: " << phone << endl;
    //     cout << "Email: " << mail << endl;
    // }
};

string low(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
    }
    s[0] -= 32;
    return s;
}

class Account
{
protected:
    string username, password;

public:
    Account() {}
    Account(string username, string password) : username(username), password(password) {}
    string get_username()
    {
        return username;
    }
    string get_password()
    {
        return password;
    }
    void set_password(string password)
    {
        this->password = password;
    }
    void set_username(string username)
    {
        this->username = username;
    }
    ~Account() {}
};

class MediatorUser
{
public:
    virtual long long calc_money() = 0;
    virtual bool findCard(string type) = 0;
    virtual long long send_money_to_account() = 0;
};

class MediatorBank
{
public:
    virtual void send_money_to_other_user(User *user) = 0;
    virtual void send_noti_to_user() = 0;
};

class Card
{
protected:
    long long money_in_card;
    string type;
    MediatorUser *mediator;

public:
    Card() {}
    Card(MediatorUser *mediator, string type) : mediator(mediator), type(type), money_in_card(0) {}
    ~Card()
    {
        // delete mediator; ???????????????
    }
    long long get_money_in_card()
    {
        return money_in_card;
    }
    string get_type()
    {
        return type;
    }
    void set_type(string type)
    {
        this->type = type;
    }
    void set_money_in_card(long long money_in_card)
    {
        this->money_in_card = money_in_card;
    }

    void calc_all_money()
    {
        long long tmp = mediator->calc_money();
        cout << "All money: " << tmp << endl;
    }
    bool find_card(string type)
    {
        return mediator->findCard(type);
    }
    long long send_money_to_account()
    {
        return mediator->send_money_to_account();
    }
};

class User : public People, public MediatorUser
{
protected:
    int ID;
    long long money;
    Account account;
    vector<Card> cards;
    MediatorBank *mediator;

public:
    User() {}
    User(string name, string address, string phone, string mail, int ID, long long money) : People(name, address, phone, mail), ID(ID), money(money) {}
    User(string name, string address, string phone) : People(name, address, phone), ID(0), money(0) {}
    User(People p) : People(p), ID(0), money(0) {}
    void set_money(long long money)
    {
        this->money = money;
    }
    long long get_money()
    {
        return money;
    }
    void set_ID(int ID)
    {
        this->ID = ID;
    }
    int get_ID()
    {
        return ID;
    }
    void set_account(Account account)
    {
        this->account = account;
    }
    Account get_account()
    {
        return account;
    }
    void add_card(Card card)
    {
        cards.push_back(card);
    }
    vector<Card> get_cards()
    {
        return cards;
    }
    void changePassword()
    {
        string password;
        cout << "Input new password: ";
        getline(cin, password);
        account.set_password(password);
    }
    void change_money()
    {
        cout << "You are not allowed to change money!\n";
        return;
    }
    void showInfo()
    {
        // People::showInfo();
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << mail << endl;
        cout << "Money in account: " << money << endl;
        if (cards.size() == 0)
            cout << "No card!" << endl;
        else
            for (int i = 0; i < cards.size(); i++)
            {
                cout << "Card " << i + 1 << ": " << cards[i].get_type() << " card | Money in this card: " << cards[i].get_money_in_card() << endl;
            }
    }
    long long calc_money() override
    {
        long long res = 0;
        for (int i = 0; i < cards.size(); i++)
        {
            res += cards[i].get_money_in_card();
        }
        return res;
    }
    bool findCard(string type) override
    {
        for (int i = 0; i < cards.size(); i++)
        {
            if (cards[i].get_type() == type)
                return true;
        }
        return false;
    }
    long long send_money_to_account() override
    {
        long long res = 0;
        for (int i = 0; i < cards.size(); i++)
        {
            res += cards[i].get_money_in_card();
            cards[i].set_money_in_card(0);
        }
        return res;
    }
    void set_mediator(MediatorBank *mediator)
    {
        this->mediator = mediator;
    }
    void send_money_to_other_user()
    {
        mediator->send_money_to_other_user(this);
    }
    void get_noti(string noti)
    {
        cout << "User " << name << " got a notification: " << noti << endl;
    }
    ~User()
    {
        // delete mediator; ??????????????????????
    }
};

class AdapterManager
{
public:
    AdapterManager() {}
    ~AdapterManager()
    {
    }
    void change_money(User *user, Bank *bank) const
    {
        cout << "Change money of " << user->get_name() << " to: ";
        long long tmp;
        cin >> tmp;
        cin.ignore();
        cout << "Change money of " << user->get_name() << " from " << user->get_money() << " to " << tmp << " successfully!" << endl;
        user->set_money(tmp);
        return;
    }
};

class Manager : public People, public AdapterManager
{
protected:
    string ID, password;
    long long salary;
    MediatorBank *mediator;

public:
    Manager() {}
    Manager(string name, string address, string phone, string mail, string ID, long long salary) : People(name, address, phone, mail), ID(ID), salary(salary) {}
    ~Manager()
    {
        //////////////////////////////
    }
    long long get_salary()
    {
        return salary;
    }
    void set_salary(long long salary)
    {
        this->salary = salary;
    }
    void set_ID(string ID)
    {
        this->ID = ID;
    }
    void set_password(string password)
    {
        this->password = password;
    }
    string get_ID()
    {
        return ID;
    }
    string get_password()
    {
        return password;
    }
    void set_info()
    {
        People::set_info();
        cout << "ID: ";
        getline(cin, ID);
        cout << "Password: ";
        getline(cin, password);
        cout << "Salary: ";
        cin >> salary;
        cin.ignore();
    }
    void set_mediator(MediatorBank *mediator)
    {
        this->mediator = mediator;
    }
    virtual void requestChangeSalary()
    {
        cout << "Please waiting, admin will process your request!" << endl;
    }
    void send_noti_to_user()
    {
        mediator->send_noti_to_user();
    }
    void showInfo()
    {
        // People::showInfo();
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << mail << endl;
        cout << "ID: " << ID << endl;
        cout << "Salary: " << salary << endl;
    }
};

class AdapterBank
{
public:
    AdapterBank() {}
    ~AdapterBank()
    {
    }
    void create_account(User *user, Bank *bank) const;
    void create_card(User *user, Bank *bank)
    {
        cout << user->get_name() << endl;
        string type;
        cout << "What type of card do you want to create? (Silver/Gold/Platinum): ";
        getline(cin, type);
        type = low(type);
        while (type != "Silver" && type != "Gold" && type != "Platinum")
        {
            cout << "What type of card do you want to create? (Silver/Gold/Platinum): ";
            getline(cin, type);
        }

        if ((type == "Silver" && user->get_money() < 1000000) || (type == "Gold" && user->get_money() < 5000000) || (type == "Platinum" && user->get_money() < 10000000))
        {
            cout << "Not enough money to create card!" << endl;
            return;
        }
        cout << "Create " << type << " card for " << user->get_name() << " successfully!" << endl;
        cout << "Money in this card: ";
        long long tmp;
        cin >> tmp;
        cin.ignore();
        if (tmp > user->get_money())
        {
            cout << "Not enough money to send to this card!\n";
            return;
        }
        user->set_money(user->get_money() - tmp);
        Card card(user, type);
        card.set_money_in_card(tmp);
        user->add_card(card);
        return;
    }
};

class Bank : public MediatorBank, public AdapterBank
{
protected:
    string bankName, location;

public:
    vector<Manager *> managers;
    vector<User *> users;
    Bank()
    {
        managers.clear();
        users.clear();
    }
    Bank(string name, string location) : bankName(name), location(location)
    {
        managers.clear();
        users.clear();
    }
    ~Bank() {}
    // vector<Manager> get_managers()
    // {
    //     return managers;
    // }
    // vector<User> get_users()
    // {
    //     return users;
    // }
    string get_bankName()
    {
        return bankName;
    }
    string get_location()
    {
        return location;
    }
    void add_user(User *user)
    {
        user->set_ID(users.size() + 1);
        users.push_back(user);
    }
    void delete_user(User *user)
    {
        cout << "Delete user " << user->get_name() << " successfully!" << endl;
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i]->get_name() == user->get_name())
            {
                users.erase(users.begin() + i);
                break;
            }
        }
    }
    void add_manager(Manager *manager)
    {
        managers.push_back(manager);
    }
    void delete_manager(Manager *manager)
    {
        cout << "Delete manager " << manager->get_name() << " successfully!" << endl;
        for (int i = 0; i < managers.size(); i++)
        {
            if (managers[i]->get_name() == manager->get_name())
            {
                managers.erase(managers.begin() + i);
                break;
            }
        }
    }
    void showListUser()
    {
        cout << "List of users in " << bankName << ": \n";
        if (users.size() == 0)
            cout << "No data!\n";
        else
            for (int i = 0; i < users.size(); i++)
            {
                cout << "Users " << users[i]->get_ID() << ":\n";
                users[i]->showInfo();
            }
    }
    void showListManager() const
    {
        cout << "List of managers in " << bankName << ": \n";
        if (managers.size() == 0)
            cout << "No data!\n";
        else
            for (int i = 0; i < managers.size(); i++)
            {
                cout << "Manager " << i + 1 << ":\n";
                managers[i]->showInfo();
            }
    }
    void UpdateUser(User *user)
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i]->get_name() == user->get_name())
            {
                users[i] = user;
                break;
            }
        }
    }
    void UpdateManager(Manager *manager)
    {
        for (int i = 0; i < managers.size(); i++)
        {
            if (managers[i]->get_name() == manager->get_name())
            {
                managers[i] = manager;
                break;
            }
        }
    }
    void processchangeSalary(Manager *manager)
    {
        for (int i = 0; i < managers.size(); i++)
        {
            if (true) // managers[i].get_ID() == manager->get_ID()
            {
                cout << "Change salary of " << manager->get_name() << " to: ";
                int tmp;
                cin >> tmp;
                cin.ignore();
                cout << "Change salary of " << manager->get_name() << " from " << managers[i]->get_salary() << " to " << tmp << " successfully!" << endl;
                managers[i]->set_salary(tmp);
                UpdateManager(managers[i]);
                return;
            }
        }
    }
    bool searchUser(string name)
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i]->get_name() == name)
                return true;
        }
        return false;
    }
    Manager *searchManager(string ID, string password)
    {
        for (int i = 0; i < managers.size(); i++)
        {
            if (managers[i]->get_ID() == ID && managers[i]->get_password() == password)
                return managers[i];
        }
    }
    void send_money_to_other_user(User *user) override
    {
        cout << "Who do you want to send money to? ";
        string name;
        getline(cin, name);
        User *user_get_money = new User();
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i]->get_name() == name)
            {
                user_get_money = users[i];
                break;
            }
        }
        cout << "How much do you want to send? ";
        long long tmp;
        cin >> tmp;
        cin.ignore();
        if (tmp > user->get_money())
            cout << "Not enough money to send to this user!\n";
        else
        {
            user_get_money->set_money(user_get_money->get_money() + tmp);
            user->set_money(user->get_money() - tmp);
            cout << "Send money to " << user_get_money->get_name() << " successfully!\n";
            UpdateUser(user_get_money);
        }
        delete user_get_money;
    }
    void send_noti_to_user() override
    {
        string noti;
        cout << "Enter notification: ";
        getline(cin, noti);
        for (int i = 0; i < users.size(); i++)
        {
            users[i]->get_noti(noti);
        }
        cout << "Send notification to all users successfully!\n";
    }
};

void addUserToBank(User *user, Bank *bank)
{
    ofstream file("Account.txt", ios::app);
    if (file.is_open())
    {
        file << bank->get_bankName() << endl;
        file << bank->get_location() << endl;
        file << user->get_account().get_username() << endl;
        file << user->get_account().get_password() << endl;
        file << user->get_name() << endl;
        file << user->get_address() << endl;
        file << user->get_phone() << endl;
        file << user->get_mail() << endl;
        file << user->get_ID() << endl;
        file << user->get_money() << endl;
        int n = user->get_cards().size();
        file << n << endl;
        for (int i = 0; i < n; i++)
        {
            file << user->get_cards()[i].get_type() << endl;
            file << user->get_cards()[i].get_money_in_card() << endl;
        }
        file << endl;
        file.close();
        cout << "User info saved to Account.txt successfully!" << endl;
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

// void addManagerToBank()
// {
//     ofstream file("Manager.txt", ios::app);
//     if (file.is_open())
//     {
//         string name, address, phone, mail, ID, password, bankName, location;
//         long long salary;
//         cout << "Bank name: ";
//         getline(cin, bankName);
//         cout << "Bank's location: ";
//         getline(cin, location);
//         cout << "Name: ";
//         getline(cin, name);
//         cout << "Address: ";
//         getline(cin, address);
//         cout << "Phone: ";
//         getline(cin, phone);
//         cout << "Email: ";
//         getline(cin, mail);
//         cout << "ID: ";
//         getline(cin, ID);
//         cout << "Password: ";
//         getline(cin, password);
//         cout << "Salary: ";
//         cin >> salary;
//         cin.ignore();
//         if(mail == "")
//             mail = name + "@gmail.com";
//         for(int i = 0; i < mail.length(); i++)
//             if(mail[i] == ' ')
//                 mail.erase(mail.begin() + i);

//         file << bankName << endl;
//         file << location << endl;
//         file << name << endl;
//         file << address << endl;
//         file << phone << endl;
//         file << mail << endl;
//         file << ID << endl;
//         file << password << endl;
//         file << salary << endl;
//         file << endl;
//         file.close();
//         cout << "Manager info saved to Manager.txt successfully!" << endl;
//     }
//     else
//     {
//         cout << "Unable to open file!" << endl;
//     }
// }

void init(vector<Bank *> banks)
{
    ifstream file("Account.txt");
    if (file.is_open())
    {
        string bankName, location, username, password, name, address, phone, mail;
        int ID, money, n;
        while (!file.eof())
        {
            getline(file, bankName);
            if (bankName == "")
                break;
            getline(file, location);
            getline(file, username);
            getline(file, password);
            getline(file, name);
            getline(file, address);
            getline(file, phone);
            getline(file, mail);
            file >> ID;
            file.ignore();
            file >> money;
            file.ignore();
            User *user = new User(name, address, phone, mail, ID, money);
            Account account(username, password);
            user->set_account(account);
            file >> n;
            file.ignore();
            for (int i = 0; i < n; i++)
            {
                string type;
                long long money_in_card;
                getline(file, type);
                file >> money_in_card;
                file.ignore();
                Card card(user, type);
                card.set_money_in_card(money_in_card);
                user->add_card(card);
            }
            file.ignore();
            for (int i = 0; i < banks.size(); i++)
            {
                if (banks[i]->get_bankName() == bankName && banks[i]->get_location() == location)
                {
                    banks[i]->add_user(user);
                    break;
                }
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
    file.open("Manager.txt");
    if (file.is_open())
    {
        string name, address, phone, mail, ID, password, bankName, location;
        long long salary;
        while (!file.eof())
        {
            getline(file, bankName);
            if (bankName == "")
                break;
            getline(file, location);
            getline(file, name);
            getline(file, address);
            getline(file, phone);
            getline(file, mail);
            getline(file, ID);
            getline(file, password);
            file >> salary;
            file.ignore(); // ignore cin
            file.ignore(); // ignore endl
            Manager *manager = new Manager(name, address, phone, mail, ID, salary);
            manager->set_password(password);
            for (int i = 0; i < banks.size(); i++)
            {
                if (banks[i]->get_bankName() == bankName && banks[i]->get_location() == location)
                {
                    banks[i]->add_manager(manager);
                    break;
                }
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
    cout << "Init successfully!" << endl;
}

void saveData(vector<Bank *> banks)
{
    ofstream fout("Account.txt");
    for (int i = 0; i < banks.size(); i++)
    {
        for (int j = 0; j < banks[i]->users.size(); j++)
        {
            fout << banks[i]->get_bankName() << endl;
            fout << banks[i]->get_location() << endl;
            fout << banks[i]->users[j]->get_account().get_username() << endl;
            fout << banks[i]->users[j]->get_account().get_password() << endl;
            fout << banks[i]->users[j]->get_name() << endl;
            fout << banks[i]->users[j]->get_address() << endl;
            fout << banks[i]->users[j]->get_phone() << endl;
            fout << banks[i]->users[j]->get_mail() << endl;
            fout << banks[i]->users[j]->get_ID() << endl;
            fout << banks[i]->users[j]->get_money() << endl;
            int n = banks[i]->users[j]->get_cards().size();
            fout << n << endl;
            for (int k = 0; k < n; k++)
            {
                fout << banks[i]->users[j]->get_cards()[k].get_type() << endl;
                fout << banks[i]->users[j]->get_cards()[k].get_money_in_card() << endl;
            }
            fout << endl;
        }
    }
    fout.close();

    fout.open("Manager.txt");
    for (int i = 0; i < banks.size(); i++)
    {
        for (int j = 0; j < banks[i]->managers.size(); j++)
        {
            fout << banks[i]->get_bankName() << endl;
            fout << banks[i]->get_location() << endl;
            fout << banks[i]->managers[j]->get_name() << endl;
            fout << banks[i]->managers[j]->get_address() << endl;
            fout << banks[i]->managers[j]->get_phone() << endl;
            fout << banks[i]->managers[j]->get_mail() << endl;
            fout << banks[i]->managers[j]->get_ID() << endl;
            fout << banks[i]->managers[j]->get_password() << endl;
            fout << banks[i]->managers[j]->get_salary() << endl;
            fout << endl;
        }
    }
    fout.close();
}

void AdapterBank::create_account(User *user, Bank *bank) const
{
    string username, password;
    cout << "Username: ";
    getline(cin, username);
    while (bank->searchUser(username))
    {
        cout << "Username already exists! Please choose another username: ";
        getline(cin, username);
    }
    cout << "Password: ";
    getline(cin, password);
    Account account(username, password);
    user->set_account(account);
    user->set_money(0);
    user->set_ID(bank->users.size() + 1);
    cout << "Create account for " << user->get_name() << " successfully!" << endl;
    user->set_email();
    bank->add_user(user);
    addUserToBank(user, bank);
    return;
}

class ClassAdapter : public Manager, public Bank
{
protected:
    Manager *manager;
    Bank *bank;

public:
    ClassAdapter() {}
    ClassAdapter(Manager *manager, Bank *bank) : manager(manager), bank(bank) {}
    ~ClassAdapter()
    {
        delete bank;
        delete manager;
    }
    void requestChangeSalary() override
    {
        bank->processchangeSalary(manager);
        return;
    }
    void access(Manager *manager, Bank *bank)
    {
        this->manager = manager;
        this->bank = bank;
    }
};

void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void TextColor(int x)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

void drawBox(int y)
{
    TextColor(68);
    for (int i = 0; i <= y + 1; i++)
    {
        gotoxy(95, i + 2);
        SetConsoleOutputCP(65001);
        cout << "║║";
    }
    TextColor(7);
}
int choiceMenu(vector<string> adj)
{
    int choice = 0;
    drawBox(adj.size());
    for (int i = 0; i < adj.size(); i++)
    {

        gotoxy(100, i + 3);
        if (i == choice)
        {
            cout << "-> ";
            TextColor(10);
        }
        else
            cout << "   ";
        cout << i + 1 << ". " << adj[i] << endl;
        TextColor(7);
    }
    while (1)
    {
        if (kbhit())
        {
            char ch = getch();
            if (toupper(ch) == 'W')
                --choice;
            if (toupper(ch) == 'S')
                ++choice;
            if (choice < 0)
                choice = adj.size() - 1;
            if (choice >= adj.size())
                choice = 0;
            if (ch == 13)
                break;
            for (int i = 0; i < adj.size(); i++)
            {
                gotoxy(100, i + 3);
                if (i == choice)
                {
                    cout << "-> ";
                    TextColor(10);
                }
                else
                    cout << "   ";
                cout << i + 1 << ". " << adj[i] << endl;
                TextColor(7);
            }
        }
    }
    system("cls");
    return choice;
}

int main()
{
    Bank *bank = new Bank();

    AdapterBank *adapterB = new AdapterBank();
    AdapterManager *adapterM = new AdapterManager();
    ClassAdapter *adapterC = new ClassAdapter();

    // User tmp("Thanh", "HCM", "0123456789", "", 0, 1000000);
    // tmp.set_mediator(bank);
    // Manager tmp2("Thaadasnh", "HCfasfaM", "01234aaaaaa6789", "", "", 10131232130);
    // bank->add_manager(tmp2);
    // bank->add_user(tmp);

    // addManagerToBank(); bug

    vector<Bank *> banks = {new Bank("Vietcombank", "Ho Chi Minh City"),
                            new Bank("Vietinbank", "Ha Noi"),
                            new Bank("Agribank", "Ho Chi Minh City"),
                            new Bank("BIDV", "Da Nang"),
                            new Bank("Vietcombank", "Ha Noi")};
    init(banks);
    system("cls");
    cout << "Welcome to Viet Nam Bank!\nPlease choose a bank to continue: \n";
    int choice1 = choiceMenu({"Vietcombank, Ho Chi Minh City", "Vietinbank, Ha Noi", "Agribank, Ho Chi Minh City", "BIDV, Da Nang", "Vietcombank, Ha Noi"});

    bank = banks[choice1];

    cout << "Welcome to " << bank->get_bankName() << "!\n";
    cout << "Please choose an option: \n";
    choice1 = choiceMenu({"Sign In", "Sign Up", "Exit"});

    bool flag1 = false;
    while (!flag1)
    {
        switch (choice1)
        {
            int choice2;
        case 0:
        {
            cout << "Sign In as: \n";
            choice2 = choiceMenu({"User", "Manager", "Admin", "Exit"});
            switch (choice2)
            {
            case 0:
            {
                User *user = new User();
                cout << "Username: ";
                string username;
                getline(cin, username);
                cout << "Password: ";
                string password;
                getline(cin, password);
                bool fought = false;
                for (int i = 0; i < bank->users.size(); i++)
                {
                    if (bank->users[i]->get_account().get_username() == username && bank->users[i]->get_account().get_password() == password)
                    {
                        user = bank->users[i];
                        fought = true;
                        break;
                    }
                }
                if (fought == false)
                    cout << "Wrong username or password!\n";
                else
                {
                    cout << "Sign in successfully!" << endl;
                    cout << "Welcome " << user->get_name() << endl;
                    bool flag2 = false;
                    while (!flag2)
                    {
                        // cout << "1. Change info\n";
                        // cout << "2. Change password\n";
                        // cout << "3. Create card\n"; // adapter
                        // cout << "4. Show info\n";
                        // cout << "5. Send request to change money\n"; // adapter
                        // cout << "6. Sum of money in cards\n";        // mediator
                        // cout << "7. Find card\n";                    // mediator
                        // cout << "8. Rut tien ve tai khoan\n";        // mediator
                        // cout << "9. Send money to other user\n";     // mediator
                        // cout << "10. Exit\n";

                        int choice3 = choiceMenu({"Change info", "Change password", "Create card", "Show info", "Send request to change money", "Sum of money in cards", "Find card", "Rut tien ve tai khoan", "Send money to other user", "Back"});
                        switch (choice3)
                        {
                        case 0:
                        {
                            user->changeInfo();
                            bank->UpdateUser(user);
                            break;
                        }
                        case 1:
                        {
                            user->changePassword();
                            bank->UpdateUser(user);
                            break;
                        }
                        case 2:
                        {
                            adapterB->create_card(user, bank);
                            bank->UpdateUser(user);
                            break;
                        }
                        case 3:
                        {
                            user->showInfo();
                            break;
                        }
                        case 4:
                        {
                            user->change_money();
                            cout << "An manager will process your request!\n";
                            adapterM->change_money(user, bank);
                            bank->UpdateUser(user);
                            break;
                        }
                        case 5:
                        {
                            if (user->get_cards().size() == 0)
                                cout << "You have no card!\n";
                            else
                                user->get_cards()[0].calc_all_money();
                            break;
                        }
                        case 6:
                        {
                            if (user->get_cards().size() == 0)
                                cout << "You have no card!\n";
                            else
                            {
                                cout << "Choose type to check: \n";
                                string type;
                                getline(cin, type);
                                type = low(type);
                                if (user->findCard(type))
                                {
                                    cout << "You have this card!\nMoney in this card: ";
                                    cout << user->get_cards()[0].get_money_in_card() << endl;
                                    // Same result because of same mediator
                                    // cout << user->get_cards()[1].get_money_in_card() << endl;
                                }
                                else
                                    cout << "You don't have this card!\n";
                            }
                            break;
                        }
                        case 7:
                        {
                            if (user->get_cards().size() == 0)
                                cout << "You have no card!\n";
                            else
                            {
                                user->set_money(user->get_money() + user->send_money_to_account());
                                cout << "Rut tien thanh cong!\n";
                            }

                            break;
                        }
                        case 8:
                        {
                            user->send_money_to_other_user();
                            break;
                        }
                        case 9:
                        {
                            flag2 = true;
                            break;
                        }
                        default:
                            break;
                        }
                    }
                }
                break;
            }
            case 1:
            {
                string password, ID;
                cout << "Enter your ID: ";
                getline(cin, ID);
                cout << "Enter your password: ";
                getline(cin, password);
                // Manager *pManager = bank->searchManager(ID, password);
                Manager *pManager = new Manager("ThanhTo", "HCM", "0123456789", "", "", 1000000);
                if (pManager != NULL)
                {
                    cout << "Hello " << pManager->get_name() << endl;
                    bool flag3 = false;
                    while (!flag3)
                    {
                        int choice4 = choiceMenu({"Change money of user", "Send request to change salary", "Send notification to all users", "Back"});

                        switch (choice4)
                        {
                        case 0:
                        {
                            string name;
                            bool found = false;
                            cout << "Enter name of user: ";
                            getline(cin, name);
                            User *user = new User();
                            for (int i = 0; i < bank->users.size(); i++)
                            {
                                if (bank->users[i]->get_name() == name)
                                {
                                    user = bank->users[i];
                                    found = true;
                                    break;
                                }
                            }
                            if (found == false)
                                cout << "User not found!\n";
                            else
                            {
                                pManager->change_money(user, bank);
                                bank->UpdateUser(user);
                            }
                            delete user;
                            break;
                        }
                        case 1:
                        {
                            pManager->requestChangeSalary();
                            cout << "Admin processed your request!\n";
                            adapterC->access(pManager, bank);
                            adapterC->requestChangeSalary();
                            break;
                        }
                        case 2:
                        {
                            pManager->set_mediator(bank);
                            pManager->send_noti_to_user();
                            break;
                        }
                        case 3:
                        {
                            flag3 = false;
                            break;
                        }
                        default:
                            break;
                        }
                    }
                }
                delete pManager;
                break;
            }
            case 2:
            {
                cout << "Hello admin!" << endl;
                bool flag4 = false;
                while (!flag4)
                {
                    int choice5 = choiceMenu({"Show list of users", "Show list of managers", "Add user", "Delete user", "Add manager", "Delete manager", "Back"});

                    switch (choice5)
                    {
                    case 0:
                    {
                        bank->showListUser();
                        break;
                    }
                    case 1:
                    {
                        bank->showListManager();
                        break;
                    }
                    case 2:
                    {
                        User *user = new User();
                        user->set_mediator(bank);
                        user->set_info();
                        bank->create_account(user, bank);
                        cout << "Add user " << user->get_name() << " successfully!" << endl;
                    }
                    case 3:
                    {
                        string name;
                        cout << "Enter name of user: ";
                        getline(cin, name);
                        User *user = new User();
                        for (int i = 0; i < bank->users.size(); i++)
                        {
                            if (bank->users[i]->get_name() == name)
                            {
                                user = bank->users[i];
                                break;
                            }
                        }
                        bank->delete_user(user);
                        delete user;
                        break;
                    }
                    case 4:
                    {
                        Manager *manager = new Manager();
                        manager->set_mediator(bank);
                        manager->set_info();
                        bank->add_manager(manager);
                        cout << "Add manager " << manager->get_name() << " successfully!" << endl;
                        break;
                    }
                    case 5:
                    {
                        string name;
                        cout << "Enter name of manager: ";
                        getline(cin, name);
                        Manager *manager = new Manager();
                        for (int i = 0; i < bank->managers.size(); i++)
                        {
                            if (bank->managers[i]->get_name() == name)
                            {
                                manager = bank->managers[i];
                                break;
                            }
                        }
                        bank->delete_manager(manager);
                        delete manager;
                        break;
                    }
                    case 6:
                    {
                        flag4 = true;
                        break;
                    }
                    default:
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                flag1 = true;
                break;
            }
            default:
                break;
            }
            break;
        }

        case 1:
        {
            User *user = new User();
            user->set_mediator(bank);
            user->set_info();
            adapterB->create_account(user, bank);
            cout << "Add user " << user->get_name() << " successfully!" << endl;
            break;
        }
        case 2:
        {
            flag1 = true;
            break;
        }
        default:
            break;
        }
    }
    delete adapterB;
    delete adapterM;
    delete adapterC;
    for(int i = 0; i < banks.size(); i++)
    {
        delete banks[i];
    }
    // delete bank;
    //still leak
    return 0;
}


// 2 vector trong class Bank tai sao k de private duoc ?
