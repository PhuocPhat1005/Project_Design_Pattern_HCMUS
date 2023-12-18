#include "bank.cpp"

int main()
{
    Bank *bank = new Bank();

    AdapterBank *adapterB = new AdapterBank();
    AdapterManager *adapterM = new AdapterManager();
    ClassAdapter *adapterC = new ClassAdapter();

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

    bool flag1 = false;
    while (!flag1)
    {
        choice1 = choiceMenu({"Sign In", "Sign Up", "Exit"});
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
                vector<User *> users = bank->get_users();
                for (int i = 0; i < users.size(); i++)
                {
                    if (users[i]->get_account().get_username() == username && users[i]->get_account().get_password() == password)
                    {
                        user = users[i];
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
                Manager *pManager = bank->searchManager(ID, password);
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
                            vector<User *> users = bank->get_users();
                            for (int i = 0; i < users.size(); i++)
                            {
                                if (users[i]->get_name() == name)
                                {
                                    user = users[i];
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
                            flag3 = true;
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
                        vector<User *> users = bank->get_users();
                        for (int i = 0; i < users.size(); i++)
                        {
                            if (users[i]->get_name() == name)
                            {
                                user = users[i];
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
                        vector<Manager *> managers = bank->get_managers();
                        for (int i = 0; i < managers.size(); i++)
                        {
                            if (managers[i]->get_name() == name)
                            {
                                manager = managers[i];
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
    saveData(banks);
    system("cls");
    cout << "Exit successfully!\n";
    delete adapterB;
    delete adapterM;
    delete adapterC;
    for (int i = 0; i < banks.size(); i++)
    {
        delete banks[i];
    }
    // delete bank;
    // still leak
    return 0;
}
