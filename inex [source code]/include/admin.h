#ifndef ADMIN_H
#define ADMIN_H
#include<common.h>
#include<bits/stdc++.h>
using namespace std;

class admin:public common //common class er ta inherit korse
{
private:
    static int count_pass;
    static int count_login;
    static int counter;
    static int delete_opt;
    string admin_username;
    string admin_password;
    string id_in_string;
    string search_content;
    char admin_password_temp[20];
    const char* select_pass="SELECT passcode FROM passcode WHERE serial=1";
    const char* select_admin_name="SELECT admin_name FROM admin_login";
    const char* select_admin_name_and_pass="SELECT admin_name,admin_password FROM admin_login";
    const char* select_cust_acc_no="SELECT customer_account_no FROM customers";
    const char* select_all_from_cust="SELECT * FROM customers";
    const char* select_all_from_cust_baln="SELECT * FROM customer_balance";
    const char* select_all_from_cust_del_info="SELECT * FROM customer_delete_request_information";
    const char* select_all_from_cust_del_baln="SELECT * FROM customer_delete_request_balance";
    const char* select_cust_acc_from_del="SELECT customer_account_no FROM customer_delete_request_information";
    const char* select_all_from_deltd_info="SELECT * FROM customer_deleted_information";
    const char* select_all_from_deltd_baln="SELECT * FROM customer_deleted_balance";
    const char* select_acc_no_from_deltd_info="SELECT customer_account_no FROM customer_deleted_information";

public:
    void first_window();
    void admin_login();
    void admin_login_pass(string);
    void admin_create_new();
    void admin_user();
    void admin_pass(string);
    void admin_menu();
    void admin_menu_content();
    void admin_menu_select(int);
    void menu_toggling();
    void admin_search_any_account();
    void admin_search_any_information();
    void admin_delete_any_account();
    void admin_delete_account(int,int);
    void admin_delete_option();
    void admin_delete_select(int);
    void admin_delete_choose(int,int);
    void requested_or_deleted_account();
    void requested_or_deleted_account_select(int);
    void requested_or_deleted_account_content();
    void requested_or_deleted_account_toggling();
    void account_deletion_request();
    void delete_request_account_select(int);
    void delete_request_account_content();
    void delete_request_account_toggling();
    void delete_request_account_personal_information();
    void delete_request_account_balance_information();
    void delete_request_account_delete();
    void deleted_account();
    void deleted_account_select(int);
    void deleted_account_content();
    void deleted_account_toggling();
    void deleted_account_personal_information();
    void deleted_account_balance_information();
    void hard_delete_account();
    void permanent_delete_account(int);
    void permanent_delete_choose(int);
    void admin_update_any_account();
    void admin_update_content_select(int);
    void admin_update_content();
    void admin_update_toggling(int);
    void admin_update_insert(int, int);
    void admin_update_options(int);
    void admin_view_all();
    void admin_view_balance();
};



#endif // ADMIN_H
