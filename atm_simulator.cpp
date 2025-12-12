#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <sstream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

class Account {
private:

    int bankname;
    string username;

    string accountnumber;
    long long cardnumber;
    string password;

    int availablefunds;


public:

    Account();
    Account(int banme, string uname, long long cnum, string pw, int afund);

    int getBankname();
    string getUsername();

    string getAccountnumber();
    long long getCardnumber();
    string getPassword();
    int getAvailablefunds();

    void update_availablefund(int money);

};

Account::Account() {

    bankname = 0;
    username = "";

    accountnumber = "";
    cardnumber = 11111111;
    password = "1111";

    availablefunds = 0;


}

Account::Account(int bname, string uname, long long cnum, string pw, int afund) {

    bankname = bname;
    username = uname;

    string a = to_string(rand() % (999 - 111 + 1) + 111);
    string b = to_string(rand() % (999 - 111 + 1) + 111);
    string c = to_string(rand() % (99999 - 11111 + 1) + 11111);
    accountnumber = a + "-" + b + "-" + c;

    cardnumber = cnum;
    password = pw;

    availablefunds = afund;

}

int Account::getBankname() {

    return this->bankname;
}

string Account::getUsername() {

    return username;
}

string Account::getAccountnumber() {

    return accountnumber;
}

long long Account::getCardnumber() {

    return cardnumber;
}

string Account::getPassword() {

    return password;
}

int Account::getAvailablefunds() {

    return availablefunds;
}

// 일단 history 제외

void Account::update_availablefund(int money) {
    availablefunds = availablefunds + money;
}




class Bank {

private:

    map <long long, Account> card_dict; // carnumber로 account 찾기
    map <string, long long> Account_dict;
    // 일단 두 가지 모두 하되, 나중에 복잡해 보인다면, card number로만 접근하자. card로만!


public:

    Bank();
    void makeAccount();

    Account GetAccountBycard_dict(long long cardnumber);
    long long GetAccountByAccount_dict(string Account);

    void adding_availablefundBycard_dict(long long cardnumber, int amount);
    void subtracting_availablefundBycard_dict(long long cardnumber, int amount);


    int GetavailablefundBycard_dict(long long cardnumber);

    int GetbanktypeBycard_dict(long long cardnumber);

    bool BankValidation(long long CardNumber) {
        if (card_dict.find(CardNumber) != card_dict.end()) {
            return true;
        }
        else {
            return false;
        }
    }
    bool BankValidation_Account(string AccountNumber) {
        if (Account_dict.find(AccountNumber) != Account_dict.end()) {
            return true;
        }
        else {
            return false;
        }
    }
};

Bank::Bank() {


}

void Bank::makeAccount() {

    int bname;
    string uname;

    string anum;
    // cnum은 private static
    string pw;

    int fund;
    long long cnum;


    cout << "Enter your name" << endl;
    cin >> uname;

    cout << "Enter your bank" << endl;
    cout << "(1) 우리은행 (2) 신한은행 (3) 하나은행 (4) 국민은행" << endl;
    while (true) {

        cin >> bname;

        try {

            if (bname < 1 || bname > 4)
                throw bname;
            else
                break;
        }
        catch (int bname) {
            cout << "That is not an option! : " << bname << endl;
            cout << "Enter your bank. Again!" << endl;
        }
    }

    cout << "Enter your password (4 digit number) " << endl;
    while (true) {

        string numlst = "0123456789";

        cin >> pw;
        try {

            if (pw.length() != 4)

                throw pw;


            for (int i = 0; i < 4; i++) {

                if (numlst.find(pw[i]) == string::npos)

                    throw pw;

            }

            break;
        }
        catch (string pw) {
            cout << "This is invalid password! : " << pw << endl;
            cout << "Enter your password. Again!" << endl;
        }
    }

    cout << "Enter your fund" << endl;

    while (true) {

        cin >> fund;
        try {
            if (fund < 0 || fund >50000000)
                throw fund;
            else
                break;
        }
        catch (int fund) {
            cout << "This Availablefund Could not Exist by The Law :" << fund << endl;
            cout << "Enter your fund. Again!" << endl;
        }
    }
    // int 범위를 넘어가는 값을 설정하면 어떻게 해야 할까..? 이 또한 처리를 할 수 있을까?

    int a = rand() % (9999 - 1000 + 1) + 1000;
    int b = rand() % (9999 - 1000 + 1) + 1000;
    int c = rand() % (9999 - 1000 + 1) + 1000;
    int d = rand() % (9999 - 1000 + 1) + 1000;
    long long A = 1000000000000;
    long long B = 100000000;
    long long C = 10000;

    cnum = a * A + b * B + c * C + d;

    cout << "This is your card number : " << a << "-" << b << "-" << c << "-" << d << endl;


    Account new_account(bname, uname, cnum, pw, fund);
    cout << "This is your account number : " << new_account.getAccountnumber() << endl;

    card_dict.insert(make_pair(new_account.getCardnumber(), new_account));
    Account_dict.insert(make_pair(new_account.getAccountnumber(), new_account.getCardnumber()));

}



// ACCOUNT => Present Account
Account Bank::GetAccountBycard_dict(long long cardnumber) {
    Account ACCOUNT = card_dict[cardnumber];
    return ACCOUNT;
}

long long Bank::GetAccountByAccount_dict(string Account) {
    long long cardnum = Account_dict[Account];
    return cardnum;
}

void Bank::adding_availablefundBycard_dict(long long cardnumber, int amount) {
    Account ACCOUNT = card_dict[cardnumber];
    ACCOUNT.update_availablefund(amount);
    card_dict[cardnumber] = ACCOUNT;
}


void Bank::subtracting_availablefundBycard_dict(long long cardnumber, int amount) {
    Account ACCOUNT = card_dict[cardnumber];
    ACCOUNT.update_availablefund(-amount);
    card_dict[cardnumber] = ACCOUNT;
}


int Bank::GetavailablefundBycard_dict(long long cardnumber) {
    Account ACCOUNT = card_dict[cardnumber];
    return ACCOUNT.getAvailablefunds();
}


int Bank::GetbanktypeBycard_dict(long long cardnumber) {
    Account ACCOUNT = card_dict[cardnumber];
    return ACCOUNT.getBankname();
}

class ATM {
protected:
    int PrimaryBankName; // 1 우리 2 신한 3 하나 4 국민
    long long* SerialNumber;
    string Type; //single or multi
    string Language; //uni or bi
    int InitialFund;
    Bank* myBank;
    long long AdminCard = 0000;
    vector<string> history;

public:
    ATM() {
        //default constructor
    }
    ATM(int PB, long long SN, string type, string language, int IF, Bank* a, long long AC) {
        InitialFund = int{ IF };
        SerialNumber = new long long(SN);
        PrimaryBankName = PB; // 1 우리 2 신한 3 하나 4 국민
        Type = type;
        Language = language;
        myBank = a;
        AdminCard = AC;
    }
    ~ATM() {
        delete SerialNumber;
    }
    int getPrimaryBankName() {
        return this->PrimaryBankName;
    }
    string getType() {
        return this->Type;
    }
    string getLanguage() {
        return this->Language;
    }
    int getSerialNumber() {
        return *(this->SerialNumber);
    }
    int getInitialFund() {
        return this->InitialFund;
    }



    void Transaction_korean(int sort, long long CardNumber) {

        int fee{ 0 };

        int run{ 0 };
        cout << "Start trading. Press 0 to start Press 1 to exit" << endl;

        for (;;) {
            cin >> run;
            if (run == 0 || run == 1) {
                break;
            }
            else {
                cout << "Press 0 to start Press 1 to exit, again" << endl;
            }
        }
        if (run == 0) {
            if (sort == 1) {
                int amount{ 0 };
                int billtype{ 0 };
                int billnum{ 0 };
                int billnum_1{ 0 };
                int count{ 0 };

                cout << "예금하실 수단을 선택하세요." << endl << "1.현금 2.수표" << endl;
                for (;;) {
                    cin >> billtype;
                    if (billtype == 1 || billtype == 2) {
                        break;
                    }
                    else {
                        cout << "다시 입력하세요." << endl;
                        cout << "1.현금 2.수표" << endl;
                    }
                }
                if (billtype == 1) {
                    cout << "예금에 사용하실 지폐를 선택하세요." << endl << "1.1000원권 2.5000원권 3.10000원권 4.50000원권" << endl;
                    for (;;) {
                        cin >> billnum;
                        if (billnum == 1 || billnum == 2 || billnum == 3 || billnum == 4) {
                            break;
                        }
                        else {
                            cout << "다시 입력하세요." << endl;
                            cout << "1.1000원권 2.5000원권 3.10000원권 4.50000원권" << endl;
                        }
                    }
                }
                else if (billtype == 2) {
                    cout << "예금에 사용하실 수표를 선택하세요." << endl << "1.10만원권 2.100만원권" << endl;
                    for (;;) {
                        cin >> billnum_1;
                        if (billnum_1 == 1 || billnum_1 == 2) {
                            break;
                        }
                        else {
                            cout << "다시 입력하세요." << endl;
                            cout << "1.10만원권 2.100만원권" << endl;
                        }
                    }
                    if (billnum_1 == 1) {
                        billnum = 5;
                    }
                    else if (billnum_1 == 2) {
                        billnum = 6;
                    }
                    else {
                        cout << "billnum ERROR" << endl;
                    }
                }
                else {
                    cout << "billtype ERROR" << endl;
                }

                cout << "금액권 수를 입력하세요" << endl;
                for (;;) {
                    cin >> count;
                    if (0 < count < 51) {
                        if (billnum == 1) {
                            amount = (count * 1000);

                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 2) {
                            amount = (count * 5000);

                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 3) {
                            amount = (count * 10000);

                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 4) {
                            amount = (count * 50000);

                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 5) {
                            amount = (count * 100000);
                            break;
                        }
                        else if (billnum == 6) {
                            amount = (count * 1000000);
                            break;
                        }
                    }
                    else {
                        cout << "금액권 수는 1개 이상 50개 이하만 입력 가능합니다. 다시 입력하세요." << endl;
                    }
                }
                myBank->adding_availablefundBycard_dict(CardNumber, amount - fee);
                cout << amount - fee << "원이 예금되었습니다" << endl; // 현재 잔액 넣을지 말지
                history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has deposited " + to_string(amount - fee) + "won.");
            }

            if (sort == 2) {
                int amount{ 0 };

                fee = 1000;


                cout << "출금하실 금액을 입력하세요." << endl;


                while (true) {
                    cin >> amount;
                    try {
                        if (amount % 10000 != 0 || InitialFund < amount - fee || myBank->GetAccountBycard_dict(CardNumber).getAvailablefunds() < amount + fee)
                            throw amount;
                        else
                            break;
                    }
                    catch (int amount) {
                        if (amount % 10000 != 0)
                            cout << "출금은 만원 단위로만 가능합니다. 다시 입력해주세요." << endl;
                        else if (InitialFund < amount - fee)
                            cout << "ATM기에 잔고가 부족합니다. 다시 입력해주세요" << endl;
                        else
                            cout << "계좌에 잔고가 부족합니다. 다시 입력해주세요" << endl;
                    }
                }

                cout << "출금에 사용하실 지폐를 선택하세요." << endl << "1.10000원권 2.50000원권" << endl;
                int cash_type_W = 0;

                while (true) {
                    cin >> cash_type_W;
                    try {
                        if (cash_type_W == 1 or 2)
                            break;
                        else
                            throw amount;
                    }
                    catch (int amount) { cout << "지폐 형식이 올바르지 않습니다. 다시 입력해주세요" << endl; }
                }

                InitialFund = InitialFund - amount + fee;
                myBank->adding_availablefundBycard_dict(CardNumber, -amount - fee);
                cout << amount << "원이 출금되었고," << "수수료는 " << fee << "입니다. 현재 잔액은" << myBank->GetavailablefundBycard_dict(CardNumber) << "원 입니다." << endl;
                history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + " withdrew " + to_string(amount) + "won.");

            }


            if (sort == 3) {
                string acceptor; // 받는사람 계좌
                int method{ 0 };
                int amount{ 0 }; // 송금할 금액
                long long real_cardnum{ 0 };
                cout << "거래방식을 선택하세요" << endl;
                cout << "1. 현금 송금, 2. 계좌 송금" << endl;
                for (;;) {
                    cin >> method;
                    if (method == 1 || method == 2) {
                        break;
                    }
                    else {
                        cout << "거래방식을 다시 선택하세요" << endl;
                        cout << "1. 현금 송금, 2. 계좌 송금" << endl;
                    }
                }
                cout << "송금하실 계좌번호를 입력하세요" << endl;
                for (;;) {
                    cin >> acceptor;
                    if (myBank->BankValidation_Account(acceptor) == true) {
                        real_cardnum = myBank->GetAccountByAccount_dict(acceptor);
                        break;
                    }
                    else {
                        cout << "송금하실 계좌번호를 다시 입력하세요." << endl;
                    }
                }
                if (method == 1) {
                    if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                        fee = 2000;
                    }
                    else { fee = 3000; }

                    cout << "송금하실 금액을 입력하세요." << endl;


                    while (true) {
                        cin >> amount;
                        try {
                            if (amount % 10000 != 0)
                                throw amount;
                            else
                                break;
                        }
                        catch (int amount) {
                            if (amount % 10000 != 0)
                                cout << "송금은 만원 단위로만 가능합니다. 다시 입력해주세요." << endl;
                        }
                    }

                    cout << "송금에 사용하실 지폐를 선택하세요." << endl << "1.10000원권 2.50000원권" << endl;
                    int cash_type_W = 0;

                    while (true) {
                        cin >> cash_type_W;
                        try {
                            if (cash_type_W == 1 or 2)
                                break;
                            else
                                throw amount;
                        }
                        catch (int amount) { cout << "지폐 형식이 올바르지 않습니다. 다시 입력해주세요." << endl; }
                    }

                    InitialFund += amount;
                    myBank->adding_availablefundBycard_dict(real_cardnum, amount - fee);
                    cout << amount - fee << "원이 송금되었습니다. 수수료는 " << fee << "입니다." << endl;
                    history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has transfered " + to_string(amount - fee) + "won to " + myBank->GetAccountBycard_dict(real_cardnum).getUsername() + ".");
                }
                else if (method == 2) {
                    if (myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
                        if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                            fee = 2000;
                        }
                        else {
                            fee = 3000;
                        }
                    }
                    cout << "송금할 금액을 입력하세요." << endl;
                    cin >> amount;
                    if (myBank->GetAccountBycard_dict(CardNumber).getAvailablefunds() < amount + fee) {
                        cout << "계좌 내 잔액이 부족합니다." << endl;
                    }
                    else {
                        myBank->adding_availablefundBycard_dict(CardNumber, -amount);
                        myBank->adding_availablefundBycard_dict(real_cardnum, amount - fee);
                        cout << amount - fee << "원이 송금되었습니다. 수수료는 " << fee << "입니다. 현재 잔액은" << myBank->GetavailablefundBycard_dict(CardNumber) << "원 입니다." << endl;
                        history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has transfered " + to_string(amount) + "won to " + myBank->GetAccountBycard_dict(real_cardnum).getUsername() + "won.");
                    }
                }
            }
        }
        else if (run == 1) {}
    }

    void Transaction_english(int sort, long long CardNumber) {

        int fee{ 0 };

        int run{ 0 };
        cout << "Start trading. Press 0 to start Press 1 to exit" << endl;

        for (;;) {
            cin >> run;
            if (run == 0 || run == 1) {
                break;
            }
            else {
                cout << "Press 0 to start Press 1 to exit, again" << endl;
            }
        }
        if (run == 0) {
            if (sort == 1) {
                int amount{ 0 };
                int billtype{ 0 };
                int billnum{ 0 };
                int billnum_1{ 0 };
                int count{ 0 };
                fee = 0;

                cout << "Select the type to deposit." << endl << "1.Cash 2.Check" << endl;
                for (;;) {
                    cin >> billtype;
                    if (billtype == 1 || billtype == 2) {
                        break;
                    }
                    else {
                        cout << "Type again." << endl;
                        cout << "1.Cash 2.Check" << endl;
                    }
                }
                if (billtype == 1) {
                    cout << "Select the cash type." << endl << "1.1000won 2.5000won 3.10000won 4.50000won" << endl;
                    for (;;) {
                        cin >> billnum;
                        if (billnum == 1 || billnum == 2 || billnum == 3 || billnum == 4) {
                            break;
                        }
                        else {
                            cout << "Type again." << endl;
                            cout << "1.1000won 2.5000won 3.10000won 4.50000won" << endl;
                        }
                    }
                }
                else if (billtype == 2) {
                    cout << "Select the check type." << endl << "1.100,000won 2.1,000,000won" << endl;
                    for (;;) {
                        cin >> billnum_1;
                        if (billnum_1 == 1 || billnum_1 == 2) {
                            break;
                        }
                        else {
                            cout << "Type again." << endl;
                            cout << "1.100,000won 2.1,000,000won" << endl;
                        }
                    }
                    if (billnum_1 == 1) {
                        billnum = 5;
                    }
                    else if (billnum_1 == 2) {
                        billnum = 6;
                    }
                    else {
                        cout << "billnum ERROR" << endl;
                    }
                }
                else {
                    cout << "billtype ERROR" << endl;
                }

                cout << "Enter the number of cash or check" << endl;
                for (;;) {
                    cin >> count;
                    if (0 < count < 51) {
                        if (billnum == 1) {
                            amount = (count * 1000);

                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 2) {
                            amount = (count * 5000);
                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 3) {
                            amount = (count * 10000);
                            InitialFund = InitialFund + amount + fee;
                            break;
                        }
                        else if (billnum == 4) {
                            amount = (count * 50000);
                            InitialFund = InitialFund + amount + fee;
                            break;
                        }
                        else if (billnum == 5) {
                            amount = (count * 100000);
                            break;

                        }
                        else if (billnum == 6) {
                            amount = (count * 1000000);
                            break;

                        }
                    }
                    else {
                        cout << "The number of cash or check must be between 1 and 50. Please enter again." << endl;
                    }
                }

                myBank->adding_availablefundBycard_dict(CardNumber, amount - fee);
                cout << amount - fee << "won has been deposited." << endl; // 현재 잔액 넣을지 말지
                history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has deposited " + to_string(amount - fee) + "won.");
            }

            if (sort == 2) {
                int amount{ 0 };

                fee = 1000;

                cout << "Enter the amount to withdraw." << endl;


                while (true) {
                    cin >> amount;
                    try {
                        if (amount % 10000 != 0 || InitialFund < amount - fee || myBank->GetAccountBycard_dict(CardNumber).getAvailablefunds() < amount + fee)
                            throw amount;
                        else
                            break;
                    }
                    catch (int amount) {
                        if (amount % 10000 != 0)
                            cout << "This can be only units of KRW 10,000. Please enter again." << endl;
                        else if (InitialFund < amount - fee)
                            cout << "ATM balance is insufficient. Please enter again." << endl;
                        else
                            cout << "Account balance is insufficient. Please enter again." << endl;
                    }
                }

                cout << "Select the banknote to use for withdrawal." << endl << "1.10,000 won 2.50,000 won" << endl;
                int cash_type_W = 0;

                while (true) {
                    cin >> cash_type_W;
                    try {
                        if (cash_type_W == 1 or 2)
                            break;
                        else
                            throw amount;
                    }
                    catch (int amount) { cout << "The banknote format is incorrect. Please enter again." << endl; }
                }

                InitialFund = InitialFund - amount + fee;
                myBank->adding_availablefundBycard_dict(CardNumber, -amount - fee);
                cout << amount << "won has been withdrawn. And the fee is " << fee << "won. Now the balance in the account is " << myBank->GetavailablefundBycard_dict(CardNumber) << "won." << endl;
                history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + " withdrew " + to_string(amount) + "won.");

            }

            if (sort == 3) {
                string acceptor; // 받는사람 계좌
                int method{ 0 };
                int amount{ 0 }; // 송금할 금액
                long long real_cardnum{ 0 };
                cout << "Choose your trading method." << endl;
                cout << "1. Cash transfer, 2. Account transfer" << endl;
                for (;;) {
                    cin >> method;
                    if (method == 1 || method == 2) {
                        break;
                    }
                    else {
                        cout << "Choose your trading method, again." << endl;
                        cout << "1. Cash transfer, 2. Account transfer" << endl;
                    }
                }
                cout << "Enter the account number to transfer." << endl;
                for (;;) {
                    cin >> acceptor;
                    if (myBank->BankValidation_Account(acceptor) == true) {
                        real_cardnum = myBank->GetAccountByAccount_dict(acceptor);
                        break;
                    }
                    else {
                        cout << "Enter the account number to transfer, again" << endl;
                    }
                }
                if (method == 1) {
                    if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                        fee = 2000;
                    }
                    else { fee = 3000; }

                    cout << "Enter the amount to transfer" << endl;


                    while (true) {
                        cin >> amount;
                        try {
                            if (amount % 10000 != 0)
                                throw amount;
                            else
                                break;
                        }
                        catch (int amount) {
                            if (amount % 10000 != 0)
                                cout << "Transfer is only possible in units of 10,000 won. Please enter again." << endl;
                        }
                    }

                    cout << "Select the banknote you would like to use for the transfer." << endl << "1.10000won 2.50000won" << endl;
                    int cash_type_W = 0;

                    while (true) {
                        cin >> cash_type_W;
                        try {
                            if (cash_type_W == 1 or 2)
                                break;
                            else
                                throw amount;
                        }
                        catch (int amount) { cout << "The banknote format is incorrect.Please enter again." << endl; }
                    }

                    InitialFund += amount;
                    myBank->adding_availablefundBycard_dict(real_cardnum, amount - fee);
                    cout << amount - fee << "won has been transfered. The fee is " << fee << "won." << endl;
                    history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has transfered " + to_string(amount - fee) + "won to " + myBank->GetAccountBycard_dict(real_cardnum).getUsername() + ".");
                }
                else if (method == 2) {
                    if (myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
                        if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                            fee = 2000;
                        }
                        else {
                            fee = 3000;
                        }
                    }
                    cout << "Enter the amount to transfer." << endl;
                    cin >> amount;
                    if (myBank->GetAccountBycard_dict(CardNumber).getAvailablefunds() < amount + fee) {
                        cout << "The balance in the account is insufficient." << endl;
                    }
                    else {
                        myBank->adding_availablefundBycard_dict(CardNumber, -amount - fee);
                        myBank->adding_availablefundBycard_dict(real_cardnum, amount);
                        cout << amount - fee << "won has been transfered. The fee is " << fee << "won. Now, the balance in the account is " << myBank->GetavailablefundBycard_dict(CardNumber) << "won." << endl;
                        history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has transfered " + to_string(amount) + "won to " + myBank->GetAccountBycard_dict(real_cardnum).getUsername() + "won.");
                    }
                }
            }
        }
        else if (run == 1) {}
    }


    void Authorization_korean() {

        long long CardNumber;
        int sort{ 0 };
        string password;
        cout << "카드번호를 입력해 주십시오. 중단하시려면 1번을 눌러주십시오." << endl;
        cin >> CardNumber;

        if (CardNumber == 1) {
        }
        else if (CardNumber == AdminCard) {
            cout << "Administrator, if you enter 'yes', you can check the transaction details." << endl;

            string admin_menu;
            while (true) {
                cin >> admin_menu;
                try {
                    if (admin_menu == "yes") { break; }
                    else { throw admin_menu; }
                }
                catch (string admin_menu) {
                    cout << "Wrong. Type again." << endl;
                }
            }

            if (admin_menu == "yes") {
                int N = history.size();
                fstream newfile;

                //쓰기
                remove("Transaction History.txt");

                newfile.open("Transaction History.txt", ios::out);  // open a file to perform write operation using file object
                if (newfile.is_open())     //checking whether the file is open
                {
                    for (int i = 0; i < N; i++) {
                        newfile << i + 1;
                        newfile << ". ";
                        newfile << history[i];
                        newfile << "\t";
                        newfile << "\n";
                    }
                    newfile.close(); //close the file object
                }


                //읽기
                newfile.open("Transaction History.txt", ios::in); //open a file to perform read operation using file object
                if (newfile.is_open()) {   //checking whether the file is open
                    string tp;
                    while (getline(newfile, tp)) {  //read data from file object and put it into string.
                        cout << tp;   //print the data of the string
                    }
                    newfile.close();
                }


            }

        }

        else if (myBank->BankValidation(CardNumber) == true && myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
            cout << "주거래은행과 일치합니다" << endl;
            cout << "1.예금 2.출금 3.송금 중 종류를 선택하세요" << endl;
            cin >> sort;
            for (int i{ 0 }; i < 5; i++) {
                cout << "비밀번호를 입력하세요." << endl;
                cin >> password;
                if (myBank->GetAccountBycard_dict(CardNumber).getPassword() == password) {
                    cout << "비밀번호가 일치합니다" << endl;
                    Transaction_korean(sort, CardNumber);
                    break;
                }
                else if (i == 4) {
                    cout << "비밀번호를 5회 틀렸습니다." << endl;
                }
                else {
                    cout << "비밀번호를 다시 입력하십시오. 현재 " << 4 - i << "회 남았습니다." << endl;
                }
            }
        }
        else if (CardNumber == AdminCard) {}
        else if (myBank->BankValidation(CardNumber) == false) {
            cout << "해당 은행에 등록되지 않은 카드입니다" << endl;
        }

        else if (myBank->GetAccountBycard_dict(CardNumber).getBankname() != PrimaryBankName) {
            cout << "주거래은행이 달라 거래가 불가능합니다." << endl;
        }

        else {
            cout << "알 수 없는 오류가 발생했습니다." << endl;
        }
    }

    void Authorization_english() {
        long long CardNumber;
        int sort{ 0 };
        string password;
        cout << "Enter your card number. If you want to exit, press 1." << endl;
        cin >> CardNumber;

        if (CardNumber == 1) {
        }
        else if (CardNumber == AdminCard) {
            cout << "Administrator, if you enter 'yes', you can check the transaction details." << endl;

            string admin_menu;
            while (true) {
                cin >> admin_menu;
                try {
                    if (admin_menu == "yes") { break; }
                    else { throw admin_menu; }
                }
                catch (string admin_menu) {
                    cout << "Wrong. Type again." << endl;
                }
            }

            if (admin_menu == "yes") {
                int N = history.size();
                fstream newfile;

                //쓰기
                remove("Transaction History.txt");

                newfile.open("Transaction History.txt", ios::out);  // open a file to perform write operation using file object
                if (newfile.is_open())     //checking whether the file is open
                {
                    for (int i = 0; i < N; i++) {
                        newfile << i + 1;
                        newfile << ". ";
                        newfile << history[i];
                        newfile << "\t";
                        newfile << "\n";
                    }
                    newfile.close(); //close the file object
                }


                //읽기
                newfile.open("Transaction History.txt", ios::in); //open a file to perform read operation using file object
                if (newfile.is_open()) {   //checking whether the file is open
                    string tp;
                    while (getline(newfile, tp)) {  //read data from file object and put it into string.
                        cout << tp;   //print the data of the string
                    }
                    newfile.close();
                }


            }

        }

        else if (myBank->BankValidation(CardNumber) == true && myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
            cout << "It corresponds to the primary bank." << endl;
            cout << "1.Deposit 2.Withdrawal 3.Transfer" << endl;
            cin >> sort;
            for (int i{ 0 }; i < 5; i++) {
                cout << "Enter your password" << endl;
                cin >> password;
                if (myBank->GetAccountBycard_dict(CardNumber).getPassword() == password) {
                    cout << "Correct password." << endl;
                    Transaction_english(sort, CardNumber);
                    break;
                }
                else if (i == 4) {
                    cout << "5 times wrong." << endl;
                }
                else {
                    cout << "Wrong password. Now " << 4 - i << "times you can try." << endl;
                }
            }
        }
        else if (CardNumber == AdminCard) {}
        else if (myBank->BankValidation(CardNumber) == false) {
            cout << "Unregisterd card." << endl;
        }

        else if (myBank->GetAccountBycard_dict(CardNumber).getBankname() != PrimaryBankName) {
            cout << "Accounts with different primary bank cannot be transacted." << endl;
        }

        else {
            cout << "ERROR" << endl;
        }
    }


};

class single_ATM : public ATM {
protected:
public:

    single_ATM(int PB, long long SN, string language, int IF, Bank* a, long long AC) {
        InitialFund = int{ IF };
        SerialNumber = new long long(SN);
        PrimaryBankName = PB; // 1 우리 2 신한 3 하나 4 국민
        Type = "single";
        Language = language;
        myBank = a;
        AdminCard = AC;
    }

    void start_ATM() {
        if (Language == "bi") {
            int language_selector{ 0 };
            cout << "언어를 선택하세요." << endl;
            cout << "Select language." << endl;
            cout << "1. 한국어    2. ENGLISH 3. EXIT" << endl;
            for (;;) {
                cin >> language_selector;
                if (language_selector == 1 || language_selector == 2 || language_selector == 3) {
                    break;
                }
                else {
                    cout << "언어를 다시 선택하세요." << endl;
                    cout << "Select language again." << endl;
                    cout << "1.한국어 2.ENGLISH 3. EXIT" << endl;
                }
            }
            if (language_selector == 1) {
                Authorization_korean();
            }
            else if (language_selector == 2) {
                Authorization_english();
            }
            else if (language_selector == 3) {

            }
            else {
                cout << "Error" << endl;
                cout << "에러가 발생했습니다." << endl;
            }
        }
        else if (Language == "uni") {
            Authorization_english(); //unilingual의 경우 default 값을 영어로 설정
        }
        else {
            cout << "Unvalid Language" << endl << "비정상적인 언어" << endl;
        }
    }

};

class multi_ATM : public ATM {
private:
    int fee = 1000;
public:

    multi_ATM(int PB, long long SN, string language, int IF, Bank* a, long long AC) {
        InitialFund = int{ IF };
        SerialNumber = new long long(SN);
        PrimaryBankName = PB; // 1 우리 2 신한 3 하나 4 국민
        Type = "multi";
        Language = language;
        myBank = a;
        AdminCard = AC;
    }



    void start_ATM() {
        if (Language == "bi") {
            int language_selector{ 0 };
            cout << "언어를 선택하세요." << endl;
            cout << "Select language." << endl;
            cout << "1. 한국어    2. ENGLISH 3. EXIT" << endl;
            for (;;) {
                cin >> language_selector;
                if (language_selector == 1 || language_selector == 2 || language_selector == 3) {
                    break;
                }
                else {
                    cout << "언어를 다시 선택하세요." << endl;
                    cout << "Select language again." << endl;
                    cout << "1.한국어 2.ENGLISH 3. EXIT" << endl;
                }
            }
            if (language_selector == 1) {
                Authorization_korean();
            }
            else if (language_selector == 2) {
                Authorization_english();
            }
            else if (language_selector == 3) {
            }
            else {
                cout << "Error" << endl;
                cout << "에러가 발생했습니다." << endl;
            }
        }
        else if (Language == "uni") {
            Authorization_english(); //unilingual의 경우 default 값을 영어로 설정
        }
        else {
            cout << "Unvalid Language" << endl << "비정상적인 언어" << endl;
        }
    }



    void Transaction_korean(int sort, long long CardNumber) {
        int run{ 0 };
        cout << "거래를 시작합니다. 시작하시려면 0번 나가시려면 1번을 눌러주세요" << endl;
        for (;;) {
            cin >> run;
            if (run == 0 || run == 1) {
                break;
            }
            else {
                cout << "잘못 누르셨습니다. 시작하시려면 0번 나가시려면 1번을 눌러주세요" << endl;
            }
        }
        if (run == 0) {
            if (sort == 1) {

                int amount{ 0 };
                int billtype{ 0 };
                int billnum{ 0 };
                int billnum_1{ 0 };
                int count{ 0 };
                if (myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
                    fee = 0;
                }
                else {
                    fee = 1000;
                }
                cout << "예금하실 수단을 선택하세요." << endl << "1.현금 2.수표" << endl;
                for (;;) {
                    cin >> billtype;
                    if (billtype == 1 || billtype == 2) {
                        break;
                    }
                    else {
                        cout << "다시 입력하세요." << endl;
                        cout << "1.현금 2.수표" << endl;
                    }
                }
                if (billtype == 1) {
                    cout << "예금에 사용하실 지폐를 선택하세요." << endl << "1.1000원권 2.5000원권 3.10000원권 4.50000원권" << endl;
                    for (;;) {
                        cin >> billnum;
                        if (billnum == 1 || billnum == 2 || billnum == 3 || billnum == 4) {
                            break;
                        }
                        else {
                            cout << "다시 입력하세요." << endl;
                            cout << "1.1000원권 2.5000원권 3.10000원권 4.50000원권" << endl;
                        }
                    }
                }
                else if (billtype == 2) {
                    cout << "예금에 사용하실 수표를 선택하세요." << endl << "1.10만원권 2.100만원권" << endl;
                    for (;;) {
                        cin >> billnum_1;
                        if (billnum_1 == 1 || billnum_1 == 2) {
                            break;
                        }
                        else {
                            cout << "다시 입력하세요." << endl;
                            cout << "1.10만원권 2.100만원권" << endl;
                        }
                    }
                    if (billnum_1 == 1) {
                        billnum = 5;
                    }
                    else if (billnum_1 == 2) {
                        billnum = 6;
                    }
                    else {
                        cout << "billnum ERROR" << endl;
                    }
                }
                else {
                    cout << "billtype ERROR" << endl;
                }

                cout << "금액권 수를 입력하세요" << endl;
                for (;;) {
                    cin >> count;
                    if (0 < count < 51) {
                        if (billnum == 1) {
                            amount = (count * 1000);
                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 2) {
                            amount = (count * 5000);
                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 3) {
                            amount = (count * 10000);
                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 4) {
                            amount = (count * 50000);
                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 5) {
                            amount = (count * 100000);
                            break;

                        }
                        else if (billnum == 6) {
                            amount = (count * 1000000);
                            break;

                        }
                    }
                    else {
                        cout << "금액권 수는 1개 이상 50개 이하만 입력 가능합니다. 다시 입력하세요." << endl;
                    }
                }


                myBank->adding_availablefundBycard_dict(CardNumber, amount - fee);
                cout << amount - fee << "원이 예금되었습니다" << endl; // 현재 잔액 넣을지 말지
                history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has deposited " + to_string(amount) + "won.");
            }
            if (sort == 2) {
                int amount{ 0 };
                if (myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
                    fee = 1000;
                }
                else { fee = 2000; }

                cout << "출금하실 금액을 입력하세요." << endl;


                while (true) {
                    cin >> amount;
                    try {
                        if (amount % 10000 != 0 || InitialFund < amount - fee || myBank->GetAccountBycard_dict(CardNumber).getAvailablefunds() < amount + fee)
                            throw amount;
                        else
                            break;
                    }
                    catch (int amount) {
                        if (amount % 10000 != 0)
                            cout << "출금은 만원 단위로만 가능합니다. 다시 입력해주세요." << endl;
                        else if (InitialFund < amount - fee)
                            cout << "ATM기에 잔고가 부족합니다. 다시 입력해주세요" << endl;
                        else
                            cout << "계좌에 잔고가 부족합니다. 다시 입력해주세요" << endl;
                    }
                }

                cout << "출금에 사용하실 지폐를 선택하세요." << endl << "1.10000원권 2.50000원권" << endl;
                int cash_type_W = 0;

                while (true) {
                    cin >> cash_type_W;
                    try {
                        if (cash_type_W == 1 or 2)
                            break;
                        else
                            throw amount;
                    }
                    catch (int amount) { cout << "지폐 형식이 올바르지 않습니다. 다시 입력해주세요" << endl; }
                }

                InitialFund = InitialFund - amount + fee;
                myBank->adding_availablefundBycard_dict(CardNumber, -amount - fee);
                cout << amount + fee << "원이 출금되었습니다" << "현재 잔액은" << myBank->GetavailablefundBycard_dict(CardNumber) << "원 입니다." << endl;
                history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "님이 " + to_string(amount) + "원 출금하셨습니다");

            }


            if (sort == 3) {
                string acceptor; // 받는사람 계좌
                int method{ 0 };
                int amount{ 0 }; // 송금할 금액
                long long real_cardnum{ 0 };
                cout << "거래방식을 선택하세요" << endl;
                cout << "1. 현금 송금, 2. 계좌 송금" << endl;
                for (;;) {
                    cin >> method;
                    if (method == 1 || method == 2) {
                        break;
                    }
                    else {
                        cout << "거래방식을 다시 선택하세요" << endl;
                        cout << "1. 현금 송금, 2. 계좌 송금" << endl;
                    }
                }
                cout << "송금하실 계좌번호를 입력하세요" << endl;
                for (;;) {
                    cin >> acceptor;
                    if (myBank->BankValidation_Account(acceptor) == true) {
                        real_cardnum = myBank->GetAccountByAccount_dict(acceptor);
                        break;
                    }
                    else {
                        cout << "송금하실 계좌번호를 다시 입력하세요." << endl;
                    }
                }
                if (method == 1) {
                    if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                        fee = 2000;
                    }
                    else { fee = 3000; }

                    cout << "송금하실 금액을 입력하세요." << endl;


                    while (true) {
                        cin >> amount;
                        try {
                            if (amount % 10000 != 0)
                                throw amount;
                            else
                                break;
                        }
                        catch (int amount) {
                            if (amount % 10000 != 0)
                                cout << "송금은 만원 단위로만 가능합니다. 다시 입력해주세요." << endl;
                        }
                    }

                    cout << "송금에 사용하실 지폐를 선택하세요." << endl << "1.10000원권 2.50000원권" << endl;
                    int cash_type_W = 0;

                    while (true) {
                        cin >> cash_type_W;
                        try {
                            if (cash_type_W == 1 or 2)
                                break;
                            else
                                throw amount;
                        }
                        catch (int amount) { cout << "지폐 형식이 올바르지 않습니다. 다시 입력해주세요." << endl; }
                    }

                    InitialFund += amount;
                    myBank->adding_availablefundBycard_dict(real_cardnum, amount - fee);
                    cout << amount - fee << "원이 송금되었습니다. 수수료는 " << fee << "입니다." << endl;
                    history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has transfered " + to_string(amount - fee) + "won to " + myBank->GetAccountBycard_dict(real_cardnum).getUsername() + ".");
                }
                else if (method == 2) {
                    if (myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
                        if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                            fee = 2000;
                        }
                        else {
                            fee = 3000;
                        }
                    }
                    else {
                        if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                            fee = 3000;
                        }
                        else {
                            fee = 4000;
                        }
                    }
                    cout << "송금할 금액을 입력하세요." << endl;
                    cin >> amount;
                    if (myBank->GetAccountBycard_dict(CardNumber).getAvailablefunds() < amount + fee) {
                        cout << "계좌 내 잔액이 부족합니다." << endl;
                    }
                    else {
                        myBank->adding_availablefundBycard_dict(CardNumber, -amount);
                        myBank->adding_availablefundBycard_dict(real_cardnum, amount - fee);
                        cout << amount - fee << "원이 송금되었습니다. 수수료는 " << fee << "입니다. 현재 잔액은" << myBank->GetavailablefundBycard_dict(CardNumber) << "원 입니다." << endl;
                        history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has transfered " + to_string(amount) + "won to " + myBank->GetAccountBycard_dict(real_cardnum).getUsername() + "won.");
                    }
                }
            }
        }
        else if (run == 1) {};
    }

    void Transaction_english(int sort, long long CardNumber) {
        int run{ 0 };
        cout << "Start trading. Press 0 to start Press 1 to exit" << endl;

        for (;;) {
            cin >> run;
            if (run == 0 || run == 1) {
                break;
            }
            else {
                cout << "Press 0 to start Press 1 to exit, again" << endl;
            }
        }
        if (run == 0) {
            if (sort == 1) {
                int amount{ 0 };
                int billtype{ 0 };
                int billnum{ 0 };
                int billnum_1{ 0 };
                int count{ 0 };
                if (myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
                    fee = 0;
                }
                else {
                    fee = 1000;
                }
                cout << "Select the type to deposit." << endl << "1.Cash 2.Check." << endl;
                for (;;) {
                    cin >> billtype;
                    if (billtype == 1 || billtype == 2) {
                        break;
                    }
                    else {
                        cout << "Type again." << endl;
                        cout << "1.Cash 2.Check" << endl;
                    }
                }
                if (billtype == 1) {
                    cout << "Select the cash type." << endl << "1.1000won 2.5000won 3.10000won 4.50000won" << endl;
                    for (;;) {
                        cin >> billnum;
                        if (billnum == 1 || billnum == 2 || billnum == 3 || billnum == 4) {
                            break;
                        }
                        else {
                            cout << "Type again." << endl;
                            cout << "1.1000won 2.5000won 3.10000won 4.50000won" << endl;
                        }
                    }
                }
                else if (billtype == 2) {
                    cout << "Select the check type." << endl << "1.100,000won 2.1,000,000won" << endl;
                    for (;;) {
                        cin >> billnum_1;
                        if (billnum_1 == 1 || billnum_1 == 2) {
                            break;
                        }
                        else {
                            cout << "Type again." << endl;
                            cout << "1.100,000won 2.1,000,000won" << endl;
                        }
                    }
                    if (billnum_1 == 1) {
                        billnum = 5;
                    }
                    else if (billnum_1 == 2) {
                        billnum = 6;
                    }
                    else {
                        cout << "billnum ERROR" << endl;
                    }
                }
                else {
                    cout << "billtype ERROR" << endl;
                }

                cout << "Enter the number of cash or check" << endl;
                for (;;) {
                    cin >> count;
                    if (0 < count < 51) {
                        if (billnum == 1) {
                            amount = (count * 1000);
                            InitialFund = InitialFund + amount + fee;
                            break;
                        }
                        else if (billnum == 2) {
                            amount = (count * 5000);
                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 3) {
                            amount = (count * 10000);
                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 4) {
                            amount = (count * 50000);
                            InitialFund = InitialFund + amount + fee;
                            break;

                        }
                        else if (billnum == 5) {
                            amount = (count * 100000);
                            break;

                        }
                        else if (billnum == 6) {
                            amount = (count * 1000000);
                            break;

                        }
                    }
                    else {
                        cout << "The number of cash or check must be between 1 and 50. Please enter again." << endl;
                    }
                }


                myBank->adding_availablefundBycard_dict(CardNumber, amount - fee);
                cout << amount - fee << "won has been deposited." << endl; // 현재 잔액 넣을지 말지
                history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has deposited " + to_string(amount) + "won.");
            }

            if (sort == 2) {
                int amount{ 0 };
                if (myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
                    fee = 1000;
                }
                else { fee = 2000; }

                cout << "Enter the amount to withdraw." << endl;


                while (true) {
                    cin >> amount;
                    try {
                        if (amount % 10000 != 0 || InitialFund < amount - fee || myBank->GetAccountBycard_dict(CardNumber).getAvailablefunds() < amount + fee)
                            throw amount;
                        else
                            break;
                    }
                    catch (int amount) {
                        if (amount % 10000 != 0)
                            cout << "This can be only units of KRW 10,000. Please enter again." << endl;
                        else if (InitialFund < amount - fee)
                            cout << "ATM balance is insufficient. Please enter again." << endl;
                        else
                            cout << "Account balance is insufficient. Please enter again." << endl;
                    }
                }

                cout << "Select the banknote to use for withdrawal." << endl << "1.10,000 won 2.50,000 won" << endl;
                int cash_type_W = 0;

                while (true) {
                    cin >> cash_type_W;
                    try {
                        if (cash_type_W == 1 or 2)
                            break;
                        else
                            throw amount;
                    }
                    catch (int amount) { cout << "The banknote format is incorrect. Please enter again." << endl; }
                }

                InitialFund = InitialFund - amount + fee;
                myBank->adding_availablefundBycard_dict(CardNumber, -amount - fee);
                cout << amount << "won has been withdrawn. And the fee is " << fee << "won. Now the balance in the account is " << myBank->GetavailablefundBycard_dict(CardNumber) << "won." << endl;
                history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has withdrawn " + to_string(amount) + "won.");

            }

            if (sort == 3) {
                string acceptor; // 받는사람 계좌
                int method{ 0 };
                int amount{ 0 }; // 송금할 금액
                long long real_cardnum{ 0 };
                cout << "Choose your trading method." << endl;
                cout << "1. Cash transfer, 2. Account transfer" << endl;
                for (;;) {
                    cin >> method;
                    if (method == 1 || method == 2) {
                        break;
                    }
                    else {
                        cout << "Choose your trading method, again." << endl;
                        cout << "1. Cash transfer, 2. Account transfer" << endl;
                    }
                }
                cout << "Enter the account number to transfer." << endl;
                for (;;) {
                    cin >> acceptor;
                    if (myBank->BankValidation_Account(acceptor) == true) {
                        real_cardnum = myBank->GetAccountByAccount_dict(acceptor);
                        break;
                    }
                    else {
                        cout << "Enter the account number to transfer, again" << endl;
                    }
                }
                if (method == 1) {
                    if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                        fee = 2000;
                    }
                    else { fee = 3000; }

                    cout << "Enter the amount to transfer" << endl;


                    while (true) {
                        cin >> amount;
                        try {
                            if (amount % 10000 != 0)
                                throw amount;
                            else
                                break;
                        }
                        catch (int amount) {
                            if (amount % 10000 != 0)
                                cout << "Transfer is only possible in units of 10,000 won. Please enter again." << endl;
                        }
                    }

                    cout << "Select the banknote you would like to use for the transfer." << endl << "1.10000won 2.50000won" << endl;
                    int cash_type_W = 0;

                    while (true) {
                        cin >> cash_type_W;
                        try {
                            if (cash_type_W == 1 or 2)
                                break;
                            else
                                throw amount;
                        }
                        catch (int amount) { cout << "The banknote format is incorrect.Please enter again." << endl; }
                    }

                    InitialFund += amount;
                    myBank->adding_availablefundBycard_dict(real_cardnum, amount - fee);
                    cout << amount - fee << "won has been transfered. The fee is " << fee << "won." << endl;
                    history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has transfered " + to_string(amount - fee) + "won to " + myBank->GetAccountBycard_dict(real_cardnum).getUsername() + ".");
                }
                else if (method == 2) {
                    if (myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
                        if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                            fee = 2000;
                        }
                        else {
                            fee = 3000;
                        }
                    }
                    else {
                        if (myBank->GetAccountBycard_dict(real_cardnum).getBankname() == PrimaryBankName) {
                            fee = 3000;
                        }
                        else {
                            fee = 4000;
                        }
                    }
                    cout << "Enter the amount to transfer." << endl;
                    cin >> amount;
                    if (myBank->GetAccountBycard_dict(CardNumber).getAvailablefunds() < amount + fee) {
                        cout << "The balance in the account is insufficient." << endl;
                    }
                    else {
                        myBank->adding_availablefundBycard_dict(CardNumber, -amount);
                        myBank->adding_availablefundBycard_dict(real_cardnum, amount - fee);
                        cout << amount - fee << "won has been transfered. The fee is " << fee << "won. Now, the balance in the account is " << myBank->GetavailablefundBycard_dict(CardNumber) << "won." << endl;
                        history.push_back(to_string(CardNumber) + " " + myBank->GetAccountBycard_dict(CardNumber).getUsername() + "has transfered " + to_string(amount) + "won to " + myBank->GetAccountBycard_dict(real_cardnum).getUsername() + "won.");
                    }
                }
            }
        }

        else if (run == 1) {}
    }

    void Authorization_korean() {
        long long CardNumber;
        int sort{ 0 };
        string password;
        cout << "카드 번호를 입력하세요. 종료하시려면 1을 눌러주세요." << endl;
        cin >> CardNumber;
        if (CardNumber == AdminCard) {
            cout << "Administrator, if you enter 'yes', you can check the transaction details." << endl;

            string admin_menu;
            while (true) {
                cin >> admin_menu;
                try {
                    if (admin_menu == "yes") { break; }
                    else { throw admin_menu; }
                }
                catch (string admin_menu) {
                    cout << "Wrong. Type again." << endl;
                }
            }

            if (admin_menu == "yes") {
                int N = history.size();
                fstream newfile;

                //쓰기
                remove("Transaction History.txt");

                newfile.open("Transaction History.txt", ios::out);  // open a file to perform write operation using file object
                if (newfile.is_open())     //checking whether the file is open
                {
                    for (int i = 0; i < N; i++) {
                        newfile << i + 1;
                        newfile << ". ";
                        newfile << history[i];
                        newfile << "\t";
                        newfile << "\n";
                    }
                    newfile.close(); //close the file object
                }


                //읽기
                newfile.open("Transaction History.txt", ios::in); //open a file to perform read operation using file object
                if (newfile.is_open()) {   //checking whether the file is open
                    string tp;
                    while (getline(newfile, tp)) {  //read data from file object and put it into string.
                        cout << tp << endl;   //print the data of the string
                    }
                    newfile.close();
                }


            }

        }

        else if (CardNumber == 1) {
            cout << "EXIT" << endl;
        }

        else if (myBank->BankValidation(CardNumber) == true && myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
            cout << "주거래은행과 일치합니다." << endl;
            cout << "1.예금 2.출금 3.송금" << endl;
            cin >> sort;
            for (int i{ 0 }; i < 5; i++) {
                cout << "비밀번호를 입력하십시오." << endl;
                cin >> password;
                if (myBank->GetAccountBycard_dict(CardNumber).getPassword() == password) {
                    cout << "비밀번호가 일치합니다." << endl;
                    Transaction_korean(sort, CardNumber);
                    break;
                }
                else if (i == 4) {
                    cout << "비밀번호를 5회 틀리셨습니다." << endl;
                }
                else {
                    cout << "비밀번호가 틀렸습니다. 현재 " << 4 - i << "회 남았습니다." << endl;
                }
            }
        }
        else if (CardNumber == AdminCard) {}
        else if (myBank->BankValidation(CardNumber) == false) {
            cout << "등록되지 않은 카드입니다." << endl;
        }
        else if (myBank->GetAccountBycard_dict(CardNumber).getBankname() != PrimaryBankName) {
            cout << "주거래은행이 달라 수수료가 발생합니다." << endl;
            cout << "1.예금 2.출금 3.송금" << endl;
            cin >> sort;
            for (int i{ 0 }; i < 3; i++) {
                cout << "비밀번호를 입력하십시오." << endl;
                cin >> password;
                if (myBank->GetAccountBycard_dict(CardNumber).getPassword() == password) {
                    cout << "비밀번호가 일치합니다." << endl;
                    Transaction_korean(sort, CardNumber);
                    break;
                }
                else if (i == 2) {
                    cout << "비밀번호를 3회 틀리셨습니다." << endl;
                }
                else {
                    cout << "비밀번호가 틀렸습니다. 현재 " << 2 - i << "회 남았습니다." << endl;
                }
            }
        }
        else {
            cout << "오류가 발생했습니다." << endl;
        }
    }

    void Authorization_english() {
        long long CardNumber;
        int sort{ 0 };
        string password;
        cout << "Enter your card number. If you want to exit, press 1." << endl;
        cin >> CardNumber;

        if (CardNumber == AdminCard) {
            cout << "Administrator, if you enter 'yes', you can check the transaction details." << endl;

            string admin_menu;
            while (true) {
                cin >> admin_menu;
                try {
                    if (admin_menu == "yes") { break; }
                    else { throw admin_menu; }
                }
                catch (string admin_menu) {
                    cout << "Wrong. Type again." << endl;
                }
            }

            if (admin_menu == "yes") {
                int N = history.size();
                fstream newfile;

                //쓰기
                remove("Transaction History.txt");

                newfile.open("Transaction History.txt", ios::out);  // open a file to perform write operation using file object
                if (newfile.is_open())     //checking whether the file is open
                {
                    for (int i = 0; i < N; i++) {
                        newfile << i + 1;
                        newfile << ". ";
                        newfile << history[i];
                        newfile << "\t";
                        newfile << "\n";
                    }
                    newfile.close(); //close the file object
                }


                //읽기
                newfile.open("Transaction History.txt", ios::in); //open a file to perform read operation using file object
                if (newfile.is_open()) {   //checking whether the file is open
                    string tp;
                    while (getline(newfile, tp)) {  //read data from file object and put it into string.
                        cout << tp;   //print the data of the string
                    }
                    newfile.close();
                }


            }

        }

        if (CardNumber == 1) {
            cout << "EXIT" << endl;
        }

        else if (myBank->BankValidation(CardNumber) == true && myBank->GetAccountBycard_dict(CardNumber).getBankname() == PrimaryBankName) {
            cout << "It corresponds to the primary bank" << endl;
            cout << "1.Deposit, 2.Withdrawal, 3.Transfer" << endl;
            cin >> sort;
            for (int i{ 0 }; i < 3; i++) {
                cout << "Enter your password." << endl;
                cin >> password;
                if (myBank->GetAccountBycard_dict(CardNumber).getPassword() == password) {
                    cout << "Correct password" << endl;
                    Transaction_english(sort, CardNumber);
                    break;
                }
                else if (i == 2) {
                    cout << "3 times wrong." << endl;
                }
                else {
                    cout << "Wrong password. Now " << 2 - i << "times you can try." << endl;
                }
            }
        }
        else if (CardNumber == AdminCard) {}
        else if (myBank->BankValidation(CardNumber) == false) {
            cout << "Unregisterd card." << endl;
        }
        else if (myBank->GetAccountBycard_dict(CardNumber).getBankname() != PrimaryBankName) {
            cout << "Accounts with different primary bank incur additional fees" << endl;
            cout << "1.Deposit, 2.Withdrawal, 3.Transfer" << endl;
            cin >> sort;
            for (int i{ 0 }; i < 5; i++) {
                cout << "Enter your password." << endl;
                cin >> password;
                if (myBank->GetAccountBycard_dict(CardNumber).getPassword() == password) {
                    cout << "Correct password" << endl;
                    Transaction_english(sort, CardNumber);
                    break;
                }
                else if (i == 4) {
                    cout << "5 times wrong." << endl;
                }
                else {
                    cout << "Wrong password. Now " << 4 - i << "times you can try." << endl;
                }
            }
        }
        else {
            cout << "ERROR" << endl;
        }
    }
};






int main()

{
    Bank b1;
    single_ATM ATM1 = single_ATM(1, 111111, "uni", 50000, &b1, 0000); //(1) 우리은행 (2) 신한은행 (3) 하나은행 (4) 국민은행
    multi_ATM ATM2 = multi_ATM(2, 222222, "bi", 50000, &b1, 0000);
    multi_ATM ATM3 = multi_ATM(2, 333333, "bi", 50000, &b1, 0000);

    cout << "<ATM1>" << endl;
    cout << "serial number: " << ATM1.getSerialNumber() << endl;
    cout << "type: " << ATM1.getType() << endl;
    cout << "language: " << ATM1.getLanguage() << endl;
    cout << "initial fund: " << ATM1.getInitialFund() << endl;

    b1.makeAccount();
    b1.makeAccount();
    b1.makeAccount();

    for (;;) {
        cout << "ATM을 선택하십시오" << endl;
        int a{ 0 };
        cin >> a;


        if (a == 1) {
            ATM1.start_ATM();
        }
        else if (a == 2) {
            ATM2.start_ATM();
        }
        else if (a == 3) {
            ATM3.start_ATM();
        }

        else {

            cout << b1.GetAccountBycard_dict(1041146773349500).getAvailablefunds() << endl;
            cout << b1.GetAccountBycard_dict(3358996274646705).getAvailablefunds() << endl;
            cout << b1.GetAccountBycard_dict(1961149139953942).getAvailablefunds() << endl;

            cout << ATM1.getInitialFund() << endl;
            cout << ATM2.getInitialFund() << endl;
            cout << ATM3.getInitialFund() << endl;


        }




    }
    return 0;
}