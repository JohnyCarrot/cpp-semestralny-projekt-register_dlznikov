#pragma once

#include <iostream>
#include <sstream>
#include <assert.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
class Node
{
public:
    std::string key;
    Node* next;

};
//1.uloha
class Register {
    std::vector<std::string> IDcka;
    std::uintmax_t velkost_suboru;
public:
    Node* head = nullptr;
    void push(const std::string key);
    void deleteAllNodes(Node** head_ref);
    inline bool test_suboru ()const;
    Register();
    void inicializacia();
    void nacitaj_zo_suboru(const std::string& nazov_suboru);
  std::string vloz_pohladavku(const std::string &pohladavka);
  std::string citaj_subor() const;
  std::string premaz_subor();
  std::string hladaj_podla_id(const std::string &hladane_id)const;
    std::string hladaj_podla_veritela(const std::string &hladane_id)const;
    std::string hladaj_podla_dlznika(const std::string &hladane_id)const;
    std::string pocet_vsetkych_pohladaviek() const;
    int suma_vsetkych_pohladaviek() const;

};


