#pragma once

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <string>

using namespace std;

class User;
class Manager;
class Bank;

class People
{
protected:
    string name, address, phone, mail;

public:
    People() { ; }
    People(string name, string address, string phone, string mail) : name(name), address(address), phone(phone), mail(mail) { set_email(); }
    People(string name, string address, string phone) : name(name), address(address), phone(phone) { set_email(); }
    ~People() { ; }
    void set_email();
    void set_name(string name);
    string get_name();
    string get_address();
    string get_phone();
    string get_mail();

    void set_info();
    void changeInfo();
};

string low(string s);

class Account
{
protected:
    string username, password;

public:
    Account() { ; }
    Account(string username, string password) : username(username), password(password) {}
    ~Account() { ; }
    string get_username();
    string get_password();
    void set_username(string username);
    void set_password(string password);
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
    Card() { ; }
    Card(MediatorUser *mediator, string type) : mediator(mediator), type(type), money_in_card(0) {}
    ~Card() { ; }
    void set_money_in_card(long long money_in_card);
    void set_type(string type);
    long long get_money_in_card();
    string get_type();
    void calc_all_money();
    bool find_card(string type);
    long long send_money_to_account();
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
    User() { ; }
    User(string name, string address, string phone, string mail, int ID, long long money) : People(name, address, phone, mail), ID(ID), money(money) {}
    User(string name, string address, string phone) : People(name, address, phone), ID(0), money(0) {}
    User(People p) : People(p), ID(0), money(0) {}
    ~User() { ; }

    void set_money(long long money);
    long long get_money();
    void set_ID(int ID);
    int get_ID();
    void set_account(Account account);
    Account get_account();
    void add_card(Card card);
    vector<Card> get_cards();
    void changePassword();
    void change_money();
    void showInfo();
    long long calc_money() override;
    bool findCard(string type) override;
    long long send_money_to_account() override;
    void set_mediator(MediatorBank *mediator);
    void send_money_to_other_user();
    void get_noti(string noti);
};

class AdapterManager
{
public:
    AdapterManager() { ; }
    ~AdapterManager() { ; }
    void change_money(User *user, Bank *bank) const;
};

class Manager : public People, public AdapterManager
{
protected:
    string ID, password;
    long long salary;
    MediatorBank *mediator;

public:
    Manager() { ; }
    Manager(string name, string address, string phone, string mail, string ID, long long salary) : People(name, address, phone, mail), ID(ID), salary(salary) {}
    ~Manager() { ; }

    long long get_salary();
    void set_salary(long long salary);
    void set_ID(string ID);
    void set_password(string password);
    string get_ID();
    string get_password();
    void set_info();
    void set_mediator(MediatorBank *mediator);
    virtual void requestChangeSalary();
    void send_noti_to_user();
    void showInfo();
};

class AdapterBank
{
public:
    AdapterBank() { ; }
    ~AdapterBank() { ; }
    void create_account(User *user, Bank *bank) const;
    void create_card(User *user, Bank *bank) const;
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
    Bank(string bankName, string location) : bankName(bankName), location(location)
    {
        managers.clear();
        users.clear();
    }
    ~Bank() { ; }
    void set_bankName(string bankName);
    void set_location(string location);
    string get_bankName();
    string get_location();
    void add_manager(Manager *manager);
    void add_user(User *user);
    void delete_manager(Manager *manager);
    void delete_user(User *user);
    void showListManager() const;
    void showListUser() const;
    void UpdateManager(Manager *manager);
    void UpdateUser(User *user);
    void processchangeSalary(Manager *manager);
    bool searchUser(string name);
    Manager *searchManager(string ID, string password);
    void send_money_to_other_user(User *user) override;
    void send_noti_to_user() override;
};

void adduserToBank(User *user, Bank *bank);
void init(vector<Bank *> banks);
void saveData(vector<Bank *> banks);
// void addManagerToBank();

class ClassAdapter : public Manager, public Bank
{
protected:
    Manager *manager;
    Bank *bank;

public:
    ClassAdapter() { ; }
    ClassAdapter(Manager *manager, Bank *bank) : manager(manager), bank(bank) {}
    ~ClassAdapter()
    {
        delete manager;
        delete bank;
    };
    void requestChangeSalary() override;
    void access(Manager *manager, Bank *bank);
};

void gotoxy(int x, int y);
void TextColor(int x);
void drawBox(int y);
int choiceMenu(vector<string> adj);
