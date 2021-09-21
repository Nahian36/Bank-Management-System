#ifndef COMMON_H
#define COMMON_H
#include<bits/stdc++.h>


class common
{
private:
    int load;
    char dig[3];
public:
    void loading();
    void logout();
    virtual void first_window()=0;
};

#endif // COMMON_H
