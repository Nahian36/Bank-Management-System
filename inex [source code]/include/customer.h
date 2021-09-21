#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<bits/stdc++.h>
#include"common.h"
using namespace std;


class customer:public common //common class er ta inherit korse
{ private:
     int customer_id;
     static int count_login_pass;
     static int counterr;
     static int delete_op;
     static int customer_count_login;
     string customer_fullname;
     string customer_password;
     string customer_address;
     string customer_dob;
     string customer_phone;
     string customer_balance;
     const char* select_cust_id="SELECT customer_id FROM customer_login";
     const char* select_cust_id_pass="SELECT customer_id,customer_password FROM customer_login";
     const char* select_cust_username="SELECT customer_username FROM customers";
     const char* select_max_acc_no="SELECT MAX(customer_account_no) FROM customers";
     const char* select_all_from_cust="SELECT * FROM customers";
     const char* select_all_from_cust_balance="SELECT * FROM customer_balance";


public:

    void first_window();
    void customer_login_pass(int);
    void customer_create_new();
    void customer_user(int, string, string, string, string, string);
    void customer_pass(int, string, string, string, string, string, string);
    void customer_menu(int);
    void customer_menu_content();
    void customer_menu_select(int);
    void menu_toggling(int);
    void customer_update_content_select(int);
    void customer_update_content();
    void customer_update_toggling(int);
    void customer_update_insert(int, int);
    void customer_update_options(int);
    void customer_view_information(int);
    void customer_delete_account(int);
    void delete_select(int);
    void delete_option();
    void delete_choose(int);
    void customer_transaction(int);
    void balance_content();
    void balance_select(int);
    void balance_toggling(int);
    void customer_balance_deposit(int);
    void customer_balance_withdraw(int);
};
#endif // CUSTOMER_H
