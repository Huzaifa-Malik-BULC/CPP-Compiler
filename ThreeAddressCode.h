#pragma once
#include<iostream>
#include<fstream>
using namespace std;

struct ThreeAddress {
    char data[10];
    char temp[7];
};

void threeAddressCode(string input_file, string output_file) {
    ThreeAddress s[30];
    char d1[7], d2[7] = "t";
    int i = 0, j = 1, len = 0;

    ifstream f1(input_file);
    ofstream f2(output_file);

    while (f1 >> s[len].data) {
        len++;
    }

    _itoa(j, d1, 7);
    strcat(d2, d1);
    strcpy(s[j].temp, d2);
    strcpy(d1, "");
    strcpy(d2, "t");

    // Process the first operation outside the loop
    if (!strcmp(s[3].data, "*") || !strcmp(s[3].data, "/")) {
        f2 << s[j].temp << "=" << s[i + 2].data << s[i + 3].data << s[i + 4].data;
        j++;
    }
    else {
        f2 << s[j].temp << "=" << s[i + 2].data << s[i + 3].data << s[i + 4].data;
        j++;
    }

    for (i = 4; i < len - 2; i += 2) {
        _itoa(j, d1, 7);
        strcat(d2, d1);
        strcpy(s[j].temp, d2);

        if (!strcmp(s[i + 1].data, "*") || !strcmp(s[i + 1].data, "/"))
            f2 << "\n" << s[j].temp << "=" << s[j - 1].temp << s[i + 1].data << s[i + 2].data;
        else if (!strcmp(s[i + 1].data, "+") || !strcmp(s[i + 1].data, "-"))
            f2 << "\n" << s[j].temp << "=" << s[j - 1].temp << s[i + 1].data << s[i + 2].data;

        strcpy(d1, "");
        strcpy(d2, "t");
        j++;
    }

    f2 << "\n" << s[0].data << "=" << s[j - 1].temp;

    f1.close();
    f2.close();

}