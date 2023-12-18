#include "bank.h"

void People::set_email() // set email for user
{
    if (mail == "") // if user doesn't input email, email will be name + @gmail
    {
        mail = name + "@gmail.com";
        for (int i = 0; i < mail.length(); i++) // convert string to lowercase
            if (mail[i] == ' ')                 // if user input space, erase it
                mail.erase(mail.begin() + i);
    }
}

void People::set_name(string name) // set name for user
{
    this->name = name;
}

string People::get_name() // get name of user
{
    return name;
}

string People::get_address() // get address of user
{
    return address;
}

string People::get_phone() // get phone of user
{
    return phone;
}

string People::get_mail() // get mail of user
{
    return mail;
}

void People::set_info() // set info for user
{
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter phone: ";
    getline(cin, phone);
    cout << "Enter mail: ";
    getline(cin, mail);
}

void People::changeInfo() // change info for users
{
    string tmp = "";
    cout << "New Name (press -1 not to change): ";
    getline(cin, tmp);
    if (tmp != "-1")
        name = tmp;
    cout << "New Address (press -1 not to change): ";
    getline(cin, tmp);
    if (tmp != "-1")
        address = tmp;
    cout << "New Phone (press -1 not to change): ";
    getline(cin, tmp);
    if (tmp != "-1")
        phone = tmp;
    cout << "New Email (press -1 not to change): ";
    getline(cin, tmp);
    if (tmp != "-1")
        mail = tmp;
}

string low(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
    s[0] -= 32;
    return s;
}

string Account::get_username() // get username of user
{
    return username;
}

string Account::get_password() // get password of user
{
    return password;
}

void Account::set_username(string username) // set username for user
{
    this->username = username;
}

void Account::set_password(string password) // set password for user
{
    this->password = password;
}

long long Card::get_money_in_card() // get money of card
{
    return money_in_card;
}

string Card::get_type() // get type of card
{
    return type;
}

void Card::set_money_in_card(long long money_in_card) // set money for card
{
    this->money_in_card = money_in_card;
}

void Card::set_type(string type) // set type for card
{
    this->type = type;
}

void Card::calc_all_money()
{
    long long tmp = mediator->calc_money();
    cout << "All money: " << tmp << endl;
}

bool Card::find_card(string type) // find card
{
    return mediator->findCard(type);
}

long long Card::send_money_to_account() // send money to account
{
    return mediator->send_money_to_account();
}

void User::set_money(long long money)
{
    this->money = money;
}
long long User::get_money()
{
    return money;
}
void User::set_ID(int ID)
{
    this->ID = ID;
}
int User::get_ID()
{
    return ID;
}
void User::set_account(Account account)
{
    this->account = account;
}
Account User::get_account()
{
    return account;
}
void User::add_card(Card card)
{
    cards.push_back(card);
}
vector<Card> User::get_cards()
{
    return cards;
}
void User::changePassword()
{
    string password;
    cout << "Input new password: ";
    getline(cin, password);
    account.set_password(password);
}
void User::change_money()
{
    cout << "You are not allowed to change money!\n";
    return;
}
void User::showInfo()
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
long long User::calc_money()
{
    long long res = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        res += cards[i].get_money_in_card();
    }
    return res;
}
bool User::findCard(string type)
{
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i].get_type() == type)
            return true;
    }
    return false;
}
long long User::send_money_to_account()
{
    long long res = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        res += cards[i].get_money_in_card();
        cards[i].set_money_in_card(0);
    }
    return res;
}
void User::set_mediator(MediatorBank *mediator)
{
    this->mediator = mediator;
}
void User::send_money_to_other_user()
{
    mediator->send_money_to_other_user(this);
}
void User::get_noti(string noti)
{
    cout << "User " << name << " got a notification: " << noti << endl;
}

void AdapterManager::change_money(User *user, Bank *bank) const
{
    cout << "Change money of " << user->get_name() << " to: ";
    long long tmp;
    cin >> tmp;
    cin.ignore();
    cout << "Change money of " << user->get_name() << " from " << user->get_money() << " to " << tmp << " successfully!" << endl;
    user->set_money(tmp);
    return;
}

long long Manager::get_salary()
{
    return salary;
}
void Manager::set_salary(long long salary)
{
    this->salary = salary;
}
void Manager::set_ID(string ID)
{
    this->ID = ID;
}
void Manager::set_password(string password)
{
    this->password = password;
}
string Manager::get_ID()
{
    return ID;
}
string Manager::get_password()
{
    return password;
}
void Manager::set_info()
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
void Manager::set_mediator(MediatorBank *mediator)
{
    this->mediator = mediator;
}
void Manager::requestChangeSalary()
{
    cout << "Please waiting, admin will process your request!" << endl;
}
void Manager::send_noti_to_user()
{
    mediator->send_noti_to_user();
}
void Manager::showInfo()
{
    // People::showInfo();
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phone << endl;
    cout << "Email: " << mail << endl;
    cout << "ID: " << ID << endl;
    cout << "Salary: " << salary << endl;
}

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

void AdapterBank::create_card(User *user, Bank *bank) const
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

void Bank::set_bankName(string bankName)
{
    this->bankName = bankName;
}

string Bank::get_bankName()
{
    return bankName;
}
string Bank::get_location()
{
    return location;
}
void Bank::add_user(User *user)
{
    user->set_ID(users.size() + 1);
    users.push_back(user);
}
void Bank::delete_user(User *user)
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
void Bank::add_manager(Manager *manager)
{
    managers.push_back(manager);
}
void Bank::delete_manager(Manager *manager)
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
void Bank::showListUser() const
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
void Bank::showListManager() const
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
void Bank::UpdateUser(User *user)
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
void Bank::UpdateManager(Manager *manager)
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
void Bank::processchangeSalary(Manager *manager)
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
bool Bank::searchUser(string name)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->get_name() == name)
            return true;
    }
    return false;
}
Manager *Bank::searchManager(string ID, string password)
{
    for (int i = 0; i < managers.size(); i++)
    {
        if (managers[i]->get_ID() == ID && managers[i]->get_password() == password)
            return managers[i];
    }
}
void Bank::send_money_to_other_user(User *user)
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
void Bank::send_noti_to_user()
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

void ClassAdapter::requestChangeSalary()
{
    bank->processchangeSalary(manager);
    return;
}
void ClassAdapter::access(Manager *manager, Bank *bank)
{
    this->manager = manager;
    this->bank = bank;
}

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
